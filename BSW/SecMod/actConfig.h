/****************************************************************************
 ** Main author: UBR                     Creation date: 10/17/03
 ** $Author:: mneuhaus                 $ $JustDate:: 10/17/03             $
 ** $Workfile:: actConfig.h            $ $Revision:: 1939                 $
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
 **     Layer: Core Module - Interface
 **
 ***************************************************************************/

/****************************************************************************
 **
 ** This file contains: Endianess switch, arithmetic word type defintions,
 **                     workspace allocation switch, etc.
 **
 ** constants:
 **   LITTLE_ENDIAN
 **   actBN_BYTES_PER_DIGIT
 **   actBN_BITS_PER_DIGIT
 **   actEC_PRECOMP_GROUPS
 **   actBN_MOD_EXP_WINDOW_SIZE
 **   actEC_MOD_EXP_WINDOW_SIZE
 **   actEC_MOD_EXP_TMP
 **   actBN_EUCLID
 **
 ** types:
 **   actBNLENGTH, actBNDIGIT, actBNDDIGIT
 **
 ** macros:
 **   actECMalloc(), actECFree()
 **
 ** functions:
 **
 ***************************************************************************/

#ifndef ACTCONFIG_H
#define ACTCONFIG_H

# include "Platform_Types.h"
#include "actITypes.h"

/****************************************************************************
 ** Types and constants
 ***************************************************************************/

/****************************************************************************
 ** Endianess switch
 ***************************************************************************/

# if ( CPU_BYTE_ORDER == LOW_BYTE_FIRST )
#  define LITTLE_ENDIAN
#else
# if defined( LITTLE_ENDIAN )
#  undef LITTLE_ENDIAN
# endif
#endif

/****************************************************************************
 ** Main arithmetic data types:    actBNLENGTH, actBNDIGIT, actBNDDIGIT
 **
 **  A long number is represented as a little endian array of actBNDIGITs,
 **  the length of this array will be represented as actBNLENGTH.
 **
 ** CAUTION:
 **  These types are strongly dependend of the used hardware platform!
 **  The arithmetic module is designed to work on 8-Bit, 16-Bit and 32-Bit
 **  platforms, which means actBNDIGIT should be an unsigned type of this
 **  size. Basically your choise have to fulfill these conditions:
 **
 ** MAJOR CONDITIONS:
 **  - actBNLENGTH is a signed type
 **  - actBNDIGIT and actBNDDIGIT are unsigned types
 **  - an actBNDIGIT has 8, 16 or 32 bits
 **  - an actBNDDIGIT is exactly twice as long as an actBNDIGIT
 **  - for efficiency the processor should be able to multiply (add) two
 **    actDIGITs into one actBNDDIGIT
 ****************************************************************************
 **
 ** !!! NOTE !!! NOTE !!! NOTE !!!
 **
 **  The arithmetic modules were successfully tested on various 16-Bit and
 **  32-Bit platforms, which are the recommended platforms. On these
 **  platforms, switches to 8-Bit digit size were also tested, but not on
 **  a 'real' 8-Bit platform!
 **  If an 'int' has only 8 bit, there may be some 'length problems' left
 **  for numbers with more than 127 bytes (if actBNLENGTH is an 'int').
 **  Also, functions of type 'int' may have incorrect return values (>127).
 ***************************************************************************/

/*
   The BigNum length type:
*/
typedef int actBNLENGTH;

/*
   The BigNum digit and double digit types:
*/

#define actBN_BITS_PER_DIGIT     (ACT_PLATFORM_BITS_PER_DIGIT)
#define actBN_BYTES_PER_DIGIT    ((actBN_BITS_PER_DIGIT)>>3)

#if ( actBN_BITS_PER_DIGIT == 8 )
# define actBN_BITS_PER_DIGIT_IS_VALID
/*  8-Bit digits, 16-Bit ddigits */
typedef actU8 actBNDIGIT;
typedef actU16 actBNDDIGIT;
#endif
#if  ( actBN_BITS_PER_DIGIT == 16 )
# define actBN_BITS_PER_DIGIT_IS_VALID
/* 16-Bit digits, 32-Bit ddigits */
typedef actU16 actBNDIGIT;
typedef actU32 actBNDDIGIT;
#endif
#if  ( actBN_BITS_PER_DIGIT == 32 )
# define actBN_BITS_PER_DIGIT_IS_VALID
   /* 32-Bit digits, 64-Bit ddigits */
