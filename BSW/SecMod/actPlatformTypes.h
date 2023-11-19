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
 * $LastChangedBy: men $
 * $LastChangedDate: 2008-06-02 17:41:49 +0200 (Mo, 02. Jun 2008) $
 * $LastChangedRevision: 1650 $
 * $URL: https://scm/svn/library-es/branches/library-es/1.2.0-VectorInformatik/development/i386/lib_es/header/platform_t.h $
 *
 *****************************************************************************
 */

/****************************************************************************
 **
 **     Part of the embedded systems library cvActLib/ES
 **
 **     Layer: User Module Standard Interface
 **
 ***************************************************************************/

/****************************************************************************
 **
 ** This file contains: Platform depending type definitions.
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

#ifndef ACTPLATFORMTYPES_H
#define ACTPLATFORMTYPES_H

#include <limits.h>

# include "Std_Types.h"
# include "Platform_Types.h"

/******************************************************************************
 * AUTOSAR abstraction
 *****************************************************************************/
/* CPU type definition */
/* 8 bit CPU */
# if (CPU_TYPE == CPU_TYPE_8)
#  define ACT_PLATFORM_CPUTYPE_8BIT
/* 16 bit CPU */
# elif (CPU_TYPE == CPU_TYPE_16)
#  define ACT_PLATFORM_CPUTYPE_16BIT
/* 32 bit CPU */
# elif (CPU_TYPE == CPU_TYPE_32)
#  define ACT_PLATFORM_CPUTYPE_32BIT
# else
#  error "No valid CPU_TYPE from Platform_Types.h was found!"
# endif

/******************************************************************************
 * Platform depending types
 *****************************************************************************/
typedef uint8     actPlatformUint8;
typedef uint16    actPlatformUint16;
typedef uint32    actPlatformUint32;

#if defined( ACT_PLATFORM_UINT64_AVAILABLE )
# undef ACT_PLATFORM_UINT64_AVAILABLE
#endif

#if defined( ACT_PLATFORM_CPUTYPE_32BIT )
/* Use ULLONG_MAX defined in limits.h to detect availability of 64 bit type */
# if defined( ULLONG_MAX )
#  define ACT_PLATFORM_BITS_PER_DIGIT  32
#  define ACT_PLATFORM_UINT64_AVAILABLE  /* 64 bit type */
typedef unsigned long long actPlatformUint64;
# else
#  define ACT_PLATFORM_BITS_PER_DIGIT  16
# endif /* ULLONG_MAX */
#  define ACT_PLATFORM_ALIGNMENT       4
#elif defined( ACT_PLATFORM_CPUTYPE_16BIT )
# define ACT_PLATFORM_BITS_PER_DIGIT   16
#  define ACT_PLATFORM_ALIGNMENT       4
#elif defined( ACT_PLATFORM_CPUTYPE_8BIT )
# define ACT_PLATFORM_BITS_PER_DIGIT   8
#  define ACT_PLATFORM_ALIGNMENT       1
#else
# error "actPlatformTypes.h: Current CPU type is not supported!"
#endif

/* Access macros for ROM data */
#define ACT_ROM_POST

#define ACT_ROM_STR(x)    (x)

#define ACT_ROM_BYT(x)    (*(x))
#define ACT_ROM_WRD(x)    (*(x))
#define ACT_ROM_PTR(x)    ((actPROMU8)(*(x)))
#define ACT_ROM_DWD(x)    (*(x))

#define ACT_ROM_R_BYT(x)  (x)
#define ACT_ROM_R_WRD(x)  (x)
#define ACT_ROM_R_PTR(x)  ((actPROMU8)(x))
#define ACT_ROM_R_DWD(x)  (x)

#if !defined(V_NULL)
# define V_NULL ((void*)0)
#endif

# define CRYPTOCV_FUNC_NULL_PTR ((void (*)(void))0)

#ifndef STATIC
#define STATIC static
#endif
#define CRYPTOCV_NONE       /* empty storage used instead of extern, static, volatile... */

# define CRYPTOCV_P2VAR(storage, ptrtype)                   storage P2VAR(ptrtype, AUTOMATIC, CRYPTOCV_APPL_VAR)                 /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
# define CRYPTOCV_P2VAR_TYPE(storage, ptrtype)              typedef storage P2VAR(ptrtype, TYPEDEF, CRYPTOCV_APPL_VAR)           /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
# define CRYPTOCV_P2VAR_PARA(ptrtype)                       P2VAR(ptrtype, AUTOMATIC, CRYPTOCV_APPL_VAR)                         /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */

# define CRYPTOCV_CONSTP2VAR(storage, ptrtype)              storage CONSTP2VAR(ptrtype, AUTOMATIC, CRYPTOCV_APPL_VAR)            /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
# define CRYPTOCV_CONST(storage, type)                      storage CONST(type, CRYPTOCV_APPL_CONST)                             /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
# define CRYPTOCV_CONST_TYPE(storage, type)                 typedef storage CONST(type, TYPEDEF)                                 /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */

# define CRYPTOCV_P2CONST(storage, ptrtype)                 storage P2CONST(ptrtype, AUTOMATIC, CRYPTOCV_APPL_VAR)               /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
# define CRYPTOCV_P2CONST_TYPE(storage, ptrtype)            typedef storage P2CONST(ptrtype, TYPEDEF, CRYPTOCV_APPL_VAR)         /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
# define CRYPTOCV_P2CONST_PARA(ptrtype)                     P2CONST(ptrtype, AUTOMATIC, CRYPTOCV_APPL_VAR)                       /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */

# define CRYPTOCV_P2ROMCONST(storage, ptrtype)              storage P2CONST(ptrtype, AUTOMATIC, CRYPTOCV_APPL_CONST)             /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
# define CRYPTOCV_P2ROMCONST_TYPE(storage, ptrtype)         typedef storage P2CONST(ptrtype, TYPEDEF, CRYPTOCV_APPL_CONST)       /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
# define CRYPTOCV_P2ROMCONST_PARA(ptrtype)                  P2CONST(ptrtype, AUTOMATIC, CRYPTOCV_APPL_CONST)                     /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */

# define CRYPTOCV_CONSTP2CONST(storage, ptrtype)            storage CONSTP2CONST(ptrtype, AUTOMATIC, CRYPTOCV_APPL_VAR)          /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
# define CRYPTOCV_CONSTP2ROMCONST(storage, ptrtype)         storage CONSTP2CONST(ptrtype, AUTOMATIC, CRYPTOCV_APPL_CONST)        /* PRQA S 0342,3410,3453,0881 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453, MD_Can_0881_Asr_abstract */
# define CRYPTOCV_CONSTP2CONST_TYPE(storage, ptrtype)       typedef storage CONSTP2CONST(ptrtype, TYPEDEF, CRYPTOCV_APPL_VAR)    /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
# define CRYPTOCV_CONSTP2ROMCONST_TYPE(storage, ptrtype)    typedef storage CONSTP2CONST(ptrtype, TYPEDEF, CRYPTOCV_APPL_CONST)  /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
# define CRYPTOCV_FUNC(rettype)                             FUNC(rettype, CRYPTOCV_CODE)                                         /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */
# define CRYPTOCV_P2FUNC(storage, rettype, fctname)         storage P2FUNC(rettype, AUTOMATIC, fctname)                          /* PRQA S 0342,3410,3453 */ /* MD_Can_0342, MD_Can_3410, MD_Can_3453 */

#endif /* ACTPLATFORMTYPES_H */

