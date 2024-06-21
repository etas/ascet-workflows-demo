/**
*
* \file
*
* \brief Definition of Xcp_StimProcessor().
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_stim.c 22416 2011-04-25 09:06:24Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"

#if defined( XCP_ENABLE ) && defined ( XCP_ENABLE_STIM )

/**
 * This function receives data for a single STIM list and writes each ODT within the STIM list to the
 * ECU's memory.
 *
 * If this function detects that an ODT is missing from within the STIM list it discards all ODTs of the
 * current raster of the STIM list and returns an error value.
 * In order to detect missing ODTs the function assumes that the XCP master transmits the ODTs within a
 * STIM list in order of ascending PID.
 *
 * \param [in] daqListId    The ID of the STIM list to be received.
 * \param [in] sessionId    The ID of the session containing the STIM list.
 * \param [in] pSessionCfg  The configuration of the session containing the STIM list.
 *
 * \return If this function finds no errors but does not write any data to the ECU's memory it returns
 * XCPEVENT_DAQSTIM_NOT_EXECUTED. This occurs if the first ODT entry of the first ODT of the specified STIM
 * list is not configured, in which case the XCP specification tells us to skip the STIM list.
 *
 * If at least one of the DTOs associated with this STIM list has not yet been received, or has been dropped entirely,
 * the function returns XCPEVENT_MISSING_DTO. In the latter case, all the data which \em has been received for this
 * raster of the STIM list was discarded. In neither case was any data written to the ECU's memory.
 * 
 * Otherwise, the function returns at least one of these values ORed together:
 *  - XCPEVENT_DAQSTIM_EXECUTED The STIM list was written to the ECU's memory.
 *  - XCPEVENT_DTO_OVERFILL     At least one DTO of the STIM list is configured to supply more data than it can hold.
 *                              Stimulation values which would fall partially or entirely outside the DTO were not written to
 *                              the ECU's memory.
 * Note that these two values are not mutually-exclusive.
 */
