/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  WdgIf.h
 *        \brief  WdgIf header file
 *
 *      \details  This is the header file of the module WdgIf
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Christian Leder               virchl        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  05.00.00  2015-11-25  virchl  FEAT-1411     First version of the migrated Watchdog Interface
 *  05.01.00  2016-05-20  virchl  ESCAN00090649 Updated version numbers due to generator update
 *  05.01.01  2016-10-21  virchl  ESCAN00092990 Patch-version-check removed between Implementation and Generator
 *  05.02.00  2017-01-11  virchl  ESCAN00093505 Automatic mode for calculating slave trigger pattern may expand time 
 *                                              duration for reaching safe state or omit reaching safe state at all
 *                                ESCAN00093580 Incorrect usage of Det
 *********************************************************************************************************************/

#if !defined (WDGIF_H)
# define WDGIF_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "WdgIf_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* ----- Vendor and module identification ----- */
# define WDGIF_VENDOR_ID                          (30u)
# define WDGIF_MODULE_ID                          (43u)

/* ----- AUTOSAR Software specification version information ----- */
# define WDGIF_AR_RELEASE_MAJOR_VERSION           (4u)
# define WDGIF_AR_RELEASE_MINOR_VERSION           (0u)
# define WDGIF_AR_RELEASE_REVISION_VERSION        (1u)

/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define WDGIF_SW_MAJOR_VERSION                   (5u)
# define WDGIF_SW_MINOR_VERSION                   (2u)
# define WDGIF_SW_PATCH_VERSION                   (0u)

# define WDGIF_INSTANCE_ID                        (0u)

/* ----- AUTOSAR Software specification version information (AUTOSAR 3 environment) ----- */
# define WDGIF_AR_MAJOR_VERSION      WDGIF_AR_RELEASE_MAJOR_VERSION
# define WDGIF_AR_MINOR_VERSION      WDGIF_AR_RELEASE_MINOR_VERSION
# define WDGIF_AR_PATCH_VERSION      WDGIF_AR_RELEASE_REVISION_VERSION

/* ----- WdgIf_Cfg.h version check ----- */
/* Protection against incorrect include file version (WdgIf_Cfg.h) */
#if ( (WDGIF_CFG_SW_MAJOR_VERSION != WDGIF_SW_MAJOR_VERSION) \
   || (WDGIF_CFG_SW_MINOR_VERSION != WDGIF_SW_MINOR_VERSION) \
   || (WDGIF_CFG_SW_PATCH_VERSION != WDGIF_SW_PATCH_VERSION) )
# error "Version mismatch! Incorrect version of WdgIf_Cfg.h"
#endif

/* ----- API service IDs ----- */

# define WDGIF_SID_SET_MODE                       (0x01u) /*!< Service ID: WdgIf_SetMode() */
# define WDGIF_SID_SET_TRIGGER_CONDITION          (0x02u) /*!< Service ID: WdgIf_SetTriggerCondition() */
# define WDGIF_SID_GET_VERSION_INFO               (0x03u) /*!< Service ID: WdgIf_GetVersionInfo() */
# define WDGIF_SID_SET_TRIGGER_WINDOW             (0x04u) /*!< Service ID: WdgIf_SetTriggerWindow() */

/* ----- Error codes ----- */
# define WDGIF_E_PARAM_DEVICE                     (0x01u) /*!< Error code: API service called with wrong device index
                                                           *               parameter
                                                           */
# define WDGIF_E_INV_POINTER                      (0x02u) /*!< Error code: API service called with NULL_PTR as
                                                           *               parameter
                                                           */

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
#  define WDGIF_START_SEC_CONST_UNSPECIFIED 
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*! Constant structure of type WdgIf_InterfaceType containing the configuration of the WdgIf */
extern CONST (WdgIf_InterfaceType, WDGIF_CONST) WdgIf_Interface;
#  define WDGIF_STOP_SEC_CONST_UNSPECIFIED 
#  include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define WDGIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  WdgIf_SetMode()
 *********************************************************************************************************************/
