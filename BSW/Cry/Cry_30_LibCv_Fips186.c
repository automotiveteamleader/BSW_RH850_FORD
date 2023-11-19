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
 *         File:  Cry_30_LibCv_Fips186.c
 *    Component:  SysService_AsrCry
 *       Module:  MICROSAR Cryptographic library module (Cry)
 *    Generator:  -
 *
 *  Description:  Implements the FIPS186-2 RNG API for the ASR CSM
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

#define CRY_FIPS186_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_LibCv.h"
#include "Cry_30_LibCv_Fips186.h"
#include "Csm_Cbk.h"


#if ( CRY_30_LIBCV_FIPS186CONFIG == STD_ON )
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#define CRY_FIPS186_USE_SYNC_JOB_PROCESSING     CRY_30_LIBCV_USE_SYNC_JOB_PROCESSING
#define CRY_FIPS186_WATCHDOG_PTR                (0u)

#if !defined (CRY_LOCAL)
# define CRY_LOCAL static
#endif

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 **********************************************************************************************************************/

#if ( CRY_FIPS186_USE_SYNC_JOB_PROCESSING == STD_OFF )
typedef struct
{
  P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr;
  P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) seedPtr;
  uint32 seedLength;
} Cry_30_LibCv_Fips186Seed_BufferType;

typedef struct
{
  P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr;
  P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) resultPtr;
  uint32 resultLength;
} Cry_30_LibCv_Fips186Generate_BufferType;
#endif /* ( CRY_FIPS186_USE_SYNC_JOB_PROCESSING == STD_OFF ) */


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

#if ( CRY_FIPS186_USE_SYNC_JOB_PROCESSING == STD_OFF )
# define CRY_30_LIBCV_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_LOCAL VAR(Cry_30_LibCv_Fips186Generate_BufferType, CRY_30_LIBCV_VAR_NOINIT) Cry_30_LibCv_Fips186Generate_Buffer; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
CRY_LOCAL VAR(Cry_30_LibCv_Fips186Seed_BufferType, CRY_30_LIBCV_VAR_NOINIT) Cry_30_LibCv_Fips186Seed_Buffer; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_LIBCV_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define CRY_30_LIBCV_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_LOCAL VAR(uint8, CRY_30_LIBCV_VAR_NOINIT) Cry_30_LibCv_Fips186Seed_Status; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_LIBCV_STOP_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
#endif


/**********************************************************************************************************************
 *  GLOBAL DATA
 **********************************************************************************************************************/


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/
#define CRY_30_LIBCV_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186SeedStartInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr );

CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186SeedUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr,
                                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) seedPtr,
                                                                                            uint32 seedLength );

CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186GenerateInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr,
                                                                                          P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr,
                                                                                          uint32 resultLength );

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Cry_30_LibCv_Fips186SeedStartInternal()
 **********************************************************************************************************************/
/*! \brief      Common service start function for synchronous and asynchronous behavior
 *  \see        Cry_30_LibCv_Fips186SeedStart()
 **********************************************************************************************************************/
CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186SeedStartInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr ) /* PRQA S 3673 */ /* MD_CRY_16.7 */
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  P2CONST( Cry_30_LibCv_Fips186ConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_LibCv_Fips186ConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cfgPtr;

  P2VAR( Cry_30_LibCv_Fips186WorkSpaceType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) workSpacePtr = Cry_30_LibCv_GetAddrFips186WorkSpace(Cry_30_LibCv_GetFips186WorkSpaceIdxOfFips186Config(contextPtr));

  if ( Cry_30_LibCv_IsSaveStateOfFips186Config(contextPtr) && (workSpacePtr->seedInitialized == TRUE) )
  {
    /* Do nothing when Save State is enabled and RNG is already initialized */
    retVal = CSM_E_OK;
  }
  else
  {
    /* Initialize workspace */
    if (ESL_ERC_NO_ERROR == esl_initWorkSpaceHeader( &workSpacePtr->workSpace.header,
                                                     ESL_MAXSIZEOF_WS_FIPS186,
                                                     CRY_FIPS186_WATCHDOG_PTR) )
    {
      retVal = CSM_E_OK;
    } 
  }

  return retVal;
}

