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
 *         File:  Cry_30_LibCv_CmacAes128Ver.c
 *    Component:  SysService_AsrCry
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  Implements the CRY CmacAes128Ver Api for the ASR CSM
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

#define CRY_CMACAES128VER_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_LibCv.h"
#include "Cry_30_LibCv_CmacAes128Ver.h"
#include "Csm_Cbk.h"


#if ( CRY_30_LIBCV_CMACAES128VERCONFIG == STD_ON )
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define CRY_CMACAES128VER_USE_SYNC_JOB_PROCESSING     CRY_30_LIBCV_USE_SYNC_JOB_PROCESSING
#define CRY_CMACAES128VER_WATCHDOG_PTR                (0u)
#define CRY_CMACAES128VER_MACSIZE                     (16u)
#define CRY_CMACAES128VER_BITS_PER_BYTE               (8u)
 
#if !defined (CRY_LOCAL)
# define CRY_LOCAL static
#endif

#if !defined (CRY_30_LIBCV_DUMMY_STATEMENT)
# if ( CRY_30_LIBCV_USE_DUMMY_STATEMENT == STD_ON )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define CRY_30_LIBCV_DUMMY_STATEMENT(statement) ( (void)(statement) )
# else
#  define CRY_30_LIBCV_DUMMY_STATEMENT(statement)
# endif
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if ( CRY_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
typedef struct
{
  P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr;
  P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) keyPtr;
  P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) dataPtr;
  uint32 dataLength;
  P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) MacPtr;
  uint32 MacLength;
  P2VAR( Csm_VerifyResultType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr;
} Cry_30_LibCv_CmacAes128Ver_BufferType;
#endif /* ( CRY_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF ) */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#if ( CRY_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
# define CRY_30_LIBCV_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_LOCAL VAR(Cry_30_LibCv_CmacAes128Ver_BufferType, CRY_30_LIBCV_VAR_NOINIT) Cry_30_LibCv_CmacAes128Ver_Buffer; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_LIBCV_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define CRY_30_LIBCV_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_LOCAL VAR(uint8, CRY_30_LIBCV_VAR_NOINIT) Cry_30_LibCv_CmacAes128Ver_Status; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_LIBCV_STOP_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CRY_30_LIBCV_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128VerStartInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                             P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) keyPtr);

CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128VerUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                              P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) dataPtr,
                                                                                              uint32 dataLength);

CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128VerFinishInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                              P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) MacPtr,
                                                                                              uint32 MacLength,
                                                                                              P2VAR( Csm_VerifyResultType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Cry_30_LibCv_CmacAes128VerStartInternal()
 *********************************************************************************************************************/
/*! \brief      Common service start function for synchronous and asynchronous behavior
 *  \see        Cry_30_LibCv_CmacAes128VerStart()
 *********************************************************************************************************************/
CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128VerStartInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                             P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) keyPtr)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  P2CONST( Cry_30_LibCv_CmacAes128VerConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_LibCv_CmacAes128VerConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cfgPtr;

  P2VAR( Cry_30_LibCv_CmacAes128VerWorkSpaceType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) workSpacePtr = Cry_30_LibCv_GetAddrCmacAes128VerWorkSpace(Cry_30_LibCv_GetCmacAes128VerWorkSpaceIdxOfCmacAes128VerConfig(contextPtr));

  /* Null pointer and range check */
  if (keyPtr->length <= 0xFFFFu)
  {
    /* Init work space */
    if (ESL_ERC_NO_ERROR == esl_initWorkSpaceHeader( &workSpacePtr->workSpace.header,
                                                     ESL_MAXSIZEOF_WS_CMACAES,
                                                     CRY_CMACAES128VER_WATCHDOG_PTR ) )
    {
      /* Init HMAC SHA-1 */
      if (ESL_ERC_NO_ERROR == esl_initCMACAES128( &workSpacePtr->workSpace,
                                                  (eslt_Length)keyPtr->length,
                                                  (P2CONST(eslt_Byte, AUTOMATIC, CRY_30_LIBCV_APPL_VAR))keyPtr->data ) )
      {
        retVal = CSM_E_OK;
      }
    }
  }

  return retVal;
}


