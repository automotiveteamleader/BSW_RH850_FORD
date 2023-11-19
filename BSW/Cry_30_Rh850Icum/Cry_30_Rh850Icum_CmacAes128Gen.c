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
 *         File:  Cry_30_Rh850Icum_CmacAes128Gen.c
 *    Component:  DrvCry_Rh850Icum
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  Implements the CMAC generate CRY API for the ICUM.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define CRY_30_RH850ICUM_CMACAES128GEN_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_Rh850Icum.h"
#include "Csm_Cbk.h"
#include "Cry_30_Rh850Icum_CommonUtil.h"

#if ( CRY_30_RH850ICUM_CMACAES128GENCONFIG == STD_ON )
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#define CRY_30_RH850ICUM_CMACAES128GEN_USE_SYNC_JOB_PROCESSING     CRY_30_RH850ICUM_USE_SYNC_JOB_PROCESSING
#define CRY_30_RH850ICUM_CMACAES128GEN_KEYSIZE                     (16u)
#define CRY_30_RH850ICUM_CMACAES128GEN_USE_SHE_KEY                 (1u)
#define CRY_30_RH850ICUM_CMACAES128GEN_MAC_LENGTH                  (16u)
#define CRY_30_RH850ICUM_CMACAES128GEN_BLOCKSIZE                   (16u)
#define CRY_30_RH850ICUM_CMACAES128GEN_BITS_PER_BYTE               (8u)

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
  P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultPtr;
  P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultLengthPtr;
  boolean TruncationIsAllowed;
} Cry_30_Rh850Icum_CmacAes128Gen_BufferType;


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

# define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_30_RH850ICUM_LOCAL VAR(Cry_30_Rh850Icum_CmacAes128Gen_BufferType, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_CmacAes128Gen_Buffer; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_RH850ICUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#if ( CRY_30_RH850ICUM_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
# define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_30_RH850ICUM_LOCAL VAR(uint8, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_CmacAes128Gen_Status; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_RH850ICUM_STOP_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define CRY_30_RH850ICUM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128GenStartInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                           P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr);

CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128GenUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) dataPtr,
                                                                            uint32 dataLength);

CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128GenFinishInternal(P2CONST(void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                            P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultPtr,
                                                                            P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultLengthPtr,
                                                                            boolean TruncationIsAllowed);


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128GenStartInternal()
 **********************************************************************************************************************/
/*! \brief      Common service start function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_CmacAes128GenStart()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128GenStartInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                           P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  P2CONST( Cry_30_Rh850Icum_CmacAes128GenConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_Rh850Icum_CmacAes128GenConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ))cfgPtr;

  /* PRQA S 0310 2 */ /* MD_CRY_11.4 */
  P2VAR(Cry_30_Rh850Icum_CmacAes128GenWorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) workSpacePtr =
    (P2VAR(Cry_30_Rh850Icum_CmacAes128GenWorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))Cry_30_Rh850Icum_GetAddrCmacAes128GenWorkSpace(Cry_30_Rh850Icum_GetCmacAes128GenWorkSpaceIdxOfCmacAes128GenConfig(contextPtr));


  /* State, Range and NULL_PTR check */
  if ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_IDLE )
  {
    if ( ( cfgPtr != NULL_PTR )
      && ( keyPtr != NULL_PTR )
      && ( (keyPtr->length == CRY_30_RH850ICUM_CMACAES128GEN_KEYSIZE) || ( keyPtr->length == CRY_30_RH850ICUM_CMACAES128GEN_USE_SHE_KEY ) ) )
    {
      if ( keyPtr->length ==CRY_30_RH850ICUM_CMACAES128GEN_USE_SHE_KEY )
      {
        /* Length is 1 -> assume key data is slot id */
        /* Save keyID into the buffer, so that it can be used in the update-function */
        workSpacePtr->keyID = (uint32)(keyPtr->data[0] & 0xFFu);
        retVal = CSM_E_OK;
      }
      else if ( keyPtr->length == CRY_30_RH850ICUM_CMACAES128GEN_KEYSIZE )
      {
        /* Length matches key size */
        /* Load the key data to the RAM key slot of the ICUMB */
        if ( CSM_E_OK == Cry_30_Rh850Icum_LoadPlainKey( (P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ))keyPtr->data ) ) /* PRQA S 0310 */ /* MD_CRY_11.4 */
        {
          /* Set RAM key slot as ID */
          if (Cry_30_Rh850Icum_GetKeyIdTypeOfCmacAes128GenConfig(contextPtr) == CRY_30_RH850ICUM_KEYIDTYPE_RAW)
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

      Cry_30_Rh850Icum_CmacAes128Gen_Buffer.cfgPtr = cfgPtr;
      Cry_30_Rh850Icum_CmacAes128Gen_Buffer.keyPtr = keyPtr;
    }
  }
  else
  {
    retVal = CSM_E_BUSY;
  }

  if ( retVal == CSM_E_OK)
  {
    Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_MACGENERATE_START;
  }

  return retVal;
} /* PRQA S 6080 */ /* MD_MSR_STMIF */


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128GenUpdateInternal()
 **********************************************************************************************************************/
