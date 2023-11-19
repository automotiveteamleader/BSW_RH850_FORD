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
 *         File:  Cry_30_Rh850Icum_KeyWrapSym.c
 *    Component:  DrvCry_Rh850Icum
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  Implements the KeyWrapSym CRY API for the ICUMB.
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file.
 *********************************************************************************************************************/

#define CRY_30_RH850ICUM_KEYWRAPSYM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_Rh850Icum.h"
#include "Csm_Cbk.h"
#include "Cry_30_Rh850Icum_KeyWrapSym.h"
#include "Cry_30_Rh850Icum_CommonUtil.h"

#if ( CRY_30_RH850ICUM_KEYWRAPSYMCONFIG == STD_ON )
/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/
#define CRY_30_RH850ICUM_KEYWRAPSYM_USE_SYNC_JOB_PROCESSING     CRY_30_RH850ICUM_USE_SYNC_JOB_PROCESSING
#define CRY_30_RH850ICUM_KEYWRAPSYM_DATA_LENGTH                 (112u)
#define CRY_30_RH850ICUM_KEYWRAPSYM_OFFSET_M1                   (0u)
#define CRY_30_RH850ICUM_KEYWRAPSYM_OFFSET_M2                   (16u)
#define CRY_30_RH850ICUM_KEYWRAPSYM_OFFSET_M3                   (48u)
#define CRY_30_RH850ICUM_KEYWRAPSYM_OFFSET_M4                   (64u)
#define CRY_30_RH850ICUM_KEYWRAPSYM_OFFSET_M5                   (96u)

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

#if ( CRY_30_RH850ICUM_KEYWRAPSYM_USE_SYNC_JOB_PROCESSING == STD_OFF )
typedef struct
{
  P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) cfgPtr;
  P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) dataPtr;
  P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) dataLengthPtr;
  P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) keyPtr;
  P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR) wrappingKeyPtr;
} Cry_30_Rh850Icum_KeyWrapSym_BufferType;
#endif /* ( CRY_30_RH850ICUM_KEYWRAPSYM_USE_SYNC_JOB_PROCESSING == STD_OFF ) */

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 **********************************************************************************************************************/

#if ( CRY_30_RH850ICUM_KEYWRAPSYM_USE_SYNC_JOB_PROCESSING == STD_OFF )
# define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_30_RH850ICUM_LOCAL VAR(Cry_30_Rh850Icum_KeyWrapSym_BufferType, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_KeyWrapSym_Buffer; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
# define CRY_30_RH850ICUM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define CRY_30_RH850ICUM_START_SEC_VAR_NOINIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
CRY_30_RH850ICUM_LOCAL VAR(uint8, CRY_30_RH850ICUM_VAR_NOINIT) Cry_30_Rh850Icum_KeyWrapSym_Status; /* PRQA S 0779 */ /* MD_MSR_5.1_779 */
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
CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyWrapSymStartInternal( void );

CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyWrapSymUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                                            P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) dataPtr,
                                                                            P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) dataLengthPtr );

CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyWrapSymFinishInternal( void );


/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyWrapSymStartInternal()
 **********************************************************************************************************************/
/*! \brief      Common service start function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_KeyWrapSymStart()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyWrapSymStartInternal( void )
{
  Csm_ReturnType retVal;

  /* State and NULL_PTR check */
  if ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_IDLE )
  {
    retVal = CSM_E_OK;
    Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_KEYWRAPSYM_START;
  }
  else
  {
    retVal = CSM_E_BUSY;
  }

  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyWrapSymUpdateInternal()
 **********************************************************************************************************************/