/**********************************************************************************************************************
 * Cry_30_LibCv_Fips186SeedUpdateInternal()
 **********************************************************************************************************************/
/*! \brief      Common service update function for synchronous and asynchronous behavior
 *  \see        Cry_30_LibCv_Fips186SeedUpdate()
 **********************************************************************************************************************/
CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186SeedUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr,
                                                                                            P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) seedPtr,
                                                                                            uint32 seedLength )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  P2CONST( Cry_30_LibCv_Fips186ConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_LibCv_Fips186ConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cfgPtr;

  P2VAR( Cry_30_LibCv_Fips186WorkSpaceType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) workSpacePtr = Cry_30_LibCv_GetAddrFips186WorkSpace(Cry_30_LibCv_GetFips186WorkSpaceIdxOfFips186Config(contextPtr));

  P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) statePtr = 0u;

  /* (Re)-initialization necessary? */
  if (Cry_30_LibCv_IsSaveStateOfFips186Config(contextPtr) && (workSpacePtr->seedInitialized == TRUE))
  {
    /* FIPS186 stir up */
    if (ESL_ERC_NO_ERROR == esl_stirFIPS186( &workSpacePtr->workSpace,
                                             (eslt_Length)seedLength,
                                             (P2VAR(eslt_Byte, AUTOMATIC, CRY_30_LIBCV_APPL_VAR))seedPtr) ) /* PRQA S 0311 */ /* MD_CRY_11.5 */
    {
      retVal = CSM_E_OK;
    }
  }
  else
  {
    /* FIPS186 initialization */
    if (ESL_ERC_NO_ERROR == esl_initFIPS186( &workSpacePtr->workSpace,
                                             (eslt_Length)seedLength,
                                             (P2CONST(eslt_Byte, AUTOMATIC, CRY_30_LIBCV_APPL_VAR))seedPtr,
                                             (P2VAR(eslt_Byte, AUTOMATIC, CRY_30_LIBCV_APPL_VAR))statePtr) )
    {
      workSpacePtr->seedInitialized = TRUE;
      retVal = CSM_E_OK;
    }
  }

  return retVal;
}

/**********************************************************************************************************************
 * Cry_30_LibCv_Fips186GenerateInternal()
 **********************************************************************************************************************/
/*! \brief      Common service finish function for synchronous and asynchronous behavior
 *  \see        Cry_30_LibCv_Fips186Generate()
 **********************************************************************************************************************/
CRY_LOCAL FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186GenerateInternal( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr,
                                                                                          P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR )  resultPtr,
                                                                                          uint32                                   resultLength )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  P2CONST( Cry_30_LibCv_Fips186ConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) contextPtr =
    (P2CONST( Cry_30_LibCv_Fips186ConfigType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ))cfgPtr;

  P2VAR( Cry_30_LibCv_Fips186WorkSpaceType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) workSpacePtr = Cry_30_LibCv_GetAddrFips186WorkSpace(Cry_30_LibCv_GetFips186WorkSpaceIdxOfFips186Config(contextPtr));

  /* Generate random numbers according to FIPS186-2 */
  if ( ESL_ERC_NO_ERROR == ( esl_getBytesFIPS186( &workSpacePtr->workSpace,
                                                  (eslt_Length)resultLength,
                                                  (P2VAR( eslt_Byte, AUTOMATIC, CRY_30_LIBCV_APPL_VAR )) resultPtr ) ) )
  {
    retVal = CSM_E_OK;
  }

  return retVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Cry_30_LibCv_Fips186Init()
 **********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the FIPS186-2 service of the CSM module.
 *  \context       Function could be called from task level only.
 *  \reentrant     Non reentrant
 *  \synchronous   Sync. or async. (depending on configuration)
 *  \note          Called by application.
 **********************************************************************************************************************/
FUNC( void, CRY_30_LIBCV_CODE) Cry_30_LibCv_Fips186Init( void )
{
#if ( CRY_FIPS186_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_Fips186Seed_Status = CRY_30_LIBCV_STATE_IDLE;
#endif
}


