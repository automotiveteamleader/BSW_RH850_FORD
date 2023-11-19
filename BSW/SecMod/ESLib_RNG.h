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
 * $LastChangedDate: 2015-12-11 12:07:04 +0100 (Fr, 11 Dez 2015) $
 * $LastChangedRevision: 2154 $
 * $URL: https://subversion/svn/library-ES/branches/library-es/1.2.0-VectorInformatik/development/common/lib_es/include/ESLib_RNG.h $
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
 ** This file contains: random number generator interface.
 **
 **
 ** constants:
 **   ESL_MAXSIZEOF_WS_RNG
 **
 ** types:
 **   eslt_WorkSpaceRNG
 **
 ** macros:
 **
 ** functions:
 **   esl_initRNG
 **   esl_getBytesRNG
 **   esl_stirRNG
 **
 ***************************************************************************/

#ifndef __ESLib_RNG_H__
#define __ESLib_RNG_H__

#include "ESLib_t.h"


#ifdef  __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * Random number generator defines and functions
 *****************************************************************************/


#define ESL_MAXSIZEOF_WS_RNG ESL_MAXSIZEOF_WS_FIPS186

typedef struct
{
   eslt_WorkSpaceHeader header;
   eslt_Byte wsRNG[ ESL_MAXSIZEOF_WS_RNG];
}eslt_WorkSpaceRNG;


#define ESL_SIZEOF_RNG_STATE ESL_SIZEOF_RNGFIPS186_STATE


/*****************************************************************************
 * Random number generator functions (according to FIPS186-2)
 *****************************************************************************/

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_initRNG(
   CRYPTOCV_P2VAR_PARA( eslt_WorkSpaceRNG ) workSpace,
   const eslt_Length entropyLength, CRYPTOCV_P2CONST_PARA( eslt_Byte ) entropy,
   CRYPTOCV_P2VAR_PARA( eslt_Byte ) savedState );
/* ErrorCode:
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_MODE_INVALID
      ESL_ERC_NO_ERROR */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_getBytesRNG(
   const eslt_Length targetLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) target );

/* ErrorCode:
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_NO_ERROR */

extern CRYPTOCV_FUNC( eslt_ErrorCode ) esl_stirRNG(
   const eslt_Length inputLength, CRYPTOCV_P2VAR_PARA( eslt_Byte ) input );

/* ErrorCode:
      ESL_ERC_PARAMETER_INVALID
      ESL_ERC_WS_STATE_INVALID
      ESL_ERC_WS_TOO_SMALL
      ESL_ERC_NO_ERROR */

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif  /* _ESLib_RNG_H__ */

