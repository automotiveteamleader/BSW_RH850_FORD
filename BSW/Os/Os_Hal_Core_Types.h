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
 * \addtogroup  Os_Hal_Core
 * \{
 *
 * \file        Os_Hal_Core_Types.h
 * \brief       Core and multi-core related primitives.
 *
 * Internal comment removed.
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
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/
#if !defined(OS_HAL_CORE_TYPES_H)                                                                                       /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_CORE_TYPES_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */

/* Os kernel module dependencies */
# include "Os_Cfg.h"

/* Os HAL dependencies */
# include "Os_Hal_Interrupt_Types.h"
# include "Os_Hal_Context_Types.h"

/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/

/*! Defines whether the HAL provides a count leading zeros command (STD_ON) or not (STD_OFF). */
# define OS_HAL_COUNT_LEADING_ZEROS_HARDWARE     STD_ON

/*! The required address width to subscript the bits of a Os_Hal_CoreBitFieldType.
 * The value can be selected from the following table:
 * typeof(Os_Hal_BitFieldType)      | OS_HAL_INDEXBITWIDTH
 * :------------------------------: | :----------------------------
 * uint8                            | 3
 * uint16                           | 4
 * uint32                           | 5
 * uint64                           | 6
 */
# define OS_HAL_INDEXBITWIDTH       (5)

/*! Defines the stack fill pattern, which is used to initialize an empty stack. */
# define OS_HAL_STACK_FILL_PATTERN  ((Os_Hal_StackType)0xAAAAAAAAUL)

/*! Defines the value which is returned by \ref Os_Hal_SpinTryLock, if locking succeeded. */
# define OS_HAL_SPINLOCKSUCCEEDED   ((Os_Hal_SpinlockResultType)1)

/*! Defines the value of lock variable, when it is unlocked. */
# define OS_HAL_SPIN_UNLOCKED       ((Os_Hal_SpinlockType)0)

/*! Mask to set the table mode flag in the EI level interrupt control register.*/
# define OS_HAL_INTC_TABLE_MODE     ((uint8)0x40)
/*! Mask to set the request flag in the EI level interrupt control register.*/
# define OS_HAL_INTC_REQUEST_FLAG   ((uint8)0x10)
/*! Mask to set the interrupt processing disabled bit in the EI level interrupt control register.*/
# define OS_HAL_INTC_INT_SET_MASK   ((uint8)0x80)
/*! Mask to clear the interrupt processing disabled bit in the EI level interrupt control register.*/
# define OS_HAL_INTC_INT_CLR_MASK   ((uint8)0x7F)
/*! Mask to set the request flag in the EI level interrupt control register.*/
# define OS_HAL_INTC_INT_SET_PEND   (OS_HAL_INTC_REQUEST_FLAG)
/*! Mask to clear the request flag in the EI level interrupt control register.*/
# define OS_HAL_INTC_INT_CLR_PEND   ((uint8)0xEF)

/*! PSW Mask for ID flag - Disable EI interrupt handling. */
# define OS_HAL_PSW_ID_MSK   (0x00000020UL)

/*! PSW Mask for EP flag - Disable EE interrupt handling. */
# define OS_HAL_PSW_EP_MSK   (0x00000040UL)

/*! PSW Mask for NP flag - Disable FE interrupt handling. */
# define OS_HAL_PSW_NP_MSK   (0x00000080UL)

/*! Defines the value for register MPM which is used to disable the MPU. */
# define OS_HAL_MPU_DISABLE  ((uint32)0x00000000UL)
/*! Defines the value for register MPM which is used to enable the MPU. */
# define OS_HAL_MPU_ENABLE   ((uint32)0x00000003UL)
/*! Defines the value for register MPAT0 which is used to setup access rights of MPU region 0 . */
# define OS_HAL_MPU_MPAT0    ((uint32)0x000000DBUL)

/*! Defines the memory start address. */
# define OS_HAL_MEM_STARTADDR   ((uint32)0x00000000UL)
/*! Defines the memory end address. */
# define OS_HAL_MEM_ENDADDR     ((uint32)0xFFFFFFFFUL)

/*! Macro to access the high byte of INTIPIRn EI level interrupt register */
# define OS_HAL_XSIG_INTCTRL(addr)   (*((P2VAR(volatile uint8, AUTOMATIC, OS_VAR_NOINIT))(addr)))                       /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Macro to access the inter-processor interrupt control register IPIR_CHn */
# define OS_HAL_XSIG_TRIGGER(addr)   (*((P2VAR(volatile uint32, AUTOMATIC, OS_VAR_NOINIT))(addr)))                      /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*!
 * \brief Interrupt lock level for tasks.
 * \details The PMR register must be set to zero to enable all interrupts.
 *
 */
# define OS_HAL_INTERRUPT_LOCK_LEVEL_TASK     (0UL)

/*!
 * \briefs Global interrupt state to enable all interrupts.
 * \details The PSW ID flag must be cleared to enable all interrupts.
 */
# define OS_HAL_INTERRUPT_GLOBAL_ENABLE_STATE (0UL)

/*!
 * \briefs Global interrupt state to disable all interrupts.
 * \details The PSW ID flag must be set to disable all interrupts.
 */
# define OS_HAL_INTERRUPT_GLOBAL_DISABLE_STATE (OS_HAL_PSW_ID_MSK)

/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/
/*! Platform specific core data. */
typedef uint32 Os_Hal_CoreType;

/*! Data type which is used to perform efficient calculation of count leading zero bits. */
typedef uint32 Os_Hal_BitFieldType;

/*! Platform type of an 8 bit hardware register */
typedef uint8 Os_Hal_Reg8BitType;

/*! Platform type of a 16 bit hardware register */
typedef uint16 Os_Hal_Reg16BitType;

/*! Platform type of a 32 bit hardware register */
typedef uint32 Os_Hal_Reg32BitType;

/*! Pointer to a 8 bit hardware register */
typedef P2VAR(volatile Os_Hal_Reg8BitType, TYPEDEF, AUTOMATIC) Os_Hal_Reg8BitRefType;

/*! Pointer to a 16 bit hardware register */
typedef P2VAR(volatile Os_Hal_Reg16BitType, TYPEDEF, AUTOMATIC) Os_Hal_Reg16BitRefType;

/*! Pointer to a 32 bit hardware register */
typedef P2VAR(volatile Os_Hal_Reg32BitType, TYPEDEF, AUTOMATIC) Os_Hal_Reg32BitRefType;

/*! Defines the type of the stack array. */
typedef uint32 Os_Hal_StackType;

/*! Platform type of a spinlock */
typedef uint32 Os_Hal_SpinlockType;

/*! Platform type of a spinlock result */
typedef Os_Hal_SpinlockType Os_Hal_SpinlockResultType;

/*! Forward declaration of platform core configuration type. */
struct Os_Hal_CoreConfigType_Tag;
typedef struct Os_Hal_CoreConfigType_Tag Os_Hal_CoreConfigType;

/*! Forward declaration of platform specific dynamic system information type. */
struct Os_Hal_Core2ThreadType_Tag;
typedef struct Os_Hal_Core2ThreadType_Tag Os_Hal_Core2ThreadType;

/*! Forward declaration of platform specific system information configuration type. */
struct Os_Hal_Core2ThreadConfigType_Tag;
typedef struct Os_Hal_Core2ThreadConfigType_Tag Os_Hal_Core2ThreadConfigType;

/*! Forward declaration of a platform specific AUTOSAR core configuration type.*/
struct Os_Hal_CoreAsrConfigType_Tag;
typedef struct Os_Hal_CoreAsrConfigType_Tag Os_Hal_CoreAsrConfigType;

/*! Forward declaration of a platform specific system information configuration type. */
struct Os_Hal_SystemConfigType_Tag;
typedef struct Os_Hal_SystemConfigType_Tag Os_Hal_SystemConfigType;

/*! Forward declaration of a platform specific XSignal interrupt configuration type. */
struct Os_Hal_XSigInterruptConfigType_Tag;
typedef struct Os_Hal_XSigInterruptConfigType_Tag Os_Hal_XSigInterruptConfigType;

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

#endif /* OS_HAL_CORE_TYPES_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_Core_Types.h
 **********************************************************************************************************************/

