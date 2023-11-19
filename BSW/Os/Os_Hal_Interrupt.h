/***********************************************************************************************************************
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  --------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/**
 *  \addtogroup Os_Hal_Interrupt
 *  \{
 *
 *  \file       Os_Hal_Interrupt.h
 *  \brief
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined (OS_HAL_INTERRUPT_H)                                                                                       /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_INTERRUPT_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_InterruptInt.h"
# include "Os_Hal_Interrupt_Lcfg.h"

/* Os kernel module declarations */
# include "Os_Interrupt.h"
# include "Os_Cfg.h"
# include "Os_TimingProtection_Cfg.h"
# include "Os_Common.h"
# include "Os_TimingProtection.h"

/* Os HAL dependencies */
# include "Os_Hal_Interrupt_Cfg.h"
# include "Os_Hal_Compiler.h"
# include "Os_Hal_Core.h"
# include "Os_Hal_Derivative.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/*! Calculates the priority mask for the passed level. */
# define OS_HAL_LEVEL_MASK(Level)     ((uint32)(((uint32)OS_HAL_PMR_MASK) >> (Level)) << (Level))                       /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Priority mask to disable all timing protection, CAT1 and CAT2 interrupts. */
# define OS_HAL_DISABLE_TP_LEVEL      OS_HAL_LEVEL_MASK(OS_CFG_HAL_TP_DISABLE_LEVEL)
/*! Priority mask to disable all CAT1 and CAT2 interrupts. */
# define OS_HAL_DISABLE_CAT1_LEVEL    OS_HAL_LEVEL_MASK(OS_CFG_HAL_ISR1_DISABLE_LEVEL)
/*! Priority mask to disable all CAT2 interrupts. */
# define OS_HAL_DISABLE_CAT2_LEVEL    OS_HAL_LEVEL_MASK(OS_CFG_HAL_ISR2_DISABLE_LEVEL)

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

# define OS_START_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  Os_Hal_IntDisableAndReturnGlobalState()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_Hal_IntGlobalStateType, OS_CODE, OS_ALWAYS_INLINE,                      /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntDisableAndReturnGlobalState, (void))
{
  Os_Hal_IntGlobalStateType retState;

  /* #10 Get the masked global flag from PSW */
  retState = Os_Hal_GetIntState();

  /* #20 Disable global core interrupts */
  Os_Hal_DisableGlobal();

  return retState;
}

/***********************************************************************************************************************
 *  Os_Hal_IntSetGlobalState()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntSetGlobalState,
(
  P2CONST(Os_Hal_IntGlobalStateType, AUTOMATIC, OS_APPL_DATA) State
))
{
  Os_Hal_IntGlobalStateType psw;

  /* #10 get the current PSW */
  psw = (Os_Hal_IntGlobalStateType)Os_Hal_GetPSW();
  /* #20 clear the global flag */
  psw &= (Os_Hal_IntGlobalStateType)~OS_HAL_PSW_ID_MSK;
  /* #30 write the new wanted global flag */
  Os_Hal_SetPSW((uint32)(psw | (*State)));                                                                              /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
}

/***********************************************************************************************************************
 *  Os_Hal_IntGetLevel()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntGetLevel,
(
  P2VAR(Os_Hal_IntLevelType, AUTOMATIC, OS_APPL_DATA) Level
))
{
  *Level = Os_Hal_GetLevel();                                                                                           /* SBSW_OS_HAL_PWA_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_IntSetLevel()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntSetLevel,
(
  P2CONST(Os_Hal_IntLevelType, AUTOMATIC, OS_APPL_DATA) Level
))
{
  Os_Hal_SetLevel(*Level);                                                                                              /* PRQA S 3112 */ /* MD_Os_Hal_3112 */
}

