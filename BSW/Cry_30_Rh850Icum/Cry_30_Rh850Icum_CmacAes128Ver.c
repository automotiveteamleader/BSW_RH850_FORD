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
 *         File:  Cry_30_Rh850Icum_CmacAes128Ver.c
 *    Component:  DrvCry_Rh850Icum
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  Implements the CMAC verify CRY API for the ICUMB.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define CRY_30_RH850ICUM_CMACAES128VER_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_Rh850Icum.h"
#include "Csm_Cbk.h"
#include "Cry_30_Rh850Icum_CommonUtil.h"

#if ( CRY_30_RH850ICUM_CMACAES128VERCONFIG == STD_ON )
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#define CRY_30_RH850ICUM_CMACAES128VER_USE_SYNC_JOB_PROCESSING     CRY_30_RH850ICUM_USE_SYNC_JOB_PROCESSING
#define CRY_30_RH850ICUM_CMACAES128VER_KEYSIZE                     (16u)
#define CRY_30_RH850ICUM_CMACAES128VER_USE_SHE_KEY                 (1u)
#define CRY_30_RH850ICUM_CMACAES128VER_MAC_LENGTH                  (16u)
#define CRY_30_RH850ICUM_CMACAES128VER_MAX_MAC_LENGTH_IN_BITS      (128u)
#define CRY_30_RH850ICUM_CMACAES128VER_BLOCKSIZE                   (16u)
#define CRY_30_RH850ICUM_CMACAES128VER_BITS_PER_BYTE               (8u)
#define CRY_30_RH850ICUM_CMACAES128VER_VERIFICATION_STATUS_OFFSET  (0u)
#define CRY_30_RH850ICUM_CMACAES128VER_VERIFICATION_STATUS_MASK    (0x01u)

#define USE_CMAC_GENERATE_FOR_BIT_VERIFICATION


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
  P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) dataPtr;
  uint32 dataLength;
  P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) MacPtr;
  uint32 MacLength;
  P2VAR( Csm_VerifyResultType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultPtr;
} Cry_30_Rh850Icum_CmacAes128Ver_BufferType;

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

# define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_30_RH850ICUM_LOCAL VAR(Cry_30_Rh850Icum_CmacAes128Ver_BufferType, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_CmacAes128Ver_Buffer; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_RH850ICUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if ( CRY_30_RH850ICUM_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
# define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_30_RH850ICUM_LOCAL VAR(uint8, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_CmacAes128Ver_Status; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_RH850ICUM_STOP_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define CRY_30_RH850ICUM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128VerStartInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                                                   P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr);

CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128VerUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                                                    P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) dataPtr,
                                                                                                    uint32 dataLength);

CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128VerFinishInternal( P2CONST(void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr, 
                                                                                                    P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) MacPtr,
                                                                                                    uint32 MacLength,
                                                                                                    P2VAR( Csm_VerifyResultType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultPtr );

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128VerStartInternal()
 **********************************************************************************************************************/
/*! \brief      Common service start function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_CmacAes128VerStart()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128VerStartInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                                                   P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  P2CONST( Cry_30_Rh850Icum_CmacAes128VerConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_Rh850Icum_CmacAes128VerConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ))cfgPtr;

  /* PRQA S 0310 2 */ /* MD_CRY_11.4 */
  P2VAR(Cry_30_Rh850Icum_CmacAes128VerWorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) workSpacePtr =
    (P2VAR(Cry_30_Rh850Icum_CmacAes128VerWorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))Cry_30_Rh850Icum_GetAddrCmacAes128VerWorkSpace(Cry_30_Rh850Icum_GetCmacAes128VerWorkSpaceIdxOfCmacAes128VerConfig(contextPtr));

  /* State, Range and NULL_PTR check */
  if ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_IDLE )
  {
    if ( ( cfgPtr != NULL_PTR )
      && ( keyPtr != NULL_PTR )
      && ( (keyPtr->length == CRY_30_RH850ICUM_CMACAES128VER_KEYSIZE) || ( keyPtr->length == CRY_30_RH850ICUM_CMACAES128VER_USE_SHE_KEY ) ) )
    {
      if ( keyPtr->length == CRY_30_RH850ICUM_CMACAES128VER_USE_SHE_KEY )
      {
        /* Length is 1 -> assume key data is slot id */
        /* Save keyID into the buffer, so that it can be used in the update-function */
        workSpacePtr->keyID = (uint32)(keyPtr->data[0] & 0xFFu);
        retVal = CSM_E_OK;
      }
      else if ( keyPtr->length == CRY_30_RH850ICUM_CMACAES128VER_KEYSIZE )
      {
        /* Length matches key size */
        /* Load the key data to the RAM key slot of the ICUMB */
        if ( CSM_E_OK == Cry_30_Rh850Icum_LoadPlainKey( (P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ))keyPtr->data ) ) /* PRQA S 0310 */ /* MD_CRY_11.4 */
        {
          /* Set RAM key slot as ID */
          if (Cry_30_Rh850Icum_GetKeyIdTypeOfCmacAes128VerConfig(contextPtr) == CRY_30_RH850ICUM_KEYIDTYPE_RAW)
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

      Cry_30_Rh850Icum_CmacAes128Ver_Buffer.cfgPtr = cfgPtr;
      Cry_30_Rh850Icum_CmacAes128Ver_Buffer.keyPtr = keyPtr;
    }
  }
  else
  {
    retVal = CSM_E_BUSY;
  }
  if ( retVal == CSM_E_OK)
  {
    Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_MACVERIFY_START;
  }

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128VerUpdateInternal()
 **********************************************************************************************************************/
/*! \brief      Common service update function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_CmacAes128VerUpdate()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128VerUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                                                    P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) dataPtr,
                                                                                                    uint32 dataLength)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  /* State and NULL_PTR check */
  if ( ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_MACVERIFY_START )
    && ( cfgPtr != NULL_PTR )
    && ( dataPtr != NULL_PTR ) )
  {
    Cry_30_Rh850Icum_CmacAes128Ver_Buffer.cfgPtr = cfgPtr;
    Cry_30_Rh850Icum_CmacAes128Ver_Buffer.dataPtr = dataPtr;
    Cry_30_Rh850Icum_CmacAes128Ver_Buffer.dataLength = dataLength;
    retVal = CSM_E_OK;
  }

  if ( retVal == CSM_E_OK)
  {
    Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_MACVERIFY_UPDATE;
  }

  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128VerFinishInternal()
 **********************************************************************************************************************/
