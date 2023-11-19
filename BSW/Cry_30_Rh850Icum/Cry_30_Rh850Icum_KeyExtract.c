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
 *         File:  Cry_30_Rh850Icum_KeyExtract.c
 *    Component:  DrvCry_Rh850Icum
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  Implements the KeyExtract CRY API for the ICUMB.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define CRY_30_RH850ICUM_KEYEXTRACT_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_Rh850Icum.h"
#include "Csm_Cbk.h"
#include "Cry_30_Rh850Icum_KeyExtract.h"
#include "Cry_30_Rh850Icum_CommonUtil.h"

#if ( CRY_30_RH850ICUM_KEYEXTRACTCONFIG == STD_ON )
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#define CRY_30_RH850ICUM_KEYEXTRACT_USE_SYNC_JOB_PROCESSING       CRY_30_RH850ICUM_USE_SYNC_JOB_PROCESSING
#define CRY_30_RH850ICUM_KEYEXTRACT_KEYUPDATE                     (64u)
#define CRY_30_RH850ICUM_KEYEXTRACT_KEYUPDATE_WITH_KEYID          (65u)
#define CRY_30_RH850ICUM_KEYEXTRACT_DEFAULT_KEY_LENGTH            (16u)
#define CRY_30_RH850ICUM_KEYEXTRACT_BLOCK_LENGTH                  (16u)

#define CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_KEYSLOT_ID             (1u)
#define CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M1                     (16u)
#define CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M2                     (32u)
#define CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M3                     (16u)
#define CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M4                     (32u)
#define CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M5                     (16u)

#define CRY_30_RH850ICUM_KEYEXTRACT_OFFSET_M1                     (0u)
#define CRY_30_RH850ICUM_KEYEXTRACT_OFFSET_M2                     (CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M1)
#define CRY_30_RH850ICUM_KEYEXTRACT_OFFSET_M3                     (CRY_30_RH850ICUM_KEYEXTRACT_OFFSET_M2 + CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M2)
#define CRY_30_RH850ICUM_KEYEXTRACT_OFFSET_M4                     (CRY_30_RH850ICUM_KEYEXTRACT_OFFSET_M3 + CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M3)
#define CRY_30_RH850ICUM_KEYEXTRACT_OFFSET_M5                     (CRY_30_RH850ICUM_KEYEXTRACT_OFFSET_M4 + CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M4)

#define CRY_30_RH850ICUM_KEYEXTRACT_KEY_INFORMATION_OFFSET        (15u)
#define CRY_30_RH850ICUM_KEYEXTRACT_AUTHID_MASK                   (0xF0)
#define CRY_30_RH850ICUM_KEYEXTRACT_KEYID_MASK                    (0x0F)

#define CRY_30_RH850ICUM_KEYEXTRACT_END_OF_FIRST_KEYPAGE          (CRY_30_RH850ICUM_KEY_RAM)
#define CRY_30_RH850ICUM_KEYEXTRACT_MAPPED_OFFSET                 (3u)
#define CRY_30_RH850ICUM_KEYEXTRACT_MAPPED_OFFSET_SECOND_KEYPAGE  (10u)
#define CRY_30_RH850ICUM_KEYEXTRACT_RAW_OFFSET_SECOND_KEYPAGE     (11u)
#define CRY_30_RH850ICUM_KEYEXTRACT_BITS_PER_BYTE                 (8u)

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

#if ( CRY_30_RH850ICUM_KEYEXTRACT_USE_SYNC_JOB_PROCESSING == STD_OFF )
typedef struct
{
  P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr;
  P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) dataPtr;
  uint32 dataLength;
  P2VAR( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr;
} Cry_30_Rh850Icum_KeyExtract_BufferType;
#endif /* ( CRY_30_RH850ICUM_KEYEXTRACT_USE_SYNC_JOB_PROCESSING == STD_OFF ) */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