/*! \brief      Common service update function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_KeyWrapSymUpdate()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyWrapSymUpdateInternal( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                                            P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) dataPtr,
                                                                            P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) dataLengthPtr )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  r_icumif_isd_t * p_ISD = &ISD;

  /* State and NULL_PTR check */
  if ( ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_KEYWRAPSYM_START )
    && ( cfgPtr != NULL_PTR )
    && ( dataPtr != NULL_PTR )
    && ( dataLengthPtr != NULL_PTR ) )
  {
    if ( *dataLengthPtr == CRY_30_RH850ICUM_KEYWRAPSYM_DATA_LENGTH )
    {

      p_ISD->service_id = SERVICE_03_AES_RAM_KEY_EXPORT_SHE;
      p_ISD->p_callbackfunc = 0;
      p_ISD->job_id = 0;
      p_ISD->prm.RAM_KEY_EXPORT_SHE.p_M1 = &dataPtr[CRY_30_RH850ICUM_KEYWRAPSYM_OFFSET_M1];
      p_ISD->prm.RAM_KEY_EXPORT_SHE.p_M2 = &dataPtr[CRY_30_RH850ICUM_KEYWRAPSYM_OFFSET_M2];
      p_ISD->prm.RAM_KEY_EXPORT_SHE.p_M3 = &dataPtr[CRY_30_RH850ICUM_KEYWRAPSYM_OFFSET_M3];
      p_ISD->prm.RAM_KEY_EXPORT_SHE.p_M4 = &dataPtr[CRY_30_RH850ICUM_KEYWRAPSYM_OFFSET_M4];
      p_ISD->prm.RAM_KEY_EXPORT_SHE.p_M5 = &dataPtr[CRY_30_RH850ICUM_KEYWRAPSYM_OFFSET_M5];

      /* trigger the security service */
      Cry_30_Rh850Icum_TriggerServiceAndWait(p_ISD);

      /* Write length of data to pointer */
      *dataLengthPtr = CRY_30_RH850ICUM_KEYWRAPSYM_DATA_LENGTH;

      if (p_ISD->service_result != SERV_OK)
      {
        retVal = CSM_E_NOT_OK;
      }
      else
      {
        retVal = CSM_E_OK;
      }
    }

    /* TODO: Check for errors */
  }
  if ( retVal == CSM_E_OK)
  {
    Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_KEYWRAPSYM_UPDATE;
  }
  return retVal;
}

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyWrapSymFinishInternal()
 **********************************************************************************************************************/
/*! \brief      Common service update function for synchronous and asynchronous behavior
 *  \see        Cry_30_Rh850Icum_KeyWrapSymFinish()
 **********************************************************************************************************************/
CRY_30_RH850ICUM_LOCAL FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyWrapSymFinishInternal( void )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

  /* State check */
  if ( Cry_30_Rh850Icum_ServiceState == CRY_30_RH850ICUM_SERVICE_KEYWRAPSYM_UPDATE )
  {
    retVal = CSM_E_OK;
  }

  Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_IDLE;

  return retVal;
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyWrapSymInit()
 **********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the PRNG of the SHE.
 *  \context       Function could be called from task level only.
 *  \reentrant     Non reentrant
 *  \synchronous   Sync. or async. (depending on configuration)
 *  \note          Called by Cry_Init().
 **********************************************************************************************************************/