/*! \brief      Common service finish function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_CmacAes128VerFinish()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128VerFinishInternal( P2CONST(void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                                                    P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) MacPtr,
                                                                                                    uint32 MacLength,
                                                                                                    P2VAR( Csm_VerifyResultType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultPtr)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  Csm_VerifyResultType verifyResult = CSM_E_VER_NOT_OK;
#ifdef ICUM_MAC_IN_BIT_SUPPORT
  uint32 macLengthInBits;
#endif
  uint8 macLengthInBytes;
  uint64 msgLengthInBit;
#ifndef USE_CMAC_GENERATE_FOR_BIT_VERIFICATION
  uint8 macBuffer[16];
  uint8 verifyBitMask = 0u;
  uint32 numberBitsInLastByte = 0u;
  uint8_least i;
#endif
  r_icumif_isd_t * p_ISD = &ISD;

  P2CONST(Cry_30_Rh850Icum_CmacAes128VerConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) contextPtr =
    (P2CONST(Cry_30_Rh850Icum_CmacAes128VerConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))cfgPtr;

  /* PRQA S 0310 2 */ /* MD_CRY_11.4 */
  P2VAR(Cry_30_Rh850Icum_CmacAes128VerWorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) workSpacePtr =
    (P2VAR(Cry_30_Rh850Icum_CmacAes128VerWorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))Cry_30_Rh850Icum_GetAddrCmacAes128VerWorkSpace(Cry_30_Rh850Icum_GetCmacAes128VerWorkSpaceIdxOfCmacAes128VerConfig(contextPtr));

  msgLengthInBit = ((uint64)Cry_30_Rh850Icum_CmacAes128Ver_Buffer.dataLength) * CRY_30_RH850ICUM_CMACAES128VER_BITS_PER_BYTE;

  /* State, Range and NULL_PTR check */
  if ( ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_MACVERIFY_UPDATE )
    && ( cfgPtr != NULL_PTR )
    && ( MacPtr != NULL_PTR )
    && ( resultPtr != NULL_PTR )
    && ( ( MacLength <= CRY_30_RH850ICUM_CMACAES128VER_MAC_LENGTH ) || (MacLength <= (CRY_30_RH850ICUM_CMACAES128VER_MAC_LENGTH * CRY_30_RH850ICUM_CMACAES128VER_BITS_PER_BYTE)) ) /* Check for valid MAC length */
    && (msgLengthInBit != 0u ) ) /* Check data length to avoid ERC_GENERAL_ERROR from ICUM */
  {
    if (MacLength != 0)
    {
      /* Interpret the passed mac */
      if (Cry_30_Rh850Icum_IsLengthInBytesOfCmacAes128VerConfig(contextPtr))
      {
#ifdef ICUM_MAC_IN_BIT_SUPPORT
        macLengthInBits = MacLength * CRY_30_RH850ICUM_CMACAES128VER_BITS_PER_BYTE;
#endif
        macLengthInBytes = (uint8)MacLength;
      }
      else
      {
#ifdef ICUM_MAC_IN_BIT_SUPPORT
        macLengthInBits = MacLength;
#endif
        macLengthInBytes = (uint8)(MacLength / CRY_30_RH850ICUM_CMACAES128VER_BITS_PER_BYTE);
#ifndef USE_CMAC_GENERATE_FOR_BIT_VERIFICATION
        /* Discard the bits in the last byte - ICUM does not support verification witrh bits using the verification command */
        if ((MacLength & (CRY_30_RH850ICUM_CMACAES128VER_BITS_PER_BYTE - 1)) != 0u) /* Calculate modulo */
        {
          /* Add one byte to the length, because number of bits is not a multiple of 8 */
          macLengthInBytes += 1;
        }
#endif
      }

      p_ISD->service_id = SERVICE_01_AES_CMAC;
      p_ISD->p_callbackfunc = 0;
      p_ISD->job_id = 0;
      p_ISD->prm.AES_CMAC.key_group = KEY_GRP_SHE;
      p_ISD->prm.AES_CMAC.key_id = (uint8)Cry_30_Rh850Icum_GetRawIcumKeyId(workSpacePtr->keyID, Cry_30_Rh850Icum_GetKeyIdTypeOfCmacAes128VerConfig(contextPtr));
      p_ISD->prm.AES_CMAC.p_msg = Cry_30_Rh850Icum_CmacAes128Ver_Buffer.dataPtr;
      p_ISD->prm.AES_CMAC.msg_size_in_bytes = Cry_30_Rh850Icum_CmacAes128Ver_Buffer.dataLength;
      p_ISD->prm.AES_CMAC.job_slice = 0;

#ifndef USE_CMAC_GENERATE_FOR_BIT_VERIFICATION
      p_ISD->prm.AES_CMAC.cmac_operation = CMAC_GENERATION;
      p_ISD->prm.AES_CMAC.p_cmac = macBuffer;
      p_ISD->prm.AES_CMAC.cmac_size_in_bytes = 16;
#else
      p_ISD->prm.AES_CMAC.cmac_operation = CMAC_VERIFICATION;
      p_ISD->prm.AES_CMAC.p_cmac = (P2VAR(uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))MacPtr; /* PRQA S 0311 */ /* MD_CRY_11.5 */
      p_ISD->prm.AES_CMAC.cmac_size_in_bytes = macLengthInBytes;
#endif

      Cry_30_Rh850Icum_TriggerServiceAndWait(p_ISD);

      retVal = CSM_E_OK;
      verifyResult = CSM_E_VER_OK;

#ifndef USE_CMAC_GENERATE_FOR_BIT_VERIFICATION
      for (i = 0u; i < (macLengthInBytes - 1u); i++)
      {
        if (MacPtr[i] != macBuffer[i])
        {
          /* Verification does not match */
          verifyResult = CSM_E_VER_NOT_OK;
        }
      }
      if (Cry_30_Rh850Icum_IsLengthInBytesOfCmacAes128VerConfig(contextPtr))
      {
        /* Bitmask contains all 8 bit */
        verifyBitMask = 0xFFu;
      }
      else
      {
        /* Compute number of bits to verify in the last byte */
        numberBitsInLastByte = MacLength & (CRY_30_RH850ICUM_CMACAES128VER_BITS_PER_BYTE - 1u); /* Calculate modulo */
        if (numberBitsInLastByte == 0u)
        {
          numberBitsInLastByte = CRY_30_RH850ICUM_CMACAES128VER_BITS_PER_BYTE;
        }
        /* Generate bitmask which contains all bits to be verified
        * This depends on the byteorder */
#if (CPU_BIT_ORDER == LSB_FIRST)   /*little endian bit ordering*/
        for (i = CRY_30_RH850ICUM_CMACAES128VER_BITS_PER_BYTE; i > (CRY_30_RH850ICUM_CMACAES128VER_BITS_PER_BYTE - numberBitsInLastByte); i--)
        {
          verifyBitMask |= (1u << (i - 1u));
        }
#else
        for (i = 0u; i < numberBitsInLastByte; i++)
        {
          verifyBitMask |= (1u << i);
        }
#endif
      }
      /* Verify the last masked byte */
      if ((MacPtr[macLengthInBytes - 1u] & verifyBitMask)
        != (macBuffer[macLengthInBytes - 1u] & verifyBitMask))
      {
        verifyResult = CSM_E_VER_NOT_OK;
      }

#else
      retVal = CSM_E_OK;
      if (p_ISD->prm.AES_CMAC.verification_result == VERIFICATION_PASS)
      {
        verifyResult = CSM_E_VER_OK;
      }
      else
      {
        verifyResult = CSM_E_VER_NOT_OK;

        if (p_ISD->service_result != SERV_OK)
        {
          retVal = CSM_E_NOT_OK;
        }
        else
        {
          retVal = CSM_E_OK;
        }
      }
#endif
    }
    else /* MacLength == 0 */
    {
      verifyResult = CSM_E_VER_OK;

      if (p_ISD->service_result != SERV_OK)
      {
        retVal = CSM_E_NOT_OK;
      }
      else
      {
        retVal = CSM_E_OK;
      }
    }

    /* Write back the result of the verification */
    *resultPtr = verifyResult;
  }

  Cry_30_Rh850Icum_CancelCommand();
  Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_IDLE;

  return retVal;
}


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128VerInit()
 **********************************************************************************************************************/
