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
 *  \ingroup    Os_Hal
 *  \addtogroup Os_Hal_Timer_STM
 *
 *  \{
 *
 *  \file       Os_Hal_Timer_STM.h
 *  \brief
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined(OS_HAL_TIMER_STM_H)                                                                                        /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_TIMER_STM_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
# include "Os_Hal_Timer_STMInt.h"
# include "Os_Hal_Compiler.h"
# include "Os_Hal_Interrupt.h"
# include "Os_Hal_INTC.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

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
 *  Os_Hal_TimerFrtInit_STM()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_TimerFrtInit_STM,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
))                                                                                                                      /* COV_OS_HALTIMERSTMUNSUPPORTED_XX */
{
  Os_Hal_STMRefType TimerRef = (Os_Hal_STMRefType)(TimerConfig->TimerBaseAddr);                                         /* PRQA S 0303 */ /* MD_Os_Hal_0303 */

  /* #10 Initialize register FEINTFMSKn. */  
  *((Os_Hal_Reg32BitRefType)(osFEINTFMSKnBase[TimerConfig->TimerIndex])) |= osFEINTFMSK[TimerConfig->TimerChannel];     /* PRQA S 0303 */ /* MD_Os_Hal_0303 */ /* SBSW_OS_HAL_PWA_FEINTFMSKCONFIG */
  
  /* #20 Initialize timer unit STMn. */  
  TimerRef->osSTMnTT = (uint32)(1UL << TimerConfig->TimerChannel); /* stop timer channel */                             /* SBSW_OS_HAL_PWA_FRTCONFIG */
  TimerRef->osSTMnIS |= osINTSTMnConfig[TimerConfig->TimerChannel]; /* select interrupt mapping */                      /* SBSW_OS_HAL_PWA_FRTCONFIG */
  TimerRef->osSTMnCKSEL &= (uint32)~(1UL << TimerConfig->TimerChannel); /* select clock */                              /* SBSW_OS_HAL_PWA_FRTCONFIG */
  TimerRef->osSTMnCNT[TimerConfig->TimerChannel - 1].osSTMCNTx = (uint32)0x0UL; /* clear counter */                     /* SBSW_OS_HAL_PWA_FRTCONFIG */
  TimerRef->osSTMnCNT[TimerConfig->TimerChannel - 1].osSTMCMPxA = TimerConfig->CompareValue; /* set compare value A */  /* SBSW_OS_HAL_PWA_FRTCONFIG */
  TimerRef->osSTMnCNT[TimerConfig->TimerChannel - 1].osSTMCMPxB = TimerConfig->CompareValue; /* set compare value B */  /* SBSW_OS_HAL_PWA_FRTCONFIG */
  TimerRef->osSTMnSTC = (uint32)(1UL << (TimerConfig->TimerChannel * 4)); /* clear interrupt flag */                    /* SBSW_OS_HAL_PWA_FRTCONFIG */
  TimerRef->osSTMnTS = (uint32)(1UL << TimerConfig->TimerChannel); /* start timer channel */                            /* SBSW_OS_HAL_PWA_FRTCONFIG */
}

/***********************************************************************************************************************
 *  Os_Hal_GetCounterValue_STM()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE Os_Hal_TimerFrtTickType, OS_CODE, OS_ALWAYS_INLINE,                        /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_GetCounterValue_STM,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
))                                                                                                                      /* COV_OS_HALTIMERSTMUNSUPPORTED_XX */
{
  Os_Hal_STMRefType TimerRef = (Os_Hal_STMRefType)(TimerConfig->TimerBaseAddr);                                         /* PRQA S 0303 */ /* MD_Os_Hal_0303 */
  /* #10 Return the current compare value. */
  return TimerRef->osSTMnCNT[TimerConfig->TimerChannel-1].osSTMCNTx;                                                    /* PRQA S 0303 */ /* MD_Os_Hal_0303 */
}

/***********************************************************************************************************************
 *  Os_Hal_SetCompareValue_STM()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_SetCompareValue_STM,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig,
  Os_Hal_TimerFrtTickType ExpirationTime
))                                                                                                                      /* COV_OS_HALTIMERSTMUNSUPPORTED_XX */
{
  Os_Hal_STMRefType TimerRef = (Os_Hal_STMRefType)(TimerConfig->TimerBaseAddr);                                         /* PRQA S 0303 */ /* MD_Os_Hal_0303 */
  /* #10 Set the current compare value. */
  TimerRef->osSTMnCNT[TimerConfig->TimerChannel-1].osSTMCMPxA = ExpirationTime; /* set compare value A */               /* SBSW_OS_HAL_PWA_FRTCONFIG */
  TimerRef->osSTMnCNT[TimerConfig->TimerChannel-1].osSTMCMPxB = ExpirationTime; /* set compare value B */               /* SBSW_OS_HAL_PWA_FRTCONFIG */
}

/***********************************************************************************************************************
 *  Os_Hal_TimerAcknowledge_STM()
 **********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
OS_FUNC_ATTRIBUTE_DEFINITION(OS_LOCAL_INLINE void, OS_CODE, OS_ALWAYS_INLINE,                                           /* PRQA S 3219 */ /* MD_Os_Hal_3219 */
Os_Hal_TimerAcknowledge_STM,
(
  P2CONST(Os_Hal_TimerFrtConfigType, AUTOMATIC, OS_CONST) TimerConfig
))                                                                                                                      /* COV_OS_HALTIMERSTMUNSUPPORTED_XX */
{
  Os_Hal_STMRefType TimerRef = (Os_Hal_STMRefType)(TimerConfig->TimerBaseAddr);                                         /* PRQA S 0303 */ /* MD_Os_Hal_0303 */
  /* #10 Acknowledge the timer interrupt. */
  TimerRef->osSTMnSTC = (uint32)(3UL << (TimerConfig->TimerChannel * 4));                                               /* SBSW_OS_HAL_PWA_FRTCONFIG */
}

# define OS_STOP_SEC_CODE
# include "Os_MemMap_OsCode.h"                                                                                          /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* OS_HAL_TIMER_STM_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Timer_STM.h
 **********************************************************************************************************************/