/***********************************************************************************************************************
 *  Os_Hal_IntGetGlobalEnable()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntGetGlobalEnable,
(
  P2VAR(Os_Hal_IntGlobalStateType, AUTOMATIC, OS_APPL_DATA) State
))
{
  /* #10 Return global flag state to enable all interrupts. */
  *State = (Os_Hal_IntGlobalStateType)OS_HAL_INTERRUPT_GLOBAL_ENABLE_STATE;                                             /* PRQA S 3112 */ /* MD_Os_Hal_3112 */ /* SBSW_OS_HAL_PWA_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_IntGetCat2LockLevel()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntGetCat2LockLevel,
(
  P2VAR(Os_Hal_IntLevelType, AUTOMATIC, OS_APPL_DATA) Level
))
{
  /* #10 Return the interrupt lock level to disable all cat2 interrupts. */
  *Level = (Os_Hal_IntLevelType)OS_HAL_DISABLE_CAT2_LEVEL;                                                              /* SBSW_OS_HAL_PWA_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_IntGetCat1LockLevel()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntGetCat1LockLevel,
(
  P2VAR(Os_Hal_IntLevelType, AUTOMATIC, OS_APPL_DATA) Level
))
{
  /* #10 Return the interrupt lock level to disable all cat2 and cat1 interrupts. */
  *Level = (Os_Hal_IntLevelType)OS_HAL_DISABLE_CAT1_LEVEL;                                                              /* SBSW_OS_HAL_PWA_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_IntGetTPLockLevel()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntGetTPLockLevel,
(
  P2VAR(Os_Hal_IntLevelType, AUTOMATIC, OS_APPL_DATA) Level
))
{
  /* #10 Return the interrupt lock level to disable TP, cat1 and cat2 interrupts. */
  *Level = (Os_Hal_IntLevelType)OS_HAL_DISABLE_TP_LEVEL;                                                                /* SBSW_OS_HAL_PWA_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_IntGetTaskLevel()
 **********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntGetTaskLevel,
(
  P2VAR(Os_Hal_IntLevelType, AUTOMATIC, OS_APPL_DATA) Level
))
{
  /* #10 Return the interrupt lock level for tasks. */
  *Level = (Os_Hal_IntLevelType)OS_HAL_INTERRUPT_LOCK_LEVEL_TASK;                                                       /* SBSW_OS_HAL_PWA_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_IntGetInterruptState()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntGetInterruptState,
(
  P2VAR(Os_Hal_IntStateType, AUTOMATIC, OS_VAR_NOINIT) InterruptState
))
{
  /* #10 Fetch level and global interrupt state. */
  InterruptState->PSW = Os_Hal_GetIntState();                                                                           /* SBSW_OS_HAL_PWA_CALLER */
  InterruptState->PMR = Os_Hal_GetLevel();                                                                              /* SBSW_OS_HAL_PWA_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_IntDisableSource()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntDisableSource,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  /* #10 Disable the given source. */
  IsrConfig->EICnRef->EICnLo |= OS_HAL_INTC_INT_SET_MASK;                                                               /* SBSW_OS_HAL_PWA_PA_ISRCONFIG */

  /* #20 Ensure that the state is changed in hardware. */
  Os_Hal_SyncMemory();
}

/***********************************************************************************************************************
 *  Os_Hal_IntEnableSource()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntEnableSource,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  /* #10 Enable the given source. */
  IsrConfig->EICnRef->EICnLo &= OS_HAL_INTC_INT_CLR_MASK;                                                               /* SBSW_OS_HAL_PWA_PA_ISRCONFIG */

  /* #20 Ensure that the state is changed in hardware. */
  Os_Hal_SyncMemory();
}

/***********************************************************************************************************************
 *  Os_Hal_IntIsClearPendingSupported()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntIsClearPendingSupported,( void ))
{
  return !0;
}

/***********************************************************************************************************************
 *  Os_Hal_IntClearPending()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntClearPending,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  /* #10 Clear the pending flag of the given interrupt. */
  IsrConfig->EICnRef->EICnHi &= OS_HAL_INTC_INT_CLR_PEND;                                                               /* SBSW_OS_HAL_PWA_PA_ISRCONFIG */

  /* #20 Ensure that the state is changed in hardware. */
  Os_Hal_SyncMemory();
}

/***********************************************************************************************************************
 *  Os_Hal_IntIsInterruptSourceEnabled()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntIsInterruptSourceEnabled,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  return ((IsrConfig->EICnRef->EICnLo & OS_HAL_INTC_INT_SET_MASK) == 0x0);
}

/***********************************************************************************************************************
 *  Os_Hal_IntIsInterruptPending()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntIsInterruptPending,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  return ((IsrConfig->EICnRef->EICnHi & OS_HAL_INTC_INT_SET_PEND) != 0x0);
}

/***********************************************************************************************************************
 *  Os_Hal_IntEndOfInterrupt()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntEndOfInterrupt,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig
))
{
  OS_IGNORE_UNREF_PARAM(IsrConfig);                                                                                     /* PRQA S 3112 */ /* MD_Os_Hal_3112 */

  /* #10 Inform hardware about end of interrupt. */
  Os_Hal_EndOfInterrupt();
}