/*! \brief      Initializes the MAC generation
 *  \context    System Startup
 *  \note       Called by Cry_Init
 **********************************************************************************************************************/
FUNC( void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128VerInit( void )
{
#if ( CRY_30_RH850ICUM_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_CmacAes128Ver_Status = CRY_30_RH850ICUM_STATE_IDLE;
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128VerMainFunction()
 **********************************************************************************************************************/
/*! \brief      API to be called to process the requested services.
 *  \context    Function could be called from task level only
 *  \note       Scheduled by the CSM
**********************************************************************************************************************/
FUNC(void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128VerMainFunction( void )
{
#if ( CRY_30_RH850ICUM_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_ReturnType retVal;

  switch(Cry_30_Rh850Icum_CmacAes128Ver_Status)
  {
    case CRY_30_RH850ICUM_STATE_START:
    {
      retVal=Cry_30_Rh850Icum_CmacAes128VerStartInternal(
        Cry_30_Rh850Icum_CmacAes128Ver_Buffer.cfgPtr,
        Cry_30_Rh850Icum_CmacAes128Ver_Buffer.keyPtr );

      Cry_30_Rh850Icum_CmacAes128Ver_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_MacVerifyCallbackNotification( retVal );
      break;
    }
    case CRY_30_RH850ICUM_STATE_UPDATE:
    {
      retVal=Cry_30_Rh850Icum_CmacAes128VerUpdateInternal(
        Cry_30_Rh850Icum_CmacAes128Ver_Buffer.cfgPtr,
        Cry_30_Rh850Icum_CmacAes128Ver_Buffer.dataPtr,
        Cry_30_Rh850Icum_CmacAes128Ver_Buffer.dataLength );

      Cry_30_Rh850Icum_CmacAes128Ver_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_MacVerifyCallbackNotification( retVal );
      break;
    }
    case CRY_30_RH850ICUM_STATE_FINISH:
    {
      retVal=Cry_30_Rh850Icum_CmacAes128VerFinishInternal(
        Cry_30_Rh850Icum_CmacAes128Ver_Buffer.cfgPtr,
        Cry_30_Rh850Icum_CmacAes128Ver_Buffer.MacPtr,
        Cry_30_Rh850Icum_CmacAes128Ver_Buffer.MacLength,
        Cry_30_Rh850Icum_CmacAes128Ver_Buffer.resultPtr );

      Cry_30_Rh850Icum_CmacAes128Ver_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_MacVerifyCallbackNotification( retVal );
      Csm_MacVerifyServiceFinishNotification();
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
 * Cry_30_Rh850Icum_CmacAes128VerStart()
**********************************************************************************************************************/
/*! \brief        This interface shall be used to initialize the MAC verify service of the CSM module.
 *  \param[in]    cfgPtr        Pointer to ConfigStructure
 *  \param[in]    keyPtr        Holds a pointer to the key necessary for the MAC verification.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_BUSY    Request failed, service is still busy.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128VerStart( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                                 P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

#if ( CRY_30_RH850ICUM_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
    Cry_30_Rh850Icum_CmacAes128Ver_Buffer.cfgPtr = cfgPtr;
    Cry_30_Rh850Icum_CmacAes128Ver_Buffer.keyPtr = keyPtr;
    Cry_30_Rh850Icum_CmacAes128Ver_Status = CRY_30_RH850ICUM_STATE_START;
    retVal = CSM_E_OK;
#else
    retVal = Cry_30_Rh850Icum_CmacAes128VerStartInternal( cfgPtr, keyPtr );
#endif

  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128VerUpdate()
**********************************************************************************************************************/
/*! \brief        This interface shall be used to feed the MAC verification service with the input data.
 *  \param[in]    cfgPtr        Pointer to ConfigStructure
 *  \param[in]    dataPtr       Holds a pointer to the data for which a MAC shall be verified.
 *  \param[in]    dataLength    Contains the number of bytes for which the MAC shall be verified.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \pre          Service was started.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128VerUpdate( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                                  P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) dataPtr,
                                                                                  uint32 dataLength)
{
#if ( CRY_30_RH850ICUM_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_CmacAes128Ver_Buffer.cfgPtr = cfgPtr;
  Cry_30_Rh850Icum_CmacAes128Ver_Buffer.dataPtr = dataPtr;
  Cry_30_Rh850Icum_CmacAes128Ver_Buffer.dataLength = dataLength;
  Cry_30_Rh850Icum_CmacAes128Ver_Status = CRY_30_RH850ICUM_STATE_UPDATE;
  return CSM_E_OK;
#else
  return Cry_30_Rh850Icum_CmacAes128VerUpdateInternal( cfgPtr, dataPtr, dataLength );
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128VerFinish()
**********************************************************************************************************************/
/*! \brief        This interface shall be used to finish the MAC verification service.
 *  \param[in]    cfgPtr        Pointer to ConfigStructure
 *  \param[in]    MacPtr        Holds a pointer to the memory location which will hold the MAC to verify.
 *  \param[in]    MacLength     Holds the length of the MAC to be verified.
 *                              Note: the computed MAC will be internally truncated to this length.
 *  \param[out]   resultPtr     Holds a pointer to the memory location which will hold the result of the MAC verification.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \pre          Service was started.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128VerFinish( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                                  P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) MacPtr,
                                                                                  uint32 MacLength,
                                                                                  P2VAR( Csm_VerifyResultType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultPtr)
{
  CRY_30_RH850ICUM_DUMMY_STATEMENT( cfgPtr ); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#if ( CRY_30_RH850ICUM_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_CmacAes128Ver_Buffer.cfgPtr = cfgPtr;
  Cry_30_Rh850Icum_CmacAes128Ver_Buffer.MacPtr = MacPtr;
  Cry_30_Rh850Icum_CmacAes128Ver_Buffer.MacLength = MacLength;
  Cry_30_Rh850Icum_CmacAes128Ver_Buffer.resultPtr = resultPtr;
  Cry_30_Rh850Icum_CmacAes128Ver_Status = CRY_30_RH850ICUM_STATE_FINISH;
  return CSM_E_OK;
#else
  return Cry_30_Rh850Icum_CmacAes128VerFinishInternal(cfgPtr, MacPtr, MacLength, resultPtr );
#endif
}


#define CRY_30_RH850ICUM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ( CRY_30_RH850ICUM_CMACAES128VERCONFIG == STD_ON ) */
/**********************************************************************************************************************
 * Module specific MISRA deviations
 *********************************************************************************************************************/
/* module specific MISRA deviations:

MD_CRY_11.4:
Reason: Cast needed to use SHE as a CSM service.
Risk: Invalid memory access.
Prevention: Covered by code review and test.

MD_CRY_11.5:
Reason: Cast needed because API of r_icumif is incompatible to CSM/CRY API in terms of qualification.
Risk: Invalid memory access.
Prevention: Covered by code review and test.

 */

/**********************************************************************************************************************
 *  END OF FILE: CRY_30_RH850ICUM_CMACAES128VER.C
 *********************************************************************************************************************/
