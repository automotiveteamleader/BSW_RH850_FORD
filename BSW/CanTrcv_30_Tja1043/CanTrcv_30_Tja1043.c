/* Kernbauer Version: 1.16 Konfiguration: DrvTransCan Erzeugungsgangnummer: 18 */

/**********************************************************************************************************************
 |               C O P Y R I G H T
 |-----------------------------------------------------------------------
 |------  Copyright (c) 2000-2016 by Vector Informatik GmbH, all rights 
 |reserved
 |
 | Please note, that this file contains an implementation example for 
 | CanTrcv. This code may influence the behaviour of the CanTrcv
 | in principle. Therefore, great care must be taken to verify
 | the correctness of the implementation.
 |
 | The contents of the originally delivered files are only examples resp. 
 | implementation proposals. With regard to the fact that these functions 
 | are meant for demonstration purposes only, Vector Informatik's 
 | liability shall be expressly excluded in cases of ordinary negligence, 
 | to the extent admissible by law or statute.
 |  -------------------------------------------------------------------------------------------------------------------
 |  FILE DESCRIPTION
 |  -------------------------------------------------------------------------------------------------------------------
 |         File:  CanTrcv_30_Tja1043.c
 |      Project:  MICROSAR
 |       Module:  CAN Transceiver driver
 |    Generator:  DaVinci Configurator 5
 |  Description:  Implementation of the MICROSAR CAN Transceiver Driver.
 **********************************************************************************************************************/

 /**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Senol Cendere                 Ces           Vector Informatik GmbH
 *  Matthias Fleischmann          Fn            Vector Informatik GmbH
 *  Mihai Olariu                  Ou            Vector Informatik GmbH
 *  Timo Vanoni                   Tvi           Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  Andreas Weinrauch             Was           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  1.00.00   2010-05-07  Tvi     -             First Implementation
 *  1.01.00   2011-01-10  Tvi     -             (No changes here. Just merge with new HL)
 *  1.02.00   2011-02-14  Tvi     -             (update to new template in order to merge with new HL)
 *  2.00.00   2011-07-29  Seu     -             (update to new template in order to merge with new HL)
 *  2.01.00   2012-01-23  Seu     -             (update to new template in order to merge with new HL)
 *  2.01.01   2012-08-16  Tvi     -             (update to new template in order to merge with new HL)
 *  3.00.00   2013-02-01  Seu     ESCAN00064742 Add support for ASR4.0.3
 *            2013-02-01  Seu     ESCAN00064743 AR3-2406: Asynchronous transceiver handling according to AUTOASR 3.2.2
 *  3.01.00   2013-05-24  Seu     -             (no changes here, just updated HL code)
 *  4.00.00   2014-10-27  Seu     ESCAN00079165 AR4-698: Post-Build Selectable (Identity Manager)
 *  4.00.01   2015-30-07  Seu     -             (no changes here, just updated HL code)
 *  4.01.00   2015-12-10  Seu     -             (no changes here, just updated HL code)
 *  4.02.00   2016-11-14  Was     ESCAN00068402 Compiler warning: conditional expression or part of it is always true/false
 *********************************************************************************************************************/

/* ********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Matthias Fleischmann          Fn            Vector Informatik GmbH
 *  Mihai Olariu                  Ou            Vector Informatik GmbH
 *  Timo Vanoni                   Tvi           Vector Informatik GmbH
 *  Eugen Stripling               Seu           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2008-02-25  Fn      -             Intitial revision of the core implementation
 *  01.00.01  2008-04-17  Fn      -             Update of the include file names
 *  01.01.00  2008-06-26  Ou      ESCAN00027616 Various compile errors, problems with Organi
 *  01.02.00  2008-09-12  Ou      ESCAN00029980 Compiler failure due to wrong definition of SW version
 *  01.03.00  2008-10-07  Ou      ESCAN00028298 Several warnings due to unreferenced local variables
 *                        Ou      ESCAN00029572 DrvTrans__coreCanxAsr raise DET error if CanTrcv_SetOpMode is called with invalid TrcvWakeupMode
 *                        Ou      ESCAN00030536 Compile error at extended version check
 *  01.04.00  2008-12-11  Ou      ESCAN00031771 Adjust wakeup by bus handling for platforms which cannot be woken up with a CAN frame
 *  01.05.00  2009-02-19  Tvi     ESCAN00033258 GetBusWuReason may return an invalid value
 *  01.06.00  2009-02-26  Tvi     ESCAN00033383 Don't throw DET error in case the same mode is requested again
 *                        Tvi     ESCAN00033398 Compiler warnings when using different transceiver types within the same stack
 *                        Tvi     ESCAN00033413 Possible out of bounds access in SetOpMode if DET is enabled
 *  02.00.00  2009-06-29  Fn      ESCAN00035913 CAN Transceiver channel does not wake up
 *  02.00.01  2009-10-15  Tvi     ESCAN00038495 Compile error: unknown type definitions in dio.h
 *  02.01.00  2009-11-04  Tvi     ESCAN00036841 OP_MODE_SLEEP should be independent of GENERAL_WAKE_UP_SUPPORT
 *                        Tvi     ESCAN00038945 Use different DioPins tokens for GetOpMode and CHECK_WA
 *                        Tvi     ESCAN00038946 Rename filenames to match BSW00347
 *                        Tvi     ESCAN00038947 CanTrcv087 has to be implemented the correct way
 *                        Tvi     ESCAN00039039 Add support for timers
 *                        Tvi     ESCAN00039041 Allow transition to OP_MODE_NORMAL even if it is the current OpMode
 *                        Tvi     ESCAN00039043 Implement an initialization via OP_MODE_NORMAL
 *                        Tvi     ESCAN00039194 Disable IcuNotification when entering Normal mode in Init and SetOpMode
 *  02.02.00  2010-05-04  Tvi     ESCAN00040088 Compiler Warning: unused parameter 'TrcvWakeupMode'
 *  02.20.00  2010-07-01  Tvi     ESCAN00046512 Add support for partial network transceivers
 *            2010-11-29  Tvi     ESCAN00046781 Support Multiple Identity Configuration
 *                                ESCAN00045601 "Channel Used" parameter not well implemented
 *                                ESCAN00046813 Adapt AUTOSAR version check
 *                                ESCAN00047668 Critical areas should be Trcv specific
 *  02.20.01  2011-02-08  Tvi     ESCAN00048498 Wrong DEM Events used
 *  02.20.02  2011-03-11  Tvi     ESCAN00049830 Remove ASR Version check for SPI / DIO
 *                                ESCAN00049831 [PN only] Store wakeup event and report them if Trcv is in Standby mode
 *  03.00.00  2011-05-05  Tvi     ESCAN00051930 Add support for ASR3.2.1
 *                                ESCAN00051564 Remove the AUTOSAR Release Version Check
 *  03.01.00  2011-11-22  Tvi     ESCAN00054349 AR3-1738: Add support for asynchronous transceiver driver
 *                                ESCAN00053272 AR3-1698: Add MISRA justifications in source code for automatic generation of MISRA reports
 *                                ESCAN00053265 AR3-2069: Remove non-SchM code for critical section handling
 *  03.01.01  2012-02-12  Tvi     ESCAN00057892 [PN only] CanTrcv does not wakeup when Synchronous SPI is being used
 *                        Tvi     ESCAN00056788 Compiler error/warning: DRVTRANS__CORECANXASR_RELEASE_VERSION' redefined
 *  04.00.00  2012-05-21  Tvi     ESCAN00058641 AR4-95: Provide CanTrcv according ASR 4, Asynchronous Transceiver Mode Changes
 *                                ESCAN00059656 Add support for SetPNActivationState according to ASR4
 *                                ESCAN00060455 AR3-2406: Asynchronous transceiver handling according to AUTOASR 3.2.2
 *  04.00.01  2012-09-27  Tvi     ESCAN00061779 [CFG5/ASR4 only]: Compiler error about unkown struct member instanceID
 *  04.01.00  2012-10-08  Tvi     ESCAN00062121 Report DEM if PN is not available
 *                        Tvi     ESCAN00066283 AR4-352: Support partial networking
 *  04.02.00  2013-11-20  Tvi     ESCAN00071370 AR4-569: [CanTrcv]  Incompatible  argument  in call to EcuM_SetWakeupEvent()
 *  04.03.00  2014-01-10  Tvi     ESCAN00073861 AR4-345: Implement PF4_PostBuildSelectable
 *  05.00.00  2014-09-24  Seu     ESCAN00076622 AR4-698: Post-Build Selectable (Identity Manager)
 *  05.00.01  2014-11-13  Seu     -             MISRA deviation comment for rule 6080 added (APIs: *_ClearTrcvWufFlag() and *_CheckWakeFlag())
 *  05.01.00  2015-05-04  Seu     ESCAN00077814 Support for CAN Transceiver on System-Basis Chips (SBCs)
 *            2015-07-23  Seu     ESCAN00084154 Only since R13: Compiler error: C2059: syntax error : '{'
 *            2015-07-23  Seu     ESCAN00083583 Adapt in order to fix ESCAN00083361 / ESCAN00083362
 *            2015-07-23  Seu     ESCAN00083395 Compiler warning: parameter is never used
 *  05.01.01  2015-09-24  Seu     ESCAN00085451 Support usage of Partial Networking for SBCs.
 *  05.01.02  2015-10-06  Seu     ESCAN00085678 Initialize requestState in case of INTERFACE_SBC and PN is used
 *  05.02.00  2015-02-04  Seu     ESCAN00080310 FEAT-427: SafeBSW Step I
 *            2015-10-05  Seu     ESCAN00081795 FEAT-1275: SafeBSW Step 2
 *            2015-10-05  Seu     ESCAN00085154 FEAT-1527: SafeBSW Step 3
 *  05.03.00  2016-01-16  Seu     ESCAN00087580 SafeBSW - Silent Analysis
 *            2016-03-09  Seu     ESCAN00088810 Add Postbuild Loadable Support for CanTrcvDrv
 *  05.04.00  2016-04-05  Seu     ESCAN00087813 FEAT-1688: SafeBSW Step 4
 *            2016-05-19  Seu     ESCAN00090097 Compiler error: Syntax Error caused by undefined compiler class
 *  05.04.01  2016-08-02  Seu     ESCAN00091270 MISRA deviation: MISRA-C:2004 Rule 8.8
 *            2016-08-17  Seu     ESCAN00091505 Improve code coverage and doxygen comments
 *            2016-10-17  Seu     ESCAN00091616 Compiler error: identifier index not declared
 * *******************************************************************************************************************/

