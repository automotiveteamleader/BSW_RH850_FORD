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
 *         File:  Cry_30_Rh850Icum_CommonUtil.c
 *    Component:  DrvCry_Rh850Icum
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  Common functions for the ICUM Module
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define CRY_30_RH850ICUM_COMMONUTIL_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_Rh850Icum.h"
#include "Cry_30_Rh850Icum_CommonUtil.h"
#include "r_icumif.api.h"

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#define CRY_END_OF_FIRST_KEYPAGE          (CRY_30_RH850ICUM_KEY_RAM)
#define CRY_MAPPED_OFFSET                 (3u)
#define CRY_MAPPED_OFFSET_SECOND_KEYPAGE  (10u)
#define CRY_RAW_OFFSET_SECOND_KEYPAGE     (6u)

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
VAR(Cry_30_Rh850Icum_ServiceState_type, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_ServiceState;
#endif

VAR(r_icumif_isd_t, CRY_30_RH850ICUM_VAR_NOINIT) ISD;

#define CRY_30_RH850ICUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

#define CRY_30_RH850ICUM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

FUNC(uint32, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_GetExtKeyFlag(uint32 keyId, uint32 keyIdType)
{
  uint32 flagKeyMd = 0u;

  if (keyIdType == CRY_30_RH850ICUM_KEYIDTYPE_MAPPED)
  {
    if (keyId > CRY_MAPPED_OFFSET_SECOND_KEYPAGE)     /* Check if second keyslot page shall be used */
    {
      flagKeyMd = 1u;
    }
  }
  else /* keyIdType == CRY_30_RH850ICUM_KEYIDTYPE_RAW */
  {
    if (keyId > CRY_END_OF_FIRST_KEYPAGE)
    {
      flagKeyMd = 1u;
    }
  }
  return flagKeyMd;
}

FUNC(uint32, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_GetRawKeyId(uint32 keyId, uint32 keyIdType)
{
  uint32 tmpKeyId;

  if (keyIdType == CRY_30_RH850ICUM_KEYIDTYPE_MAPPED)
  {
    if (keyId == CRY_KEYID_MAPPED_MASTER_ECU_KEY)
    {
      tmpKeyId = CRY_30_RH850ICUM_MASTER_ECU_KEY;
    }
    else if (keyId == CRY_KEYID_MAPPED_KEY_RAM)
    {
      tmpKeyId = CRY_30_RH850ICUM_KEY_RAM;
    }
    else if (keyId > CRY_MAPPED_OFFSET_SECOND_KEYPAGE)     /* Check if second keyslot page shall be used */
    {
      tmpKeyId = (keyId + CRY_MAPPED_OFFSET) - CRY_MAPPED_OFFSET_SECOND_KEYPAGE;
    }
    else
    {
      tmpKeyId = keyId + CRY_MAPPED_OFFSET;
    }
  }
  else /* keyIdType == CRY_30_RH850ICUM_KEYIDTYPE_RAW */
  {
    tmpKeyId = keyId;
    if (keyId > CRY_END_OF_FIRST_KEYPAGE)
    {
      tmpKeyId = keyId - CRY_RAW_OFFSET_SECOND_KEYPAGE;
    }
  }
  return tmpKeyId;
}

FUNC(uint32, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_GetRawIcumKeyId(uint32 keyId, uint32 keyIdType)
{
  uint32 tmpKeyId;

  if (keyIdType == CRY_30_RH850ICUM_KEYIDTYPE_MAPPED)
  {
    if (keyId == CRY_KEYID_MAPPED_MASTER_ECU_KEY)
    {
      tmpKeyId = CRY_30_RH850ICUM_MASTER_ECU_KEY;
    }
    else if (keyId == CRY_KEYID_MAPPED_KEY_RAM)
    {
      tmpKeyId = CRY_30_RH850ICUM_KEY_RAM;
    }
    else if (keyId > CRY_MAPPED_OFFSET_SECOND_KEYPAGE)     /* Check if second keyslot page shall be used */
    {
      tmpKeyId = (keyId + CRY_MAPPED_OFFSET);
    }
    else
    {
      tmpKeyId = keyId + CRY_MAPPED_OFFSET;
    }
  }
  else /* keyIdType == CRY_30_RH850ICUM_KEYIDTYPE_RAW */
  {
    tmpKeyId = keyId;
    if (keyId > CRY_END_OF_FIRST_KEYPAGE)
    {
      tmpKeyId = keyId;
    }
  }
  return tmpKeyId;
}

FUNC(void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_TriggerServiceAndWait( P2VAR(r_icumif_isd_t, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) p_ISD)
{
  /* trigger the service request */
  R_ICUMIF_ServiceRequest(p_ISD);

  /* go in HALT mode    */
  /* wait for interrupt */
  while (!R_ICUMIF_IsServiceCompleted(p_ISD))
  {
    /*
    __asm("halt");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    __asm("nop");
    */
  }
}

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_LoadPlainKey
 **********************************************************************************************************************/
/*! \brief        The Cry_30_Rh850Icum_LoadPlainKey function updates the RAM key memory slot with a 128-bit plain text key.
 *  \param[in]    key           Pointer to the 128-bit plain text key.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 **********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_LoadPlainKey( P2CONST(uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) key )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  r_icumif_isd_t * p_ISD = &ISD;


  p_ISD->service_id = SERVICE_03_AES_KEY_UPDATE_PLAIN;
  p_ISD->p_callbackfunc = 0;
  p_ISD->job_id = 0;

  /* not working as expected, workaround see lines below
  p_ISD->prm.KEY_UPDATE_PLAIN.key_group = KEY_GRP_SHE;
  p_ISD->prm.KEY_UPDATE_PLAIN.key_id = SHE_RAM_KEY;
  */

  p_ISD->prm.KEY_UPDATE_PLAIN.key_group = KEY_GRP_AES_RAM;
  p_ISD->prm.KEY_UPDATE_PLAIN.key_id = 0;

  p_ISD->prm.KEY_UPDATE_PLAIN.p_key_value = key;
  p_ISD->prm.KEY_UPDATE_PLAIN.key_size_in_bytes = AES_BLOCK_SIZE_IN_BYTES;
  p_ISD->prm.KEY_UPDATE_PLAIN.mem_cluster_verif = 0;

  p_ISD->prm.KEY_UPDATE_PLAIN.flags.encryption = 1;
  p_ISD->prm.KEY_UPDATE_PLAIN.flags.decryption = 1;
  p_ISD->prm.KEY_UPDATE_PLAIN.flags.cmac_generation = 1;
  p_ISD->prm.KEY_UPDATE_PLAIN.flags.cmac_verification = 1;
  p_ISD->prm.KEY_UPDATE_PLAIN.flags.disable_on_debug = 0;

  Cry_30_Rh850Icum_TriggerServiceAndWait(p_ISD);

  if (p_ISD->service_result != SERV_OK)
  {
    retVal = CSM_E_NOT_OK;
  }
  else
  {
    retVal = CSM_E_OK;
  }

  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CancelCommand
 **********************************************************************************************************************/
/*! \brief        The Cry_30_Rh850Icum_CancelCommand cancels the current executing command on the ICU.
 **********************************************************************************************************************/
FUNC( void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CancelCommand( void )
{
  /* ICUM does not support the cancel command */
}




#define CRY_30_RH850ICUM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  END OF FILE: CRY_30_RH850ICUM_COMMONUTIL.C
 *********************************************************************************************************************/