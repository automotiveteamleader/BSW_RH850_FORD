/*
 *****************************************************************************
 *
 * copyright: (c) 2008 cv cryptovision GmbH, all rights reserved
 *
 * product:   cv act library/ES
 *
 * license:   The conditions for the use of this software are regulated
 *            in the
 *            Software License Agreement for Evaluation of the
 *            Performance Estimation Tool for the cv act library/ES
 *            The License Agreement should be included in this delivery,
 *            if the License Agreement is not included please request it from
 *            our WebSite: http://www.cryptovision.com/
 *
 *****************************************************************************
 *
 * Author: alf, cv cryptovision GmbH, 10/01/04
 *
 * $LastChangedBy: mneuhaus $
 * $LastChangedDate: 2016-12-16 08:10:42 +0100 (Fr, 16 Dez 2016) $
 * $LastChangedRevision: 2374 $
 * $URL: https://subversion/svn/library-ES/branches/library-es/1.2.0-VectorInformatik/development/common/lib_es/include/ESLib.h $
 *
 *****************************************************************************
 */

/*******************************************************************************
 **
 **     Part of the embedded systems library cv_Act_Library/ES
 **
 **     Layer: API
 **
 *******************************************************************************/

/*******************************************************************************
 **
 ** This file contains: The interface for the standard set of functions.
 **
 **
 **
 ** constants:
 **
 ** types:
 **
 ** macros:
 **
 ** functions:
 **
 *******************************************************************************/

#ifndef __ESLib_H__
#define __ESLib_H__ 1

#include "ESLib_t.h"
#include "ESLib_ERC.h"
#include "ESLib_RNG.h"
#include "ESLib_V1.1_compatibility.h"

#ifdef  __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Library version
 *****************************************************************************/

CRYPTOCV_CONST( extern, char ) ESLib_Version[];
CRYPTOCV_CONST( extern, eslt_Version ) ESLib_Params[];

#ifndef  NULL
   #define  NULL  ((void *) 0)
#endif

/*****************************************************************************
 * Library initialisation function
 * (must be called before any use of the library)
 *****************************************************************************/
extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initESCryptoLib( void ); /* sets LibStatus to some default value
                                also initalizes Lib internal vars if needed
                                on some controlers this function initializes
                                the library for multithreading features */

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID */

/*****************************************************************************
 * Workspace initialisation function
 *****************************************************************************/
extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initWorkSpaceHeader(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHeader ) workSpaceHeader, const eslt_Length workSpaceSize,
   CRYPTOCV_P2FUNC( CRYPTOCV_NONE, void, watchdog )( void ) );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID */

/*****************************************************************************
 * This part describes the cryto-functions inside the lib/es.
 * This Version includes:   FIPS186 (PRNG functions)
 *                          AES128 (single block / multi block modes)
 *                          AES GCM, (AES with Galois/Counter Mode authentication)
 *                          GMAC, (Galois MAC)
 *                          SHA1, (Secure-Hash-Algorithm-1 (160 bit))
 *                          RIPEMD160, (Hash-Algorithm, 160 bit)
 *                          MD5, (Hash-Algorithm, 128 bit)
 *                          SHA224, SHA256, (Secure-Hash-Algorithm 2 (224 / 256 bit))
 *                          SHA384, SHA512, (Secure-Hash-Algorithm 2 (384 / 512 bit))
 *                          HMAC-SHA1, (HMAC-SHA1 according to )
 *                          KDF (key derivation function according to ...)
 *                          EcP (elliptic curve operations on GfP)
 *                          RSA (PKCS#1 primitives and Ver.1.5)
 *                          CMAC-AES128 (CMAC-AES128 according to RFC4493)
 *                          EdDSA (EdDSA signatures over Curve25519)
 *                          EC-D/H (key agreement Curve25519)
 *****************************************************************************/
extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initTriggerFct(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHeader ) workSpaceHeader, CRYPTOCV_P2FUNC( CRYPTOCV_NONE, void, watchdog )( void ) );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

/*****************************************************************************
 * FIPS186 functions for a random number generator
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initFIPS186(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceFIPS186 ) workSpace,
   const eslt_Length entropyLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) entropy,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) savedState );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_ES_TOO_SMALL
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_RNG_ENTROPY_TOO_SMALL */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_getBytesFIPS186(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceFIPS186 ) workSpace,
   const eslt_Length targetLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) target );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_ES_TOO_SMALL
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_RNG_BAD_INTERNAL_STATE */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_stirFIPS186(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceFIPS186 ) workSpace,
   const eslt_Length inputLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_ES_TOO_SMALL
      ESL_ERC_PARAMETER_INVALID */

/*****************************************************************************
 * AES functions supporting different modes
 *****************************************************************************/

/* =============================================================================
 * = AES functions for multi and single mode (key generation) (128, 192, 256 bit)
 * ============================================================================= */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateKeyAES128( CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );
extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateKeyAES192( CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );
extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateKeyAES256( CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );
/* Assumes:
      esl_initRNG(...); has been called
   CallBacks:
      esl_getBytesRNG(...); cfg. ESLib_RNG.h
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_ES_TOO_SMALL
      ESL_ERC_PARAMETER_INVALID
      and all possible error codes which can occur in esl_getBytesRNG */

/* =============================================================================
 * = AES multi block crypto functions (128, 192, 256 bit)
 * ============================================================================= */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptAES128(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES128 ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,
   const eslt_BlockMode blockMode, const eslt_PaddingMode paddingMode,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) initializationVector );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptAES192(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES192 ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,
   const eslt_BlockMode blockMode, const eslt_PaddingMode paddingMode,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) initializationVector );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptAES256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES256 ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,
   const eslt_BlockMode blockMode, const eslt_PaddingMode paddingMode,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) initializationVector );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_MODE_INCOMPATIBLE
      ESL_ERC_MODE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptAES128(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES128 ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptAES192(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES192 ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptAES256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES256 ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeEncryptAES128(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES128 ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length )outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeEncryptAES192(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES192 ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length )outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeEncryptAES256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES256 ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length )outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptAES128(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES128 ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,
   const eslt_BlockMode blockMode, const eslt_PaddingMode paddingMode,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) initializationVector );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptAES192(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES192 ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,
   const eslt_BlockMode blockMode, const eslt_PaddingMode paddingMode,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) initializationVector );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptAES256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES256 ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,
   const eslt_BlockMode blockMode, const eslt_PaddingMode paddingMode,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) initializationVector );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_MODE_INCOMPATIBLE
      ESL_ERC_MODE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptAES128(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES128 ) workSpace,
   const  eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptAES192(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES192 ) workSpace,
   const  eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptAES256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES256 ) workSpace,
   const  eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeDecryptAES128(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES128 ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeDecryptAES192(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES192 ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeDecryptAES256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES256 ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT
      ESL_ERC_AES_PADDING_INVALID */

/* =============================================================================
 * = AES128 single block crypto functions (other key length on request)
 * ============================================================================= */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptAES128Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES128Block ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptAES192Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES192Block ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptAES256Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES256Block ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptAES128Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES128Block ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) inputBlock, CRYPTOCV_P2VAR_PARA( eslt_Byte ) outputBlock );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptAES192Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES192Block ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) inputBlock, CRYPTOCV_P2VAR_PARA( eslt_Byte ) outputBlock );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptAES256Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES256Block ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) inputBlock, CRYPTOCV_P2VAR_PARA( eslt_Byte ) outputBlock );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptAES128Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES128Block ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptAES192Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES192Block ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptAES256Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES256Block ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptAES128Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES128Block ) workSpace,