/* PRQA S 0715 EOF */ /* MD_CanTrcv_30_Tja1043_0715 */
/* PRQA S 0850 EOF */ /* MD_MSR_19.8 */
/* PRQA S 0777 EOF */ /* MD_CanTrcv_30_Tja1043_0777 */
/* PRQA S 3453 EOF */ /* MD_MSR_19.7 */
/* PRQA S 0779 EOF */ /* MD_CanTrcv_30_Tja1043_0779 */

/* ********************************************************************************************************************
 *  INCLUDES
 * *******************************************************************************************************************/
#define CANTRCV_30_TJA1043_INCLUDE_INTERNAL
#define V_CANTRCV_30_TJA1043_SOURCE

/* \trace SPEC-19973, SPEC-20008, SPEC-19954, SPEC-19965 */
/* \trace SPEC-14977, SPEC-15093, SPEC-15086, SPEC-14969 */
#include "CanTrcv_30_Tja1043.h"

# include "Dio.h"

#include "CanIf.h"

#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif

#include "EcuM.h"

/* *********************************************************************************************************************
 *  VERSION CHECK
 * ********************************************************************************************************************/

#if (DRVTRANS__CORECANXASR_VERSION                             != 0x0504u)
# error "Module CanTrcv_30_Tja1043: Source and Header files are inconsistent!"
#endif
#if (DRVTRANS__CORECANXASR_RELEASE_VERSION                     != 0x01u)
# error "Module CanTrcv_30_Tja1043: Source and Header files are inconsistent!"
#endif

/* ** Version Check: CFG5 - Base part ** */
#define CANTRCV_30_TJA1043_BASE_GENDATA_COMP_VERSION     0x0104u

#if (CANTRCV_30_TJA1043_GENTOOL_CFG5_BASE_COMP_VERSION != CANTRCV_30_TJA1043_BASE_GENDATA_COMP_VERSION)
# error "Module CanTrcv_30_Tja1043: Source and Generated Header files are inconsistent! [BASE]"
#endif

# if (DRVTRANS_TJA1043CANDIOASR_VERSION                    != 0x0402u)
#  error "Module CanTrcv_30_Tja1043: Source and Header files are inconsistent!"
# endif
# if (DRVTRANS_TJA1043CANDIOASR_RELEASE_VERSION            != 0x00u)
#  error "Module CanTrcv_30_Tja1043: Source and Header files are inconsistent!"
# endif

/* ** Version Check: CFG5 - HW specific part ** */
#if (CANTRCV_30_TJA1043_GENTOOL_CFG5_HW_COMP_VERSION != 0x0103u)
# error "Module CanTrcv_30_Tja1043: Source and Generated Header files are inconsistent!"
#endif

/* ********************************************************************************************************************
 *  LOCAL DEFINES
 * ********************************************************************************************************************/

#if !defined (CANTRCV_30_TJA1043_LOCAL)
# define CANTRCV_30_TJA1043_LOCAL             static
#endif

#if !defined (CANTRCV_30_TJA1043_LOCAL_INLINE)
# define CANTRCV_30_TJA1043_LOCAL_INLINE      LOCAL_INLINE
#endif

#define CanTrcvCfg_IsChannelUsed(ch)                   CanTrcv_30_Tja1043_IsChannelUsed(ch)
#define CanTrcvCfg_IsWakeupByBusUsed(ch)               CanTrcv_30_Tja1043_IsWakeupByBusUsed(ch)
#define CanTrcvCfg_GetWakeupSource(ch)                 CanTrcv_30_Tja1043_GetWakeupSource(ch)
#define CanTrcvCfg_GetWakeupSourceSyserr(ch)           CanTrcv_30_Tja1043_GetWuSrcSyserr(ch)
#define CanTrcvCfg_GetWakeupSourcePor(ch)              CanTrcv_30_Tja1043_GetWuSrcPor(ch)
#define CanTrcvCfg_IsIcuChannelSet(ch)                 CanTrcv_30_Tja1043_IsIcuChannelSetOfChannel(ch)
#define CanTrcvCfg_GetIcuChannel(ch)                   CanTrcv_30_Tja1043_GetIcuChannelOfChannel(ch)
#define CanTrcvCfg_GetMagicNumber()                    CanTrcv_30_Tja1043_GetFinalMagicNumber()
#define CanTrcvCfg_GetGeneratorCompatibilityVersion()  CanTrcv_30_Tja1043_GetGeneratorCompatibilityVersion()

/* ********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 * ********************************************************************************************************************/
#define CANTRCV_30_TJA1043_IS_INIT                         1
#define CANTRCV_30_TJA1043_IS_NOT_INIT                     0

/* ********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 * ********************************************************************************************************************/
#define CanTrcv_EnterCritical() SchM_Enter_CanTrcv_30_Tja1043_CANTRCV_30_TJA1043_EXCLUSIVE_AREA_0()
#define CanTrcv_LeaveCritical() SchM_Exit_CanTrcv_30_Tja1043_CANTRCV_30_TJA1043_EXCLUSIVE_AREA_0()

#if (CANTRCV_30_TJA1043_DEV_ERROR_REPORT == STD_ON)
# define CanTrcv_DetReportError(apiId, errorId)  ((void)Det_ReportError((CANTRCV_30_TJA1043_MODULE_ID), (CANTRCV_30_TJA1043_INSTANCE_ID), (apiId), (errorId)))
#else
# define CanTrcv_DetReportError(apiId, errorId)
#endif

#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
#  define CanTrcv_ReportErrorNoTrcvControl(apiId) CanTrcv_DetReportError( (apiId), CANTRCV_30_TJA1043_E_NO_TRCV_CONTROL)
#endif

/* If no errors should be reported */
#if defined(CanTrcv_ReportErrorNoTrcvControl)
#else
# define CanTrcv_ReportErrorNoTrcvControl(apiId)
#endif

# if (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON)
#  define CANTRCV_30_TJA1043_CHECK_WA(index) ((CanTrcvSTB == STD_LOW) && (CanTrcvERR == STD_LOW))
# endif

/* The macro CANTRCV_30_TJA1043_IS_EXTERNAL_WU_REASON returns true if the
   given wakeup reason indicates an external wakeup event */
# if !defined(CANTRCV_30_TJA1043_IS_EXTERNAL_WU_REASON)
#   define CANTRCV_30_TJA1043_IS_EXTERNAL_WU_REASON(wuReason)               \
                        ((wuReason) == CANTRCV_30_TJA1043_WU_BY_BUS)
# endif /* !defined(CANTRCV_30_TJA1043_IS_EXTERNAL_WU_REASON) */

#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
# define CANTRCV_30_TJA1043_IS_INITIALIZED(channel) \
                  ( (CanTrcv_30_Tja1043_IsInitialized == CANTRCV_30_TJA1043_IS_INIT) \
                  )
