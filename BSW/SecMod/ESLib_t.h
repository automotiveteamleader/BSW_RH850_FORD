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
 * $LastChangedDate: 2016-12-15 16:40:28 +0100 (Do, 15 Dez 2016) $
 * $LastChangedRevision: 2373 $
 * $URL: https://subversion/svn/library-ES/branches/library-es/1.2.0-VectorInformatik/development/common/lib_es/include/ESLib_t.h $
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
 ** This file contains: Basic types definitions.
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

#ifndef __ESLib_t_H__
#define __ESLib_t_H__

#include "actConfig.h"

/*****************************************************************************
 * Basic types and constants
 *****************************************************************************/

#define ESL_BITS_PER_DIGIT     (ACT_PLATFORM_BITS_PER_DIGIT)

typedef actPlatformUint8  eslt_Size8;
typedef actPlatformUint16 eslt_Size16;
typedef actPlatformUint32 eslt_Size32;
#ifdef  ACT_PLATFORM_UINT64_AVAILABLE
typedef actPlatformUint64 eslt_Size64;
#endif

typedef eslt_Size8    eslt_Byte;
typedef eslt_Size16   eslt_Length;
typedef eslt_Size8    eslt_Mode;
typedef eslt_Size16   eslt_WSStatus;
typedef eslt_Size32   eslt_WSCheckSum;

#if defined( ESL_RSA_KEYSIZE )
#else
#  define ESL_RSA_KEYSIZE 1024
#endif /* ESL_RSA_KEYSIZE */

/* =============================================================================
   = additional datatypes for const and pointer types ==> Byte <==
   ============================================================================= */

/* These datatypes are designed to be used in parameter-lists, and usually not
   in type definitions.
   Most of these types are not used inside the library, but if they are needed
   these types are used.
   Const datatypes are defined directly by using the const-modifier, not by
   using types from the following list. (typedef const type cType; is not allowed)
   The const-modifier is only integrated into a typedef in combination
   with a pointer definition. (typedef CONST type * pcType */

CRYPTOCV_P2VAR_TYPE( CRYPTOCV_NONE, eslt_Byte ) eslt_pByte;    /* pointer to byte(s) */

CRYPTOCV_P2CONST_TYPE( CRYPTOCV_NONE, eslt_Byte ) eslt_pcByte; /* pointer to byte(s) that must not be
                                                                  manipulated using this pointer */

CRYPTOCV_P2VAR_TYPE( CRYPTOCV_NONE, eslt_pByte ) eslt_ppByte;  /* pointer to pointer(s) to byte(s)
                                                                  *ppByte = &byte1; - allowed
                                                                  **ppByte = byte2; - allowed */
CRYPTOCV_P2CONST_TYPE( CRYPTOCV_NONE, eslt_pByte ) eslt_pcpByte;  /* the byte(s) can be changed,
                                                                     the pointer(s) must not be changed */

CRYPTOCV_P2VAR_TYPE( CRYPTOCV_NONE, eslt_pcByte ) eslt_ppcByte;   /* the byte(s) must not be changed,
                                                                     the pointer(s) can be changed
                                                                     *ppByte = &byte1; - allowed
                                                                     **ppByte = byte2; - not allowed */

CRYPTOCV_P2CONST_TYPE( CRYPTOCV_NONE, eslt_pcByte ) eslt_pcpcByte;   /* neither the pointer(s) nor
                                                                        the byte(s) can be changed */

/* pcTYPE is read as pointer to a const variable of type TYPE
   the variable of type TYPE must not be changed
   pcpType means pc_pTYPE, and not p_cpTYPE */

/* Pointer to byte(s) located in ROM, e.g. RSA key data */
CRYPTOCV_P2ROMCONST_TYPE( CRYPTOCV_NONE, eslt_Byte ) eslt_pRomByte;

/*****************************************************************************
 * Library version
 *****************************************************************************/

typedef struct
{
   CRYPTOCV_P2ROMCONST( CRYPTOCV_NONE, char ) parameter;
   eslt_Size16                                     value;
} eslt_Version;

/* ******************************************************************************
   * Algorithm specific types and constants
   ****************************************************************************** */

typedef eslt_Mode     eslt_PaddingMode;
#define ESL_PM_PKCS5                      0x01u
#define ESL_PM_OFF                        0x02u
#define ESL_PM_ONEWITHZEROES              0x04u

typedef eslt_Mode     eslt_BlockMode;
#define ESL_BM_ECB                        0x00u
#define ESL_BM_CBC                        0x01u
/*#define ESL_BM_CFB                        0x02u
  #define ESL_BM_OFB                        0x03u */

#define ESL_SIZEOF_AES_BLOCK              16u

#define ESL_SIZEOF_AES128_KEY             16u
#define ESL_SIZEOF_AES128_BLOCK           ESL_SIZEOF_AES_BLOCK

#define ESL_SIZEOF_AES192_KEY             24u
#define ESL_SIZEOF_AES192_BLOCK           ESL_SIZEOF_AES_BLOCK

#define ESL_SIZEOF_AES256_KEY             32u
#define ESL_SIZEOF_AES256_BLOCK           ESL_SIZEOF_AES_BLOCK

#define ESL_SIZEOF_SIPHASH_KEY            16u

#define ESL_SIZEOF_DES_KEY                8u
#define ESL_SIZEOF_DES_BLOCK              8u
#define ESL_SIZEOF_2TDES_KEY              16u
#define ESL_SIZEOF_3TDES_KEY              24u

#define ESL_SIZEOF_RC2_KEY                16u
#define ESL_SIZEOF_RC2_EFF_KEY            16u
#define ESL_SIZEOF_RC2_BLOCK              8u

#define ESL_SIZEOF_GCM_BLOCK              ESL_SIZEOF_AES_BLOCK
#define ESL_SIZEOF_GCM_TAG                ESL_SIZEOF_AES_BLOCK

#define ESL_SIZEOF_SHA1_BLOCK             64u
#define ESL_SIZEOF_SHA1_DIGEST            20u

#define ESL_SIZEOF_RIPEMD160_BLOCK        64u
#define ESL_SIZEOF_RIPEMD160_DIGEST       20u

#define ESL_SIZEOF_SHA256_BLOCK           64u
#define ESL_SIZEOF_SHA224_DIGEST          28u
#define ESL_SIZEOF_SHA256_DIGEST          32u

#define ESL_SIZEOF_SHA512_BLOCK           128u
#define ESL_SIZEOF_SHA512_224_DIGEST      ESL_SIZEOF_SHA224_DIGEST
#define ESL_SIZEOF_SHA512_256_DIGEST      ESL_SIZEOF_SHA256_DIGEST
#define ESL_SIZEOF_SHA384_DIGEST          48u
#define ESL_SIZEOF_SHA512_DIGEST          64u

#define ESL_SIZEOF_MD5_BLOCK              64u
#define ESL_SIZEOF_MD5_DIGEST             16u

#define ESL_SIZEOF_Ed25519_KEY            32u
#define ESL_SIZEOF_Ed25519_SECRET_KEY     ESL_SIZEOF_Ed25519_KEY
#define ESL_SIZEOF_Ed25519_PUBLIC_KEY     ESL_SIZEOF_Ed25519_KEY
#define ESL_SIZEOF_Ed25519_SIGNATURE      64u
#define ESL_INSTANCE_Ed25519              0u    /* MUST match actEd25519pure */
#define ESL_INSTANCE_Ed25519ctx           1u    /* MUST match actEd25519ctx */
#define ESL_INSTANCE_Ed25519ph            2u    /* MUST match actEd25519ph */

#define ESL_SIZEOF_X25519_KEY             32u
#define ESL_SIZEOF_X25519_PRIVATE_KEY     ESL_SIZEOF_X25519_KEY
#define ESL_SIZEOF_X25519_PUBLIC_KEY      ESL_SIZEOF_X25519_KEY
#define ESL_SIZEOF_X25519_SHARED_SECRET   ESL_SIZEOF_X25519_KEY

#define ESL_Curve25519                    25519u
#define ESL_Curve448                      448u

#define ESL_SIZEOF_RNGFIPS186_STATE       (ESL_SIZEOF_SHA1_DIGEST)

#define ESL_KDF2_DEFAULT_ITERATION_COUNT   1u

/* ecc domain data types */
typedef eslt_Byte eslt_EccDomain;     /* the Domain as defined in X9.62 */
typedef eslt_Byte eslt_EccDomainExt;  /* some additional data about Domain */
typedef eslt_Byte eslt_EccSpeedUpExt; /* precomputed data for speed up */

/* ******************************************************************************
   * Work space types and constants
   ****************************************************************************** */

/* =============================================================================
   = Basic work space type definitions
   ============================================================================= */

typedef struct
{
   eslt_Length     size;        /* for overflow-checks */
   eslt_WSStatus   status;      /* for integrity checks */
   CRYPTOCV_P2FUNC( CRYPTOCV_NONE, void, watchdog )( void ); /* watchdog function */
   eslt_WSCheckSum checkSum;    /* for manipulation checks */
}eslt_WorkSpaceHeader;

/* NOTE: Any algorithm only accepts Workspaces that have initialized correctly! */
typedef struct
{
   eslt_WorkSpaceHeader header;
   eslt_Byte            ws[1];
}eslt_WorkSpace;

/* =============================================================================
   = ensure correct alignment of data
   ============================================================================= */

#ifdef ACT_PLATFORM_ALIGNMENT
# if (ACT_PLATFORM_ALIGNMENT == 1) || (ACT_PLATFORM_ALIGNMENT == 2) || (ACT_PLATFORM_ALIGNMENT == 4)
#  define ACT_ALIGN(size)   ((((size) +((ACT_PLATFORM_ALIGNMENT) -1))/(ACT_PLATFORM_ALIGNMENT))*(ACT_PLATFORM_ALIGNMENT))
# else
#  error Unknown alignment
# endif
#else
# error Alignment is not specified
#endif

#define ACT_MAX_ALIGN_OFFSET     (ACT_PLATFORM_ALIGNMENT-1)

/* =============================================================================
   = Symmetric algorithm work space sizes
   ============================================================================= */

/* AES128 workSpace sizes */
/* For (initTransformBlock, transformBlock, transformBlock, ..) calls */
#define ESL_MAXSIZEOF_WS_AES128BLOCK      (260u)
/* For (init, transform(input, len), ... ,transform(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_AES128           (ESL_MAXSIZEOF_WS_AES128BLOCK + ( 2u * ESL_SIZEOF_AES128_BLOCK ) + 8u)
/* For (init, transform(block), ... , transform(block)) sequences */
#define ESL_MINSIZEOF_WS_AES128           (ESL_MAXSIZEOF_WS_AES128 - ESL_SIZEOF_AES128_BLOCK)

/* AES192 workSpace sizes */
/* For (initTransformBlock, transformBlock, transformBlock, ..) calls */
#define ESL_MAXSIZEOF_WS_AES192BLOCK      (260u)
/* For (init, transform(input, len), ... ,transform(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_AES192           (ESL_MAXSIZEOF_WS_AES192BLOCK + ( 2u * ESL_SIZEOF_AES192_BLOCK ) + 8u)
/* For (init, transform(block), ... , transform(block)) sequences */
#define ESL_MINSIZEOF_WS_AES192           (ESL_MAXSIZEOF_WS_AES192 - ESL_SIZEOF_AES192_BLOCK)

