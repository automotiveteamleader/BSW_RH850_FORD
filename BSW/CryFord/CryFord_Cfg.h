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
#if !defined (CRYFORD_CFG_H)
#define CRYFORD_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* If enabled, dummy statements are inserted for not used parameters */
#define CRYFORD_USE_DUMMY_STATEMENT     STD_ON

/* Enable CRYFORD services */
#define CRYFORD_MACSECACCESS_ENABLED    STD_ON


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Ford security access workspace buffer */
typedef struct
{
  uint8 workSpace[192];
} CryFord_MacSecAccessWorkSpaceType;

/* Ford security access configuration */
typedef struct
{
  P2VAR( CryFord_MacSecAccessWorkSpaceType, AUTOMATIC, CRYFORD_APPL_VAR ) buffer;
  boolean useSyncJobProcessing;
} CryFord_MacSecAccessVerifyConfigType;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define CRYFORD_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern CONST(CryFord_MacSecAccessVerifyConfigType, CRYFORD_CONST) CryFord_MacSecAccessCfg;

# define CRYFORD_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* CRYFORD_CFG_H */
/**********************************************************************************************************************
 *  END OF FILE: CRYFORD_CFG.H
 *********************************************************************************************************************/