#endif

/*!
 * Internal comment removed. *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * 
 */ 

/* ********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 * ********************************************************************************************************************/

/* The following type includes CAN transceiver channel specific settings. */
typedef struct
{
  /* ---- Common attributes ---- */

  /* Last detected wakeup reason */
  CanTrcv_30_Tja1043_TrcvWakeupReasonType wakeUpReason;

  /* Specifies whether or not to report wakeups */
  CanTrcv_30_Tja1043_TrcvWakeupModeType wakeUpReport;

  /* HW specific attributes */

} CanTrcv_30_Tja1043_Prob_Type; /* PRQA S 3448 */ /* MD_CanTrcv_30_Tja1043_3448 */

/* ********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 * ********************************************************************************************************************/

#define CANTRCV_30_TJA1043_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
 /*
 * Specifies whether the CanTrcv module is initialized.
 */
# if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
CANTRCV_30_TJA1043_LOCAL VAR(uint8, CANTRCV_30_TJA1043_VAR_INIT) CanTrcv_30_Tja1043_IsInitialized = CANTRCV_30_TJA1043_IS_NOT_INIT;
# endif

#define CANTRCV_30_TJA1043_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CANTRCV_30_TJA1043_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*
 * In following variable CAN transceiver channel specific settings are stored e.g. the wake-up reason or the current operating mode. 
 * For more information see the description of type: CanTrcv_30_Tja1043_Prob_Type.
 */
VAR(CanTrcv_30_Tja1043_Prob_Type, CANTRCV_30_TJA1043_VAR_NOINIT) CanTrcv_30_Tja1043_Prob[CANTRCV_30_TJA1043_MAX_CHANNEL]; /* PRQA S 3408 */ /* MD_CanTrcv_30_Tja1043_3408 */

#if (CANTRCV_30_TJA1043_USE_INIT_POINTER == STD_ON)
/* In following variable the configuration is stored during the initialization of the CAN transceiver driver in case of a Post-build loadable / selectable configuration. */
/* PRQA S 3218 1 */ /* MD_CanTrcv_30_Tja1043_8.7 */
CANTRCV_30_TJA1043_LOCAL P2CONST(CanTrcv_30_Tja1043_ConfigType, CANTRCV_30_TJA1043_VAR_NOINIT, CANTRCV_30_TJA1043_INIT_DATA) CanTrcv_30_Tja1043_ConfigDataPtr;
#endif

#define CANTRCV_30_TJA1043_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CANTRCV_30_TJA1043_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
/* ********************************************************************************************************************
 *  LOCAL FUNCTIONS
 * ********************************************************************************************************************/
/* Local function declarations */

#if (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON) 
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_ReportWakeup
 **********************************************************************************************************************/
/*! \brief       Report the wake-up reason to the upper layer.
 *  \details     This function has no service id. Called by transceiver driver within: LL-specific.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         The LL must ensure that this API is called with valid <CanTrcvIndex>. 
 *               The value of <CanTrcvIndex> is valid if < CANTRCV_30_TJA1043_MAX_CHANNEL.
 *  \context     ANY
 *  \reentrant   TRUE only for different transceiver channels (CanTrcvIndex)
 *  \synchronous TRUE
 *  \config      CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON
 **********************************************************************************************************************/
CANTRCV_30_TJA1043_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_ReportWakeup(uint8 CanTrcvIndex);
#endif

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_LL_InitMemoryChannelBegin
 **********************************************************************************************************************/
/*! \brief       LL: LL-specific channel initialization.
 *  \details     This function is called for ALL channels and has no service id.
 *               The callee (HL) ensures the validity of <CanTrcvIndex>. 
 *               Called by transceiver driver within: CanTrcv_30_Tja1043_Init().
 *               This is ensured if <CanTrcvIndex> < CANTRCV_30_TJA1043_MAX_CHANNEL.
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE only for different transceiver channels (index)
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1043_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_LL_InitMemoryChannelBegin(uint8 CanTrcvIndex);

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_LL_InitChannel
 **********************************************************************************************************************/
/*! \brief       LL: LL-specific channel initialization.
 *  \details     This function is called only for "used" (== activated) channels and has no service id.
 *               The callee (HL) ensures the validity of <CanTrcvIndex>. 
 *               This is ensured if <CanTrcvIndex> < CANTRCV_30_TJA1043_MAX_CHANNEL.
 *               Called by transceiver driver within: CanTrcv_30_Tja1043_Init().
 *  \param[in]   CanTrcvIndex: Index of the selected transceiver channel to which API call has to be applied.
 *  \pre         -
 *  \context     TASK
 *  \reentrant   TRUE only for different transceiver channels (index)
 *  \synchronous TRUE
 *  \config      -
 **********************************************************************************************************************/
CANTRCV_30_TJA1043_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_LL_InitChannel(uint8 CanTrcvIndex);

/* ********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 * ********************************************************************************************************************/

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_InitMemory
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_InitMemory(void)
{
#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
  /* #100 Mark driver as uninitialized. */
  CanTrcv_30_Tja1043_IsInitialized = CANTRCV_30_TJA1043_IS_NOT_INIT;
#endif
}

/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_LL_InitMemoryChannelBegin
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1043_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_LL_InitMemoryChannelBegin(uint8 CanTrcvIndex)
{
  /* #100 Initialize the CAN transceiver channel-specific settings (independent active or inactive one) (LL-specific). */
  /* This API is NOT required for Tja1043. */
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(CanTrcvIndex);
}

/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_LL_InitChannel
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1043_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_LL_InitChannel(uint8 CanTrcvIndex)
{

  /* #100 Initialize the CAN transceiver channel-specific settings (only active one) (LL-specific). */
  /* This API is NOT required for Tja1043. */
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(CanTrcvIndex);
}

/**********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_Init
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_Init( P2CONST(CanTrcv_30_Tja1043_ConfigType, AUTOMATIC, CANTRCV_30_TJA1043_INIT_DATA) ConfigPtr )
{
  /* \trace SPEC-14971 */

  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANTRCV_30_TJA1043_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* ESCAN00076622 */
#if (CANTRCV_30_TJA1043_USE_INIT_POINTER == STD_ON)
  /* #100 Store the configuration pointer. (Required before any check especially for PBL-configurations due to access to GeneratorCompatibilityVersion and MagicNumber via the ConfigPtr.) */
  CanTrcv_30_Tja1043_ConfigDataPtr = ConfigPtr;

# if ((CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON) || (CANTRCV_30_TJA1043_CONFIGURATION_VARIANT == CANTRCV_30_TJA1043_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE)) /* COV_CANTRCV_HL_LL_TJA1043_VARCOV_SW_FEAT_NOT_SUPPORTED */
  /* #10 Check if parameter ConfigPtr is valid. */
  if (ConfigPtr == NULL_PTR)
  {
#  if (CANTRCV_30_TJA1043_CONFIGURATION_VARIANT == CANTRCV_30_TJA1043_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) /* COV_CANTRCV_HL_LL_TJA1043_VARCOV_SW_FEAT_NOT_SUPPORTED */
    EcuM_BswErrorHook((uint16) CANTRCV_30_TJA1043_MODULE_ID, (uint8) ECUM_BSWERROR_NULLPTR);
#  endif /* (CANTRCV_30_TJA1043_CONFIGURATION_VARIANT == CANTRCV_30_TJA1043_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) */

#  if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON) /* COV_CANTRCV_HL_LL_TJA1043_VARCOV_SW_FEAT_NOT_SUPPORTED */
    /* \trace SPEC-14948 */
    errorId = CANTRCV_30_TJA1043_E_PARAM_POINTER;
#  endif /* (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON) */
  }
  else
# endif /* (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON) || (CANTRCV_30_TJA1043_CONFIGURATION_VARIANT == CANTRCV_30_TJA1043_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) */
# if (CANTRCV_30_TJA1043_CONFIGURATION_VARIANT == CANTRCV_30_TJA1043_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) /* COV_CANTRCV_HL_LL_TJA1043_VARCOV_SW_FEAT_NOT_SUPPORTED */
  /* #20 Check the generator compatibility version */
  if (CanTrcvCfg_GetGeneratorCompatibilityVersion() != (uint32)((CANTRCV_30_TJA1043_BASE_GENDATA_COMP_VERSION << 16u) | CANTRCV_30_TJA1043_HW_GENDATA_COMP_VERSION)) /* COV_CANTRCV_HL_LL_TJA1043_CODECOV_INVALID_GENDATA */
  {
    EcuM_BswErrorHook((uint16) CANTRCV_30_TJA1043_MODULE_ID, (uint8) ECUM_BSWERROR_COMPATIBILITYVERSION);
  }
  /* #30 Check the magic number */
  else if (CanTrcvCfg_GetMagicNumber() != CANTRCV_30_TJA1043_FINAL_MAGIC_NUMBER) /* COV_CANTRCV_HL_LL_TJA1043_CODECOV_INVALID_GENDATA */
  {
    EcuM_BswErrorHook((uint16) CANTRCV_30_TJA1043_MODULE_ID, (uint8) ECUM_BSWERROR_MAGICNUMBER);
  }
  else