FUNC( void, CRY_30_RH850ICUM_CODE)  Cry_30_Rh850Icum_KeyWrapSymInit( void )
{
#if ( CRY_30_RH850ICUM_KEYWRAPSYM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_KeyWrapSym_Status = CRY_30_RH850ICUM_STATE_IDLE;
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyWrapSymMainFunction()
 **********************************************************************************************************************/
/*! \brief      API to be called to process the requested services.
 *  \context    Function could be called from task level only
 *  \note       Scheduled by the CSM
**********************************************************************************************************************/
FUNC(void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_KeyWrapSymMainFunction( void )
{
#if ( CRY_30_RH850ICUM_KEYWRAPSYM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_ReturnType retVal;
  switch(Cry_30_Rh850Icum_KeyWrapSym_Status)
  {
    case CRY_30_RH850ICUM_STATE_START:
    {
      retVal = Cry_30_Rh850Icum_KeyWrapSymStartInternal( );

      Cry_30_Rh850Icum_KeyWrapSym_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_SymKeyWrapSymCallbackNotification( retVal );
      break;
    }
    case CRY_30_RH850ICUM_STATE_UPDATE:
    {
      retVal = Cry_30_Rh850Icum_KeyWrapSymUpdateInternal( Cry_30_Rh850Icum_KeyWrapSym_Buffer.cfgPtr,
                                                Cry_30_Rh850Icum_KeyWrapSym_Buffer.dataPtr,
                                                Cry_30_Rh850Icum_KeyWrapSym_Buffer.dataLengthPtr );

      Cry_30_Rh850Icum_KeyWrapSym_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_SymKeyWrapSymCallbackNotification( retVal );
      break;
    }
    case CRY_30_RH850ICUM_STATE_FINISH:
    {
      retVal = Cry_30_Rh850Icum_KeyWrapSymFinishInternal( );

      Cry_30_Rh850Icum_KeyWrapSym_Status = CRY_30_RH850ICUM_STATE_IDLE;

      Csm_SymKeyWrapSymCallbackNotification( retVal );
      Csm_SymKeyWrapSymServiceFinishNotification();
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
 * Csm_SymKeyWrapSymStart
**********************************************************************************************************************/
/*! \brief        This interface shall be used to initialize the symmetrical key wrapping.
 *  \param[in]    cfgId         Pointer to the configuration.
 *  \param[in]    keyPtr        Holds a pointer to the symmetric key to be wrapped.
 *  \param[in]    wrappingKeyPtr Holds a pointer to the key used for wrapping.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \return       CSM_E_BUSY    Request failed, service is still busy.
 *  \context      Called by application.
 **********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyWrapSymStart( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                         P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) keyPtr,
                                                         P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) wrappingKeyPtr )
{
  Csm_ReturnType retVal = CSM_E_NOT_OK;

#if ( CRY_30_RH850ICUM_KEYWRAPSYM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_KeyWrapSym_Status = CRY_30_RH850ICUM_STATE_START;
  retVal = CSM_E_OK;
#else
  retVal = Cry_30_Rh850Icum_KeyWrapSymStartInternal( );
#endif

  CRY_30_RH850ICUM_DUMMY_STATEMENT( cfgPtr );         /* PRQA S 3112 */ /* MD_MSR_14.2 */
  CRY_30_RH850ICUM_DUMMY_STATEMENT( keyPtr );         /* PRQA S 3112 */ /* MD_MSR_14.2 */
  CRY_30_RH850ICUM_DUMMY_STATEMENT( wrappingKeyPtr ); /* PRQA S 3112 */ /* MD_MSR_14.2 */
  return retVal;
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyWrapSymUpdate
**********************************************************************************************************************/
/*! \brief        This interface shall be used to retrieve the result of the key wrapping operation from the symmetrical key wrapping.
 *  \param[in]    cfgId         Pointer to the configuration.
 *  \param[in]    dataPtr       Holds a pointer to the memory location in which the length information is stored.
 *                              On calling this function this parameter shall contain the size of the buffer provided
 *                              by dataPtr. When the request has finished, the actual length of the computed value
 *                              shall be stored.
 *  \param[in]    dataLengthPtr Holds a pointer to the memory location which will hold the first chunk of the result
 *                              of the key wrapping. If the result does not fit into the given buffer, the caller
 *                              shall call the service again, until *dataLengthPtr is equal to zero,
 *                              indicating that the complete result has been retrieved.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \pre          Service was started.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyWrapSymUpdate( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr,
                                                          P2VAR( uint8, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) dataPtr,
                                                          P2VAR( uint32, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) dataLengthPtr )
{
#if ( CRY_30_RH850ICUM_KEYWRAPSYM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_KeyWrapSym_Buffer.cfgPtr = cfgPtr;
  Cry_30_Rh850Icum_KeyWrapSym_Buffer.dataPtr = dataPtr;
  Cry_30_Rh850Icum_KeyWrapSym_Buffer.dataLengthPtr = dataLengthPtr;
  Cry_30_Rh850Icum_KeyWrapSym_Status = CRY_30_RH850ICUM_STATE_UPDATE;
  return CSM_E_OK;
#else
  return Cry_30_Rh850Icum_KeyWrapSymUpdateInternal( cfgPtr, dataPtr, dataLengthPtr );
#endif
}


/**********************************************************************************************************************
 * Cry_30_Rh850Icum_KeyWrapSymFinish
**********************************************************************************************************************/
/*! \brief        This interface shall be used to finish the symmetrical key wrapping.
 *  \param[in]    cfgId         Pointer to the configuration.
 *  \return       CSM_E_OK      Request successful.
 *  \return       CSM_E_NOT_OK  Request failed.
 *  \pre          Service was started.
 *  \context      Function could be called from task level only.
 *  \note         Called by application.
**********************************************************************************************************************/
FUNC( Csm_ReturnType, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_KeyWrapSymFinish( P2CONST( void, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cfgPtr )
{
  CRY_30_RH850ICUM_DUMMY_STATEMENT( cfgPtr );         /* PRQA S 3112 */ /* MD_MSR_14.2 */
#if ( CRY_30_RH850ICUM_KEYWRAPSYM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Cry_30_Rh850Icum_KeyWrapSym_Status = CRY_30_RH850ICUM_STATE_FINISH;
  return CSM_E_OK;
#else
  return Cry_30_Rh850Icum_KeyWrapSymFinishInternal( );
#endif
}


#define CRY_30_RH850ICUM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* ( CRY_30_RH850ICUM_KEYWRAPSYMCONFIG == STD_ON ) */

/**********************************************************************************************************************
 *  END OF FILE: CRY_30_RH850ICUM_KEYWRAPSYM.c
 *********************************************************************************************************************/
