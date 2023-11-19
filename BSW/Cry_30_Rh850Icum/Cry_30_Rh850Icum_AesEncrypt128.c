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
 *         File:  Cry_30_Rh850Icum_AesEncrypt128.c
 *    Component:  DrvCry_Rh850Icum
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  Implements the AES-128 encrypt CRY API for the ICUM.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define CRY_30_RH850ICUM_AESENCRYPT128_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_Rh850Icum.h"
#include "Csm_Cbk.h"
#include "Cry_30_Rh850Icum_AesEncrypt128.h"
#include "Cry_30_Rh850Icum_CommonUtil.h"
#include "r_icumif.api.h"

#if ( CRY_30_RH850ICUM_AESENCRYPT128CONFIG == STD_ON )
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

#define CRY_30_RH850ICUM_AESENCRYPT128_USE_SYNC_JOB_PROCESSING     CRY_30_RH850ICUM_USE_SYNC_JOB_PROCESSING
#define CRY_30_RH850ICUM_AESENCRYPT128_KEYSIZE                     (16u)
#define CRY_30_RH850ICUM_AESENCRYPT128_IVSIZE                      (16u)
#define CRY_30_RH850ICUM_AESENCRYPT128_IVBLOCK                     (1u)
#define CRY_30_RH850ICUM_AESENCRYPT128_BLOCKSIZE                   (16u)
#define CRY_30_RH850ICUM_AESENCRYPT128_USE_SHE_KEY_FLAG            (1u)

#if !defined (CRY_30_RH850ICUM_LOCAL)
# define CRY_30_RH850ICUM_LOCAL static
#endif

#if !defined (CRY_30_RH850ICUM_DUMMY_STATEMENT)
# if ( CRY_30_RH850ICUM_USE_DUMMY_STATEMENT == STD_ON )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define CRY_30_RH850ICUM_DUMMY_STATEMENT(statement) ( (void)(statement) )
# endif
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

typedef struct
{
  P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr;
  P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr;
  P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) InitVectorPtr;
  uint32 InitVectorLength;
  P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) plainTextPtr;
  uint32 plainTextLength;
  P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextPtr;
  P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextLengthPtr;
} Cry_30_Rh850Icum_AesEncrypt128_BufferType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

# define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_30_RH850ICUM_LOCAL VAR(Cry_30_Rh850Icum_AesEncrypt128_BufferType, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_AesEncrypt128_Buffer; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_RH850ICUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if ( CRY_30_RH850ICUM_AESENCRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
# define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_30_RH850ICUM_LOCAL VAR(uint8, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_AesEncrypt128_Status; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_RH850ICUM_STOP_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define CRY_30_RH850ICUM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_AesEncrypt128StartInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                            P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr,
                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) InitVectorPtr,
                                                                            uint32 InitVectorLength );

CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_AesEncrypt128UpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                             P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) plainTextPtr,
                                                                             uint32 plainTextLength,
                                                                             P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextPtr,
                                                                             P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextLengthPtr );

CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_AesEncrypt128FinishInternal( P2CONST(void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                                                    P2VAR(uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextPtr,
                                                                                                    P2VAR(uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextLengthPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_AesEncrypt128StartInternal()
 **********************************************************************************************************************/
/*! \brief      Common service start function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_AesEncrypt128Start()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_AesEncrypt128StartInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                            P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr,
                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) InitVectorPtr,
                                                                            uint32 InitVectorLength )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  P2CONST( Cry_30_Rh850Icum_AesEncrypt128ConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) contextPtr =
    (P2CONST(Cry_30_Rh850Icum_AesEncrypt128ConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ))cfgPtr;

  /* PRQA S 0310 2 */ /* MD_CRY_11.4 */
  P2VAR(Cry_30_Rh850Icum_AesEncrypt128WorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) workSpacePtr =
    (P2VAR(Cry_30_Rh850Icum_AesEncrypt128WorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))Cry_30_Rh850Icum_GetAddrAesEncrypt128WorkSpace(Cry_30_Rh850Icum_GetAesEncrypt128WorkSpaceIdxOfAesEncrypt128Config(contextPtr));

  /* State check */
  if ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_IDLE )
  {
    /* Range and NULL_PTR check */
    if ( ( cfgPtr != NULL_PTR )
      && ( keyPtr != NULL_PTR )
      && ( (keyPtr->length == CRY_30_RH850ICUM_AESENCRYPT128_KEYSIZE) || ( keyPtr->length == CRY_30_RH850ICUM_AESENCRYPT128_USE_SHE_KEY_FLAG ) )
      && ( ( InitVectorLength == CRY_30_RH850ICUM_AESENCRYPT128_IVSIZE ) || ( InitVectorLength == 0u ) ) )
    {
      /* Process keyPtr */
      if ( keyPtr->length == CRY_30_RH850ICUM_AESENCRYPT128_USE_SHE_KEY_FLAG )
      {
        /* Assume keyPtr->data is the key slot number */
        workSpacePtr->keyID = (uint32)(keyPtr->data[0] & 0xFFu);
        retVal = CSM_E_OK;
      }
      else if ( keyPtr->length == CRY_30_RH850ICUM_AESENCRYPT128_KEYSIZE )
      {
        /* Load key data to RAM key slot */
        if (CSM_E_OK == Cry_30_Rh850Icum_LoadPlainKey((P2CONST(uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))keyPtr->data) ) /* PRQA S 0310 */ /* MD_CRY_11.4 */
        {
          /* Set key ID to RAM key */
          if (Cry_30_Rh850Icum_GetKeyIdTypeOfAesEncrypt128Config(contextPtr) == CRY_30_RH850ICUM_KEYIDTYPE_RAW)
          {
            workSpacePtr->keyID = CRY_KEYID_RAW_KEY_RAM;
          }
          else
          {
            workSpacePtr->keyID = CRY_KEYID_MAPPED_KEY_RAM;
          }
          retVal = CSM_E_OK;
        }
      }
      else
      {
        retVal = CSM_E_NOT_OK;
      }

      Cry_30_Rh850Icum_AesEncrypt128_Buffer.cfgPtr = cfgPtr;
      Cry_30_Rh850Icum_AesEncrypt128_Buffer.keyPtr = keyPtr;
      Cry_30_Rh850Icum_AesEncrypt128_Buffer.InitVectorPtr = InitVectorPtr;
      Cry_30_Rh850Icum_AesEncrypt128_Buffer.InitVectorLength = InitVectorLength;
    }
  }
  else
  {
    retVal = CSM_E_BUSY;
  }

  if ( retVal == CSM_E_OK)
  {
    Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_AESENCRYPT_START;
  }

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* PRQA S 6030 */ /* MD_MSR_STCYC */


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_AesEncrypt128UpdateInternal()
 **********************************************************************************************************************/
/*! \brief      Common service update function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_AesEncrypt128Update()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_AesEncrypt128UpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                             P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) plainTextPtr,
                                                                             uint32 plainTextLength,
                                                                             P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextPtr,
                                                                             P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextLengthPtr )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  /* State and NULL_PTR and Range check */
  if ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_AESENCRYPT_START )
  {
    Cry_30_Rh850Icum_AesEncrypt128_Buffer.cfgPtr = cfgPtr;
    Cry_30_Rh850Icum_AesEncrypt128_Buffer.plainTextPtr = plainTextPtr;
    Cry_30_Rh850Icum_AesEncrypt128_Buffer.plainTextLength = plainTextLength;
    Cry_30_Rh850Icum_AesEncrypt128_Buffer.cipherTextPtr = cipherTextPtr;
    Cry_30_Rh850Icum_AesEncrypt128_Buffer.cipherTextLengthPtr = cipherTextLengthPtr;
    retVal = CSM_E_OK;
  }

  if ( retVal == CSM_E_OK)
  {
    Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_AESENCRYPT_UPDATE;
  }

  return retVal;
}

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_AesEncrypt128FinishInternal()
 **********************************************************************************************************************/
/*! \brief      Common service finish function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_AesEncrypt128Finish()
 **********************************************************************************************************************/
/* PRQA S 3673 3 */ /* MD_CSM_16.7 */
CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_AesEncrypt128FinishInternal( P2CONST(void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                                                    P2VAR(uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextPtr,
                                                                                                    P2VAR(uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextLengthPtr)

{
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint32 block_nb = 0;
  uint32 i;
  r_icumif_isd_t * p_ISD = &ISD;

  P2CONST(Cry_30_Rh850Icum_AesEncrypt128ConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) contextPtr =
    (P2CONST(Cry_30_Rh850Icum_AesEncrypt128ConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))cfgPtr;

  /* PRQA S 0310 2 */ /* MD_CRY_11.4 */
  P2VAR(Cry_30_Rh850Icum_AesEncrypt128WorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) workSpacePtr =
    (P2VAR(Cry_30_Rh850Icum_AesEncrypt128WorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))Cry_30_Rh850Icum_GetAddrAesEncrypt128WorkSpace(Cry_30_Rh850Icum_GetAesEncrypt128WorkSpaceIdxOfAesEncrypt128Config(contextPtr));

  /* State and NULL_PTR check */
  if ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_AESENCRYPT_UPDATE )
  {
    Cry_30_Rh850Icum_AesEncrypt128_Buffer.cipherTextPtr = cipherTextPtr;
    Cry_30_Rh850Icum_AesEncrypt128_Buffer.cipherTextLengthPtr = cipherTextLengthPtr;

    /* Check length - must be a multiple of 16 bytes */
    block_nb = Cry_30_Rh850Icum_AesEncrypt128_Buffer.plainTextLength / 16;

    if ((Cry_30_Rh850Icum_AesEncrypt128_Buffer.plainTextLength - (block_nb * 16)) == 0)
    {
      p_ISD->service_id = SERVICE_01_AES_CIPHER;
      p_ISD->p_callbackfunc = 0;
      p_ISD->job_id = 0;
      p_ISD->prm.AES_CIPHER.direction = CIPHER_DIR_ENCRYPTION;
      p_ISD->prm.AES_CIPHER.key_group = KEY_GRP_SHE;
      p_ISD->prm.AES_CIPHER.key_id = (uint8)Cry_30_Rh850Icum_GetRawIcumKeyId(workSpacePtr->keyID, Cry_30_Rh850Icum_GetKeyIdTypeOfAesEncrypt128Config(contextPtr));
      p_ISD->prm.AES_CIPHER.p_iv = Cry_30_Rh850Icum_AesEncrypt128_Buffer.InitVectorPtr;
      p_ISD->prm.AES_CIPHER.p_block_in = Cry_30_Rh850Icum_AesEncrypt128_Buffer.plainTextPtr;
      p_ISD->prm.AES_CIPHER.p_block_out = Cry_30_Rh850Icum_AesEncrypt128_Buffer.cipherTextPtr;
      p_ISD->prm.AES_CIPHER.size.nb_blocks = block_nb;
      p_ISD->prm.AES_CIPHER.job_slice = 0;
      p_ISD->prm.AES_CIPHER.job_cycle = JOB_ALL_AT_ONCE;

      if (Cry_30_Rh850Icum_GetBlockModeOfAesEncrypt128Config(contextPtr) == CRY_30_RH850ICUM_AESBLOCKMODE_CBC)
      {
        p_ISD->prm.AES_CIPHER.cipher_mode = CIPHER_MOD_CBC;
      }
      else
      {
        p_ISD->prm.AES_CIPHER.cipher_mode = CIPHER_MOD_ECB;
      }

      /* clear result buffer to 0 */
      for (i = 0; i <  (p_ISD->prm.AES_CIPHER.size.nb_blocks * AES_BLOCK_SIZE_IN_BYTES); i++)
      {
        p_ISD->prm.AES_CIPHER.p_block_out[i] = 0;
      }
      Cry_30_Rh850Icum_TriggerServiceAndWait(p_ISD);

      if (p_ISD->service_result != SERV_OK)
      {
        retVal = CSM_E_NOT_OK;
      }
      else
      {
        retVal = CSM_E_OK;
      }
    }
  }

  Cry_30_Rh850Icum_CancelCommand();
  Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_IDLE;

  return retVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_AesEncrypt128Init()
 **********************************************************************************************************************/
/*! \brief      Initializes the AES 128 encryption
 *  \context    System Startup
 *  \note       Called by Cry_Init
 **********************************************************************************************************************/
FUNC( void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_AesEncrypt128Init( void )
{
#if ( CRY_30_RH850ICUM_AESENCRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_AesEncrypt128_Status = CRY_30_RH850ICUM_STATE_IDLE;
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_AesEnrcryptMainFunction()
 **********************************************************************************************************************/
/*! \brief      API to be called to process the requested services.
 *  \context    Function could be called from task level only
 *  \note       Scheduled by the CSM
**********************************************************************************************************************/
FUNC(void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_AesEncrypt128MainFunction( void )
{
#if ( CRY_30_RH850ICUM_AESENCRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_ReturnType retVal;

  switch(Cry_30_Rh850Icum_AesEncrypt128_Status)
  {
    case CRY_30_RH850ICUM_STATE_START:
    {
      retVal=Cry_30_Rh850Icum_AesEncrypt128StartInternal(
        Cry_30_Rh850Icum_AesEncrypt128_Buffer.cfgPtr,
        Cry_30_Rh850Icum_AesEncrypt128_Buffer.keyPtr,
        Cry_30_Rh850Icum_AesEncrypt128_Buffer.InitVectorPtr,
        Cry_30_Rh850Icum_AesEncrypt128_Buffer.InitVectorLength );

      Cry_30_Rh850Icum_AesEncrypt128_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_SymEncryptCallbackNotification( retVal );
      break;
    }
    case CRY_30_RH850ICUM_STATE_UPDATE:
    {
      retVal=Cry_30_Rh850Icum_AesEncrypt128UpdateInternal(
        Cry_30_Rh850Icum_AesEncrypt128_Buffer.cfgPtr,
        Cry_30_Rh850Icum_AesEncrypt128_Buffer.plainTextPtr,
        Cry_30_Rh850Icum_AesEncrypt128_Buffer.plainTextLength,
        Cry_30_Rh850Icum_AesEncrypt128_Buffer.cipherTextPtr,
        Cry_30_Rh850Icum_AesEncrypt128_Buffer.cipherTextLengthPtr );

      Cry_30_Rh850Icum_AesEncrypt128_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_SymEncryptCallbackNotification( retVal );
      break;
    }
    case CRY_30_RH850ICUM_STATE_FINISH:
    {
      retVal=Cry_30_Rh850Icum_AesEncrypt128FinishInternal(
        Cry_30_Rh850Icum_AesEncrypt128_Buffer.cfgPtr,
        Cry_30_Rh850Icum_AesEncrypt128_Buffer.cipherTextPtr,
        Cry_30_Rh850Icum_AesEncrypt128_Buffer.cipherTextLengthPtr );

      Cry_30_Rh850Icum_AesEncrypt128_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_SymEncryptCallbackNotification( retVal );
      Csm_SymEncryptServiceFinishNotification();
      break;
    }
    default:
    {
      /* Nothing to do */
      break;
    }
  }
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_AesEncrypt128Start()
**********************************************************************************************************************/
/*! \brief        This interface shall be used to initialize the symmetrical encryption service of the CSM module.
 *  \param[in]    cfgPtr        Pointer to ConfigStructure
 *  \param[in]    keyPtr        Holds a pointer to the key which has to be used during the symmetrical encryption
 *                              operation.
 *  \param[in]    InitVectorPtr Holds a pointer to initialisation vector which has to be used during the symmetrical
 *                              encryption.
 *  \param[in]    InitVectorLength Holds a pointer to the initialisation vector which has to be used during the
 *                              symmetrical encryption.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_BUSY    Request failed, service is still busy.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_AesEncrypt128Start( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                            P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr,
                                                            P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) InitVectorPtr,
                                                            VAR(uint32, AUTOMATIC) InitVectorLength )
{
  Csm_ReturnType retVal;

#if ( CRY_30_RH850ICUM_AESENCRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_AesEncrypt128_Buffer.cfgPtr = cfgPtr;
  Cry_30_Rh850Icum_AesEncrypt128_Buffer.keyPtr = keyPtr;
  Cry_30_Rh850Icum_AesEncrypt128_Buffer.InitVectorPtr = InitVectorPtr;
  Cry_30_Rh850Icum_AesEncrypt128_Buffer.InitVectorLength = InitVectorLength;
  Cry_30_Rh850Icum_AesEncrypt128_Status = CRY_30_RH850ICUM_STATE_START;
  retVal = CSM_E_OK;
#else
  retVal = Cry_30_Rh850Icum_AesEncrypt128StartInternal( cfgPtr, keyPtr, InitVectorPtr, InitVectorLength );
#endif

  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_AesEncrypt128Update()
**********************************************************************************************************************/
/*! \brief        This interface shall be used to feed the symmetrical encryption service with the input data.
 *  \param[in]    cfgPtr        Pointer to ConfigStructure
 *  \param[in]    plainTextPtr  Holds a pointer to the data for which a encrypted text shall be computed.
 *  \param[in]    plainTextLength Contains the number of bytes for which the encrypted text shall be computed.
 *  \param[out]   cipherTextPtr Holds a pointer to the memory location which will hold the encrypted text.
 *  \param[in,out] cipherTextLengthPtr Holds a pointer to the memory location in which the length information is stored. On
 *                              calling this function this parameter shall contain the size of the provided buffer.
 *                              When the request has finished, the actual length of the returned encrypted text shall
 *                              be stored.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_SMALL_BUFFER  The provided buffer is too small to store the result and truncation was not
 *                              allowed.
 *  \pre          Service was started.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_AesEncrypt128Update( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                             P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) plainTextPtr,
                                                             uint32 plainTextLength,
                                                             P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextPtr,
                                                             P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextLengthPtr )
{
#if ( CRY_30_RH850ICUM_AESENCRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_AesEncrypt128_Buffer.cfgPtr = cfgPtr;
  Cry_30_Rh850Icum_AesEncrypt128_Buffer.plainTextPtr = plainTextPtr;
  Cry_30_Rh850Icum_AesEncrypt128_Buffer.plainTextLength = plainTextLength;
  Cry_30_Rh850Icum_AesEncrypt128_Buffer.cipherTextPtr = cipherTextPtr;
  Cry_30_Rh850Icum_AesEncrypt128_Buffer.cipherTextLengthPtr = cipherTextLengthPtr;
  Cry_30_Rh850Icum_AesEncrypt128_Status = CRY_30_RH850ICUM_STATE_UPDATE;
  return CSM_E_OK;
#else
  return Cry_30_Rh850Icum_AesEncrypt128UpdateInternal( cfgPtr, plainTextPtr, plainTextLength, cipherTextPtr, cipherTextLengthPtr );
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_AesEncrypt128Finish()
**********************************************************************************************************************/
/*! \brief        This interface shall be used to finish the symmetrical encryption service.
 *  \param[in]    cfgPtr        Pointer to ConfigStructure
 *  \param[out]   cipherTextPtr Holds a pointer to the memory location which will hold the encrypted text.
 *  \param[in,out] cipherTextLengthPtr Holds a pointer to the memory location in which the length information is stored. On
 *                              calling this function this parameter shall contain the size of the provided buffer.
 *                              When the request has finished, the actual length of the returned encrypted text shall
 *                              be stored.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_SMALL_BUFFER  The provided buffer is too small to store the result and truncation was not
 *                              allowed.
 *  \pre          Service was started.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_AesEncrypt128Finish( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,               /* PRQA S 3673 */ /* MD_CRY_16.7 */
                                                             P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextPtr,         /* PRQA S 3673 */ /* MD_CRY_16.7 */
                                                             P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cipherTextLengthPtr ) /* PRQA S 3673 */ /* MD_CRY_16.7 */
{
  CRY_30_RH850ICUM_DUMMY_STATEMENT( cfgPtr );              /* PRQA S 3112 */ /* MD_MSR_14.2 */
  CRY_30_RH850ICUM_DUMMY_STATEMENT( cipherTextPtr );       /* PRQA S 3112 */ /* MD_MSR_14.2 */
  CRY_30_RH850ICUM_DUMMY_STATEMENT( cipherTextLengthPtr ); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#if ( CRY_30_RH850ICUM_AESENCRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_AesEncrypt128_Status = CRY_30_RH850ICUM_STATE_FINISH;
  return CSM_E_OK;
#else
  return Cry_30_Rh850Icum_AesEncrypt128FinishInternal(cfgPtr, cipherTextPtr, cipherTextLengthPtr);
#endif
}


#define CRY_30_RH850ICUM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ( CRY_30_RH850ICUM_AESENCRYPT128CONFIG == STD_ON ) */
/**********************************************************************************************************************
 * Module specific MISRA deviations
 *********************************************************************************************************************/
/* module specific MISRA deviations:

MD_CRY_11.4:
Reason: Cast needed to use SHE as a CSM service.
Risk: Invalid memory access.
Prevention: Covered by code review and test.

 */

/**********************************************************************************************************************
 *  END OF FILE: CRY_30_RH850ICUM_AESENCRYPT128.C
 *********************************************************************************************************************/