/**********************************************************************************************************************
 *  Cry_30_LibCv_CmacAes128VerUpdateInternal()
 *********************************************************************************************************************/
/*! \brief      Common service update function for synchronous and asynchronous behavior
 *  \see        Cry_30_LibCv_CmacAes128VerUpdate()
 *********************************************************************************************************************/
CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128VerUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                              P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) dataPtr,
                                                                                              uint32 dataLength)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  P2CONST( Cry_30_LibCv_CmacAes128VerConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_LibCv_CmacAes128VerConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cfgPtr;

  P2VAR( Cry_30_LibCv_CmacAes128VerWorkSpaceType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) workSpacePtr = Cry_30_LibCv_GetAddrCmacAes128VerWorkSpace(Cry_30_LibCv_GetCmacAes128VerWorkSpaceIdxOfCmacAes128VerConfig(contextPtr));

  /* Null pointer check; check for valid data region */
  if (dataLength < 0xFFFFu)
  {
    /* Update HMAC calculation */
    if (ESL_ERC_NO_ERROR == esl_updateCMACAES128( &workSpacePtr->workSpace,
                                                  (eslt_Length)dataLength,
                                                  (P2CONST(eslt_Byte, AUTOMATIC, CRY_30_LIBCV_APPL_VAR))dataPtr))
    {
      retVal = CSM_E_OK;
    }
  }

  return retVal;
}


/**********************************************************************************************************************
 *  Cry_30_LibCv_CmacAes128VerFinishInternal()
 *********************************************************************************************************************/
/*! \brief      Common service finish function for synchronous and asynchronous behavior
 *  \see        Cry_30_LibCv_CmacAes128VerFinish()
 *********************************************************************************************************************/
CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128VerFinishInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                              P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) MacPtr,
                                                                                              uint32 MacLength,
                                                                                              P2VAR( Csm_VerifyResultType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  eslt_Byte macBuffer[CRY_CMACAES128VER_MACSIZE];
  Csm_VerifyResultType result = CSM_E_VER_NOT_OK;
  uint8_least i;
  uint32 veriefyLength = 0u;
  uint8 verifyBitMask = 0u;
  uint32 numberBitsInLastByte = 0u;

  P2CONST( Cry_30_LibCv_CmacAes128VerConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_LibCv_CmacAes128VerConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cfgPtr;

  P2VAR( Cry_30_LibCv_CmacAes128VerWorkSpaceType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) workSpacePtr = Cry_30_LibCv_GetAddrCmacAes128VerWorkSpace(Cry_30_LibCv_GetCmacAes128VerWorkSpaceIdxOfCmacAes128VerConfig(contextPtr));

  if ( Cry_30_LibCv_IsLengthInBytesOfCmacAes128VerConfig(contextPtr) )
  {
    /* Interpet length as number of bytes */
    veriefyLength = MacLength;
  }
  else
  {
    /* Interpet length as number of bits */
    veriefyLength = MacLength / CRY_CMACAES128VER_BITS_PER_BYTE;
    if ((MacLength & (CRY_CMACAES128VER_BITS_PER_BYTE - 1u)) != 0u)
    {
      veriefyLength += 1u;
    }
  }

  if (veriefyLength <= CRY_CMACAES128VER_MACSIZE)
  {
    /* Finalize the HMAC calculation */
    if (ESL_ERC_NO_ERROR == esl_finalizeCMACAES128( &workSpacePtr->workSpace,
                                                    macBuffer ) )
    {
      retVal = CSM_E_OK;
      result = CSM_E_VER_OK;
      for (i = 0u; i < (veriefyLength - 1u); i++)
      {
        if (MacPtr[i] != macBuffer[i])
        {
          /* Verification does not match */
          result = CSM_E_VER_NOT_OK;
          break;
        }
      }
      if (Cry_30_LibCv_IsLengthInBytesOfCmacAes128VerConfig(contextPtr))
      {
        /* Bitmask contains all 8 bit */
        verifyBitMask = 0xFFu;
      }
      else
      {
        /* Compute number of bits to verify in the last byte */
        numberBitsInLastByte = MacLength & (CRY_CMACAES128VER_BITS_PER_BYTE - 1u);  /* Calculate modulo */
        if (numberBitsInLastByte == 0u)
        {
          numberBitsInLastByte = CRY_CMACAES128VER_BITS_PER_BYTE;
        }
        /* Generate bitmask which contains all bits to be verified
         * This depends on the byteorder */
#if (CPU_BIT_ORDER == LSB_FIRST)   /*little endian bit ordering*/
        for (i = CRY_CMACAES128VER_BITS_PER_BYTE; i > (CRY_CMACAES128VER_BITS_PER_BYTE - numberBitsInLastByte); i--)
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
      if ( (MacPtr[veriefyLength - 1u] & verifyBitMask)
        != (macBuffer[veriefyLength - 1u] & verifyBitMask) )
      {
        result = CSM_E_VER_NOT_OK;
      }

    }
  }

  /* Write back result */
  *resultPtr = result;

  return retVal;
} /* PRQA S 6010 */ /* MD_MSR_STPTH */ /* PRQA S 6030 */ /* MD_MSR_STCYC */


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Cry_30_LibCv_CmacAes128VerInit()
 *********************************************************************************************************************/
/*! \brief      Initializes the service
 *  \context    System Startup
 *  \note       Called by application (BswM)
 *********************************************************************************************************************/
FUNC( void, CRY_30_LIBCV_CODE) Cry_30_LibCv_CmacAes128VerInit( void )
{
#if ( CRY_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_CmacAes128Ver_Status = CRY_30_LIBCV_STATE_IDLE;
#endif
}


/**********************************************************************************************************************
 *  Cry_30_LibCv_CmacAes128VerMainFunction()
 *********************************************************************************************************************/
/*! \brief      API to be called to process the requested services.
 *  \context    Function could be called from task level only
 *  \note       Scheduled by the CSM
 *********************************************************************************************************************/
FUNC(void, CRY_30_LIBCV_CODE) Cry_30_LibCv_CmacAes128VerMainFunction( void )
{
#if ( CRY_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_ReturnType retVal;

  switch(Cry_30_LibCv_CmacAes128Ver_Status)
  {
    case CRY_30_LIBCV_STATE_START:
    {
      retVal = Cry_30_LibCv_CmacAes128VerStartInternal( Cry_30_LibCv_CmacAes128Ver_Buffer.cfgPtr,
                                                        Cry_30_LibCv_CmacAes128Ver_Buffer.keyPtr );

      Cry_30_LibCv_CmacAes128Ver_Status = CRY_30_LIBCV_STATE_IDLE;

      Csm_MacVerifyCallbackNotification( retVal );
      break;
    }
    case CRY_30_LIBCV_STATE_UPDATE:
    {
      retVal = Cry_30_LibCv_CmacAes128VerUpdateInternal( Cry_30_LibCv_CmacAes128Ver_Buffer.cfgPtr,
                                                         Cry_30_LibCv_CmacAes128Ver_Buffer.dataPtr,
                                                         Cry_30_LibCv_CmacAes128Ver_Buffer.dataLength );

      Cry_30_LibCv_CmacAes128Ver_Status = CRY_30_LIBCV_STATE_IDLE;

      Csm_MacVerifyCallbackNotification( retVal );
      break;
    }
    case CRY_30_LIBCV_STATE_FINISH:
    {
      retVal = Cry_30_LibCv_CmacAes128VerFinishInternal( Cry_30_LibCv_CmacAes128Ver_Buffer.cfgPtr,
                                                         Cry_30_LibCv_CmacAes128Ver_Buffer.MacPtr,
                                                         Cry_30_LibCv_CmacAes128Ver_Buffer.MacLength,
                                                         Cry_30_LibCv_CmacAes128Ver_Buffer.resultPtr );

      Cry_30_LibCv_CmacAes128Ver_Status = CRY_30_LIBCV_STATE_IDLE;

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
 *  Cry_30_LibCv_CmacAes128VerStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the MAC verification service of the CSM module.
 *  \param[in]     cfgPtr        Pointer to the configuration.
 *  \param[in]     keyPtr        Holds a pointer to the key.
 *  \return        CSM_E_OK      Request successful
 *  \return        CSM_E_NOT_OK  Request failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23050
 *  \trace         SPEC-47519
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128VerStart( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                           P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) keyPtr)
{
#if ( CRY_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_CmacAes128Ver_Buffer.cfgPtr = cfgPtr;
  Cry_30_LibCv_CmacAes128Ver_Buffer.keyPtr = keyPtr;
  Cry_30_LibCv_CmacAes128Ver_Status = CRY_30_LIBCV_STATE_START;
  return CSM_E_OK;
#else
  return Cry_30_LibCv_CmacAes128VerStartInternal( cfgPtr, keyPtr );
#endif
}


/**********************************************************************************************************************
 *  Cry_30_LibCv_CmacAes128VerUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the MAC verification service with the input data.
 *  \param[in]     cfgPtr        Pointer to the configuration.
 *  \param[in]     dataPtr       Holds a pointer to the data for which a MAC shall be computed.
 *  \param[in]     dataLength    Contains the number of bytes for which the MAC shall be computed.
 *  \return        CSM_E_OK      Request successful
 *  \return        CSM_E_NOT_OK  Request failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23050
 *  \trace         SPEC-47368
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128VerUpdate( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) dataPtr,
                                                                            uint32 dataLength)
{
#if ( CRY_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_CmacAes128Ver_Buffer.cfgPtr = cfgPtr;
  Cry_30_LibCv_CmacAes128Ver_Buffer.dataPtr = dataPtr;
  Cry_30_LibCv_CmacAes128Ver_Buffer.dataLength = dataLength;
  Cry_30_LibCv_CmacAes128Ver_Status = CRY_30_LIBCV_STATE_UPDATE;
  return CSM_E_OK;
#else
  return Cry_30_LibCv_CmacAes128VerUpdateInternal( cfgPtr, dataPtr, dataLength );
#endif
}


/**********************************************************************************************************************
 *  Cry_30_LibCv_CmacAes128VerFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the MAC verification service.
 *  \param[in]     cfgPtr        Pointer to the configuration.
 *  \param[out]    MacPtr        Holds a pointer to the memory location which will hold the MAC to verify.
 *  \param[in,out] MacLength     Holds the length of the MAC to be verified.
 *  \param[in]     resultPtr     Holds a pointer to the memory location which will hold the MAC.
 *  \return        CSM_E_OK      Request successful
 *  \return        CSM_E_NOT_OK  Request failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23050
 *  \trace         SPEC-47401
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128VerFinish( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) MacPtr,
                                                                            uint32 MacLength,
                                                                            P2VAR( Csm_VerifyResultType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr)
{
#if ( CRY_CMACAES128VER_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_CmacAes128Ver_Buffer.cfgPtr = cfgPtr;
  Cry_30_LibCv_CmacAes128Ver_Buffer.MacPtr = MacPtr;
  Cry_30_LibCv_CmacAes128Ver_Buffer.MacLength = MacLength;
  Cry_30_LibCv_CmacAes128Ver_Buffer.resultPtr = resultPtr;
  Cry_30_LibCv_CmacAes128Ver_Status = CRY_30_LIBCV_STATE_FINISH;
  return CSM_E_OK;
#else
  return Cry_30_LibCv_CmacAes128VerFinishInternal( cfgPtr, MacPtr, MacLength, resultPtr );
#endif
}


#define CRY_30_LIBCV_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ( CRY_30_LIBCV_CMACAES128VER_ENABLED == STD_ON ) */

/**********************************************************************************************************************
 *  END OF FILE: CRY_CMACAES128VER.C
 *********************************************************************************************************************/

 