CRYPTOCV_P2CONST_PARA( eslt_Byte ) inputBlock, CRYPTOCV_P2VAR_PARA( eslt_Byte ) outputBlock );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptAES192Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES192Block ) workSpace,
CRYPTOCV_P2CONST_PARA( eslt_Byte ) inputBlock, CRYPTOCV_P2VAR_PARA( eslt_Byte ) outputBlock );

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptAES256Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceAES256Block ) workSpace,
CRYPTOCV_P2CONST_PARA( eslt_Byte ) inputBlock, CRYPTOCV_P2VAR_PARA( eslt_Byte ) outputBlock );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

/*****************************************************************************
 * DES functions supporting different modes
 *****************************************************************************/

/* =============================================================================
 * = DES functions for multi and single mode (key generation)
 * ============================================================================= */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateKeyDES( CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );

/* Assumes:
      esl_initRNG(...); has been called
   CallBacks:
      esl_getBytesRNG(...); cfg. ESLib_RNG.h
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_ES_TOO_SMALL
      ESL_ERC_PARAMETER_INVALID
      and all possible error codes which can occur in esl_getBytesRNG */

/* =============================================================================
 * = DES multi block crypto functions
 * ============================================================================= */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptDES(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceDES ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,
   const eslt_BlockMode blockMode, const eslt_PaddingMode paddingMode,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) initializationVector );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_MODE_INCOMPATIBLE
      ESL_ERC_MODE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptDES(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceDES ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeEncryptDES(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceDES ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length )outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptDES(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceDES ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,
   const eslt_BlockMode blockMode, const eslt_PaddingMode paddingMode,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) initializationVector );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_MODE_INCOMPATIBLE
      ESL_ERC_MODE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptDES(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceDES ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeDecryptDES(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceDES ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length )outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT
      ESL_ERC_AES_PADDING_INVALID */

/* =============================================================================
 * = DES single block crypto functions (other key length on request)
 * ============================================================================= */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptDESBlock(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceDESBlock ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptDESBlock(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceDESBlock ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) inputBlock, CRYPTOCV_P2VAR_PARA( eslt_Byte ) outputBlock );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptDESBlock(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceDESBlock ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptDESBlock(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceDESBlock ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) inputBlock, CRYPTOCV_P2VAR_PARA( eslt_Byte ) outputBlock );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

/*****************************************************************************
 * TDES functions supporting different modes
 *****************************************************************************/

/* =============================================================================
 * = TDES functions for multi and single mode (key generation)
 * ============================================================================= */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateKey3TDES( CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );
/* Assumes:
      ESL_initRNG(...); has been called
   CallBacks:
      ESL_getBytesRNG(...); cfg. ESLib_RNG.h
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_ES_TOO_SMALL
      ESL_ERC_PARAMETER_INVALID
      and all possible error codes which can occur in esl_getBytesRNG */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateKey2TDES( CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );
/* Assumes:
      ESL_initRNG(...); has been called
   CallBacks:
      ESL_getBytesRNG(...); cfg. ESLib_RNG.h
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_ES_TOO_SMALL
      ESL_ERC_PARAMETER_INVALID
      and all possible error codes which can occur in esl_getBytesRNG */

/* =============================================================================
 * = TDES multi block crypto functions
 * ============================================================================= */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptTDES(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceTDES ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) key, const eslt_Byte key_len,
   const eslt_BlockMode blockMode, const eslt_PaddingMode paddingMode,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) initializationVector );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_MODE_INCOMPATIBLE
      ESL_ERC_MODE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptTDES(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceTDES ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeEncryptTDES(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceTDES ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length )outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptTDES(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceTDES ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) key, const eslt_Byte key_len,
   const eslt_BlockMode blockMode, const eslt_PaddingMode paddingMode,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) initializationVector );
/* ErrorCode:
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_MODE_INVALID
      ESL_ERC_TDES_KEY_LENGTH_INVALID
      ESL_ERC_NO_ERROR */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptTDES(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceTDES ) workSpace,
   const  eslt_Length inputSize,  CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   CRYPTOCV_P2VAR_PARA( eslt_Length )outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeDecryptTDES(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceTDES ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length )outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT
      ESL_ERC_AES_PADDING_INVALID */

/* =============================================================================
 * = TDES single block crypto functions (other key length on request)
 * ============================================================================= */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptTDESBlock(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceTDESBlock ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) key, const eslt_Byte key_len );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptTDESBlock(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceTDESBlock ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) inputBlock, CRYPTOCV_P2VAR_PARA( eslt_Byte ) outputBlock );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptTDESBlock(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceTDESBlock ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) key, const eslt_Byte key_len );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_TDES_KEY_LENGTH_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptTDESBlock(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceTDESBlock ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) inputBlock, CRYPTOCV_P2VAR_PARA( eslt_Byte ) outputBlock );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

/*****************************************************************************
 * RC2 functions supporting different modes
 *****************************************************************************/

/* =============================================================================
 * = RC2 functions for multi and single mode (key generation)
 * ============================================================================= */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateKeyRC2( CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );

/* Assumes:
      ESL_initRNG(...); has been called
   CallBacks:
      ESL_getBytesRNG(...); cfg. ESLib_RNG.h
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_ES_TOO_SMALL
      ESL_ERC_PARAMETER_INVALID
      and all possible error codes which can occur in esl_getBytesRNG */

/* =============================================================================
 * = RC2 multi block crypto functions
 * ============================================================================= */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptRC2(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRC2 ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) key, const eslt_Length key_len, const eslt_Length eff_key_len,
   const eslt_BlockMode blockMode, const eslt_PaddingMode paddingMode,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) initializationVector );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_MODE_INCOMPATIBLE
      ESL_ERC_MODE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptRC2(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRC2 ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeEncryptRC2(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRC2 ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptRC2(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRC2 ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) key, const eslt_Length key_len, const eslt_Length eff_key_len,
   const eslt_BlockMode blockMode, const eslt_PaddingMode paddingMode,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) initializationVector );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_MODE_INCOMPATIBLE
      ESL_ERC_MODE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptRC2(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRC2 ) workSpace,
   const  eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeDecryptRC2(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRC2 ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) outputSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) output );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT
      ESL_ERC_AES_PADDING_INVALID */

/* =============================================================================
 * = RC2 single block crypto functions (other key length on request)
 * ============================================================================= */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptRC2Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRC2Block ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,  const eslt_Length key_len,  const eslt_Length eff_key_len );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptRC2Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRC2Block ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) inputBlock,  CRYPTOCV_P2VAR_PARA( eslt_Byte ) outputBlock );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptRC2Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRC2Block ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,  const eslt_Length key_len,  const eslt_Length eff_key_len );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptRC2Block(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRC2Block ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) inputBlock, CRYPTOCV_P2VAR_PARA( eslt_Byte ) outputBlock );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT
      ESL_ERC_MEMORY_CONFLICT */

