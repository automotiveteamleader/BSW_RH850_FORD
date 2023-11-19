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
 * $LastChangedBy: alf $
 * $LastChangedDate: 2009-03-27 11:46:25 +0100 (Fr, 27. Mrz 2009) $
 * $LastChangedRevision: 1831 $
 * $URL: https://scm/svn/library-ES/branches/library-es/1.2.0-VectorInformatik/development/common/lib_es/include/ESLib_V1.1_compatibility.h $
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

#ifndef __ESLib_comp1_1_h__
#define __ESLib_comp1_1_h__


#ifdef  __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * some compatibility defines, as minor changes have been done in Version 1.2
 *****************************************************************************/


#define esl_initWorkSpace(x,y,z)       esl_initWorkSpaceHeader(x,y,z)
#define ESL_ERC_AES_INVALID_PADDING    ESL_ERC_AES_PADDING_INVALID

#ifdef  __cplusplus
} /* extern "C" */
#endif

#endif  /* __ESLib_comp1_1_h__ */