#if ( CRY_30_RH850ICUM_KEYEXTRACT_USE_SYNC_JOB_PROCESSING == STD_OFF )
# define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_30_RH850ICUM_LOCAL VAR(Cry_30_Rh850Icum_KeyExtract_BufferType, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_KeyExtract_Buffer; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_RH850ICUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_30_RH850ICUM_LOCAL VAR(uint8, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_KeyExtract_Status; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_RH850ICUM_STOP_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif


/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define CRY_30_RH850ICUM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyExtractStartInternal( void );

CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyExtractUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) dataPtr,
                                                                            uint32 dataLength );

CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyExtractFinishInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                                            P2VAR( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr );

CRY_30_RH850ICUM_LOCAL FUNC(uint8, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_GetKeyIdRaw( uint8 keyId,
                                                                           Cry_30_Rh850Icum_KeyIdTypeOfKeyExtractConfigType keyIdType);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

 /**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyExtractStartInternal()
 **********************************************************************************************************************/
 /*! \brief     Function to convert a given keyId to it's RAW representation to be able to compare it to the authId
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC(uint8, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_GetKeyIdRaw( uint8 keyId,
  Cry_30_Rh850Icum_KeyIdTypeOfKeyExtractConfigType keyIdType)
{
  uint8 keyIdRaw;

  if (keyIdType == CRY_30_RH850ICUM_KEYIDTYPE_RAW)
  {
    keyIdRaw = keyId;
    if (keyId > CRY_30_RH850ICUM_KEYEXTRACT_END_OF_FIRST_KEYPAGE)
    {
      keyIdRaw = keyId - CRY_30_RH850ICUM_KEYEXTRACT_RAW_OFFSET_SECOND_KEYPAGE;
    }
  }
  else /* mapped */
  {
    switch (keyId)
    {
      case CRY_KEYID_MAPPED_MASTER_ECU_KEY:
        keyIdRaw = CRY_KEYID_RAW_MASTER_ECU_KEY;
        break;

      case CRY_KEYID_MAPPED_KEY_RAM:
        keyIdRaw = CRY_KEYID_RAW_KEY_RAM;
        break;

      default:
        keyIdRaw = keyId + CRY_30_RH850ICUM_KEYEXTRACT_MAPPED_OFFSET;
        if (keyId > CRY_30_RH850ICUM_KEYEXTRACT_MAPPED_OFFSET_SECOND_KEYPAGE)
        {
          keyIdRaw -= CRY_30_RH850ICUM_KEYEXTRACT_MAPPED_OFFSET_SECOND_KEYPAGE;
        }
        break;
    }
  }
  return keyIdRaw;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyExtractStartInternal()
 **********************************************************************************************************************/
/*! \brief      Common service start function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_KeyExtractStart()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyExtractStartInternal( void )
{
  Csm_ReturnType retVal;

  /* State and NULL_PTR check */
  if ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_IDLE )
  {
    retVal = CSM_E_OK;
    Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_KEYEXTRACT_START;
  }
  else
  {
    retVal = CSM_E_BUSY;
  }

  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyExtractUpdateInternal()
 **********************************************************************************************************************/