/*****************************************************************************
 * GMAC functions
 *****************************************************************************/
extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initGMAC (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceGMAC ) workSpace,
   const eslt_Length keyLength,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,
   const eslt_Length ivLength,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) iv );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_GCM_INVALID_KEY_LENGTH */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateGMAC (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceGMAC ) workSpace,
   const eslt_Length inputLength,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_GCM_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeGMAC (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceGMAC ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) tag );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL */

extern CRYPTOCV_FUNC(eslt_ErrorCode) esl_verifyGMAC(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceGMAC) workSpace,
   CRYPTOCV_P2CONST_PARA(eslt_Byte) tag);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_GCM_TAG_VERIFICATION_FAILED
*/

/*****************************************************************************
 * GCM functions
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptGCM (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceGCM ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,
   const eslt_Length keyLength,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) iv,
   const eslt_Length ivLength );
extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptGCM (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceGCM ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) key,
   const eslt_Length keyLength,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) iv,
   const eslt_Length ivLength );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_GCM_INVALID_KEY_LENGTH */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateAuthDataEncryptGCM (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceGCM ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   const eslt_Length inputLength );
extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateAuthDataDecryptGCM (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceGCM ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   const eslt_Length inputLength );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_GCM_TOTAL_LENGTH_OVERFLOW
      ESL_ERC_GCM_STATE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updatePlaintextEncryptGCM (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceGCM ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   const eslt_Length inputLength,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) output,
   CRYPTOCV_P2VAR_PARA( eslt_Size32 ) bytes_out );
extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateCiphertextDecryptGCM (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceGCM ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) input,
   const eslt_Length inputLength,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) output,
   CRYPTOCV_P2VAR_PARA( eslt_Size32 ) bytes_out );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_GCM_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeEncryptGCM (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceGCM ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) output,
   CRYPTOCV_P2VAR_PARA( eslt_Size32 ) bytes_out,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) tag );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeDecryptGCM (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceGCM ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) output,
   CRYPTOCV_P2VAR_PARA( eslt_Size32 ) bytes_out,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) tag );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_GCM_TAG_VERIFICATION_FAILED */

/*****************************************************************************
 * SHA-1 hash functions
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSHA1( CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSHA1 ) workSpace );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initChainingVariablesSHA1(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSHA1 ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) CV, CRYPTOCV_P2CONST_PARA( eslt_Byte ) bitLen);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSHA1(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSHA1 ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSHA1(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSHA1 ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

/******************************************************************************
 * SHA-256 hash functions                                                     *
 ******************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSHA256( CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSHA256 ) workSpace );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initChainingVariablesSHA256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSHA256 ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) CV, CRYPTOCV_P2CONST_PARA( eslt_Byte ) bitLen);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSHA256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSHA256 ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSHA256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSHA256 ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

/******************************************************************************
 * SHA-512 hash functions
 ******************************************************************************/

extern CRYPTOCV_FUNC(eslt_ErrorCode) esl_initSHA512(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceSHA512) workSpace);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC(eslt_ErrorCode) esl_updateSHA512(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceSHA512) workSpace,
   const eslt_Length inputSize,
   CRYPTOCV_P2CONST_PARA(eslt_Byte) input);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC(eslt_ErrorCode) esl_finalizeSHA512(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceSHA512) workSpace,
   CRYPTOCV_P2VAR_PARA(eslt_Byte) messageDigest);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

/*****************************************************************************
 * RIPEMD-160 hash functions
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initRIPEMD160( CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRIPEMD160 ) workSpace );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initChainingVariablesRIPEMD160(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRIPEMD160 ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) CV, CRYPTOCV_P2CONST_PARA( eslt_Byte ) bitLen);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateRIPEMD160(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRIPEMD160 ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeRIPEMD160(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRIPEMD160 ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

/*****************************************************************************
 * MD5 hash functions
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initMD5( CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceMD5 ) workSpace );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initChainingVariablesMD5(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceMD5 ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) CV, CRYPTOCV_P2CONST_PARA( eslt_Byte ) bitLen);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateMD5(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceMD5 ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeMD5(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceMD5 ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

/*****************************************************************************
 * HashMACSHA-1 crypto functions (according to RFC 2104 with SHA-1)
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateKeyHashMACSHA1(
   const eslt_Length keyLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_ES_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      and all possible error codes which can occur in esl_getBytesRNG */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initHashMACSHA1(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHMACSHA1 ) workSpace,
   const eslt_Length keyLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HMAC_KEY_LENGTH_OUT_OF_RANGE */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateHashMACSHA1(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHMACSHA1 ) workSpace,
   const eslt_Length inputLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashMACSHA1(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHMACSHA1 ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageHashMAC );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifyHashMACSHA1(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHMACSHA1 ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageHashMAC );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HMAC_INCORRECT_MAC */

/*****************************************************************************
 * HashMACRIPEMD160 crypto functions (according to RFC 2104 with RIPEMD-160)
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateKeyHashMACRIPEMD160(
   const eslt_Length keyLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_ES_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      and all possible error codes which can occur in esl_getBytesRNG */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initHashMACRIPEMD160(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHMACRIPEMD160 ) workSpace,
  const eslt_Length keyLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HMAC_KEY_LENGTH_OUT_OF_RANGE */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateHashMACRIPEMD160(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHMACRIPEMD160 ) workSpace,
    const eslt_Length inputLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashMACRIPEMD160(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHMACRIPEMD160 ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageHashMAC );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifyHashMACRIPEMD160(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHMACRIPEMD160 ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageHashMAC );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HMAC_INCORRECT_MAC */

/*****************************************************************************
 * HashMACSHA256 crypto functions (according to RFC 2104 with SHA-256)
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateKeyHashMACSHA256(
   const eslt_Length keyLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_ES_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      and all possible error codes which can occur in esl_getBytesRNG */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initHashMACSHA256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHMACSHA256 ) workSpace,
   const eslt_Length keyLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HMAC_KEY_LENGTH_OUT_OF_RANGE */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateHashMACSHA256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHMACSHA256 ) workSpace,
 const eslt_Length inputLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashMACSHA256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHMACSHA256 ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageHashMAC );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifyHashMACSHA256(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceHMACSHA256 ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageHashMAC );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HMAC_INCORRECT_MAC */

CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initCMACAES128(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceCMACAES ) workSpace,
   const eslt_Length keyLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HMAC_KEY_LENGTH_OUT_OF_RANGE */

CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateCMACAES128(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceCMACAES ) workSpace,
   const eslt_Length inputLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeCMACAES128(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceCMACAES ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageCMAC );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifyCMACAES128(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceCMACAES ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageCMAC );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HMAC_INCORRECT_MAC */

CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSipHash(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSipHash ) workSpace,
   const eslt_Length keyLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HMAC_KEY_LENGTH_OUT_OF_RANGE */

CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSipHash(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSipHash ) workSpace,
   const eslt_Length inputLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSipHash(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSipHash ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageMAC );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySipHash(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSipHash ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageMAC );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HMAC_INCORRECT_MAC */

/*****************************************************************************
 * Key derivation function (KDF) according to ANSI X9.63
 *****************************************************************************/

CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initKDFX963SHA1( CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceKDFX963SHA1 ) workSpace );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

CRYPTOCV_FUNC( eslt_ErrorCode ) esl_deriveKeyKDFX963SHA1(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceKDFX963SHA1 ) workSpace,
   const eslt_Length secretLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) secret,
   const eslt_Length infoLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) info,
   const eslt_Length keyLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

/*****************************************************************************
 * Crypto functions KEY-derive according to PKCS#5 v2.0
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initKDF2HMACSHA1(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceKDF2HMACSHA1 ) workSpace, const eslt_Length iterationCount);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_KDF_ITERATION_COUNT_OUT_OF_RANGE */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_deriveKeyKDF2HMACSHA1(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceKDF2HMACSHA1 ) workSpace,
   const eslt_Length secretLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) secret,
   const eslt_Length infoLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) info,
   const eslt_Length keyLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID */

/*****************************************************************************
 * Crypto functions ECP (Ecc over Gf(p))
 *****************************************************************************/

/* =============================================================================
 * = LengthOf-Functions
 * =============================================================================
 * = They can compute the bytelength of the i-n and outputparameters of EcP
 * = functions */

extern CRYPTOCV_FUNC( eslt_Length ) esl_getMaxLengthOfEcPmessage( CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomain ) domain );
extern CRYPTOCV_FUNC( eslt_Length ) esl_getLengthOfEcPpublicKey_comp( CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomain ) domain );
extern CRYPTOCV_FUNC( eslt_Length ) esl_getLengthOfEcPprivateKey( CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomain ) domain );
extern CRYPTOCV_FUNC( eslt_Length ) esl_getLengthOfEcPsignature_comp( CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomain ) domain );
extern CRYPTOCV_FUNC( eslt_Length ) esl_getLengthOfEcPsecret_comp( CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomain ) domain );

/* =============================================================================
 * = Initialisation-Functions
 * =============================================================================
 * =
 * = They initialize the EcPWorkspace for usage in a special primitive.
 * = As different primitives use different alorithms each one needs some other
 * = initialisation details.
 * = The signature and the keygeneration need some additional information, as
 * = that increases speed. */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initGenerateKeyEcP_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceEcP ) workSpace, CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomain ) domain,
   CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomainExt ) domainExt, CRYPTOCV_P2ROMCONST_PARA( eslt_EccSpeedUpExt ) speedUpExt );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems
      ESL_ERC_ECC_DOMAIN_INVALID - points not on curve and such
      ESL_ERC_ECC_DOMAINEXT_INVALID - points not on curve and such
      ESL_ERC_ECC_SPEEDUPEXT_INVALID - points not on curve and such */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignDSAEcP_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceEcP ) workSpace, CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomain ) domain,
   CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomainExt ) domainExt, CRYPTOCV_P2ROMCONST_PARA( eslt_EccSpeedUpExt ) speedUpExt );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems
      ESL_ERC_ECC_DOMAIN_INVALID - points not on curve and such
      ESL_ERC_ECC_DOMAINEXT_INVALID - points not on curve and such
      ESL_ERC_ECC_SPEEDUPEXT_INVALID - points not on curve and such */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initVerifyDSAEcP_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceEcP ) workSpace,
   CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomain ) domain, CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomainExt ) domainExt );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems
      ESL_ERC_ECC_DOMAIN_INVALID - points not on curve and such
      ESL_ERC_ECC_DOMAINEXT_INVALID - points not on curve and such */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initGenerateSharedSecretDHEcP_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceEcP ) workSpace,
   CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomain ) domain, CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomainExt ) domainExt );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems
      ESL_ERC_ECC_DOMAIN_INVALID - points not on curve and such
      ESL_ERC_ECC_DOMAINEXT_INVALID - points not on curve and such */

/* =============================================================================
 * = EcP primitives
 * =============================================================================
 * =
 * = Each of these functions executes one crypto primitive.
 * = In- and outputs are simple byte-arrays (octet strings) in big endian format,
 * = that can be easily used to buil up structures that conform to most
 * = standards.
 * = (cfg. X.680 and X.690 - ASN.1-BER and other standards refering these)
 * = The functions do not add tags and length information to all in- and output,
 * = as that would produce much overhead. On many embedded systems this would be
 * = not appreciated.
 * = All funtions assume, that all memory areas do not overlap, though some
 * = functions allow some pointers to be equal under special assumptions. */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateKeyEcP_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceEcP ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) privateKey,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) publicKey_x, CRYPTOCV_P2VAR_PARA( eslt_Byte ) publicKey_y);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems
      ESL_ERC_ECC_PUBKEY_INVALID
      and all possible error codes which can occur in esl_getBytesRNG */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_signDSAEcP_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceEcP ) workSpace,
   eslt_Length messageLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) message, CRYPTOCV_P2CONST_PARA( eslt_Byte ) privateKey,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signature_rLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature_r,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signature_sLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature_s );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems
      ESL_ERC_ECC_PRIVKEY_INVALID
      ESL_ERC_ECC_MESSAGE_TOO_LONG
      and all possible error codes which can occur in esl_getBytesRNG */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifyDSAEcP_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceEcP ) workSpace,
   eslt_Length messageLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) message,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) publicKey_x, CRYPTOCV_P2CONST_PARA( eslt_Byte ) publicKey_y,
   eslt_Length signature_rLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature_r,
   eslt_Length signature_sLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature_s );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems
      ESL_ERC_ECC_PUBKEY_INVALID
      ESL_ERC_ECC_MESSAGE_TOO_LONG
      ESL_ERC_ECC_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateSharedSecretDHEcP_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceEcP ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) privateKey,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) publicKey_x, CRYPTOCV_P2CONST_PARA( eslt_Byte ) publicKey_y,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) secret_x, CRYPTOCV_P2VAR_PARA( eslt_Byte ) secret_y );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems
      ESL_ERC_ECC_PUBKEY_INVALID
      ESL_ERC_ECC_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initExchangeKeyDHEcP_key(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceEcP ) workSpace,
   CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomain ) domain, CRYPTOCV_P2ROMCONST_PARA( eslt_EccDomainExt ) domainExt );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems
      ESL_ERC_ECC_DOMAIN_INVALID - points not on curve and such
      ESL_ERC_ECC_DOMAINEXT_INVALID - points not on curve and such */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_exchangeKeyDHEcP_key(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceEcP ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) privateKey,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) publicKey_x, CRYPTOCV_P2CONST_PARA( eslt_Byte ) publicKey_y,
   eslt_Length infoLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) info, eslt_Length iterationCount,
   eslt_Length keyLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) key );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems
      ESL_ERC_ECC_PUBKEY_INVALID
      ESL_ERC_ECC_PRIVKEY_INVALID */

