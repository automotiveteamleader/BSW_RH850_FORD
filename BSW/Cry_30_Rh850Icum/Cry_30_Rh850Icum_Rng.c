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
 *         File:  Cry_30_Rh850Icum_Rng.c
 *    Component:  DrvCry_Rh850Icum
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  Implements the PRNG CRY API for the ICUMB.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define CRY_30_RH850ICUM_RNG_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_Rh850Icum.h"
#include "Csm_Cbk.h"
#include "Cry_30_Rh850Icum_CommonUtil.h"

#if ( CRY_30_RH850ICUM_RNGCONFIG== STD_ON )
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#define CRY_30_RH850ICUM_RNG_USE_SYNC_JOB_PROCESSING     CRY_30_RH850ICUM_USE_SYNC_JOB_PROCESSING
#define CRY_30_RH850ICUM_RNG_RNG_SIZE                    (16u)

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

#if ( CRY_30_RH850ICUM_RNG_USE_SYNC_JOB_PROCESSING == STD_OFF )
typedef struct
{
  P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr;
  P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) seedPtr;
  uint32 seedLength;
} Cry_30_Rh850Icum_RngSeed_BufferType;

typedef struct
{
  P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr;
  P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) resultPtr;
  uint32 resultLength;
} Cry_30_Rh850Icum_RngGenerate_BufferType;
#endif /* ( CRY_30_RH850ICUM_RNG_USE_SYNC_JOB_PROCESSING == STD_OFF ) */


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

#if ( CRY_30_RH850ICUM_RNG_USE_SYNC_JOB_PROCESSING == STD_OFF )
# define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_30_RH850ICUM_LOCAL VAR(Cry_30_Rh850Icum_RngGenerate_BufferType, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_RngGenerate_Buffer; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
CRY_30_RH850ICUM_LOCAL VAR(Cry_30_Rh850Icum_RngSeed_BufferType, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_RngSeed_Buffer; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_RH850ICUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_30_RH850ICUM_LOCAL VAR(uint8, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_RngSeed_Status; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
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

CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedStartInternal( void );

CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedUpdateInternal( P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) seedPtr,
                                                                          uint32 seedLength );

CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedFinishInternal( void );

CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngGenerateInternal( P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) resultPtr,
                                                                        uint32 resultLength );

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_RngSeedStartInternal()
 **********************************************************************************************************************/
/*! \brief      Common service start function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_RngSeedStart()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedStartInternal( void )
{
  Csm_ReturnType retVal = CSM_E_BUSY;

  /* State and NULL_PTR check */
  if ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_IDLE )
  {
    Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_PRNGSEED_START;
    retVal = CSM_E_OK;
  }

  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_RngSeedUpdateInternal()
 **********************************************************************************************************************/
/*! \brief      Common service update function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_RngSeedUpdate()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedUpdateInternal( P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) seedPtr,
                                                                          uint32 seedLength )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  /* NULL_PTR and range check */
  if ( ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_PRNGSEED_START )
    && ( seedPtr != NULL_PTR )
    && ( seedLength == CRY_30_RH850ICUM_RNG_RNG_SIZE ) )
  {
    /* ICUM uses a TRNG. Seeding is not needed and not supported by the ICUM */
      retVal = CSM_E_OK;
  }

  if ( retVal == CSM_E_OK)
  {
    Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_PRNGSEED_UPDATE;
  }

  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_RngSeedFinishInternal()
 **********************************************************************************************************************/
/*! \brief      Common service finish function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_RngSeedFinish()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedFinishInternal( void )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  /* State and NULL_PTR check */
  if ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_PRNGSEED_UPDATE )
  {
    retVal = CSM_E_OK;
  }

  Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_IDLE;

  return retVal;
}

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_RngGenerateInternal()
 **********************************************************************************************************************/
