/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Cry_30_LibCv.h
 *    Component:  SysService_AsrCry
 *       Module:  MICROSAR Cryptographic library module (Cry)
 *    Generator:  -
 *
 *  Description:  This header file implements the  Cry API for the ASR CSM
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Philipp Ritter                visrpp        Vector Informatik GmbH
 *  Markus Schneider              vismss        Vector Informatik GmbH
 *  Tobias Finke                  vistof        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2012-10-28  visrpp  ESCAN00062708 Creation
 *  01.00.01  2013-09-24  vismss  ESCAN00070622 Wrong header file included
 *  01.00.02  2013-10-10  vismss  ESCAN00071019 Fixed naming issue of the MainFunctions
 *  01.01.00  2015-02-23  vismss  ESCAN00081848 Implementation of FIPS186-2 algorithm
 *                                              Implementation of HMAC SHA-1 algorithm
 *                                              Rework of AES128 decrypt/encrypt
 *  01.02.00  2015-04-22  vistof  ESCAN00082609 Implementation of RSA-1024 decrypt algorithm
 *                                              Implementation of RSA-SHA1 signature verify algorithm
 *  01.02.01  2015-06-12  vismss  ESCAN00083381 Refactoring of the key types. Outsourced in Cry_30_LibCv_Key_Types.h
 *  01.02.02  2015-09-30  vistof  ESCAN00085565 Fixed wrong cast of cfgPtr in Cry_30_LibCv_RsaSha1SigVerStartInternal
 *                                ESCAN00085569 Fixed define for dummy statements
 *                                ESCAN00084378 Fixed bug: MAC Verification returns CSM_E_NOT_OK 
 *                                              if the verification fails
 *                                ESCAN00085628 Fixed bug: Signature Verification returns CSM_E_NOT_OK 
 *                                              if the verification fails
 *                                ESCAN00085633 Prevent unaligned access to workspace struct
 *  02.00.00  2015-11-27  vismss  ESCAN00086830 Support of DaVinci Configurator 5
 *  02.00.01  2016-01-26  vismss  ESCAN00087766 Added RSA decryption use private key switch for branch 02.xx.xx
 *  02.00.02  2016-01-28  vismss  ESCAN00087891 Fixed compiler warning
 *  02.01.00  2016-04-27  vistof  ESCAN00089711 Fixed wrong behaviour of Save State
 *                                              Fixed doxygen comment of Cry_30_LibCv_HmacSha1VerifyFinish
 *                                              Remove duplicate includes in Cry.c
 *                                              Remove unnecessary NULL_PTR checks in HmacSha1Verify
 *                                ESCAN00090064 FEAT-1938: CMAC AES-128 for SW Cry
 *                                ESCAN00090325 MAC length can be configured to be in Bits or Bytes
 *  02.02.00  2016-09-20  vismss  ESCAN00091960 Implementation of SHA256, HMAC SHA256, ECDH, ECDSA, PBKDF2
 *  03.00.00  2016-10-21  vistof  ESCAN00092447 FEAT-1995: Support CRY(HW) and CRY(SW) in the same SIP
 *  03.00.01  2017-05-23  vistof  ESCAN00095276 Fixed misaligned access to workspace structure
 *********************************************************************************************************************/

 #if !defined (CRY_30_LIBCV_H)
 #define CRY_30_LIBCV_H

 /* PRQA S 0779 EOF */ /* MD_MSR_5.1_779 */

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Cry_30_LibCv_Cfg.h"

# if ( CRY_30_LIBCV_AESENCRYPT128CONFIG == STD_ON )
#  include "Cry_30_LibCv_AesEncrypt128.h"
# endif

# if ( CRY_30_LIBCV_AESDECRYPT128CONFIG == STD_ON )
#  include "Cry_30_LibCv_AesDecrypt128.h"
# endif

# if ( CRY_30_LIBCV_HMACSHA1VERIFYCONFIG == STD_ON )
#  include "Cry_30_LibCv_HmacSha1.h"
# endif

# if ( CRY_30_LIBCV_FIPS186CONFIG == STD_ON )
#  include "Cry_30_LibCv_Fips186.h"
# endif

# if ( CRY_30_LIBCV_CMACAES128GENCONFIG == STD_ON )
#  include "Cry_30_LibCv_CmacAes128Gen.h"
# endif

# if ( CRY_30_LIBCV_CMACAES128VERCONFIG == STD_ON )
#  include "Cry_30_LibCv_CmacAes128Ver.h"
# endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/** Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define CRY_30_LIBCV_VERSION                           (0x0300u)
#define CRY_30_LIBCV_RELEASE_VERSION                   (0x01u)

/** Vendor and module identification */
#define CRY_30_LIBCV_VENDOR_ID                         (30u)
#define CRY_30_LIBCV_MODULE_ID                         (255u)
#define CRY_30_LIBCV_INSTANCE_ID                       (0u)

/** AUTOSAR Software Specification Version Information */
#define CRY_AR_RELEASE_MAJOR_VERSION          (0x04)
#define CRY_AR_RELEASE_MINOR_VERSION          (0x00)
#define CRY_AR_RELEASE_REVISION_VERSION       (0x03)

/** Component Version Information */
/* No u suffix is used for shift operator because some compilers may have problems */
#define CRY_30_LIBCV_SW_MAJOR_VERSION                  (CRY_30_LIBCV_VERSION >> 8)
#define CRY_30_LIBCV_SW_MINOR_VERSION                  (CRY_30_LIBCV_VERSION & 0x00FF)
#define CRY_30_LIBCV_SW_PATCH_VERSION                  (CRY_30_LIBCV_RELEASE_VERSION)

/** State machine job status */
#define CRY_30_LIBCV_STATE_IDLE                        (0x00u)
#define CRY_30_LIBCV_STATE_START                       (0x01u)
#define CRY_30_LIBCV_STATE_UPDATE                      (0x02u)
#define CRY_30_LIBCV_STATE_FINISH                      (0x03u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CRY_30_LIBCV_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

FUNC (void, CRY_30_LIBCV_CODE) Cry_30_LibCv_Init( void );
FUNC (void, CRY_30_LIBCV_CODE) Cry_30_LibCv_InitMemory( void );

#if ( CRY_30_LIBCV_VERSION_INFO_API == STD_ON )
FUNC( void, CRY_30_LIBCV_CODE ) Cry_30_LibCv_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cryVerInfoPtr );
#endif

#define CRY_30_LIBCV_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* CRY_30_LIBCV_H_ */

/**********************************************************************************************************************
 *  END OF FILE: CRY_30_LIBCV.H
 *********************************************************************************************************************/
