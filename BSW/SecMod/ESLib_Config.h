/****************************************************************************
 **
 ** $HeadURL: https://subversion/svn/library-ES/branches/library-es/1.2.0-VectorInformatik/development/common/testBench/source/testSHA512-256.c $
 ** $Revision: 2198 $
 ** $Date: 2016-01-13 08:46:05 +0100 (Mi, 13 Jan 2016) $
 ** $Author: mneuhaus $
 **
 ** \copyright(cv cryptovision GmbH, 2016)
 **
 ** \version(cv library/es 1.2)
 **
 ***************************************************************************/

/****************************************************************************
 **
 **     Part of the embedded systems library cv act library/ES
 **
 **     Layer: User Module Standard Interface
 **
 ***************************************************************************/

/****************************************************************************
 **
 ** this file contains: platform dependent configurations
 **
 **
 ** constants:
 **   ESL_SUPPORT_Curve25519
 **   ESL_SUPPORT_Curve448
 **
 ** types:
 **
 ** macros:
 **
 ** functions:
 **
 ***************************************************************************/


#ifndef     __EsLib_Config_H__
    #define __EsLib_Config_H__
    /*  curves supported for EdDSA signatures. */
    #define ESL_SUPPORT_Curve25519
    #undef  ESL_SUPPORT_Curve448

#endif  /*  __EsLib_Config_H__ */