/*! \brief        Selects a Watchdog Mode
 *  \details      WdgIf_SetMode calls the platform specific implementation according to the parameter DeviceIndex. It 
 *                switches the watchdog unit in the desired mode.
 *                In case when State Combiner functionality is enabled, it can also address master or slave instance of
 *                the State Combiner module, with purpose to change the mode of the watchdog used by the State Combiner
 *  \param[in]    DeviceIndex   Index of the Watchdog device
 *  \param[in]    WdgMode       New mode to be set
 *  \return       E_OK          New mode selected successfully
 *  \return       E_NOT_OK      Error detected
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        SPEC-2247065
 */
FUNC(Std_ReturnType, WDGIF_CODE) WdgIf_SetMode(
  VAR(uint8, AUTOMATIC) DeviceIndex,
  VAR(WdgIf_ModeType, AUTOMATIC) WdgMode
  );


/**********************************************************************************************************************
 *  WdgIf_SetTriggerCondition()
 *********************************************************************************************************************/
/*! \brief        Triggers the Watchdog and sets a new timeout
 *  \details      WdgIf_SetTriggerCondition calls the platform specific implementation according to the parameter 
 *                DeviceIndex. It sets a new timeout for the watchdog unit and clears the window start.
 *                In case when State Combiner functionality is enabled, it can also address master or slave instance of
 *                the State Combiner module, with purpose to service watchdog used by the State Combiner if combined 
 *                status of all cores is correct.
 *  \param[in]    DeviceIndex   Index of the Watchdog device
 *  \param[in]    Timeout       New timeout to be set
 *  \return       E_OK          Trigger and timeout set was successfully
 *  \return       E_NOT_OK      Error detected
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        SPEC-2247065
 */
FUNC(Std_ReturnType, WDGIF_CODE) WdgIf_SetTriggerCondition(
  VAR(uint8, AUTOMATIC) DeviceIndex,
  VAR(uint16, AUTOMATIC) Timeout
  );


/**********************************************************************************************************************
 *  WdgIf_SetTriggerWindow()
 *********************************************************************************************************************/
/*! \brief        Triggers the Watchdog and sets a new window start and timeout
 *  \details      WdgIf_SetTriggerWindow calls the platform specific implementation according to the parameter 
 *                DeviceIndex. It sets a new timeout and new window start for the watchdog unit.
 *                In case when State Combiner functionality is enabled, it can also address master or slave instance of
 *                the State Combiner module, with purpose to service watchdog used by the State Combiner if combined
 *                status of all cores is correct.
 *  \param[in]    DeviceIndex   Index of the Watchdog device
 *  \param[in]    WindowStart   New window start time to be set
 *  \param[in]    Timeout       New timeout to be set
 *  \return       E_OK          Trigger, window start and timeout set was successful
 *  \return       E_NOT_OK      Error detected
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \trace        SPEC-2247065
 */
FUNC(Std_ReturnType, WDGIF_CODE) WdgIf_SetTriggerWindow(
  VAR (uint8, AUTOMATIC) DeviceIndex,
  VAR (uint16, AUTOMATIC) WindowStart,
  VAR (uint16, AUTOMATIC) Timeout
  );


# if (WDGIF_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  WdgIf_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief        Returns the version information of this module
 *  \details      WdgIf_GetVersionInfo returns information about the version of this module. This includes the module
 *                ID, the vendor ID, and the vendor-specific version number
 *  \param[in]    versioninfo       Pointer to where to store the version information of the WdgIf module
 *  \pre          -
 *  \context      TASK
 *  \reentrant    TRUE
 *  \synchronous  TRUE
 *  \config       WDGIF_VERSION_INFO_API is STD_ON
 *  \note         Module does not need to be initialized to use this service
 */
FUNC(void, WDGIF_CODE) WdgIf_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, WDGIF_APPL_DATA) versioninfo);
# endif /* WDGIF_VERSION_INFO_API == STD_ON */


# define WDGIF_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* WDGIF_H */

/**********************************************************************************************************************
 *  END OF FILE: WdgIf.h
 *********************************************************************************************************************/