/**********************************************************************************************************************
 * Cry_30_LibCv_Fips186SeedMainFunction()
 **********************************************************************************************************************/
/*! \brief      API to be called to process the requested services.
 *  \context    Function could be called from task level only
 *  \note       Scheduled by the CSM
**********************************************************************************************************************/
FUNC(void, CRY_30_LIBCV_CODE) Cry_30_LibCv_Fips186SeedMainFunction( void )
{
#if ( CRY_FIPS186_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_ReturnType retVal;
  switch(Cry_30_LibCv_Fips186Seed_Status)
  {
    case CRY_30_LIBCV_STATE_START:
    {
      retVal = Cry_30_LibCv_Fips186SeedStartInternal( Cry_30_LibCv_Fips186Seed_Buffer.cfgPtr );

      Cry_30_LibCv_Fips186Seed_Status = CRY_30_LIBCV_STATE_IDLE;

      Csm_RandomSeedCallbackNotification( retVal );
      break;
    }
    case CRY_30_LIBCV_STATE_UPDATE:
    {
      retVal = Cry_30_LibCv_Fips186SeedUpdateInternal( Cry_30_LibCv_Fips186Seed_Buffer.cfgPtr,
                                                       Cry_30_LibCv_Fips186Seed_Buffer.seedPtr,
                                                       Cry_30_LibCv_Fips186Seed_Buffer.seedLength );

      Cry_30_LibCv_Fips186Seed_Status = CRY_30_LIBCV_STATE_IDLE;

      Csm_RandomSeedCallbackNotification( retVal );
      break;
    }
    case CRY_30_LIBCV_STATE_FINISH:
    {
      retVal = CSM_E_OK;

      Cry_30_LibCv_Fips186Seed_Status = CRY_30_LIBCV_STATE_IDLE;

      Csm_RandomSeedCallbackNotification( retVal );
      Csm_RandomSeedServiceFinishNotification();
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
 * Cry_30_LibCv_Fips186GenerateMainFunction()
 **********************************************************************************************************************/
/*! \brief      API to be called to process the requested services.
 *  \context    Function could be called from task level only
 *  \note       Scheduled by the CSM
**********************************************************************************************************************/
FUNC(void, CRY_30_LIBCV_CODE) Cry_30_LibCv_Fips186GenerateMainFunction( void )
{
#if ( CRY_FIPS186_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_ReturnType retVal;

  retVal = Cry_30_LibCv_Fips186GenerateInternal( Cry_30_LibCv_Fips186Generate_Buffer.cfgPtr,
                                                 Cry_30_LibCv_Fips186Generate_Buffer.resultPtr,
                                                 Cry_30_LibCv_Fips186Generate_Buffer.resultLength );

  Csm_RandomGenerateCallbackNotification( retVal );
  Csm_RandomGenerateServiceFinishNotification();

#endif
}


/**********************************************************************************************************************
 * Cry_30_LibCv_Fips186SeedStart()
**********************************************************************************************************************/
/*! \brief        This function initializes the workspace for the random seed service.
 *  \param[in]    cfgPtr        Pointer to the configuration.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \context      Called by CSM.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186SeedStart( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr ) /* PRQA S 3673 */ /* MD_CRY_16.7 */
{
#if ( CRY_FIPS186_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_Fips186Seed_Buffer.cfgPtr = cfgPtr;
  Cry_30_LibCv_Fips186Seed_Status = CRY_30_LIBCV_STATE_START;
  return CSM_E_OK;
#else
  return Cry_30_LibCv_Fips186SeedStartInternal(cfgPtr);
#endif
}


/**********************************************************************************************************************
 * Cry_30_LibCv_Fips186SeedUpdate()
**********************************************************************************************************************/
/*! \brief         This function shall be used to feed a seed to the random number generator.
 *  \param[in]     cfgPtr        Pointer to the configuration.
 *  \param[in]     seedPtr       Holds a pointer to the seed for the random number generator.
 *  \param[in]     seedLength    Contains the length of the seed in bytes.
 *  \return        CSM_E_OK      Request successful.
 *  \return        CSM_E_NOT_OK  Request failed.
 *  \context       Called by CSM.
 *  \note          This function can be called more than once.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186SeedUpdate( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr,
                                                                          P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) seedPtr,
                                                                          uint32 seedLength )
{
#if ( CRY_FIPS186_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_Fips186Seed_Buffer.cfgPtr = cfgPtr;
  Cry_30_LibCv_Fips186Seed_Buffer.seedPtr = seedPtr;
  Cry_30_LibCv_Fips186Seed_Buffer.seedLength = seedLength;
  Cry_30_LibCv_Fips186Seed_Status = CRY_30_LIBCV_STATE_UPDATE;
  return CSM_E_OK;
#else
  return Cry_30_LibCv_Fips186SeedUpdateInternal(cfgPtr, seedPtr, seedLength);
#endif
}


/**********************************************************************************************************************
 * Cry_30_LibCv_Fips186SeedFinish()
**********************************************************************************************************************/
/*! \brief         This function finalizes the random seed service.
 *  \param[in]     cfgPtr        Pointer to the configuration.
 *  \return        CSM_E_OK      Request successful.
 *  \context       Called by CSM.
 *  \note          This function does actually nothing but is needed for the service configuration function pointer.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186SeedFinish( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr ) /* PRQA S 3673 */ /* MD_CRY_16.7 */
{
  CRY_30_LIBCV_DUMMY_STATEMENT( cfgPtr ); /* PRQA S 3112 */ /* MD_CRY_14.2 */

#if ( CRY_FIPS186_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_Fips186Seed_Status = CRY_30_LIBCV_STATE_FINISH;
  return CSM_E_OK;
#else
  return CSM_E_OK;
#endif
}

/**********************************************************************************************************************
 * Cry_30_LibCv_Fips186Generate()
**********************************************************************************************************************/
/*! \brief         Generates a random number according to the FIPS186-2 specification.
 *  \param[in]     cfgPtr        Pointer to the configuration.
 *  \param[out]    resultPtr     Holds a pointer to the memory location which will hold the result of the random
 *                                number generation. The memory location must have at least the size "resultLength".
 *  \param[in]     resultLength  Holds the amount of random bytes which should be generated.
 *  \return        CSM_E_OK      - Request successful.
 *  \return        CSM_E_NOT_OK  - Request failed.
 *  \context       Called by CSM.
 *  \pre           The context buffer must be the same that has been used for the call of the FIPS186 RandomSeed
 *                  interface.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_Fips186Generate( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cfgPtr,
                                                                        P2VAR( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr,
                                                                        uint32 resultLength )
{
#if ( CRY_FIPS186_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_LibCv_Fips186Generate_Buffer.cfgPtr = cfgPtr;
  Cry_30_LibCv_Fips186Generate_Buffer.resultPtr = resultPtr;
  Cry_30_LibCv_Fips186Generate_Buffer.resultLength = resultLength;
  Cry_30_LibCv_Fips186Seed_Status = CRY_30_LIBCV_STATE_FINISH;
  return CSM_E_OK;
#else
  return Cry_30_LibCv_Fips186GenerateInternal(cfgPtr, resultPtr, resultLength);
#endif
}

#define CRY_30_LIBCV_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ( CRY_30_LIBCV_FIPS186CONFIG == STD_ON ) */

/**********************************************************************************************************************
 * Module specific MISRA deviations
 *********************************************************************************************************************/
/* Justification for module-specific MISRA deviations:

  MD_CRY_11.5:
    Reason:     The provided API parameter has no constant qualifier. However the API only passes the parameter to
                another function, which has a constant modifier.
    Risk:       No risk since the esl_stirFIPS186 function doesn't modify the buffer.
    Prevention: Covered by code review.

  MD_CRY_16.7:
    Reason:     The given pointer shall not be CONST due to AUTOSAR CSM SWS as the data can be modified in lower layers.
    Risk:       None.
    Prevention: Covered by code review.

 */

/**********************************************************************************************************************
 *  END OF FILE: CRY_30_LIBCV_FIPS186.c
 *********************************************************************************************************************/