uint XCP_FN_TYPE Xcp_StimProcessor(
    const uint                 daqListId,
    const uint                 sessionId,
    Xcp_SessionConfig_t* const pSessionCfg
)
{
    Xcp_DaqConfig_t* const pDaqCfg          = pSessionCfg->pDaqConfigs + daqListId;
    Xcp_OdtEntryAddr_t*    pOdtEntryAddr    = pSessionCfg->pOdtEntryAddrs + pDaqCfg->idxDaqStart;
    Xcp_StatePtr8          pOdtEntryCfg     = pSessionCfg->pOdtEntryCfgs + pDaqCfg->idxDaqStart;
    Xcp_StatePtr8          pDtoPacket;
    Xcp_StatePtr8          pDtoPacketStart;
    uint                   numOdtEntries    = pDaqCfg->numOdtEntries;               /* We assume, at first, that this session does not use dynamic DAQs. */
    uint                   numOdt           = pDaqCfg->numOdt;                      /* We assume, at first, that this session does not use dynamic DAQs. */
    uint                   odtId;
    uint                   odtEntryId;
    uint                   peekIdx          = 0;
    const uint             isPidOff         = pSessionCfg->pDaqStates[daqListId].daqListMode & XCP_DAQLISTMODE_PIDOFF;
    const uint             isTimestamped    = ( pSessionCfg->numBytesTimestamp != 0 ) && ( pSessionCfg->pDaqStates[daqListId].daqListMode & (uint8)XCP_DAQLISTMODE_TIMESTAMP );
    uint                   retValue         = XCPEVENT_DAQSTIM_NOT_EXECUTED;

#ifdef XCP_ENABLE_DYNDAQ
    if( pSessionCfg->maxDynDaqLists > 0 )
    {
        /* This session uses dynamic DAQs. */
        numOdt = pSessionCfg->pDaqDynConfigs[ daqListId ].numOdt;
    }
    else
#endif /* XCP_ENABLE_DYNDAQ */

    /* If the first ODT entry of the first ODT of this DAQ list has a 0 length we can skip the
     * whole of the DAQ list (see XCP specification part 1 section 1.1.3.1). */
    if( 0 == *pOdtEntryCfg )
    {
        return XCPEVENT_DAQSTIM_NOT_EXECUTED;
    }

#ifdef XCP_ATOMIC_DATA_SAMPLING_PER_DAQ_LIST
    XCP_DISABLE_ALL_INTERRUPTS();
#endif

    /*
     * First we check that every ODT in the DAQ list has been received.
     *
     * While tracking missing STIM ODTs we assume that the XCP master will send STIM ODTs in ascending PID order.
     *
     * The XCP specification (part 1 section 1.1.3.1) states that the STIM processor can ignore an ODT which begins with an
     * ODT entry which is configured with a zero length. The XCP slave driver assumes that the master will not transmit a
     * STIM DTO which corresponds to such an ODT.
     *
     * If the DAQ list is in PID_OFF mode all we can do is check that the expected number of ODTs has been received.
     */

    /* Iterate over all ODTs in this DAQ list. Note there may be no ODTs in this DAQ list. */
    for( odtId = 0; odtId < numOdt; ++odtId )
    {
        /* If the first ODT entry in this ODT has a 0 length we can skip to the next ODT 
         * (see XCP specification part 1 section 1.1.3.1) */
        if( 0 == *pOdtEntryCfg )
        {
            pOdtEntryCfg += pDaqCfg->numOdtEntries;
            continue;
        }

        /* Peek at the nth-next RX buffer from our transport layer. */
        pDtoPacket = (pSessionCfg->pPeekRxBuf)( sessionId, daqListId + XCP_FIRST_DAQ_CHANNEL, peekIdx++ );
        if( !pDtoPacket )
        {
            /* We have peeked at all the DTOs which are available. */
            break;
        }

        /* Does the current STIM DTO packet not have the expected PID? (We assume the packets are received in order of ODT ID.) */
        if( pDtoPacket[0] != ( pDaqCfg->firstPid + odtId ) && !isPidOff )
        {
            break;
        }

        pOdtEntryCfg += pDaqCfg->numOdtEntries;
    }

    /* Reset the value of pOdtEntryCfg. */
    pOdtEntryCfg = pSessionCfg->pOdtEntryCfgs + pDaqCfg->idxDaqStart;

    /* Did we break out of the loop early? */
    if( odtId != numOdt )
    {
        /* We failed to receive at least one DTO in the STIM list. The missing STIM DTO has either been dropped entirely
         * or is just delayed. */

        if( pDtoPacket )
        {
            /* We broke out of the loop because the current STIM DTO does not have the expected PID. In other words, the
             * missing STIM DTO has been dropped entirely; it is not just delayed.
             *
             * We want to discard all DTOs in the current cycle of the STIM list. To do this, we discard STIM DTOs until
             * either we run out of STIM DTOs, or we find the STIM DTO at the start of the *next* cycle of the STIM list.
             *
             * (Note that the current STIM list cannot be operating in PID_OFF mode if we reach this point).
             * (Note also the ordering of the statements in the loop: we must not check the PID of the first STIM DTO,
             * because it will (almost always) equal firstPid). */

            do
            {
                /* Discard the current STIM DTO and move to the next one. */
    		    (pSessionCfg->pRxNext)( sessionId, daqListId + XCP_FIRST_DAQ_CHANNEL );
                /* Get the newly-current STIM DTO. */
                pDtoPacket = (pSessionCfg->pGetRxBuf)( sessionId, daqListId + XCP_FIRST_DAQ_CHANNEL );
            }
            while( pDtoPacket && pDtoPacket[0] != pDaqCfg->firstPid );
        }

#ifdef XCP_ATOMIC_DATA_SAMPLING_PER_DAQ_LIST
    XCP_ENABLE_ALL_INTERRUPTS();
#endif
        return XCPEVENT_MISSING_DTO;
    }

    /*
     * Now we read the DTOs and write the STIM data to memory.
     */

    /* Iterate over all ODTs in this DAQ list. Note there may be no ODTs in this DAQ list. */
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

        /* Get a RX buffer from our transport layer. */
        pDtoPacket = pDtoPacketStart = (pSessionCfg->pGetRxBuf)( sessionId, daqListId + XCP_FIRST_DAQ_CHANNEL );
        if( !pDtoPacket )
        {
            /* If we reach this point something has gone wrong, because we should only be processing DTOs which are
             * guaranteed to be present. */
            retValue |= XCPEVENT_MISSING_DTO;
            break;
        }

        /* Skip the PID of the DTO, if one is present. We have already checked that each DTO has the correct PID. */
        if( !isPidOff )
        {
            ++pDtoPacket;
        }

        /* If we are processing the first ODT of the DAQ list, and if a timestamp is configured for the DAQ list,
         * we skip the timestamp. */
        if( odtId == 0ul && isTimestamped )
        {
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

        /* Read data for each ODT entry until we reach one which has a zero address configured. */
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

                /* Would the current ODT entry need to extend beyond the end of the DTO packet? */
                if( pDtoPacket + 1 - pDtoPacketStart > pSessionCfg->maxDtoLen )
                {
                    retValue |= XCPEVENT_DTO_OVERFILL;
                    break;
                }

                /* According to the XCP specification the bit offset can be from 0 to 31. However, recall that our
                 * implementation of WRITE_DAQ adjusts the bit offset to be from 0 to 7. */
                if( *pDtoPacket )
                {
                    *XCP_UNPACK_ODTENTRY_BYTEADDR( *pOdtEntryAddr, *pOdtEntryCfg ) |= (uint8)( 1ul << XCP_UNPACK_ODTENTRY_BITOFFSET( *pOdtEntryAddr, *pOdtEntryCfg ) );
                }
                else
                {
                    *XCP_UNPACK_ODTENTRY_BYTEADDR( *pOdtEntryAddr, *pOdtEntryCfg ) &= (uint8)~( 1ul << XCP_UNPACK_ODTENTRY_BITOFFSET( *pOdtEntryAddr, *pOdtEntryCfg ) );
                }

                ++pDtoPacket;
            }
            else
            {
                /* Would the current ODT entry need to extend beyond the end of the DTO packet? */
                if( pDtoPacket + XCP_UNPACK_ODTENTRY_NUMBYTES( *pOdtEntryAddr, *pOdtEntryCfg ) - pDtoPacketStart >
                    pSessionCfg->maxDtoLen )
                {
                    retValue |= XCPEVENT_DTO_OVERFILL;
                    break;
                }

                /* The current ODT entry refers to a whole number of bytes. */
                Xcp_MemCopy( XCP_UNPACK_ODTENTRY_BYTEADDR( *pOdtEntryAddr, *pOdtEntryCfg ),
                             pDtoPacket,
                             XCP_UNPACK_ODTENTRY_NUMBYTES( *pOdtEntryAddr, *pOdtEntryCfg ) );

                pDtoPacket += XCP_UNPACK_ODTENTRY_NUMBYTES( *pOdtEntryAddr, *pOdtEntryCfg );
            }
            ++pOdtEntryAddr;
            ++pOdtEntryCfg;

            /* We have successfully applied at least one ODT entry to the ECU memory. */
            retValue |= XCPEVENT_DAQSTIM_EXECUTED;
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
        /* Mark the RX buffer as free */
		(pSessionCfg->pRxNext)( sessionId, daqListId + XCP_FIRST_DAQ_CHANNEL );
    }

#ifdef XCP_ATOMIC_DATA_SAMPLING_PER_DAQ_LIST
    XCP_ENABLE_ALL_INTERRUPTS();
#endif

    return retValue;
}

#endif /* XCP_ENABLE && XCP_ENABLE_STIM */ 