/*! \brief      Common service update function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_KeyExtractUpdate()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyExtractUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) dataPtr,
                                                                            uint32 dataLength )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  r_icumif_isd_t * p_ISD = &ISD;
#if ((CSM_MAX_ALIGN_SCALAR_TYPE / CRY_30_RH850ICUM_KEYEXTRACT_BITS_PER_BYTE  * CSM_SYM_KEY_MAX_SIZE) < (CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M4 + CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M5))
  uint8 dummyBuffer[CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M4 + CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M5] =
  {
    0x00
  };
#endif
  P2CONST(uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) m1m2m3Ptr = NULL_PTR;
  P2VAR(uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) m4m5Ptr = NULL_PTR;
  uint8 keyId = 0u;
  uint8 keyIdRaw_tmp = 0u;
  uint8 authId = 0u;
  Cry_30_Rh850Icum_KeyIdTypeOfKeyExtractConfigType keyIdType_tmp = CRY_30_RH850ICUM_KEYIDTYPE_RAW;

  P2CONST( Cry_30_Rh850Icum_KeyExtractConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_Rh850Icum_KeyExtractConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ))cfgPtr;

  /* PRQA S 0310 2 */ /* MD_CRY_11.4 */
  P2VAR(Cry_30_Rh850Icum_KeyExtractWorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) workSpacePtr =
    (P2VAR(Cry_30_Rh850Icum_KeyExtractWorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))Cry_30_Rh850Icum_GetAddrKeyExtractWorkSpace(Cry_30_Rh850Icum_GetKeyExtractWorkSpaceIdxOfKeyExtractConfig(contextPtr));

  /* State and NULL_PTR check */
  if ( ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_KEYEXTRACT_START )
    && ( cfgPtr != NULL_PTR )
    && ( dataPtr != NULL_PTR ) )
  {

    if (((dataLength == CRY_30_RH850ICUM_KEYEXTRACT_KEYUPDATE) || (dataLength == CRY_30_RH850ICUM_KEYEXTRACT_KEYUPDATE_WITH_KEYID)))
    {
      if (dataLength == CRY_30_RH850ICUM_KEYEXTRACT_KEYUPDATE)
      {
        /* Extract KeyID and AuthID from M1 */
        m1m2m3Ptr = &dataPtr[0u];
        keyId = (uint8)((m1m2m3Ptr[CRY_30_RH850ICUM_KEYEXTRACT_KEY_INFORMATION_OFFSET] & CRY_30_RH850ICUM_KEYEXTRACT_AUTHID_MASK) >> 4u);
        authId = (uint8)(m1m2m3Ptr[CRY_30_RH850ICUM_KEYEXTRACT_KEY_INFORMATION_OFFSET] & CRY_30_RH850ICUM_KEYEXTRACT_KEYID_MASK);

        /* The keyId has to be interpreted as RAW */
        keyIdType_tmp = CRY_30_RH850ICUM_KEYIDTYPE_RAW;
      }
      else /* CRY_30_RH850ICUM_KEYEXTRACT_KEYUPDATE_WITH_KEYID */
      {
        /* Extract KeyID from prepending byte and AuthID from M1 */
        m1m2m3Ptr = &dataPtr[1u];
        keyId = dataPtr[0u];
        authId = (uint8)((m1m2m3Ptr[CRY_30_RH850ICUM_KEYEXTRACT_KEY_INFORMATION_OFFSET] & CRY_30_RH850ICUM_KEYEXTRACT_AUTHID_MASK) >> 4u);

        /* The keyId has to be interpreted as specified in the configuration */
        keyIdType_tmp = Cry_30_Rh850Icum_GetKeyIdTypeOfKeyExtractConfig(contextPtr);
      }

      /* Check if authId is valid */
      keyIdRaw_tmp = Cry_30_Rh850Icum_GetKeyIdRaw(keyId, keyIdType_tmp);
      if ( ( authId == keyIdRaw_tmp)
        || ( authId == CRY_30_RH850ICUM_MASTER_ECU_KEY )
        || ((authId == CRY_30_RH850ICUM_SECRET_KEY) && (keyIdRaw_tmp == CRY_30_RH850ICUM_KEY_RAM) ) )
      {

        p_ISD->service_id = SERVICE_03_AES_KEY_UPDATE_SHE;
        p_ISD->p_callbackfunc = 0;
        p_ISD->job_id = 0;
        p_ISD->prm.KEY_UPDATE_SHE.p_M1 = &m1m2m3Ptr[CRY_30_RH850ICUM_KEYEXTRACT_OFFSET_M1];
        p_ISD->prm.KEY_UPDATE_SHE.p_M2 = &m1m2m3Ptr[CRY_30_RH850ICUM_KEYEXTRACT_OFFSET_M2];
        p_ISD->prm.KEY_UPDATE_SHE.p_M3 = &m1m2m3Ptr[CRY_30_RH850ICUM_KEYEXTRACT_OFFSET_M3];
        p_ISD->prm.KEY_UPDATE_SHE.extended_key_id = (uint8)(Cry_30_Rh850Icum_GetExtKeyFlag(keyId, keyIdType_tmp) & 0xFF);

        /* Check if size of data buffer in Csm_SymKeyType is big enougth to store M4 and M5 */
#if ((CSM_MAX_ALIGN_SCALAR_TYPE / CRY_30_RH850ICUM_KEYEXTRACT_BITS_PER_BYTE  * CSM_SYM_KEY_MAX_SIZE) >= (CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M4 + CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M5))
        /* The cast is needed to store data to the key buffer independant of the type of the key.data array */
        /* PRQA S 0310 1 */ /* MD_MSR_11.4 */
        m4m5Ptr = (P2VAR(uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))workSpacePtr->key.data;

        workSpacePtr->key.length = CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M4 + CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_M5;

        retVal = CSM_E_OK;
#else /* CsmSymKeyExtractMaxKeySize must be set to at least 48 */
        m4m5Ptr = dummyBuffer;
        workSpacePtr->key.length = 0u;

        retVal = CSM_E_NOT_OK;
#endif

        p_ISD->prm.KEY_UPDATE_SHE.p_M4 = &m4m5Ptr[0u];
        p_ISD->prm.KEY_UPDATE_SHE.p_M5 = &m4m5Ptr[32u];

        /* trigger the security service */
        Cry_30_Rh850Icum_TriggerServiceAndWait(p_ISD);

        if (p_ISD->service_result != SERV_OK)
        {
          retVal = CSM_E_NOT_OK;
        }

      }
      else /* AuthId was invalid */
      {
        workSpacePtr->key.length = 0u;
        retVal = CSM_E_NOT_OK;
      }
    }
    else if ( dataLength == CRY_30_RH850ICUM_KEYEXTRACT_DEFAULT_KEY_LENGTH )
    {
      /* Load key data to RAM key slot */
      if ( CSM_E_OK == Cry_30_Rh850Icum_LoadPlainKey( (P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ))dataPtr ) )
      {
        /* Set key ID to RAM key */
        if (Cry_30_Rh850Icum_GetKeyIdTypeOfKeyExtractConfig(contextPtr) == CRY_30_RH850ICUM_KEYIDTYPE_RAW)
        {
          workSpacePtr->key.data[0] = CRY_KEYID_RAW_KEY_RAM;
        }
        else /* CRY_30_RH850ICUM_KEYIDTYPE_MAPPED */
        {
          workSpacePtr->key.data[0] = CRY_KEYID_MAPPED_KEY_RAM;
        }

        workSpacePtr->key.length = CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_KEYSLOT_ID;

        retVal = CSM_E_OK;
      }
    }
    else if ( dataLength == CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_KEYSLOT_ID )
    {
      /* Assume key is key slot number */
      workSpacePtr->key.length = CRY_30_RH850ICUM_KEYEXTRACT_LENGTH_KEYSLOT_ID;
      workSpacePtr->key.data[0u] = dataPtr[0u];

      retVal = CSM_E_OK;
    }
    else
    {
      /* No key detected */
      workSpacePtr->key.length = 0u;

      retVal = CSM_E_NOT_OK;
    }

    /* TODO: Check for errors */
  }

  if ( retVal == CSM_E_OK)
  {
    Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_KEYEXTRACT_UPDATE;
  }

  CRY_30_RH850ICUM_DUMMY_STATEMENT(m4m5Ptr); /* PRQA S 3112 */ /* MD_MSR_14.2 */

  return retVal;
} /* PRQA S 6010 */ /* MD_MSR_STPTH */ /* PRQA S 6030 */ /* MD_MSR_STCYC */ /* PRQA S 6080 */ /* MD_MSR_STMIF */

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyExtractFinishInternal()
 **********************************************************************************************************************/
