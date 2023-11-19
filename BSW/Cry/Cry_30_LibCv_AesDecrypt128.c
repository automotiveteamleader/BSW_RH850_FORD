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
 *         File:  Cry_30_LibCv_AesDecrypt128.c
 *    Component:  SysService_AsrCry
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  Implements the AES-128 decrypt CRY API for the ASR CSM
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#define CRY_AESDECRYPT128_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_LibCv.h"
#include "Csm_Cbk.h"
#include "ESLib.h"

#if ( CRY_30_LIBCV_AESDECRYPT128CONFIG == STD_ON )
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#define CRY_AESDECRYPT128_USE_SYNC_JOB_PROCESSING     CRY_30_LIBCV_USE_SYNC_JOB_PROCESSING
#define CRY_AESDECRYPT128_KEYSIZE                     (16u)
#define CRY_AESDECRYPT128_IVSIZE                      (16u)
#define CRY_AESDECRYPT128_WATCHDOG_PTR                (0u)

#if !defined (CRY_LOCAL)
# define CRY_LOCAL static
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

#if ( CRY_AESDECRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
typedef struct
{
  P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr;
  P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) keyPtr;
  P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) InitVectorPtr;
  uint32 InitVectorLength;
  P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cipherTextPtr;
  uint32 cipherTextLength;
  P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextPtr;
  P2VAR( uint32, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextLengthPtr;
} Cry_30_LibCv_AesDecrypt128_BufferType;
#endif /* ( CRY_AESDECRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF ) */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

#if ( CRY_AESDECRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
# define CRY_30_LIBCV_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_LOCAL VAR(Cry_30_LibCv_AesDecrypt128_BufferType, CRY_30_LIBCV_VAR_NOINIT) Cry_30_LibCv_AesDecrypt128_Buffer; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_LIBCV_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define CRY_30_LIBCV_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_LOCAL VAR(uint8, CRY_30_LIBCV_VAR_NOINIT) Cry_30_LibCv_AesDecrypt128_Status; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_LIBCV_STOP_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define CRY_30_LIBCV_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

CRY_LOCAL FUNC(Csm_ReturnType, CRY_30_LIBCV_CODE) Cry_30_LibCv_AesDecrypt128StartInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                           P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) keyPtr,
                                                                                           P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) InitVectorPtr,
                                                                                           uint32 InitVectorLength);

CRY_LOCAL FUNC(Csm_ReturnType, CRY_30_LIBCV_CODE) Cry_30_LibCv_AesDecrypt128UpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cipherTextPtr,
                                                                                            uint32 cipherTextLength,
                                                                                            P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextPtr,
                                                                                            P2VAR( uint32, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextLengthPtr);

