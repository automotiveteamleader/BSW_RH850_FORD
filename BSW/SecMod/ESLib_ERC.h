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
 * Author: alf, cv cryptovision GmbH, 02/25/05
 *
 * $LastChangedBy: mneuhaus $
 * $LastChangedDate: 2016-12-15 16:40:28 +0100 (Do, 15 Dez 2016) $
 * $LastChangedRevision: 2373 $
 * $URL: https://subversion/svn/library-ES/branches/library-es/1.2.0-VectorInformatik/development/common/lib_es/include/ESLib_ERC.h $
 *
 *****************************************************************************
 */

/****************************************************************************
 **
 **     Part of the embedded systems library cvActLib/ES
 **
 **     Layer:
 **
 ***************************************************************************/

/****************************************************************************
 **
 ** This file contains: Error code definitions.
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
 ***************************************************************************/


#ifndef __ESLib_ERC_H__
#define __ESLib_ERC_H__ 1

#include "ESLib_t.h"

#ifdef  __cplusplus
extern "C" {
#endif

/*****************************************************************************
 *  Return code constants
 *****************************************************************************/

/* general error or return types: the highest nibble classifies the error types */
#define ESL_ERT_RETURNCODE    0x0000u /* no error */
#define ESL_ERT_WARNING       0x1000u /* a warning */
#define ESL_ERT_ERROR         0x2000u /* a fatal error */

/* workspace and init-errorcodes; second nibble == 1 */
#define ESL_ERT_WS_ERROR      ESL_ERT_ERROR+0x0100u


/*****************************************************************************
 * General Error or Return Codes
 *****************************************************************************/

typedef enum _eslt_ErrorCode {

   /* OK, NO ERROR */
   ESL_ERC_NO_ERROR                          = ESL_ERT_RETURNCODE,

   /* WARNINGS */
   ESL_ERC_WARNING                           = ESL_ERT_WARNING,

   /* GENERAL ERRORS */
   ESL_ERC_ERROR                             = ESL_ERT_ERROR,

   /* invalid workspace  */
   ESL_ERC_WS_STATE_INVALID                  = ESL_ERT_ERROR + 0x0001u,

   /* the given workSpace is too small */
   ESL_ERC_WS_TOO_SMALL                      = ESL_ERT_ERROR + 0x0002u,

   /* some parameters contain invalid values */
   ESL_ERC_PARAMETER_INVALID                 = ESL_ERT_ERROR + 0x0003u,

   /* unsupported mode (eslt_Mode) */
   ESL_ERC_MODE_INVALID                      = ESL_ERT_ERROR + 0x0004u,

   /* if two valid modes interfere */
   ESL_ERC_MODE_INCOMPATIBLE                 = ESL_ERT_ERROR + 0x0005u,

   /* memory conflict  */
   ESL_ERC_MEMORY_CONFLICT                   = ESL_ERT_ERROR + 0x0006u,

   /* the given output length is not sufficient */
   ESL_ERC_OUTPUT_SIZE_TOO_SHORT             = ESL_ERT_ERROR + 0x0007u,
   ESL_ERC_BUFFER_TOO_SMALL                  = ESL_ERT_ERROR + 0x0007u,   /* alias! */

   /* invalid input */
   ESL_ERC_INPUT_INVALID                     = ESL_ERT_ERROR + 0x0008u,


   /*  FIPS186 ERRORS  */
   /* init (HW not available, no response) */
   ESL_ERC_RNG_INIT_FAILED                   = ESL_ERT_ERROR + 0x0009u,

   /* not enough entropy */
   ESL_ERC_RNG_ENTROPY_TOO_SMALL             = ESL_ERT_ERROR + 0x000Au,

   /* bad internal state of RNG */
   ESL_ERC_RNG_BAD_INTERNAL_STATE            = ESL_ERT_ERROR + 0x000Bu,


   /*  AES128 ERRORS */
   /* the given padding is invalid */
   ESL_ERC_AES_PADDING_INVALID               = ESL_ERT_ERROR + 0x000Cu,

   /* Hash and HashMAC/ ERRORS */
   ESL_ERC_SHA1_TOTAL_LENGTH_OVERFLOW        = ESL_ERT_ERROR + 0x000Du,

   /*  key length is zero */
   ESL_ERC_HMAC_KEY_LENGTH_OUT_OF_RANGE      = ESL_ERT_ERROR + 0x000Eu,

   /* the given HashMAC is invalid  */
   ESL_ERC_HMAC_INCORRECT_MAC                = ESL_ERT_ERROR + 0x000Fu,


   /* KDF2 ERRORS */
   /* iteration count is zero */
   ESL_ERC_KDF_ITERATION_COUNT_OUT_OF_RANGE  = ESL_ERT_ERROR + 0x0010u,


   /* ECC ERRORS */
   /* the given domain parameter are invalid */
   ESL_ERC_ECC_DOMAIN_INVALID                = ESL_ERT_ERROR + 0x0011u,

   /* the public key is invalid */
   ESL_ERC_ECC_PUBKEY_INVALID                = ESL_ERT_ERROR + 0x0012u,

   /* the input message is too long */
   ESL_ERC_ECC_MESSAGE_TOO_LONG              = ESL_ERT_ERROR + 0x0013u,

   /* the private key is invalid */
   ESL_ERC_ECC_PRIVKEY_INVALID               = ESL_ERT_ERROR + 0x0014u,

   /* values do not match p and n */
   ESL_ERC_ECC_DOMAINEXT_INVALID             = ESL_ERT_ERROR + 0x0015u,

   /* value groups is not supported */
   ESL_ERC_ECC_SPEEDUPEXT_INVALID            = ESL_ERT_ERROR + 0x0016u,

   /* internal error of the  */
   ESL_ERC_ECC_INTERNAL_ERROR                = ESL_ERT_ERROR + 0x0017u,

   /* signature invalid */
   ESL_ERC_ECC_SIGNATURE_INVALID             = ESL_ERT_ERROR + 0x0018u,


   /* RSA ERRORS */
   /* the given module is not supported */
   ESL_ERC_RSA_MODULE_OUT_OF_RANGE           = ESL_ERT_ERROR + 0x0019u,

   /* input value (code) out of range */
   ESL_ERC_RSA_CODE_OUT_OF_RANGE             = ESL_ERT_ERROR + 0x001Au,

   /* input value (message) out of range */
   ESL_ERC_RSA_MESSAGE_OUT_OF_RANGE          = ESL_ERT_ERROR + 0x001Bu,

   /* input value (signature) out of range */
   ESL_ERC_RSA_SIGNATURE_OUT_OF_RANGE        = ESL_ERT_ERROR + 0x001Cu,

   /* the given signature is invalid */
   ESL_ERC_RSA_SIGNATURE_INVALID             = ESL_ERT_ERROR + 0x001Du,

   /* encoding invalid */
   ESL_ERC_RSA_ENCODING_INVALID              = ESL_ERT_ERROR + 0x001Eu,

   /* RSA public key invalid */
   ESL_ERC_RSA_PUBKEY_INVALID                = ESL_ERT_ERROR + 0x001Fu,

   /* RSA private key invalid */
   ESL_ERC_RSA_PRIVKEY_INVALID               = ESL_ERT_ERROR + 0x0020u,

   /* SHA-256 ERRORS */
   ESL_ERC_SHA256_TOTAL_LENGTH_OVERFLOW      = ESL_ERT_ERROR + 0x0021u,

   /* RIPEMD160 ERRORS */
   ESL_ERC_RIPEMD160_TOTAL_LENGTH_OVERFLOW   = ESL_ERT_ERROR + 0x0022u,


   /*  DES ERRORS */
   /* the given padding is invalid */
   ESL_ERC_DES_PADDING_INVALID               = ESL_ERT_ERROR + 0x0025u,


   /*  TDES ERRORS */
   /* the given key length is invalid */
   ESL_ERC_TDES_KEY_LENGTH_INVALID           = ESL_ERT_ERROR + 0x0026u,


   /* GCM Errors */
   /* key length must be one of the AES key lengths: 16, 24 or 32 bytes */
   ESL_ERC_GCM_INVALID_KEY_LENGTH            = ESL_ERT_ERROR + 0x0027u,

   /* input too long */
   ESL_ERC_GCM_TOTAL_LENGTH_OVERFLOW         = ESL_ERT_ERROR + 0x0028u,

   /* given tag does not match the computed tag */
   ESL_ERC_GCM_TAG_VERIFICATION_FAILED       = ESL_ERT_ERROR + 0x0029u,

   /* passing AAD after message data */
   ESL_ERC_GCM_STATE_INVALID                 = ESL_ERT_ERROR + 0x002Au,

   /* IV length must be at least 1 (bit) */
   ESL_ERC_INVALID_IV_LENGTH                 = ESL_ERT_ERROR + 0x002Bu,   /* NOT specific for GCM!! */


   /* SHA-512 Errors */
   ESL_ERC_TOTAL_LENGTH_OVERFLOW             = ESL_ERT_ERROR + 0x002Cu,   /* NOT specific for SHA-512!! */


   /* EdDSA Errors */
   /* curve not supported */
   ESL_ERC_CURVE_NOT_SUPPORTED               = ESL_ERT_ERROR + 0x002Du,   /* NOT specific for EdDSA!! */

   /* signature invalid */
   ESL_ERC_SIGNATURE_INVALID                 = ESL_ERT_ERROR + 0x002Eu,   /* NOT specific for EdDSA!! */

   /* RNG failed - no private key generated */
   ESL_ERC_RNG_FAILED                        = ESL_ERT_ERROR + 0x002Fu,   /* NOT specific for EdDSA!! */

   /* EdDSA instance not supported */
   ESL_ERC_INSTANCE_NOT_SUPPORTED            = ESL_ERT_ERROR + 0x0030u,

   /* unspecific Errors */
   /* unrecoverable error */
   ESL_ERC_UNRECOVERABLE_ERROR               = ESL_ERT_ERROR + 0x0800u,


   /* 16 bit signed error codes */
   ESL_ERC_16BITS                            = 0x7FFFu
} eslt_ErrorCode;

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif /*__ESLib_ERC_H__ */