/* AES256 workSpace sizes */
/* For (initTransformBlock, transformBlock, transformBlock, ..) calls */
#define ESL_MAXSIZEOF_WS_AES256BLOCK      (260u)
/* For (init, transform(input, len), ... ,transform(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_AES256           (ESL_MAXSIZEOF_WS_AES256BLOCK + ( 2u * ESL_SIZEOF_AES256_BLOCK ) + 8u)
/* For (init, transform(block), ... , transform(block)) sequences */
#define ESL_MINSIZEOF_WS_AES256           (ESL_MAXSIZEOF_WS_AES256 - ESL_SIZEOF_AES256_BLOCK)

/* DES workSpace sizes */
/* For (initTransformBlock, transformBlock, transformBlock, ..) calls */
#define ESL_MAXSIZEOF_WS_DESBLOCK         (200u)
/* For (init, transform(input, len), ... ,transform(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_DES              (ESL_MAXSIZEOF_WS_DESBLOCK + ( 2u * ESL_SIZEOF_DES_BLOCK ) + 8u)
/* For (init, transform(block), ... , transform(block)) sequences */
#define ESL_MINSIZEOF_WS_DES              (ESL_MAXSIZEOF_WS_DES - ESL_SIZEOF_DES_BLOCK)

/* TDES workSpace sizes */
/* For (initTransformBlock, transformBlock, transformBlock, ..) calls */
#define ESL_MAXSIZEOF_WS_TDESBLOCK         (500u)
/* For (init, transform(input, len), ... ,transform(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_TDES              (ESL_MAXSIZEOF_WS_TDESBLOCK + ( 2u * ESL_SIZEOF_DES_BLOCK ) + 8u)
/* For (init, transform(block), ... , transform(block)) sequences */
#define ESL_MINSIZEOF_WS_TDES              (ESL_MAXSIZEOF_WS_TDES - ESL_SIZEOF_DES_BLOCK)

/* RC2 workSpace sizes */
/* For (initTransformBlock, transformBlock, transformBlock, ..) calls */
#define ESL_MAXSIZEOF_WS_RC2BLOCK         (200u)
/* For (init, transform(input, len), ... ,transform(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_RC2              (ESL_MAXSIZEOF_WS_RC2BLOCK + ( 2u * ESL_SIZEOF_RC2_BLOCK ) + 8u)
/* For (init, transform(block), ... , transform(block)) sequences */
#define ESL_MINSIZEOF_WS_RC2              (ESL_MAXSIZEOF_WS_RC2 - ESL_SIZEOF_RC2_BLOCK)

/* GCM and GMAC workSpace sizes */
/* For (init, update(input, len), ... ,update(input, len), finalize) sequences
  ##########################################################################
  ##  Please read the "library/es Porting Guide" for more information!
  ########################################################################## */
/* #define ESL_SIZEOF_GHASH_SPEEDUP            0 */ /*  for actGHASH_SPEED_UP set to 0  (see "Porting Guide") */
#define ESL_SIZEOF_GHASH_SPEEDUP             256    /*  for actGHASH_SPEED_UP set to 1  (see "Porting Guide") */
/* #define ESL_SIZEOF_GHASH_SPEEDUP         4096 */ /*  for actGHASH_SPEED_UP set to 4  (see "Porting Guide") */
#define ESL_SIZEOF_WS_GHASH               (3* ESL_SIZEOF_GCM_TAG + 4u + ESL_SIZEOF_GHASH_SPEEDUP)
#define ESL_MAXSIZEOF_WS_GCM              (ESL_MAXSIZEOF_WS_AES256 + ESL_SIZEOF_WS_GHASH + ESL_SIZEOF_GCM_TAG + 2* ESL_SIZEOF_GCM_BLOCK + 24u)
#define ESL_MAXSIZEOF_WS_GMAC             (ESL_MAXSIZEOF_WS_GCM)

/* SHA-1 workSpace sizes */
/* For (init, update(input, len), ... ,update(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_SHA1             (ESL_SIZEOF_SHA1_BLOCK + ESL_SIZEOF_SHA1_DIGEST + 12u)
/* For (init, update(block), ... , update(block)) sequences */
#define ESL_MINSIZEOF_WS_SHA1             (ESL_MAXSIZEOF_WS_SHA1 - ESL_SIZEOF_SHA1_BLOCK)

/* SHA-256 workSpace sizes */
/* For (init, update(input, len), ... ,update(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_SHA256            (ESL_SIZEOF_SHA256_BLOCK + ESL_SIZEOF_SHA256_DIGEST + 12u)
/* For (init, update(block), ... , update(block)) sequences */
#define ESL_MINSIZEOF_WS_SHA256            (ESL_MAXSIZEOF_WS_SHA256 - ESL_SIZEOF_SHA256_BLOCK)

/* SHA-224 workSpace sizes */
/* For (init, update(input, len), ... ,update(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_SHA224            ESL_MAXSIZEOF_WS_SHA256    /*  same as SHA256!! */
/* For (init, update(block), ... , update(block)) sequences */
#define ESL_MINSIZEOF_WS_SHA224            ESL_MINSIZEOF_WS_SHA256    /*  same as SHA256!! */

/* SHA-512 workSpace sizes */
/* For (init, update(input, len), ... ,update(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_SHA512            (ESL_SIZEOF_SHA512_BLOCK + ESL_SIZEOF_SHA512_DIGEST + 20u)
/* For (init, update(block), ... , update(block)) sequences */
#define ESL_MINSIZEOF_WS_SHA512            ESL_MAXSIZEOF_WS_SHA512

/* SHA-512/224 workSpace sizes */
/* For (init, update(input, len), ... ,update(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_SHA512_224        ESL_MAXSIZEOF_WS_SHA512    /*  same as SHA512!! */
/* For (init, update(block), ... , update(block)) sequences */
#define ESL_MINSIZEOF_WS_SHA512_224        ESL_MINSIZEOF_WS_SHA512    /*  same as SHA512!! */

/* SHA-512/256 workSpace sizes */
/* For (init, update(input, len), ... ,update(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_SHA512_256        ESL_MAXSIZEOF_WS_SHA512    /*  same as SHA512!! */
/* For (init, update(block), ... , update(block)) sequences */
#define ESL_MINSIZEOF_WS_SHA512_256        ESL_MINSIZEOF_WS_SHA512    /*  same as SHA512!! */

/* SHA-384 workSpace sizes */
/* For (init, update(input, len), ... ,update(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_SHA384            ESL_MAXSIZEOF_WS_SHA512    /*  same as SHA512!! */
/* For (init, update(block), ... , update(block)) sequences */
#define ESL_MINSIZEOF_WS_SHA384            ESL_MINSIZEOF_WS_SHA512    /*  same as SHA512!! */

/* MD5 workSpace sizes */
/* For (init, update(input, len), ... ,update(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_MD5              (ESL_SIZEOF_MD5_BLOCK + ESL_SIZEOF_MD5_DIGEST + 12u)
/* For (init, update(block), ... , update(block)) sequences */
#define ESL_MINSIZEOF_WS_MD5              (ESL_MAXSIZEOF_WS_MD5 - ESL_SIZEOF_MD5_BLOCK)

/* HMACSHA-1 workSpace sizes */
/* For (init, update(input, len), ... ,update(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_HMACSHA1         (ESL_MAXSIZEOF_WS_SHA1 + ESL_SIZEOF_SHA1_BLOCK + 4u)

/* HMACSHA-256 workSpace sizes */
/* For (init, update(input, len), ... ,update(input, len), finalize) sequences */
#define ESL_MAXSIZEOF_WS_HMACSHA256       (ESL_MAXSIZEOF_WS_SHA256 + ESL_SIZEOF_SHA256_BLOCK + 4u)

/* RIPEMD-160 */
#define ESL_MAXSIZEOF_WS_RIPEMD160        ESL_MAXSIZEOF_WS_SHA1
#define ESL_MAXSIZEOF_WS_HMACRIPEMD160    ESL_MAXSIZEOF_WS_HMACSHA1
#define ESL_MINSIZEOF_WS_RIPEMD160        (ESL_MAXSIZEOF_WS_SHA1 - ESL_SIZEOF_SHA1_BLOCK)

/* CMAC (AES-128) */
#define ESL_MAXSIZEOF_WS_CMACAES          ESL_MAXSIZEOF_WS_AES128

/* SipHash */
#define ESL_MAXSIZEOF_WS_SIPHASH          48u

/* KDF-2 workSpace sizes */
#define ESL_MAXSIZEOF_WS_KDF2HMACSHA1     (ESL_MAXSIZEOF_WS_HMACSHA1 + ( 2u * ESL_SIZEOF_SHA1_DIGEST ) + 4u)

/* KDF-X963 workSpace sizes */
#define ESL_MAXSIZEOF_WS_KDFX963SHA1      (ESL_MAXSIZEOF_WS_SHA1 + ESL_SIZEOF_SHA1_DIGEST)

/* FIPS186 workspace sizes */
#define ESL_MAXSIZEOF_WS_FIPS186          ((ESL_MAXSIZEOF_WS_SHA1) + (ESL_SIZEOF_SHA1_DIGEST) + 4u)

/* =============================================================================
   = ECC algorithm work space sizes
   ============================================================================= */

/* ECP workSpace sizes

   All sizes up to the listed length in bits of the field primes p and n.
   For key generation (kg), signature generation (sp), signature verification (vp),
   Diffie-Hellman generate secret (dh_prim) or key exchange (dh) different memory
   sizes are required. */

/* p_bits, n_bits <= 160                                  (Fermat inversion values:) */
#define ESL_SIZEOF_WS_ECP_160_KG   (440u) /* kg, dh_prim   (384)   */
#define ESL_SIZEOF_WS_ECP_160_DH   (460u) /* dh            (404)   */
#define ESL_SIZEOF_WS_ECP_160_SP   (520u) /* sp            (464)   */
#define ESL_SIZEOF_WS_ECP_160_VP   (628u) /* vp            (572)   */
/* p_bits, n_bits <= 192 */
#define ESL_SIZEOF_WS_ECP_192_KG   (504u) /* kg, dh_prim   (440)   */
#define ESL_SIZEOF_WS_ECP_192_DH   (528u) /* dh            (464)   */
#define ESL_SIZEOF_WS_ECP_192_SP   (600u) /* sp            (536)   */
#define ESL_SIZEOF_WS_ECP_192_VP   (728u) /* vp            (664)   */
/* p_bits, n_bits <= 224 */
#define ESL_SIZEOF_WS_ECP_224_KG   (568u) /* kg, dh_prim   (496)   */
#define ESL_SIZEOF_WS_ECP_224_DH   (596u) /* dh            (524)   */
#define ESL_SIZEOF_WS_ECP_224_SP   (680u) /* sp            (608)   */
#define ESL_SIZEOF_WS_ECP_224_VP   (828u) /* vp            (756)   */
/* p_bits, n_bits <= 256 */
#define ESL_SIZEOF_WS_ECP_256_KG   (632u) /* kg, dh_prim   (552)   */
#define ESL_SIZEOF_WS_ECP_256_DH   (664u) /* dh            (584)   */
#define ESL_SIZEOF_WS_ECP_256_SP   (760u) /* sp            (680)   */
#define ESL_SIZEOF_WS_ECP_256_VP   (928u) /* vp            (848)   */

/* 256 bit size choosen for eslt_WorkSpaceEcP definition: */
#define ESL_MAXSIZEOF_WS_ECP        ESL_SIZEOF_WS_ECP_256_VP /* kg, dh_prim, dh, sp, vp */

/* =============================================================================
   = RSA work space sizes (core)
   ============================================================================= */

/* RSA core pub/priv/privCRT for 1k, 1.5k, 2k, 3k and 4k RSA */