/*! \brief      Common service finish function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_RngGenerate()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngGenerateInternal( P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) resultPtr,
                                                                        uint32 resultLength )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 randomNumberBuffer[CRY_30_RH850ICUM_RNG_RNG_SIZE];
  uint8_least i;
  r_icumif_isd_t *p_ISD = &ISD;

  /* State, NULL_PTR and range check */
  if ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_IDLE )
  {
    if ( ( resultPtr != NULL_PTR )
      && ( resultLength <= CRY_30_RH850ICUM_RNG_RNG_SIZE ) )
    {
      p_ISD->service_id = SERVICE_02_RAND_GENERATE;
      p_ISD->p_callbackfunc = 0;
      p_ISD->job_id = 0;
      p_ISD->prm.RAND_GENERATE.p_block_out = randomNumberBuffer;
      p_ISD->prm.RAND_GENERATE.nb_blocks = 1;
      p_ISD->prm.RAND_GENERATE.job_slice = 0;

      /* trigger the security service */
      Cry_30_Rh850Icum_TriggerServiceAndWait(p_ISD);

      if (p_ISD->service_result != SERV_OK)
      {
        retVal = CSM_E_NOT_OK;
      }
      else {
        /* Write back data */
        for (i = 0u; i < resultLength; i++)
        {
          resultPtr[i] = randomNumberBuffer[i];
        }

        retVal = CSM_E_OK;
      }
    }
  }
  else
  {
    retVal = CSM_E_BUSY;
  }

  Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_IDLE;

  return retVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_RngInit()
 **********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the PRNG of the SHE.
 *  \context       Function could be called from task level only.
 *  \reentrant     Non reentrant
 *  \synchronous   Sync. or async. (depending on configuration)
 *  \note          Called by Cry_Init().
 **********************************************************************************************************************/