/*****************************************************************************
 * Crypto functions RSA
 * according to PKCS#1 2.1
 * according to PKCS#1 primitives RSAEP, RSADP, RSASP1, RSAVP1
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptRSA_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAdec_prim ) workSpace,
    eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
    eslt_Length privateKeyExponentSize, eslt_pRomByte privateKeyExponent );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptRSA_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAdec_prim ) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) cipher,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) messageSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) message );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_CODE_OUT_OF_RANGE
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

/********/
extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptRSACRT_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTdec_prim ) workSpace,
   eslt_Length   keyPairPrimePSize, eslt_pRomByte keyPairPrimeP,
   eslt_Length   keyPairPrimeQSize, eslt_pRomByte keyPairPrimeQ,
   eslt_Length   privateKeyExponentDPSize, eslt_pRomByte privateKeyExponentDP,
   eslt_Length   privateKeyExponentDQSize, eslt_pRomByte privateKeyExponentDQ,
   eslt_Length   privateKeyInverseQISize, eslt_pRomByte privateKeyInverseQI );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptRSACRT_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTdec_prim ) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) cipher,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) messageSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) message );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_CODE_OUT_OF_RANGE
       - 0 <= (int)cipher <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

/********/
extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignRSA_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAsig_prim ) workSpace,
     eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
     eslt_Length privateKeyExponentSize, eslt_pRomByte privateKeyExponent );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_signRSA_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAsig_prim ) workSpace,
   eslt_Length messageSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) message,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE
       - 0 <= (int)message <= modul-1
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignRSACRT_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTsig_prim ) workSpace,
   eslt_Length keyPairPrimePSize, eslt_pRomByte keyPairPrimeP,
   eslt_Length keyPairPrimeQSize, eslt_pRomByte keyPairPrimeQ,
   eslt_Length privateKeyExponentDPSize, eslt_pRomByte privateKeyExponentDP,
   eslt_Length privateKeyExponentDQSize, eslt_pRomByte privateKeyExponentDQ,
   eslt_Length privateKeyInverseQISize, eslt_pRomByte privateKeyInverseQI);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_signRSACRT_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTsig_prim ) workSpace,
   eslt_Length messageSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) message,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE
       - 0 <= (int)message <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptRSA_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAenc_prim ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length publicKeyExponentSize, eslt_pRomByte publicKeyExponent );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
      ESL_ERC_RSA_PUBKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptRSA_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAenc_prim ) workSpace,
   eslt_Length messageSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) message,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) cipherSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) cipher );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE
       - 0 <= (int)message <= modul-1
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initVerifyRSA_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver_prim ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length publicKeyExponentSize, eslt_pRomByte publicKeyExponent );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
      ESL_ERC_RSA_PUBKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifyRSA_prim(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver_prim ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) messageSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) message );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

/*****************************************************************************
 * Crypto functions RSA
 * according to PKCS#1 2.1
 * according to PKCS#1 V1.5-Versionen
 * these versions include simple padding, sign & verify use SHA-1
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptRSA_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAdec ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length privateKeyExponentSize, eslt_pRomByte privateKeyExponent );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptPubRSA_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAdec ) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) cipher,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) messageSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) message );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_CODE_OUT_OF_RANGE
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptPrivRSA_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAdec ) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) cipher,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) messageSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) message );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_CODE_OUT_OF_RANGE
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */
extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptRSA_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAdec ) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) cipher,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) messageSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) message );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_CODE_OUT_OF_RANGE
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptRSACRT_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTdec ) workSpace,
   eslt_Length keyPairPrimePSize, eslt_pRomByte keyPairPrimeP,
   eslt_Length keyPairPrimeQSize, eslt_pRomByte keyPairPrimeQ,
   eslt_Length privateKeyExponentDPSize, eslt_pRomByte privateKeyExponentDP,
   eslt_Length privateKeyExponentDQSize, eslt_pRomByte privateKeyExponentDQ,
   eslt_Length privateKeyInverseQISize, eslt_pRomByte privateKeyInverseQI );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_decryptRSACRT_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTdec ) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) cipher,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) messageSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) message );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_CODE_OUT_OF_RANGE
       - 0 <= (int)cipher <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignRSASHA1_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAsig ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length privateKeyExponentSize, eslt_pRomByte privateKeyExponent );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - if keyPairModuleSize < 46d = headLen+hLen+11, where
                           * hLen is the length of the Hashvalue (SHA-1: 20d= 0x14)
                           * headLen is the AlgoIDentifier (RSA+SHA1: 15d=0x0f)
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSignRSASHA1_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAsig ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
   - ErrorCodes of the underlying Hash-Function (SHA-1)
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSASHA1_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignRSACRTSHA1_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTsig ) workSpace,
   eslt_Length keyPairPrimePSize, eslt_pRomByte keyPairPrimeP,
   eslt_Length keyPairPrimeQSize, eslt_pRomByte keyPairPrimeQ,
   eslt_Length privateKeyExponentDPSize, eslt_pRomByte privateKeyExponentDP,
   eslt_Length privateKeyExponentDQSize, eslt_pRomByte privateKeyExponentDQ,
   eslt_Length privateKeyInverseQISize,eslt_pRomByte privateKeyInverseQI );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - keyPairModuleSize < 46d = headLen+hLen+11, where
                              * hLen is the length of the Hashvalue (SHA-1: 20d= 0x14)
                              * headLen is the AlgoIDentifier (RSA+SHA1: 15d=0x0f)
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSignRSACRTSHA1_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTsig ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
   - ErrorCodes of the underlying Hash-Function (SHA-1)
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSACRTSHA1_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initEncryptRSA_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAenc ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length publicKeyExponentSize, eslt_pRomByte publicKeyExponent );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_PUBKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_encryptRSA_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAenc ) workSpace,
   eslt_Length messageSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) message,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) cipherSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) cipher );
/* Assumes:
       - *cipherSize >= keyPairModuleSize
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE
       - if messageSize > keyPairModuleSize - 11
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT

      and all possible error codes which can occur in esl_getBytesRNG */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initVerifyRSASHA1_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length publicKeyExponentSize, eslt_pRomByte publicKeyExponent );
/* Assumes:
       - publicKeyExponent  < keyPairModule
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
      ESL_ERC_RSA_PUBKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateVerifyRSASHA1_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashVerifyRSASHA1_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ... */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSASHA1_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA1_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSASHA1_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );
/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA1_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

