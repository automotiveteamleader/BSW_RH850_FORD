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
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Cry_30_LibCv_Fips186.h
 *    Component:  SysService_AsrCry
 *       Module:  MICROSAR Cryptographic library module (Cry)
 *    Generator:  -
 *
 *  Description:  This header file implements the FIPS 186-2 RNG Cry API for the ASR CSM
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#if !defined (CRY_30_LIBCV_FIPS186_H)
#define CRY_30_LIBCV_FIPS186_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Csm_Types.h"
#include "ESLib.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CRY_30_LIBCV_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern FUNC( void, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186Init( void );
extern FUNC( void, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186SeedMainFunction( void );
extern FUNC( void, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186GenerateMainFunction( void );

FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186SeedStart( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr );

FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186SeedUpdate( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr,
                                                                          P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) seedPtr,
                                                                          uint32 seedLength );

FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186SeedFinish( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr );

FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186Generate( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr,
                                                                        P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr,
                                                                        uint32 resultLength );

#define CRY_30_LIBCV_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* CRY_30_LIBCV_FIPS186_H */
/**********************************************************************************************************************
 *  END OF FILE: CRY_30_LIBCV_FIPS186.H
 *********************************************************************************************************************/