#define ESL_DIGIT_LENGTH_P_Q(bitLength)         (((((bitLength / 2) + 32u) - 1u) / actBN_BITS_PER_DIGIT) + 1u)
#define ESL_SIZEOF_WS_RSA_PRIV_CRT(bitLength)   (72u + (((5u * ESL_DIGIT_LENGTH_P_Q(bitLength)) + ((1u + actRSA_MOD_EXP_TMP) * (ESL_DIGIT_LENGTH_P_Q(bitLength) + 1u))) * actBN_BYTES_PER_DIGIT))

/* n_bits <= 512 */
#define ESL_SIZEOF_WS_RSA_PUB_512               ( 466u)
#define ESL_SIZEOF_WS_RSA_PRIV_512              ( 466u)
/* n_bits <= 1024 */
#define ESL_SIZEOF_WS_RSA_PUB_1024              ( 816u)
#define ESL_SIZEOF_WS_RSA_PRIV_1024             ( 816u)
#define ESL_SIZEOF_WS_RSA_PRIV_CRT_1024         ESL_SIZEOF_WS_RSA_PRIV_CRT(1024u)   /* assumes: p_bits, q_bits <= 544 */
/* n_bits <= 1536 */
#define ESL_SIZEOF_WS_RSA_PUB_1536              (1200u)
#define ESL_SIZEOF_WS_RSA_PRIV_1536             (1200u)
#define ESL_SIZEOF_WS_RSA_PRIV_CRT_1536         ESL_SIZEOF_WS_RSA_PRIV_CRT(1536u)   /* assumes: p_bits, q_bits <= 800 */
/* n_bits <= 2048 */
#define ESL_SIZEOF_WS_RSA_PUB_2048              (1584u)
#define ESL_SIZEOF_WS_RSA_PRIV_2048             (1584u)
#define ESL_SIZEOF_WS_RSA_PRIV_CRT_2048         ESL_SIZEOF_WS_RSA_PRIV_CRT(2048u)   /* assumes: p_bits, q_bits <= 1056 */
/* n_bits <= 3072 */
#define ESL_SIZEOF_WS_RSA_PUB_3072              (2352u)
#define ESL_SIZEOF_WS_RSA_PRIV_3072             (2352u)
#define ESL_SIZEOF_WS_RSA_PRIV_CRT_3072         ESL_SIZEOF_WS_RSA_PRIV_CRT(3072u)   /* assumes: p_bits, q_bits <= 1568 */
/* n_bits <= 4096 */
#define ESL_SIZEOF_WS_RSA_PUB_4096              (3120u)
#define ESL_SIZEOF_WS_RSA_PRIV_4096             (3120u)
#define ESL_SIZEOF_WS_RSA_PRIV_CRT_4096         ESL_SIZEOF_WS_RSA_PRIV_CRT(4096u)   /* assumes: p_bits, q_bits <= 2080 */

/* RSA V15 core enc/dec workspace organisation
   WS_Header || BufferLength || Buffer || WS_RSA_PRIM (inkl. WS_RSA_PRIM_Header) */
#define ESL_WS_RSA_V15_ED_OFFSET_BUFFERLENGTH                  (ACT_ALIGN (sizeof(eslt_WorkSpaceHeader)))
#define ESL_WS_RSA_V15_ED_OFFSET_BUFFER                        (ACT_ALIGN (ESL_WS_RSA_V15_ED_OFFSET_BUFFERLENGTH + sizeof(eslt_Length)))
#define ESL_WS_RSA_V15_ED_OFFSET_WS_RSA_PRIM(ByteSizeOfBuffer) (ACT_ALIGN (ESL_WS_RSA_V15_ED_OFFSET_BUFFER + (ByteSizeOfBuffer)))
#define ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD(ByteSizeOfBuffer) (ESL_WS_RSA_V15_ED_OFFSET_WS_RSA_PRIM(ByteSizeOfBuffer))
#define ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1024              (sizeof(eslt_WorkSpaceHeader) + sizeof(eslt_Length) + 128u + (3u*ACT_MAX_ALIGN_OFFSET))
#define ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1536              (ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1024 + 64u)
#define ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_2048              (ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1024 + 128u)
#define ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_3072              (ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1024 + 256u)
#define ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_4096              (ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1024 + 384u)
#define ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_512               (ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1024 - 32u)

/* RSA V15 core sig/ver workspace organisation (SHA1)
   WS_Header || BufferLength || Buffer || WS_SHA1 (inkl. WS_SHA1_HEADER) || WS_RSA_PRIM (inkl. WS_RSA_PRIM_Header) */
#define ESL_WS_RSA_V15_SV_SHA1_BUFFERLENGTH                      (ACT_ALIGN (sizeof(eslt_WorkSpaceHeader)))
#define ESL_WS_RSA_V15_SV_SHA1_BUFFER                            (ACT_ALIGN (ESL_WS_RSA_V15_SV_SHA1_BUFFERLENGTH + sizeof(eslt_Length)))
#define ESL_WS_RSA_V15_SV_SHA1_WS_SHA1(ByteSizeOfBuffer)         (ACT_ALIGN (ESL_WS_RSA_V15_SV_SHA1_BUFFER + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_V15_SV_SHA1_WS_RSA_PRIM(ByteSizeOfBuffer)     (ACT_ALIGN (ESL_WS_RSA_V15_SV_SHA1_WS_SHA1(ByteSizeOfBuffer) + sizeof(eslt_WorkSpaceSHA1)))
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA1_OVERHEAD(ByteSizeOfBuffer) (ESL_WS_RSA_V15_SV_SHA1_WS_RSA_PRIM(ByteSizeOfBuffer))
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA1_OVERHEAD_1024              (sizeof(eslt_WorkSpaceHeader) + sizeof(eslt_Length) + 128u + sizeof(eslt_WorkSpaceSHA1) + (4u*ACT_MAX_ALIGN_OFFSET))
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA1_OVERHEAD_1536              (ESL_SIZEOF_WS_RSA_V15_SV_SHA1_OVERHEAD_1024 + 64u)
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA1_OVERHEAD_2048              (ESL_SIZEOF_WS_RSA_V15_SV_SHA1_OVERHEAD_1024 + 128u)
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA1_OVERHEAD_3072              (ESL_SIZEOF_WS_RSA_V15_SV_SHA1_OVERHEAD_1024 + 256u)
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA1_OVERHEAD_4096              (ESL_SIZEOF_WS_RSA_V15_SV_SHA1_OVERHEAD_1024 + 384u)
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA1_OVERHEAD_512               (ESL_SIZEOF_WS_RSA_V15_SV_SHA1_OVERHEAD_1024 - 32u)

/* RSA V15 core sig/ver workspace organisation (RIPEMD160)
   WS_Header || BufferLength || Buffer || WS_RIPEMD160 (inkl. WS_RIPEMD160_HEADER) || WS_RSA_PRIM (inkl. WS_RSA_PRIM_Header) */
#define ESL_WS_RSA_V15_SV_RIPEMD160_BUFFERLENGTH                      (ACT_ALIGN (sizeof(eslt_WorkSpaceHeader)))
#define ESL_WS_RSA_V15_SV_RIPEMD160_BUFFER                            (ACT_ALIGN (ESL_WS_RSA_V15_SV_RIPEMD160_BUFFERLENGTH + sizeof(eslt_Length)))
#define ESL_WS_RSA_V15_SV_RIPEMD160_WS_RIPEMD160(ByteSizeOfBuffer)    (ACT_ALIGN (ESL_WS_RSA_V15_SV_RIPEMD160_BUFFER + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_V15_SV_RIPEMD160_WS_RSA_PRIM(ByteSizeOfBuffer)     (ACT_ALIGN (ESL_WS_RSA_V15_SV_RIPEMD160_WS_RIPEMD160(ByteSizeOfBuffer) + sizeof(eslt_WorkSpaceRIPEMD160)))
#define ESL_SIZEOF_WS_RSA_V15_SV_RIPEMD160_OVERHEAD(ByteSizeOfBuffer) (ESL_WS_RSA_V15_SV_RIPEMD160_WS_RSA_PRIM(ByteSizeOfBuffer))
#define ESL_SIZEOF_WS_RSA_V15_SV_RIPEMD160_OVERHEAD_1024              (sizeof(eslt_WorkSpaceHeader) + sizeof(eslt_Length) + 128u + sizeof(eslt_WorkSpaceRIPEMD160) + (4u*ACT_MAX_ALIGN_OFFSET))
#define ESL_SIZEOF_WS_RSA_V15_SV_RIPEMD160_OVERHEAD_1536              (ESL_SIZEOF_WS_RSA_V15_SV_RIPEMD160_OVERHEAD_1024 + 64u)
#define ESL_SIZEOF_WS_RSA_V15_SV_RIPEMD160_OVERHEAD_2048              (ESL_SIZEOF_WS_RSA_V15_SV_RIPEMD160_OVERHEAD_1024 + 128u)
#define ESL_SIZEOF_WS_RSA_V15_SV_RIPEMD160_OVERHEAD_3072              (ESL_SIZEOF_WS_RSA_V15_SV_RIPEMD160_OVERHEAD_1024 + 256u)
#define ESL_SIZEOF_WS_RSA_V15_SV_RIPEMD160_OVERHEAD_4096              (ESL_SIZEOF_WS_RSA_V15_SV_RIPEMD160_OVERHEAD_1024 + 384u)

/* RSA V15 core sig/ver workspace organisation (SHA256)
   WS_Header || BufferLength || Buffer || WS_SHA256 (inkl. WS_SHA256_HEADER) || WS_RSA_PRIM (inkl. WS_RSA_PRIM_Header) */
#define ESL_WS_RSA_V15_SV_SHA256_BUFFERLENGTH                      (ACT_ALIGN (sizeof(eslt_WorkSpaceHeader)))
#define ESL_WS_RSA_V15_SV_SHA256_BUFFER                            (ACT_ALIGN (ESL_WS_RSA_V15_SV_SHA256_BUFFERLENGTH + sizeof(eslt_Length)))
#define ESL_WS_RSA_V15_SV_SHA256_WS_SHA256(ByteSizeOfBuffer)       (ACT_ALIGN (ESL_WS_RSA_V15_SV_SHA256_BUFFER + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_V15_SV_SHA256_WS_RSA_PRIM(ByteSizeOfBuffer)     (ACT_ALIGN (ESL_WS_RSA_V15_SV_SHA256_WS_SHA256(ByteSizeOfBuffer) + sizeof(eslt_WorkSpaceSHA256)))
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD(ByteSizeOfBuffer) (ESL_WS_RSA_V15_SV_SHA256_WS_RSA_PRIM(ByteSizeOfBuffer))
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_1024              (sizeof(eslt_WorkSpaceHeader) + sizeof(eslt_Length) + 128u + sizeof(eslt_WorkSpaceSHA256) + (4u*ACT_MAX_ALIGN_OFFSET))
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_1536              (ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_1024 + 64u)
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_2048              (ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_1024 + 128u)
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_3072              (ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_1024 + 256u)
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_4096              (ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_1024 + 384u)
#define ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_512               (ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_1024 - 32u)

/* RSA V15 core hash overhead ( NOTE: must be MAX(SHA1_OVERHEAD, SHA256_OVERHEAD, RIPEMD160_OVERHEAD) ) */
#define ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_512    (ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_512)
#define ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_1024   (ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_1024)
#define ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_1536   (ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_1536)
#define ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_2048   (ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_2048)
#define ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_3072   (ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_3072)
#define ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_4096   (ESL_SIZEOF_WS_RSA_V15_SV_SHA256_OVERHEAD_4096)

/* RSA OAEP core enc/dec workspace organisation (SHA1)
   WS_Header || BufferLength || 2 x Buffer (RSA result, DB and temporary hash value) || WS_SHA1 (inkl. WS_SHA1_HEADER) || WS_RSA_PRIM (inkl. WS_RSA_PRIM_Header) */