/*****************************************************************************
 * Crypto functions RSA (sign/verify) with RIPEMD-160
 * according to PKCS#1 1.5
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignRSARIPEMD160_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAsig ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length privateKeyExponentSize, eslt_pRomByte privateKeyExponent );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - if keyPairModuleSize < 46d = headLen+hLen+11, where
                           * hLen is the length of the Hashvalue (RIPEMD-160: 20d= 0x14)
                           * headLen is the AlgoIDentifier (RSA+RIPEMD-160: 15d=0x0f)
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSignRSARIPEMD160_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAsig ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
   - ErrorCodes of the underlying Hash-Function (RIPEMD-160)
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSARIPEMD160_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignRSACRTRIPEMD160_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTsig ) workSpace,
   eslt_Length keyPairPrimePSize, eslt_pRomByte keyPairPrimeP,
   eslt_Length keyPairPrimeQSize, eslt_pRomByte keyPairPrimeQ,
   eslt_Length privateKeyExponentDPSize, eslt_pRomByte privateKeyExponentDP,
   eslt_Length privateKeyExponentDQSize, eslt_pRomByte privateKeyExponentDQ,
   eslt_Length privateKeyInverseQISize, eslt_pRomByte privateKeyInverseQI );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - keyPairModuleSize < 46d = headLen+hLen+11, where
                              * hLen is the length of the Hashvalue (RIPEMD-160: 20d= 0x14)
                              * headLen is the AlgoIDentifier (RSA+RIPEMD-160: 15d=0x0f)
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSignRSACRTRIPEMD160_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTsig ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
   - ErrorCodes of the underlying Hash-Function (RIPEMD-160)
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSACRTRIPEMD160_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize, CRYPTOCV_P2VAR_PARA( eslt_Byte   ) signature);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initVerifyRSARIPEMD160_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length publicKeyExponentSize, eslt_pRomByte publicKeyExponent );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
      ESL_ERC_RSA_PUBKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateVerifyRSARIPEMD160_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashVerifyRSARIPEMD160_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest);

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ... */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSARIPEMD160_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace, CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature);

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_RIPEMD160_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSARIPEMD160_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_RIPEMD160_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

/*****************************************************************************
 * Crypto functions RSA (sign/verify) with SHA-256
 * according to PKCS#1 1.5
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignRSASHA256_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAsig ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length privateKeyExponentSize, eslt_pRomByte privateKeyExponent    );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - if keyPairModuleSize < 46d = headLen+hLen+11, where
                           * hLen is the length of the Hashvalue (SHA-256: 20d= 0x14)
                           * headLen is the AlgoIDentifier (RSA+SHA-256: 15d=0x0f)
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSignRSASHA256_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAsig ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
   - ErrorCodes of the underlying Hash-Function (SHA-256)
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSASHA256_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignRSACRTSHA256_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTsig ) workSpace,
   eslt_Length keyPairPrimePSize, eslt_pRomByte keyPairPrimeP,
   eslt_Length keyPairPrimeQSize, eslt_pRomByte keyPairPrimeQ,
   eslt_Length privateKeyExponentDPSize, eslt_pRomByte privateKeyExponentDP,
   eslt_Length privateKeyExponentDQSize, eslt_pRomByte privateKeyExponentDQ,
   eslt_Length privateKeyInverseQISize, eslt_pRomByte privateKeyInverseQI );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - keyPairModuleSize < 46d = headLen+hLen+11, where
                              * hLen is the length of the Hashvalue (SHA-256: 20d= 0x14)
                              * headLen is the AlgoIDentifier (RSA+SHA-256: 15d=0x0f)
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSignRSACRTSHA256_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTsig ) workSpace,
   const eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
   - ErrorCodes of the underlying Hash-Function (SHA-256)
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSACRTSHA256_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize, CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initVerifyRSASHA256_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length publicKeyExponentSize, eslt_pRomByte publicKeyExponent );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
      ESL_ERC_RSA_PUBKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateVerifyRSASHA256_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashVerifyRSASHA256_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace, CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ... */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSASHA256_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace,CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA256_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSASHA256_V15(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAver ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA256_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifyPaddingRSAEM_V15(
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) message, CRYPTOCV_P2VAR_PARA( eslt_Length ) paddingLength, eslt_Byte blockType );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_RSA_ENCODING_INVALID */

/*****************************************************************************
 * Crypto functions RSA (encrypt/decrypt) using SHA-1
 * according to PKCS#1 OAEP
 *****************************************************************************/
CRYPTOCV_FUNC(eslt_ErrorCode) esl_initEncryptRSASHA1_OAEP(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPenc) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length publicKeyExponentSize, eslt_pRomByte publicKeyExponent);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_PUBKEY_INVALID */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_encryptRSASHA1_OAEP_Seed_Label(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPenc) workSpace,
   eslt_Length messageSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) message,
   eslt_Length labelSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) label,
   eslt_Length inSeedSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) inSeed,
   CRYPTOCV_P2VAR_PARA(eslt_Length) cipherSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) cipher);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_encryptRSASHA1_OAEP(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPenc) workSpace,
   eslt_Length messageSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) message,
   CRYPTOCV_P2VAR_PARA(eslt_Length) cipherSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) cipher);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_encryptRSASHA1_OAEP_Seed(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPenc) workSpace,
   eslt_Length messageSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) message,
   eslt_Length inSeedSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) inSeed,
   CRYPTOCV_P2VAR_PARA(eslt_Length) cipherSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) cipher);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_encryptRSASHA1_OAEP_Label(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPenc) workSpace,
   eslt_Length messageSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) message,
   eslt_Length labelSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) label,
   CRYPTOCV_P2VAR_PARA(eslt_Length) cipherSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) cipher);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_initDecryptRSASHA1_OAEP(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPdec) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length privateKeyExponentSize, eslt_pRomByte privateKeyExponent);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_PRIVKEY_INVALID */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_decodeRSASHA1_OAEP(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpace) workSpace, eslt_Length encodedMessageSize,
   eslt_Length labelSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) label,
   CRYPTOCV_P2VAR_PARA(eslt_Length) messageSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) message);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_decryptRSASHA1_OAEP_Label(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPdec) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) cipher,
   eslt_Length labelSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) label,
   CRYPTOCV_P2VAR_PARA(eslt_Length) messageSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) message);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_decryptRSASHA1_OAEP(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPdec) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) cipher,
   CRYPTOCV_P2VAR_PARA(eslt_Length) messageSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) message);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptRSACRTSHA1_OAEP(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTOAEPdec ) workSpace,
   eslt_Length keyPairPrimePSize, eslt_pRomByte keyPairPrimeP,
   eslt_Length keyPairPrimeQSize, eslt_pRomByte keyPairPrimeQ,
   eslt_Length privateKeyExponentDPSize, eslt_pRomByte privateKeyExponentDP,
   eslt_Length privateKeyExponentDQSize, eslt_pRomByte privateKeyExponentDQ,
   eslt_Length privateKeyInverseQISize, eslt_pRomByte privateKeyInverseQI );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_PRIVKEY_INVALID */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_decryptRSACRTSHA1_OAEP_Label(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSACRTOAEPdec) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) cipher,
   eslt_Length labelSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) label,
   CRYPTOCV_P2VAR_PARA(eslt_Length) messageSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) message);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_decryptRSACRTSHA1_OAEP(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSACRTOAEPdec) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) cipher,
   CRYPTOCV_P2VAR_PARA(eslt_Length) messageSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) message);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

/*****************************************************************************
 * Crypto functions RSA (encrypt/decrypt) using SHA-256
 * according to PKCS#1 OAEP
 *****************************************************************************/