FUNC( void, CRY_30_RH850ICUM_CODE)  Cry_30_Rh850Icum_RngInit( void )
{
  /* ICUM does not need to initialize the RNG */

#if ( CRY_30_RH850ICUM_RNG_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_RngSeed_Status = CRY_30_RH850ICUM_STATE_IDLE;
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_RngSeedMainFunction()
 **********************************************************************************************************************/
/*! \brief      API to be called to process the requested services.
 *  \context    Function could be called from task level only
 *  \note       Scheduled by the CSM
**********************************************************************************************************************/
FUNC(void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_RngSeedMainFunction( void )
{
#if ( CRY_30_RH850ICUM_RNG_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_ReturnType retVal;
  switch(Cry_30_Rh850Icum_RngSeed_Status)
  {
    case CRY_30_RH850ICUM_STATE_START:
    {
      retVal = Cry_30_Rh850Icum_RngSeedStartInternal( );

      Cry_30_Rh850Icum_RngSeed_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_RandomSeedCallbackNotification( retVal );
      break;
    }
    case CRY_30_RH850ICUM_STATE_UPDATE:
    {
      retVal = Cry_30_Rh850Icum_RngSeedUpdateInternal( Cry_30_Rh850Icum_RngSeed_Buffer.seedPtr,
                                              Cry_30_Rh850Icum_RngSeed_Buffer.seedLength );

      Cry_30_Rh850Icum_RngSeed_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_RandomSeedCallbackNotification( retVal );
      break;
    }
    case CRY_30_RH850ICUM_STATE_FINISH:
    {
      retVal = Cry_30_Rh850Icum_RngSeedFinishInternal( );

      Cry_30_Rh850Icum_RngSeed_Status = CRY_30_RH850ICUM_STATE_IDLE;

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
 * Cry_30_Rh850Icum_RngGenerateMainFunction()
 **********************************************************************************************************************/
/*! \brief      API to be called to process the requested services.
 *  \context    Function could be called from task level only
 *  \note       Scheduled by the CSM
**********************************************************************************************************************/
FUNC(void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_RngGenerateMainFunction( void )
{
#if ( CRY_30_RH850ICUM_RNG_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_ReturnType retVal;

  retVal=Cry_30_Rh850Icum_RngGenerateInternal( Cry_30_Rh850Icum_RngGenerate_Buffer.resultPtr, Cry_30_Rh850Icum_RngGenerate_Buffer.resultLength );

  Csm_RandomGenerateCallbackNotification( retVal );
  Csm_RandomGenerateServiceFinishNotification();

#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_RngSeedStart()
**********************************************************************************************************************/
/*! \brief        This function sets the state for asynchronous mode
 *  \param[in]    cfgPtr        Pointer to the configuration.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_BUSY    Request failed, service is still busy.
 *  \context      Called by CSM.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedStart( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr ) /* PRQA S 3673 */ /* MD_CRY_16.7 */
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

#if ( CRY_30_RH850ICUM_RNG_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_RngSeed_Status = CRY_30_RH850ICUM_STATE_START;
  retVal = CSM_E_OK;
#else
  retVal = Cry_30_Rh850Icum_RngSeedStartInternal( );
#endif

  CRY_30_RH850ICUM_DUMMY_STATEMENT( cfgPtr ); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_RngSeedUpdate()
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
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedUpdate( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                        P2CONST( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) seedPtr,
                                                        uint32 seedLength )
{
  CRY_30_RH850ICUM_DUMMY_STATEMENT( cfgPtr ); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#if ( CRY_30_RH850ICUM_RNG_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_RngSeed_Buffer.seedPtr = seedPtr;
  Cry_30_Rh850Icum_RngSeed_Buffer.seedLength = seedLength;
  Cry_30_Rh850Icum_RngSeed_Status = CRY_30_RH850ICUM_STATE_UPDATE;
  return CSM_E_OK;
#else
  return Cry_30_Rh850Icum_RngSeedUpdateInternal( seedPtr, seedLength );
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_RngSeedFinish()
**********************************************************************************************************************/
/*! \brief         This function finalizes the random seed service.
 *  \param[in]     cfgPtr        Pointer to the configuration.
 *  \return        CSM_E_OK      Request successful.
 *  \context       Called by CSM.
 *  \note          This function does actually nothing but is needed for the service configuration function pointer.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngSeedFinish( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr ) /* PRQA S 3673 */ /* MD_CRY_16.7 */
{
  CRY_30_RH850ICUM_DUMMY_STATEMENT( cfgPtr ); /* PRQA S 3112 */ /* MD_MSR_14.2 */
#if ( CRY_30_RH850ICUM_RNG_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_RngSeed_Status = CRY_30_RH850ICUM_STATE_FINISH;
  return CSM_E_OK;
#else
  return Cry_30_Rh850Icum_RngSeedFinishInternal( );
#endif
}

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_RngGenerate()
**********************************************************************************************************************/
/*! \brief         Generates a random number according to the SHE specification.
 *  \param[in]     cfgPtr        Pointer to the configuration.
 *  \param[out]    resultPtr     Holds a pointer to the memory location which will hold the result of the random
 *                                number generation. The memory location must have at least the size "resultLength".
 *  \param[in]     resultLength  Holds the amount of random bytes which should be generated.
 *  \return        CSM_E_OK      - Request successful.
 *  \return        CSM_E_NOT_OK  - Request failed.
 *  \context       Called by CSM.
 *  \pre           The SHE PRNG have to be initialized
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_RngGenerate( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                      P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) resultPtr,
                                                      uint32 resultLength )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

#if ( CRY_30_RH850ICUM_RNG_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_RngGenerate_Buffer.resultPtr = resultPtr;
  Cry_30_Rh850Icum_RngGenerate_Buffer.resultLength = resultLength;
  Cry_30_Rh850Icum_RngSeed_Status = CRY_30_RH850ICUM_STATE_FINISH;
  retVal = CSM_E_OK;
#else
  retVal = Cry_30_Rh850Icum_RngGenerateInternal( resultPtr, resultLength );
#endif

  CRY_30_RH850ICUM_DUMMY_STATEMENT( cfgPtr ); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  return retVal;
}

#define CRY_30_RH850ICUM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ( CRY_30_RH850ICUM_RNGCONFIG== STD_ON ) */

/**********************************************************************************************************************
 *  END OF FILE: CRY_30_RH850ICUM_RNG.c
 *********************************************************************************************************************/
