 /**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**
 * \addtogroup  Os_Hal_Context
 * \{
 *
 * \file        Os_Hal_Context.c
 * \brief       Context related primitives which must not be inlined.
 *
 *
 *********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

                                                                                                                        /* PRQA S 0777, 0779, 0810, 0828, 0857 EOF */ /* MD_MSR_5.1_777, MD_MSR_5.1_779, MD_MSR_1.1_810, MD_MSR_1.1_828, MD_MSR_1.1_857 */

#define OS_HAL_CONTEXT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
/* AUTOSAR includes */
#include "Std_Types.h"

/* Os kernel module dependencies */

/* Os hal dependencies */
#include "Os_Hal_Context.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define OS_START_SEC_CODE
#include "Os_MemMap_OsCode.h"                                                                                           /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Os_Hal_ContextSwitch()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(void, OS_CODE, OS_HAL_NOINLINE,
Os_Hal_ContextSwitch,
(
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Current,
  P2CONST(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Next
))
{
  /* #10 Store common context registers to current context. */
  Current->Os_Hal_LP  = Os_Hal_GetLP();                                                                                 /* SBSW_OS_HAL_PWA_CALLER */
  Current->Os_Hal_PSW = Os_Hal_GetPSW();                                                                                /* SBSW_OS_HAL_PWA_CALLER */
  Current->Os_Hal_PMR = Os_Hal_GetPMR();                                                                                /* SBSW_OS_HAL_PWA_CALLER */

  /* #20 If MemoryProtection is enabled, store MemoryProtection specific registers to current context. */
  if (Os_MpIsEnabled() != 0)
  {
    Current->Os_Hal_ASID  = Os_Hal_GetASID();                                                                           /* SBSW_OS_HAL_PWA_CALLER */
    Current->Os_Hal_MPLA0 = Os_Hal_GetMPLA0();                                                                          /* SBSW_OS_HAL_PWA_CALLER */
    Current->Os_Hal_MPUA0 = Os_Hal_GetMPUA0();                                                                          /* SBSW_OS_HAL_PWA_CALLER */
  }

  /* #30 Disable all interrupts. */
  Os_Hal_DisableGlobal();
  Os_Hal_DisableFE();

  /* #40 Restore common context registers from next context. */
  Os_Hal_SetLP(Next->Os_Hal_LP);
  Os_Hal_SetPMR(Next->Os_Hal_PMR);

  /* #50 Start or resume next thread. */
  Os_Hal_StartNextThread((const uint32*)Current, (const uint32*)Next);                                                  /* PRQA S 0306, 0310 */ /* MD_Os_Hal_0306, MD_Os_Hal_0310 */ /* SBSW_OS_HAL_FC_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_ContextCall()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(void, OS_CODE, OS_HAL_NOINLINE,
Os_Hal_ContextCall,
(
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Current,
  P2CONST(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Next
))
{
  /* #10 Store common context registers to current context. */
  Current->Os_Hal_PSW = Os_Hal_GetPSW();                                                                                /* SBSW_OS_HAL_PWA_CALLER */
  Current->Os_Hal_LP  = Os_Hal_GetLP();                                                                                 /* SBSW_OS_HAL_PWA_CALLER */
  Current->Os_Hal_PMR = Os_Hal_GetPMR();                                                                                /* SBSW_OS_HAL_PWA_CALLER */

  /* #20 If MemoryProtection is enabled, store MPU specific registers to current context and set new ASID. */
  if (Os_MpIsEnabled() != 0)
  {
    Current->Os_Hal_ASID  = Os_Hal_GetASID();                                                                           /* SBSW_OS_HAL_PWA_CALLER */
    Current->Os_Hal_MPLA0 = Os_Hal_GetMPLA0();                                                                          /* SBSW_OS_HAL_PWA_CALLER */
    Current->Os_Hal_MPUA0 = Os_Hal_GetMPUA0();                                                                          /* SBSW_OS_HAL_PWA_CALLER */
    Os_Hal_SetASID(Next->Os_Hal_ASID);
    Os_Hal_SyncPipeline();
  }

  /* #30 Disable EI and FE interrupts. */
  Os_Hal_DisableGlobal();
  Os_Hal_DisableFE();

  /* #40 Prepare registers and call ServiceFunction. */
  Os_Hal_SetLP(Next->Os_Hal_LP);
  Os_Hal_SetPMR(Next->Os_Hal_PMR);
  Os_Hal_CallFunc((uint32*)Current, (const uint32*)Next);                                                               /* PRQA S 0310, 0310 */ /* MD_Os_Hal_0310, MD_Os_Hal_0310 */ /* SBSW_OS_HAL_FC_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_ContextCallOnStack()
 **********************************************************************************************************************/
 /*!
  * Internal comment removed.
 *
 *
 *
 *
 *
  */
OS_FUNC_ATTRIBUTE_DEFINITION(void, OS_CODE, OS_HAL_NOINLINE,
Os_Hal_ContextCallOnStack,
(
  P2VAR(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Current,
  P2CONST(Os_Hal_ContextType, AUTOMATIC, OS_VAR_NOINIT) Next
))
{
  /* #10 Store common context registers to current context. */
  Current->Os_Hal_PSW = Os_Hal_GetPSW();                                                                                /* SBSW_OS_HAL_PWA_CALLER */
  Current->Os_Hal_LP    = Os_Hal_GetLP();                                                                               /* SBSW_OS_HAL_PWA_CALLER */
  Current->Os_Hal_PMR   = Os_Hal_GetPMR();                                                                              /* SBSW_OS_HAL_PWA_CALLER */

  /* #20 If MemoryProtection is enabled, store MPU specific registers to current context and set new ASID. */
  if (Os_MpIsEnabled() != 0)
  {
    Current->Os_Hal_ASID  = Os_Hal_GetASID();                                                                           /* SBSW_OS_HAL_PWA_CALLER */
    Current->Os_Hal_MPLA0 = Os_Hal_GetMPLA0();                                                                          /* SBSW_OS_HAL_PWA_CALLER */
    Current->Os_Hal_MPUA0 = Os_Hal_GetMPUA0();                                                                          /* SBSW_OS_HAL_PWA_CALLER */
  }

  /* #30 Disable EI and FE interrupts. */
  Os_Hal_DisableGlobal();
  Os_Hal_DisableFE();

  /* #40 Prepare registers and call ServiceFunction. */
  Os_Hal_SetLP(Next->Os_Hal_LP);
  Os_Hal_SetPMR(Next->Os_Hal_PMR);
  Os_Hal_CallFuncOnStack((uint32*)Current, (const uint32*)Next);                                                        /* PRQA S 0310, 0310 */ /* MD_Os_Hal_0310, MD_Os_Hal_0310 */ /* SBSW_OS_HAL_FC_CALLER */
}

#define OS_STOP_SEC_CODE
#include "Os_MemMap_OsCode.h"                                                                                           /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*!
 * \}
 */

/**********************************************************************************************************************
 *  END OF FILE: Os_Hal_Context.c
 *********************************************************************************************************************/
