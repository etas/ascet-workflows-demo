/**
*
* \file
*
* \brief Implements functions associated with preparing for and executing RESUME mode.
*
* Copyright ETAS GmbH, Stuttgart.
*
* This file is covered by the licence and disclaimer document which is installed with
* the XCP ECU software package.
*
* \version $Id: xcpcan_resume.c 18358 2010-03-25 13:57:40Z olcritch $
*
******************************************************************************/

#include "xcp_common.h"
#include "xcp_auto_confdefs.h"
#include "xcp_priv.h"
#include "xcp_inf.h"

#if defined( XCP_ON_CAN ) && defined( XCP_ENABLE_RESUME )

#include "xcpcan_auto_confpriv.h"
#include "xcpcan_priv.h"

/**
 * This function prepares a DAQ list for RESUME by writing any required state into the non-volatile (NV) RAM region.
 *
 * \param [in] sessionId    The ID of the session.
 * \param [in] daqListId    The ID of the DAQ list which is to be prepared for RESUME.
 * \param [in] nvIdx        This function will store data into the NV RAM region beginning at this point.
 *
 * \return The number of bytes written into the NV RAM region.
 */
uint XCP_FN_TYPE XcpCan_PrepareResume(
    uint sessionId,
    uint daqListId,
    uint nvIdx
)
{
#ifdef XCP_ENABLE_DYNDAQ
    /* If the specified DAQ list is dynamic store its configured ID in non-volatile memory.
     * Note that we store the configured ID even if it equals XCPCAN_INVALID_MSGID, thereby indicating that the DAQ list's
     * ID has not been configured at runtime. */

    if( Xcp_SessionConfigs[ sessionId ].maxDynDaqLists > 0 )
    {
        XcpApp_NvMemWrite( nvIdx, (Xcp_StatePtr8)( XCPCAN_SESSIONCFG( sessionId )->pDynDaqMsgIds + daqListId ), sizeof( XcpCan_DynDaqMsgId_t ) );

        return sizeof( XcpCan_DynDaqMsgId_t );
    }

#endif /* XCP_ENABLE_DYNDAQ */

    return 0;
}

/**
 * This function RESUMEs a DAQ list by reading state which was previous written into the non-volatile (NV) RAM
 * region (by XcpCan_PrepareResume()).
 *
 * \param [in] sessionId    The ID of the session.
 * \param [in] daqListId    The ID of the DAQ list which is to be RESUMEd.
 * \param [in] nvIdx        This function will read data from the NV RAM region beginning at this point.
 *
 * \return The number of bytes read from the NV RAM region.
 */
uint XCP_FN_TYPE XcpCan_DoResume(
    uint sessionId,
    uint daqListId,
    uint nvIdx
)
{
#ifdef XCP_ENABLE_DYNDAQ
    /* If the specified DAQ list is dynamic read its configured ID from non-volatile memory.
     * Note that we read the configured ID even if it equals XCPCAN_INVALID_MSGID, thereby indicating that the DAQ list's
     * ID has not been configured at runtime. */

    if( Xcp_SessionConfigs[ sessionId ].maxDynDaqLists > 0 )
    {
        XcpApp_NvMemRead( nvIdx, (Xcp_StatePtr8)( XCPCAN_SESSIONCFG( sessionId )->pDynDaqMsgIds + daqListId ), sizeof( XcpCan_DynDaqMsgId_t ) );

        return sizeof( XcpCan_DynDaqMsgId_t );
    }

#endif /* XCP_ENABLE_DYNDAQ */

    return 0;
}

#endif /* XCP_ON_CAN && XCP_ENABLE_RESUME */
