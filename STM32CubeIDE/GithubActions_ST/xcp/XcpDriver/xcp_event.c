/**
*
* \file
*
* \brief Definition of Xcp_Event().
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_event.c 22409 2011-04-22 10:40:28Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"

#ifdef XCP_ENABLE

/**
 * This function should be called by the user application to notify the XCP slave driver of the occurrence of
 * DAQ events.
 *
 * Depending on doStim, the function will process either STIM or DAQ lists which are associated with the specified event.
 * If an error is encountered while processing one STIM or DAQ list, processing will continue with the next list.
 *
 * \param [in] eventId      The ID of the event which has occurred.
 * \param [in] doStim       A boolean indicating whether to do the STIM or DAQ actions associated with this event.
 *
 * \return
 *  - XCPEVENT_DAQSTIM_NOT_EXECUTED  There is no running DAQ/STIM list which matches the function's arguments. No data
 *                                   was transferred.
 *  Otherwise delegated to either Xcp_DaqProcessor() or Xcp_StimProcessor().
 */
uint XCP_FN_TYPE Xcp_Event(
    uint eventId,
    uint doStim
)
{
    uint                 daqListId;
    uint                 sessionId;
    Xcp_SessionConfig_t* pSessionCfg = Xcp_SessionConfigs;
    uint                 retValue    = XCPEVENT_DAQSTIM_NOT_EXECUTED;

    for( sessionId = 0; sessionId < XCP_NUM_SESSIONS; ++sessionId )
    {
        const uint numdaqLists = (uint)pSessionCfg->numStatDaqLists + (uint)Xcp_Sessions[ sessionId ].numDynDaqLists;
        Xcp_Daq_t* pDaqState   = pSessionCfg->pDaqStates;

        for( daqListId = 0; daqListId < numdaqLists; ++daqListId )
        {
            /* Is the current DAQ list running, and is it associated with the specified event? */
            if( ( pDaqState->daqListMode & XCP_DAQLISTMODE_RUNNING ) &&
                (uint)pDaqState->daqEvent == eventId )
            {
#ifdef XCP_ENABLE_STIM
                if( doStim && ( pDaqState->daqListMode & XCP_DAQLISTMODE_DIRECTION ) )
                {
                    /* The current DAQ list is running in STIM mode. */
                    retValue |= Xcp_StimProcessor( daqListId, sessionId, pSessionCfg );
                }
                else
#endif /* XCP_ENABLE_STIM */
                if( !doStim && !( pDaqState->daqListMode & XCP_DAQLISTMODE_DIRECTION ) )
                {
                    /* The current DAQ list is running in DAQ mode. */
                    retValue |= Xcp_DaqProcessor( daqListId, sessionId, pSessionCfg );
                }
            }
            ++pDaqState;
        }

        ++pSessionCfg;
    }

    return retValue;
}

#endif /* XCP_ENABLE */