# endif /* (CANTRCV_30_TJA1043_CONFIGURATION_VARIANT == CANTRCV_30_TJA1043_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE) */
#endif /* (CANTRCV_30_TJA1043_USE_INIT_POINTER == STD_ON) */
  {
    uint8_least index;

#if (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON) 
    Dio_LevelType CanTrcvERR;
    Dio_LevelType CanTrcvSTB;
#endif

#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
    /* #110 Set transceiver driver as initialized at all. */
    CanTrcv_30_Tja1043_IsInitialized = CANTRCV_30_TJA1043_IS_INIT;
#endif

    /* #120 Run through all transceiver channels and initialize them.*/
    for(index = 0; index < CANTRCV_30_TJA1043_MAX_CHANNEL; ++index)
    {

      /* Initialize variables */

      /* Initialize LL */
      CanTrcv_30_Tja1043_LL_InitMemoryChannelBegin((uint8)index);

      /* #130 Set the channel states concerning: initialization, wake-up report and wake-up reason to default values. */
      CanTrcv_30_Tja1043_Prob[index].wakeUpReport = CANTRCV_30_TJA1043_WU_ENABLE; /* SBSW_CANTRCV_HL_TJA1043_1 */
      CanTrcv_30_Tja1043_Prob[index].wakeUpReason = CANTRCV_30_TJA1043_WU_ERROR; /* SBSW_CANTRCV_HL_TJA1043_1 */

      /* #140 Set the channel state concerning: request state to default values (only SPI-interface or SBC-interface with PN). */

      /* ----- Implementation ----------------------------------------------- */

      /* #190 Initialize next parameters only for active transceiver channels. */
      if(CanTrcvCfg_IsChannelUsed(index))
      {

        /* #200 If no wake-up event occurred during initialization the default reason is RESET. */
        CanTrcv_30_Tja1043_Prob[index].wakeUpReason = CANTRCV_30_TJA1043_WU_RESET; /* SBSW_CANTRCV_HL_TJA1043_1 */

        /* #220 Do additional checks: wake-up event, HW status, PN configuration. (critical section is used). */
        CanTrcv_EnterCritical();
#if (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON) 
        /* \trace SPEC-14953 */

        CanTrcvERR = Dio_ReadChannel(CanTrcv_30_Tja1043_GetPinERROfDioConfiguration(index));
        CanTrcvSTB = Dio_ReadChannel(CanTrcv_30_Tja1043_GetPinSTBOfDioConfiguration(index));

#endif /* CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON || CANTRCV_30_TJA1043_HW_PN_SUPPORT == STD_ON */

        /* #240 Determine whether a wake-up event (BY_BUS, BY_PIN) occurred or NOT. If occurred store it. */
#if (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON)
        if(CANTRCV_30_TJA1043_CHECK_WA(index))
        {
          /* The wake-up reason is: BY_BUS */
          CanTrcv_30_Tja1043_Prob[index].wakeUpReason = CANTRCV_30_TJA1043_WU_BY_BUS; /* SBSW_CANTRCV_HL_TJA1043_1 */
        }
#endif /* CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON */

        CanTrcv_LeaveCritical();

        /* Do some generic initialization of LL */
        CanTrcv_30_Tja1043_LL_InitChannel((uint8)index);

#if (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON) 
        /* #260 Report the detected wake-up event to the upper layer. */
        CanTrcv_30_Tja1043_ReportWakeup((uint8)index);
#endif

        /* #270 Set the operating mode to NORMAL. In case of SPI-interface always synchronous. (critical section used) */
        CanTrcv_EnterCritical();

#if (CANTRCV_30_TJA1043_USE_ICU == STD_ON)
        if (CanTrcvCfg_IsIcuChannelSet(index)) /* \trace SPEC-14950 */
        {
          Icu_DisableNotification( CanTrcvCfg_GetIcuChannel(index) ); /* \trace SPEC-14973*/
        }
#endif

        Dio_WriteChannel(CanTrcv_30_Tja1043_GetPinSTBOfDioConfiguration(index),STD_HIGH);
        Dio_WriteChannel(CanTrcv_30_Tja1043_GetPinENOfDioConfiguration(index),STD_HIGH);
        
        CanTrcv_LeaveCritical();

      } /* CanTrcvChannelUsed == TRUE */
    } /* for (...) */
  } /* if (ConfigPtr == NULL_PTR) .. else */

#if (CANTRCV_30_TJA1043_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1043_E_NO_ERROR) /* PRQA S 3356, 3359 */ /* MD_CanTrcv_30_Tja1043_335X, MD_CanTrcv_30_Tja1043_335X */ /* COV_CANTRCV_HL_TJA1043_CODECOV_NOT_EACH_CONFIG */
  { /* PRQA S 3201 */ /* MD_CanTrcv_30_Tja1043_3201 */
    CanTrcv_DetReportError(CANTRCV_30_TJA1043_INIT_ID, errorId);
  }
#else
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(errorId);
#endif
  