# if defined( ACT_PLATFORM_UINT64_AVAILABLE )
typedef actU32 actBNDIGIT;
typedef actU64 actBNDDIGIT;
# else
#  error UNABLE TO DEFINE 64 BIT DOUBLE DIGIT TYPE (NOT AVAILABLE)
# endif
#endif
#if defined( actBN_BITS_PER_DIGIT_IS_VALID )
#else
# error actBN_BITS_PER_DIGIT value unsupported
#endif

/****************************************************************************
 ** MontMul version switch
 ***************************************************************************/

#if 1
/* one inner loop */
# define actBN_MONT_MUL_VERSION     0
#endif
#if 0
/* two inner loops + prime structure optimizations (equals version 1 in this state) */
# define actBN_MONT_MUL_VERSION     1
#endif

/****************************************************************************
 ** Modular exponentation configuration switch (BNModExp)
 **
 **  window size    temporary variables    improvement factor
 **  -----------    -------------------    ------------------
 **     1 (sqr-and-mult)      1                     1
 **     2                     2                     1.09
 **     3                     4                     1.16
 **     4                     8                     1.22
 **     5                    16                     1.26
 **     k                  2^(k-1)
 **
 ** NOTE:
 **  - Each temporay variable is of length:   modulus_length_in_digits + 1
 **  - The improvement factors are concerning the duration for a modular
 **    exponentiation without precomputation time, assuming a random
 **    exponent and no special algorithm for modular squaring.
 ***************************************************************************/

#if 0
# define actBN_MOD_EXP_WINDOW_SIZE  0  /* variable k-bit window algorithm */
#endif
#if 1
# define actBN_MOD_EXP_WINDOW_SIZE  1  /* fixed 1-bit window algorithm (sqr-and-mult) */
#endif
#if 0
# define actBN_MOD_EXP_WINDOW_SIZE  2  /* fixed 2-bit window algorithm */
#endif
#if 0
# define actBN_MOD_EXP_WINDOW_SIZE  3  /* fixed 3-bit window algorithm */
#endif

#define actEC_MOD_EXP_WINDOW_SIZE   ( ((actBN_MOD_EXP_WINDOW_SIZE)==0) ? 3:(actBN_MOD_EXP_WINDOW_SIZE) )
#define actEC_MOD_EXP_TMP           ( 1 << ((actEC_MOD_EXP_WINDOW_SIZE)-1) )
#define actRSA_MOD_EXP_WINDOW_SIZE  ( ((actBN_MOD_EXP_WINDOW_SIZE)==0) ? 3:(actBN_MOD_EXP_WINDOW_SIZE) )
#define actRSA_MOD_EXP_TMP          ( 1 << ((actRSA_MOD_EXP_WINDOW_SIZE)-1) )

/****************************************************************************
 ** Switch 'ON/OFF' the extended Euclidian algorithm modul. The extended
 ** GCD is used for field inversions.
 **
 ** NOTE:
 **  - In general, it is faster to invert via Euclid than via Fermat (using
 **    modular exponentiation), but the GCD modul increases the code size.
 ***************************************************************************/

#if 0
# define actBN_EUCLID
#else
# if defined( actBN_EUCLID )
#  undef actBN_EUCLID
# endif
#endif

/****************************************************************************
 ** SHA-1 / RIPEMD-160 / SHA-256 / AES switches
 ***************************************************************************/

/*--------------------------------------------------------------------------
   Please choose a code size optimization level for the SHA-1 module:
   -------------------------------------------------------------------------
   Example: actSHAUpdate() benchmarks and SHA-1 module code sizes.
    - Machine:   Pentium 4, 3 GHz, 1 GB RAM, Windows 2000
    - Compiler:  VS VC++ 6.0
   -------------------------------------------------------------------------
                  | timings (in MB/sec, | code size (in bytes,
        level     | optimize size)      | optimize size)
      ------------|---------------------|---------------------
           0      |        40           |    1131
           1      |        60           |    1033
           2      |        85           |    4198
           3      |       120           |    4790
   -----------------------------------------------------------------------*/
