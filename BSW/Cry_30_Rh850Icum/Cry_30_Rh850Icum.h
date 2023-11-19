/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2016 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Cry_30_Rh850Icum.h
 *    Component:  DrvCry_Rh850Icum
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  This header file implements the CRY API for the ICUM.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Tobias Finke                  vistof        Vector Informatik GmbH
 *  Markus Schneider              vismss        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2016-10-21  vistof  ESCAN00092461 Creation
 *********************************************************************************************************************/

 #if !defined (CRY_30_RH850ICUM_H)
 #define CRY_30_RH850ICUM_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Cry_30_Rh850Icum_Cfg.h"

#if ( CRY_30_RH850ICUM_AESENCRYPT128CONFIG == STD_ON )
# include "Cry_30_Rh850Icum_AesEncrypt128.h"
#endif

#if ( CRY_30_RH850ICUM_AESDECRYPT128CONFIG == STD_ON )
# include "Cry_30_Rh850Icum_AesDecrypt128.h"
#endif

#if ( CRY_30_RH850ICUM_CMACAES128GENCONFIG == STD_ON )
# include "Cry_30_Rh850Icum_CmacAes128Gen.h"
#endif

#if ( CRY_30_RH850ICUM_CMACAES128VERCONFIG == STD_ON )
# include "Cry_30_Rh850Icum_CmacAes128Ver.h"
#endif

#if ( CRY_30_RH850ICUM_RNGCONFIG == STD_ON )
# include "Cry_30_Rh850Icum_Rng.h"
#endif

#if ( CRY_30_RH850ICUM_KEYEXTRACTCONFIG == STD_ON )
# include "Cry_30_Rh850Icum_KeyExtract.h"
#endif

#if ( CRY_30_RH850ICUM_KEYWRAPSYMCONFIG == STD_ON )
# include "Cry_30_Rh850Icum_KeyWrapSym.h"
#endif

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/** Version - BCD coded version number - Main- and Sub-Version - Release-Version */
#define CRY_30_RH850ICUM_VERSION                           (0x0100u)
#define CRY_30_RH850ICUM_RELEASE_VERSION                   (0x00u)

/** Vendor and module identification */
#define CRY_30_RH850ICUM_VENDOR_ID                         (30u)
#define CRY_30_RH850ICUM_MODULE_ID                         (255u)
#define CRY_30_RH850ICUM_INSTANCE_ID                       (0u)

/** AUTOSAR Software Specification Version Information */
#define CRY_30_RH850ICUM_AR_RELEASE_MAJOR_VERSION          (0x04)
#define CRY_30_RH850ICUM_AR_RELEASE_MINOR_VERSION          (0x00)
#define CRY_30_RH850ICUM_AR_RELEASE_REVISION_VERSION       (0x03)

/** Component Version Information */
/* No u suffix is used for shift operator because some compilers may have problems */
#define CRY_30_RH850ICUM_SW_MAJOR_VERSION                  (CRY_30_RH850ICUM_VERSION >> 8)
#define CRY_30_RH850ICUM_SW_MINOR_VERSION                  (CRY_30_RH850ICUM_VERSION & 0x00FF)
#define CRY_30_RH850ICUM_SW_PATCH_VERSION                  (CRY_30_RH850ICUM_RELEASE_VERSION)


/* State machine job status */
#define CRY_30_RH850ICUM_STATE_IDLE                        (0x00u)
#define CRY_30_RH850ICUM_STATE_START                       (0x01u)
#define CRY_30_RH850ICUM_STATE_UPDATE                      (0x02u)
#define CRY_30_RH850ICUM_STATE_FINISH                      (0x03u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CRY_30_RH850ICUM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

FUNC (void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_Init( void );
FUNC (void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_InitMemory( void );

#if ( CRY_30_RH850ICUM_VERSION_INFO_API == STD_ON )
FUNC( void, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cryVerInfoPtr );
#endif

#define CRY_30_RH850ICUM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* CRY_30_RH850ICUM_H */

/**********************************************************************************************************************
 *  END OF FILE: CRY_30_RH850ICUM.H
 *********************************************************************************************************************/