#define ESL_WS_RSA_OAEP_ED_SHA1_BUFFERLENGTH                      (ACT_ALIGN (sizeof(eslt_WorkSpaceHeader)))
#define ESL_WS_RSA_OAEP_ED_SHA1_BUFFER                            (ACT_ALIGN (ESL_WS_RSA_OAEP_ED_SHA1_BUFFERLENGTH + sizeof(eslt_Length)))
#define ESL_WS_RSA_OAEP_ED_SHA1_DB_BUFFER(ByteSizeOfBuffer)       (ACT_ALIGN (ESL_WS_RSA_OAEP_ED_SHA1_BUFFER + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_OAEP_ED_SHA1_WS_SHA1(ByteSizeOfBuffer)         (ACT_ALIGN (ESL_WS_RSA_OAEP_ED_SHA1_DB_BUFFER(ByteSizeOfBuffer) + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_OAEP_ED_SHA1_WS_RSA_PRIM(ByteSizeOfBuffer)     (ACT_ALIGN (ESL_WS_RSA_OAEP_ED_SHA1_WS_SHA1(ByteSizeOfBuffer) + sizeof(eslt_WorkSpaceSHA1)))
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA1_OVERHEAD(ByteSizeOfBuffer) (ESL_WS_RSA_OAEP_ED_SHA1_WS_RSA_PRIM(ByteSizeOfBuffer))
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA1_OVERHEAD_1024              (sizeof(eslt_WorkSpaceHeader) + sizeof(eslt_Length) + (2 * 128u) + sizeof(eslt_WorkSpaceSHA1) + 4u*ACT_MAX_ALIGN_OFFSET)
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA1_OVERHEAD_1536              (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA1_OVERHEAD_1024 + (2u * 64u))
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA1_OVERHEAD_2048              (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA1_OVERHEAD_1024 + (2u * 128u))
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA1_OVERHEAD_3072              (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA1_OVERHEAD_1024 + (2u * 256u))
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA1_OVERHEAD_4096              (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA1_OVERHEAD_1024 + (2u * 384u))
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA1_OVERHEAD_512               (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA1_OVERHEAD_1024 - (2u * 32u))

/* RSA OAEP core enc/dec workspace organisation (SHA256)
   WS_Header || BufferLength || 2 x Buffer (RSA result, DB and temporary hash value) || WS_SHA256 (inkl. WS_SHA256_HEADER) || WS_RSA_PRIM (inkl. WS_RSA_PRIM_Header) */
#define ESL_WS_RSA_OAEP_ED_SHA256_BUFFERLENGTH                      (ACT_ALIGN (sizeof(eslt_WorkSpaceHeader)))
#define ESL_WS_RSA_OAEP_ED_SHA256_BUFFER                            (ACT_ALIGN (ESL_WS_RSA_OAEP_ED_SHA256_BUFFERLENGTH + sizeof(eslt_Length)))
#define ESL_WS_RSA_OAEP_ED_SHA256_DB_BUFFER(ByteSizeOfBuffer)       (ACT_ALIGN (ESL_WS_RSA_OAEP_ED_SHA256_BUFFER + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_OAEP_ED_SHA256_WS_SHA256(ByteSizeOfBuffer)         (ACT_ALIGN (ESL_WS_RSA_OAEP_ED_SHA256_DB_BUFFER(ByteSizeOfBuffer) + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_OAEP_ED_SHA256_WS_RSA_PRIM(ByteSizeOfBuffer)     (ACT_ALIGN (ESL_WS_RSA_OAEP_ED_SHA256_WS_SHA256(ByteSizeOfBuffer) + sizeof(eslt_WorkSpaceSHA256)))
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD(ByteSizeOfBuffer) (ESL_WS_RSA_OAEP_ED_SHA256_WS_RSA_PRIM(ByteSizeOfBuffer))
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_1024              (sizeof(eslt_WorkSpaceHeader) + sizeof(eslt_Length) + (2 * 128u) + sizeof(eslt_WorkSpaceSHA256) + 4u*ACT_MAX_ALIGN_OFFSET)
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_1536              (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_1024 + (2u * 64u))
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_2048              (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_1024 + (2u * 128u))
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_3072              (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_1024 + (2u * 256u))
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_4096              (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_1024 + (2u * 384u))
#define ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_512               (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_1024 - (2u * 32u))

/* RSA PSS core hash overhead ( NOTE: must be MAX(SHA1_OVERHEAD, SHA256_OVERHEAD, RIPEMD160_OVERHEAD) ) */
#define ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_512                 (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_512)
#define ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_1024                (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_1024)
#define ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_1536                (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_1536)
#define ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_2048                (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_2048)
#define ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_3072                (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_3072)
#define ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_4096                (ESL_SIZEOF_WS_RSA_OAEP_ED_SHA256_OVERHEAD_4096)

/* RSA PSS core sig/ver workspace organisation (SHA1)
   WS_Header || BufferLength || 2 x Buffer (RSA result, DB and temporary hash value) || WS_SHA1 (inkl. WS_SHA1_HEADER) || WS_RSA_PRIM (inkl. WS_RSA_PRIM_Header) */
#define ESL_WS_RSA_PSS_SV_SHA1_BUFFERLENGTH                      (ACT_ALIGN (sizeof(eslt_WorkSpaceHeader)))
#define ESL_WS_RSA_PSS_SV_SHA1_BUFFER                            (ACT_ALIGN (ESL_WS_RSA_PSS_SV_SHA1_BUFFERLENGTH + sizeof(eslt_Length)))
#define ESL_WS_RSA_PSS_SV_SHA1_DB_BUFFER(ByteSizeOfBuffer)       (ACT_ALIGN (ESL_WS_RSA_PSS_SV_SHA1_BUFFER + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_PSS_SV_SHA1_WS_SHA1(ByteSizeOfBuffer)         (ACT_ALIGN (ESL_WS_RSA_PSS_SV_SHA1_DB_BUFFER(ByteSizeOfBuffer) + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_PSS_SV_SHA1_WS_RSA_PRIM(ByteSizeOfBuffer)     (ACT_ALIGN (ESL_WS_RSA_PSS_SV_SHA1_WS_SHA1(ByteSizeOfBuffer) + sizeof(eslt_WorkSpaceSHA1)))
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA1_OVERHEAD(ByteSizeOfBuffer) (ESL_WS_RSA_PSS_SV_SHA1_WS_RSA_PRIM(ByteSizeOfBuffer))
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA1_OVERHEAD_1024              (sizeof(eslt_WorkSpaceHeader) + sizeof(eslt_Length) + (2 * 128u) + sizeof(eslt_WorkSpaceSHA1) + 4u*ACT_MAX_ALIGN_OFFSET)
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA1_OVERHEAD_1536              (ESL_SIZEOF_WS_RSA_PSS_SV_SHA1_OVERHEAD_1024 + (2u * 64u))
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA1_OVERHEAD_2048              (ESL_SIZEOF_WS_RSA_PSS_SV_SHA1_OVERHEAD_1024 + (2u * 128u))
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA1_OVERHEAD_3072              (ESL_SIZEOF_WS_RSA_PSS_SV_SHA1_OVERHEAD_1024 + (2u * 256u))
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA1_OVERHEAD_4096              (ESL_SIZEOF_WS_RSA_PSS_SV_SHA1_OVERHEAD_1024 + (2u * 384u))
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA1_OVERHEAD_512               (ESL_SIZEOF_WS_RSA_PSS_SV_SHA1_OVERHEAD_1024 - (2u * 32u))

/* RSA PSS core sig/ver workspace organisation (RIPEMD160)
   WS_Header || BufferLength || 2 x Buffer (RSA result, DB and temporary hash value) || WS_RIPEMD160 (inkl. WS_RIPEMD160_HEADER) || WS_RSA_PRIM (inkl. WS_RSA_PRIM_Header) */
#define ESL_WS_RSA_PSS_SV_RIPEMD160_BUFFERLENGTH                      (ACT_ALIGN (sizeof(eslt_WorkSpaceHeader)))
#define ESL_WS_RSA_PSS_SV_RIPEMD160_BUFFER                            (ACT_ALIGN (ESL_WS_RSA_PSS_SV_RIPEMD160_BUFFERLENGTH + sizeof(eslt_Length)))
#define ESL_WS_RSA_PSS_SV_RIPEMD160_DB_BUFFER(ByteSizeOfBuffer)       (ACT_ALIGN (ESL_WS_RSA_PSS_SV_RIPEMD160_BUFFER + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_PSS_SV_RIPEMD160_WS_RIPEMD160(ByteSizeOfBuffer)    (ACT_ALIGN (ESL_WS_RSA_PSS_SV_RIPEMD160_DB_BUFFER(ByteSizeOfBuffer) + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_PSS_SV_RIPEMD160_WS_RSA_PRIM(ByteSizeOfBuffer)     (ACT_ALIGN (ESL_WS_RSA_PSS_SV_RIPEMD160_WS_RIPEMD160(ByteSizeOfBuffer) + sizeof(eslt_WorkSpaceRIPEMD160)))
#define ESL_SIZEOF_WS_RSA_PSS_SV_RIPEMD160_OVERHEAD(ByteSizeOfBuffer) (ESL_WS_RSA_PSS_SV_RIPEMD160_WS_RSA_PRIM(ByteSizeOfBuffer))
#define ESL_SIZEOF_WS_RSA_PSS_SV_RIPEMD160_OVERHEAD_1024              (sizeof(eslt_WorkSpaceHeader) + sizeof(eslt_Length) + (2 * 128u) + sizeof(eslt_WorkSpaceRIPEMD160) + 4u*ACT_MAX_ALIGN_OFFSET)
#define ESL_SIZEOF_WS_RSA_PSS_SV_RIPEMD160_OVERHEAD_1536              (ESL_SIZEOF_WS_RSA_PSS_SV_RIPEMD160_OVERHEAD_1024 + (2u * 64u))
#define ESL_SIZEOF_WS_RSA_PSS_SV_RIPEMD160_OVERHEAD_2048              (ESL_SIZEOF_WS_RSA_PSS_SV_RIPEMD160_OVERHEAD_1024 + (2u * 128u))
#define ESL_SIZEOF_WS_RSA_PSS_SV_RIPEMD160_OVERHEAD_3072              (ESL_SIZEOF_WS_RSA_PSS_SV_RIPEMD160_OVERHEAD_1024 + (2u * 256u))
#define ESL_SIZEOF_WS_RSA_PSS_SV_RIPEMD160_OVERHEAD_4096              (ESL_SIZEOF_WS_RSA_PSS_SV_RIPEMD160_OVERHEAD_1024 + (2u * 384u))
#define ESL_SIZEOF_WS_RSA_PSS_SV_RIPEMD160_OVERHEAD_512               (ESL_SIZEOF_WS_RSA_PSS_SV_RIPEMD160_OVERHEAD_1024 - (2u * 32u))

/* RSA PSS core sig/ver workspace organisation (SHA256)
   WS_Header || BufferLength || 2 x Buffer (RSA result, DB and temporary hash value) || WS_SHA256 (inkl. WS_SHA256_HEADER) || WS_RSA_PRIM (inkl. WS_RSA_PRIM_Header) */
