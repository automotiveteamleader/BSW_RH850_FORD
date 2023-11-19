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
 *         File:  Cry_30_Rh850Icum_CommonUtil.h
 *    Component:  DrvCry_Rh850Icum
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  This header file implements the utils for the ICUM Module
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#if !defined (CRY_30_RH850ICUM_COMMONUTIL_H)
#define CRY_30_RH850ICUM_COMMONUTIL_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Csm_Types.h"
#include "Cry_30_Rh850Icum_Cfg.h"
#include "r_icumif.api.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

 /* PRQA S 0779 22 */ /* MD_MSR_5.1_779 */
typedef enum
{
  CRY_30_RH850ICUM_SERVICE_IDLE,
  CRY_30_RH850ICUM_SERVICE_AESDECRYPT_START,
  CRY_30_RH850ICUM_SERVICE_AESDECRYPT_UPDATE,
  CRY_30_RH850ICUM_SERVICE_AESENCRYPT_START,
  CRY_30_RH850ICUM_SERVICE_AESENCRYPT_UPDATE,
  CRY_30_RH850ICUM_SERVICE_MACGENERATE_START,
  CRY_30_RH850ICUM_SERVICE_MACGENERATE_UPDATE,
  CRY_30_RH850ICUM_SERVICE_MACVERIFY_START,
  CRY_30_RH850ICUM_SERVICE_MACVERIFY_UPDATE,
  CRY_30_RH850ICUM_SERVICE_KEYEXTRACT_START,
  CRY_30_RH850ICUM_SERVICE_KEYEXTRACT_UPDATE,
  CRY_30_RH850ICUM_SERVICE_KEYWRAPSYM_START,
  CRY_30_RH850ICUM_SERVICE_KEYWRAPSYM_UPDATE,
  CRY_30_RH850ICUM_SERVICE_KEYWRAPSYM_FOR_PROVISION,
  CRY_30_RH850ICUM_SERVICE_PRNGSEED_START,
  CRY_30_RH850ICUM_SERVICE_PRNGSEED_UPDATE
} Cry_30_Rh850Icum_ServiceState_type;


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

#define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#if ( (CRY_30_RH850ICUM_AESDECRYPT128CONFIG == STD_ON) \
   || (CRY_30_RH850ICUM_AESENCRYPT128CONFIG == STD_ON) \
   || (CRY_30_RH850ICUM_CMACAES128GENCONFIG == STD_ON) \
   || (CRY_30_RH850ICUM_CMACAES128VERCONFIG == STD_ON) \
   || (CRY_30_RH850ICUM_KEYEXTRACTCONFIG == STD_ON) \
   || (CRY_30_RH850ICUM_KEYWRAPSYMCONFIG == STD_ON) \
   || (CRY_30_RH850ICUM_RNGCONFIG == STD_ON) )
extern VAR(Cry_30_Rh850Icum_ServiceState_type, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_ServiceState;
#endif

extern VAR(r_icumif_isd_t, CRY_30_RH850ICUM_VAR_NOINIT) ISD;

#define CRY_30_RH850ICUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* SHE keys */
#define CRY_30_RH850ICUM_SECRET_KEY                     (0x00u)
#define CRY_30_RH850ICUM_MASTER_ECU_KEY                 (0x01u)
#define CRY_30_RH850ICUM_BOOT_MAC_KEY                   (0x02u)
#define CRY_30_RH850ICUM_BOOT_MAC                       (0x03u)
#define CRY_30_RH850ICUM_KEY_1                          (0x04u)
#define CRY_30_RH850ICUM_KEY_2                          (0x05u)
#define CRY_30_RH850ICUM_KEY_3                          (0x06u)
#define CRY_30_RH850ICUM_KEY_4                          (0x07u)
#define CRY_30_RH850ICUM_KEY_5                          (0x08u)
#define CRY_30_RH850ICUM_KEY_6                          (0x09u)
#define CRY_30_RH850ICUM_KEY_7                          (0x0Au)
#define CRY_30_RH850ICUM_KEY_8                          (0x0Bu)
#define CRY_30_RH850ICUM_KEY_9                          (0x0Cu)
#define CRY_30_RH850ICUM_KEY_10                         (0x0Du)
#define CRY_30_RH850ICUM_KEY_RAM                        (0x0Eu)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CRY_30_RH850ICUM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

 /**********************************************************************************************************************
 * Cry_30_Rh850Icum_GetExtKeyFlag
 **********************************************************************************************************************/
 /*! \brief       Check if the keyId is extended or not.
 *  \param[in]    keyId         Id of the SHE key
 *  \param[in]    keyIdType     Type of the KeyId.
 *  \return       0             keyId is not extended.
 *  \return       1             keyId is extended.
 **********************************************************************************************************************/
FUNC(uint32, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_GetExtKeyFlag(uint32 keyId, uint32 keyIdType);

/**********************************************************************************************************************
* Cry_30_Rh850Icum_GetRawKeyId
**********************************************************************************************************************/
/*! \brief       Get the Raw (SHE) interpretation of a keyId.
*  \param[in]    keyId         Id of the SHE key
*  \param[in]    keyIdType     Type of the KeyId.
*  \return       Raw (SHE) interpretation of the KeyId.
**********************************************************************************************************************/
FUNC(uint32, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_GetRawKeyId(uint32 keyId, uint32 keyIdType);

/**********************************************************************************************************************
* Cry_30_Rh850Icum_GetRawIcumKeyId
**********************************************************************************************************************/
/*! \brief       Get the Raw (R_ICUMIF) interpretation of a keyId.
*  \param[in]    keyId         Id of the SHE key
*  \param[in]    keyIdType     Type of the KeyId.
*  \return       Raw (R_ICUMIF) interpretation of the KeyId.
**********************************************************************************************************************/
FUNC(uint32, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_GetRawIcumKeyId(uint32 keyId, uint32 keyIdType);

/**********************************************************************************************************************
* Cry_30_Rh850Icum_TriggerServiceAndWait
**********************************************************************************************************************/
/*! \brief       Start a service and wait for an answer of the ICUM firmware
*  \param[in]    p_ISD         Pointer to the service structure.
**********************************************************************************************************************/
FUNC(void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_TriggerServiceAndWait(P2VAR(r_icumif_isd_t, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) p_ISD);

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_LoadPlainKey
 **********************************************************************************************************************/
/*! \brief        The Cry_30_Rh850Icum_LoadPlainKey function updates the RAM key memory slot with a 128-bit plain text key.
 *  \param[in]    key           Pointer to the 128-bit plain text key.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 **********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_LoadPlainKey( P2CONST(uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) key );

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CancelCommand
 **********************************************************************************************************************/
/*! \brief        The Cry_30_Rh850Icum_CancelCommand cancels the current executing command on the ICU.
 **********************************************************************************************************************/
FUNC( void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CancelCommand( void );

#define CRY_30_RH850ICUM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* CRY_30_RH850ICUM_COMMONUTIL_H */

/**********************************************************************************************************************
 *  END OF FILE: SHE.H
 *********************************************************************************************************************/
