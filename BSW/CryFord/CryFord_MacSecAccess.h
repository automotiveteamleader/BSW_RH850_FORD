/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2015 by Vector Informatik GmbH.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  CryFord_MacSecAccess.h
 *    Component:  SysService_AsrCryFord
 *       Module:  MICROSAR Cryptographic library module (Cry)
 *    Generator:  -
 *
 *  Description:  This header file implements the FORD Security Access MAC CRY API for the ASR CSM
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Markus Schneider              vismss        Vector Informatik GmbH
 *  Tobias Finke                  vistof        Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2015-04-10  vismss  ESCAN00082351 Creation
 *  01.00.01  2015-08-04  vismss  ESCAN00084343 Fixed bug: Verification returns CSM_E_NOT_OK if the verification fails
 *                        vismss  ESCAN00083238 Changes to process
 *  01.00.02  2015-09-29  vistof  ESCAN00085511 Fixed parameter check to prevent possible buffer overflow
 *                        vistof  ESCAN00085580 Fixed define for dummy statements
 *********************************************************************************************************************/

#if !defined (CRYFORD_MACSECACCESS_H)
#define CRYFORD_MACSECACCESS_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Csm_Types.h"
#include "CryFord_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/** Component version information (decimal version of ALM implementation package) */
#define CRYFORD_SW_MAJOR_VERSION                  (1u)
#define CRYFORD_SW_MINOR_VERSION                  (0u)
#define CRYFORD_SW_PATCH_VERSION                  (2u)

/** Vendor and module identification */
#define CRYFORD_VENDOR_ID                         (30u)
#define CRYFORD_MODULE_ID                         (255u)
#define CRYFORD_INSTANCE_ID                       (0u)

/** AUTOSAR Software Specification Version Information */
#define CRYFORD_AR_RELEASE_MAJOR_VERSION          (0x04)
#define CRYFORD_AR_RELEASE_MINOR_VERSION          (0x00)
#define CRYFORD_AR_RELEASE_REVISION_VERSION       (0x03)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CRYFORD_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern FUNC( void, CRYFORD_CODE) CryFord_MacSecAccessInit( void );
extern FUNC( void, CRYFORD_CODE) CryFord_MacSecAccessVerifyMainFunction( void );

extern FUNC( Csm_ReturnType, CRYFORD_CODE ) CryFord_MacSecAccessVerifyStart( P2CONST( void, AUTOMATIC, CRYFORD_APPL_VAR) cfgPtr,
                                                                 P2CONST( Csm_SymKeyType, AUTOMATIC, CRYFORD_APPL_VAR ) keyPtr );

extern FUNC( Csm_ReturnType, CRYFORD_CODE ) CryFord_MacSecAccessVerifyUpdate( P2CONST( void, AUTOMATIC, CRYFORD_APPL_VAR) cfgPtr,
                                                                  P2CONST( uint8, AUTOMATIC, CRYFORD_APPL_VAR ) dataPtr,
                                                                  uint32 dataLength );

extern FUNC( Csm_ReturnType, CRYFORD_CODE ) CryFord_MacSecAccessVerifyFinish( P2CONST( void, AUTOMATIC, CRYFORD_APPL_VAR) cfgPtr,
                                                                  P2CONST( uint8, AUTOMATIC, CRYFORD_APPL_VAR ) MacPtr,
                                                                  uint32 MacLength,
                                                                  P2VAR( Csm_VerifyResultType, AUTOMATIC, CRYFORD_APPL_VAR ) resultPtr );

#define CRYFORD_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif  /* CRYFORD_MACSECACCESS_H */
/**********************************************************************************************************************
 *  END OF FILE: CRYFORD_MACSECACCESS.H
 *********************************************************************************************************************/