/*! \brief      Common service update function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_KeyExtractFinish()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyExtractFinishInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                                            P2VAR( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr ) /* PRQA S 3673 */ /* MD_CRY_16.7 */
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 i;

  P2CONST( Cry_30_Rh850Icum_KeyExtractConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_Rh850Icum_KeyExtractConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ))cfgPtr;

  /* PRQA S 0310 2 */ /* MD_CRY_11.4 */
  P2VAR(Cry_30_Rh850Icum_KeyExtractWorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) workSpacePtr =
    (P2VAR(Cry_30_Rh850Icum_KeyExtractWorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))Cry_30_Rh850Icum_GetAddrKeyExtractWorkSpace(Cry_30_Rh850Icum_GetKeyExtractWorkSpaceIdxOfKeyExtractConfig(contextPtr));


  uint32 keyLength;

  /* State and NULL_PTR check */
  if ( ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_KEYEXTRACT_UPDATE )
    && ( cfgPtr != NULL_PTR )
    && ( keyPtr != NULL_PTR ) )
  {
    keyLength = workSpacePtr->key.length;

    if (keyLength == 1)
    {
      keyPtr->data[0u] = workSpacePtr->key.data[0u];
    }
    else
    {
      /* Copy from buffer */
      for (i = 0u; i < keyLength; i++)
      {
        /* The cast is needed, in order to store the data to the key buffer, which can be uint8, uint16 or uint32 */
        /* PRQA S 0310 1 */ /* MD_MSR_11.4 */
        ((P2VAR(uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))keyPtr->data)[i] = ((P2VAR(uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))workSpacePtr->key.data)[i];
      }
    }

    /* Set key length */
    keyPtr->length = keyLength;

    retVal = CSM_E_OK;
  }

  Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_IDLE;

  return retVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyExtractInit()
 **********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the PRNG of the SHE.
 *  \context       Function could be called from task level only.
 *  \reentrant     Non reentrant
 *  \synchronous   Sync. or async. (depending on configuration)
 *  \note          Called by Cry_Init().
 **********************************************************************************************************************/