CRYPTOCV_FUNC(eslt_ErrorCode) esl_initEncryptRSASHA256_OAEP(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPenc) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length publicKeyExponentSize, eslt_pRomByte publicKeyExponent);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_PUBKEY_INVALID */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_encryptRSASHA256_OAEP_Seed_Label(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPenc) workSpace,
   eslt_Length messageSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) message,
   eslt_Length labelSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) label,
   eslt_Length inSeedSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) inSeed,
   CRYPTOCV_P2VAR_PARA(eslt_Length) cipherSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) cipher);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_encryptRSASHA256_OAEP(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPenc) workSpace,
   eslt_Length messageSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) message,
   CRYPTOCV_P2VAR_PARA(eslt_Length) cipherSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) cipher);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_encryptRSASHA256_OAEP_Seed(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPenc) workSpace,
   eslt_Length messageSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) message,
   eslt_Length inSeedSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) inSeed,
   CRYPTOCV_P2VAR_PARA(eslt_Length) cipherSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) cipher);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_encryptRSASHA256_OAEP_Label(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPenc) workSpace,
   eslt_Length messageSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) message,
   eslt_Length labelSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) label,
   CRYPTOCV_P2VAR_PARA(eslt_Length) cipherSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) cipher);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_initDecryptRSASHA256_OAEP(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPdec) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length privateKeyExponentSize, eslt_pRomByte privateKeyExponent);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_PRIVKEY_INVALID */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_decodeRSASHA256_OAEP(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpace) workSpace, eslt_Length encodedMessageSize,
   eslt_Length labelSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) label,
   CRYPTOCV_P2VAR_PARA(eslt_Length) messageSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) message);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_decryptRSASHA256_OAEP_Label(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPdec) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) cipher,
   eslt_Length labelSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) label,
   CRYPTOCV_P2VAR_PARA(eslt_Length) messageSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) message);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_decryptRSASHA256_OAEP(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSAOAEPdec) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) cipher,
   CRYPTOCV_P2VAR_PARA(eslt_Length) messageSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) message);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initDecryptRSACRTSHA256_OAEP(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSACRTOAEPdec ) workSpace,
   eslt_Length keyPairPrimePSize, eslt_pRomByte keyPairPrimeP,
   eslt_Length keyPairPrimeQSize, eslt_pRomByte keyPairPrimeQ,
   eslt_Length privateKeyExponentDPSize, eslt_pRomByte privateKeyExponentDP,
   eslt_Length privateKeyExponentDQSize, eslt_pRomByte privateKeyExponentDQ,
   eslt_Length privateKeyInverseQISize, eslt_pRomByte privateKeyInverseQI );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_PRIVKEY_INVALID */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_decryptRSACRTSHA256_OAEP_Label(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSACRTOAEPdec) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) cipher,
   eslt_Length labelSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) label,
   CRYPTOCV_P2VAR_PARA(eslt_Length) messageSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) message);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

CRYPTOCV_FUNC(eslt_ErrorCode) esl_decryptRSACRTSHA256_OAEP(
   CRYPTOCV_P2VAR_PARA(eslt_WorkSpaceRSACRTOAEPdec) workSpace,
   eslt_Length cipherSize, CRYPTOCV_P2CONST_PARA(eslt_Byte) cipher,
   CRYPTOCV_P2VAR_PARA(eslt_Length) messageSize, CRYPTOCV_P2VAR_PARA(eslt_Byte) message);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE */

/*****************************************************************************
 * Crypto functions RSA (sign/verify) with SHA-1
 * according to PKCS#1 PSS
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignRSASHA1_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length privateKeyExponentSize, eslt_pRomByte privateKeyExponent );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - if keyPairModuleSize < hLen + sLen +2
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSignRSASHA1_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
   - ErrorCodes of the underlying Hash-Function (SHA-1)
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashSignRSASHA1_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSigSignRSASHA1_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length saltSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) salt,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSigSignRSASHA1_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSigSignRSASHA1_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSASHA1_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   eslt_Length saltSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) salt,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSASHA1_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSASHA1_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initVerifyRSASHA1_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length publicKeyExponentSize, eslt_pRomByte publicKeyExponent );

/* Assumes:
       - publicKeyExponent  < keyPairModule
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - if keyPairModuleSize < hLen + sLen +2
      ESL_ERC_RSA_PUBKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateVerifyRSASHA1_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashVerifyRSASHA1_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ... */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSASHA1_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length saltSize,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA1_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSASHA1_PSS_AutoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA1_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSASHA1_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA1_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSASHA1_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA1_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSASHA1_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length saltSize, eslt_Length signatureSize,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA1_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSASHA1_PSS_AutoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA1_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSASHA1_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA1_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSASHA1_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA1_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateMaskMGF1RSASHA1_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSHA1 ) wsHash,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) tempHash,
   eslt_Length seedLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) seed,
   eslt_Length maskLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) mask );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ... */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_calcSaltedHashRSASHA1_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSHA1 ) wsHash,
   eslt_Length saltSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) salt,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) saltedHash );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ... */

/*****************************************************************************
 * Crypto functions RSA (sign/verify) with RIPEMD-160
 * according to PKCS#1 PSS
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignRSARIPEMD160_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length privateKeyExponentSize, eslt_pRomByte privateKeyExponent );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - if keyPairModuleSize < hLen + sLen +2
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSignRSARIPEMD160_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
   - ErrorCodes of the underlying Hash-Function (SHA-1)
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashSignRSARIPEMD160_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSigSignRSARIPEMD160_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length saltSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) salt,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSigSignRSARIPEMD160_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSigSignRSARIPEMD160_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSARIPEMD160_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   eslt_Length saltSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) salt,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSARIPEMD160_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSARIPEMD160_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initVerifyRSARIPEMD160_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length publicKeyExponentSize, eslt_pRomByte publicKeyExponent );

/* Assumes:
       - publicKeyExponent  < keyPairModule
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - if keyPairModuleSize < hLen + sLen +2
      ESL_ERC_RSA_PUBKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateVerifyRSARIPEMD160_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashVerifyRSARIPEMD160_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ... */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSARIPEMD160_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length saltSize,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_RIPEMD160_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSARIPEMD160_PSS_AutoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_RIPEMD160_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSARIPEMD160_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_RIPEMD160_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSARIPEMD160_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_RIPEMD160_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSARIPEMD160_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length saltSize, eslt_Length signatureSize,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_RIPEMD160_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSARIPEMD160_PSS_AutoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_RIPEMD160_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSARIPEMD160_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_RIPEMD160_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSARIPEMD160_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_RIPEMD160_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateMaskMGF1RSARIPEMD160_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRIPEMD160 ) wsHash,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) tempHash,
   eslt_Length seedLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) seed,
   eslt_Length maskLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) mask );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ... */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_calcSaltedHashRSARIPEMD160_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRIPEMD160 ) wsHash,
   eslt_Length saltSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) salt,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) saltedHash );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ... */