#if (CANTRCV_30_TJA1043_USE_INIT_POINTER == STD_OFF)
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(ConfigPtr);
#endif
}  /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_SetOpMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_SetOpMode(uint8 CanTrcvIndex, CanTrcv_TrcvModeType OpMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1043_E_NO_ERROR;

  CanTrcv_30_Tja1043_TrcvModeType currentOpMode;

  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_TJA1043_MAX_CHANNEL)
  {
    /* \trace SPEC-19976 */  
    errorId = CANTRCV_30_TJA1043_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19976 */
    errorId = CANTRCV_30_TJA1043_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1043_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15064 */
    errorId = CANTRCV_30_TJA1043_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute transition of operating mode only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
#endif
    {
      /* #110 Check if the current operating mode equals the requested one. */
      (void)CanTrcv_30_Tja1043_GetOpMode(CanTrcvIndex, &currentOpMode); /* SBSW_CANTRCV_HL_TJA1043_3 */

      if (currentOpMode == OpMode) /* \trace SPEC-15090 */
      {
        /* \trace SPEC-19955 */
        returnVal = E_OK;

      }
      else
      {
        /* #160 The requested one does NOT equal the current one. Execute the requested mode change. (critical section is used) */
        /* \trace SPEC-19962 */
        switch(OpMode)
        {
          /* #200 Mode change request to NORMAL. */
          case CANTRCV_30_TJA1043_OP_MODE_NORMAL:

            /* #210 Check whether it is an internal wake-up. If yes store the wake-up reason. */         
            if(
               (CanTrcv_30_Tja1043_Prob[CanTrcvIndex].wakeUpReason == CANTRCV_30_TJA1043_WU_ERROR))
            {
              /* Transceiver is switched from STANDBY/SLEEP -> NORMAL and has not detected any wakeup.
                 This is considered as internal wakeup. */
              CanTrcv_30_Tja1043_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_TJA1043_WU_INTERNALLY; /* SBSW_CANTRCV_HL_TJA1043_1 */
            }
            
            CanTrcv_EnterCritical();

            /* #220 If ICU is configured, disable ICU. */
# if (CANTRCV_30_TJA1043_USE_ICU == STD_ON)
            if (CanTrcvCfg_IsIcuChannelSet(CanTrcvIndex)) /* \trace SPEC-14950 */
            {
              Icu_DisableNotification( CanTrcvCfg_GetIcuChannel(CanTrcvIndex) ); /* \trace SPEC-14973 */
            }
# endif
            
            {
              /* #240 No mode request is currently pending. Store the current mode request. (only SPI-interface) */
              /* #250 Execute operating mode change request to NORMAL. */
              Dio_WriteChannel(CanTrcv_30_Tja1043_GetPinSTBOfDioConfiguration(CanTrcvIndex),STD_HIGH);
              Dio_WriteChannel(CanTrcv_30_Tja1043_GetPinENOfDioConfiguration(CanTrcvIndex),STD_HIGH);
              
            }

            CanTrcv_LeaveCritical();
            returnVal = E_OK;
            break;

          case CANTRCV_30_TJA1043_OP_MODE_STANDBY:
             /* #300 Mode change request to STANDBY. (only if supported by HW) */
            /* #310 Mode transition to STANDBY is only possible from NORMAL. Otherwise DET error is reported. */
            if(currentOpMode != CANTRCV_30_TJA1043_OP_MODE_NORMAL) /* \trace SPEC-19955 */
            {
#  if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
              /* \trace SPEC-19985 */
              errorId = CANTRCV_30_TJA1043_E_TRCV_NOT_NORMAL;
#  endif
            }
            else
            {
              /* #320 Current mode is NORMAL: Execute mode request. */
              CanTrcv_EnterCritical();

              /* #330 If ICU is configured, disable ICU. */
# if (CANTRCV_30_TJA1043_USE_ICU == STD_ON)
              if (CanTrcvCfg_IsIcuChannelSet(CanTrcvIndex)) /* \trace SPEC-14950 */
              {
                Icu_EnableNotification( CanTrcvCfg_GetIcuChannel(CanTrcvIndex) ); /* \trace SPEC-15004 */
              }
# endif
              /* #340 Reset wake-up reason. */
              CanTrcv_30_Tja1043_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_TJA1043_WU_ERROR; /* SBSW_CANTRCV_HL_TJA1043_1 */

              {
                /* #360 No mode request is currently pending. Store the mode request. (only SPI-interface) */
                /* #370 Execute operating mode change request to STANDBY. */
                Dio_WriteChannel(CanTrcv_30_Tja1043_GetPinENOfDioConfiguration(CanTrcvIndex),STD_LOW);
                Dio_WriteChannel(CanTrcv_30_Tja1043_GetPinSTBOfDioConfiguration(CanTrcvIndex),STD_LOW);
              }

              CanTrcv_LeaveCritical();
              returnVal = E_OK;
            }
            break;

          case CANTRCV_30_TJA1043_OP_MODE_SLEEP:
            /* #400 Mode change request to SLEEP. (only if supported by HW) */

            /* #410 Mode transition to SLEEP is only possible from STANDBY. Otherwise DET error is reported. */
            if(currentOpMode != CANTRCV_30_TJA1043_OP_MODE_STANDBY)
            {
#  if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
              /* \trace SPEC-19964 */
              errorId = CANTRCV_30_TJA1043_E_TRCV_NOT_STANDBY;
#  endif
            }
            else
            {
              CanTrcv_EnterCritical();

              {
                /* #430 No mode request is currently pending. Store the mode request. (only SPI-interface) */
                /* #440 Execute operating mode change request to SLEEP. */
                Dio_WriteChannel(CanTrcv_30_Tja1043_GetPinENOfDioConfiguration(CanTrcvIndex),STD_HIGH);
                Dio_WriteChannel(CanTrcv_30_Tja1043_GetPinSTBOfDioConfiguration(CanTrcvIndex),STD_LOW);
              }

              CanTrcv_LeaveCritical();
              returnVal = E_OK;
            }
            break;

          default: /* PRQA S 2018 */ /* MD_MSR_14.1 */
#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
            /* \trace SPEC-14963 */
            /* #40 Check if parameter OpMode is valid. */
            errorId = CANTRCV_30_TJA1043_E_PARAM_TRCV_OP_MODE;
#endif
            break;
          } /* switch() */
      } /* currentOpMode == OpMode */

      /* #600 If mode request executed successfully then inform the CanIf else report error. */
      if (returnVal == E_OK)
      {
        (void)CanTrcv_30_Tja1043_GetOpMode(CanTrcvIndex, &currentOpMode); /* SBSW_CANTRCV_HL_TJA1043_3 */

        if(currentOpMode == OpMode) /* COV_CANTRCV_LL_TJA1043_CODECOV_HW_FAILURE */
        {
          CanIf_30_Tja1043_TrcvModeIndication(CanTrcvIndex, currentOpMode); /* \trace SPEC-20006 */
        }
        else
        {
          /* \trace SPEC-20011 */
          errorId = CANTRCV_30_TJA1043_E_NO_TRCV_CONTROL;

          returnVal = E_NOT_OK;
        } /* currentOpMode != OpMode */
      } /* returnVal == E_OK */
    } /* channelUsed == TRUE */
  }

#if (CANTRCV_30_TJA1043_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1043_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1043_SETOPMODE_ID, errorId);
  }
#else
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(errorId);
#endif
  return returnVal;
} /* PRQA S 6010,6030,6050,6080 */ /* MD_MSR_STPTH,MD_MSR_STCYC,MD_MSR_STCAL,MD_MSR_STMIF */

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_GetOpMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_GetOpMode(uint8 CanTrcvIndex, P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANTRCV_30_TJA1043_APPL_VAR) OpMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1043_E_NO_ERROR;

  Dio_LevelType CanTrcvSTB;
  Dio_LevelType CanTrcvEN;

  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter OpMode is valid. */
  if(OpMode == NULL_PTR)
  {
    /* \trace SPEC-14958 */
    errorId = CANTRCV_30_TJA1043_E_PARAM_POINTER;
  }
  /* #20 Check if parameter CanTrcvIndex is valid. */
  else if(CanTrcvIndex >= CANTRCV_30_TJA1043_MAX_CHANNEL)
  {
    /* \trace SPEC-20009 */
    errorId = CANTRCV_30_TJA1043_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-20009 */
    errorId = CANTRCV_30_TJA1043_E_INVALID_CAN_NETWORK;
  }
  /* #40 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1043_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15042 */
    errorId =  CANTRCV_30_TJA1043_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
#endif
    {
      /* #200 DIO-interface: Read the mode from status of PINs of underlying HW. (critical section used) */
      /* #201 SPI-interface: Read the mode from state variable. */
      /* #202 SBC-interface: Read the mode via SBC module API. (critical section used) */
      CanTrcv_EnterCritical();

      CanTrcvSTB = Dio_ReadChannel(CanTrcv_30_Tja1043_GetPinSTBOfDioConfiguration(CanTrcvIndex));
      CanTrcvEN  = Dio_ReadChannel(CanTrcv_30_Tja1043_GetPinENOfDioConfiguration(CanTrcvIndex));
      
      CanTrcv_LeaveCritical();

      {
        /* \trace SPEC-19974 */

        if((CanTrcvSTB == STD_HIGH) && (CanTrcvEN == STD_HIGH)) /* COV_CANTRCV_HL_LL_TJA1043_CODECOV_HW_SPECIFIC */
        {
          /* CAN transceiver is in normal operation mode */
          *OpMode = CANTRCV_30_TJA1043_OP_MODE_NORMAL; /* SBSW_CANTRCV_HL_TJA1043_2 */
          returnVal = E_OK;
        }

        if((CanTrcvSTB == STD_LOW) && (CanTrcvEN == STD_HIGH))
        {
          /* CAN transceiver is in sleep mode */
          *OpMode = CANTRCV_30_TJA1043_OP_MODE_SLEEP; /* SBSW_CANTRCV_HL_TJA1043_2 */
          returnVal = E_OK;
        }

        if((CanTrcvSTB == STD_LOW) && (CanTrcvEN == STD_LOW))
        {
          /* CAN transceiver is in standby mode */
          *OpMode = CANTRCV_30_TJA1043_OP_MODE_STANDBY; /* SBSW_CANTRCV_HL_TJA1043_2 */
          returnVal = E_OK;
        }
      }

      /* #210 If reading of operating mode NOT succeeded report error. */
      if (returnVal == E_NOT_OK) /* PRQA S 3356,3359 */ /* MD_CanTrcv_30_Tja1043_13.7 */ /* COV_CANTRCV_HL_LL_TJA1043_CODECOV_HW_SPECIFIC */
      { /* PRQA S 3201 */ /* MD_CanTrcv_30_Tja1043_3201 */
        /* \trace SPEC-19940 */
        errorId = CANTRCV_30_TJA1043_E_NO_TRCV_CONTROL;
      }
    } /* Channel is used */
  } /* DET checks passed */
  
#if (CANTRCV_30_TJA1043_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1043_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1043_GETOPMODE_ID, errorId);
  }
#else
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(errorId);
#endif

 return returnVal;
}  /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_GetBusWuReason
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_GetBusWuReason(uint8 CanTrcvIndex, P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANTRCV_30_TJA1043_APPL_VAR) Reason)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1043_E_NO_ERROR;

#if (CANTRCV_30_TJA1043_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_TJA1043_WAKEUP_NONE) 
  CanTrcv_30_Tja1043_TrcvModeType currentOpMode;
