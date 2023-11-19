/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2016 by Vector Informatik GmbH.                                                All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Csm.c
 *        \brief  MICROSAR Crypto Service Manager (CSM)
 *
 *      \details  Implementation of the MICROSAR Crypto Service Manager (CSM)
 *
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

#define CSM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Csm.h"
#include "Csm_Cbk.h"

#if ( CSM_DEV_ERROR_REPORT == STD_ON )
# include "Det.h"
#endif

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

 /* Check the version of CSM header file */
#if (  (CSM_SW_MAJOR_VERSION != (2u)) \
    || (CSM_SW_MINOR_VERSION != (2u)) \
    || (CSM_SW_PATCH_VERSION != (3u)) )
  #error "Vendor specific version numbers of Csm.c and Csm.h are inconsistent"
#endif

#if (  (CSM_TYPES_MAJOR_VERSION != (2u)) \
    || (CSM_TYPES_MINOR_VERSION != (2u)) \
    || (CSM_TYPES_PATCH_VERSION != (3u)) )
  #error "Vendor specific version numbers of Csm.c and Csm_Types.h are inconsistent"
#endif

#if (  (CSM_CBK_MAJOR_VERSION != (2u)) \
    || (CSM_CBK_MINOR_VERSION != (2u)) \
    || (CSM_CBK_PATCH_VERSION != (3u)) )
  #error "Vendor specific version numbers of Csm.c and Csm_Cbk.h are inconsistent"
#endif

/* AUTOSAR version information check has to match definition in header file */
#if (  (CSM_AR_RELEASE_MAJOR_VERSION != (4u)) \
    || (CSM_AR_RELEASE_MINOR_VERSION != (0u)) \
    || (CSM_AR_RELEASE_REVISION_VERSION != (3u)) )
  #error "AUTOSAR Specification Version numbers of Csm.c and Csm.h are inconsistent!"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/*! Service idle state */
#define CSM_SERVICE_IDLE      (0u)
/*! Service active state */
#define CSM_SERVICE_ACTIVE    (1u)

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

#if !defined (CSM_LOCAL)
# define CSM_LOCAL static
#endif

/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/

#define CSM_START_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Initialization state of the module */
#if ( CSM_NUMBER_OF_SERVICES > 0u )
CSM_LOCAL VAR(uint8, CSM_VAR_ZERO_INIT) Csm_IsInitialized = CSM_UNINIT; /* PRQA S 3408 */ /* MD_CSM_DEBUG */
#endif

#define CSM_STOP_SEC_VAR_ZERO_INIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CSM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Initialization state of services */
#if ( CSM_NUMBER_OF_SERVICES > 0u )
CSM_LOCAL VAR(uint8, CSM_VAR_NOINIT) Csm_ServiceState[CSM_NUMBER_OF_SERVICES]; /* PRQA S 3408 */ /* MD_CSM_DEBUG */
#endif

#define CSM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define CSM_START_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Last used configuration ID */
#if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
# if ( CSM_NUMBER_OF_SERVICES > 0u )
CSM_LOCAL VAR(Csm_ConfigIdType, CSM_VAR_NOINIT) Csm_LastCfgId; /* PRQA S 3408 */ /* MD_CSM_DEBUG */
# endif
#endif

#define CSM_STOP_SEC_VAR_NOINIT_16BIT
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#define CSM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  Csm_InitMemory()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC(void, CSM_CODE) Csm_InitMemory( void )
{
  /* ----- Implementation ----------------------------------------------- */
#if ( CSM_NUMBER_OF_SERVICES > 0u )
  Csm_IsInitialized = CSM_UNINIT;
#endif
} /* Csm_InitMemory() */

/**********************************************************************************************************************
 *  Csm_Init()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC(void, CSM_CODE) Csm_Init( void )
{
#if ( CSM_NUMBER_OF_SERVICES > 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType cfgId;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Set all service states to idle */
  for ( cfgId = 0u; cfgId < CSM_NUMBER_OF_SERVICES; cfgId++ )
  {
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_02 */
  }

#endif
#if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
# if ( CSM_NUMBER_OF_SERVICES > 0 )
  /* #20 Set last configuration ID to zero for asynchronous mode */
  Csm_LastCfgId = 0u;
# endif
#endif

#if ( CSM_NUMBER_OF_SERVICES > 0u )
  /* #30 Set CSM initialization state to initialized */
  Csm_IsInitialized = CSM_INITIALIZED;
#endif
} /* Csm_Init() */

#if ( CSM_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  Csm_GetVersionInfo()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, CSM_APPL_VAR ) versioninfo )
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
# if ( CSM_DEV_ERROR_REPORT == STD_ON )
  if (versioninfo == NULL_PTR)
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  else
# endif
  {
    /* ----- Implementation ----------------------------------------------- */
    versioninfo->vendorID = (uint16)CSM_VENDOR_ID; /* SBSW_CSM_01 */
    versioninfo->moduleID = (uint8)CSM_MODULE_ID; /* SBSW_CSM_01 */
    versioninfo->sw_major_version = (uint8)CSM_SW_MAJOR_VERSION; /* SBSW_CSM_01 */
    versioninfo->sw_minor_version = (uint8)CSM_SW_MINOR_VERSION; /* SBSW_CSM_01 */
    versioninfo->sw_patch_version = (uint8)CSM_SW_PATCH_VERSION; /* SBSW_CSM_01 */
  }

  /* ----- Development Error Report --------------------------------------- */
# if ( CSM_DEV_ERROR_REPORT == STD_ON )
  if (errorId != CSM_E_NO_ERROR)
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)CSM_GETVERSIONINFO_ID, CSM_E_PARAM_PTR_INVALID );
  }
# else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_GetVersionInfo() */
#endif

#if ( CSM_USE_INTERRUPTION == STD_ON )
/**********************************************************************************************************************
 *  Csm_Interruption()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_Interruption( void )
{
  /* Function is not supported */
  return;
} /* Csm_Interruption() */
#endif

/**********************************************************************************************************************
 *  Csm_MainFunction()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_MainFunction( void )
{
#if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  /* ----- Implementation ----------------------------------------------- */
# if ( CSM_NUMBER_OF_HASH_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_HASH; Csm_LastCfgId < ( CSM_NUMBER_OF_HASH_CONFIGS + CSM_OFFSET_HASH ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_HashConfigs[Csm_LastCfgId-(CSM_OFFSET_HASH)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_MAC_GENERATE; Csm_LastCfgId < ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS + CSM_OFFSET_MAC_GENERATE ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_MacGenerateConfigs[Csm_LastCfgId-(CSM_OFFSET_MAC_GENERATE)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_MAC_VERIFY; Csm_LastCfgId < ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS + CSM_OFFSET_MAC_VERIFY ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_MacVerifyConfigs[Csm_LastCfgId-(CSM_OFFSET_MAC_VERIFY)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_RANDOM_SEED; Csm_LastCfgId < ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS + CSM_OFFSET_RANDOM_SEED ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_RandomSeedConfigs[Csm_LastCfgId-(CSM_OFFSET_RANDOM_SEED)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_RANDOM_GENERATE; Csm_LastCfgId < ( CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS + CSM_OFFSET_RANDOM_GENERATE ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_RandomGenerateConfigs[Csm_LastCfgId-(CSM_OFFSET_RANDOM_GENERATE)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_SYM_BLOCK_ENCRYPT; Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS + CSM_OFFSET_SYM_BLOCK_ENCRYPT ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_SymBlockEncryptConfigs[Csm_LastCfgId-(CSM_OFFSET_SYM_BLOCK_ENCRYPT)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_SYM_BLOCK_DECRYPT; Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS + CSM_OFFSET_SYM_BLOCK_DECRYPT ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_SymBlockDecryptConfigs[Csm_LastCfgId-(CSM_OFFSET_SYM_BLOCK_DECRYPT)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_SYM_ENCRYPT; Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS + CSM_OFFSET_SYM_ENCRYPT ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_SymEncryptConfigs[Csm_LastCfgId-(CSM_OFFSET_SYM_ENCRYPT)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_SYM_DECRYPT; Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS + CSM_OFFSET_SYM_DECRYPT ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_SymDecryptConfigs[Csm_LastCfgId-(CSM_OFFSET_SYM_DECRYPT)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_ASYM_ENCRYPT; Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS + CSM_OFFSET_ASYM_ENCRYPT ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_AsymEncryptConfigs[Csm_LastCfgId-(CSM_OFFSET_ASYM_ENCRYPT)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_ASYM_DECRYPT; Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS + CSM_OFFSET_ASYM_DECRYPT ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_AsymDecryptConfigs[Csm_LastCfgId-(CSM_OFFSET_ASYM_DECRYPT)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_SIGNATURE_GENERATE; Csm_LastCfgId < ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS + CSM_OFFSET_SIGNATURE_GENERATE ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_SignatureGenerateConfigs[Csm_LastCfgId-(CSM_OFFSET_SIGNATURE_GENERATE)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_SIGNATURE_VERIFY; Csm_LastCfgId < ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS + CSM_OFFSET_SIGNATURE_VERIFY ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_SignatureVerifyConfigs[Csm_LastCfgId-(CSM_OFFSET_SIGNATURE_VERIFY)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_CHECKSUM_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_CHECKSUM; Csm_LastCfgId < ( CSM_NUMBER_OF_CHECKSUM_CONFIGS + CSM_OFFSET_CHECKSUM ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_ChecksumConfigs[Csm_LastCfgId-(CSM_OFFSET_CHECKSUM)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_KEY_DERIVE; Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS + CSM_OFFSET_KEY_DERIVE ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_KeyDeriveConfigs[Csm_LastCfgId-(CSM_OFFSET_KEY_DERIVE)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_KEY_DERIVE_SYM_KEY; Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS + CSM_OFFSET_KEY_DERIVE_SYM_KEY ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_KeyDeriveSymKeyConfigs[Csm_LastCfgId-(CSM_OFFSET_KEY_DERIVE_SYM_KEY)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_KEY_EXCHANGE_CALC_PUB_VAL; Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_PUB_VAL ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_KeyExchangeCalcPubValConfigs[Csm_LastCfgId-(CSM_OFFSET_KEY_EXCHANGE_CALC_PUB_VAL)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET; Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_KeyExchangeCalcSecretConfigs[Csm_LastCfgId-(CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY; Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_KeyExchangeCalcSymKeyConfigs[Csm_LastCfgId-(CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_SYM_KEY_EXTRACT; Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS + CSM_OFFSET_SYM_KEY_EXTRACT ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_SymKeyExtractConfigs[Csm_LastCfgId-(CSM_OFFSET_SYM_KEY_EXTRACT)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_SYM_KEY_WRAP_SYM; Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS + CSM_OFFSET_SYM_KEY_WRAP_SYM ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_SymKeyWrapSymConfigs[Csm_LastCfgId-(CSM_OFFSET_SYM_KEY_WRAP_SYM)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_SYM_KEY_WRAP_ASYM; Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS + CSM_OFFSET_SYM_KEY_WRAP_ASYM ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_SymKeyWrapAsymConfigs[Csm_LastCfgId-(CSM_OFFSET_SYM_KEY_WRAP_ASYM)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT; Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS + CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_AsymPublicKeyExtractConfigs[Csm_LastCfgId-(CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT; Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_AsymPrivateKeyExtractConfigs[Csm_LastCfgId-(CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM; Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_AsymPrivateKeyWrapSymConfigs[Csm_LastCfgId-(CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif
# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS > 0u )
  for ( Csm_LastCfgId = CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM; Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM ); Csm_LastCfgId++ )
  {
    if ( Csm_ServiceState[Csm_LastCfgId] != CSM_SERVICE_IDLE )
    {
      Csm_AsymPrivateKeyWrapAsymConfigs[Csm_LastCfgId-(CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM)].PrimitiveMainFct(); /* SBSW_CSM_05 */
    }
  }
