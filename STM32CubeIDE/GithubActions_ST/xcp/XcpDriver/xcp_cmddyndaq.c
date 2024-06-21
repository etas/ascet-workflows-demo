/**
*
* \file
*
* \brief XCP dynamic DAQ commands.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcp_cmddyndaq.c 17051 2009-11-24 09:37:39Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_inf.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_auto_confpriv.h"

#if defined( XCP_ENABLE ) && defined( XCP_ENABLE_DYNDAQ )

/**
 * This function implements the XCP command FREE_DAQ as described in the XCP specification.
 *
 * The function stops all DAQ lists and resets their state before deleting them. This is done to prevent a
 * new dynamic DAQ list acquiring "left over" state from a previously-deleted DAQ list.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE Xcp_CmdFreeDaq(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    Xcp_SessionConfig_t* const pSessionCfg     = Xcp_SessionConfigs + sessionId;
    Xcp_StatePtr16 const       pNumDynDaqLists = &( Xcp_Sessions[ sessionId ].numDynDaqLists );
    uint                       i;

    /* Clear the state of all DAQ lists.
     * Note that it is important that the first action we take causes the DAQ lists to stop running. */
    for( i = 0; i < (uint)pSessionCfg->numStatDaqLists + (uint)*pNumDynDaqLists; ++i )
    {
        Xcp_ResetDaqList( sessionId, i );
    }

    /* Reset dynamic DAQ list state. */
    Xcp_MemZero( (Xcp_StatePtr8)( pSessionCfg->pDaqDynConfigs ), *pNumDynDaqLists * sizeof( Xcp_DaqDynConfig_t ) );

    /* Clear ODT entries. */
    Xcp_MemZero( (Xcp_StatePtr8)( pSessionCfg->pOdtEntryAddrs ), (uint)( pSessionCfg->totOdtEntries * sizeof( Xcp_OdtEntryAddr_t ) ) );
    Xcp_MemZero( (Xcp_StatePtr8)( pSessionCfg->pOdtEntryCfgs ) , (uint)( pSessionCfg->totOdtEntries * sizeof( uint8 ) ) );

    *pNumDynDaqLists = 0;

    /* Send positive response. */
    pTxPacket->pid = XCP_PID_RESPONSE;
    *pTxPacketSize = 1;

    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command ALLOC_DAQ as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE Xcp_CmdAllocDaq(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  reserved;
        uint16 numDaq;
    } ) CmdPacket_t;

    const CmdPacket_t* const   pCmdPacket      = (CmdPacket_t*)pRxPacket;
    Xcp_SessionConfig_t* const pSessionCfg     = Xcp_SessionConfigs + sessionId;
    Xcp_StatePtr16 const       pNumDynDaqLists = &( Xcp_Sessions[ sessionId ].numDynDaqLists );
    const Xcp_DaqDynConfig_t*  pDaqDynCfg      = pSessionCfg->pDaqDynConfigs;
    uint                       i;

    /* Assume this method will fail. */
    pTxPacket->pid = XCP_PID_ERROR;
    *pTxPacketSize = 2;

    /* Check whether ALLOC_ODT has already been called for any dynamic DAQ list. */
    for( i = 0; i < (uint)*pNumDynDaqLists; ++i )
    {
        if( 0 != pDaqDynCfg->numOdt )
        {
            /* ALLOC_ODT has already been called for at least one dynamic DAQ list. This is an error. */
            pTxPacket->data[0]  = XCP_ERR_SEQUENCE;
            return( XCP_RX_READY | XCP_TX_READY );
        }

        ++pDaqDynCfg;
    }

    if( pCmdPacket->numDaq > pSessionCfg->maxDynDaqLists )
    {
        /* We cannot allocate the requested number of dynamic DAQ lists; send a negative response with XCP_ERR_MEMORY_OVERFLOW */
        pTxPacket->data[0] = XCP_ERR_MEMORY_OVERFLOW;
    }
    else
    {
        *pNumDynDaqLists = pCmdPacket->numDaq;
        pTxPacket->pid   = XCP_PID_RESPONSE;
        *pTxPacketSize   = 1;
    }

    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command ALLOC_ODT as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE Xcp_CmdAllocOdt(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  reserved;
        uint16 daqListId;
        uint8  numOdt;
    } ) CmdPacket_t;

    const CmdPacket_t* const   pCmdPacket      = (CmdPacket_t*)pRxPacket;
    Xcp_SessionConfig_t* const pSessionCfg     = Xcp_SessionConfigs + sessionId;
    const uint                 numDynDaqLists  = Xcp_Sessions[ sessionId ].numDynDaqLists;
    Xcp_DaqDynConfig_t*        pDaqDynCfg      = pSessionCfg->pDaqDynConfigs;
    uint                       odtId;
    uint                       daqListId;

    /* Assume this method will fail. */
    pTxPacket->pid = XCP_PID_ERROR;
    *pTxPacketSize = 2;

    if( 0 == numDynDaqLists )
    {
        /* ALLOC_DAQ has not yet been called. This is an error. */
        pTxPacket->data[0] = XCP_ERR_SEQUENCE;
        return( XCP_RX_READY | XCP_TX_READY );
    }

    /* Check whether ALLOC_ODT_ENTRY has already been called for any dynamic DAQ list. */
    for( daqListId = 0; daqListId < numDynDaqLists; ++daqListId )
    {
        for( odtId = 0; odtId < pDaqDynCfg->numOdt; ++odtId )
        {
            if( 0 != pDaqDynCfg->odtEntryNums[ odtId ] )
            {
                /* ALLOC_ODT_ENTRY has already been called for at least one dynamic DAQ list. This is an error. */
                pTxPacket->data[0]  = XCP_ERR_SEQUENCE;
                return( XCP_RX_READY | XCP_TX_READY );
            }
        }

        ++pDaqDynCfg;
    }

    pDaqDynCfg = pSessionCfg->pDaqDynConfigs + pCmdPacket->daqListId;

    if( pCmdPacket->daqListId >= numDynDaqLists )
    {
        /* The given DAQ list ID does not refer to a valid dynamic DAQ list. */
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        return( XCP_RX_READY | XCP_TX_READY );
    }

    if( pCmdPacket->numOdt > pSessionCfg->pDaqConfigs[ pCmdPacket->daqListId ].numOdt )
    {
        /* We cannot allocate the requested number of dynamic ODTs; send a negative response with XCP_ERR_MEMORY_OVERFLOW */
        pTxPacket->data[0] = XCP_ERR_MEMORY_OVERFLOW;
    }
    else
    {
        pDaqDynCfg->numOdt = pCmdPacket->numOdt;

        pTxPacket->pid = XCP_PID_RESPONSE;
        *pTxPacketSize = 1;
    }

    return( XCP_RX_READY | XCP_TX_READY );
}