#define actSHA_SPEED_UP   1
/*------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
   Please choose a code size optimization level for the RIPEMD-160 module:
   -----------------------------------------------------------------------*/
#define actRMD160_SPEED_UP   1
/*------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
   Please choose a code size optimization level for the SHA-256 module:
   -------------------------------------------------------------------------
   Example: actSHA256Update() benchmarks and SHA-256 module code sizes.
    - Machine:   Pentium III, 1 GHz, 256 MB RAM, Windows 2000
    - Compiler:  VS VC++ 6.0
   -------------------------------------------------------------------------
                  | timings (in MB/sec,  | code size (in bytes,
        level     | optimize size)       | optimize size)
      ------------|----------------------|---------------------
           0      |      16.8            |     894 + 256 byte K-Box
           1      |      29.0            |    3041 + 256 byte K-Box
   -----------------------------------------------------------------------*/
#define actSHA256_SPEED_UP   0
/*------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
   Please choose a code size optimization level for the SHA-512 module:
   -------------------------------------------------------------------------
   Example: actSHA512Update() benchmarks and SHA-512 module code sizes.
    - Machine:   Pentium III, 1 GHz, 256 MB RAM, Windows 2000
    - Compiler:  VS VC++ 6.0
   -------------------------------------------------------------------------
                  | timings (in MB/sec,  | code size (in bytes,
        level     | optimize size)       | optimize size)
      ------------|----------------------|---------------------
           0      |                      |
           1      |                      |
   -----------------------------------------------------------------------*/
#define actSHA512_SPEED_UP   0
/*------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
   Please choose a code size optimization level for the MD5 module:
   -------------------------------------------------------------------------
   Example: actMD5Update() benchmarks and MD5 module code sizes.
    - Machine:   Pentium III, 1 GHz, 256 MB RAM, Windows 2000
    - Compiler:  VS VC++ 6.0
   -------------------------------------------------------------------------
                  | timings (in MB/sec,  | code size (in bytes,
        level     | optimize size)       | optimize size)
      ------------|----------------------|---------------------
           0      |      ----            |    722 + 320 byte tables
           1      |      ----            |   1248 + 256 byte tables
           2      |      ----            |   2166
   -----------------------------------------------------------------------*/
#define actMD5_SPEED_UP   1
/*------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
    Speed up level 0 - 3 in AES modul.
   -----------------------------------------------------------------------*/
#define actAES_SPEED_UP   1
/*--------------------------------------------------------------------------
   level 0,1 :       1,0 KB memory is required for look up tables
   level 2,3 :       8,5 KB memory is required for look up tables
--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
    Speed up level 0 / 1 / 4 for GHASH module
    "1":  256 bytes RAM (workspace) +  32 bytes ROM for look up tables
    "4": 4096 bytes RAM (workspace) + 512 bytes ROM for look up tables

    ##  Please read the "library/es Porting Guide"
    ##  for more information!
   -----------------------------------------------------------------------*/
#define actGHASH_SPEED_UP   1

/****************************************************************************
 ** Random call back function used inside actCLibrary (key generation etc.)
 ***************************************************************************/

#if 0
# define actPRNG_CALLBACK
#else
# if defined( actPRNG_CALLBACK )
#  undef actPRNG_CALLBACK /* LIB_ES callback is used */
# endif
#endif

/****************************************************************************
 ** watchdog functionality
 ***************************************************************************/

/*--------------------------------------------------------------------------
    watchdog call frequency
  -------------------------------------------------------------------------*/
#define  actWD_LEVEL 3
/*--------------------------------------------------------------------------
   level 0: WD is disabled
   level 1: WD called from outer functions only
   level 2: WD called from inner functions as well
   level 3: WD also called in inner hash loops
--------------------------------------------------------------------------*/

#endif   /* ACTCONFIG_H */