# endif

# if ( CSM_NUMBER_OF_SERVICES > 0u )
  Csm_LastCfgId = CSM_NUMBER_OF_SERVICES;
# endif
#endif
} /* PRQA S 6010 */ /* MD_MSR_STPTH */ /* PRQA S 6030 */ /* MD_MSR_STCYC */ /* Csm_MainFunction() */

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_HASH_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_HashStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_HashStart( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_HASH_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range against the provided configuration ID */
  if ( ! ( ( cfgId >= CSM_OFFSET_HASH ) && ( cfgId < ( CSM_NUMBER_OF_HASH_CONFIGS + CSM_OFFSET_HASH ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #30 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_HASH;

    /* #40 Call of configured function pointer */
    retVal = Csm_HashConfigs[localId].PrimitiveStartFct( Csm_HashConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #50 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_HASHSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_HashStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_HASH_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_HashUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_HashUpdate( Csm_ConfigIdType cfgId,
                                                 P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                 uint32 dataLength )
{
# if ( CSM_NUMBER_OF_HASH_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( dataPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_HASH ) && ( cfgId < ( CSM_NUMBER_OF_HASH_CONFIGS + CSM_OFFSET_HASH ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_HASH;
    /* #40 Call of configured function pointer */
    retVal = Csm_HashConfigs[localId].PrimitiveUpdateFct( Csm_HashConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_HASHUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_HashUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_HASH_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_HashFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 4 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_HashFinish( Csm_ConfigIdType cfgId,
                                                 P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
                                                 P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) resultLengthPtr,
                                                 boolean truncationIsAllowed )
{
# if ( CSM_NUMBER_OF_HASH_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( resultPtr == NULL_PTR ) || ( resultLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_HASH ) && ( cfgId < ( CSM_NUMBER_OF_HASH_CONFIGS + CSM_OFFSET_HASH ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_HASH;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_HashConfigs[localId].PrimitiveFinishFct( Csm_HashConfigs[localId].PrimitiveConfigPtr, resultPtr, resultLengthPtr, truncationIsAllowed ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_HASHFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( resultPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( resultLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( truncationIsAllowed ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_HashFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_HASH_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_HashCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_HashCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_HASH_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_HASH ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_HASH_CONFIGS + CSM_OFFSET_HASH ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_HashConfigs[Csm_LastCfgId - CSM_OFFSET_HASH].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_HashCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_HASH_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_HashServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_HashServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_HASH_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_HASH ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_HASH_CONFIGS + CSM_OFFSET_HASH ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_HashServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_MacGenerateStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_MacGenerateStart( Csm_ConfigIdType cfgId,
                                                       P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr )
{
# if ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( keyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_MAC_GENERATE ) && ( cfgId < ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS + CSM_OFFSET_MAC_GENERATE ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_MAC_GENERATE;

    /* #50 Call of configured function pointer */
    retVal = Csm_MacGenerateConfigs[localId].PrimitiveStartFct( Csm_MacGenerateConfigs[localId].PrimitiveConfigPtr, keyPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_MACGENERATESTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_MacGenerateStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_MacGenerateUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_MacGenerateUpdate( Csm_ConfigIdType cfgId,
                                                        P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                        uint32 dataLength )
{
# if ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( dataPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_MAC_GENERATE ) && ( cfgId < ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS + CSM_OFFSET_MAC_GENERATE ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_MAC_GENERATE;
    /* #40 Call of configured function pointer */
    retVal = Csm_MacGenerateConfigs[localId].PrimitiveUpdateFct( Csm_MacGenerateConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_MACGENERATEUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_MacGenerateUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_MacGenerateFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 4 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_MacGenerateFinish( Csm_ConfigIdType cfgId,
                                                        P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
                                                        P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) resultLengthPtr,
                                                        boolean truncationIsAllowed )
{
# if ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( resultPtr == NULL_PTR ) || ( resultLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_MAC_GENERATE ) && ( cfgId < ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS + CSM_OFFSET_MAC_GENERATE ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_MAC_GENERATE;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_MacGenerateConfigs[localId].PrimitiveFinishFct( Csm_MacGenerateConfigs[localId].PrimitiveConfigPtr, resultPtr, resultLengthPtr, truncationIsAllowed ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_MACGENERATEFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( resultPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( resultLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( truncationIsAllowed ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_MacGenerateFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_MacGenerateCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_MacGenerateCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_MAC_GENERATE ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS + CSM_OFFSET_MAC_GENERATE ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_MacGenerateConfigs[Csm_LastCfgId - CSM_OFFSET_MAC_GENERATE].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_MacGenerateCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_MacGenerateServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_MacGenerateServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_MAC_GENERATE ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS + CSM_OFFSET_MAC_GENERATE ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_MacGenerateServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_MacVerifyStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_MacVerifyStart( Csm_ConfigIdType cfgId,
                                                     P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr )
{
# if ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( keyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_MAC_VERIFY ) && ( cfgId < ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS + CSM_OFFSET_MAC_VERIFY ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_MAC_VERIFY;

    /* #50 Call of configured function pointer */
    retVal = Csm_MacVerifyConfigs[localId].PrimitiveStartFct( Csm_MacVerifyConfigs[localId].PrimitiveConfigPtr, keyPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_MACVERIFYSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_MacVerifyStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_MacVerifyUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_MacVerifyUpdate( Csm_ConfigIdType cfgId,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                      uint32 dataLength )
{
# if ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( dataPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_MAC_VERIFY ) && ( cfgId < ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS + CSM_OFFSET_MAC_VERIFY ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_MAC_VERIFY;
    /* #40 Call of configured function pointer */
    retVal = Csm_MacVerifyConfigs[localId].PrimitiveUpdateFct( Csm_MacVerifyConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_MACVERIFYUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_MacVerifyUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_MacVerifyFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 4 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_MacVerifyFinish( Csm_ConfigIdType cfgId,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) MacPtr,
                                                      uint32 MacLength,
                                                      P2VAR( Csm_VerifyResultType, AUTOMATIC, CSM_APPL_VAR ) resultPtr )
{
# if ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( MacPtr == NULL_PTR ) || ( resultPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_MAC_VERIFY ) && ( cfgId < ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS + CSM_OFFSET_MAC_VERIFY ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_MAC_VERIFY;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_MacVerifyConfigs[localId].PrimitiveFinishFct( Csm_MacVerifyConfigs[localId].PrimitiveConfigPtr, MacPtr, MacLength, resultPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_MACVERIFYFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( MacPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( MacLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( resultPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_MacVerifyFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_MacVerifyCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_MacVerifyCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_MAC_VERIFY ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS + CSM_OFFSET_MAC_VERIFY ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_MacVerifyConfigs[Csm_LastCfgId - CSM_OFFSET_MAC_VERIFY].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_MacVerifyCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_MacVerifyServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_MacVerifyServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_MAC_VERIFY ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS + CSM_OFFSET_MAC_VERIFY ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_MacVerifyServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_RandomSeedStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_RandomSeedStart( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range against the provided configuration ID */
  if ( ! ( ( cfgId >= CSM_OFFSET_RANDOM_SEED ) && ( cfgId < ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS + CSM_OFFSET_RANDOM_SEED ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #30 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_RANDOM_SEED;

    /* #40 Call of configured function pointer */
    retVal = Csm_RandomSeedConfigs[localId].PrimitiveStartFct( Csm_RandomSeedConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #50 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_RANDOMSEEDSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_RandomSeedStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_RandomSeedUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_RandomSeedUpdate( Csm_ConfigIdType cfgId,
                                                       P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) seedPtr,
                                                       uint32 seedLength )
{
# if ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( seedPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_RANDOM_SEED ) && ( cfgId < ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS + CSM_OFFSET_RANDOM_SEED ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_RANDOM_SEED;
    /* #40 Call of configured function pointer */
    retVal = Csm_RandomSeedConfigs[localId].PrimitiveUpdateFct( Csm_RandomSeedConfigs[localId].PrimitiveConfigPtr, seedPtr, seedLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_RANDOMSEEDUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( seedPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( seedLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_RandomSeedUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_RandomSeedFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_RandomSeedFinish( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range */
  if ( ! ( ( cfgId >= CSM_OFFSET_RANDOM_SEED ) && ( cfgId < ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS + CSM_OFFSET_RANDOM_SEED ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_RANDOM_SEED;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #30 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #40 Call of configured function pointer */
    retVal = Csm_RandomSeedConfigs[localId].PrimitiveFinishFct( Csm_RandomSeedConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_RANDOMSEEDFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_RandomSeedFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_RandomSeedCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_RandomSeedCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_RANDOM_SEED ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS + CSM_OFFSET_RANDOM_SEED ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_RandomSeedConfigs[Csm_LastCfgId - CSM_OFFSET_RANDOM_SEED].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_RandomSeedCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_RandomSeedServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_RandomSeedServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_RANDOM_SEED ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS + CSM_OFFSET_RANDOM_SEED ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_RandomSeedServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_RandomGenerate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_RandomGenerate( Csm_ConfigIdType cfgId,
                                                     P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
                                                     uint32 resultLength )
{
# if ( CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( resultPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_RANDOM_GENERATE ) && ( cfgId < ( CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS + CSM_OFFSET_RANDOM_GENERATE ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_RANDOM_GENERATE;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
    /* #50 Set service status to active if the asynchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
#  endif

    /* #60 Call of configured function pointer */
    retVal = Csm_RandomGenerateConfigs[localId].PrimitiveFct( Csm_RandomGenerateConfigs[localId].PrimitiveConfigPtr, resultPtr, resultLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_RANDOMGENERATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( resultPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( resultLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
}
#endif
#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_RandomGenerateCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_RandomGenerateCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_RANDOM_GENERATE ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS + CSM_OFFSET_RANDOM_GENERATE ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_RandomGenerateConfigs[Csm_LastCfgId - CSM_OFFSET_RANDOM_GENERATE].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_RandomGenerateCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_RandomGenerateServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_RandomGenerateServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_RANDOM_GENERATE ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS + CSM_OFFSET_RANDOM_GENERATE ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_RandomGenerateServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymBlockEncryptStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymBlockEncryptStart( Csm_ConfigIdType cfgId,
                                                           P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr )
{
# if ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( keyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_BLOCK_ENCRYPT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS + CSM_OFFSET_SYM_BLOCK_ENCRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_BLOCK_ENCRYPT;

    /* #50 Call of configured function pointer */
    retVal = Csm_SymBlockEncryptConfigs[localId].PrimitiveStartFct( Csm_SymBlockEncryptConfigs[localId].PrimitiveConfigPtr, keyPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMBLOCKENCRYPTSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_SymBlockEncryptStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymBlockEncryptUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 5 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymBlockEncryptUpdate( Csm_ConfigIdType cfgId,
                                                            P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                            uint32 plainTextLength,
                                                            P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                            P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr )
{
# if ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( plainTextPtr == NULL_PTR ) || ( cipherTextPtr == NULL_PTR ) || ( cipherTextLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_BLOCK_ENCRYPT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS + CSM_OFFSET_SYM_BLOCK_ENCRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_BLOCK_ENCRYPT;
    /* #40 Call of configured function pointer */
    retVal = Csm_SymBlockEncryptConfigs[localId].PrimitiveUpdateFct( Csm_SymBlockEncryptConfigs[localId].PrimitiveConfigPtr, plainTextPtr, plainTextLength, cipherTextPtr, cipherTextLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMBLOCKENCRYPTUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymBlockEncryptUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymBlockEncryptFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymBlockEncryptFinish( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range */
  if ( ! ( ( cfgId >= CSM_OFFSET_SYM_BLOCK_ENCRYPT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS + CSM_OFFSET_SYM_BLOCK_ENCRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_BLOCK_ENCRYPT;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #30 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #40 Call of configured function pointer */
    retVal = Csm_SymBlockEncryptConfigs[localId].PrimitiveFinishFct( Csm_SymBlockEncryptConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMBLOCKENCRYPTFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymBlockEncryptFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymBlockEncryptCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymBlockEncryptCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_BLOCK_ENCRYPT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS + CSM_OFFSET_SYM_BLOCK_ENCRYPT ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_SymBlockEncryptConfigs[Csm_LastCfgId - CSM_OFFSET_SYM_BLOCK_ENCRYPT].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_SymBlockEncryptCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymBlockEncryptServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymBlockEncryptServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_BLOCK_ENCRYPT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS + CSM_OFFSET_SYM_BLOCK_ENCRYPT ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_SymBlockEncryptServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymBlockDecryptStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymBlockDecryptStart( Csm_ConfigIdType cfgId,
                                                           P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr )
{
# if ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( keyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_BLOCK_DECRYPT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS + CSM_OFFSET_SYM_BLOCK_DECRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_BLOCK_DECRYPT;

    /* #50 Call of configured function pointer */
    retVal = Csm_SymBlockDecryptConfigs[localId].PrimitiveStartFct( Csm_SymBlockDecryptConfigs[localId].PrimitiveConfigPtr, keyPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMBLOCKDECRYPTSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_SymBlockDecryptStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymBlockDecryptUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 5 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymBlockDecryptUpdate( Csm_ConfigIdType cfgId,
                                                            P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                            uint32 cipherTextLength,
                                                            P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                            P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr )
{
# if ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( cipherTextPtr == NULL_PTR ) || ( plainTextPtr == NULL_PTR ) || ( plainTextLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_BLOCK_DECRYPT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS + CSM_OFFSET_SYM_BLOCK_DECRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_BLOCK_DECRYPT;
    /* #40 Call of configured function pointer */
    retVal = Csm_SymBlockDecryptConfigs[localId].PrimitiveUpdateFct( Csm_SymBlockDecryptConfigs[localId].PrimitiveConfigPtr, cipherTextPtr, cipherTextLength, plainTextPtr, plainTextLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMBLOCKDECRYPTUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymBlockDecryptUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymBlockDecryptFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymBlockDecryptFinish( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range */
  if ( ! ( ( cfgId >= CSM_OFFSET_SYM_BLOCK_DECRYPT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS + CSM_OFFSET_SYM_BLOCK_DECRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_BLOCK_DECRYPT;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #30 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #40 Call of configured function pointer */
    retVal = Csm_SymBlockDecryptConfigs[localId].PrimitiveFinishFct( Csm_SymBlockDecryptConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMBLOCKDECRYPTFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymBlockDecryptFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymBlockDecryptCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymBlockDecryptCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_BLOCK_DECRYPT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS + CSM_OFFSET_SYM_BLOCK_DECRYPT ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_SymBlockDecryptConfigs[Csm_LastCfgId - CSM_OFFSET_SYM_BLOCK_DECRYPT].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_SymBlockDecryptCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymBlockDecryptServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymBlockDecryptServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_BLOCK_DECRYPT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS + CSM_OFFSET_SYM_BLOCK_DECRYPT ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_SymBlockDecryptServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymEncryptStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymEncryptStart( Csm_ConfigIdType cfgId,
                                                      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) InitVectorPtr,
                                                      uint32 InitVectorLength )
{
# if ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( keyPtr == NULL_PTR ) || ( InitVectorPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_ENCRYPT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS + CSM_OFFSET_SYM_ENCRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_ENCRYPT;

    /* #50 Call of configured function pointer */
    retVal = Csm_SymEncryptConfigs[localId].PrimitiveStartFct( Csm_SymEncryptConfigs[localId].PrimitiveConfigPtr, keyPtr, InitVectorPtr, InitVectorLength ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMENCRYPTSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( InitVectorPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( InitVectorLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_SymEncryptStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymEncryptUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 5 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymEncryptUpdate( Csm_ConfigIdType cfgId,
                                                       P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                       uint32 plainTextLength,
                                                       P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                       P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr )
{
# if ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( plainTextPtr == NULL_PTR ) || ( cipherTextPtr == NULL_PTR ) || ( cipherTextLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_ENCRYPT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS + CSM_OFFSET_SYM_ENCRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_ENCRYPT;
    /* #40 Call of configured function pointer */
    retVal = Csm_SymEncryptConfigs[localId].PrimitiveUpdateFct( Csm_SymEncryptConfigs[localId].PrimitiveConfigPtr, plainTextPtr, plainTextLength, cipherTextPtr, cipherTextLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMENCRYPTUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymEncryptUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymEncryptFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymEncryptFinish( Csm_ConfigIdType cfgId,
                                                       P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                       P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr )
{
# if ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( cipherTextPtr == NULL_PTR ) || ( cipherTextLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_ENCRYPT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS + CSM_OFFSET_SYM_ENCRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_ENCRYPT;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_SymEncryptConfigs[localId].PrimitiveFinishFct( Csm_SymEncryptConfigs[localId].PrimitiveConfigPtr, cipherTextPtr, cipherTextLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMENCRYPTFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymEncryptFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymEncryptCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymEncryptCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_ENCRYPT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS + CSM_OFFSET_SYM_ENCRYPT ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_SymEncryptConfigs[Csm_LastCfgId - CSM_OFFSET_SYM_ENCRYPT].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_SymEncryptCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymEncryptServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymEncryptServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_ENCRYPT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS + CSM_OFFSET_SYM_ENCRYPT ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_SymEncryptServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymDecryptStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymDecryptStart( Csm_ConfigIdType cfgId,
                                                      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) InitVectorPtr,
                                                      uint32 InitVectorLength )
{
# if ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( keyPtr == NULL_PTR ) || ( InitVectorPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_DECRYPT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS + CSM_OFFSET_SYM_DECRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_DECRYPT;

    /* #50 Call of configured function pointer */
    retVal = Csm_SymDecryptConfigs[localId].PrimitiveStartFct( Csm_SymDecryptConfigs[localId].PrimitiveConfigPtr, keyPtr, InitVectorPtr, InitVectorLength ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMDECRYPTSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( InitVectorPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( InitVectorLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_SymDecryptStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymDecryptUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 5 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymDecryptUpdate( Csm_ConfigIdType cfgId,
                                                       P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                       uint32 cipherTextLength,
                                                       P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                       P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr )
{
# if ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( cipherTextPtr == NULL_PTR ) || ( plainTextPtr == NULL_PTR ) || ( plainTextLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_DECRYPT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS + CSM_OFFSET_SYM_DECRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_DECRYPT;
    /* #40 Call of configured function pointer */
    retVal = Csm_SymDecryptConfigs[localId].PrimitiveUpdateFct( Csm_SymDecryptConfigs[localId].PrimitiveConfigPtr, cipherTextPtr, cipherTextLength, plainTextPtr, plainTextLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMDECRYPTUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymDecryptUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymDecryptFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymDecryptFinish( Csm_ConfigIdType cfgId,
                                                       P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                       P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr )
{
# if ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( plainTextPtr == NULL_PTR ) || ( plainTextLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_DECRYPT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS + CSM_OFFSET_SYM_DECRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_DECRYPT;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_SymDecryptConfigs[localId].PrimitiveFinishFct( Csm_SymDecryptConfigs[localId].PrimitiveConfigPtr, plainTextPtr, plainTextLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMDECRYPTFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymDecryptFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymDecryptCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymDecryptCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_DECRYPT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS + CSM_OFFSET_SYM_DECRYPT ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_SymDecryptConfigs[Csm_LastCfgId - CSM_OFFSET_SYM_DECRYPT].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_SymDecryptCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymDecryptServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymDecryptServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_DECRYPT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS + CSM_OFFSET_SYM_DECRYPT ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_SymDecryptServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymEncryptStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymEncryptStart( Csm_ConfigIdType cfgId,
                                                       P2CONST( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr )
{
# if ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( keyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_ENCRYPT ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS + CSM_OFFSET_ASYM_ENCRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_ENCRYPT;

    /* #50 Call of configured function pointer */
    retVal = Csm_AsymEncryptConfigs[localId].PrimitiveStartFct( Csm_AsymEncryptConfigs[localId].PrimitiveConfigPtr, keyPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMENCRYPTSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_AsymEncryptStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymEncryptUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 5 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymEncryptUpdate( Csm_ConfigIdType cfgId,
                                                        P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                        uint32 plainTextLength,
                                                        P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                        P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr )
{
# if ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( plainTextPtr == NULL_PTR ) || ( cipherTextPtr == NULL_PTR ) || ( cipherTextLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_ENCRYPT ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS + CSM_OFFSET_ASYM_ENCRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_ENCRYPT;
    /* #40 Call of configured function pointer */
    retVal = Csm_AsymEncryptConfigs[localId].PrimitiveUpdateFct( Csm_AsymEncryptConfigs[localId].PrimitiveConfigPtr, plainTextPtr, plainTextLength, cipherTextPtr, cipherTextLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMENCRYPTUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_AsymEncryptUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymEncryptFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymEncryptFinish( Csm_ConfigIdType cfgId,
                                                        P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                        P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr )
{
# if ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( cipherTextPtr == NULL_PTR ) || ( cipherTextLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_ENCRYPT ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS + CSM_OFFSET_ASYM_ENCRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_ENCRYPT;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_AsymEncryptConfigs[localId].PrimitiveFinishFct( Csm_AsymEncryptConfigs[localId].PrimitiveConfigPtr, cipherTextPtr, cipherTextLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMENCRYPTFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_AsymEncryptFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymEncryptCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_AsymEncryptCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_ASYM_ENCRYPT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS + CSM_OFFSET_ASYM_ENCRYPT ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_AsymEncryptConfigs[Csm_LastCfgId - CSM_OFFSET_ASYM_ENCRYPT].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_AsymEncryptCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymEncryptServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_AsymEncryptServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_ASYM_ENCRYPT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS + CSM_OFFSET_ASYM_ENCRYPT ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_AsymEncryptServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymDecryptStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymDecryptStart( Csm_ConfigIdType cfgId,
                                                       P2CONST( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr )
{
# if ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( keyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_DECRYPT ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS + CSM_OFFSET_ASYM_DECRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_DECRYPT;

    /* #50 Call of configured function pointer */
    retVal = Csm_AsymDecryptConfigs[localId].PrimitiveStartFct( Csm_AsymDecryptConfigs[localId].PrimitiveConfigPtr, keyPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMDECRYPTSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_AsymDecryptStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymDecryptUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 5 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymDecryptUpdate( Csm_ConfigIdType cfgId,
                                                        P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                        uint32 cipherTextLength,
                                                        P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                        P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr )
{
# if ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( cipherTextPtr == NULL_PTR ) || ( plainTextPtr == NULL_PTR ) || ( plainTextLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_DECRYPT ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS + CSM_OFFSET_ASYM_DECRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_DECRYPT;
    /* #40 Call of configured function pointer */
    retVal = Csm_AsymDecryptConfigs[localId].PrimitiveUpdateFct( Csm_AsymDecryptConfigs[localId].PrimitiveConfigPtr, cipherTextPtr, cipherTextLength, plainTextPtr, plainTextLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMDECRYPTUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( cipherTextLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_AsymDecryptUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymDecryptFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymDecryptFinish( Csm_ConfigIdType cfgId,
                                                        P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                        P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr )
{
# if ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( plainTextPtr == NULL_PTR ) || ( plainTextLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_DECRYPT ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS + CSM_OFFSET_ASYM_DECRYPT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_DECRYPT;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_AsymDecryptConfigs[localId].PrimitiveFinishFct( Csm_AsymDecryptConfigs[localId].PrimitiveConfigPtr, plainTextPtr, plainTextLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMDECRYPTFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( plainTextLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_AsymDecryptFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymDecryptCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_AsymDecryptCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_ASYM_DECRYPT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS + CSM_OFFSET_ASYM_DECRYPT ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_AsymDecryptConfigs[Csm_LastCfgId - CSM_OFFSET_ASYM_DECRYPT].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_AsymDecryptCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymDecryptServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_AsymDecryptServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_ASYM_DECRYPT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS + CSM_OFFSET_ASYM_DECRYPT ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_AsymDecryptServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SignatureGenerateStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SignatureGenerateStart( Csm_ConfigIdType cfgId,
                                                             P2CONST( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr )
{
# if ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( keyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SIGNATURE_GENERATE ) && ( cfgId < ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS + CSM_OFFSET_SIGNATURE_GENERATE ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SIGNATURE_GENERATE;

    /* #50 Call of configured function pointer */
    retVal = Csm_SignatureGenerateConfigs[localId].PrimitiveStartFct( Csm_SignatureGenerateConfigs[localId].PrimitiveConfigPtr, keyPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SIGNATUREGENERATESTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_SignatureGenerateStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SignatureGenerateUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SignatureGenerateUpdate( Csm_ConfigIdType cfgId,
                                                              P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                              uint32 dataLength )
{
# if ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( dataPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SIGNATURE_GENERATE ) && ( cfgId < ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS + CSM_OFFSET_SIGNATURE_GENERATE ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SIGNATURE_GENERATE;
    /* #40 Call of configured function pointer */
    retVal = Csm_SignatureGenerateConfigs[localId].PrimitiveUpdateFct( Csm_SignatureGenerateConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SIGNATUREGENERATEUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SignatureGenerateUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SignatureGenerateFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SignatureGenerateFinish( Csm_ConfigIdType cfgId,
                                                              P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
                                                              P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) resultLengthPtr )
{
# if ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( resultPtr == NULL_PTR ) || ( resultLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SIGNATURE_GENERATE ) && ( cfgId < ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS + CSM_OFFSET_SIGNATURE_GENERATE ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SIGNATURE_GENERATE;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_SignatureGenerateConfigs[localId].PrimitiveFinishFct( Csm_SignatureGenerateConfigs[localId].PrimitiveConfigPtr, resultPtr, resultLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SIGNATUREGENERATEFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( resultPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( resultLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SignatureGenerateFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SignatureGenerateCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SignatureGenerateCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SIGNATURE_GENERATE ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS + CSM_OFFSET_SIGNATURE_GENERATE ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_SignatureGenerateConfigs[Csm_LastCfgId - CSM_OFFSET_SIGNATURE_GENERATE].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_SignatureGenerateCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SignatureGenerateServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SignatureGenerateServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SIGNATURE_GENERATE ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS + CSM_OFFSET_SIGNATURE_GENERATE ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_SignatureGenerateServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SignatureVerifyStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SignatureVerifyStart( Csm_ConfigIdType cfgId,
                                                           P2CONST( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr )
{
# if ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( keyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SIGNATURE_VERIFY ) && ( cfgId < ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS + CSM_OFFSET_SIGNATURE_VERIFY ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SIGNATURE_VERIFY;

    /* #50 Call of configured function pointer */
    retVal = Csm_SignatureVerifyConfigs[localId].PrimitiveStartFct( Csm_SignatureVerifyConfigs[localId].PrimitiveConfigPtr, keyPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SIGNATUREVERIFYSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_SignatureVerifyStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SignatureVerifyUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SignatureVerifyUpdate( Csm_ConfigIdType cfgId,
                                                            P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                            uint32 dataLength )
{
# if ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( dataPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SIGNATURE_VERIFY ) && ( cfgId < ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS + CSM_OFFSET_SIGNATURE_VERIFY ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SIGNATURE_VERIFY;
    /* #40 Call of configured function pointer */
    retVal = Csm_SignatureVerifyConfigs[localId].PrimitiveUpdateFct( Csm_SignatureVerifyConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SIGNATUREVERIFYUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SignatureVerifyUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SignatureVerifyFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 4 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SignatureVerifyFinish( Csm_ConfigIdType cfgId,
                                                            P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) signaturePtr,
                                                            uint32 signatureLength,
                                                            P2VAR( Csm_VerifyResultType, AUTOMATIC, CSM_APPL_VAR ) resultPtr )
{
# if ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( signaturePtr == NULL_PTR ) || ( resultPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SIGNATURE_VERIFY ) && ( cfgId < ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS + CSM_OFFSET_SIGNATURE_VERIFY ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SIGNATURE_VERIFY;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_SignatureVerifyConfigs[localId].PrimitiveFinishFct( Csm_SignatureVerifyConfigs[localId].PrimitiveConfigPtr, signaturePtr, signatureLength, resultPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SIGNATUREVERIFYFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( signaturePtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( signatureLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( resultPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SignatureVerifyFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SignatureVerifyCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SignatureVerifyCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SIGNATURE_VERIFY ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS + CSM_OFFSET_SIGNATURE_VERIFY ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_SignatureVerifyConfigs[Csm_LastCfgId - CSM_OFFSET_SIGNATURE_VERIFY].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_SignatureVerifyCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SignatureVerifyServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SignatureVerifyServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SIGNATURE_VERIFY ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS + CSM_OFFSET_SIGNATURE_VERIFY ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_SignatureVerifyServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_CHECKSUM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_ChecksumStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_ChecksumStart( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_CHECKSUM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range against the provided configuration ID */
  if ( ! ( ( cfgId >= CSM_OFFSET_CHECKSUM ) && ( cfgId < ( CSM_NUMBER_OF_CHECKSUM_CONFIGS + CSM_OFFSET_CHECKSUM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #30 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_CHECKSUM;

    /* #40 Call of configured function pointer */
    retVal = Csm_ChecksumConfigs[localId].PrimitiveStartFct( Csm_ChecksumConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #50 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_CHECKSUMSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_ChecksumStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_CHECKSUM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_ChecksumUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_ChecksumUpdate( Csm_ConfigIdType cfgId,
                                                     P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                     uint32 dataLength )
{
# if ( CSM_NUMBER_OF_CHECKSUM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( dataPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_CHECKSUM ) && ( cfgId < ( CSM_NUMBER_OF_CHECKSUM_CONFIGS + CSM_OFFSET_CHECKSUM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_CHECKSUM;
    /* #40 Call of configured function pointer */
    retVal = Csm_ChecksumConfigs[localId].PrimitiveUpdateFct( Csm_ChecksumConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_CHECKSUMUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_ChecksumUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_CHECKSUM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_ChecksumFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 4 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_ChecksumFinish( Csm_ConfigIdType cfgId,
                                                     P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
                                                     P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) resultLengthPtr,
                                                     boolean truncationIsAllowed )
{
# if ( CSM_NUMBER_OF_CHECKSUM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( resultPtr == NULL_PTR ) || ( resultLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_CHECKSUM ) && ( cfgId < ( CSM_NUMBER_OF_CHECKSUM_CONFIGS + CSM_OFFSET_CHECKSUM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_CHECKSUM;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_ChecksumConfigs[localId].PrimitiveFinishFct( Csm_ChecksumConfigs[localId].PrimitiveConfigPtr, resultPtr, resultLengthPtr, truncationIsAllowed ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_CHECKSUMFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( resultPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( resultLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( truncationIsAllowed ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_ChecksumFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_CHECKSUM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_ChecksumCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_ChecksumCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_CHECKSUM_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_CHECKSUM ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_CHECKSUM_CONFIGS + CSM_OFFSET_CHECKSUM ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_ChecksumConfigs[Csm_LastCfgId - CSM_OFFSET_CHECKSUM].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_ChecksumCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_CHECKSUM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_ChecksumServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_ChecksumServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_CHECKSUM_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_CHECKSUM ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_CHECKSUM_CONFIGS + CSM_OFFSET_CHECKSUM ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_ChecksumServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyDeriveStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyDeriveStart( Csm_ConfigIdType cfgId,
                                                     uint32 keyLength,
                                                     uint32 iterations )
{
# if ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range against the provided configuration ID */
  if ( ! ( ( cfgId >= CSM_OFFSET_KEY_DERIVE ) && ( cfgId < ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS + CSM_OFFSET_KEY_DERIVE ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #30 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_KEY_DERIVE;

    /* #40 Call of configured function pointer */
    retVal = Csm_KeyDeriveConfigs[localId].PrimitiveStartFct( Csm_KeyDeriveConfigs[localId].PrimitiveConfigPtr, keyLength, iterations ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #50 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYDERIVESTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( iterations ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_KeyDeriveStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyDeriveUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyDeriveUpdate( Csm_ConfigIdType cfgId,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) passwordPtr,
                                                      uint32 passwordLength,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) saltPtr,
                                                      uint32 saltLength )
{
# if ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( passwordPtr == NULL_PTR ) || ( saltPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_KEY_DERIVE ) && ( cfgId < ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS + CSM_OFFSET_KEY_DERIVE ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_KEY_DERIVE;
    /* #40 Call of configured function pointer */
    retVal = Csm_KeyDeriveConfigs[localId].PrimitiveUpdateFct( Csm_KeyDeriveConfigs[localId].PrimitiveConfigPtr, passwordPtr, passwordLength, saltPtr, saltLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYDERIVEUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( passwordPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( passwordLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( saltPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( saltLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_KeyDeriveUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyDeriveFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 2 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyDeriveFinish( Csm_ConfigIdType cfgId,
                                                      P2VAR( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr )
{
# if ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( keyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_KEY_DERIVE ) && ( cfgId < ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS + CSM_OFFSET_KEY_DERIVE ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_KEY_DERIVE;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_KeyDeriveConfigs[localId].PrimitiveFinishFct( Csm_KeyDeriveConfigs[localId].PrimitiveConfigPtr, keyPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYDERIVEFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_KeyDeriveFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyDeriveCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_KeyDeriveCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_KEY_DERIVE ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS + CSM_OFFSET_KEY_DERIVE ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_KeyDeriveConfigs[Csm_LastCfgId - CSM_OFFSET_KEY_DERIVE].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_KeyDeriveCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyDeriveServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_KeyDeriveServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_KEY_DERIVE ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS + CSM_OFFSET_KEY_DERIVE ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_KeyDeriveServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyDeriveSymKey()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 5 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyDeriveSymKey( Csm_ConfigIdType cfgId,
                                                      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) baseKeyPtr,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) customisationValPtr,
                                                      uint32 customisationValLength,
                                                      P2VAR( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) derivedKeyPtr )
{
# if ( CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( baseKeyPtr == NULL_PTR ) || ( customisationValPtr == NULL_PTR ) || ( derivedKeyPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_KEY_DERIVE_SYM_KEY ) && ( cfgId < ( CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS + CSM_OFFSET_KEY_DERIVE_SYM_KEY ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_KEY_DERIVE_SYM_KEY;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
    /* #50 Set service status to active if the asynchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
#  endif

    /* #60 Call of configured function pointer */
    retVal = Csm_KeyDeriveSymKeyConfigs[localId].PrimitiveFct( Csm_KeyDeriveSymKeyConfigs[localId].PrimitiveConfigPtr, baseKeyPtr, customisationValPtr, customisationValLength, derivedKeyPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYDERIVESYMKEY_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( baseKeyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( customisationValPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( customisationValLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( derivedKeyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
}
#endif
#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyDeriveSymKeyCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_KeyDeriveSymKeyCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_KEY_DERIVE_SYM_KEY ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS + CSM_OFFSET_KEY_DERIVE_SYM_KEY ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_KeyDeriveSymKeyConfigs[Csm_LastCfgId - CSM_OFFSET_KEY_DERIVE_SYM_KEY].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_KeyDeriveSymKeyCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyDeriveSymKeyServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_KeyDeriveSymKeyServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_KEY_DERIVE_SYM_KEY ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS + CSM_OFFSET_KEY_DERIVE_SYM_KEY ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_KeyDeriveSymKeyServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcPubVal()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 5 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcPubVal( Csm_ConfigIdType cfgId,
                                                            P2CONST( Csm_KeyExchangeBaseType, AUTOMATIC, CSM_APPL_VAR ) basePtr,
                                                            P2CONST( Csm_KeyExchangePrivateType, AUTOMATIC, CSM_APPL_VAR ) privateValuePtr,
                                                            P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) publicValuePtr,
                                                            P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) publicValueLengthPtr )
{
# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( basePtr == NULL_PTR ) || ( privateValuePtr == NULL_PTR ) || ( publicValuePtr == NULL_PTR ) || ( publicValueLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_PUB_VAL ) && ( cfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_PUB_VAL ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_KEY_EXCHANGE_CALC_PUB_VAL;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
    /* #50 Set service status to active if the asynchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
#  endif

    /* #60 Call of configured function pointer */
    retVal = Csm_KeyExchangeCalcPubValConfigs[localId].PrimitiveFct( Csm_KeyExchangeCalcPubValConfigs[localId].PrimitiveConfigPtr, basePtr, privateValuePtr, publicValuePtr, publicValueLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYEXCHANGECALCPUBVAL_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( basePtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( privateValuePtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( publicValuePtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( publicValueLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
}
#endif
#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcPubValCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_KeyExchangeCalcPubValCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_PUB_VAL ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_PUB_VAL ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_KeyExchangeCalcPubValConfigs[Csm_LastCfgId - CSM_OFFSET_KEY_EXCHANGE_CALC_PUB_VAL].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_KeyExchangeCalcPubValCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcPubValServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_KeyExchangeCalcPubValServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_PUB_VAL ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_PUB_VAL ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_KeyExchangeCalcPubValServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSecretStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcSecretStart( Csm_ConfigIdType cfgId,
                                                                 P2CONST( Csm_KeyExchangeBaseType, AUTOMATIC, CSM_APPL_VAR ) basePtr,
                                                                 P2CONST( Csm_KeyExchangePrivateType, AUTOMATIC, CSM_APPL_VAR ) privateValuePtr )
{
# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( basePtr == NULL_PTR ) || ( privateValuePtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET ) && ( cfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET;

    /* #50 Call of configured function pointer */
    retVal = Csm_KeyExchangeCalcSecretConfigs[localId].PrimitiveStartFct( Csm_KeyExchangeCalcSecretConfigs[localId].PrimitiveConfigPtr, basePtr, privateValuePtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYEXCHANGECALCSECRETSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( basePtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( privateValuePtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_KeyExchangeCalcSecretStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSecretUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcSecretUpdate( Csm_ConfigIdType cfgId,
                                                                  P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) partnerPublicValuePtr,
                                                                  uint32 partnerPublicValueLength )
{
# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( partnerPublicValuePtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET ) && ( cfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET;
    /* #40 Call of configured function pointer */
    retVal = Csm_KeyExchangeCalcSecretConfigs[localId].PrimitiveUpdateFct( Csm_KeyExchangeCalcSecretConfigs[localId].PrimitiveConfigPtr, partnerPublicValuePtr, partnerPublicValueLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYEXCHANGECALCSECRETUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( partnerPublicValuePtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( partnerPublicValueLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_KeyExchangeCalcSecretUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSecretFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 4 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcSecretFinish( Csm_ConfigIdType cfgId,
                                                                  P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) sharedSecretPtr,
                                                                  P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) sharedSecretLengthPtr,
                                                                  boolean truncationIsAllowed )
{
# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( sharedSecretPtr == NULL_PTR ) || ( sharedSecretLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET ) && ( cfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_KeyExchangeCalcSecretConfigs[localId].PrimitiveFinishFct( Csm_KeyExchangeCalcSecretConfigs[localId].PrimitiveConfigPtr, sharedSecretPtr, sharedSecretLengthPtr, truncationIsAllowed ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYEXCHANGECALCSECRETFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( sharedSecretPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( sharedSecretLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( truncationIsAllowed ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_KeyExchangeCalcSecretFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSecretCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_KeyExchangeCalcSecretCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_KeyExchangeCalcSecretConfigs[Csm_LastCfgId - CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_KeyExchangeCalcSecretCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSecretServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_KeyExchangeCalcSecretServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_SECRET ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_KeyExchangeCalcSecretServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSymKeyStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcSymKeyStart( Csm_ConfigIdType cfgId,
                                                                 P2CONST( Csm_KeyExchangeBaseType, AUTOMATIC, CSM_APPL_VAR ) basePtr,
                                                                 P2CONST( Csm_KeyExchangePrivateType, AUTOMATIC, CSM_APPL_VAR ) privateValuePtr )
{
# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( basePtr == NULL_PTR ) || ( privateValuePtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY ) && ( cfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY;

    /* #50 Call of configured function pointer */
    retVal = Csm_KeyExchangeCalcSymKeyConfigs[localId].PrimitiveStartFct( Csm_KeyExchangeCalcSymKeyConfigs[localId].PrimitiveConfigPtr, basePtr, privateValuePtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYEXCHANGECALCSYMKEYSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( basePtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( privateValuePtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_KeyExchangeCalcSymKeyStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSymKeyUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcSymKeyUpdate( Csm_ConfigIdType cfgId,
                                                                  P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) partnerPublicValuePtr,
                                                                  uint32 partnerPublicValueLength )
{
# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( partnerPublicValuePtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY ) && ( cfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY;
    /* #40 Call of configured function pointer */
    retVal = Csm_KeyExchangeCalcSymKeyConfigs[localId].PrimitiveUpdateFct( Csm_KeyExchangeCalcSymKeyConfigs[localId].PrimitiveConfigPtr, partnerPublicValuePtr, partnerPublicValueLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYEXCHANGECALCSYMKEYUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( partnerPublicValuePtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( partnerPublicValueLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_KeyExchangeCalcSymKeyUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSymKeyFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 2 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcSymKeyFinish( Csm_ConfigIdType cfgId,
                                                                  P2VAR( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) sharedKeyPtr )
{
# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( sharedKeyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY ) && ( cfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_KeyExchangeCalcSymKeyConfigs[localId].PrimitiveFinishFct( Csm_KeyExchangeCalcSymKeyConfigs[localId].PrimitiveConfigPtr, sharedKeyPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_KEYEXCHANGECALCSYMKEYFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( sharedKeyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_KeyExchangeCalcSymKeyFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSymKeyCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_KeyExchangeCalcSymKeyCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_KeyExchangeCalcSymKeyConfigs[Csm_LastCfgId - CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_KeyExchangeCalcSymKeyCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSymKeyServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_KeyExchangeCalcSymKeyServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS + CSM_OFFSET_KEY_EXCHANGE_CALC_SYM_KEY ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_KeyExchangeCalcSymKeyServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyExtractStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyExtractStart( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range against the provided configuration ID */
  if ( ! ( ( cfgId >= CSM_OFFSET_SYM_KEY_EXTRACT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS + CSM_OFFSET_SYM_KEY_EXTRACT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #30 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_KEY_EXTRACT;

    /* #40 Call of configured function pointer */
    retVal = Csm_SymKeyExtractConfigs[localId].PrimitiveStartFct( Csm_SymKeyExtractConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #50 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMKEYEXTRACTSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_SymKeyExtractStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyExtractUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyExtractUpdate( Csm_ConfigIdType cfgId,
                                                          P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                          uint32 dataLength )
{
# if ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( dataPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_KEY_EXTRACT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS + CSM_OFFSET_SYM_KEY_EXTRACT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_KEY_EXTRACT;
    /* #40 Call of configured function pointer */
    retVal = Csm_SymKeyExtractConfigs[localId].PrimitiveUpdateFct( Csm_SymKeyExtractConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMKEYEXTRACTUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymKeyExtractUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyExtractFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 2 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyExtractFinish( Csm_ConfigIdType cfgId,
                                                          P2VAR( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr )
{
# if ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( keyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_KEY_EXTRACT ) && ( cfgId < ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS + CSM_OFFSET_SYM_KEY_EXTRACT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_KEY_EXTRACT;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_SymKeyExtractConfigs[localId].PrimitiveFinishFct( Csm_SymKeyExtractConfigs[localId].PrimitiveConfigPtr, keyPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMKEYEXTRACTFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymKeyExtractFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyExtractCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymKeyExtractCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_KEY_EXTRACT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS + CSM_OFFSET_SYM_KEY_EXTRACT ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_SymKeyExtractConfigs[Csm_LastCfgId - CSM_OFFSET_SYM_KEY_EXTRACT].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_SymKeyExtractCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyExtractServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymKeyExtractServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_KEY_EXTRACT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS + CSM_OFFSET_SYM_KEY_EXTRACT ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_SymKeyExtractServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyWrapSymStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyWrapSymStart( Csm_ConfigIdType cfgId,
                                                         P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
                                                         P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) wrappingkeyPtr )
{
# if ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( keyPtr == NULL_PTR ) || ( wrappingkeyPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_KEY_WRAP_SYM ) && ( cfgId < ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS + CSM_OFFSET_SYM_KEY_WRAP_SYM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_KEY_WRAP_SYM;

    /* #50 Call of configured function pointer */
    retVal = Csm_SymKeyWrapSymConfigs[localId].PrimitiveStartFct( Csm_SymKeyWrapSymConfigs[localId].PrimitiveConfigPtr, keyPtr, wrappingkeyPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMKEYWRAPSYMSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( wrappingkeyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_SymKeyWrapSymStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyWrapSymUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyWrapSymUpdate( Csm_ConfigIdType cfgId,
                                                          P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                          P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) dataLengthPtr )
{
# if ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( dataPtr == NULL_PTR ) || ( dataLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_KEY_WRAP_SYM ) && ( cfgId < ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS + CSM_OFFSET_SYM_KEY_WRAP_SYM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_KEY_WRAP_SYM;
    /* #40 Call of configured function pointer */
    retVal = Csm_SymKeyWrapSymConfigs[localId].PrimitiveUpdateFct( Csm_SymKeyWrapSymConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMKEYWRAPSYMUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymKeyWrapSymUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyWrapSymFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyWrapSymFinish( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range */
  if ( ! ( ( cfgId >= CSM_OFFSET_SYM_KEY_WRAP_SYM ) && ( cfgId < ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS + CSM_OFFSET_SYM_KEY_WRAP_SYM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_KEY_WRAP_SYM;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #30 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #40 Call of configured function pointer */
    retVal = Csm_SymKeyWrapSymConfigs[localId].PrimitiveFinishFct( Csm_SymKeyWrapSymConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMKEYWRAPSYMFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymKeyWrapSymFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyWrapSymCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymKeyWrapSymCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_KEY_WRAP_SYM ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS + CSM_OFFSET_SYM_KEY_WRAP_SYM ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_SymKeyWrapSymConfigs[Csm_LastCfgId - CSM_OFFSET_SYM_KEY_WRAP_SYM].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_SymKeyWrapSymCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyWrapSymServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymKeyWrapSymServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_KEY_WRAP_SYM ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS + CSM_OFFSET_SYM_KEY_WRAP_SYM ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_SymKeyWrapSymServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyWrapAsymStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyWrapAsymStart( Csm_ConfigIdType cfgId,
                                                          P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
                                                          P2CONST( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) wrappingkeyPtr )
{
# if ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( keyPtr == NULL_PTR ) || ( wrappingkeyPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_KEY_WRAP_ASYM ) && ( cfgId < ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS + CSM_OFFSET_SYM_KEY_WRAP_ASYM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_KEY_WRAP_ASYM;

    /* #50 Call of configured function pointer */
    retVal = Csm_SymKeyWrapAsymConfigs[localId].PrimitiveStartFct( Csm_SymKeyWrapAsymConfigs[localId].PrimitiveConfigPtr, keyPtr, wrappingkeyPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMKEYWRAPASYMSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( wrappingkeyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_SymKeyWrapAsymStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyWrapAsymUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyWrapAsymUpdate( Csm_ConfigIdType cfgId,
                                                           P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                           P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) dataLengthPtr )
{
# if ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( dataPtr == NULL_PTR ) || ( dataLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_SYM_KEY_WRAP_ASYM ) && ( cfgId < ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS + CSM_OFFSET_SYM_KEY_WRAP_ASYM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_KEY_WRAP_ASYM;
    /* #40 Call of configured function pointer */
    retVal = Csm_SymKeyWrapAsymConfigs[localId].PrimitiveUpdateFct( Csm_SymKeyWrapAsymConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMKEYWRAPASYMUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymKeyWrapAsymUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyWrapAsymFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyWrapAsymFinish( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range */
  if ( ! ( ( cfgId >= CSM_OFFSET_SYM_KEY_WRAP_ASYM ) && ( cfgId < ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS + CSM_OFFSET_SYM_KEY_WRAP_ASYM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_SYM_KEY_WRAP_ASYM;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #30 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #40 Call of configured function pointer */
    retVal = Csm_SymKeyWrapAsymConfigs[localId].PrimitiveFinishFct( Csm_SymKeyWrapAsymConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_SYMKEYWRAPASYMFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_SymKeyWrapAsymFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyWrapAsymCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymKeyWrapAsymCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_KEY_WRAP_ASYM ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS + CSM_OFFSET_SYM_KEY_WRAP_ASYM ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_SymKeyWrapAsymConfigs[Csm_LastCfgId - CSM_OFFSET_SYM_KEY_WRAP_ASYM].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_SymKeyWrapAsymCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_SymKeyWrapAsymServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_SymKeyWrapAsymServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_SYM_KEY_WRAP_ASYM ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS + CSM_OFFSET_SYM_KEY_WRAP_ASYM ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_SymKeyWrapAsymServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPublicKeyExtractStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPublicKeyExtractStart( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range against the provided configuration ID */
  if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS + CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #30 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT;

    /* #40 Call of configured function pointer */
    retVal = Csm_AsymPublicKeyExtractConfigs[localId].PrimitiveStartFct( Csm_AsymPublicKeyExtractConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #50 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMPUBLICKEYEXTRACTSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_AsymPublicKeyExtractStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPublicKeyExtractUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPublicKeyExtractUpdate( Csm_ConfigIdType cfgId,
                                                                 P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                                 uint32 dataLength )
{
# if ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( dataPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS + CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT;
    /* #40 Call of configured function pointer */
    retVal = Csm_AsymPublicKeyExtractConfigs[localId].PrimitiveUpdateFct( Csm_AsymPublicKeyExtractConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMPUBLICKEYEXTRACTUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_AsymPublicKeyExtractUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPublicKeyExtractFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 2 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPublicKeyExtractFinish( Csm_ConfigIdType cfgId,
                                                                 P2VAR( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr )
{
# if ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( keyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS + CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_AsymPublicKeyExtractConfigs[localId].PrimitiveFinishFct( Csm_AsymPublicKeyExtractConfigs[localId].PrimitiveConfigPtr, keyPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMPUBLICKEYEXTRACTFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_AsymPublicKeyExtractFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPublicKeyExtractCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_AsymPublicKeyExtractCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS + CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_AsymPublicKeyExtractConfigs[Csm_LastCfgId - CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_AsymPublicKeyExtractCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPublicKeyExtractServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_AsymPublicKeyExtractServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS + CSM_OFFSET_ASYM_PUBLIC_KEY_EXTRACT ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_AsymPublicKeyExtractServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyExtractStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyExtractStart( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range against the provided configuration ID */
  if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #30 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT;

    /* #40 Call of configured function pointer */
    retVal = Csm_AsymPrivateKeyExtractConfigs[localId].PrimitiveStartFct( Csm_AsymPrivateKeyExtractConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #50 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMPRIVATEKEYEXTRACTSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_AsymPrivateKeyExtractStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyExtractUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyExtractUpdate( Csm_ConfigIdType cfgId,
                                                                  P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                                  uint32 dataLength )
{
# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( dataPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT;
    /* #40 Call of configured function pointer */
    retVal = Csm_AsymPrivateKeyExtractConfigs[localId].PrimitiveUpdateFct( Csm_AsymPrivateKeyExtractConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLength ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMPRIVATEKEYEXTRACTUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLength ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_AsymPrivateKeyExtractUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyExtractFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 2 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyExtractFinish( Csm_ConfigIdType cfgId,
                                                                  P2VAR( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr )
{
# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( keyPtr == NULL_PTR )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #40 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #50 Call of configured function pointer */
    retVal = Csm_AsymPrivateKeyExtractConfigs[localId].PrimitiveFinishFct( Csm_AsymPrivateKeyExtractConfigs[localId].PrimitiveConfigPtr, keyPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMPRIVATEKEYEXTRACTFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_AsymPrivateKeyExtractFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyExtractCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_AsymPrivateKeyExtractCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_AsymPrivateKeyExtractConfigs[Csm_LastCfgId - CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_AsymPrivateKeyExtractCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyExtractServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_AsymPrivateKeyExtractServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_EXTRACT ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_AsymPrivateKeyExtractServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapSymStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyWrapSymStart( Csm_ConfigIdType cfgId,
                                                                 P2CONST( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
                                                                 P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) wrappingkeyPtr )
{
# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( keyPtr == NULL_PTR ) || ( wrappingkeyPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM;

    /* #50 Call of configured function pointer */
    retVal = Csm_AsymPrivateKeyWrapSymConfigs[localId].PrimitiveStartFct( Csm_AsymPrivateKeyWrapSymConfigs[localId].PrimitiveConfigPtr, keyPtr, wrappingkeyPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMPRIVATEKEYWRAPSYMSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( wrappingkeyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_AsymPrivateKeyWrapSymStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapSymUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyWrapSymUpdate( Csm_ConfigIdType cfgId,
                                                                  P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                                  P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) dataLengthPtr )
{
# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( dataPtr == NULL_PTR ) || ( dataLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM;
    /* #40 Call of configured function pointer */
    retVal = Csm_AsymPrivateKeyWrapSymConfigs[localId].PrimitiveUpdateFct( Csm_AsymPrivateKeyWrapSymConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMPRIVATEKEYWRAPSYMUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_AsymPrivateKeyWrapSymUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapSymFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyWrapSymFinish( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range */
  if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #30 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #40 Call of configured function pointer */
    retVal = Csm_AsymPrivateKeyWrapSymConfigs[localId].PrimitiveFinishFct( Csm_AsymPrivateKeyWrapSymConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMPRIVATEKEYWRAPSYMFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_AsymPrivateKeyWrapSymFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapSymCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_AsymPrivateKeyWrapSymCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_AsymPrivateKeyWrapSymConfigs[Csm_LastCfgId - CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_AsymPrivateKeyWrapSymCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapSymServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_AsymPrivateKeyWrapSymServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_SYM ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_AsymPrivateKeyWrapSymServiceFinishNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapAsymStart()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyWrapAsymStart( Csm_ConfigIdType cfgId,
                                                                  P2CONST( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
                                                                  P2CONST( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) wrappingkeyPtr )
{
# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( keyPtr == NULL_PTR ) || ( wrappingkeyPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range against the provided configuration ID */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check initialization state of the component */
  else if ( Csm_IsInitialized != CSM_INITIALIZED )
  {
    errorId =  CSM_E_UNINIT;
  }
  /* #40 Check if service is idle */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_IDLE )
  {
    retVal = CSM_E_BUSY;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM;

    /* #50 Call of configured function pointer */
    retVal = Csm_AsymPrivateKeyWrapAsymConfigs[localId].PrimitiveStartFct( Csm_AsymPrivateKeyWrapAsymConfigs[localId].PrimitiveConfigPtr, keyPtr, wrappingkeyPtr ); /* SBSW_CSM_03 */
    if ( retVal == CSM_E_OK )
    {
      /* #60 Set service state to active */
      Csm_ServiceState[cfgId] = CSM_SERVICE_ACTIVE; /* SBSW_CSM_04 */
    }
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMPRIVATEKEYWRAPASYMSTART_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( keyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( wrappingkeyPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* PRQA S 6080 */ /* MD_MSR_STMIF */ /* Csm_AsymPrivateKeyWrapAsymStart() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapAsymUpdate()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
/* PRQA S 3673 3 */ /* MD_CSM_16.7 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyWrapAsymUpdate( Csm_ConfigIdType cfgId,
                                                                   P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                                   P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) dataLengthPtr )
{
# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check for null pointers */
  if ( ( dataPtr == NULL_PTR ) || ( dataLengthPtr == NULL_PTR ) )
  {
    errorId = CSM_E_PARAM_PTR_INVALID;
  }
  /* #20 Check configuration range */
  else if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #30 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM;
    /* #40 Call of configured function pointer */
    retVal = Csm_AsymPrivateKeyWrapAsymConfigs[localId].PrimitiveUpdateFct( Csm_AsymPrivateKeyWrapAsymConfigs[localId].PrimitiveConfigPtr, dataPtr, dataLengthPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMPRIVATEKEYWRAPASYMUPDATE_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  CSM_DUMMY_STATEMENT( dataLengthPtr ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_AsymPrivateKeyWrapAsymUpdate() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapAsymFinish()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 */
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyWrapAsymFinish( Csm_ConfigIdType cfgId )
{
# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS != 0u )
  /* ----- Local Variables ---------------------------------------------- */
  Csm_ConfigIdType localId;
  Csm_ReturnType retVal = CSM_E_NOT_OK;
  uint8 errorId = CSM_E_NO_ERROR;

  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check configuration range */
  if ( ! ( ( cfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM ) && ( cfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM ) ) ) )
  {
    errorId = CSM_E_PARAM_METHOD_INVALID;
  }
  /* #20 Check service active state of the component */
  else if ( Csm_ServiceState[cfgId] != CSM_SERVICE_ACTIVE )
  {
    errorId = CSM_E_SERVICE_NOT_STARTED;
  }
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    localId = cfgId - CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM;

#  if ( CSM_USE_SYNC_JOB_PROCESSING == STD_ON )
    /* #30 Set service status to idle if the synchronous interface is used */
    Csm_ServiceState[cfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
#  endif

    /* #40 Call of configured function pointer */
    retVal = Csm_AsymPrivateKeyWrapAsymConfigs[localId].PrimitiveFinishFct( Csm_AsymPrivateKeyWrapAsymConfigs[localId].PrimitiveConfigPtr ); /* SBSW_CSM_03 */
  }

  /* ----- Development Error Report --------------------------------------- */
#  if (CSM_DEV_ERROR_REPORT == STD_ON)
  if ( errorId != CSM_E_NO_ERROR )
  {
    (void)Det_ReportError( (uint16)CSM_MODULE_ID, CSM_INSTANCE_ID, (uint8)(CSM_ASYMPRIVATEKEYWRAPASYMFINISH_ID), errorId );
  }
#  else
  CSM_DUMMY_STATEMENT( errorId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
#  endif

  return retVal;
# else
  CSM_DUMMY_STATEMENT( cfgId ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
  return CSM_E_NOT_OK;
# endif
} /* Csm_AsymPrivateKeyWrapAsymFinish() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapAsymCallbackNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_AsymPrivateKeyWrapAsymCallbackNotification( Csm_ReturnType Result )
{
# if ( ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range against the last provided configuration ID */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM ) ) ) )
  {  
    /* #20 Call of configured callback function pointer */
    (void)Csm_AsymPrivateKeyWrapAsymConfigs[Csm_LastCfgId - CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM].CallbackFct( Result ); /* SBSW_CSM_06 */
  }
# else
  CSM_DUMMY_STATEMENT( Result ); /* PRQA S 3112, 3199 */ /* MD_MSR_14.2 */ /* lint -e{438} */
# endif
} /* Csm_AsymPrivateKeyWrapAsymCallbackNotification() */
#endif

#if ( ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) || ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS != 0u ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapAsymServiceFinishNotification()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 */
FUNC( void, CSM_CODE ) Csm_AsymPrivateKeyWrapAsymServiceFinishNotification( void )
{
# if ( ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS != 0u ) && ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF ) )
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check configuration range */
  if ( ( ( Csm_LastCfgId >= CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM ) && ( Csm_LastCfgId < ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS + CSM_OFFSET_ASYM_PRIVATE_KEY_WRAP_ASYM ) ) ) )
  {  
    /* #20 Set service state to idle */
    Csm_ServiceState[Csm_LastCfgId] = CSM_SERVICE_IDLE; /* SBSW_CSM_04 */
  }
# endif
} /* Csm_AsymPrivateKeyWrapAsymServiceFinishNotification() */
#endif

#define CSM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Module specific MISRA deviations
 *********************************************************************************************************************/
/* Module specific MISRA deviations:

  MD_CSM_DEBUG:
    Reason:     For testing and debugging reason the CSM_LOCAL can be overwritten to remove the static keyword.
    Risk:       None
    Prevention: Covered by code review.
  MD_CSM_16.7:
    Reason:     Pointer can only be const when method is empty and only Dummy statements are used.
    Risk:       None
    Prevention: Covered by code review.
*/

/* SBSW_JUSTIFICATION_BEGIN
  \ID SBSW_CSM_01
    \DESCRIPTION The function Csm_GetVersionInfo writes to the object referenced by parameter VersionInfoPtr
    \COUNTERMEASURE \N The caller ensures that the pointer passed to the parameter VersionInfoPtr is valid.

  \ID SBSW_CSM_02
    \DESCRIPTION Iterating over an array of data.
    \COUNTERMEASURE \N The for loop ensures that cfgId never exceeds the size of the array Csm_ServiceState.

  \ID SBSW_CSM_03
    \DESCRIPTION Function pointer call to user configured CRY function.
    \COUNTERMEASURE \R The provided cfgId by the caller is checked against the possible configuration range
                       of the specific service. The allocation to the service specific configuration is made
                       by substracting the service offset. The reference to a valid object is set by the user.

  \ID SBSW_CSM_04
    \DESCRIPTION Set the Csm_ServiceState of specific service to CSM_SERVICE_IDLE/CSM_SERVICE_ACTIVE
    \COUNTERMEASURE \R The function verifies that the index is in the possible configuration range of the 
                       specific service.

  \ID SBSW_CSM_05
    \DESCRIPTION Function pointer call to user configured CRY main function.
    \COUNTERMEASURE \N The for loop and the subtraction of the CSM_OFFSET_<SERVICE> ensure that the index
                       never exceeds the size of the array Csm_<Service>Configs.

  \ID SBSW_CSM_06
    \DESCRIPTION Function pointer call to user configured CRY callback function.
    \COUNTERMEASURE \R The Csm_LastCfgId is only modified within the Csm_MainFunction.
                       The function verifies that the Csm_LastCfgId is in the possible configuration range
                       of the specific service.
SBSW_JUSTIFICATION_END */

/* COV_JUSTIFICATION_BEGIN
  \ID COV_CSM_NON_RTE
    \ACCEPT TX
    \REASON Ensures the variable or error code define exists if the CSM is used without RTE
COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: CSM.C
 *********************************************************************************************************************/