/*! \brief      Common service update function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_CmacAes128GenUpdate()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128GenUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) dataPtr,
                                                                            uint32 dataLength)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  /* State and NULL_PTR check */
  if ( ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_MACGENERATE_START )
    && ( cfgPtr != NULL_PTR )
    && ( dataPtr != NULL_PTR ) )
  {
    Cry_30_Rh850Icum_CmacAes128Gen_Buffer.cfgPtr = cfgPtr;
    Cry_30_Rh850Icum_CmacAes128Gen_Buffer.dataPtr = dataPtr;
    Cry_30_Rh850Icum_CmacAes128Gen_Buffer.dataLength = dataLength;
    retVal = CSM_E_OK;
  }

  if ( retVal == CSM_E_OK)
  {
    Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_MACGENERATE_UPDATE;
  }

  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128GenFinishInternal()
 **********************************************************************************************************************/
/*! \brief      Common service finish function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_CmacAes128GenFinish()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128GenFinishInternal(P2CONST(void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
  P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultPtr,
                                                                            P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultLengthPtr,
                                                                            boolean TruncationIsAllowed)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint32 resultLength;
  uint8_least i;
  uint8 macBuffer[CRY_30_RH850ICUM_CMACAES128GEN_MAC_LENGTH];
  r_icumif_isd_t * p_ISD = &ISD;

  P2CONST(Cry_30_Rh850Icum_CmacAes128GenConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) contextPtr =
    (P2CONST(Cry_30_Rh850Icum_CmacAes128GenConfigType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))cfgPtr;

  /* PRQA S 0310 2 */ /* MD_CRY_11.4 */
  P2VAR(Cry_30_Rh850Icum_CmacAes128GenWorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) workSpacePtr =
    (P2VAR(Cry_30_Rh850Icum_CmacAes128GenWorkSpaceType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR))Cry_30_Rh850Icum_GetAddrCmacAes128GenWorkSpace(Cry_30_Rh850Icum_GetCmacAes128GenWorkSpaceIdxOfCmacAes128GenConfig(contextPtr));

  /* State and NULL_PTR check */
  if ( ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_MACGENERATE_UPDATE )
    && ( resultPtr != NULL_PTR )
    && ( resultLengthPtr != NULL_PTR ) )
  {
    resultLength = (*resultLengthPtr & 0xFFFFu);

    p_ISD->service_id = SERVICE_01_AES_CMAC;
    p_ISD->p_callbackfunc = 0;
    p_ISD->job_id = 0;
    p_ISD->prm.AES_CMAC.key_group = KEY_GRP_SHE;
    p_ISD->prm.AES_CMAC.key_id = (uint8)Cry_30_Rh850Icum_GetRawIcumKeyId(workSpacePtr->keyID, Cry_30_Rh850Icum_GetKeyIdTypeOfCmacAes128GenConfig(contextPtr));
    p_ISD->prm.AES_CMAC.cmac_operation = CMAC_GENERATION;
    p_ISD->prm.AES_CMAC.p_msg = Cry_30_Rh850Icum_CmacAes128Gen_Buffer.dataPtr;
    p_ISD->prm.AES_CMAC.msg_size_in_bytes = Cry_30_Rh850Icum_CmacAes128Gen_Buffer.dataLength;
    p_ISD->prm.AES_CMAC.p_cmac = macBuffer;
    p_ISD->prm.AES_CMAC.cmac_size_in_bytes = CRY_30_RH850ICUM_CMACAES128GEN_MAC_LENGTH;
    p_ISD->prm.AES_CMAC.job_slice = 0;

    Cry_30_Rh850Icum_TriggerServiceAndWait(p_ISD);

    /* Copy MAC to result pointer and truncate optionally */
    if ( ( TruncationIsAllowed == FALSE )
      && ( resultLength < CRY_30_RH850ICUM_CMACAES128GEN_MAC_LENGTH ) )
    {
      /* No output written */
      *resultLengthPtr = 0u;

      /* MAC cannot be written to the buffer */
      retVal = CSM_E_SMALL_BUFFER;
    }
    else
    {
      if ( resultLength > CRY_30_RH850ICUM_CMACAES128GEN_MAC_LENGTH )
      {
        resultLength = CRY_30_RH850ICUM_CMACAES128GEN_MAC_LENGTH;
      }

      for ( i = 0u; i < resultLength; i++ )
      {
        resultPtr[i] = macBuffer[i];
      }

      /* Write back result length */
      *resultLengthPtr = resultLength;

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
 * Cry_30_Rh850Icum_CmacAes128GenInit()
 **********************************************************************************************************************/
/*! \brief      Initializes the MAC generation
 *  \context    System Startup
 *  \note       Called by Cry_Init
 **********************************************************************************************************************/
FUNC( void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128GenInit( void )
{
#if ( CRY_30_RH850ICUM_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_CmacAes128Gen_Status = CRY_30_RH850ICUM_STATE_IDLE;
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128GenMainFunction()
 **********************************************************************************************************************/
/*! \brief      API to be called to process the requested services.
 *  \context    Function could be called from task level only
 *  \note       Scheduled by the CSM
**********************************************************************************************************************/
FUNC(void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128GenMainFunction( void )
{
#if ( CRY_30_RH850ICUM_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_ReturnType retVal;

  switch(Cry_30_Rh850Icum_CmacAes128Gen_Status)
  {
    case CRY_30_RH850ICUM_STATE_START:
    {
      retVal=Cry_30_Rh850Icum_CmacAes128GenStartInternal(
        Cry_30_Rh850Icum_CmacAes128Gen_Buffer.cfgPtr,
        Cry_30_Rh850Icum_CmacAes128Gen_Buffer.keyPtr );

      Cry_30_Rh850Icum_CmacAes128Gen_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_MacGenerateCallbackNotification( retVal );
      break;
    }
    case CRY_30_RH850ICUM_STATE_UPDATE:
    {
      retVal=Cry_30_Rh850Icum_CmacAes128GenUpdateInternal(
        Cry_30_Rh850Icum_CmacAes128Gen_Buffer.cfgPtr,
        Cry_30_Rh850Icum_CmacAes128Gen_Buffer.dataPtr,
        Cry_30_Rh850Icum_CmacAes128Gen_Buffer.dataLength );

      Cry_30_Rh850Icum_CmacAes128Gen_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_MacGenerateCallbackNotification( retVal );
      break;
    }
    case CRY_30_RH850ICUM_STATE_FINISH:
    {
      retVal=Cry_30_Rh850Icum_CmacAes128GenFinishInternal(
        Cry_30_Rh850Icum_CmacAes128Gen_Buffer.cfgPtr,
        Cry_30_Rh850Icum_CmacAes128Gen_Buffer.resultPtr,
        Cry_30_Rh850Icum_CmacAes128Gen_Buffer.resultLengthPtr,
        Cry_30_Rh850Icum_CmacAes128Gen_Buffer.TruncationIsAllowed );

      Cry_30_Rh850Icum_CmacAes128Gen_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_MacGenerateCallbackNotification( retVal );
      Csm_MacGenerateServiceFinishNotification();
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
 * Cry_30_Rh850Icum_CmacAes128GenStart()
**********************************************************************************************************************/
/*! \brief        This interface shall be used to initialize the MAC generate service of the CSM module.
 *  \param[in]    cfgPtr        Pointer to ConfigStructure
 *  \param[in]    keyPtr        Holds a pointer to the key necessary for the MAC generation.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_BUSY    Request failed, service is still busy.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128GenStart( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                         P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

#if ( CRY_30_RH850ICUM_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_CmacAes128Gen_Buffer.cfgPtr = cfgPtr;
  Cry_30_Rh850Icum_CmacAes128Gen_Buffer.keyPtr = keyPtr;
  Cry_30_Rh850Icum_CmacAes128Gen_Status = CRY_30_RH850ICUM_STATE_START;
  retVal = CSM_E_OK;
#else
  retVal = Cry_30_Rh850Icum_CmacAes128GenStartInternal(cfgPtr, keyPtr );
#endif

  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128GenUpdate()
**********************************************************************************************************************/
/*! \brief        This interface shall be used to feed the MAC generate service with the input data.
 *  \param[in]    cfgPtr        Pointer to ConfigStructure
 *  \param[in]    dataPtr       Holds a pointer to the data for which a MAC shall be computed.
 *  \param[in]    dataLength    Contains the number of bytes for which the MAC shall be computed.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \pre          Service was started.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128GenUpdate( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                          P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) dataPtr,
                                                          uint32 dataLength)
{
#if ( CRY_30_RH850ICUM_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_CmacAes128Gen_Buffer.cfgPtr = cfgPtr;
  Cry_30_Rh850Icum_CmacAes128Gen_Buffer.dataPtr = dataPtr;
  Cry_30_Rh850Icum_CmacAes128Gen_Buffer.dataLength = dataLength;
  Cry_30_Rh850Icum_CmacAes128Gen_Status = CRY_30_RH850ICUM_STATE_UPDATE;
  return CSM_E_OK;
#else
  return Cry_30_Rh850Icum_CmacAes128GenUpdateInternal(cfgPtr, dataPtr, dataLength );
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_CmacAes128GenFinish()
**********************************************************************************************************************/
/*! \brief        This interface shall be used to finish the MAC generation service.
 *  \param[in]    cfgPtr        Pointer to ConfigStructure
 *  \param[out]   resultPtr     Holds a pointer to the memory location which will hold the result of the MAC generation.
 *                              If the result does not fit into the given buffer, and truncation is allowed,
 *                              the result shall be truncated
 *  \param[in,out] resultLengthPtr Holds a pointer to the memory location in which the length information is stored.
 *                              On calling this function this parameter shall contain the size of the buffer
 *                              provided by resultPtr. When the request has finished,
 *                              the actual length of the returned MAC shall be stored.
 *  \param[in]    TruncationIsAllowed   This parameter states whether a truncation of the result is allowed or not.
 *                              TRUE: truncation is allowed.
 *                              FALSE: truncation is not allowed.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_SMALL_BUFFER  The provided buffer is too small to store the result and truncation was not
 *                              allowed.
 *  \pre          Service was started.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC(Csm_ReturnType, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_CmacAes128GenFinish( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr,
                                                                 P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultPtr,
                                                                 P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultLengthPtr,
                                                                 boolean TruncationIsAllowed)
{
  CRY_30_RH850ICUM_DUMMY_STATEMENT( cfgPtr ); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#if ( CRY_30_RH850ICUM_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_CmacAes128Gen_Buffer.resultPtr = resultPtr;
  Cry_30_Rh850Icum_CmacAes128Gen_Buffer.resultLengthPtr = resultLengthPtr;
  Cry_30_Rh850Icum_CmacAes128Gen_Buffer.TruncationIsAllowed = TruncationIsAllowed;
  Cry_30_Rh850Icum_CmacAes128Gen_Status = CRY_30_RH850ICUM_STATE_FINISH;
  return CSM_E_OK;
#else
  return Cry_30_Rh850Icum_CmacAes128GenFinishInternal(cfgPtr, resultPtr, resultLengthPtr, TruncationIsAllowed );
#endif
}


#define CRY_30_RH850ICUM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ( CRY_30_RH850ICUM_CMACAES128GENCONFIG == STD_ON ) */
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
 *  END OF FILE: CRY_30_RH850ICUM_CMACAES128GEN.C
 *********************************************************************************************************************/