#endif

  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if the return-parameter Reason is valid. */
  if(Reason == NULL_PTR)
  {
    /* \trace SPEC-15063 */
    errorId = CANTRCV_30_TJA1043_E_PARAM_POINTER;
  }
  /* #20 Check if parameter CanTrcvIndex is valid. */
  else if(CanTrcvIndex >= CANTRCV_30_TJA1043_MAX_CHANNEL)
  {
    /* \trace SPEC-19993 */
    errorId = CANTRCV_30_TJA1043_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19993 */
    errorId = CANTRCV_30_TJA1043_E_INVALID_CAN_NETWORK;
  }
  /* #40 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1043_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15059 */
    errorId = CANTRCV_30_TJA1043_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
#endif
    {
      /* UREQ00015010 */
      /* #200 Check the wake-up reason for validity. */
#if (CANTRCV_30_TJA1043_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_TJA1043_WAKEUP_NONE) 
      if(CanTrcv_30_Tja1043_Prob[CanTrcvIndex].wakeUpReason == CANTRCV_30_TJA1043_WU_ERROR)
      {
        /* #300 If wake-up reason is invalid return WU_ERROR. */
        *Reason = CANTRCV_30_TJA1043_WU_ERROR; /* SBSW_CANTRCV_HL_TJA1043_2 */

        /* #310 Wake-up reason is invalid (WU_ERROR). This is OK only in case of transceiver channel is in NORMAL mode. */
        (void)CanTrcv_30_Tja1043_GetOpMode(CanTrcvIndex, &currentOpMode); /* SBSW_CANTRCV_HL_TJA1043_3 */

        if(currentOpMode != CANTRCV_30_TJA1043_OP_MODE_NORMAL)
        {
          /* \trace SPEC-19980 */
          /* #320 Being in any mode except NORMAL with WU_ERROR is an error hence report it. */
          errorId = CANTRCV_30_TJA1043_E_NO_TRCV_CONTROL;
        }
      }
      else
      {
        /* #400 Wake-up reason is valid (neither WU_ERROR nor WU_NOT_SUPPORTED). Return the current wake-up reason.*/
        *Reason = CanTrcv_30_Tja1043_Prob[CanTrcvIndex].wakeUpReason; /* SBSW_CANTRCV_HL_TJA1043_2 */
        returnVal = E_OK;
      }
#else /* (CANTRCV_30_TJA1043_GENERAL_WAKE_UP_SUPPORT == CANTRCV_30_TJA1043_WAKEUP_NONE) */
      *Reason = CANTRCV_30_TJA1043_WU_NOT_SUPPORTED; /* SBSW_CANTRCV_HL_TJA1043_2 */
#endif /* (CANTRCV_30_TJA1043_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_TJA1043_WAKEUP_NONE) */
    } /* IsChannelUsed */
  }
  
#if (CANTRCV_30_TJA1043_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1043_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1043_GETBUSWUREASON_ID, errorId);
  }
#else
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(errorId);
#endif
  
  return returnVal;
}  /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_SetWakeupMode
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_SetWakeupMode(uint8 CanTrcvIndex, CanTrcv_TrcvWakeupModeType TrcvWakeupMode)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1043_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_TJA1043_MAX_CHANNEL)
  {
    /* \trace SPEC-19998 */
    errorId = CANTRCV_30_TJA1043_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-19998 */
    errorId = CANTRCV_30_TJA1043_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1043_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-15077 */
    errorId = CANTRCV_30_TJA1043_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_TJA1043_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_TJA1043_WAKEUP_NONE) 
# if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active. */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
    {
      /* #200 Set the requested wake-up mode. */
      switch(TrcvWakeupMode)
      {
        case CANTRCV_30_TJA1043_WU_ENABLE:
             /* \trace SPEC-19990 */
             CanTrcv_30_Tja1043_Prob[CanTrcvIndex].wakeUpReport = CANTRCV_30_TJA1043_WU_ENABLE; /* SBSW_CANTRCV_HL_TJA1043_1 */

             /* #300 In addition: If requested wake-up mode is WU_ENABLE report if wake-up event(s) is/are pending. */
# if (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON) 
             CanTrcv_30_Tja1043_ReportWakeup(CanTrcvIndex);
# endif

             returnVal = E_OK;
             break;

        case CANTRCV_30_TJA1043_WU_DISABLE:
             /* \trace SPEC-20012 */
             CanTrcv_30_Tja1043_Prob[CanTrcvIndex].wakeUpReport = CANTRCV_30_TJA1043_WU_DISABLE; /* SBSW_CANTRCV_HL_TJA1043_1 */

             returnVal = E_OK;
             break;

        case CANTRCV_30_TJA1043_WU_CLEAR:
             /* \trace SPEC-19961 */
             /* #500 In addition: If requested wake-up mode is WU_CLEAR clear the wake-up reason and all detected wake-up events. */
             CanTrcv_30_Tja1043_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_TJA1043_WU_ERROR; /* SBSW_CANTRCV_HL_TJA1043_1 */
             returnVal = E_OK;

             break;
        default:  /* PRQA S 2018 */ /* MD_MSR_14.1 */
# if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
             /* #40 Check if parameter TrcvWakeupMode is valid. */
             errorId = CANTRCV_30_TJA1043_E_PARAM_TRCV_WAKEUP_MODE; /* \trace SPEC-15036 */
# endif
             break;
      }
    }
#endif /* CANTRCV_30_TJA1043_GENERAL_WAKE_UP_SUPPORT != CANTRCV_30_TJA1043_WAKEUP_NONE */
  }
  
#if (CANTRCV_30_TJA1043_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1043_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1043_SETWAKEUPMODE_ID, errorId);
  }
#else
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(errorId);
#endif  
  
#if (CANTRCV_30_TJA1043_GENERAL_WAKE_UP_SUPPORT == CANTRCV_30_TJA1043_WAKEUP_NONE) 
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(TrcvWakeupMode);
# if(CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_OFF)
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(CanTrcvIndex);
# endif
#endif
  /* \trace SPEC-19978: Not implemented as no need to query HW at this place. */

  return returnVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_CheckWakeup
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(Std_ReturnType, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_CheckWakeup(uint8 CanTrcvIndex)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType returnVal = E_NOT_OK;
  uint8 errorId = CANTRCV_30_TJA1043_E_NO_ERROR;

#if (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON) 
  Dio_LevelType CanTrcvERR;
  Dio_LevelType CanTrcvSTB;
#endif /* CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED */

  /* ----- Development Error Checks ------------------------------------- */
#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter CanTrcvIndex is valid. */
  if(CanTrcvIndex >= CANTRCV_30_TJA1043_MAX_CHANNEL)
  {
    /* \trace SPEC-20003 */
    errorId = CANTRCV_30_TJA1043_E_INVALID_CAN_NETWORK;
  }
  /* #20 Check if transceiver channel (CanTrcvIndex) is active. */
  else if(!CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
  {
    /* \trace SPEC-20003 */
    errorId = CANTRCV_30_TJA1043_E_INVALID_CAN_NETWORK;
  }
  /* #30 Check if transceiver channel (CanTrcvIndex) is initialized. */
  else if(!CANTRCV_30_TJA1043_IS_INITIALIZED(CanTrcvIndex))
  {
    /* \trace SPEC-19994 */
    errorId = CANTRCV_30_TJA1043_E_UNINIT;
  }
  else
#endif
  {
    /* ----- Implementation ----------------------------------------------- */
#if (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON)
# if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_OFF)
    /* #100 Do execute the request only if transceiver channel (CanTrcvIndex) is active and wake-up detection is enabled. (critical section used) */
    if(CanTrcvCfg_IsChannelUsed(CanTrcvIndex))
# endif
    {
      if(CanTrcvCfg_IsWakeupByBusUsed(CanTrcvIndex) &&
         (CanTrcv_30_Tja1043_Prob[CanTrcvIndex].wakeUpReport == CANTRCV_30_TJA1043_WU_ENABLE)) /* COV_CANTRCV_HL_TJA1043_CODECOV_IS_WU_BY_BUS_USED */
      {
        CanTrcv_30_Tja1043_TrcvModeType currentOpMode;
        CanTrcv_EnterCritical();

        /* #110 Is the transceiver channel in NORMAL? (only DIO-/SBC-interface) */
        (void)CanTrcv_30_Tja1043_GetOpMode(CanTrcvIndex, &currentOpMode); /* SBSW_CANTRCV_HL_TJA1043_3 */

        if (currentOpMode == CANTRCV_30_TJA1043_OP_MODE_NORMAL)
        {
          /* #120 Operating mode NORMAL: No valid wake-up event detected. (only DIO-/SBC-interface)*/
          returnVal = E_NOT_OK;
        }
        else
        /* #200 Check if there are any wake-up events pending in HW. */
        if (CANTRCV_30_TJA1043_IS_EXTERNAL_WU_REASON(CanTrcv_30_Tja1043_Prob[CanTrcvIndex].wakeUpReason)) /* COV_CANTRCV_HL_LL_TJA1043_CODECOV_WU_BY_PIN */
        {
          /* #300 Any wake-up event is pending: Check if currently an operating mode change is requested. (only asynchronous SPI-interface) */
          {
            /* #340 Operating mode STANDBY / SLEEP: Report the detected wake-up event to the EcuM. */
            CanTrcv_30_Tja1043_ReportWakeup(CanTrcvIndex);

            returnVal = E_OK; /* wake-up detected  */
          }
        }
        else
        {
          /* #400 No pending wake-up flags. Request the underlying HW for wake-up flags. */
          CanTrcvERR = Dio_ReadChannel(CanTrcv_30_Tja1043_GetPinERROfDioConfiguration(CanTrcvIndex));
          CanTrcvSTB = Dio_ReadChannel(CanTrcv_30_Tja1043_GetPinSTBOfDioConfiguration(CanTrcvIndex));
          if (CANTRCV_30_TJA1043_CHECK_WA(CanTrcvIndex)) /* COV_CANTRCV_HL_LL_TJA1043_CODECOV_CHECK_WA */
          {
            CanTrcv_30_Tja1043_Prob[CanTrcvIndex].wakeUpReason = CANTRCV_30_TJA1043_WU_BY_BUS; /* SBSW_CANTRCV_HL_TJA1043_1 */
            CanTrcv_30_Tja1043_ReportWakeup(CanTrcvIndex);

            returnVal = E_OK;  /* Wakeup detected */ /* \trace SPEC-20014 */
          }

        }

        CanTrcv_LeaveCritical();

      }
    }
#else
    returnVal = E_NOT_OK;
#endif /* CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED */
  }
  
#if (CANTRCV_30_TJA1043_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1043_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1043_CHECKWAKEUP_ID, errorId);
  }
#else
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(errorId);
#endif  
  
#if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_OFF) && (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_OFF)
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(CanTrcvIndex);
#endif
  return returnVal;
}  /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