/***********************************************************************************************************************
 *  Os_Hal_IntIsrLevelIsLe()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType,                                                          /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
OS_CODE, OS_ALWAYS_INLINE, Os_Hal_IntIsrLevelIsLe,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) IsrConfig,
  P2CONST(Os_Hal_IntLevelType, AUTOMATIC, OS_CONST) Level
))
{
  return (Os_StdReturnType)(IsrConfig->IntMask <= (*Level));
}

/***********************************************************************************************************************
 *  Os_Hal_IntLevelIsGt()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE,                                                 /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
OS_ALWAYS_INLINE, Os_Hal_IntLevelIsGt,
(
  P2CONST(Os_Hal_IntLevelType, AUTOMATIC, OS_CONST) LevelX,
  P2CONST(Os_Hal_IntLevelType, AUTOMATIC, OS_CONST) LevelY
))
{
  return (Os_StdReturnType)((*LevelX) > (*LevelY));
}

/***********************************************************************************************************************
 *  Os_Hal_IntTrapRestore()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE,                                                             /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
OS_ALWAYS_INLINE, Os_Hal_IntTrapRestore,
(
  P2CONST(Os_Hal_IntTrapStateType, AUTOMATIC, OS_VAR_NOINIT) InterruptState
))
{
  Os_Hal_IntSetGlobalState(InterruptState);                                                                             /* SBSW_OS_HAL_FC_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_IntTrapUpdate()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE,                                                             /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
OS_ALWAYS_INLINE, Os_Hal_IntTrapUpdate,
(
  P2VAR(Os_Hal_IntTrapStateType, AUTOMATIC, OS_VAR_NOINIT) InterruptState
))
{
  *InterruptState = Os_Hal_GetIntState();                                                                               /* SBSW_OS_HAL_PWA_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_IntInterruptSourceInit()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE,                                                             /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
OS_ALWAYS_INLINE, Os_Hal_IntInterruptSourceInit,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_APPL_DATA) InterruptSource
))
{
  /* #10 Bind the interrupt to its core */
  Os_Hal_InitEIC(InterruptSource);                                                                                      /* SBSW_OS_HAL_FC_CALLER */

  /* #20 Initialize interrupt control register */
  Os_Hal_InitIBD(InterruptSource);                                                                                      /* SBSW_OS_HAL_FC_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_IntIsGlobal2LevelSwitchSupported()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_3219 */
Os_Hal_IntIsGlobal2LevelSwitchSupported, (void))
{
  return !0;
}

/***********************************************************************************************************************
 *  Os_Hal_InitEIC()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_InitEIC,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_CONST) IsrConfig
))
{
  /* #10 Initialize the error interrupt control register. */
  IsrConfig->EICnRef->EICnLo = (uint8)(IsrConfig->EICnRef->EICnLo & 0x80)                                               /* SBSW_OS_HAL_PWA_PA_ISRCONFIG */
                                    | OS_HAL_INTC_TABLE_MODE
                                    | ((uint8)IsrConfig->IntLevel);
}

/***********************************************************************************************************************
 *  Os_Hal_InitIBD()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_InitIBD,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_CONST) IsrConfig
))
{
  /* #10 Check whether the hardware has a bind register or not */
  if(OS_HAL_EIBD2_BASE != 0)
  {
    /* #20 Initialize the binding register. */
    IsrConfig->IBDnRef->IBDnReg = (uint32)(IsrConfig->CoreID << 16) | (IsrConfig->CoreID + 1);                          /* SBSW_OS_HAL_PWA_PA_ISRCONFIG */
  }
}

/***********************************************************************************************************************
 *  Os_Hal_IntSetRequest()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntSetRequest,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_CONST) IsrConfig
))
{
  /* #10 Request the given interrupt. */
  Os_Hal_IntDisableSource(IsrConfig);                                                                                   /* SBSW_OS_HAL_FC_CALLER */
  IsrConfig->EICnRef->EICnHi |= OS_HAL_INTC_REQUEST_FLAG;                                                               /* SBSW_OS_HAL_PWA_PA_ISRCONFIG */
  Os_Hal_IntEnableSource(IsrConfig);                                                                                    /* SBSW_OS_HAL_FC_CALLER */
}

/***********************************************************************************************************************
 *  Os_Hal_IntGetRequest()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE uint8, OS_CODE, OS_ALWAYS_INLINE,                                          /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_IntGetRequest,
(
  P2CONST(Os_Hal_IntIsrConfigType, AUTOMATIC, OS_CONST) IsrConfig
))                                                                                                                      /* COV_OS_HALPLATFORMPITUNSUPPORTED_XX */
{
  /* #10 The the request state from the hardware. */
  return (IsrConfig->EICnRef->EICnHi & OS_HAL_INTC_REQUEST_FLAG);
}

/***********************************************************************************************************************
 *  Os_Hal_IntIsPeripheralInterruptTriggerSupported()
 **********************************************************************************************************************/
 /*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_3219 */
Os_Hal_IntIsPeripheralInterruptTriggerSupported, (void))
{
  /* #10 Return !0 because the peripheral interrupts can be triggered. */
  return !0;
}

/***********************************************************************************************************************
 *  Os_Hal_IntIsLevelSupported()
 **********************************************************************************************************************/
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_StdReturnType, OS_CODE, OS_ALWAYS_INLINE,                               /* PRQA S 3219 */ /* MD_Os_3219 */
Os_Hal_IntIsLevelSupported, (void))
{
  return !0;
}

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* OS_HAL_INTERRUPT_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Interrupt.h
 **********************************************************************************************************************/