/**
 * This function implements the XCP command ALLOC_ODT_ENTRY as described in the XCP specification.
 *
 * \param [in] sessionId        The index of the session which received this command.
 * \param [in] pRxPacket        The command packet.
 * \param [out] pTxPacket       The response packet.
 * \param [in] prevCmd          The ID of the previous command, or XCP_CMD_CURR_CMD if this command is being re-processed.
 * \param [out] pTxPacketSize   The number of bytes present at pTxPacket.
 *
 * \return
 *  - XCP_RX_READY | XCP_TX_READY   This command was processed successfully.
 */
uint XCP_FN_TYPE Xcp_CmdAllocOdtEntry(
    uint            sessionId,
    Xcp_Packet_t*   pRxPacket,
    Xcp_Packet_t*   pTxPacket,
    uint            prevCmd,
    uint*           pTxPacketSize
)
{
    typedef XCP_PACK( struct
    {
        uint8  pid;
        uint8  reserved;
        uint16 daqListId;
        uint8  odtId;
        uint8  numOdtEntries;
    } ) CmdPacket_t;

    const CmdPacket_t* const   pCmdPacket      = (CmdPacket_t*)pRxPacket;
    Xcp_SessionConfig_t* const pSessionCfg     = Xcp_SessionConfigs + sessionId;
    const uint                 numDynDaqLists  = Xcp_Sessions[ sessionId ].numDynDaqLists;
    Xcp_DaqDynConfig_t* const  pDaqDynCfg      = pSessionCfg->pDaqDynConfigs + pCmdPacket->daqListId;

    /* Assume this method will fail. */
    pTxPacket->pid = XCP_PID_ERROR;
    *pTxPacketSize = 2;

    /* First we must check the validity of the given DAQ list ID. */

    if( 0 == numDynDaqLists )
    {
        /* ALLOC_DAQ has not yet been called. */
        pTxPacket->data[0] = XCP_ERR_SEQUENCE;
        return( XCP_RX_READY | XCP_TX_READY );
    }

    if( pCmdPacket->daqListId >= numDynDaqLists )
    {
        /* The given DAQ list ID does not refer to a valid dynamic DAQ list. */
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        return( XCP_RX_READY | XCP_TX_READY );
    }

    /* Now that the given DAQ list ID is valid we can make use of it to perform ODT checks. */

    if( 0 == pDaqDynCfg->numOdt )
    {
        /* ALLOC_ODT has not yet been called for the given dynamic DAQ. This is an error. */
        pTxPacket->data[0] = XCP_ERR_SEQUENCE;
        return( XCP_RX_READY | XCP_TX_READY );
    }

    if( pCmdPacket->odtId >= pDaqDynCfg->numOdt )
    {
        /* The given ODT ID does not refer to a valid dynamic ODT. */
        pTxPacket->data[0] = XCP_ERR_OUT_OF_RANGE;
        return( XCP_RX_READY | XCP_TX_READY );
    }

    if( pCmdPacket->numOdtEntries > pSessionCfg->pDaqConfigs[ pCmdPacket->daqListId ].numOdtEntries )
    {
        /* We cannot allocate the requested number of dynamic ODT entries; send a negative response with XCP_ERR_MEMORY_OVERFLOW */
        pTxPacket->data[0] = XCP_ERR_MEMORY_OVERFLOW;
    }
    else
    {
        pDaqDynCfg->odtEntryNums[ pCmdPacket->odtId ] = pCmdPacket->numOdtEntries;

        pTxPacket->pid = XCP_PID_RESPONSE;
        *pTxPacketSize = 1;
    }

    return( XCP_RX_READY | XCP_TX_READY );
}

#endif /* XCP_ENABLE && XCP_ENABLE_DYNDAQ */