#if (CANTRCV_30_TJA1043_GET_VERSION_INFO == STD_ON) /* \trace SPEC-15105 */
/* \trace SPEC-19953 */
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_GetVersionInfo
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, CANTRCV_30_TJA1043_APPL_VAR) VersionInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CANTRCV_30_TJA1043_E_NO_ERROR;
  
  /* ----- Development Error Checks ------------------------------------- */
# if (CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON)
  /* #10 Check if parameter VersionInfo is valid. */
  if(VersionInfo == NULL_PTR)
  {
    errorId = CANTRCV_30_TJA1043_E_PARAM_POINTER;
  }
  else
# endif /* CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON */
  {
    /* ----- Implementation ----------------------------------------------- */
    /* \trace SPEC-14986, SPEC-15032 */
    /* #100 Retrieve the version information: VENDOR_ID, MODULE_ID, SW_MAJOR-, SW_MINOR- and SW_PATCH-version. */
    VersionInfo->vendorID = CANTRCV_30_TJA1043_VENDOR_ID; /* SBSW_CANTRCV_HL_TJA1043_2 */
    VersionInfo->moduleID = CANTRCV_30_TJA1043_MODULE_ID; /* SBSW_CANTRCV_HL_TJA1043_2 */

    VersionInfo->sw_major_version = CANTRCV_30_TJA1043_SW_MAJOR_VERSION; /* SBSW_CANTRCV_HL_TJA1043_2 */
    VersionInfo->sw_minor_version = CANTRCV_30_TJA1043_SW_MINOR_VERSION; /* SBSW_CANTRCV_HL_TJA1043_2 */
    VersionInfo->sw_patch_version = CANTRCV_30_TJA1043_SW_PATCH_VERSION; /* SBSW_CANTRCV_HL_TJA1043_2 */
  }
  
#if (CANTRCV_30_TJA1043_DEV_ERROR_REPORT == STD_ON)
  if (errorId != CANTRCV_30_TJA1043_E_NO_ERROR)
  {
    CanTrcv_DetReportError(CANTRCV_30_TJA1043_GETVERSIONINFO_ID, errorId);
  }
#else
  CANTRCV_30_TJA1043_DUMMY_STATEMENT(errorId);
#endif 
}
#endif /* CANTRCV_30_TJA1043_GET_VERSION_INFO == STD_ON */

/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_MainFunction
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 **********************************************************************************************************************/
FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_MainFunction(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8_least index;
  
  /* ----- Implementation ----------------------------------------------- */
  /* \trace SPEC-15067, SPEC-15085 */
  /* #100 Run through all transceiver channels. */
  for(index = 0; index < CANTRCV_30_TJA1043_MAX_CHANNEL; ++index)
  {
    if (CanTrcvCfg_IsChannelUsed(index))
    {
      {
        /* #200 Execute only if transceiver channel is active and initialized. */
        CanTrcv_30_Tja1043_TrcvModeType currentOpMode;

        (void)CanTrcv_30_Tja1043_GetOpMode((uint8)index, &currentOpMode); /* SBSW_CANTRCV_HL_TJA1043_3 */

        /* #300 Execute only if transceiver channel is in power-down mode (STANDBY / SLEEP). (only DIO- or SBC-interface) */
        if (currentOpMode != CANTRCV_30_TJA1043_OP_MODE_NORMAL)
        {
#if (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON) && (CANTRCV_30_TJA1043_GENERAL_WAKE_UP_SUPPORT == CANTRCV_30_TJA1043_WAKEUP_POLLING) 
          if (CanTrcvCfg_IsWakeupByBusUsed(index)) /* COV_CANTRCV_HL_TJA1043_CODECOV_IS_WU_BY_BUS_USED */
          {
            {
              /* #210 Transceiver channel is in power-down mode (STANDBY / SLEEP) and has wake-up support enabled: Check if a wake-up event occurred. (critical section used) */
              Dio_LevelType CanTrcvERR;
              Dio_LevelType CanTrcvSTB;

              CanTrcv_TrcvWakeupReasonType wakeupReason = CANTRCV_30_TJA1043_WU_ERROR;

              CanTrcv_EnterCritical();
              /* #310 Determine whether a wake-up event occurred or NOT from current state of DIO pins. (only DIO-interface) */
              CanTrcvERR = Dio_ReadChannel(CanTrcv_30_Tja1043_GetPinERROfDioConfiguration(index));
              CanTrcvSTB = Dio_ReadChannel(CanTrcv_30_Tja1043_GetPinSTBOfDioConfiguration(index));
              if(CANTRCV_30_TJA1043_CHECK_WA(index)) /* COV_CANTRCV_HL_LL_TJA1043_CODECOV_CHECK_WA */
              {
                wakeupReason = CANTRCV_30_TJA1043_WU_BY_BUS;
              }

              if (wakeupReason != CANTRCV_30_TJA1043_WU_ERROR)
              {
                /* #500 If any wake-up event detected, store the wake-up event. */
                CanTrcv_30_Tja1043_Prob[index].wakeUpReason = wakeupReason; /* SBSW_CANTRCV_HL_TJA1043_1 */

                if (CanTrcv_30_Tja1043_Prob[index].wakeUpReport == CANTRCV_30_TJA1043_WU_ENABLE)
                {
                  /* #510 If any wake-up event detected and wake-up detection is enabled, inform the EcuM to check for wake-up event(s). */
                  EcuM_CheckWakeup( CanTrcvCfg_GetWakeupSource(index) );
                }
              }

              CanTrcv_LeaveCritical();
            } /* (!CanTrcv_30_Tja1043_IsReqFlagPnd(index)) */
          }
# endif /* (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON) */
        } /* CanTrcv_30_Tja1043_Prob[index].curOpMode != CANTRCV_30_TJA1043_OP_MODE_NORMAL */
      } /* CanTrcv_30_Tja1043_Prob[index].isInit != CANTRCV_30_TJA1043_IS_INIT */
    } /*  CanTrcvCfg_IsChannelUsed(index)  */
  } /* for ... */
}  /* PRQA S 6030,6080 */ /* MD_MSR_STCYC,MD_MSR_STMIF */

#if (CANTRCV_30_TJA1043_WAKEUP_BY_BUS_USED == STD_ON) 
/***********************************************************************************************************************
| NAME:  CanTrcv_30_Tja1043_ReportWakeup
 **********************************************************************************************************************/
/*! Internal comment removed.
 *
 *
 *
 **********************************************************************************************************************/
