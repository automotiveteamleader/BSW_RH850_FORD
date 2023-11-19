/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2016 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Cry_30_Rh850Icum_Rng.h
 *    Component:  DrvCry_Rh850Icum
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  This header file implements the PRNG CRY API for the ICUMB.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (CRY_30_RH850ICUM_RNG_H)
#define CRY_30_RH850ICUM_RNG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Csm_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CRY_30_RH850ICUM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern FUNC( void, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngInit( void );

extern FUNC( void, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedMainFunction( void );
extern FUNC( void, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngGenerateMainFunction( void );

extern FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedStart( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr );

extern FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedUpdate( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                               P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) seedPtr,
                                                               uint32 seedLength );

extern FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedFinish( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr );

extern FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngGenerate( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                             P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) resultPtr,
                                                             uint32 resultLength );

#define CRY_30_RH850ICUM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* CRY_30_RH850ICUM_RNG_H */
/**********************************************************************************************************************
 *  END OF FILE: CRY_30_RH850ICUM_RNG.H
 *********************************************************************************************************************/