#define ESL_WS_RSA_PSS_SV_SHA256_BUFFERLENGTH                      (ACT_ALIGN (sizeof(eslt_WorkSpaceHeader)))
#define ESL_WS_RSA_PSS_SV_SHA256_BUFFER                            (ACT_ALIGN (ESL_WS_RSA_PSS_SV_SHA256_BUFFERLENGTH + sizeof(eslt_Length)))
#define ESL_WS_RSA_PSS_SV_SHA256_DB_BUFFER(ByteSizeOfBuffer)       (ACT_ALIGN (ESL_WS_RSA_PSS_SV_SHA256_BUFFER + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_PSS_SV_SHA256_WS_SHA256(ByteSizeOfBuffer)       (ACT_ALIGN (ESL_WS_RSA_PSS_SV_SHA256_DB_BUFFER(ByteSizeOfBuffer) + (ByteSizeOfBuffer)))
#define ESL_WS_RSA_PSS_SV_SHA256_WS_RSA_PRIM(ByteSizeOfBuffer)     (ACT_ALIGN (ESL_WS_RSA_PSS_SV_SHA256_WS_SHA256(ByteSizeOfBuffer) + sizeof(eslt_WorkSpaceSHA256)))
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD(ByteSizeOfBuffer) (ESL_WS_RSA_PSS_SV_SHA256_WS_RSA_PRIM(ByteSizeOfBuffer))
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_1024              (sizeof(eslt_WorkSpaceHeader) + sizeof(eslt_Length) + (2 * 128u) + sizeof(eslt_WorkSpaceSHA256) + 4u*ACT_MAX_ALIGN_OFFSET)
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_1536              (ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_1024 + (2u * 64u))
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_2048              (ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_1024 + (2u * 128u))
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_3072              (ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_1024 + (2u * 256u))
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_4096              (ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_1024 + (2u * 384u))
#define ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_512               (ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_1024 - (2u * 32u))

/* RSA PSS core hash overhead ( NOTE: must be MAX(SHA1_OVERHEAD, SHA256_OVERHEAD, RIPEMD160_OVERHEAD) ) */
#define ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_512    (ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_512)
#define ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_1024   (ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_1024)
#define ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_1536   (ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_1536)
#define ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_2048   (ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_2048)
#define ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_3072   (ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_3072)
#define ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_4096   (ESL_SIZEOF_WS_RSA_PSS_SV_SHA256_OVERHEAD_4096)
/* =============================================================================
   = RSA primitive work space sizes
   ============================================================================= */

/* NOTE: All CRT size values assume:            p_bits, q_bits <= n_bits + 32 */

/* RSA PRIM 512 */
#define ESL_SIZEOF_WS_RSA_ENC_PRIM_512          ESL_SIZEOF_WS_RSA_PUB_512
#define ESL_SIZEOF_WS_RSA_SIG_PRIM_512          ESL_SIZEOF_WS_RSA_PRIV_512
/* RSA PRIM 1k enc/dec */
#define ESL_SIZEOF_WS_RSA_ENC_PRIM_1024         ESL_SIZEOF_WS_RSA_PUB_1024
#define ESL_SIZEOF_WS_RSA_DEC_PRIM_1024         ESL_SIZEOF_WS_RSA_PRIV_1024
#define ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_1024     ESL_SIZEOF_WS_RSA_PRIV_CRT_1024
/* RSA PRIM 1k sig/ver */
#define ESL_SIZEOF_WS_RSA_SIG_PRIM_1024         ESL_SIZEOF_WS_RSA_PRIV_1024
#define ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_1024     ESL_SIZEOF_WS_RSA_PRIV_CRT_1024
#define ESL_SIZEOF_WS_RSA_VER_PRIM_1024         ESL_SIZEOF_WS_RSA_PUB_1024
/* RSA PRIM 1k enc/dec/sig/ver */
#define ESL_SIZEOF_WS_RSA_PRIM_1024             ESL_SIZEOF_WS_RSA_PUB_1024

/* RSA PRIM 1.5k enc/dec */
#define ESL_SIZEOF_WS_RSA_ENC_PRIM_1536         ESL_SIZEOF_WS_RSA_PUB_1536
#define ESL_SIZEOF_WS_RSA_DEC_PRIM_1536         ESL_SIZEOF_WS_RSA_PRIV_1536
#define ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_1536     ESL_SIZEOF_WS_RSA_PRIV_CRT_1536
/* RSA PRIM 1.5k sig/ver */
#define ESL_SIZEOF_WS_RSA_SIG_PRIM_1536         ESL_SIZEOF_WS_RSA_PRIV_1536
#define ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_1536     ESL_SIZEOF_WS_RSA_PRIV_CRT_1536
#define ESL_SIZEOF_WS_RSA_VER_PRIM_1536         ESL_SIZEOF_WS_RSA_PUB_1536
/* RSA PRIM 1.5k enc/dec/sig/ver */
#define ESL_SIZEOF_WS_RSA_PRIM_1536             ESL_SIZEOF_WS_RSA_PUB_1536

/* RSA PRIM 2k enc/dec */
#define ESL_SIZEOF_WS_RSA_ENC_PRIM_2048         ESL_SIZEOF_WS_RSA_PUB_2048
#define ESL_SIZEOF_WS_RSA_DEC_PRIM_2048         ESL_SIZEOF_WS_RSA_PRIV_2048
#define ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_2048     ESL_SIZEOF_WS_RSA_PRIV_CRT_2048
/* RSA PRIM 2k sig/ver */
#define ESL_SIZEOF_WS_RSA_SIG_PRIM_2048         ESL_SIZEOF_WS_RSA_PRIV_2048
#define ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_2048     ESL_SIZEOF_WS_RSA_PRIV_CRT_2048
#define ESL_SIZEOF_WS_RSA_VER_PRIM_2048         ESL_SIZEOF_WS_RSA_PUB_2048
/* RSA PRIM 2k enc/dec/sig/ver */
#define ESL_SIZEOF_WS_RSA_PRIM_2048             ESL_SIZEOF_WS_RSA_PUB_2048

/* RSA PRIM 3k enc/dec */
#define ESL_SIZEOF_WS_RSA_ENC_PRIM_3072         ESL_SIZEOF_WS_RSA_PUB_3072
#define ESL_SIZEOF_WS_RSA_DEC_PRIM_3072         ESL_SIZEOF_WS_RSA_PRIV_3072
#define ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_3072     ESL_SIZEOF_WS_RSA_PRIV_CRT_3072
/* RSA PRIM 3k sig/ver */
#define ESL_SIZEOF_WS_RSA_SIG_PRIM_3072         ESL_SIZEOF_WS_RSA_PRIV_3072
#define ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_3072     ESL_SIZEOF_WS_RSA_PRIV_CRT_3072
#define ESL_SIZEOF_WS_RSA_VER_PRIM_3072         ESL_SIZEOF_WS_RSA_PUB_3072
/* RSA PRIM 3k enc/dec/sig/ver */
#define ESL_SIZEOF_WS_RSA_PRIM_3072             ESL_SIZEOF_WS_RSA_PUB_3072

/* RSA PRIM 4k enc/dec */
#define ESL_SIZEOF_WS_RSA_ENC_PRIM_4096         ESL_SIZEOF_WS_RSA_PUB_4096
#define ESL_SIZEOF_WS_RSA_DEC_PRIM_4096         ESL_SIZEOF_WS_RSA_PRIV_4096
#define ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_4096     ESL_SIZEOF_WS_RSA_PRIV_CRT_4096
/* RSA PRIM 4k sig/ver */
#define ESL_SIZEOF_WS_RSA_SIG_PRIM_4096         ESL_SIZEOF_WS_RSA_PRIV_4096
#define ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_4096     ESL_SIZEOF_WS_RSA_PRIV_CRT_4096
#define ESL_SIZEOF_WS_RSA_VER_PRIM_4096         ESL_SIZEOF_WS_RSA_PUB_4096
/* RSA PRIM 4k enc/dec/sig/ver */
#define ESL_SIZEOF_WS_RSA_PRIM_4096             ESL_SIZEOF_WS_RSA_PUB_4096

#if (ESL_RSA_KEYSIZE == 4096)
/* RSA PRIM enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC_PRIM          ESL_SIZEOF_WS_RSA_ENC_PRIM_4096
# define ESL_MAXSIZEOF_WS_RSA_DEC_PRIM          ESL_SIZEOF_WS_RSA_DEC_PRIM_4096
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC_PRIM      ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_4096
/* RSA PRIM sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG_PRIM          ESL_SIZEOF_WS_RSA_SIG_PRIM_4096
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG_PRIM      ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_4096
# define ESL_MAXSIZEOF_WS_RSA_VER_PRIM          ESL_SIZEOF_WS_RSA_VER_PRIM_4096
/* RSA PRIM enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PRIM              ESL_SIZEOF_WS_RSA_PRIM_4096
#endif

#if (ESL_RSA_KEYSIZE == 3072)
/* RSA PRIM enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC_PRIM          ESL_SIZEOF_WS_RSA_ENC_PRIM_3072
# define ESL_MAXSIZEOF_WS_RSA_DEC_PRIM          ESL_SIZEOF_WS_RSA_DEC_PRIM_3072
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC_PRIM      ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_3072
/* RSA PRIM sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG_PRIM          ESL_SIZEOF_WS_RSA_SIG_PRIM_3072
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG_PRIM      ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_3072
# define ESL_MAXSIZEOF_WS_RSA_VER_PRIM          ESL_SIZEOF_WS_RSA_VER_PRIM_3072
/* RSA PRIM enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PRIM              ESL_SIZEOF_WS_RSA_PRIM_3072
#endif

#if (ESL_RSA_KEYSIZE == 2048)
/* RSA PRIM enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC_PRIM          ESL_SIZEOF_WS_RSA_ENC_PRIM_2048
# define ESL_MAXSIZEOF_WS_RSA_DEC_PRIM          ESL_SIZEOF_WS_RSA_DEC_PRIM_2048
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC_PRIM      ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_2048
/* RSA PRIM sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG_PRIM          ESL_SIZEOF_WS_RSA_SIG_PRIM_2048
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG_PRIM      ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_2048
# define ESL_MAXSIZEOF_WS_RSA_VER_PRIM          ESL_SIZEOF_WS_RSA_VER_PRIM_2048
/* RSA PRIM enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PRIM              ESL_SIZEOF_WS_RSA_PRIM_2048
#endif

#if (ESL_RSA_KEYSIZE == 1536)
/* RSA PRIM enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC_PRIM          ESL_SIZEOF_WS_RSA_ENC_PRIM_1536
# define ESL_MAXSIZEOF_WS_RSA_DEC_PRIM          ESL_SIZEOF_WS_RSA_DEC_PRIM_1536
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC_PRIM      ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_1536
/* RSA PRIM sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG_PRIM          ESL_SIZEOF_WS_RSA_SIG_PRIM_1536
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG_PRIM      ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_1536
# define ESL_MAXSIZEOF_WS_RSA_VER_PRIM          ESL_SIZEOF_WS_RSA_VER_PRIM_1536
/* RSA PRIM enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PRIM              ESL_SIZEOF_WS_RSA_PRIM_1536
#endif

#if (ESL_RSA_KEYSIZE == 1024)
/* RSA PRIM enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC_PRIM          ESL_SIZEOF_WS_RSA_ENC_PRIM_1024
# define ESL_MAXSIZEOF_WS_RSA_DEC_PRIM          ESL_SIZEOF_WS_RSA_DEC_PRIM_1024
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC_PRIM      ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_1024
/* RSA PRIM sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG_PRIM          ESL_SIZEOF_WS_RSA_SIG_PRIM_1024
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG_PRIM      ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_1024
# define ESL_MAXSIZEOF_WS_RSA_VER_PRIM          ESL_SIZEOF_WS_RSA_VER_PRIM_1024
/* RSA PRIM enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PRIM              ESL_SIZEOF_WS_RSA_PRIM_1024
#endif

#if (ESL_RSA_KEYSIZE == 512)
/* RSA PRIM enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC_PRIM          ESL_SIZEOF_WS_RSA_ENC_PRIM_512
# define ESL_MAXSIZEOF_WS_RSA_DEC_PRIM          ESL_SIZEOF_WS_RSA_DEC_PRIM_512
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC_PRIM      ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_512
/* RSA PRIM sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG_PRIM          ESL_SIZEOF_WS_RSA_SIG_PRIM_512
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG_PRIM      ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_512
# define ESL_MAXSIZEOF_WS_RSA_VER_PRIM          ESL_SIZEOF_WS_RSA_VER_PRIM_512
/* RSA PRIM enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PRIM              ESL_SIZEOF_WS_RSA_PRIM_512
#endif

#if !defined(ESL_MAXSIZEOF_WS_RSA_ENC_PRIM)
/* RSA PRIM enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC_PRIM          ESL_SIZEOF_WS_RSA_ENC_PRIM_4096
# define ESL_MAXSIZEOF_WS_RSA_DEC_PRIM          ESL_SIZEOF_WS_RSA_DEC_PRIM_4096
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC_PRIM      ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_4096
/* RSA PRIM sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG_PRIM          ESL_SIZEOF_WS_RSA_SIG_PRIM_4096
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG_PRIM      ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_4096
# define ESL_MAXSIZEOF_WS_RSA_VER_PRIM          ESL_SIZEOF_WS_RSA_VER_PRIM_4096
/* RSA PRIM enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PRIM              ESL_SIZEOF_WS_RSA_PRIM_4096
#endif

/* =============================================================================
   = RSA PKCS#1 V1.5 algorithm work space sizes
   ============================================================================= */

