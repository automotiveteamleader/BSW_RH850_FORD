/****************************************************************************
 ** Main author: UBR                     Creation date: 10/17/03
 ** $Author:: sst                      $ $JustDate:: 02/09/04             $
 ** $Workfile:: actITypes.h            $ $Revision:: 1061                 $
 ** $NoKeywords::                                                         $
 **
 **
 ** \copyright(cv cryptovision GmbH, 1999 - 2005                          )
 **
 ** \version(1.0 (beta )                                                  )
 ***************************************************************************/

/****************************************************************************
 **
 **     Part of the actCLibrary
 **
 **     Layer: User Module - Interface
 **
 ***************************************************************************/

/****************************************************************************
 **
 ** This file contains: Basic type defintions.
 **
 ** constants:
 **   actOK
 **   actEXCEPTION_NULL
 **   actEXCEPTION_CURVE
 **   actEXCEPTION_PRIVKEY
 **   actEXCEPTION_POINT
 **   actEXCEPTION_PUBKEY
 **   actEXCEPTION_LENGTH
 **   actEXCEPTION_ALGOID
 **   actEXCEPTION_PADDING
 **   actEXCEPTION_INPUT_LENGTH
 **   actEXCEPTION_MEMORY
 **   actVERIFICATION_FAILED
 **
 ** types:
 **   actU8, actU16, actU32
 **   actRETURNCODE
 **
 ** macros:
 **
 ** functions:
 **
 ***************************************************************************/

#ifndef ACTITYPES_H
#define ACTITYPES_H

#include "actPlatformTypes.h"

/****************************************************************************
 ** Types and constants
 ***************************************************************************/

/* basic unsigned int types */
typedef actPlatformUint8 actU8;
typedef actPlatformUint16 actU16;
typedef actPlatformUint32 actU32;
#ifdef  ACT_PLATFORM_UINT64_AVAILABLE
typedef actPlatformUint64 actU64;
#endif

/* Pointer to key data, typically located in ROM (e.g. RSA keys) */
/* Pointer to key data, typically located in ROM (e.g. RSA keys) */
CRYPTOCV_P2ROMCONST_TYPE( CRYPTOCV_NONE, actU8 ) actPKey;

/* Pointer to byte(s) located in ROM, e.g. digest information */
CRYPTOCV_P2ROMCONST_TYPE( CRYPTOCV_NONE, actU8 ) actPROMU8;

#ifndef  NULL
# define NULL  ((void *) 0)
#endif

/****************************************************************************
 ** Global Return and Errorcodes
 ***************************************************************************/

/* Our returncodes are actBYTEs */
typedef int actRETURNCODE;
/* no failures */
#define actOK                       0x00u
/* internal error during computation */
#define actEXCEPTION_UNKNOWN        0x01u
/* null pointer exception */
#define actEXCEPTION_NULL           0xFFu
/* invalid curve domain or extension data (decoding error) */
#define actEXCEPTION_DOMAIN         0xFEu
#define actEXCEPTION_DOMAIN_EXT     0xFDu
#define actEXCEPTION_SPEEDUP_EXT    0xFCu
/* invalid private key d ( d==0 || d>=n ) */
#define actEXCEPTION_PRIVKEY        0xFBu
/* invalid point ( invalid TAG or not on curve ) */
#define actEXCEPTION_POINT          0xFAu
/* invalid public key exception */
#define actEXCEPTION_PUBKEY         0xF9u
/* invalid length */
#define actEXCEPTION_LENGTH         0xF8u
/* invalid algorithm identifier */
#define actEXCEPTION_ALGOID         0xF7u
/* unpad error */
#define actEXCEPTION_PADDING        0xF6u
/* bad input length */
#define actEXCEPTION_INPUT_LENGTH   0xF5u
/* worspace or buffer too small */
#define actEXCEPTION_MEMORY         0xF4u
/* signature does NOT verify */
#define actVERIFICATION_FAILED      0xF3u

#endif   /* ACTITYPES_H */
