/**
*
* \file
*
* \brief Definition of Xcp_DaqProcessor().
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_daq.c 22409 2011-04-22 10:40:28Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"
#if defined( XCP_ON_CAN )
    #include "xcpcan_auto_confpriv.h"
#elif defined( XCP_ON_IP )
    #include "xcpip_auto_confpriv.h"
#endif

#ifdef XCP_ENABLE

/**
 * This function samples data for a single DAQ list and transmits each ODT within the DAQ list to the
 * XCP master.
 *
 * If XCP_ATOMIC_DATA_SAMPLING_PER_ODT or XCP_ATOMIC_DATA_SAMPLING_PER_DAQ_LIST are configured then interrupts are
 * disabled during the sampling of each ODT or DAQ list as appropriate.
 * Otherwise it is the user's responsibility to ensure that the task executing this function is not
 * pre-empted in such a way as to cause data to be modified while it is being sampled.
 *
 * \param [in] daqListId    The ID of the DAQ list to be sampled.
 * \param [in] sessionId    The ID of the session containing the DAQ list to be sampled.
 * \param [in] pSessionCfg  The configuration of the session containing the DAQ list to be sampled.
 *
 * \return If this function finds no errors but does not sample any measurement data it returns
 * XCPEVENT_DAQSTIM_NOT_EXECUTED. This occurs if the first ODT entry of the first ODT of the specified
 * DAQ list is not configured, in which case the XCP specification tells us to skip the DAQ list.
 *
 * Otherwise, the function returns at least one of these values ORed together:
 *  - XCPEVENT_DAQSTIM_EXECUTED At least one DTO associated with the DAQ list was successfully sampled.
 *  - XCPEVENT_DAQ_OVERLOAD     At least one of the DTOs associated with the previous raster of this DAQ list has
 *                              not yet been transmitted. Not all the DTOs of the current raster were sampled.
 *  - XCPEVENT_DTO_OVERFILL     At least one DTO of the DAQ list is configured to sample more data than it can hold.
 *                              Measurement values which would fall partially or entirely outside the DTO will not be sampled.
 * Note that these three values are not mutually-exclusive.
 */