/* NOTE: All CRT size values assume:            p_bits, q_bits <= n_bits + 32 */

/* RSA V15 512 */
#define ESL_SIZEOF_WS_RSA_ENC_512               (ACT_ALIGN (ESL_SIZEOF_WS_RSA_ENC_PRIM_512      + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_512))
#define ESL_SIZEOF_WS_RSA_SIG_512               (ACT_ALIGN (ESL_SIZEOF_WS_RSA_SIG_PRIM_512      + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_512))

/* RSA V15 1k enc/dec */
#define ESL_SIZEOF_WS_RSA_ENC_1024              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_ENC_PRIM_1024     + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1024))
#define ESL_SIZEOF_WS_RSA_DEC_1024              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_DEC_PRIM_1024     + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1024))
#define ESL_SIZEOF_WS_RSA_CRT_DEC_1024          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_1024 + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1024))
/* RSA V15 1k sig/ver */
#define ESL_SIZEOF_WS_RSA_SIG_1024              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_SIG_PRIM_1024     + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_1024))
#define ESL_SIZEOF_WS_RSA_CRT_SIG_1024          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_1024 + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_1024))
#define ESL_SIZEOF_WS_RSA_VER_1024              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_VER_PRIM_1024     + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_1024))
/* RSA V15 1k enc/dec/sig/ver */
#define ESL_SIZEOF_WS_RSA_V15_1024              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_1024         + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_1024))

/* RSA V15 1.5k enc/dec */
#define ESL_SIZEOF_WS_RSA_ENC_1536              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_ENC_PRIM_1536     + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1536))
#define ESL_SIZEOF_WS_RSA_DEC_1536              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_DEC_PRIM_1536     + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1536))
#define ESL_SIZEOF_WS_RSA_CRT_DEC_1536          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_1536 + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_1536))
/* RSA V15 1.5k sig/ver */
#define ESL_SIZEOF_WS_RSA_SIG_1536              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_SIG_PRIM_1536     + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_1536))
#define ESL_SIZEOF_WS_RSA_CRT_SIG_1536          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_1536 + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_1536))
#define ESL_SIZEOF_WS_RSA_VER_1536              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_VER_PRIM_1536     + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_1536))
/* RSA V15 1.5k enc/dec/sig/ver */
#define ESL_SIZEOF_WS_RSA_V15_1536              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_1536         + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_1536))

/* RSA V15 2k enc/dec */
#define ESL_SIZEOF_WS_RSA_ENC_2048              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_ENC_PRIM_2048     + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_2048))
#define ESL_SIZEOF_WS_RSA_DEC_2048              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_DEC_PRIM_2048     + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_2048))
#define ESL_SIZEOF_WS_RSA_CRT_DEC_2048          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_2048 + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_2048))
/* RSA V15 2k sig/ver */
#define ESL_SIZEOF_WS_RSA_SIG_2048              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_SIG_PRIM_2048     + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_2048))
#define ESL_SIZEOF_WS_RSA_CRT_SIG_2048          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_2048 + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_2048))
#define ESL_SIZEOF_WS_RSA_VER_2048              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_VER_PRIM_2048     + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_2048))
/* RSA V15 2k enc/dec/sig/ver */
#define ESL_SIZEOF_WS_RSA_V15_2048              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_2048         + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_2048))

/* RSA V15 3k enc/dec */
#define ESL_SIZEOF_WS_RSA_ENC_3072              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_ENC_PRIM_3072     + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_3072))
#define ESL_SIZEOF_WS_RSA_DEC_3072              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_DEC_PRIM_3072     + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_3072))
#define ESL_SIZEOF_WS_RSA_CRT_DEC_3072          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_3072 + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_3072))
/* RSA V15 2k sig/ver */
#define ESL_SIZEOF_WS_RSA_SIG_3072              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_SIG_PRIM_3072     + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_3072))
#define ESL_SIZEOF_WS_RSA_CRT_SIG_3072          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_3072 + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_3072))
#define ESL_SIZEOF_WS_RSA_VER_3072              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_VER_PRIM_3072     + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_3072))
/* RSA V15 2k enc/dec/sig/ver */
#define ESL_SIZEOF_WS_RSA_V15_3072              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_3072         + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_3072))

/* RSA V15 3k enc/dec */
#define ESL_SIZEOF_WS_RSA_ENC_4096              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_ENC_PRIM_4096     + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_4096))
#define ESL_SIZEOF_WS_RSA_DEC_4096              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_DEC_PRIM_4096     + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_4096))
#define ESL_SIZEOF_WS_RSA_CRT_DEC_4096          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_4096 + ESL_SIZEOF_WS_RSA_V15_ED_V15OVERHEAD_4096))
/* RSA V15 2k sig/ver */
#define ESL_SIZEOF_WS_RSA_SIG_4096              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_SIG_PRIM_4096     + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_4096))
#define ESL_SIZEOF_WS_RSA_CRT_SIG_4096          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_4096 + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_4096))
#define ESL_SIZEOF_WS_RSA_VER_4096              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_VER_PRIM_4096     + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_4096))
/* RSA V15 2k enc/dec/sig/ver */
#define ESL_SIZEOF_WS_RSA_V15_4096              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_4096         + ESL_SIZEOF_WS_RSA_V15_SV_HASH_OVERHEAD_4096))

#if (ESL_RSA_KEYSIZE == 4096)
/* RSA V15 enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC               ESL_SIZEOF_WS_RSA_ENC_4096
# define ESL_MAXSIZEOF_WS_RSA_DEC               ESL_SIZEOF_WS_RSA_DEC_4096
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC           ESL_SIZEOF_WS_RSA_CRT_DEC_4096
/* RSA V15 sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG               ESL_SIZEOF_WS_RSA_SIG_4096
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG           ESL_SIZEOF_WS_RSA_CRT_SIG_4096
# define ESL_MAXSIZEOF_WS_RSA_VER               ESL_SIZEOF_WS_RSA_VER_4096
/* RSA V15 enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_V15               ESL_SIZEOF_WS_RSA_V15_4096
#endif

#if (ESL_RSA_KEYSIZE == 3072)
/* RSA V15 enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC               ESL_SIZEOF_WS_RSA_ENC_3072
# define ESL_MAXSIZEOF_WS_RSA_DEC               ESL_SIZEOF_WS_RSA_DEC_3072
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC           ESL_SIZEOF_WS_RSA_CRT_DEC_3072
/* RSA V15 sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG               ESL_SIZEOF_WS_RSA_SIG_3072
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG           ESL_SIZEOF_WS_RSA_CRT_SIG_3072
# define ESL_MAXSIZEOF_WS_RSA_VER               ESL_SIZEOF_WS_RSA_VER_3072
/* RSA V15 enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_V15               ESL_SIZEOF_WS_RSA_V15_3072
#endif

#if (ESL_RSA_KEYSIZE == 2048)
/* RSA V15 enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC               ESL_SIZEOF_WS_RSA_ENC_2048
# define ESL_MAXSIZEOF_WS_RSA_DEC               ESL_SIZEOF_WS_RSA_DEC_2048
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC           ESL_SIZEOF_WS_RSA_CRT_DEC_2048
/* RSA V15 sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG               ESL_SIZEOF_WS_RSA_SIG_2048
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG           ESL_SIZEOF_WS_RSA_CRT_SIG_2048
# define ESL_MAXSIZEOF_WS_RSA_VER               ESL_SIZEOF_WS_RSA_VER_2048
/* RSA V15 enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_V15               ESL_SIZEOF_WS_RSA_V15_2048
#endif

#if (ESL_RSA_KEYSIZE == 1536)
/* RSA V15 enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC               ESL_SIZEOF_WS_RSA_ENC_1536
# define ESL_MAXSIZEOF_WS_RSA_DEC               ESL_SIZEOF_WS_RSA_DEC_1536
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC           ESL_SIZEOF_WS_RSA_CRT_DEC_1536
/* RSA V15 sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG               ESL_SIZEOF_WS_RSA_SIG_1536
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG           ESL_SIZEOF_WS_RSA_CRT_SIG_1536
# define ESL_MAXSIZEOF_WS_RSA_VER               ESL_SIZEOF_WS_RSA_VER_1536
/* RSA V15 enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_V15               ESL_SIZEOF_WS_RSA_V15_1536
#endif

#if (ESL_RSA_KEYSIZE == 1024)
/* RSA V15 enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC               ESL_SIZEOF_WS_RSA_ENC_1024
# define ESL_MAXSIZEOF_WS_RSA_DEC               ESL_SIZEOF_WS_RSA_DEC_1024
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC           ESL_SIZEOF_WS_RSA_CRT_DEC_1024
/* RSA V15 sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG               ESL_SIZEOF_WS_RSA_SIG_1024
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG           ESL_SIZEOF_WS_RSA_CRT_SIG_1024
# define ESL_MAXSIZEOF_WS_RSA_VER               ESL_SIZEOF_WS_RSA_VER_1024
/* RSA V15 enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_V15               ESL_SIZEOF_WS_RSA_V15_1024
#endif

#if (ESL_RSA_KEYSIZE == 512)
/* RSA V15 enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC               ESL_SIZEOF_WS_RSA_ENC_512
# define ESL_MAXSIZEOF_WS_RSA_DEC               ESL_SIZEOF_WS_RSA_DEC_512
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC           ESL_SIZEOF_WS_RSA_CRT_DEC_512
/* RSA V15 sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG               ESL_SIZEOF_WS_RSA_SIG_512
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG           ESL_SIZEOF_WS_RSA_CRT_SIG_512
# define ESL_MAXSIZEOF_WS_RSA_VER               ESL_SIZEOF_WS_RSA_VER_512
/* RSA V15 enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_V15               ESL_SIZEOF_WS_RSA_V15_512
#endif

#if !defined(ESL_MAXSIZEOF_WS_RSA_ENC)
/* RSA V15 enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_ENC               ESL_SIZEOF_WS_RSA_ENC_4096
# define ESL_MAXSIZEOF_WS_RSA_DEC               ESL_SIZEOF_WS_RSA_DEC_4096
# define ESL_MAXSIZEOF_WS_RSA_CRT_DEC           ESL_SIZEOF_WS_RSA_CRT_DEC_4096
/* RSA V15 sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_SIG               ESL_SIZEOF_WS_RSA_SIG_4096
# define ESL_MAXSIZEOF_WS_RSA_CRT_SIG           ESL_SIZEOF_WS_RSA_CRT_SIG_4096
# define ESL_MAXSIZEOF_WS_RSA_VER               ESL_SIZEOF_WS_RSA_VER_4096
/* RSA V15 enc/dec/sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_V15               ESL_SIZEOF_WS_RSA_V15_4096
#endif

/* =============================================================================
   = RSA OAEP algorithm work space sizes
   ============================================================================= */

