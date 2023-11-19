/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2015 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  CryFord_Cfg.h
 *    Component:  SysService_AsrCryFord
 *       Module:  MICROSAR Cryptographic library module (Cry)
 *    Generator:  -
 *
 *  Description:  This file contains configuration data which is needed by the module implementation.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define CRYFORD_CFG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "CryFord_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/

# define CRYFORD_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Ford security access workspace */
VAR(CryFord_MacSecAccessWorkSpaceType, CRYFORD_VAR_NOINIT) CryFord_MacSecAccessWorkSpace;

# define CRYFORD_STOP_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define CRYFORD_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Ford security access configuration */
CONST(CryFord_MacSecAccessVerifyConfigType, CRYFORD_CONST) CryFord_MacSecAccessCfg =
{
  &CryFord_MacSecAccessWorkSpace, /**< Pointer to the workspace buffer */
  TRUE                            /**< Use synchronous job processing */
};

# define CRYFORD_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: CRYFORD_CFG.C
 *********************************************************************************************************************/