uint XCP_FN_TYPE Xcp_DaqProcessor(
    const uint                 daqListId,
    const uint                 sessionId,
    Xcp_SessionConfig_t* const pSessionCfg
)
{
    Xcp_StatePtr8          pDtoPacket;
    Xcp_StatePtr8          pDtoPacketStart;
    uint                   odtId;
    uint                   odtEntryId;
    Xcp_DaqConfig_t* const pDaqCfg         = pSessionCfg->pDaqConfigs + daqListId;
    uint                   numOdtEntries   = pDaqCfg->numOdtEntries;               /* We assume, at first, that this session does not use dynamic DAQs. */
    uint                   numOdt          = pDaqCfg->numOdt;                      /* We assume, at first, that this session does not use dynamic DAQs. */
    Xcp_OdtEntryAddr_t*    pOdtEntryAddr   = pSessionCfg->pOdtEntryAddrs + pDaqCfg->idxDaqStart;
    Xcp_StatePtr8          pOdtEntryCfg    = pSessionCfg->pOdtEntryCfgs + pDaqCfg->idxDaqStart;
    const uint             isPidOff        = pSessionCfg->pDaqStates[daqListId].daqListMode & XCP_DAQLISTMODE_PIDOFF;
    const uint             isTimestamped   = ( pSessionCfg->numBytesTimestamp != 0 ) && ( pSessionCfg->pDaqStates[daqListId].daqListMode & (uint8)XCP_DAQLISTMODE_TIMESTAMP );
    uint                   retValue        = XCPEVENT_DAQSTIM_NOT_EXECUTED;

#ifdef XCP_ENABLE_DYNDAQ
    if( pSessionCfg->maxDynDaqLists > 0 )
    {
        /* This session uses dynamic DAQs. */
        numOdt = pSessionCfg->pDaqDynConfigs[ daqListId ].numOdt;
    }
    else
#endif /* XCP_ENABLE_DYNDAQ */

    /* If the first ODT entry of the first ODT of this DAQ list is not configured we can skip the
     * rest of the DAQ list (see XCP specification part 1 section 1.1.3.1). */
    if( 0 == *pOdtEntryCfg )
    {
        return XCPEVENT_DAQSTIM_NOT_EXECUTED;
    }

#ifdef XCP_ATOMIC_DATA_SAMPLING_PER_DAQ_LIST
    XCP_DISABLE_ALL_INTERRUPTS();
#endif

    /* Iterate over all ODTs in this DAQ list; note there may be no ODTs in this DAQ list. */
    for( odtId = 0; odtId < numOdt; ++odtId )
    {
        /* If this ODT begins with an ODT entry which is not configured we can skip this ODT.
         * (see XCP specification part 1 section 1.1.3.1) */
        if( 0 == *pOdtEntryCfg )
        {
            pOdtEntryAddr += pDaqCfg->numOdtEntries;
            pOdtEntryCfg  += pDaqCfg->numOdtEntries;
            continue;
        }

        /* Get a TX buffer from our transport layer. */
        pDtoPacket = pDtoPacketStart = (pSessionCfg->pGetTxBuf)( sessionId, daqListId + XCP_FIRST_DAQ_CHANNEL );
        if( !pDtoPacket )
        {
            /* No TX buffer is available; this is an error. There should be enough TX buffers for a complete cycle of
             * this DAQ list; probably transmission of the previous cycle of this DAQ list is not yet complete.
             * We make no attempt to recover from this.
             */
            retValue |= XCPEVENT_DAQ_OVERLOAD;
            break;
        }

        /* If the DAQ list is not in PID_OFF mode, write a PID to the DTO packet buffer. */
        if( !isPidOff )
        {
            pDtoPacket[0] = pDaqCfg->firstPid + (uint8)odtId;
            ++pDtoPacket;
        }

        /* If a timestamp is configured, write one to the first DTO packet of the DAQ list. */
        if( odtId == 0ul && isTimestamped )
        {
            Xcp_GetTimestamp( pDtoPacket, pSessionCfg->numBytesTimestamp );
            pDtoPacket += pSessionCfg->numBytesTimestamp;
        }

#ifdef XCP_ENABLE_DYNDAQ
        /* Find the number of ODT entries in the current ODT. */
        if( pSessionCfg->maxDynDaqLists > 0 )
        {
            /* This session uses dynamic DAQs. */
            numOdtEntries = pSessionCfg->pDaqDynConfigs[ daqListId ].odtEntryNums[ odtId ];
        }
        else
        {
            /* This session does not use dynamic DAQs; numOdtEntries will already have been set correctly. */
        }
#endif /* XCP_ENABLE_DYNDAQ */

#ifdef XCP_ATOMIC_DATA_SAMPLING_PER_ODT
        XCP_DISABLE_ALL_INTERRUPTS();
#endif

        /* Copy the ODT entries for the current ODT into the DTO packet buffer. */
        for( odtEntryId = 0; odtEntryId < numOdtEntries; ++odtEntryId )
        {
            /* As soon as we find an ODT entry which is not configured we can skip to the next ODT.
             * (see XCP specification part 1 section 1.1.3.1) */
            if( 0 == *pOdtEntryCfg )
            {
                break;
            }

            if( *pOdtEntryCfg & XCP_ODTENTRY_SINGLE_BIT )
            {
                /* The current ODT entry refers to a single bit. */

                /* Is the DTO packet too full to accept the current ODT entry? */
                if( pDtoPacket + 1 - pDtoPacketStart > pSessionCfg->maxDtoLen )
                {
                    retValue |= XCPEVENT_DTO_OVERFILL;
                    break;
                }

                /* According to the XCP specification the bit offset can be from 0 to 31. However, recall that our
                 * implementation of WRITE_DAQ adjusts the bit offset to be from 0 to 7. */
                *pDtoPacket = (uint8)( ( ( *( XCP_UNPACK_ODTENTRY_BYTEADDR( *pOdtEntryAddr, *pOdtEntryCfg ) ) ) >>
                                         XCP_UNPACK_ODTENTRY_BITOFFSET( *pOdtEntryAddr, *pOdtEntryCfg ) ) & 0x1 );
                ++pDtoPacket;
            }
            else
            {
                /* The current ODT entry refers to a whole number of bytes. */

                /* Is the DTO packet too full to accept the current ODT entry? */
                if( pDtoPacket + XCP_UNPACK_ODTENTRY_NUMBYTES( *pOdtEntryAddr, *pOdtEntryCfg ) - pDtoPacketStart >
                    pSessionCfg->maxDtoLen )
                {
                    retValue |= XCPEVENT_DTO_OVERFILL;
                    break;
                }

                Xcp_MemCopy( pDtoPacket,
                             XCP_UNPACK_ODTENTRY_BYTEADDR( *pOdtEntryAddr, *pOdtEntryCfg ),
                             XCP_UNPACK_ODTENTRY_NUMBYTES( *pOdtEntryAddr, *pOdtEntryCfg ) );
                pDtoPacket += XCP_UNPACK_ODTENTRY_NUMBYTES( *pOdtEntryAddr, *pOdtEntryCfg );
            }
            ++pOdtEntryAddr;
            ++pOdtEntryCfg;
        }

        /* Each of the following pointers refers to an array which has 1 element per ODT entry for all ODTs in the
         * current DAQ list. If there are unconfigured ODT entries in the current ODT (or, in the case of a dynamic
         * DAQ list, if some of the ODT entries in the current ODT are undefined), then these pointers must be
         * advanced so as to skip to the start of the next ODT.
         */
        pOdtEntryAddr += pDaqCfg->numOdtEntries - odtEntryId;
        pOdtEntryCfg  += pDaqCfg->numOdtEntries - odtEntryId;

#ifdef XCP_ATOMIC_DATA_SAMPLING_PER_ODT
        XCP_ENABLE_ALL_INTERRUPTS();
#endif
        /* If the DTO packet buffer contains any ODT entries, transmit it. Note that odtEntryId will be zero if
         * there are no ODT entries in the current ODT. */
        if( odtEntryId > 0 )
        {
            (pSessionCfg->pTxNext)( sessionId, daqListId + XCP_FIRST_DAQ_CHANNEL, pDtoPacket - pDtoPacketStart );
            retValue |= XCPEVENT_DAQSTIM_EXECUTED;
        }
    }

#ifdef XCP_ATOMIC_DATA_SAMPLING_PER_DAQ_LIST
    XCP_ENABLE_ALL_INTERRUPTS();
#endif

    return retValue;
}

#endif /* XCP_ENABLE */
