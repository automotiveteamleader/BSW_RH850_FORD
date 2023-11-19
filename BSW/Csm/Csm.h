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
/**        \file  Csm.h
 *        \brief  MICROSAR Crypto Service Manager (CSM)
 *
 *      \details  Implementation of the MICROSAR Crypto Service Manager (CSM)
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials       Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Philipp Ritter                visrpp         Vector Informatik GmbH
 *  Markus Schneider              vismss         Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2012-10-01  visrpp  ESCAN00061819 Creation
 *  01.00.01  2013-08-12  vismss  ESCAN00069726 Fixed Csm_SymKeyExtractStart API due to AUTOSAR spec
 *  01.00.02  2013-09-03  vismss  ESCAN00070196 Fixed Version Check
 *  02.00.00  2013-09-27  vismss  ESCAN00070749 DaVinci Configurator 5 support added
 *  02.00.01  2013-11-18  vismss  ESCAN00071955 Version check mismatch
 *  02.00.02  2014-01-16  vismss  ESCAN00072996 No change in this file
 *  02.00.03  2014-05-22  vismss  ESCAN00074328 Fixed an compiler error in Csm_SymKeyExtractStart
 *                        vismss  ESCAN00075681 Encapsulated the Csm_ServiceState array
 *  02.00.04  2014-06-26  vismss  ESCAN00076503 No change in this file
 *  02.01.00  2014-10-02  vismss  ESCAN00078011 Rework of static code generator
 *                                              Fixed a problem with encapsulation of Csm_ServiceState
 *  02.02.00  2015-08-17  vismss  ESCAN00080280 FEAT-427: SafeBSW Step I
 *                        vismss  ESCAN00081768 FEAT-1275: SafeBSW Step II
 *  02.02.01  2015-10-02  vismss  ESCAN00085013 Fixed: Range check performed before first array read access
 *                        vismss  ESCAN00084427 Fixed: Typos
 *  02.02.02  2015-11-27  vismss  ESCAN00086046 FEAT-1527: SafeBSW Step III
 *  02.02.03  2016-02-26  vismss  ESCAN00087926 FEAT-1688: SafeBSW Step IV
 *                                ESCAN00087173 Fixed: Potential issue with third party CRY modules
 *********************************************************************************************************************/

#if !defined (CSM_H)
# define CSM_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
# include "Csm_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Vendor and module identification */
# define CSM_VENDOR_ID                           (30u)
# define CSM_MODULE_ID                           (110u)
# define CSM_INSTANCE_ID                         (0u)

/* AUTOSAR Software specification version information */
# define CSM_AR_RELEASE_MAJOR_VERSION            (0x04u)
# define CSM_AR_RELEASE_MINOR_VERSION            (0x00u)
# define CSM_AR_RELEASE_REVISION_VERSION         (0x03u)

/* ----- Component version information (decimal version of ALM implementation package) ----- */
# define CSM_SW_MAJOR_VERSION                    (2u)
# define CSM_SW_MINOR_VERSION                    (2u)
# define CSM_SW_PATCH_VERSION                    (3u)