CRY_LOCAL FUNC(Csm_ReturnType, CRY_30_LIBCV_CODE) Cry_30_LibCv_AesDecrypt128FinishInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                            P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextPtr,
                                                                                            P2VAR( uint32, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextLengthPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/


/**********************************************************************************************************************
 * Cry_30_LibCv_AesDecrypt128StartInternal()
 **********************************************************************************************************************/
/*! \brief      Common service start function for synchronous and asynchronous behavior
 *  \see        Cry_30_LibCv_AesDecrypt128Start()
 **********************************************************************************************************************/
CRY_LOCAL FUNC(Csm_ReturnType, CRY_30_LIBCV_CODE) Cry_30_LibCv_AesDecrypt128StartInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                           P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) keyPtr,
                                                                                           P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) InitVectorPtr,
                                                                                           uint32 InitVectorLength )
{
  Csm_ReturnType retVal = CSM_E_OK;

  P2CONST( Cry_30_LibCv_AesDecrypt128ConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_LibCv_AesDecrypt128ConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cfgPtr;

  P2VAR( Cry_30_LibCv_AesDecrypt128WorkSpaceType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) workSpacePtr = Cry_30_LibCv_GetAddrAesDecrypt128WorkSpace(Cry_30_LibCv_GetAesDecrypt128WorkSpaceIdxOfAesDecrypt128Config(contextPtr));

  P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) localIvPtr = InitVectorPtr;

  eslt_BlockMode blockMode = 0;
  eslt_PaddingMode paddingMode = 0;

  switch (Cry_30_LibCv_GetPaddingModeOfAesDecrypt128Config(contextPtr))
  {
    case CRY_30_LIBCV_AESPADDINGMODE_PKCS5:
      paddingMode = ESL_PM_PKCS5;
      break;
    default:
      retVal = CSM_E_NOT_OK;
      break;
  }

  switch (Cry_30_LibCv_GetBlockModeOfAesDecrypt128Config(contextPtr))
  {
    case CRY_30_LIBCV_AESBLOCKMODE_ECB:
      blockMode = ESL_BM_ECB;
      break;
    case CRY_30_LIBCV_AESBLOCKMODE_CBC:
      blockMode = ESL_BM_CBC;
      break;
    default:
      retVal = CSM_E_NOT_OK;
      break;
  }

  if(retVal == CSM_E_OK)
  {
    retVal = CSM_E_NOT_OK;
    /* Range check */
    if ((keyPtr->length == CRY_AESDECRYPT128_KEYSIZE) && ((InitVectorLength == CRY_AESDECRYPT128_IVSIZE) || (InitVectorLength == 0u)))
    {
      /* Init work space */
      if (ESL_ERC_NO_ERROR == esl_initWorkSpaceHeader( &workSpacePtr->workSpace.header,
                                                       ESL_MAXSIZEOF_WS_AES128,
                                                       CRY_AESDECRYPT128_WATCHDOG_PTR))
      {
        if (InitVectorLength == 0u)
        {
          /* The AES algorithm will use an IV with all zeros when the InitVectorPtr is a null pointer when operating in CBC mode */
          /* Due to the CSM passing a null pointer is not possible - therefore remapping is necessary for InitVectorLength of zero */
          localIvPtr = (P2CONST(uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR))NULL_PTR;
        }

        /* Init AES decryption */
        if (ESL_ERC_NO_ERROR == esl_initDecryptAES128( &workSpacePtr->workSpace,
                                                       (P2CONST(eslt_Byte, AUTOMATIC, CRY_30_LIBCV_APPL_VAR))keyPtr->data,
                                                       blockMode,
                                                       paddingMode,
                                                       localIvPtr))
        {
          retVal = CSM_E_OK;
        }
      }
    }
  }

  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_LibCv_AesDecrypt128UpdateInternal()
 **********************************************************************************************************************/
/*! \brief      Common service update function for synchronous and asynchronous behavior
 *  \see        Cry_30_LibCv_AesDecrypt128Update()
 **********************************************************************************************************************/
CRY_LOCAL FUNC(Csm_ReturnType, CRY_30_LIBCV_CODE) Cry_30_LibCv_AesDecrypt128UpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cipherTextPtr,
                                                                                            uint32 cipherTextLength,
                                                                                            P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextPtr,
                                                                                            P2VAR( uint32, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextLengthPtr )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  eslt_Length plainTextLength;

  P2CONST( Cry_30_LibCv_AesDecrypt128ConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_LibCv_AesDecrypt128ConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cfgPtr;

  P2VAR( Cry_30_LibCv_AesDecrypt128WorkSpaceType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) workSpacePtr = Cry_30_LibCv_GetAddrAesDecrypt128WorkSpace(Cry_30_LibCv_GetAesDecrypt128WorkSpaceIdxOfAesDecrypt128Config(contextPtr));

  /* Range check */
  if ( ( *plainTextLengthPtr <= 0xFFFFu )
    && ( cipherTextLength <= 0xFFFFu ) )
  {
    plainTextLength = (eslt_Length)(*plainTextLengthPtr & 0xFFFFu);

    /* Update AES calculation */
    if ( ESL_ERC_NO_ERROR == esl_decryptAES128( &workSpacePtr->workSpace,
                                                (eslt_Length)cipherTextLength,
                                                (P2CONST( eslt_Byte, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cipherTextPtr,
                                                &plainTextLength,
                                                (P2VAR( eslt_Byte, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))plainTextPtr) )
    {
      *plainTextLengthPtr = plainTextLength;
      retVal = CSM_E_OK;
    }
  }

  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_LibCv_AesDecrypt128FinishInternal()
 **********************************************************************************************************************/
/*! \brief      Common service finish function for synchronous and asynchronous behavior
 *  \see        Cry_30_LibCv_AesDecrypt128Finish()
 **********************************************************************************************************************/
CRY_LOCAL FUNC(Csm_ReturnType, CRY_30_LIBCV_CODE) Cry_30_LibCv_AesDecrypt128FinishInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                            P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextPtr,
                                                                                            P2VAR( uint32, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextLengthPtr )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  eslt_Length plainTextLength;

  P2CONST( Cry_30_LibCv_AesDecrypt128ConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_LibCv_AesDecrypt128ConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cfgPtr;

  P2VAR( Cry_30_LibCv_AesDecrypt128WorkSpaceType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) workSpacePtr = Cry_30_LibCv_GetAddrAesDecrypt128WorkSpace(Cry_30_LibCv_GetAesDecrypt128WorkSpaceIdxOfAesDecrypt128Config(contextPtr));

  /* Range check */
  if ( *plainTextLengthPtr <= 0xFFFFu )
  {
    plainTextLength = (eslt_Length)(*plainTextLengthPtr & 0xFFFFu);

    /* Finish AES calculation */
    if ( ESL_ERC_NO_ERROR == esl_finalizeDecryptAES128( &workSpacePtr->workSpace,
                                                        &plainTextLength,
                                                        (P2VAR( eslt_Byte, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))plainTextPtr) )
    {
      *plainTextLengthPtr = plainTextLength;
      retVal = CSM_E_OK;
    }
  }

  return retVal;
}



/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Cry_30_LibCv_AesDecrypt128Init()
 **********************************************************************************************************************/
/*! \brief      Initializes the AES 128 decryption
 *  \context    System Startup
 *  \note       Called by application (BswM)
 **********************************************************************************************************************/
FUNC( void, CRY_30_LIBCV_CODE) Cry_30_LibCv_AesDecrypt128Init( void )
{
#if ( CRY_AESDECRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_AesDecrypt128_Status = CRY_30_LIBCV_STATE_IDLE;
#endif
}


/**********************************************************************************************************************
 * Cry_30_LibCv_AesEnrcryptMainFunction()
 **********************************************************************************************************************/
/*! \brief      API to be called to process the requested services.
 *  \context    Function could be called from task level only
 *  \note       Scheduled by the CSM
**********************************************************************************************************************/
FUNC(void, CRY_30_LIBCV_CODE) Cry_30_LibCv_AesDecrypt128MainFunction( void )
{
#if ( CRY_AESDECRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_ReturnType retVal;

  switch(Cry_30_LibCv_AesDecrypt128_Status)
  {
    case CRY_30_LIBCV_STATE_START:
    {
      retVal = Cry_30_LibCv_AesDecrypt128StartInternal( Cry_30_LibCv_AesDecrypt128_Buffer.cfgPtr,
                                                        Cry_30_LibCv_AesDecrypt128_Buffer.keyPtr,
                                                        Cry_30_LibCv_AesDecrypt128_Buffer.InitVectorPtr,
                                                        Cry_30_LibCv_AesDecrypt128_Buffer.InitVectorLength);

      Cry_30_LibCv_AesDecrypt128_Status = CRY_30_LIBCV_STATE_IDLE;

      Csm_SymDecryptCallbackNotification( retVal );
      break;
    }
    case CRY_30_LIBCV_STATE_UPDATE:
    {
      retVal = Cry_30_LibCv_AesDecrypt128UpdateInternal( Cry_30_LibCv_AesDecrypt128_Buffer.cfgPtr,
                                                         Cry_30_LibCv_AesDecrypt128_Buffer.cipherTextPtr,
                                                         Cry_30_LibCv_AesDecrypt128_Buffer.cipherTextLength,
                                                         Cry_30_LibCv_AesDecrypt128_Buffer.plainTextPtr,
                                                         Cry_30_LibCv_AesDecrypt128_Buffer.plainTextLengthPtr);

      Cry_30_LibCv_AesDecrypt128_Status = CRY_30_LIBCV_STATE_IDLE;

      Csm_SymDecryptCallbackNotification( retVal );
      break;
    }
    case CRY_30_LIBCV_STATE_FINISH:
    {
      retVal=Cry_30_LibCv_AesDecrypt128FinishInternal( Cry_30_LibCv_AesDecrypt128_Buffer.cfgPtr,
                                                       Cry_30_LibCv_AesDecrypt128_Buffer.plainTextPtr,
                                                       Cry_30_LibCv_AesDecrypt128_Buffer.plainTextLengthPtr);

      Cry_30_LibCv_AesDecrypt128_Status = CRY_30_LIBCV_STATE_IDLE;

      Csm_SymDecryptCallbackNotification( retVal );
      Csm_SymDecryptServiceFinishNotification();
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
 * Cry_30_LibCv_AesDecrypt128Start()
**********************************************************************************************************************/
/*! \brief        This interface shall be used to initialize the symmetrical decryption service of the CSM module.
 *  \param[in]    cfgPtr        Pointer to ConfigStructure
 *  \param[in]    keyPtr        Holds a pointer to the key which has to be used during the symmetrical decryption
 *                              operation.
 *  \param[in]    InitVectorPtr Holds a pointer to initialisation vector which has to be used during the symmetrical
 *                              decryption.
 *  \param[in]    InitVectorLength Holds a pointer to the initialisation vector which has to be used during the
 *                              symmetrical decryption.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_AesDecrypt128Start( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                           P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) keyPtr,
                                                                           P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) InitVectorPtr,
                                                                           uint32 InitVectorLength )
{
#if ( CRY_AESDECRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_AesDecrypt128_Buffer.cfgPtr = cfgPtr;
  Cry_30_LibCv_AesDecrypt128_Buffer.keyPtr = keyPtr;
  Cry_30_LibCv_AesDecrypt128_Buffer.InitVectorPtr = InitVectorPtr;
  Cry_30_LibCv_AesDecrypt128_Buffer.InitVectorLength = InitVectorLength;
  Cry_30_LibCv_AesDecrypt128_Status = CRY_30_LIBCV_STATE_START;
  return CSM_E_OK;
#else
  return Cry_30_LibCv_AesDecrypt128StartInternal(cfgPtr, keyPtr, InitVectorPtr, InitVectorLength);
#endif
}


/**********************************************************************************************************************
 * Cry_30_LibCv_AesDecrypt128Update()
**********************************************************************************************************************/
/*! \brief        This interface shall be used to feed the symmetrical decryption service with the input data.
 *  \param[in]    cfgPtr        Pointer to ConfigStructure
 *  \param[in]    cipherTextPtr Holds a pointer to the data for which a decrypted text shall be computed.
 *  \param[in]    cipherTextLength Contains the number of bytes for which the decrypted text shall be computed.
 *  \param[out]   plainTextPtr  Holds a pointer to the memory location which will hold the decrypted text.
 *  \param[in,out] plainTextLengthPtr Holds a pointer to the memory location in which the length information is stored. On
 *                              calling this function this parameter shall contain the size of the provided buffer.
 *                              When the request has finished, the actual length of the returned decrypted text shall
 *                              be stored.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_SMALL_BUFFER  The provided buffer is too small to store the result and truncation was not
 *                              allowed.
 *  \pre          Service was started.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_AesDecrypt128Update( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cipherTextPtr,
                                                                            uint32 cipherTextLength,
                                                                            P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextPtr,
                                                                            P2VAR( uint32, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextLengthPtr )
{
#if ( CRY_AESDECRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_AesDecrypt128_Buffer.cfgPtr = cfgPtr;
  Cry_30_LibCv_AesDecrypt128_Buffer.cipherTextPtr = cipherTextPtr;
  Cry_30_LibCv_AesDecrypt128_Buffer.cipherTextLength = cipherTextLength;
  Cry_30_LibCv_AesDecrypt128_Buffer.plainTextPtr = plainTextPtr;
  Cry_30_LibCv_AesDecrypt128_Buffer.plainTextLengthPtr = plainTextLengthPtr;
  Cry_30_LibCv_AesDecrypt128_Status = CRY_30_LIBCV_STATE_UPDATE;
  return CSM_E_OK;
#else
  return Cry_30_LibCv_AesDecrypt128UpdateInternal(cfgPtr, cipherTextPtr, cipherTextLength, plainTextPtr, plainTextLengthPtr);
#endif
}


/**********************************************************************************************************************
 * Cry_30_LibCv_AesDecrypt128Finish()
**********************************************************************************************************************/
/*! \brief        This interface shall be used to finish the symmetrical decryption service.
 *  \param[in]    cfgPtr        Pointer to ConfigStructure
 *  \param[out]   plainTextPtr  Holds a pointer to the memory location which will hold the decrypted text.
 *  \param[in,out] plainTextLengthPtr Holds a pointer to the memory location in which the length information is stored. On
 *                              calling this function this parameter shall contain the size of the provided buffer.
 *                              When the request has finished, the actual length of the returned decrypted text shall
 *                              be stored.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_SMALL_BUFFER  The provided buffer is too small to store the result and truncation was not
 *                              allowed.
 *  \pre          Service was started.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_AesDecrypt128Finish( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                            P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextPtr,
                                                                            P2VAR( uint32, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) plainTextLengthPtr )
{
#if ( CRY_AESDECRYPT128_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_AesDecrypt128_Buffer.cfgPtr = cfgPtr;
  Cry_30_LibCv_AesDecrypt128_Buffer.plainTextPtr = plainTextPtr;
  Cry_30_LibCv_AesDecrypt128_Buffer.plainTextLengthPtr = plainTextLengthPtr;
  Cry_30_LibCv_AesDecrypt128_Status = CRY_30_LIBCV_STATE_FINISH;
  return CSM_E_OK;
#else
  return Cry_30_LibCv_AesDecrypt128FinishInternal(cfgPtr, plainTextPtr, plainTextLengthPtr);
#endif
}


#define CRY_30_LIBCV_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ( CRY_AESDECRYPT128CONFIG == STD_ON ) */

/**********************************************************************************************************************
 *  END OF FILE: CRY_AESDECRYPT128.C
 *********************************************************************************************************************/