/*****************************************************************************
 * Crypto functions RSA (sign/verify) with SHA-256
 * according to PKCS#1 PSS
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignRSASHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length privateKeyExponentSize, eslt_pRomByte privateKeyExponent );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - if keyPairModuleSize < hLen + sLen +2
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSignRSASHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
   - ErrorCodes of the underlying Hash-Function (SHA-1)
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashSignRSASHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSigSignRSASHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length saltSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) salt,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSigSignRSASHA256_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSigSignRSASHA256_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSASHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   eslt_Length saltSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) salt,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSASHA256_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSASHA256_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignRSACRTSHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSCRTsig ) workSpace,
   eslt_Length keyPairPrimePSize, eslt_pRomByte keyPairPrimeP,
   eslt_Length keyPairPrimeQSize, eslt_pRomByte keyPairPrimeQ,
   eslt_Length privateKeyExponentDPSize, eslt_pRomByte privateKeyExponentDP,
   eslt_Length privateKeyExponentDQSize, eslt_pRomByte privateKeyExponentDQ,
   eslt_Length privateKeyInverseQISize, eslt_pRomByte privateKeyInverseQI );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - if keyPairModuleSize < hLen + sLen +2
      ESL_ERC_RSA_PRIVKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateSignRSACRTSHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSCRTsig ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );
/* ErrorCode:
   - ErrorCodes of the underlying Hash-Function (SHA-1)
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashSignRSACRTSHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSCRTsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSigSignRSACRTSHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSCRTsig ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length saltSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) salt,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSigSignRSACRTSHA256_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSCRTsig ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSigSignRSACRTSHA256_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSCRTsig ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSACRTSHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSCRTsig ) workSpace,
   eslt_Length saltSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) salt,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSACRTSHA256_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSCRTsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeSignRSACRTSHA256_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSCRTsig ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Length ) signatureSize,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) signature );

/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_OUTPUT_SIZE_TOO_SHORT */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initVerifyRSASHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length keyPairModuleSize, eslt_pRomByte keyPairModule,
   eslt_Length publicKeyExponentSize, eslt_pRomByte publicKeyExponent );

/* Assumes:
       - publicKeyExponent  < keyPairModule
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_MODULE_OUT_OF_RANGE
       - if keyPairModuleSize < hLen + sLen +2
      ESL_ERC_RSA_PUBKEY_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateVerifyRSASHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length inputSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) input );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_HASH_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeHashVerifyRSASHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) messageDigest );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ... */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSASHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length saltSize,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA256_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSASHA256_PSS_AutoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA256_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSASHA256_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA256_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifySigVerifyRSASHA256_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA256_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSASHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length saltSize, eslt_Length signatureSize,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA256_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSASHA256_PSS_AutoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA256_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSASHA256_PSS_NoSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA256_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_finalizeVerifyRSASHA256_PSS_DigestLengthSalt(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRSAPSSver ) workSpace,
   eslt_Length signatureSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) signature );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ...
      ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE
       - 0 <= (int)signature <= modul-1, where module = PrimeP*PrimeQ
      ESL_ERC_RSA_ENCODING_INVALID
      ESL_ERC_RSA_NO_RSA_WITH_SHA256_SIGNATURE
      ESL_ERC_RSA_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateMaskMGF1RSASHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSHA256 ) wsHash,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) tempHash,
   eslt_Length seedLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) seed,
   eslt_Length maskLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) mask );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ... */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_calcSaltedHashRSASHA256_PSS(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceSHA256 ) wsHash,
   eslt_Length saltSize, CRYPTOCV_P2CONST_PARA( eslt_Byte ) salt,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) messageDigest,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) saltedHash );

/* Assumes:
       -
   ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_PARAMETER_INVALID  - format problems, nullpointer, ... */

/*****************************************************************************
 * Crypto functions EdDSA & ECDH
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initSignEdDSA (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpace ) workSpace,
   eslt_Size16 curve,
   const eslt_Byte instance,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) context,
   const eslt_Length contextLength);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_CURVE_NOT_SUPPORTED
      ESL_ERC_INSTANCE_NOT_SUPPORTED
      ESL_ERC_WS_TOO_SMALL */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_signEdDSA (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpace ) workSpace,
   CRYPTOCV_P2CONST_PARA(eslt_Byte ) input,
   eslt_Length inputLength,
   CRYPTOCV_P2CONST_PARA(eslt_Byte ) secretKey,
   CRYPTOCV_P2CONST_PARA(eslt_Byte ) publicKey,
   CRYPTOCV_P2VAR_PARA(eslt_Byte) signature,
   CRYPTOCV_P2VAR_PARA(eslt_Length) signatureLength );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_BUFFER_TOO_SMALL

      ESL_ERC_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initVerifyEdDSA (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpace ) workSpace,
   eslt_Size16 curve,
   const eslt_Byte instance,
   CRYPTOCV_P2CONST_PARA( eslt_Byte ) context,
   const eslt_Length contextLength);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_CURVE_NOT_SUPPORTED
      ESL_ERC_INSTANCE_NOT_SUPPORTED
      ESL_ERC_WS_TOO_SMALL */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_verifyEdDSA (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpace ) workSpace,
   CRYPTOCV_P2CONST_PARA(eslt_Byte) input,
   eslt_Length inputLength,
   CRYPTOCV_P2CONST_PARA(eslt_Byte) publicKey,
   CRYPTOCV_P2CONST_PARA(eslt_Byte) signature,
   eslt_Length signatureLength );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_TOTAL_LENGTH_OVERFLOW
      ESL_ERC_SIGNATURE_INVALID */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_updateEdDSA (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpace ) workSpace,
   CRYPTOCV_P2CONST_PARA(eslt_Byte) input,
   eslt_Length inputLength );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_TOTAL_LENGTH_OVERFLOW */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initGenerateKeyPairEdDSA (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpace ) workSpace,
   eslt_Size16 curve );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_CURVE_NOT_SUPPORTED
      ESL_ERC_WS_TOO_SMALL */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateKeyPairEdDSA (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpace ) workSpace,
   CRYPTOCV_P2VAR_PARA(eslt_Byte) secretKey,
   CRYPTOCV_P2VAR_PARA(eslt_Length) secretKeyLength,
   CRYPTOCV_P2VAR_PARA(eslt_Byte) publicKey,
   CRYPTOCV_P2VAR_PARA(eslt_Length) publicKeyLength );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_BUFFER_TOO_SMALL
      ESL_ERC_RNG_FAILED */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initECDH (CRYPTOCV_P2VAR_PARA(
   eslt_WorkSpace ) workSpace,
   eslt_Size16 curve);
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_CURVE_NOT_SUPPORTED
      ESL_ERC_WS_TOO_SMALL */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateEphemeralKeyPairECDH (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpace ) workSpace,
   CRYPTOCV_P2VAR_PARA(eslt_Byte) publicKey,
   CRYPTOCV_P2VAR_PARA(eslt_Length) publicKeyLength );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_BUFFER_TOO_SMALL
      ESL_ERC_RNG_FAILED
      ESL_ERC_UNRECOVERABLE_ERROR */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_importStaticPrivateKeyECDH (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpace ) workSpace,
   CRYPTOCV_P2CONST_PARA(eslt_Byte) privateKey );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_BUFFER_TOO_SMALL
      ESL_ERC_RNG_FAILED
      ESL_ERC_UNRECOVERABLE_ERROR */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_generateSharedSecretECDH (
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpace ) workSpace,
   CRYPTOCV_P2VAR_PARA(eslt_Byte) publicKey,
   CRYPTOCV_P2VAR_PARA(eslt_Byte) sharedSecret,
   CRYPTOCV_P2VAR_PARA(eslt_Length) sharedSecretLength );
/* ErrorCode:
      ESL_ERC_NO_ERROR
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_BUFFER_TOO_SMALL */

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif /* __ESLib_H__ */