/* ----- API service IDs ----- */
/* Service ID: Csm_Init() */
# define CSM_INIT_ID                             (0x00u)
/* Service ID: Csm_Interruption() */
# define CSM_INTERRUPTION_ID                     (0x02u)
/* Service ID: Csm_GetVersionInfo() */
# define CSM_GETVERSIONINFO_ID                   (0x3Bu)
/* Service ID: Csm_HashStart() */
# define CSM_HASHSTART_ID                        (0x03u)
/* Service ID: Csm_HashUpdate() */
# define CSM_HASHUPDATE_ID                       (0x04u)
/* Service ID: Csm_HashFinish() */
# define CSM_HASHFINISH_ID                       (0x05u)
/* Service ID: Csm_MacGenerateStart() */
# define CSM_MACGENERATESTART_ID                 (0x06u)
/* Service ID: Csm_MacGenerateUpdate() */
# define CSM_MACGENERATEUPDATE_ID                (0x07u)
/* Service ID: Csm_MacGenerateFinish() */
# define CSM_MACGENERATEFINISH_ID                (0x08u)
/* Service ID: Csm_MacVerifyStart() */
# define CSM_MACVERIFYSTART_ID                   (0x09u)
/* Service ID: Csm_MacVerifyUpdate() */
# define CSM_MACVERIFYUPDATE_ID                  (0x0Au)
/* Service ID: Csm_MacVerifyFinish() */
# define CSM_MACVERIFYFINISH_ID                  (0x0Bu)
/* Service ID: Csm_RandomSeedStart() */
# define CSM_RANDOMSEEDSTART_ID                  (0x0Cu)
/* Service ID: Csm_RandomSeedUpdate() */
# define CSM_RANDOMSEEDUPDATE_ID                 (0x0Du)
/* Service ID: Csm_RandomSeedFinish() */
# define CSM_RANDOMSEEDFINISH_ID                 (0x0Eu)
/* Service ID: Csm_RandomGenerate() */
# define CSM_RANDOMGENERATE_ID                   (0x0Fu)
/* Service ID: Csm_SymBlockEncryptStart() */
# define CSM_SYMBLOCKENCRYPTSTART_ID             (0x10u)
/* Service ID: Csm_SymBlockEncryptUpdate() */
# define CSM_SYMBLOCKENCRYPTUPDATE_ID            (0x11u)
/* Service ID: Csm_SymBlockEncryptFinish() */
# define CSM_SYMBLOCKENCRYPTFINISH_ID            (0x12u)
/* Service ID: Csm_SymBlockDecryptStart() */
# define CSM_SYMBLOCKDECRYPTSTART_ID             (0x13u)
/* Service ID: Csm_SymBlockDecryptUpdate() */
# define CSM_SYMBLOCKDECRYPTUPDATE_ID            (0x14u)
/* Service ID: Csm_SymBlockDecryptFinish() */
# define CSM_SYMBLOCKDECRYPTFINISH_ID            (0x15u)
/* Service ID: Csm_SymEncryptStart() */
# define CSM_SYMENCRYPTSTART_ID                  (0x16u)
/* Service ID: Csm_SymEncryptUpdate() */
# define CSM_SYMENCRYPTUPDATE_ID                 (0x17u)
/* Service ID: Csm_SymEncryptFinish() */
# define CSM_SYMENCRYPTFINISH_ID                 (0x18u)
/* Service ID: Csm_SymDecryptStart() */
# define CSM_SYMDECRYPTSTART_ID                  (0x19u)
/* Service ID: Csm_SymDecryptUpdate() */
# define CSM_SYMDECRYPTUPDATE_ID                 (0x1Au)
/* Service ID: Csm_SymDecryptFinish() */
# define CSM_SYMDECRYPTFINISH_ID                 (0x1Bu)
/* Service ID: Csm_AsymEncryptStart() */
# define CSM_ASYMENCRYPTSTART_ID                 (0x1Cu)
/* Service ID: Csm_AsymEncryptUpdate() */
# define CSM_ASYMENCRYPTUPDATE_ID                (0x1Du)
/* Service ID: Csm_AsymEncryptFinish() */
# define CSM_ASYMENCRYPTFINISH_ID                (0x1Eu)
/* Service ID: Csm_AsymDecryptStart() */
# define CSM_ASYMDECRYPTSTART_ID                 (0x1Fu)
/* Service ID: Csm_AsymDecryptUpdate() */
# define CSM_ASYMDECRYPTUPDATE_ID                (0x20u)
/* Service ID: Csm_AsymDecryptFinish() */
# define CSM_ASYMDECRYPTFINISH_ID                (0x21u)
/* Service ID: Csm_SignatureGenerateStart() */
# define CSM_SIGNATUREGENERATESTART_ID           (0x22u)
/* Service ID: Csm_SignatureGenerateUpdate() */
# define CSM_SIGNATUREGENERATEUPDATE_ID          (0x23u)
/* Service ID: Csm_SignatureGenerateFinish() */
# define CSM_SIGNATUREGENERATEFINISH_ID          (0x24u)
/* Service ID: Csm_SignatureVerifyStart() */
# define CSM_SIGNATUREVERIFYSTART_ID             (0x25u)
/* Service ID: Csm_SignatureVerifyUpdate() */
# define CSM_SIGNATUREVERIFYUPDATE_ID            (0x26u)
/* Service ID: Csm_SignatureVerifyFinish() */
# define CSM_SIGNATUREVERIFYFINISH_ID            (0x27u)
/* Service ID: Csm_ChecksumStart() */
# define CSM_CHECKSUMSTART_ID                    (0x28u)
/* Service ID: Csm_ChecksumUpdate() */
# define CSM_CHECKSUMUPDATE_ID                   (0x29u)
/* Service ID: Csm_ChecksumFinish() */
# define CSM_CHECKSUMFINISH_ID                   (0x2Au)
/* Service ID: Csm_KeyDeriveStart() */
# define CSM_KEYDERIVESTART_ID                   (0x2Bu)
/* Service ID: Csm_KeyDeriveUpdate() */
# define CSM_KEYDERIVEUPDATE_ID                  (0x2Cu)
/* Service ID: Csm_KeyDeriveFinish() */
# define CSM_KEYDERIVEFINISH_ID                  (0x2Du)
/* Service ID: Csm_KeyDeriveSymKey() */
# define CSM_KEYDERIVESYMKEY_ID                  (0x4Cu)
/* Service ID: Csm_KeyExchangeCalcPubVal() */
# define CSM_KEYEXCHANGECALCPUBVAL_ID            (0x2Eu)
/* Service ID: Csm_KeyExchangeCalcSecretStart() */
# define CSM_KEYEXCHANGECALCSECRETSTART_ID       (0x2Fu)
/* Service ID: Csm_KeyExchangeCalcSecretUpdate() */
# define CSM_KEYEXCHANGECALCSECRETUPDATE_ID      (0x30u)
/* Service ID: Csm_KeyExchangeCalcSecretFinish() */
# define CSM_KEYEXCHANGECALCSECRETFINISH_ID      (0x31u)
/* Service ID: Csm_KeyExchangeCalcSymKeyStart() */
# define CSM_KEYEXCHANGECALCSYMKEYSTART_ID       (0x3Du)
/* Service ID: Csm_KeyExchangeCalcSymKeyUpdate() */
# define CSM_KEYEXCHANGECALCSYMKEYUPDATE_ID      (0x3Eu)
/* Service ID: Csm_KeyExchangeCalcSymKeyFinish() */
# define CSM_KEYEXCHANGECALCSYMKEYFINISH_ID      (0x3Fu)
/* Service ID: Csm_SymKeyExtractStart() */
# define CSM_SYMKEYEXTRACTSTART_ID               (0x32u)
/* Service ID: Csm_SymKeyExtractUpdate() */
# define CSM_SYMKEYEXTRACTUPDATE_ID              (0x33u)
/* Service ID: Csm_SymKeyExtractFinish() */
# define CSM_SYMKEYEXTRACTFINISH_ID              (0x34u)
/* Service ID: Csm_SymKeyWrapSymStart() */
# define CSM_SYMKEYWRAPSYMSTART_ID               (0x40u)
/* Service ID: Csm_SymKeyWrapSymUpdate() */
# define CSM_SYMKEYWRAPSYMUPDATE_ID              (0x41u)
/* Service ID: Csm_SymKeyWrapSymFinish() */
# define CSM_SYMKEYWRAPSYMFINISH_ID              (0x42u)
/* Service ID: Csm_SymKeyWrapAsymStart() */
# define CSM_SYMKEYWRAPASYMSTART_ID              (0x43u)
/* Service ID: Csm_SymKeyWrapAsymUpdate() */
# define CSM_SYMKEYWRAPASYMUPDATE_ID             (0x44u)
/* Service ID: Csm_SymKeyWrapAsymFinish() */
# define CSM_SYMKEYWRAPASYMFINISH_ID             (0x45u)
/* Service ID: Csm_AsymPublicKeyExtractStart() */
# define CSM_ASYMPUBLICKEYEXTRACTSTART_ID        (0x35u)
/* Service ID: Csm_AsymPublicKeyExtractUpdate() */
# define CSM_ASYMPUBLICKEYEXTRACTUPDATE_ID       (0x36u)
/* Service ID: Csm_AsymPublicKeyExtractFinish() */
# define CSM_ASYMPUBLICKEYEXTRACTFINISH_ID       (0x37u)
/* Service ID: Csm_AsymPrivateKeyExtractStart() */
# define CSM_ASYMPRIVATEKEYEXTRACTSTART_ID       (0x38u)
/* Service ID: Csm_AsymPrivateKeyExtractUpdate() */
# define CSM_ASYMPRIVATEKEYEXTRACTUPDATE_ID      (0x39u)
/* Service ID: Csm_AsymPrivateKeyExtractFinish() */
# define CSM_ASYMPRIVATEKEYEXTRACTFINISH_ID      (0x3Au)
/* Service ID: Csm_AsymPrivateKeyWrapSymStart() */
# define CSM_ASYMPRIVATEKEYWRAPSYMSTART_ID       (0x46u)
/* Service ID: Csm_AsymPrivateKeyWrapSymUpdate() */
# define CSM_ASYMPRIVATEKEYWRAPSYMUPDATE_ID      (0x47u)
/* Service ID: Csm_AsymPrivateKeyWrapSymFinish() */
# define CSM_ASYMPRIVATEKEYWRAPSYMFINISH_ID      (0x48u)
/* Service ID: Csm_AsymPrivateKeyWrapAsymStart() */
# define CSM_ASYMPRIVATEKEYWRAPASYMSTART_ID      (0x49u)
/* Service ID: Csm_AsymPrivateKeyWrapAsymUpdate() */
# define CSM_ASYMPRIVATEKEYWRAPASYMUPDATE_ID     (0x4Au)
/* Service ID: Csm_AsymPrivateKeyWrapAsymFinish() */
# define CSM_ASYMPRIVATEKEYWRAPASYMFINISH_ID     (0x4Bu)

/* ----- Error codes ----- */
/* Error Code: Used to check if no error occurred */
# define CSM_E_NO_ERROR                          (0x00u)
/* Error Code: API request called with invalid parameter (Nullpointer) */
# define CSM_E_PARAM_PTR_INVALID                 (0x01u)
/* Error Code: Requested service is not initialized */
# define CSM_E_SERVICE_NOT_STARTED               (0x02u)
/* Error Code: API request called with invalid parameter (invalid method for selected service) */
# define CSM_E_PARAM_METHOD_INVALID              (0x03u)
/* Error Code: API request called with invalid parameter (invalid key type for selected service) */
# define CSM_E_PARAM_KEY_TYPE_INVALID            (0x04u)
/* Error Code: API request called before initialisation of CSM module */
# define CSM_E_UNINIT                            (0x05u)
/* Error Code: Provided buffer for storing the result of a computation is too small */
# define CSM_E_BUFFER_TOO_SMALL                  (0x06u)

/* ----- Modes ----- */
/* State: Uninitialized */
# define CSM_UNINIT                              (0x00u)
/* State: Initialized */
# define CSM_INITIALIZED                         (0x01u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