CANTRCV_30_TJA1043_LOCAL_INLINE FUNC(void, CANTRCV_30_TJA1043_CODE) CanTrcv_30_Tja1043_ReportWakeup(uint8 CanTrcvIndex)
{
  /* ----- Implementation ----------------------------------------------- */
  
  /* #100 If any wake-up event occurred, report it to EcuM. */
  /* #110 Depending on configuration report to EcuM the wake-up source which belongs to occurred wake-up reason (POWER_ON, BY_SYSERR (only PN), BY_BUS, BY_PIN). */
  switch(CanTrcv_30_Tja1043_Prob[CanTrcvIndex].wakeUpReason)
  {
  case CANTRCV_30_TJA1043_WU_BY_BUS:
    /* \trace SPEC-14953 */
    EcuM_SetWakeupEvent( CanTrcvCfg_GetWakeupSource(CanTrcvIndex) );
    break;

  default:
    /* No valid or an internal wakeup. Do not report this as wakeup event */
    break;
  }
}
#endif

#define CANTRCV_30_TJA1043_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* **************************************************************************/
/*  MISRA deviations                                                        */
/* **************************************************************************/
/* Justification for module-specific MISRA deviations:

MD_CanTrcv_30_Tja1043_0715:
  Reason: Complex code structure used and not split in modules or functions to make the code compact and efficent.
  Risk: Hard to understand.
  Prevention: Code inspection and multiple configuration aspects used in component test.

MD_CanTrcv_30_Tja1043_0777:
  Reason: ASR requires that all externals and APIs have the format <Msn>_<xyz>, while <Msn> has the
          format <BswmModuleName>_<VendorId>_<VendorApiInfix> for external hardware. Because of this
          requirement the first chars are same for all external declartations.
  Risk: Non-conforming Code.
  Prevention: Multiple configuration aspects used in component test.

MD_CanTrcv_30_Tja1043_0779
  Reason: Code which is much better and easier to maintain.
  Risk: Compiler and preprocessor do not support identifiers with more than 31 characters.
  Prevention: Test of software with real compiler and preprocessor on real MCU-target.

MD_CanTrcv_30_Tja1043_13.7:
  Reason: Result or value is always true or false depend on configuration aspect and used HW specific implementation
  Risk: Incorrect value return will be ignored.
  Prevention: Code inspection and test of the different variants in the component test.

MD_CanTrcv_30_Tja1043_3201:
  Reason: For some configuration variants code may be unreachable.
  Risk: Code is not executed.
  Prevention: Code inspection and test of the different variants in the component test.

MD_CanTrcv_30_Tja1043_8.7:
  Reason: Definition of CanIfState in global section because of better over-view.
  Risk: Name conflict.
  Prevention: Check for name conflicts.

MD_CanTrcv_30_Tja1043_3408:
  Reason: Some local variables are declared without static declaration to allow better debugging.
  Risk: Name conflict.
  Prevention: All external variables are prefixed with <Msn>

MD_CanTrcv_30_Tja1043_3448:
  Reason: Variables are declared with external linkage in order to allow XCP debugging. These must not be accessed
          from outside. So the types shall remain internal.
  Risk: None.
  Prevention: None.

 MD_CanTrcv_30_Tja1043_335X:
  Reason: Caused by High-level Low-level concept of CAN transceiver driver while the High-level must offer maximum flexibility for the Low-level.
          This concept may lead to fact that NOT every condition may be stimulated / required by the Low-level.
  Risk: Code is not executed.
  Prevention: Every High-level + Low-level is tested and reviewed separately.

*/

/* **************************************************************************/
/*  SILENT justifications                                                   */
/* **************************************************************************/
/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_CANTRCV_HL_TJA1043_1
\DESCRIPTION The variable "CanTrcv_30_Tja1043_Prob[]" must be accessed with index which is < CANTRCV_30_TJA1043_MAX_CHANNEL. 
\COUNTERMEASURE \N In case of an internal access initiated by the CanTrcv-driver itself this is ensured by the driver itself. The internal
access index is generated by a FOR-loop-count-index which runs from "0" until "CANTRCV_30_TJA1043_MAX_CHANNEL-1".
In case of an external access initiated by an upper layer e.g. CanIf this is ensured if CANTRCV_30_TJA1043_DEV_ERROR_DETECT == STD_ON.

\ID SBSW_CANTRCV_HL_TJA1043_2
\DESCRIPTION Write access to a pointer passed by an upper layer e.g. CanIf. Source data is of the same type as the destination data.
\COUNTERMEASURE \N The caller ensures that a valid pointer is passed. By the way compiler ensures that no memory violation occurs.

\ID SBSW_CANTRCV_HL_TJA1043_3
\DESCRIPTION Function call with passed pointer as parameter.
\COUNTERMEASURE \N Initiated and ensured by the CanTrcv-driver itself that a valid pointer is passed. By the way the compiler ensures that no memory violation occurs.

\ID SBSW_CANTRCV_HL_TJA1043_4
\DESCRIPTION Function pointer call.
\COUNTERMEASURE \N Initiated and ensured by the CanTrcv-driver itself that a valid function pointer is used. Used function pointer is retrieved from a constant table which is NOT generated. 
                   By the way the compiler ensures that no memory violation occurs.

SBSW_JUSTIFICATION_END */

/* **************************************************************************/
/*  COVERAGE justifications                                                 */
/* **************************************************************************/
/* START_COVERAGE_JUSTIFICATION

\ID COV_CANTRCV_HL_TJA1043_VARCOV_AVOID_COREVER_REDEF
  \ACCEPT TX
  \REASON Avoids the re-definition of CORE-version in case of multiple CanTrcv-driver are used. Hence decision "F" can NOT be fulfilled. Correct functionality is ensured by code-review.

\ID COV_CANTRCV_HL_TJA1043_CODECOV_NOT_EACH_CONFIG
  \ACCEPT XF
  \REASON The stimulation is not possible in each configuration. It will be ensured by inspection that both decisions are covered
          in at least one configuration. In addition correct functionality is verified by code review.

\ID COV_CANTRCV_HL_TJA1043_CODECOV_DEFENSIVE_CODING_STYLE
  \ACCEPT TX
  \REASON The code is required due to HL-LL-concept and in order to prevent malfunctions in case of programming of LL. 
          Hence the stimulation is not possible in case of correct programming of LL. The correct functionality is verified by code review.

\ID COV_CANTRCV_HL_TJA1043_CODECOV_IS_WU_BY_BUS_USED
  \ACCEPT TX
  \ACCEPT TF tx tf
  \REASON Condition / decision not covered by automatic tests. Affected code has low complexity because no else-path is available. 
          The code is verified by code inspection.

\ID COV_CANTRCV_HL_TJA1043_CODECOV_OP_MODE_REQ_NONE
  \ACCEPT TF tf tx
  \REASON Condition not covered by automatic tests but both decisions are covered. Affected code has low complexity. 
          The code is verified by code inspection.

\ID COV_CANTRCV_HL_LL_TJA1043_VARCOV_SW_FEAT_NOT_SUPPORTED
  \ACCEPT TF tf xf
  \ACCEPT XF
  \ACCEPT TX
  \REASON Post-build loadable is not supported.

\ID COV_CANTRCV_HL_LL_TJA1043_CODECOV_INVALID_GENDATA
  \ACCEPT XF xf xf tx xx
  \ACCEPT TX
  \ACCEPT XF
  \REASON Not all condition-decision variants can be stimulated, because therefore the generated data must be manipulated which is NOT applicable.
          Correct functionality is ensured by code-review.

\ID COV_CANTRCV_HL_LL_TJA1043_CODECOV_HW_SPECIFIC
  \ACCEPT XF
  \ACCEPT TF tf tx
  \REASON Depending on used HW and due to HL-LL-concept NOT all condition-decision variants can be stimulated.
          Correct functionality is ensured by code-review.

\ID COV_CANTRCV_LL_TJA1043_CODECOV_HW_FAILURE
  \ACCEPT TX
  \ACCEPT TX tx xx
  \REASON [COV_MSR_HW_FAILURE]

\ID COV_CANTRCV_HL_LL_TJA1043_CODECOV_WU_BY_PIN
  \ACCEPT XF
  \ACCEPT TF tf xf tf
  \REASON The detection of wakeup reason BY_PIN is verified by manual execution of TCASE-388160. In addition the code is verified by code inspection.

\ID COV_CANTRCV_HL_LL_TJA1043_CODECOV_CHECK_WA
  \ACCEPT TF tx tf
  \REASON For reliable detection of wakeup the operating mode of CAN transceiver HW is considered as well and must be a low power mode (STANDBY or SLEEP). 
          Hence not all conditions can be covered at runtime but both decisions are covered. Correctness of condition is verified by code inspection.

END_COVERAGE_JUSTIFICATION */ 

/* ********************************************************************************************************************
 *  END OF FILE
 * *******************************************************************************************************************/