/* NOTE: All CRT size values assume:            p_bits, q_bits <= n_bits + 32 */

/* RSA OAEP 512 */
#define ESL_SIZEOF_WS_RSA_OAEP_ENC_512          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_ENC_PRIM_512      + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_512))

/* RSA OAEP 1k enc/dec */
#define ESL_SIZEOF_WS_RSA_OAEP_ENC_1024         (ACT_ALIGN (ESL_SIZEOF_WS_RSA_ENC_PRIM_1024     + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_1024))
#define ESL_SIZEOF_WS_RSA_OAEP_DEC_1024         (ACT_ALIGN (ESL_SIZEOF_WS_RSA_DEC_PRIM_1024     + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_1024))
#define ESL_SIZEOF_WS_RSA_CRT_OAEP_DEC_1024     (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_1024 + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_1024))
/* RSA OAEP 1k enc/dec */
#define ESL_SIZEOF_WS_RSA_OAEP_1024             (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_1024         + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_1024))

/* RSA OAEP 1.5k enc/dec */
#define ESL_SIZEOF_WS_RSA_OAEP_ENC_1536         (ACT_ALIGN (ESL_SIZEOF_WS_RSA_ENC_PRIM_1536     + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_1536))
#define ESL_SIZEOF_WS_RSA_OAEP_DEC_1536         (ACT_ALIGN (ESL_SIZEOF_WS_RSA_DEC_PRIM_1536     + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_1536))
#define ESL_SIZEOF_WS_RSA_CRT_OAEP_DEC_1536     (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_1536 + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_1536))
/* RSA OAEP 1.5k enc/dec */
#define ESL_SIZEOF_WS_RSA_OAEP_1536             (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_1536         + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_1536))

/* RSA OAEP 2k enc/dec */
#define ESL_SIZEOF_WS_RSA_OAEP_ENC_2048         (ACT_ALIGN (ESL_SIZEOF_WS_RSA_ENC_PRIM_2048     + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_2048))
#define ESL_SIZEOF_WS_RSA_OAEP_DEC_2048         (ACT_ALIGN (ESL_SIZEOF_WS_RSA_DEC_PRIM_2048     + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_2048))
#define ESL_SIZEOF_WS_RSA_CRT_OAEP_DEC_2048     (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_2048 + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_2048))
/* RSA OAEP 2k enc/dec */
#define ESL_SIZEOF_WS_RSA_OAEP_2048             (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_2048         + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_2048))

/* RSA OAEP 3k enc/dec */
#define ESL_SIZEOF_WS_RSA_OAEP_ENC_3072         (ACT_ALIGN (ESL_SIZEOF_WS_RSA_ENC_PRIM_3072     + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_3072))
#define ESL_SIZEOF_WS_RSA_OAEP_DEC_3072         (ACT_ALIGN (ESL_SIZEOF_WS_RSA_DEC_PRIM_3072     + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_3072))
#define ESL_SIZEOF_WS_RSA_CRT_OAEP_DEC_3072     (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_3072 + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_3072))
/* RSA OAEP 2k enc/dec */
#define ESL_SIZEOF_WS_RSA_OAEP_3072             (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_3072         + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_3072))

/* RSA OAEP 3k enc/dec */
#define ESL_SIZEOF_WS_RSA_OAEP_ENC_4096         (ACT_ALIGN (ESL_SIZEOF_WS_RSA_ENC_PRIM_4096     + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_4096))
#define ESL_SIZEOF_WS_RSA_OAEP_DEC_4096         (ACT_ALIGN (ESL_SIZEOF_WS_RSA_DEC_PRIM_4096     + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_4096))
#define ESL_SIZEOF_WS_RSA_CRT_OAEP_DEC_4096     (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_DEC_PRIM_4096 + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_4096))
/* RSA OAEP 2k enc/dec */
#define ESL_SIZEOF_WS_RSA_OAEP_4096             (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_4096         + ESL_SIZEOF_WS_RSA_OAEP_ED_HASH_OVERHEAD_4096))

#if (ESL_RSA_KEYSIZE == 4096)
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP_ENC          ESL_SIZEOF_WS_RSA_OAEP_ENC_4096
# define ESL_MAXSIZEOF_WS_RSA_OAEP_DEC          ESL_SIZEOF_WS_RSA_OAEP_DEC_4096
# define ESL_MAXSIZEOF_WS_RSA_CRT_OAEP_DEC      ESL_SIZEOF_WS_RSA_CRT_OAEP_DEC_4096
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP              ESL_SIZEOF_WS_RSA_OAEP_4096
#endif

#if (ESL_RSA_KEYSIZE == 3072)
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP_ENC          ESL_SIZEOF_WS_RSA_OAEP_ENC_3072
# define ESL_MAXSIZEOF_WS_RSA_OAEP_DEC          ESL_SIZEOF_WS_RSA_OAEP_DEC_3072
# define ESL_MAXSIZEOF_WS_RSA_CRT_OAEP_DEC      ESL_SIZEOF_WS_RSA_CRT_OAEP_DEC_3072
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP              ESL_SIZEOF_WS_RSA_OAEP_3072
#endif

#if (ESL_RSA_KEYSIZE == 2048)
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP_ENC          ESL_SIZEOF_WS_RSA_OAEP_ENC_2048
# define ESL_MAXSIZEOF_WS_RSA_OAEP_DEC          ESL_SIZEOF_WS_RSA_OAEP_DEC_2048
# define ESL_MAXSIZEOF_WS_RSA_CRT_OAEP_DEC      ESL_SIZEOF_WS_RSA_CRT_OAEP_DEC_2048
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP              ESL_SIZEOF_WS_RSA_OAEP_2048
#endif

#if (ESL_RSA_KEYSIZE == 1536)
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP_ENC          ESL_SIZEOF_WS_RSA_OAEP_ENC_1536
# define ESL_MAXSIZEOF_WS_RSA_OAEP_DEC          ESL_SIZEOF_WS_RSA_OAEP_DEC_1536
# define ESL_MAXSIZEOF_WS_RSA_CRT_OAEP_DEC      ESL_SIZEOF_WS_RSA_CRT_OAEP_DEC_1536
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP              ESL_SIZEOF_WS_RSA_OAEP_1536
#endif

#if (ESL_RSA_KEYSIZE == 1024)
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP_ENC          ESL_SIZEOF_WS_RSA_OAEP_ENC_1024
# define ESL_MAXSIZEOF_WS_RSA_OAEP_DEC          ESL_SIZEOF_WS_RSA_OAEP_DEC_1024
# define ESL_MAXSIZEOF_WS_RSA_CRT_OAEP_DEC      ESL_SIZEOF_WS_RSA_CRT_OAEP_DEC_1024
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP              ESL_SIZEOF_WS_RSA_OAEP_1024
#endif

#if (ESL_RSA_KEYSIZE == 512)
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP_ENC          ESL_SIZEOF_WS_RSA_OAEP_ENC_512
# define ESL_MAXSIZEOF_WS_RSA_OAEP_DEC          ESL_SIZEOF_WS_RSA_OAEP_DEC_512
# define ESL_MAXSIZEOF_WS_RSA_CRT_OAEP_DEC      ESL_SIZEOF_WS_RSA_CRT_OAEP_DEC_512
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP              ESL_SIZEOF_WS_RSA_OAEP_512
#endif

#if !defined(ESL_MAXSIZEOF_WS_RSA_OAEP_ENC)
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP_ENC          ESL_SIZEOF_WS_RSA_OAEP_ENC_4096
# define ESL_MAXSIZEOF_WS_RSA_OAEP_DEC          ESL_SIZEOF_WS_RSA_OAEP_DEC_4096
# define ESL_MAXSIZEOF_WS_RSA_CRT_OAEP_DEC      ESL_SIZEOF_WS_RSA_CRT_OAEP_DEC_4096
/* RSA OAEP enc/dec */
# define ESL_MAXSIZEOF_WS_RSA_OAEP              ESL_SIZEOF_WS_RSA_OAEP_4096
#endif

/* =============================================================================
   = RSA PKCS#1 PSS algorithm work space sizes
   ============================================================================= */

/* NOTE: All CRT size values assume:            p_bits, q_bits <= n_bits + 32 */

/* RSA PSS 512 */
#define ESL_SIZEOF_WS_RSA_PSS_SIG_512           (ACT_ALIGN (ESL_SIZEOF_WS_RSA_SIG_PRIM_512      + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_512))

/* RSA PSS 1k sig/ver */
#define ESL_SIZEOF_WS_RSA_PSS_SIG_1024          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_SIG_PRIM_1024     + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_1024))
#define ESL_SIZEOF_WS_RSA_PSS_CRT_SIG_1024      (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_1024 + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_1024))
#define ESL_SIZEOF_WS_RSA_PSS_VER_1024          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_VER_PRIM_1024     + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_1024))
#define ESL_SIZEOF_WS_RSA_PSS_1024              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_1024         + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_1024))

/* RSA PSS 1.5k sig/ver */
#define ESL_SIZEOF_WS_RSA_PSS_SIG_1536          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_SIG_PRIM_1536     + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_1536))
#define ESL_SIZEOF_WS_RSA_PSS_CRT_SIG_1536      (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_1536 + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_1536))
#define ESL_SIZEOF_WS_RSA_PSS_VER_1536          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_VER_PRIM_1536     + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_1536))
#define ESL_SIZEOF_WS_RSA_PSS_1536              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_1536         + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_1536))

/* RSA PSS 2k sig/ver */
#define ESL_SIZEOF_WS_RSA_PSS_SIG_2048          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_SIG_PRIM_2048     + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_2048))
#define ESL_SIZEOF_WS_RSA_PSS_CRT_SIG_2048      (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_2048 + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_2048))
#define ESL_SIZEOF_WS_RSA_PSS_VER_2048          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_VER_PRIM_2048     + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_2048))
#define ESL_SIZEOF_WS_RSA_PSS_2048              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_2048         + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_2048))

/* RSA PSS 3k sig/ver */
#define ESL_SIZEOF_WS_RSA_PSS_SIG_3072          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_SIG_PRIM_3072     + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_3072))
#define ESL_SIZEOF_WS_RSA_PSS_CRT_SIG_3072      (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_3072 + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_3072))
#define ESL_SIZEOF_WS_RSA_PSS_VER_3072          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_VER_PRIM_3072     + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_3072))
#define ESL_SIZEOF_WS_RSA_PSS_3072              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_3072         + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_3072))

/* RSA PSS 4k sig/ver */
#define ESL_SIZEOF_WS_RSA_PSS_SIG_4096          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_SIG_PRIM_4096     + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_4096))
#define ESL_SIZEOF_WS_RSA_PSS_CRT_SIG_4096      (ACT_ALIGN (ESL_SIZEOF_WS_RSA_CRT_SIG_PRIM_4096 + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_4096))
#define ESL_SIZEOF_WS_RSA_PSS_VER_4096          (ACT_ALIGN (ESL_SIZEOF_WS_RSA_VER_PRIM_4096     + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_4096))
#define ESL_SIZEOF_WS_RSA_PSS_4096              (ACT_ALIGN (ESL_SIZEOF_WS_RSA_PRIM_4096         + ESL_SIZEOF_WS_RSA_PSS_SV_HASH_OVERHEAD_4096))