# define CSM_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if ( CSM_NUMBER_OF_HASH_CONFIGS != 0 )
extern CONST(Csm_HashConfigType, CSM_CONST) Csm_HashConfigs[CSM_NUMBER_OF_HASH_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_MAC_GENERATE_CONFIGS != 0 )
extern CONST(Csm_MacGenerateConfigType, CSM_CONST) Csm_MacGenerateConfigs[CSM_NUMBER_OF_MAC_GENERATE_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_MAC_VERIFY_CONFIGS != 0 )
extern CONST(Csm_MacVerifyConfigType, CSM_CONST) Csm_MacVerifyConfigs[CSM_NUMBER_OF_MAC_VERIFY_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_RANDOM_SEED_CONFIGS != 0 )
extern CONST(Csm_RandomSeedConfigType, CSM_CONST) Csm_RandomSeedConfigs[CSM_NUMBER_OF_RANDOM_SEED_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS != 0 )
extern CONST(Csm_RandomGenerateConfigType, CSM_CONST) Csm_RandomGenerateConfigs[CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS != 0 )
extern CONST(Csm_SymBlockEncryptConfigType, CSM_CONST) Csm_SymBlockEncryptConfigs[CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS != 0 )
extern CONST(Csm_SymBlockDecryptConfigType, CSM_CONST) Csm_SymBlockDecryptConfigs[CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS != 0 )
extern CONST(Csm_SymEncryptConfigType, CSM_CONST) Csm_SymEncryptConfigs[CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS != 0 )
extern CONST(Csm_SymDecryptConfigType, CSM_CONST) Csm_SymDecryptConfigs[CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS != 0 )
extern CONST(Csm_AsymEncryptConfigType, CSM_CONST) Csm_AsymEncryptConfigs[CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS != 0 )
extern CONST(Csm_AsymDecryptConfigType, CSM_CONST) Csm_AsymDecryptConfigs[CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS != 0 )
extern CONST(Csm_SignatureGenerateConfigType, CSM_CONST) Csm_SignatureGenerateConfigs[CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS != 0 )
extern CONST(Csm_SignatureVerifyConfigType, CSM_CONST) Csm_SignatureVerifyConfigs[CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_CHECKSUM_CONFIGS != 0 )
extern CONST(Csm_ChecksumConfigType, CSM_CONST) Csm_ChecksumConfigs[CSM_NUMBER_OF_CHECKSUM_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_KEY_DERIVE_CONFIGS != 0 )
extern CONST(Csm_KeyDeriveConfigType, CSM_CONST) Csm_KeyDeriveConfigs[CSM_NUMBER_OF_KEY_DERIVE_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS != 0 )
extern CONST(Csm_KeyDeriveSymKeyConfigType, CSM_CONST) Csm_KeyDeriveSymKeyConfigs[CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS != 0 )
extern CONST(Csm_KeyExchangeCalcPubValConfigType, CSM_CONST) Csm_KeyExchangeCalcPubValConfigs[CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS != 0 )
extern CONST(Csm_KeyExchangeCalcSecretConfigType, CSM_CONST) Csm_KeyExchangeCalcSecretConfigs[CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS != 0 )
extern CONST(Csm_KeyExchangeCalcSymKeyConfigType, CSM_CONST) Csm_KeyExchangeCalcSymKeyConfigs[CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS != 0 )
extern CONST(Csm_SymKeyExtractConfigType, CSM_CONST) Csm_SymKeyExtractConfigs[CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS != 0 )
extern CONST(Csm_SymKeyWrapSymConfigType, CSM_CONST) Csm_SymKeyWrapSymConfigs[CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS != 0 )
extern CONST(Csm_SymKeyWrapAsymConfigType, CSM_CONST) Csm_SymKeyWrapAsymConfigs[CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS != 0 )
extern CONST(Csm_AsymPublicKeyExtractConfigType, CSM_CONST) Csm_AsymPublicKeyExtractConfigs[CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS != 0 )
extern CONST(Csm_AsymPrivateKeyExtractConfigType, CSM_CONST) Csm_AsymPrivateKeyExtractConfigs[CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS != 0 )
extern CONST(Csm_AsymPrivateKeyWrapSymConfigType, CSM_CONST) Csm_AsymPrivateKeyWrapSymConfigs[CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS];
# endif

# if ( CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS != 0 )
extern CONST(Csm_AsymPrivateKeyWrapAsymConfigType, CSM_CONST) Csm_AsymPrivateKeyWrapAsymConfigs[CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS];
# endif

# define CSM_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define CSM_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  Csm_Init()
 *********************************************************************************************************************/
/*! \brief       Initializes the Csm.
 *  \details     Set all service states to initial idle.
 *  \pre         None
 *  \context     ANY
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-326
 *  \trace       SPEC-47227, SPEC-47311
 *********************************************************************************************************************/
FUNC( void, CSM_CODE)  Csm_Init( void );

/**********************************************************************************************************************
 *  Csm_InitMemory()
 *********************************************************************************************************************/
/*! \brief       Power-up memory initialization.
 *  \details     Initialize component variables at power up.
 *  \pre         Module is uninitialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \note        Use this function in case these variables are not initialized by the startup code.
 *********************************************************************************************************************/
FUNC( void, CSM_CODE ) Csm_InitMemory( void );

/**********************************************************************************************************************
 *  Csm_MainFunction()
 *********************************************************************************************************************/
/*! \brief       Implements the API to be called cyclically to process the requested services. 
 *  \details     Calls the configured main function of the specific Cry service if requested.
 *  \pre         Csm is initialized.
 *  \context     TASK
 *  \reentrant   FALSE
 *  \synchronous TRUE
 *  \trace       CREQ-328
 *  \trace       SPEC-47430, SPEC-47264, SPEC-47547, SPEC-47251, SPEC-47498, SPEC-47207, SPEC-47328
 *********************************************************************************************************************/
FUNC( void, CSM_CODE ) Csm_MainFunction( void );

# if ( CSM_USE_INTERRUPTION == STD_ON )
/**********************************************************************************************************************
 *  Csm_Interruption()
 *********************************************************************************************************************/
/*! \brief       Interruption of processing.
 *  \details     The interruption feature is not implemented.
 *  \pre         Csm is initialized.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *********************************************************************************************************************/
FUNC( void, CSM_CODE ) Csm_Interruption( void );
# endif

# if ( CSM_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 *  Csm_GetVersionInfo()
 *********************************************************************************************************************/
/*! \brief       Retrieves the version information of the Csm module.
 *  \details     Stores version information, i.e. Module Id, Vendor Id, Vendor specific version numbers to structure
 *               pointed by Versioninfo.
 *  \param[in]   Versioninfo
 *  \pre         GetVersionInfo API is enabled via pre-compile configuration.
 *  \context     TASK
 *  \reentrant   TRUE
 *  \synchronous TRUE
 *  \trace       CREQ-327
 *  \trace       SPEC-47240, SPEC-47440, SPEC-47526
 *********************************************************************************************************************/
FUNC( void, CSM_CODE ) Csm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, CSM_APPL_VAR ) versioninfo );
# endif

# if ( (CSM_NUMBER_OF_HASH_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_HashStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the hash computation service.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23043
 *  \trace         SPEC-47186
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_HashStart( Csm_ConfigIdType cfgId );

