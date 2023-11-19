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
 *  \defgroup   Os_Hal_Os  HAL OS
 *  \{
 *
 *  \file       Os_Hal_OsInt.h
 *  \brief      HAL interfaces which are visible to the user.
 *  \details
 *  This file is included by Os.h. Therefore all symbols defined here are visible to the user.
 *
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Refer to Os_Hal_Os.h.
 **********************************************************************************************************************/

#if !defined (OS_HAL_OSINT_H)                                                                                           /* PRQA S 0883 */ /* MD_Os_Hal_0883 */
# define OS_HAL_OSINT_H

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/
/* AUTOSAR includes */
# include "Std_Types.h"

/* Os module declarations */
# include "Os_Hal_Os_Types.h"

/* Os kernel module dependencies */
# include "Os_Lcfg.h"

/* Os HAL dependencies */


/***********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 **********************************************************************************************************************/

/*! \brief         Abstraction of Cat0 and Cat1 ISR definition.
 *  \details       This macro is provided for user to define a Cat0 or Cat1 interrupt service routine.
 */
# if defined (OS_CFG_COMPILER_GREENHILLS)                                                                               /* PRQA S 0883 */ /* MD_Os_Hal_0883 */

/*! \brief    Provides function definition for category 0 ISRs.
 *  \details
 *  The kernel uses this macro to provide the platform independent OS_ISR0() interface.
 *
 *  \param[in]  IsrName   The function name which contains the user code of the category 0 ISR.
 */
# define OS_HAL_ISR0_DEFINE(IsrName)    __interrupt void IsrName(void)                                                  /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! \brief    Provides function definition for category 1 ISRs.
 *  \details
 *  The kernel uses this macro to provide the platform independent OS_ISR1() interface.
 *
 *  \param[in]  IsrName   The function name which contains the user code of the category 1 ISR.
 */
# define OS_HAL_ISR1_DEFINE(IsrName)    __interrupt void IsrName(void)                                                  /* PRQA S 3453 */ /* MD_MSR_19.7 */

# elif defined (OS_STATIC_CODE_ANALYSIS)

/*! \brief    Provides function definition for category 0 ISRs.
 *  \details
 *  The kernel uses this macro to provide the platform independent OS_ISR0() interface.
 *
 *  \param[in]  IsrName   The function name which contains the user code of the category 0 ISR.
 */
#  define OS_HAL_ISR0_DEFINE(IsrName)   void IsrName(void)                                                              /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! \brief    Provides function definition for category 1 ISRs.
 *  \details
 *  The kernel uses this macro to provide the platform independent OS_ISR1() interface.
 *
 *  \param[in]  IsrName   The function name which contains the user code of the category 1 ISR.
 */
#  define OS_HAL_ISR1_DEFINE(IsrName)   void IsrName(void)                                                              /* PRQA S 3453 */ /* MD_MSR_19.7 */

# endif

/***********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

/*! Set of hardware registers to be able to resume from an exception. */
struct Os_ExceptionContextType_Tag
{
  /*! Dummy attribute */
  uint32 Dummy;
};

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/


/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/


#endif /* OS_HAL_OSINT_H */

/*!
 * \}
 */

/***********************************************************************************************************************
 *  END OF FILE: Os_Hal_OsInt.h
 **********************************************************************************************************************/

