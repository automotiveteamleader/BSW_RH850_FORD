/****************************************************************************
 ** Main author: Alf                     Creation date: 10/01/04
 ** $Author:: mgnida                   $ $JustDate:: 02/25/05             $
 ** $Workfile:: types.h                $ $Revision:: 2010                 $
 ** $NoKeywords::                                                         $
 **
 **
 ** \copyright(cv cryptovision GmbH, 1999 - 2005                          )
 **
 ** \version(cvActLibES 1.0                                               )
 ***************************************************************************/

/****************************************************************************
 **
 **     Part of the embedded systems library cvActLib/ES
 **
 **     Layer:
 **
 ***************************************************************************/

/****************************************************************************
 **
 ** This file contains: Definition of internal types and constants.
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

#ifndef __ESLib_types_H__
#define __ESLib_types_H__

#include "ESLib_t.h"

/*****************************************************************************
  Types and constants
 *****************************************************************************/
/* important WorkSpace-STate-Masks */
#define ESL_WST_M_LEN    (sizeof(eslt_WSStatus) * 8u)     /* L = status-bitLength */
#define ESL_WST_M_STATE  0xC000u /* bits 14,15 */
#define ESL_WST_M_ALGO   0x1F00u /* bits 8,9,10,11,12 */
#define ESL_WST_M_PRIM   0x00F0u /* bits 4,5,6,7 */

                              /* the workspace contains critical data
                                 maybe during consecutive enc/dec-steps */
#define ESL_WST_M_CRITICAL    0x8000u

                              /* during usage of the workspace, this state-bit
                               is active, this allows to recognize if some
                               routine was aborted at some unwanted place */
#define ESL_WST_M_RUNNING     0x4000u

#define ESL_WST_ALLOCATED 0x00FFu /* the STATUS has been set only by
                                     esl_initWorkSpaceHeader, no information about the
                                     content is known to the lib */

#define ESL_WST_ALGO_NOALGO         0u
#define ESL_WST_ALGO_AES128         0x0100u
#define ESL_WST_ALGO_SHA1           0x0200u
#define ESL_WST_ALGO_HMACSHA1       0x0300u
#define ESL_WST_ALGO_FIPS186        0x0400u
#define ESL_WST_ALGO_KDF2HMACSHA1   0x0500u
#define ESL_WST_ALGO_ECP            0x0600u
#define ESL_WST_ALGO_RSA            0x0700u
#define ESL_WST_ALGO_SHA256         0x0800u
#define ESL_WST_ALGO_SHA224         ESL_WST_ALGO_SHA256
#define ESL_WST_ALGO_RIPEMD160      0x0900u
#define ESL_WST_ALGO_AES192         0x0a00u
#define ESL_WST_ALGO_AES256         0x0b00u
#define ESL_WST_ALGO_HMACRIPEMD160  0x0c00u
#define ESL_WST_ALGO_KDFX963SHA1    0x0d00u
#define ESL_WST_ALGO_MD5            0x0e00u
#define ESL_WST_ALGO_HMACSHA256     0x0f00u
#define ESL_WST_ALGO_RC2            0x1000u
#define ESL_WST_ALGO_DES            0x1100u
#define ESL_WST_ALGO_TDES           0x1200u
#define ESL_WST_ALGO_CMACAES128     0x1300u
#define ESL_WST_ALGO_GCM            0x1400u
#define ESL_WST_ALGO_GMAC           0x1500u
#define ESL_WST_ALGO_SHA512         0x1600u
#define ESL_WST_ALGO_SHA512_224     ESL_WST_ALGO_SHA512
#define ESL_WST_ALGO_SHA512_256     ESL_WST_ALGO_SHA512
#define ESL_WST_ALGO_SHA384         ESL_WST_ALGO_SHA512
#define ESL_WST_ALGO_Ed25519        0x1700u
#define ESL_WST_ALGO_X25519         0x1800u
#define ESL_WST_ALGO_SIPHASH        0x1900u

/* the state is specified more exactly by XOR with one of the following constants */
#define ESL_WST_PRIM_ECPKG       0x0010u
#define ESL_WST_PRIM_ECPSP       0x0020u
#define ESL_WST_PRIM_ECPVP       0x0030u
#define ESL_WST_PRIM_ECPDH       0x0040u

#define ESL_WST_PRIM_RSA_CRT     0x0010u
#define ESL_WST_PRIM_RSA_NOCRT   0x0020u
#define ESL_WST_PRIM_RSA_KG      0x0030u
#define ESL_WST_PRIM_RSA_KGCRT   0x0040u

#endif /* __ESLib_types_H__ */

