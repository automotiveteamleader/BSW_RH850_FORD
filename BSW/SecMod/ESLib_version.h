/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief        Crypto library
 *
 *  \description  Main header file of cv act library/ES by cryptovision GmbH.
 *                Additional header used to document changes implemented by Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 */
/*********************************************************************************************************************/

/***********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  --------------------------------------------------------------------------------------------------------------------
 *  Thorsten Albers               Al            Vector Informatik GmbH
 *  Armin Happel                  Hp            Vector Informatik GmbH
 *  Joern Herwig                  JHg           Vector Informatik GmbH
 *  Markus Schneider              Mss           Vector Informatik GmbH
 *  Tobias Finke                  Tof           Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  01.00.00   2013-06-20  Al      -                Renamed asn_1.h to ESLib_ASN_1.h
 *                                                   Protection against multiple inclusion added
 *                                                  Renamed types.h to ESLib_types.h
 *                         Hp      -                Added SHA256 DigestInfo to ESLib_ASN_1.h
 *                         JHg     ESCAN00068215    Initial release based on original cv act library/ES and
 *                                                   SysService_Crypto 01.04.01
 *                                                  Use base types from actPlatformTypes.h
 *                                                  Use compiler abstraction for ROM pointers from Vector platform definitions
 *  01.01.00   2013-09-26  JHg     ESCAN00070713    Added version information
 *                                                  Added API for separate hash finalization and signature verification
 *                                                  Added option to locate cryptographic keys in RAM instead of ROM
 *                                                  Include primitives for DES, T-DES and RC2
 *                                                  Maximum size of RSA keys configurable at integration-time
 *  01.01.01   2014-01-14  JHg     ESCAN00072935    No changes
 *  01.02.00   2014-02-11  JHg     ESCAN00073601    No changes
 *  01.03.00   2014-04-23  JHg     ESCAN00074877    Place ASN.1 digest info in global constants
 *  01.04.00   2014-04-28  JHg     ESCAN00075253    Added dedicated file for version information
 *  02.00.00   2014-05-16  Mss     ESCAN00075467    Added memory qualifier abstraction for ASR/CBD
 *  02.01.00   2014-07-22  JHg     ESCAN00075892    Added RSA decryption with public key (esl_decryptPubRSA_V15)
 *                                                  Refactored handling of RSA padding
 *                         Mss     ESCAN00076890    Compiler error fix
 *  02.01.01   2014-11-28  Mss     ESCAN00079872    Compiler warning fix
 *  02.02.00   2014-09-04  JHg     ESCAN00080919    Corrected handling of public key padding
 *             2015-01-22  Mss     ESCAN00080920    Rework of compiler abstraction for RSA and SHA256
 *  02.02.01   2015-02-03  Mss     ESCAN00081009    No changes
 *  02.02.02   2015-06-03  Mss     ESCAN00083257    Memory qualifier abstraction for RSA SHA1 signature verification
 *  02.03.00   2015-06-16  Mss     ESCAN00083456    Rework of compiler abstraction for remaining services
 *  02.04.00   2015-10-12  JHg     ESCAN00085779    Added support for RSASSA-PSS signatures
 *                         JHg     ESCAN00085782    Compiler abstraction: Differentiate pointers to constants in RAM and ROM
 *                         JHg     ESCAN00085785    Added support for RSA key sizes up to 3072/4096 bit
 *  02.04.01   2016-03-18  JHg     ESCAN00086620    Compiler error fix
 *  02.04.02   2016-03-23  JHg     ESCAN00089062    Rework storage of parameter values in version information
 *  02.05.00   2016-03-23  JHg     ESCAN00088385    Added support for RSAES-OAEP encryption/decryption
 *             2016-05-03  JHg     ESCAN00089870    Added support for CMAC (AES-128) generation/verification
 *                         JHg     ESCAN00089873    Added support for additional padding and block operation modes
 *             2016-06-15  Tof     ESCAN00090360    Compiler error fix
 *                         Tof     ESCAN00090482    Added support for EdDSA, ECDH, GCM, GMAC, SHA-512
 *  02.05.01   2016-07-06  Tof     ESCAN00090851    Compiler error fix
 *  02.05.02   2016-11-23  Tof     ESCAN00089062    Rework storage of parameter values in version information
 *  02.06.00   2017-02-16  Mss     ESCAN00094051    Added SipHash
 *                                 ESCAN00094048    Removed C++ style comment
 *                                                  Support of variant Ed25519ctx
 *  02.06.01   2017-05-05  Mss     ESCAN00095044    Correction of SIPHASH for big endian devices
 **********************************************************************************************************************/

#ifndef __ESLib_version_H__
#define __ESLib_version_H__

/**********************************************************************************************************************
 *  VERSION
 *********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : SysService_CryptoCv CQComponent : Impl_ESLib */
#define SYSSERVICE_CRYPTOCV_ESLIB_VERSION             0x0206u
#define SYSSERVICE_CRYPTOCV_ESLIB_RELEASE_VERSION     0x01u

#endif /* __ESLib_version_H__ */