FUNC( void, CRY_30_RH850ICUM_CODE)  Cry_30_Rh850Icum_KeyExtractInit( void )
{
#if ( CRY_30_RH850ICUM_KEYEXTRACT_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_KeyExtract_Status = CRY_30_RH850ICUM_STATE_IDLE;
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyExtractMainFunction()
 **********************************************************************************************************************/
/*! \brief      API to be called to process the requested services.
 *  \context    Function could be called from task level only
 *  \note       Scheduled by the CSM
**********************************************************************************************************************/
FUNC(void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_KeyExtractMainFunction( void )
{
#if ( CRY_30_RH850ICUM_KEYEXTRACT_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_ReturnType retVal;
  switch(Cry_30_Rh850Icum_KeyExtract_Status)
  {
    case CRY_30_RH850ICUM_STATE_START:
    {
      retVal = Cry_30_Rh850Icum_KeyExtractStartInternal( );

      Cry_30_Rh850Icum_KeyExtract_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_SymKeyExtractCallbackNotification( retVal );
      break;
    }
    case CRY_30_RH850ICUM_STATE_UPDATE:
    {
      retVal = Cry_30_Rh850Icum_KeyExtractUpdateInternal( Cry_30_Rh850Icum_KeyExtract_Buffer.cfgPtr,
                                                Cry_30_Rh850Icum_KeyExtract_Buffer.dataPtr,
                                                Cry_30_Rh850Icum_KeyExtract_Buffer.dataLength );

      Cry_30_Rh850Icum_KeyExtract_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_SymKeyExtractCallbackNotification( retVal );
      break;
    }
    case CRY_30_RH850ICUM_STATE_FINISH:
    {
      retVal = Cry_30_Rh850Icum_KeyExtractFinishInternal( Cry_30_Rh850Icum_KeyExtract_Buffer.cfgPtr,
                                                Cry_30_Rh850Icum_KeyExtract_Buffer.keyPtr );

      Cry_30_Rh850Icum_KeyExtract_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_SymKeyExtractCallbackNotification( retVal );
      Csm_SymKeyExtractServiceFinishNotification();
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
 * Csm_SymKeyExtractStart
**********************************************************************************************************************/
/*! \brief        This interface shall be used to initialize the symmetrical key extraction.
 *  \param[in]    cfgId         Pointer to the configuration.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_BUSY    Request failed, service is still busy.
 *  \context      Called by CSM.
 **********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyExtractStart( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr ) /* PRQA S 3673 */ /* MD_CRY_16.7 */
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

#if ( CRY_30_RH850ICUM_KEYEXTRACT_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_KeyExtract_Status = CRY_30_RH850ICUM_STATE_START;
  retVal = CSM_E_OK;
#else
  retVal = Cry_30_Rh850Icum_KeyExtractStartInternal( );
#endif

  CRY_30_RH850ICUM_DUMMY_STATEMENT( cfgPtr ); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyExtractUpdate
**********************************************************************************************************************/
/*! \brief        This interface shall be used to feed the symmetrical key extraction service with the input data.
 *  \param[in]    cfgId         Pointer to the configuration.
 *  \param[in]    dataPtr       Holds a pointer to the data which contains the key in a format which cannot be used
 *                              directly by the CSM. From this data the key will be extracted in a CSM-conforming
 *                              format.
 *  \param[in]    dataLength    Holds the length of the data in bytes.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_BUSY    Request failed, service is still busy.
 *  \pre          Service was started.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyExtractUpdate( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                          P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) dataPtr,
                                                          uint32 dataLength )
{
#if ( CRY_30_RH850ICUM_KEYEXTRACT_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_KeyExtract_Buffer.cfgPtr = cfgPtr;
  Cry_30_Rh850Icum_KeyExtract_Buffer.dataPtr = dataPtr;
  Cry_30_Rh850Icum_KeyExtract_Buffer.dataLength = dataLength;
  Cry_30_Rh850Icum_KeyExtract_Status = CRY_30_RH850ICUM_STATE_UPDATE;
  return CSM_E_OK;
#else
  return Cry_30_Rh850Icum_KeyExtractUpdateInternal(cfgPtr, dataPtr, dataLength);
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyExtractFinish
**********************************************************************************************************************/
/*! \brief        This interface shall be used to finish the symmetrical key extraction service.
 *  \param[in]    cfgId         Pointer to the configuration.
 *  \param[inout] keyPtr        Holds a pointer to a structure where the result (i.e. the symmetrical key) is stored
 *                              in.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_BUSY    Request failed, service is still busy.
 *  \pre          Service was started.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyExtractFinish( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                          P2VAR( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr ) /* PRQA S 3673 */ /* MD_CRY_16.7 */
{
#if ( CRY_30_RH850ICUM_KEYEXTRACT_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_KeyExtract_Buffer.cfgPtr = cfgPtr;
  Cry_30_Rh850Icum_KeyExtract_Buffer.keyPtr = keyPtr;
  Cry_30_Rh850Icum_KeyExtract_Status = CRY_30_RH850ICUM_STATE_FINISH;
  return CSM_E_OK;
#else
  CRY_30_RH850ICUM_DUMMY_STATEMENT( cfgPtr ); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  return Cry_30_Rh850Icum_KeyExtractFinishInternal(cfgPtr, keyPtr);
#endif
}


#define CRY_30_RH850ICUM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ( CRY_30_RH850ICUM_KEYEXTRACTCONFIG == STD_ON ) */

/**********************************************************************************************************************
 *  END OF FILE: CRY_30_RH850ICUM_KEYEXTRACT_c
 *********************************************************************************************************************/
