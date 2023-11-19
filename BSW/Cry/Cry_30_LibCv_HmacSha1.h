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
 *         File:  Cry_30_LibCv_HmacSha1.h
 *    Component:  SysService_AsrCry
 *       Module:  MICROSAR Cryptographic library module (Cry)
 *    Generator:  -
 *
 *  Description:  This header file implements the SHA-1 HMAC Cry API for the ASR CSM
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

#if !defined (CRY_30_LIBCV_HMACSHA1_H)
#define CRY_30_LIBCV_HMACSHA1_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Csm_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CRY_30_LIBCV_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern FUNC( void, CRY_30_LIBCV_CODE) Cry_30_LibCv_HmacSha1Init( void );
extern FUNC( void, CRY_30_LIBCV_CODE) Cry_30_LibCv_HmacSha1VerifyMainFunction( void );

extern FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_HmacSha1VerifyStart( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                   P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) keyPtr );

extern FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_HmacSha1VerifyUpdate( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                    P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) dataPtr,
                                                                                    uint32 dataLength );

extern FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_HmacSha1VerifyFinish( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                    P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) MacPtr,
                                                                                    uint32 MacLength,
                                                                                    P2VAR( Csm_VerifyResultType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr );

#define CRY_30_LIBCV_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif  /* CRY_30_LIBCV_HMACSHA1_H */
/**********************************************************************************************************************
 *  END OF FILE: CRY_30_LIBCV_HMACSHA1.H
 *********************************************************************************************************************/
