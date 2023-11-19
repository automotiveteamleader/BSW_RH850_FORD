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
 *         File:  Cry_30_LibCv_CmacAes128Gen.c
 *    Component:  SysService_AsrCry
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  Implements the CRY CmacAes128Gen Api for the ASR CSM
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

#define CRY_CMACAES128GEN_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_LibCv.h"
#include "Cry_30_LibCv_CmacAes128Gen.h"
#include "Csm_Cbk.h"


#if ( CRY_30_LIBCV_CMACAES128GENCONFIG == STD_ON )
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/
#define CRY_CMACAES128GEN_USE_SYNC_JOB_PROCESSING     CRY_30_LIBCV_USE_SYNC_JOB_PROCESSING
#define CRY_CMACAES128GEN_WATCHDOG_PTR                (0u)
#define CRY_CMACAES128GEN_MACSIZE                     (16u)
#define CRY_CMACAES128GEN_BITS_PER_BYTE               (8u)

#if !defined (CRY_LOCAL)
# define CRY_LOCAL static
#endif

#if !defined (CRY_30_LIBCV_DUMMY_STATEMENT)
# if ( CRY_30_LIBCV_DUMMY_STATEMENT == STD_ON )
/* PRQA S 3453 1 */ /* MD_MSR_19.7 */
#  define CRY_30_LIBCV_DUMMY_STATEMENT(statement) ( (void)(statement) )
# else
#  define CRY_30_LIBCV_DUMMY_STATEMENT(statement)
# endif
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if ( CRY_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
typedef struct
{
  P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr;
  P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) keyPtr;
  P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) dataPtr;
  uint32 dataLength;
  P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr;
  P2VAR( uint32, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultLengthPtr;
  boolean truncationIsAllowed;
} Cry_30_LibCv_CmacAes128Gen_BufferType;
#endif /* ( CRY_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF ) */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#if ( CRY_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
# define CRY_30_LIBCV_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_LOCAL VAR(Cry_30_LibCv_CmacAes128Gen_BufferType, CRY_30_LIBCV_VAR_NOINIT) Cry_30_LibCv_CmacAes128Gen_Buffer; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_LIBCV_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define CRY_30_LIBCV_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_LOCAL VAR(uint8, CRY_30_LIBCV_VAR_NOINIT) Cry_30_LibCv_CmacAes128Gen_Status; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
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

CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128GenStartInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                             P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) keyPtr);

CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128GenUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                              P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) dataPtr,
                                                                                              uint32 dataLength);

CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128GenFinishInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                              P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr,
                                                                                              P2VAR( uint32, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultLengthPtr,
                                                                                              boolean truncationIsAllowed);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Cry_30_LibCv_CmacAes128GenStartInternal()
 *********************************************************************************************************************/
/*! \brief      Common service start function for synchronous and asynchronous behavior
 *  \see        Cry_30_LibCv_CmacAes128GenStart()
 *********************************************************************************************************************/
CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128GenStartInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                             P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) keyPtr)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  P2CONST( Cry_30_LibCv_CmacAes128GenConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_LibCv_CmacAes128GenConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cfgPtr;

  P2VAR( Cry_30_LibCv_CmacAes128GenWorkSpaceType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) workSpacePtr = Cry_30_LibCv_GetAddrCmacAes128GenWorkSpace(Cry_30_LibCv_GetCmacAes128GenWorkSpaceIdxOfCmacAes128GenConfig(contextPtr));

  /* Null pointer and range check */
  if (keyPtr->length <= 0xFFFFu)
  {
    /* Init work space */
    if (ESL_ERC_NO_ERROR == esl_initWorkSpaceHeader( &workSpacePtr->workSpace.header,
                                                     ESL_MAXSIZEOF_WS_CMACAES,
                                                     CRY_CMACAES128GEN_WATCHDOG_PTR ) )
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
 *  Cry_30_LibCv_CmacAes128GenUpdateInternal()
 *********************************************************************************************************************/
/*! \brief      Common service update function for synchronous and asynchronous behavior
 *  \see        Cry_30_LibCv_CmacAes128GenUpdate()
 *********************************************************************************************************************/
CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128GenUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                              P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) dataPtr,
                                                                                              uint32 dataLength)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  P2CONST( Cry_30_LibCv_CmacAes128GenConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_LibCv_CmacAes128GenConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cfgPtr;

  P2VAR( Cry_30_LibCv_CmacAes128GenWorkSpaceType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) workSpacePtr = Cry_30_LibCv_GetAddrCmacAes128GenWorkSpace(Cry_30_LibCv_GetCmacAes128GenWorkSpaceIdxOfCmacAes128GenConfig(contextPtr));

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
 *  Cry_30_LibCv_CmacAes128GenFinishInternal()
 *********************************************************************************************************************/
/*! \brief      Common service finish function for synchronous and asynchronous behavior
 *  \see        Cry_30_LibCv_CmacAes128GenFinish()
 *********************************************************************************************************************/
CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128GenFinishInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                              P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr,
                                                                                              P2VAR( uint32, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultLengthPtr,
                                                                                              boolean truncationIsAllowed)
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  eslt_Byte macBuffer[CRY_CMACAES128GEN_MACSIZE];
  uint32 resultLength = 0;
  uint8_least i;

  P2CONST( Cry_30_LibCv_CmacAes128GenConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_LibCv_CmacAes128GenConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cfgPtr;

  P2VAR( Cry_30_LibCv_CmacAes128GenWorkSpaceType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) workSpacePtr = Cry_30_LibCv_GetAddrCmacAes128GenWorkSpace(Cry_30_LibCv_GetCmacAes128GenWorkSpaceIdxOfCmacAes128GenConfig(contextPtr));


  /* Interpet length as number of bytes */
  resultLength = (*resultLengthPtr & 0xFFFFu);


  /* Finalize the HMAC calculation */
  if (ESL_ERC_NO_ERROR == esl_finalizeCMACAES128( &workSpacePtr->workSpace,
                                                  macBuffer) )
  {
    /* Copy MAC to result pointer and truncate optionally */
    if ((truncationIsAllowed == FALSE)
      && (resultLength < CRY_CMACAES128GEN_MACSIZE))
    {
      /* No output written */
      *resultLengthPtr = 0u;

      /* MAC cannot be written to the buffer */
      retVal = CSM_E_SMALL_BUFFER;
    }
    else
    {
      if (resultLength > CRY_CMACAES128GEN_MACSIZE)
      {
        resultLength = CRY_CMACAES128GEN_MACSIZE;
      }

      for (i = 0u; i < resultLength; i++)
      {
        resultPtr[i] = macBuffer[i];
      }

      /* Write back result length */
      *resultLengthPtr = resultLength;


      retVal = CSM_E_OK;
    }
  }

  return retVal;
}


/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Cry_30_LibCv_CmacAes128GenInit()
 *********************************************************************************************************************/
/*! \brief      Initializes the service
 *  \context    System Startup
 *  \note       Called by application (BswM)
 *********************************************************************************************************************/
FUNC( void, CRY_30_LIBCV_CODE) Cry_30_LibCv_CmacAes128GenInit( void )
{
#if ( CRY_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_CmacAes128Gen_Status = CRY_30_LIBCV_STATE_IDLE;
#endif
}


/**********************************************************************************************************************
 *  Cry_30_LibCv_CmacAes128GenMainFunction()
 *********************************************************************************************************************/
/*! \brief      API to be called to process the requested services.
 *  \context    Function could be called from task level only
 *  \note       Scheduled by the CSM
 *********************************************************************************************************************/
FUNC(void, CRY_30_LIBCV_CODE) Cry_30_LibCv_CmacAes128GenMainFunction( void )
{
#if ( CRY_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_ReturnType retVal;

  switch(Cry_30_LibCv_CmacAes128Gen_Status)
  {
    case CRY_30_LIBCV_STATE_START:
    {
      retVal = Cry_30_LibCv_CmacAes128GenStartInternal( Cry_30_LibCv_CmacAes128Gen_Buffer.cfgPtr,
                                                        Cry_30_LibCv_CmacAes128Gen_Buffer.keyPtr );

      Cry_30_LibCv_CmacAes128Gen_Status = CRY_30_LIBCV_STATE_IDLE;

      Csm_MacGenerateCallbackNotification( retVal );
      break;
    }
    case CRY_30_LIBCV_STATE_UPDATE:
    {
      retVal = Cry_30_LibCv_CmacAes128GenUpdateInternal( Cry_30_LibCv_CmacAes128Gen_Buffer.cfgPtr,
                                                         Cry_30_LibCv_CmacAes128Gen_Buffer.dataPtr,
                                                         Cry_30_LibCv_CmacAes128Gen_Buffer.dataLength );

      Cry_30_LibCv_CmacAes128Gen_Status = CRY_30_LIBCV_STATE_IDLE;

      Csm_MacGenerateCallbackNotification( retVal );
      break;
    }
    case CRY_30_LIBCV_STATE_FINISH:
    {
      retVal = Cry_30_LibCv_CmacAes128GenFinishInternal( Cry_30_LibCv_CmacAes128Gen_Buffer.cfgPtr,
                                                         Cry_30_LibCv_CmacAes128Gen_Buffer.resultPtr,
                                                         Cry_30_LibCv_CmacAes128Gen_Buffer.resultLengthPtr,
                                                         Cry_30_LibCv_CmacAes128Gen_Buffer.truncationIsAllowed );

      Cry_30_LibCv_CmacAes128Gen_Status = CRY_30_LIBCV_STATE_IDLE;

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
 *  Cry_30_LibCv_CmacAes128GenStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the MAC generation service of the CSM module.
 *  \param[in]     cfgPtr        Pointer to the configuration.
 *  \param[in]     keyPtr        Holds a pointer to the key.
 *  \return        CSM_E_OK      Request successful
 *  \return        CSM_E_NOT_OK  Request failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23049
 *  \trace         SPEC-47495
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128GenStart( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                           P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) keyPtr)
{
#if ( CRY_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_CmacAes128Gen_Buffer.cfgPtr = cfgPtr;
  Cry_30_LibCv_CmacAes128Gen_Buffer.keyPtr = keyPtr;
  Cry_30_LibCv_CmacAes128Gen_Status = CRY_30_LIBCV_STATE_START;
  return CSM_E_OK;
#else
  return Cry_30_LibCv_CmacAes128GenStartInternal( cfgPtr, keyPtr );
#endif
}


/**********************************************************************************************************************
 *  Cry_30_LibCv_CmacAes128GenUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the MAC generation service with the input data.
 *  \param[in]     cfgPtr        Pointer to the configuration.
 *  \param[in]     dataPtr       Holds a pointer to the data for which a MAC shall be computed.
 *  \param[in]     dataLength    Contains the number of bytes for which the MAC shall be computed.
 *  \return        CSM_E_OK      Request successful
 *  \return        CSM_E_NOT_OK  Request failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23049
 *  \trace         SPEC-47265
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128GenUpdate( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) dataPtr,
                                                                            uint32 dataLength)
{
#if ( CRY_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_CmacAes128Gen_Buffer.cfgPtr = cfgPtr;
  Cry_30_LibCv_CmacAes128Gen_Buffer.dataPtr = dataPtr;
  Cry_30_LibCv_CmacAes128Gen_Buffer.dataLength = dataLength;
  Cry_30_LibCv_CmacAes128Gen_Status = CRY_30_LIBCV_STATE_UPDATE;
  return CSM_E_OK;
#else
  return Cry_30_LibCv_CmacAes128GenUpdateInternal( cfgPtr, dataPtr, dataLength );
#endif
}


/**********************************************************************************************************************
 *  Cry_30_LibCv_CmacAes128GenFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the MAC generation service.
 *  \param[in]     cfgPtr        Pointer to the configuration.
 *  \param[out]    resultPtr            Holds a pointer to the memory location which will hold the hash value.
 *  \param[in,out] resultLengthPtr      Holds a pointer to the memory location in which the length information is
 *                                      stored.
 *  \param[in]     truncationIsAllowed  This parameter states whether a truncation of the result is allowed or not.
 *                                      TRUE: truncation is allowed.
 *                                      FALSE: truncation is not allowed.
 *  \return        CSM_E_OK             Request successful
 *  \return        CSM_E_NOT_OK         Request failed
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23049
 *  \trace         SPEC-47476
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128GenFinish( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                            P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr,
                                                                            P2VAR( uint32, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultLengthPtr,
                                                                            boolean truncationIsAllowed)
{
#if ( CRY_CMACAES128GEN_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_CmacAes128Gen_Buffer.cfgPtr = cfgPtr;
  Cry_30_LibCv_CmacAes128Gen_Buffer.resultPtr = resultPtr;
  Cry_30_LibCv_CmacAes128Gen_Buffer.resultLengthPtr = resultLengthPtr;
  Cry_30_LibCv_CmacAes128Gen_Buffer.truncationIsAllowed = truncationIsAllowed;
  Cry_30_LibCv_CmacAes128Gen_Status = CRY_30_LIBCV_STATE_FINISH;
  return CSM_E_OK;
#else
  return Cry_30_LibCv_CmacAes128GenFinishInternal( cfgPtr, resultPtr, resultLengthPtr, truncationIsAllowed );
#endif
}


#define CRY_30_LIBCV_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ( CRY_30_LIBCV_CMACAES128GEN_ENABLED == STD_ON ) */

/**********************************************************************************************************************
 *  END OF FILE: CRY_CMACAES128GEN.C
 *********************************************************************************************************************/

 