#if (ESL_RSA_KEYSIZE == 4096)
/* RSA PSS sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PSS_SIG           ESL_SIZEOF_WS_RSA_PSS_SIG_4096
# define ESL_MAXSIZEOF_WS_RSA_PSS_CRT_SIG       ESL_SIZEOF_WS_RSA_PSS_CRT_SIG_4096
# define ESL_MAXSIZEOF_WS_RSA_PSS_VER           ESL_SIZEOF_WS_RSA_PSS_VER_4096
# define ESL_MAXSIZEOF_WS_RSA_PSS               ESL_SIZEOF_WS_RSA_PSS_4096
#endif

#if (ESL_RSA_KEYSIZE == 3072)
/* RSA PSS sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PSS_SIG           ESL_SIZEOF_WS_RSA_PSS_SIG_3072
# define ESL_MAXSIZEOF_WS_RSA_PSS_CRT_SIG       ESL_SIZEOF_WS_RSA_PSS_CRT_SIG_3072
# define ESL_MAXSIZEOF_WS_RSA_PSS_VER           ESL_SIZEOF_WS_RSA_PSS_VER_3072
# define ESL_MAXSIZEOF_WS_RSA_PSS               ESL_SIZEOF_WS_RSA_PSS_3072
#endif

#if (ESL_RSA_KEYSIZE == 2048)
/* RSA PSS sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PSS_SIG           ESL_SIZEOF_WS_RSA_PSS_SIG_2048
# define ESL_MAXSIZEOF_WS_RSA_PSS_CRT_SIG       ESL_SIZEOF_WS_RSA_PSS_CRT_SIG_2048
# define ESL_MAXSIZEOF_WS_RSA_PSS_VER           ESL_SIZEOF_WS_RSA_PSS_VER_2048
# define ESL_MAXSIZEOF_WS_RSA_PSS               ESL_SIZEOF_WS_RSA_PSS_2048
#endif

#if (ESL_RSA_KEYSIZE == 1536)
/* RSA PSS sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PSS_SIG           ESL_SIZEOF_WS_RSA_PSS_SIG_1536
# define ESL_MAXSIZEOF_WS_RSA_PSS_CRT_SIG       ESL_SIZEOF_WS_RSA_PSS_CRT_SIG_1536
# define ESL_MAXSIZEOF_WS_RSA_PSS_VER           ESL_SIZEOF_WS_RSA_PSS_VER_1536
# define ESL_MAXSIZEOF_WS_RSA_PSS               ESL_SIZEOF_WS_RSA_PSS_1536
#endif

#if (ESL_RSA_KEYSIZE == 1024)
/* RSA PSS sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PSS_SIG           ESL_SIZEOF_WS_RSA_PSS_SIG_1024
# define ESL_MAXSIZEOF_WS_RSA_PSS_CRT_SIG       ESL_SIZEOF_WS_RSA_PSS_CRT_SIG_1024
# define ESL_MAXSIZEOF_WS_RSA_PSS_VER           ESL_SIZEOF_WS_RSA_PSS_VER_1024
# define ESL_MAXSIZEOF_WS_RSA_PSS               ESL_SIZEOF_WS_RSA_PSS_1024
#endif

#if (ESL_RSA_KEYSIZE == 512)
/* RSA PSS sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PSS_SIG           ESL_SIZEOF_WS_RSA_PSS_SIG_512
# define ESL_MAXSIZEOF_WS_RSA_PSS_CRT_SIG       ESL_SIZEOF_WS_RSA_PSS_CRT_SIG_512
# define ESL_MAXSIZEOF_WS_RSA_PSS_VER           ESL_SIZEOF_WS_RSA_PSS_VER_512
#endif

#if !defined(ESL_MAXSIZEOF_WS_RSA_PSS_SIG)
/* RSA PSS sig/ver */
# define ESL_MAXSIZEOF_WS_RSA_PSS_SIG           ESL_SIZEOF_WS_RSA_PSS_SIG_4096
# define ESL_MAXSIZEOF_WS_RSA_PSS_CRT_SIG       ESL_SIZEOF_WS_RSA_PSS_CRT_SIG_4096
# define ESL_MAXSIZEOF_WS_RSA_PSS_VER           ESL_SIZEOF_WS_RSA_PSS_VER_4096
# define ESL_MAXSIZEOF_WS_RSA_PSS               ESL_SIZEOF_WS_RSA_PSS_4096
#endif

/* =============================================================================
   = EdDSA & ECDH workspace sizes
   ============================================================================= */
#define ESL_SIZEOF_WS_Ed25519                   (ESL_MINSIZEOF_WS_SHA512 + 2* ESL_SIZEOF_SHA512_DIGEST + ESL_SIZEOF_Ed25519_PUBLIC_KEY + 32u + 520u)
#define ESL_SIZEOF_WS_X25519                    (ESL_SIZEOF_X25519_PRIVATE_KEY + ESL_SIZEOF_X25519_PUBLIC_KEY + 520u)

/* =============================================================================
   = Workspace definitions
   ============================================================================= */

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsAES128[ESL_MAXSIZEOF_WS_AES128];
      }eslt_WorkSpaceAES128;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsAES128Block[ESL_MAXSIZEOF_WS_AES128BLOCK];
      }eslt_WorkSpaceAES128Block;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsAES192[ESL_MAXSIZEOF_WS_AES192];
      }eslt_WorkSpaceAES192;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsAES192Block[ESL_MAXSIZEOF_WS_AES192BLOCK];
      }eslt_WorkSpaceAES192Block;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsAES256[ESL_MAXSIZEOF_WS_AES256];
      }eslt_WorkSpaceAES256;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsAES256Block[ESL_MAXSIZEOF_WS_AES256BLOCK];
      }eslt_WorkSpaceAES256Block;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsDES[ESL_MAXSIZEOF_WS_DES];
      }eslt_WorkSpaceDES;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsDESBlock[ESL_MAXSIZEOF_WS_DESBLOCK];
      }eslt_WorkSpaceDESBlock;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsTDES[ESL_MAXSIZEOF_WS_TDES];
      }eslt_WorkSpaceTDES;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsTDESBlock[ESL_MAXSIZEOF_WS_TDESBLOCK];
      }eslt_WorkSpaceTDESBlock;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRC2[ESL_MAXSIZEOF_WS_RC2];
      }eslt_WorkSpaceRC2;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRC2Block[ESL_MAXSIZEOF_WS_RC2BLOCK];
      }eslt_WorkSpaceRC2Block;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsGCM[ESL_MAXSIZEOF_WS_GCM];
      }eslt_WorkSpaceGCM;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsGMAC[ESL_MAXSIZEOF_WS_GMAC];
      }eslt_WorkSpaceGMAC;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsSHA1[ESL_MAXSIZEOF_WS_SHA1];
      }eslt_WorkSpaceSHA1;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsSHA224 [ESL_MAXSIZEOF_WS_SHA224];
      }eslt_WorkSpaceSHA224;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsSHA256 [ESL_MAXSIZEOF_WS_SHA256];
      }eslt_WorkSpaceSHA256;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsSHA512_224 [ESL_MAXSIZEOF_WS_SHA512_224];
      }eslt_WorkSpaceSHA512_224;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsSHA512_256 [ESL_MAXSIZEOF_WS_SHA512_256];
      }eslt_WorkSpaceSHA512_256;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsSHA384 [ESL_MAXSIZEOF_WS_SHA384];
      }eslt_WorkSpaceSHA384;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsSHA512 [ESL_MAXSIZEOF_WS_SHA512];
      }eslt_WorkSpaceSHA512;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRIPEMD160[ESL_MAXSIZEOF_WS_RIPEMD160];
      }eslt_WorkSpaceRIPEMD160;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsMD5[ESL_MAXSIZEOF_WS_MD5];
      }eslt_WorkSpaceMD5;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsHMACSHA1[ESL_MAXSIZEOF_WS_HMACSHA1];
      }eslt_WorkSpaceHMACSHA1;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsHMACSHA256[ESL_MAXSIZEOF_WS_HMACSHA256];
      }eslt_WorkSpaceHMACSHA256;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsHMACRIPEMD160[ESL_MAXSIZEOF_WS_HMACRIPEMD160];
      }eslt_WorkSpaceHMACRIPEMD160;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsCMACAES[ESL_MAXSIZEOF_WS_CMACAES];
      }eslt_WorkSpaceCMACAES;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsSipHash[ESL_MAXSIZEOF_WS_SIPHASH];
      }eslt_WorkSpaceSipHash;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsFIPS186[ESL_MAXSIZEOF_WS_FIPS186];
      }eslt_WorkSpaceFIPS186;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsKDF2HMACSHA1[ESL_MAXSIZEOF_WS_KDF2HMACSHA1];
      }eslt_WorkSpaceKDF2HMACSHA1;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsKDFX963SHA1[ESL_MAXSIZEOF_WS_KDFX963SHA1];
      }eslt_WorkSpaceKDFX963SHA1;

/* EcP workSpace */
typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsEcP[ESL_MAXSIZEOF_WS_ECP];
      }eslt_WorkSpaceEcP;

/* RSA V15 workSpaces */
typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_ENC];
      }eslt_WorkSpaceRSAenc;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_DEC];
      }eslt_WorkSpaceRSAdec;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_CRT_DEC];
      }eslt_WorkSpaceRSACRTdec;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_SIG];
      }eslt_WorkSpaceRSAsig;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_CRT_SIG];
      }eslt_WorkSpaceRSACRTsig;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_VER];
      }eslt_WorkSpaceRSAver;

/* RSA OAEP workSpaces */
typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_OAEP_ENC];
      }eslt_WorkSpaceRSAOAEPenc;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_OAEP_DEC];
      }eslt_WorkSpaceRSAOAEPdec;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_CRT_OAEP_DEC];
      }eslt_WorkSpaceRSACRTOAEPdec;

/* RSA PSS workSpaces */
typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ ESL_MAXSIZEOF_WS_RSA_PSS_SIG];
      }eslt_WorkSpaceRSAPSSsig;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ ESL_MAXSIZEOF_WS_RSA_PSS_CRT_SIG];
      }eslt_WorkSpaceRSAPSSCRTsig;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ ESL_MAXSIZEOF_WS_RSA_PSS_VER];
      }eslt_WorkSpaceRSAPSSver;

/* RSA primitive workSpaces */
typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_ENC_PRIM];
      }eslt_WorkSpaceRSAenc_prim;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_DEC_PRIM];
      }eslt_WorkSpaceRSAdec_prim;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_CRT_DEC_PRIM];
      }eslt_WorkSpaceRSACRTdec_prim;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_SIG_PRIM];
      }eslt_WorkSpaceRSAsig_prim;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_CRT_SIG_PRIM];
      }eslt_WorkSpaceRSACRTsig_prim;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsRSA[ESL_MAXSIZEOF_WS_RSA_VER_PRIM];
      }eslt_WorkSpaceRSAver_prim;

/* EdDSA & ECDH workSpaces */
typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsEd25519 [ESL_SIZEOF_WS_Ed25519];
      } eslt_WorkSpaceEd25519;

typedef struct {
              eslt_WorkSpaceHeader header;
              eslt_Byte wsX25519 [ESL_SIZEOF_WS_X25519];
      } eslt_WorkSpaceX25519;

#endif /* __ESLib_t_H__ */