/**********************************************************************************************************************
 *  Csm_HashUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the hash computation service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The hash computation is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     dataPtr      Holds a pointer to the data for which a hash value shall be computed.
 *  \param[in]     dataLength   Contains the number of bytes for which the hash value shall be computed.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23043
 *  \trace         SPEC-47402
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_HashUpdate( Csm_ConfigIdType cfgId,
                                                 P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                 uint32 dataLength );

/**********************************************************************************************************************
 *  Csm_HashFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the hash computation service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The hash computation is done by the underlying primitive.
 *  \param[in]     cfgId               Holds the identifier of the CSM module configuration.
 *  \param[out]    resultPtr           Holds a pointer to the memory location which will hold the hash value.
 *  \param[in,out] resultLengthPtr     Holds a pointer to the memory location in which the length information is
 *                                     stored.
 *  \param[in]     truncationIsAllowed This parameter states whether a truncation of the result is allowed or not.
 *                                     TRUE: truncation is allowed.
 *                                     FALSE: truncation is not allowed.
 *  \return        CSM_E_OK            Request successful
 *  \return        CSM_E_NOT_OK        Request failed
 *  \return        CSM_E_BUSY          Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23043
 *  \trace         SPEC-47525
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_HashFinish( Csm_ConfigIdType cfgId,
                                                 P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
                                                 P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) resultLengthPtr,
                                                 boolean truncationIsAllowed );
# endif

# if ( (CSM_NUMBER_OF_MAC_GENERATE_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_MacGenerateStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the MAC generation service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr       Holds a pointer to the key.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23049
 *  \trace         SPEC-47495
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_MacGenerateStart( Csm_ConfigIdType cfgId,
                                                       P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );

/**********************************************************************************************************************
 *  Csm_MacGenerateUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the MAC generation service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The MAC computation is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     dataPtr      Holds a pointer to the data for which a MAC shall be computed.
 *  \param[in]     dataLength   Contains the number of bytes for which the MAC shall be computed.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23049
 *  \trace         SPEC-47265
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_MacGenerateUpdate( Csm_ConfigIdType cfgId,
                                                        P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                        uint32 dataLength );

/**********************************************************************************************************************
 *  Csm_MacGenerateFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the MAC generation service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The MAC computation is done by the underlying primitive.
 *  \param[in]     cfgId               Holds the identifier of the CSM module configuration.
 *  \param[out]    resultPtr           Holds a pointer to the memory location which will hold the hash value.
 *  \param[in,out] resultLengthPtr     Holds a pointer to the memory location in which the length information is
 *                                     stored.
 *  \param[in]     truncationIsAllowed This parameter states whether a truncation of the result is allowed or not.
 *                                     TRUE: truncation is allowed.
 *                                     FALSE: truncation is not allowed.
 *  \return        CSM_E_OK            Request successful
 *  \return        CSM_E_NOT_OK        Request failed
 *  \return        CSM_E_BUSY          Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23049
 *  \trace         SPEC-47476
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_MacGenerateFinish( Csm_ConfigIdType cfgId,
                                                        P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
                                                        P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) resultLengthPtr,
                                                        boolean truncationIsAllowed );
# endif

# if ( (CSM_NUMBER_OF_MAC_VERIFY_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_MacVerifyStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the MAC verification service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr       Holds a pointer to the key.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23050
 *  \trace         SPEC-47519
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_MacVerifyStart( Csm_ConfigIdType cfgId,
                                                     P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );

/**********************************************************************************************************************
 *  Csm_MacVerifyUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the MAC verification service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 he MAC computation is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     dataPtr      Holds a pointer to the data for which a MAC shall be computed.
 *  \param[in]     dataLength   Contains the number of bytes for which the MAC shall be computed.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23050
 *  \trace         SPEC-47368
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_MacVerifyUpdate( Csm_ConfigIdType cfgId,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                      uint32 dataLength );

/**********************************************************************************************************************
 *  Csm_MacVerifyFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the MAC verification service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 he MAC computation is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[out]    MacPtr       Holds a pointer to the memory location which will hold the MAC to verify.
 *  \param[in,out] MacLength    Holds the length of the MAC to be verified.
 *  \param[in]     resultPtr    Holds a pointer to the memory location which will hold the MAC.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23050
 *  \trace         SPEC-47401
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_MacVerifyFinish( Csm_ConfigIdType cfgId,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) MacPtr,
                                                      uint32 MacLength,
                                                      P2VAR( Csm_VerifyResultType, AUTOMATIC, CSM_APPL_VAR ) resultPtr );
# endif

# if ( (CSM_NUMBER_OF_RANDOM_SEED_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_RandomSeedStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the random seed service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23052
 *  \trace         SPEC-47497
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_RandomSeedStart( Csm_ConfigIdType cfgId );

/**********************************************************************************************************************
 *  Csm_RandomSeedUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the random seed service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The seeding of the random number generator is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     seedPtr      Holds a pointer to the data for which a seed shall be computed.
 *  \param[in]     seedLength   Contains the number of bytes for which the seed shall be computed.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23052
 *  \trace         SPEC-47370
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_RandomSeedUpdate( Csm_ConfigIdType cfgId,
                                                       P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) seedPtr,
                                                       uint32 seedLength );

/**********************************************************************************************************************
 *  Csm_RandomSeedFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the random seed service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23052
 *  \trace         SPEC-47202
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_RandomSeedFinish( Csm_ConfigIdType cfgId );
# endif

# if ( (CSM_NUMBER_OF_RANDOM_GENERATE_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_RandomGenerate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to start the random number generation service of the CSM module.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive> of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *  \param[in]     cfgId                    Holds the identifier of the CSM module configuration.
 *  \param[out]    resultPtr                Holds a pointer to the memory location which will hold the random number.
 *  \param[in]     resultLength             Contains the number of bytes for which the random number shall be computed.
 *  \return        CSM_E_OK                 Request successful
 *  \return        CSM_E_NOT_OK             Request failed
 *  \return        CSM_E_BUSY               Request failed, service is busy
 *  \return        CSM_E_ENTROPY_EXHAUSTION request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23051
 *  \trace         SPEC-47353
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_RandomGenerate( Csm_ConfigIdType cfgId,
                                                     P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
                                                     uint32 resultLength );
# endif

# if ( (CSM_NUMBER_OF_SYM_BLOCK_ENCRYPT_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_SymBlockEncryptStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the symmetrical block encryption service of the CSM.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr       Holds a pointer to the key which has to be used.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23056
 *  \trace         SPEC-47348
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymBlockEncryptStart( Csm_ConfigIdType cfgId,
                                                           P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );

/**********************************************************************************************************************
 *  Csm_SymBlockEncryptUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the symmetrical block encryption service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The encryption process is done by the underlying primitive.
 *  \param[in]     cfgId               Holds the identifier of the CSM module configuration.
 *  \param[in]     plainTextPtr        Holds a pointer to the data for which a encrypted text shall be computed.
 *  \param[in]     plainTextLength     Contains the number of bytes for which the encrypted text shall be computed.
 *  \param[out]    cipherTextPtr       Holds a pointer to the memory location which will hold the encrypted text.
 *  \param[in,out] cipherTextLengthPtr Holds a pointer to the memory location in which the length information is
 *                                     stored.
 *  \return        CSM_E_OK            Request successful
 *  \return        CSM_E_NOT_OK        Request failed
 *  \return        CSM_E_BUSY          Request failed, service is busy
 *  \return        CSM_E_SMALL_BUFFER  The provided buffer is too small to store the result
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23056
 *  \trace         SPEC-47521
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymBlockEncryptUpdate( Csm_ConfigIdType cfgId,
                                                            P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                            uint32 plainTextLength,
                                                            P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                            P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr );

/**********************************************************************************************************************
 *  Csm_SymBlockEncryptFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the symmetrical block encryption service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The encryption process is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23056
 *  \trace         SPEC-47295
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymBlockEncryptFinish( Csm_ConfigIdType cfgId );
# endif

# if ( (CSM_NUMBER_OF_SYM_BLOCK_DECRYPT_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_SymBlockDecryptStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the symmetrical block decryption service of the CSM.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr       Holds a pointer to the key which has to be used.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23055
 *  \trace         SPEC-47345
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymBlockDecryptStart( Csm_ConfigIdType cfgId,
                                                           P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );

/**********************************************************************************************************************
 *  Csm_SymBlockDecryptUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the symmetrical block decryption service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The decryption process is done by the underlying primitive.
 *  \param[in]     cfgId              Holds the identifier of the CSM module configuration.
 *  \param[in]     cipherTextPtr      Holds a pointer to the data for which a decrypted text shall be computed.
 *  \param[in]     cipherTextLength   Contains the number of bytes for which the decrypted text shall be computed.
 *  \param[out]    plainTextPtr       Holds a pointer to the memory location which will hold the decrypted text.
 *  \param[in,out] plainTextLengthPtr Holds a pointer to the memory location in which the length information is stored.
 *  \return        CSM_E_OK           Request successful
 *  \return        CSM_E_NOT_OK       Request failed
 *  \return        CSM_E_BUSY         Request failed, service is busy
 *  \return        CSM_E_SMALL_BUFFER The provided buffer is too small to store the result
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23055
 *  \trace         SPEC-47371
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymBlockDecryptUpdate( Csm_ConfigIdType cfgId,
                                                            P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                            uint32 cipherTextLength,
                                                            P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                            P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr );

/**********************************************************************************************************************
 *  Csm_SymBlockDecryptFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the symmetrical block decryption service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The decryption process is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23055
 *  \trace         SPEC-47437
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymBlockDecryptFinish( Csm_ConfigIdType cfgId );
# endif

# if ( (CSM_NUMBER_OF_SYM_ENCRYPT_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_SymEncryptStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the symmetrical encryption service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId            Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr           Holds a pointer to the key which has to be used.
 *  \param[in]     InitVectorPtr    Holds a pointer to the initialisation vector which has to be used.
 *  \param[in]     InitVectorLength Contains the number of bytes provided as the initialisation vector.
 *  \return        CSM_E_OK         Request successful
 *  \return        CSM_E_NOT_OK     Request failed
 *  \return        CSM_E_BUSY       Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23058
 *  \trace         SPEC-47534
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymEncryptStart( Csm_ConfigIdType cfgId,
                                                      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) InitVectorPtr,
                                                      uint32 InitVectorLength );

/**********************************************************************************************************************
 *  Csm_SymEncryptUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the symmetrical encryption service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The encryption process is done by the underlying primitive.
 *  \param[in]     cfgId               Holds the identifier of the CSM module configuration.
 *  \param[in]     plainTextPtr        Holds a pointer to the data for which a encrypted text shall be computed.
 *  \param[in]     plainTextLength     Contains the number of bytes for which the encrypted text shall be computed.
 *  \param[out]    cipherTextPtr       Holds a pointer to the memory location which will hold the encrypted text.
 *  \param[in,out] cipherTextLengthPtr Holds a pointer to the memory location in which the length information is
 *                                     stored.
 *  \return        CSM_E_OK            Request successful
 *  \return        CSM_E_NOT_OK        Request failed
 *  \return        CSM_E_BUSY          Request failed, service is busy
 *  \return        CSM_E_SMALL_BUFFER  The provided buffer is too small to store the result
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23058
 *  \trace         SPEC-47447
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymEncryptUpdate( Csm_ConfigIdType cfgId,
                                                       P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                       uint32 plainTextLength,
                                                       P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                       P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr );

/**********************************************************************************************************************
 *  Csm_SymEncryptFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the symmetrical block encryption service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The encryption process is done by the underlying primitive.
 *  \param[in]     cfgId               Holds the identifier of the CSM module configuration.
 *  \param[in]     cipherTextPtr       Holds a pointer to the memory location which will hold the encrypted text.
 *  \param[in]     cipherTextLengthPtr Holds a pointer to the memory location in which the length information is
 *                                     stored.
 *  \return        CSM_E_OK            Request successful
 *  \return        CSM_E_NOT_OK        Request failed
 *  \return        CSM_E_BUSY          Request failed, service is busy
 *  \return        CSM_E_SMALL_BUFFER  Buffer is too small
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23058
 *  \trace         SPEC-47273
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymEncryptFinish( Csm_ConfigIdType cfgId,
                                                       P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                       P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr );
# endif

# if ( (CSM_NUMBER_OF_SYM_DECRYPT_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_SymDecryptStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the symmetrical encryption service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId            Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr           Holds a pointer to the key which has to be used.
 *  \param[in]     InitVectorPtr    Holds a pointer to the key which has to be used during the symmetrical encryption.
 *  \param[in]     InitVectorLength Holds a pointer to the initialisation vector which has to be used.
 *  \return        CSM_E_OK         Request successful
 *  \return        CSM_E_NOT_OK     Request failed
 *  \return        CSM_E_BUSY       Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23057
 *  \trace         SPEC-47563
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymDecryptStart( Csm_ConfigIdType cfgId,
                                                      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) InitVectorPtr,
                                                      uint32 InitVectorLength );

/**********************************************************************************************************************
 *  Csm_SymDecryptUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the symmetrical decryption service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The decryption process is done by the underlying primitive.
 *  \param[in]     cfgId              Holds the identifier of the CSM module configuration.
 *  \param[in]     cipherTextPtr      Holds a pointer to the data for which a decrypted text shall be computed.
 *  \param[in]     cipherTextLength   Contains the number of bytes for which the decrypted text shall be computed.
 *  \param[out]    plainTextPtr       Holds a pointer to the memory location which will hold the decrypted text.
 *  \param[in,out] plainTextLengthPtr Holds a pointer to the memory location in which the length information is stored.
 *  \return        CSM_E_OK           Request successful
 *  \return        CSM_E_NOT_OK       Request failed
 *  \return        CSM_E_BUSY         Request failed, service is busy
 *  \return        CSM_E_SMALL_BUFFER The provided buffer is too small to store the result
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23057
 *  \trace         SPEC-47464
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymDecryptUpdate( Csm_ConfigIdType cfgId,
                                                       P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                       uint32 cipherTextLength,
                                                       P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                       P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr );

/**********************************************************************************************************************
 *  Csm_SymDecryptFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the symmetrical decryption service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The decryption process is done by the underlying primitive.
 *  \param[in]     cfgId              Holds the identifier of the CSM module configuration.
 *  \param[in]     plainTextPtr       Holds a pointer to the memory location which will hold the decrypted text.
 *  \param[in]     plainTextLengthPtr Holds a pointer to the memory location in which the length information is stored.
 *  \return        CSM_E_OK           Request successful
 *  \return        CSM_E_NOT_OK       Request failed
 *  \return        CSM_E_BUSY         Request failed, service is busy
 *  \return        CSM_E_SMALL_BUFFER Buffer is too small
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23057
 *  \trace         SPEC-47568
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymDecryptFinish( Csm_ConfigIdType cfgId,
                                                       P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                       P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr );
# endif

# if ( (CSM_NUMBER_OF_ASYM_ENCRYPT_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_AsymEncryptStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the asymmetrical encryption service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr       Holds a pointer to the key which has to be used.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23036
 *  \trace         SPEC-47567
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymEncryptStart( Csm_ConfigIdType cfgId,
                                                       P2CONST( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );

/**********************************************************************************************************************
 *  Csm_AsymEncryptUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the asymmetrical encryption service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The encryption process is done by the underlying primitive.
 *  \param[in]     cfgId               Holds the identifier of the CSM module configuration.
 *  \param[in]     plainTextPtr        Holds a pointer to the data for which a encrypted text shall be computed.
 *  \param[in]     plainTextLength     Contains the number of bytes for which the encrypted text shall be computed.
 *  \param[out]    cipherTextPtr       Holds a pointer to the memory location which will hold the encrypted text.
 *  \param[in,out] cipherTextLengthPtr Holds a pointer to the memory location in which the length information is
 *                                     stored.
 *  \return        CSM_E_OK            Request successful
 *  \return        CSM_E_NOT_OK        Request failed
 *  \return        CSM_E_BUSY          Request failed, service is busy
 *  \return        CSM_E_SMALL_BUFFER  The provided buffer is too small to store the result
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23036
 *  \trace         SPEC-47529
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymEncryptUpdate( Csm_ConfigIdType cfgId,
                                                        P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                        uint32 plainTextLength,
                                                        P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                        P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr );

/**********************************************************************************************************************
 *  Csm_AsymEncryptFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the asymmetrical encryption service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The encryption process is done by the underlying primitive.
 *  \param[in]     cfgId               Holds the identifier of the CSM module configuration.
 *  \param[in]     cipherTextPtr       Holds a pointer to the memory location which will hold the encrypted text.
 *  \param[in]     cipherTextLengthPtr Holds a pointer to the memory location in which the length information is
 *                                     stored.
 *  \return        CSM_E_OK            Request successful
 *  \return        CSM_E_NOT_OK        Request failed
 *  \return        CSM_E_BUSY          Request failed, service is busy
 *  \return        CSM_E_SMALL_BUFFER  Buffer is too small
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23036
 *  \trace         SPEC-47340
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymEncryptFinish( Csm_ConfigIdType cfgId,
                                                        P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                        P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr );
# endif

# if ( (CSM_NUMBER_OF_ASYM_DECRYPT_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_AsymDecryptStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the asymmetrical decryption service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr       Holds a pointer to the key which has to be used.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23037
 *  \trace         SPEC-47199
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymDecryptStart( Csm_ConfigIdType cfgId,
                                                       P2CONST( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );

/**********************************************************************************************************************
 *  Csm_AsymDecryptUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the asymmetrical decryption service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The decryption process is done by the underlying primitive.
 *  \param[in]     cfgId              Holds the identifier of the CSM module configuration.
 *  \param[in]     cipherTextPtr      Holds a pointer to the data for which a decrypted text shall be computed.
 *  \param[in]     cipherTextLength   Contains the number of bytes for which the decrypted text shall be computed.
 *  \param[out]    plainTextPtr       Holds a pointer to the memory location which will hold the decrypted text.
 *  \param[in,out] plainTextLengthPtr Holds a pointer to the memory location in which the length information is stored.
 *  \return        CSM_E_OK           Request successful
 *  \return        CSM_E_NOT_OK       Request failed
 *  \return        CSM_E_BUSY         Request failed, service is busy
 *  \return        CSM_E_SMALL_BUFFER The provided buffer is too small to store the result
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23037
 *  \trace         SPEC-47194
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymDecryptUpdate( Csm_ConfigIdType cfgId,
                                                        P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
                                                        uint32 cipherTextLength,
                                                        P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                        P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr );

/**********************************************************************************************************************
 *  Csm_AsymDecryptFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the asymmetrical decryption service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 he decryption process is done by the underlying primitive.
 *  \param[in]     cfgId              Holds the identifier of the CSM module configuration.
 *  \param[in]     plainTextPtr       Holds a pointer to the memory location which will hold the decrypted text.
 *  \param[in]     plainTextLengthPtr Holds a pointer to the memory location in which the length information is stored.
 *  \return        CSM_E_OK           Request successful
 *  \return        CSM_E_NOT_OK       Request failed
 *  \return        CSM_E_BUSY         Request failed, service is busy
 *  \return        CSM_E_SMALL_BUFFER Buffer is too small
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23037
 *  \trace         SPEC-47463
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymDecryptFinish( Csm_ConfigIdType cfgId,
                                                        P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
                                                        P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr );
# endif

# if ( (CSM_NUMBER_OF_SIGNATURE_GENERATE_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_SignatureGenerateStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the signature generate service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr       Holds a pointer to the key which has to be used during the signature generation.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23053
 *  \trace         SPEC-47198
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SignatureGenerateStart( Csm_ConfigIdType cfgId,
                                                             P2CONST( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );

/**********************************************************************************************************************
 *  Csm_SignatureGenerateUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the signature generate service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The signature computation is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     dataPtr      Holds a pointer to the data for which a signature shall be computed.
 *  \param[in]     dataLength   Contains the number of bytes for which the signature shall be computed.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23053
 *  \trace         SPEC-47259
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SignatureGenerateUpdate( Csm_ConfigIdType cfgId,
                                                              P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                              uint32 dataLength );

/**********************************************************************************************************************
 *  Csm_SignatureGenerateFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the signature generate service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The signature computation is done by the underlying primitive.
 *  \param[in]     cfgId           Holds the identifier of the CSM module configuration.
 *  \param[out]    resultPtr       Holds a pointer to the memory location which will hold the signature.
 *  \param[in,out] resultLengthPtr Holds a pointer to the memory location in which the length information is stored.
 *  \return        CSM_E_OK        Request successful
 *  \return        CSM_E_NOT_OK    Request failed
 *  \return        CSM_E_BUSY      Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23053
 *  \trace         SPEC-47256
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SignatureGenerateFinish( Csm_ConfigIdType cfgId,
                                                              P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
                                                              P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) resultLengthPtr );
# endif

# if ( (CSM_NUMBER_OF_SIGNATURE_VERIFY_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_SignatureVerifyStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the signature verification service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr       Holds a pointer to the key which has to be used during the signature verification.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23054
 *  \trace         SPEC-47267
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SignatureVerifyStart( Csm_ConfigIdType cfgId,
                                                           P2CONST( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );

/**********************************************************************************************************************
 *  Csm_SignatureVerifyUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the signature verification service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The signature computation is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     dataPtr      Holds a pointer to the data for which a signature shall be computed.
 *  \param[in]     dataLength   Contains the number of bytes for which the signature shall be computed.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23054
 *  \trace         SPEC-47426
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SignatureVerifyUpdate( Csm_ConfigIdType cfgId,
                                                            P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                            uint32 dataLength );

/**********************************************************************************************************************
 *  Csm_SignatureVerifyFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the signature verification service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The signature computation is done by the underlying primitive.
 *  \param[in]     cfgId           Holds the identifier of the CSM module configuration.
 *  \param[in]     signaturePtr    Holds a pointer to the memory location which holds the signature to be verified.
 *  \param[in]     signatureLength Holds the length of the Signature to be verified.
 *  \param[out]    resultPtr       Holds a pointer to the memory location which will hold the result.
 *  \return        CSM_E_OK        Request successful
 *  \return        CSM_E_NOT_OK    Request failed
 *  \return        CSM_E_BUSY      Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23054
 *  \trace         SPEC-47460
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SignatureVerifyFinish( Csm_ConfigIdType cfgId,
                                                            P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) signaturePtr,
                                                            uint32 signatureLength,
                                                            P2VAR( Csm_VerifyResultType, AUTOMATIC, CSM_APPL_VAR ) resultPtr );
# endif

# if ( (CSM_NUMBER_OF_CHECKSUM_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_ChecksumStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the checksum generation service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23042
 *  \trace         SPEC-47333
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_ChecksumStart( Csm_ConfigIdType cfgId );

/**********************************************************************************************************************
 *  Csm_ChecksumUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the checksum generation service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The checksum computation is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     dataPtr      Holds a pointer to the data for which a checksum shall be computed.
 *  \param[in]     dataLength   Contains the number of bytes for which the checksum shall be computed.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23042
 *  \trace         SPEC-47482
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_ChecksumUpdate( Csm_ConfigIdType cfgId,
                                                     P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                     uint32 dataLength );

/**********************************************************************************************************************
 *  Csm_ChecksumFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the checksum generation service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The checksum computation is done by the underlying primitive.
 *  \param[in]     cfgId               Holds the identifier of the CSM module configuration.
 *  \param[out]    resultPtr           Holds a pointer to the memory location which will hold the checksum.
 *  \param[in,out] resultLengthPtr     Holds a pointer to the memory location in which the length information is
 *                                     stored.
 *  \param[in]     truncationIsAllowed This parameter states whether a truncation of the result is allowed or not.
 *                                     TRUE: truncation is allowed.
 *                                     FALSE: truncation is not allowed.
 *  \return        CSM_E_OK            Request successful
 *  \return        CSM_E_NOT_OK        Request failed
 *  \return        CSM_E_BUSY          Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23042
 *  \trace         SPEC-47406
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_ChecksumFinish( Csm_ConfigIdType cfgId,
                                                     P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
                                                     P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) resultLengthPtr,
                                                     boolean truncationIsAllowed );
# endif

# if ( (CSM_NUMBER_OF_KEY_DERIVE_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_KeyDeriveStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the Key Derivation service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     keyLength    Holds the length of the key to be derived by the underlying key derivation primitive.
 *  \param[in]     iterations   Holds the number of iterations to be performed by the underlying primitve.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23044
 *  \trace         SPEC-47417
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyDeriveStart( Csm_ConfigIdType cfgId,
                                                     uint32 keyLength,
                                                     uint32 iterations );

/**********************************************************************************************************************
 *  Csm_KeyDeriveUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the Key Derivation service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The key derivation computation is done by the underlying primitive.
 *  \param[in]     cfgId          Holds the identifier of the CSM module configuration.
 *  \param[in]     passwordPtr    Holds a pointer to the password, i.e. the original key, from which to derive a new
 *                                key.
 *  \param[in]     passwordLength Holds the length of the password in bytes.
 *  \param[in]     saltPtr        Holds a pointer to the cryptographic salt, i.e. a random number.
 *  \param[in]     saltLength     Holds the length of the salt in bytes.
 *  \return        CSM_E_OK       Request successful
 *  \return        CSM_E_NOT_OK   Request failed
 *  \return        CSM_E_BUSY     Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23044
 *  \trace         SPEC-47203
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyDeriveUpdate( Csm_ConfigIdType cfgId,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) passwordPtr,
                                                      uint32 passwordLength,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) saltPtr,
                                                      uint32 saltLength );

/**********************************************************************************************************************
 *  Csm_KeyDeriveFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the Key Derivation service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The key derivation computation is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in,out] keyPtr       Holds a pointer to the memory location which will hold the derived key.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23044
 *  \trace         SPEC-47313
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyDeriveFinish( Csm_ConfigIdType cfgId,
                                                      P2VAR( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
# endif

# if ( (CSM_NUMBER_OF_KEY_DERIVE_SYM_KEY_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_KeyDeriveSymKey()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the Key Derivation service of the CSM module.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive> of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *  \param[in]     cfgId                  Holds the identifier of the CSM module configuration.
 *  \param[in]     baseKeyPtr             Holds a pointer to the key from which the new key shall be derived.
 *  \param[in]     customisationValPtr    Holds a pointer to the customisation value (if any).
 *  \param[in]     customisationValLength Holds the length of the customisation value in bytes.
 *  \param[in,out] derivedKeyPtr          Holds a pointer to the memory location which will hold the key.
 *  \return        CSM_E_OK               Request successful
 *  \return        CSM_E_NOT_OK           Request failed
 *  \return        CSM_E_BUSY             Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23045
 *  \trace         SPEC-47297
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyDeriveSymKey( Csm_ConfigIdType cfgId,
                                                      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) baseKeyPtr,
                                                      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) customisationValPtr,
                                                      uint32 customisationValLength,
                                                      P2VAR( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) derivedKeyPtr );
# endif

# if ( (CSM_NUMBER_OF_KEY_EXCHANGE_CALC_PUB_VAL_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcPubVal()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the Key Derivation service of the CSM module.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive> of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *
 *  \param[in]     cfgId                Holds the identifier of the CSM module configuration.
 *  \param[in]     basePtr              Holds a pointer to the base information known to both users.
 *  \param[in]     privateValuePtr      Holds a pointer to the customisation value (if any).
 *  \param[in]     publicValuePtr       Holds the length of the customisation value in bytes.
 *  \param[in,out] publicValueLengthPtr Holds a pointer to the number of bytes for the input buffer and the number of
 *                                      actual written bytes if the request was successful.
 *  \return        CSM_E_OK             Request successful
 *  \return        CSM_E_NOT_OK         Request failed
 *  \return        CSM_E_BUSY           Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23046
 *  \trace         SPEC-47280
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcPubVal( Csm_ConfigIdType cfgId,
                                                            P2CONST( Csm_KeyExchangeBaseType, AUTOMATIC, CSM_APPL_VAR ) basePtr,
                                                            P2CONST( Csm_KeyExchangePrivateType, AUTOMATIC, CSM_APPL_VAR ) privateValuePtr,
                                                            P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) publicValuePtr,
                                                            P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) publicValueLengthPtr );
# endif

# if ( (CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SECRET_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSecretStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the Key Exchange service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId           Holds the identifier of the CSM module configuration.
 *  \param[in]     basePtr         Holds a pointer to the base information known to both users.
 *  \param[in]     privateValuePtr Holds a pointer to the private information known only to the current user.
 *  \return        CSM_E_OK        Request successful
 *  \return        CSM_E_NOT_OK    Request failed
 *  \return        CSM_E_BUSY      Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23047
 *  \trace         SPEC-47535
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcSecretStart( Csm_ConfigIdType cfgId,
                                                                 P2CONST( Csm_KeyExchangeBaseType, AUTOMATIC, CSM_APPL_VAR ) basePtr,
                                                                 P2CONST( Csm_KeyExchangePrivateType, AUTOMATIC, CSM_APPL_VAR ) privateValuePtr );

/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSecretUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the Key Exchange service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the shared secret is done by the underlying primitive.
 *  \param[in]     cfgId                    Holds the identifier of the CSM module configuration.
 *  \param[in]     partnerPublicValuePtr    Holds a pointer to the data representing the public value of the key
 *                                          exchange partner.
 *  \param[in]     partnerPublicValueLength Holds the length of the part of the partner value in bytes.
 *  \return        CSM_E_OK                 Request successful
 *  \return        CSM_E_NOT_OK             Request failed
 *  \return        CSM_E_BUSY               Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23047
 *  \trace         SPEC-47358
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcSecretUpdate( Csm_ConfigIdType cfgId,
                                                                  P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) partnerPublicValuePtr,
                                                                  uint32 partnerPublicValueLength );

/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSecretFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the checksum generation service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the shared secret is done by the underlying primitive.
 *  \param[in]     cfgId                 Holds the identifier of the CSM module configuration.
 *  \param[out]    sharedSecretPtr       Holds a pointer to the memory location which will hold the secret key.
 *  \param[in,out] sharedSecretLengthPtr Holds a pointer to the number of bytes for which a secret key shall be
 *                                       computed.
 *  \param[in]     truncationIsAllowed   This parameter states whether a truncation of the result is allowed or not.
 *                                       TRUE: truncation is allowed.
 *                                       FALSE: truncation is not allowed.
 *  \return        CSM_E_OK              Request successful
 *  \return        CSM_E_NOT_OK          Request failed
 *  \return        CSM_E_BUSY            Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23047
 *  \trace         SPEC-47268
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcSecretFinish( Csm_ConfigIdType cfgId,
                                                                  P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) sharedSecretPtr,
                                                                  P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) sharedSecretLengthPtr,
                                                                  boolean truncationIsAllowed );
# endif

# if ( (CSM_NUMBER_OF_KEY_EXCHANGE_CALC_SYM_KEY_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSymKeyStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the key exchange service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId           Holds the identifier of the CSM module configuration.
 *  \param[in]     basePtr         Holds a pointer to the base information known to both users.
 *  \param[in]     privateValuePtr Holds a pointer to the private information known only to the current user.
 *  \return        CSM_E_OK        Request successful
 *  \return        CSM_E_NOT_OK    Request failed
 *  \return        CSM_E_BUSY      Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23048
 *  \trace         SPEC-47286
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcSymKeyStart( Csm_ConfigIdType cfgId,
                                                                 P2CONST( Csm_KeyExchangeBaseType, AUTOMATIC, CSM_APPL_VAR ) basePtr,
                                                                 P2CONST( Csm_KeyExchangePrivateType, AUTOMATIC, CSM_APPL_VAR ) privateValuePtr );

/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSymKeyUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the key exchange service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *  \param[in]     cfgId                    Holds the identifier of the CSM module configuration.
 *  \param[in]     partnerPublicValuePtr    Holds a pointer to the data representing the public value of the key
 *                                          exchange partner.
 *  \param[in]     partnerPublicValueLength Holds the length of the part of the partner value in bytes.
 *  \return        CSM_E_OK                 Request successful
 *  \return        CSM_E_NOT_OK             Request failed
 *  \return        CSM_E_BUSY               Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23048
 *  \trace         SPEC-47219
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcSymKeyUpdate( Csm_ConfigIdType cfgId,
                                                                  P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) partnerPublicValuePtr,
                                                                  uint32 partnerPublicValueLength );

/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSymKeyFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the key exchange service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[out]    sharedKeyPtr Holds a pointer to the memory location which will hold the shared key.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23048
 *  \trace         SPEC-47453
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_KeyExchangeCalcSymKeyFinish( Csm_ConfigIdType cfgId,
                                                                  P2VAR( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) sharedKeyPtr );
# endif

# if ( (CSM_NUMBER_OF_SYM_KEY_EXTRACT_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_SymKeyExtractStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the symmetrical key extraction service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23059
 *  \trace         SPEC-47366
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyExtractStart( Csm_ConfigIdType cfgId );

/**********************************************************************************************************************
 *  Csm_SymKeyExtractUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the symmetrical key extraction service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     dataPtr      Holds a pointer to the data which contains the key.
 *  \param[in]     dataLength   Holds the length of the data in bytes.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23059
 *  \trace         SPEC-47301
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyExtractUpdate( Csm_ConfigIdType cfgId,
                                                          P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                          uint32 dataLength );

/**********************************************************************************************************************
 *  Csm_SymKeyExtractFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the key exchange service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[out]    keyPtr       Holds a pointer to a structure where the result (i.e. the symmetrical key) is stored.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23059
 *  \trace         SPEC-47507
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyExtractFinish( Csm_ConfigIdType cfgId,
                                                          P2VAR( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
# endif

# if ( (CSM_NUMBER_OF_SYM_KEY_WRAP_SYM_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_SymKeyWrapSymStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the symmetrical key wrapping service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId          Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr         Holds a pointer to the symmetric key to be wrapped.
 *  \param[in]     wrappingkeyPtr Holds a pointer to the key used for wrapping.
 *  \return        CSM_E_OK       Request successful
 *  \return        CSM_E_NOT_OK   Request failed
 *  \return        CSM_E_BUSY     Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23061
 *  \trace         SPEC-47276
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyWrapSymStart( Csm_ConfigIdType cfgId,
                                                         P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
                                                         P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) wrappingkeyPtr );

/**********************************************************************************************************************
 *  Csm_SymKeyWrapSymUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the symmetrical key wrapping service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId         Holds the identifier of the CSM module configuration.
 *  \param[in]     dataPtr       Holds a pointer to the data which contains the key.
 *  \param[in]     dataLengthPtr Holds a pointer to the memory location in which the length information is stored.
 *  \return        CSM_E_OK      Request successful
 *  \return        CSM_E_NOT_OK  Request failed
 *  \return        CSM_E_BUSY    Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23061
 *  \trace         SPEC-47536
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyWrapSymUpdate( Csm_ConfigIdType cfgId,
                                                          P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                          P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) dataLengthPtr );

/**********************************************************************************************************************
 *  Csm_SymKeyWrapSymFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the symmetrical key wrapping service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23061
 *  \trace         SPEC-47307
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyWrapSymFinish( Csm_ConfigIdType cfgId );
# endif

# if ( (CSM_NUMBER_OF_SYM_KEY_WRAP_ASYM_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_SymKeyWrapAsymStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the symmetrical key wrapping service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId          Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr         Holds a pointer to the symmetric key to be wrapped.
 *  \param[in]     wrappingkeyPtr Holds a pointer to the key used for wrapping.
 *  \return        CSM_E_OK       Request successful
 *  \return        CSM_E_NOT_OK   Request failed
 *  \return        CSM_E_BUSY     Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23060
 *  \trace         SPEC-47272
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyWrapAsymStart( Csm_ConfigIdType cfgId,
                                                          P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
                                                          P2CONST( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) wrappingkeyPtr );

/**********************************************************************************************************************
 *  Csm_SymKeyWrapAsymUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the symmetrical key wrapping service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId         Holds the identifier of the CSM module configuration.
 *  \param[out]    dataPtr       Holds a pointer to the data which contains the key.
 *  \param[in,out] dataLengthPtr Holds a pointer to the memory location in which the length information is stored.
 *  \return        CSM_E_OK      Request successful
 *  \return        CSM_E_NOT_OK  Request failed
 *  \return        CSM_E_BUSY    Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23060
 *  \trace         SPEC-47349
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyWrapAsymUpdate( Csm_ConfigIdType cfgId,
                                                           P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                           P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) dataLengthPtr );

/**********************************************************************************************************************
 *  Csm_SymKeyWrapAsymFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the symmetrical key wrapping service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23060
 *  \trace         SPEC-47383
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_SymKeyWrapAsymFinish( Csm_ConfigIdType cfgId );
# endif

# if ( (CSM_NUMBER_OF_ASYM_PUBLIC_KEY_EXTRACT_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_AsymPublicKeyExtractStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the public key extraction service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23041
 *  \trace         SPEC-47556
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPublicKeyExtractStart( Csm_ConfigIdType cfgId );

/**********************************************************************************************************************
 *  Csm_AsymPublicKeyExtractUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the public key extraction service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     dataPtr      Holds a pointer to the data which contains the key.
 *  \param[in]     dataLength   Holds the length of the data in bytes.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23041
 *  \trace         SPEC-47391
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPublicKeyExtractUpdate( Csm_ConfigIdType cfgId,
                                                                 P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                                 uint32 dataLength );

/**********************************************************************************************************************
 *  Csm_AsymPublicKeyExtractFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the public key extraction service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in,out] keyPtr       Holds a pointer to a structure where the result is stored in.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23041
 *  \trace         SPEC-47196
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPublicKeyExtractFinish( Csm_ConfigIdType cfgId,
                                                                 P2VAR( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
# endif

# if ( (CSM_NUMBER_OF_ASYM_PRIVATE_KEY_EXTRACT_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyExtractStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the private key extraction service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23038
 *  \trace         SPEC-47222
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyExtractStart( Csm_ConfigIdType cfgId );

/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyExtractUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the private key extraction service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in]     dataPtr      Holds a pointer to the data which contains the key.
 *  \param[in]     dataLength   Holds the length of the data in bytes.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23038
 *  \trace         SPEC-47336
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyExtractUpdate( Csm_ConfigIdType cfgId,
                                                                  P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                                  uint32 dataLength );

/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyExtractFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the private key extraction service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \param[in,out] keyPtr       Holds a pointer to a structure where the result is stored in.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23038
 *  \trace         SPEC-47258
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyExtractFinish( Csm_ConfigIdType cfgId,
                                                                  P2VAR( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
# endif

# if ( (CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_SYM_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapSymStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the asymmetrical key wrapping service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId          Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr         Holds a pointer to the private key to be wrapped.
 *  \param[in]     wrappingkeyPtr Holds a pointer to the public key used for wrapping.
 *  \return        CSM_E_OK       Request successful
 *  \return        CSM_E_NOT_OK   Request failed
 *  \return        CSM_E_BUSY     Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23040
 *  \trace         SPEC-47188
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyWrapSymStart( Csm_ConfigIdType cfgId,
                                                                 P2CONST( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
                                                                 P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) wrappingkeyPtr );

/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapSymUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the asymmetrical key wrapping service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId         Holds the identifier of the CSM module configuration.
 *  \param[in]     dataPtr       Holds a pointer to the data which contains the key.
 *  \param[in]     dataLengthPtr Holds a pointer to the memory location in which the length information is stored.
 *  \return        CSM_E_OK      Request successful
 *  \return        CSM_E_NOT_OK  Request failed
 *  \return        CSM_E_BUSY    Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23040
 *  \trace         SPEC-47472
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyWrapSymUpdate( Csm_ConfigIdType cfgId,
                                                                  P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                                  P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) dataLengthPtr );

/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapSymFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the asymmetrical key wrapping service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23040
 *  \trace         SPEC-47314
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyWrapSymFinish( Csm_ConfigIdType cfgId );
# endif

# if ( (CSM_NUMBER_OF_ASYM_PRIVATE_KEY_WRAP_ASYM_CONFIGS !=0) || ( CSM_DISABLE_NOT_USED_APIS == STD_OFF ) )
/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapAsymStart()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to initialize the asymmetrical key wrapping service of the CSM module.
 *  \details       If the service state is "active", the function shall return with "CSM_E_BUSY".
 *                 Otherwise, this function shall store the given configuration information which is identified by
 *                 "cfgId", call the function Cry_<Primitive>Start of the primitive which is identified by the "cfgId"
 *                 and return the value returned by that function. If Cry_<Primitive>Start returned successfully, the
 *                 service state has to be set to "active".
 *  \param[in]     cfgId          Holds the identifier of the CSM module configuration.
 *  \param[in]     keyPtr         Holds a pointer to the private key to be wrapped.
 *  \param[in]     wrappingkeyPtr Holds a pointer to the public key used for wrapping.
 *  \return        CSM_E_OK       Request successful
 *  \return        CSM_E_NOT_OK   Request failed
 *  \return        CSM_E_BUSY     Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is idle.
 *  \trace         DSGN-Csm23039
 *  \trace         SPEC-47218
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyWrapAsymStart( Csm_ConfigIdType cfgId,
                                                                  P2CONST( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
                                                                  P2CONST( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) wrappingkeyPtr );

/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapAsymUpdate()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to feed the asymmetrical key wrapping service with the input data.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Update of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId         Holds the identifier of the CSM module configuration.
 *  \param[in]     dataPtr       Holds a pointer to the data which contains the key.
 *  \param[in]     dataLengthPtr Holds a pointer to the memory location in which the length information is stored.
 *  \return        CSM_E_OK      Request successful
 *  \return        CSM_E_NOT_OK  Request failed
 *  \return        CSM_E_BUSY    Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23039
 *  \trace         SPEC-47195
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyWrapAsymUpdate( Csm_ConfigIdType cfgId,
                                                                   P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
                                                                   P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) dataLengthPtr );

/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapAsymFinish()
 *********************************************************************************************************************/
/*! \brief         This interface shall be used to finish the asymmetrical key wrapping service.
 *  \details       If the service state is "idle", the function has to return with "CSM_E_NOT_OK".
 *                 Otherwise, this function shall call the function Cry_<Primitive>Finish of the primitive which is
 *                 identified by the stored configuration information and return the value returned by that function.
 *                 The calculation of the extraction algorithm is done by the underlying primitive.
 *  \param[in]     cfgId        Holds the identifier of the CSM module configuration.
 *  \return        CSM_E_OK     Request successful
 *  \return        CSM_E_NOT_OK Request failed
 *  \return        CSM_E_BUSY   Request failed, service is busy
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   Depending on configuration.
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23039
 *  \trace         SPEC-47231
 *********************************************************************************************************************/
FUNC( Csm_ReturnType, CSM_CODE ) Csm_AsymPrivateKeyWrapAsymFinish( Csm_ConfigIdType cfgId );
# endif


# define CSM_STOP_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


# endif  /* CSM_H */

/**********************************************************************************************************************
 *  END OF FILE: CSM.H
 *********************************************************************************************************************/

