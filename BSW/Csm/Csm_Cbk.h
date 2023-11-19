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
/**        \file  Csm_Cbk.h
 *        \brief  MICROSAR Crypto Service Manager (CSM)
 *
 *      \details  Implementation of the MICROSAR Crypto Service Manager (CSM)
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the module's header file (Csm.h).
 *
 *  FILE VERSION
 *  -------------------------------------------------------------------------------------------------------------------
 *  Refer to the VERSION CHECK below.
 *********************************************************************************************************************/

#if !defined (CSM_CBK_H)
#define CSM_CBK_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Csm_Types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* --- Component Version Information ------------------------------------------------------------------------------- */
# define CSM_CBK_MAJOR_VERSION     (2u)
# define CSM_CBK_MINOR_VERSION     (2u)
# define CSM_CBK_PATCH_VERSION     (3u)


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA CBK AND STRUCTURES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOCBK
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOCBK
 *********************************************************************************************************************/
#define CSM_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Service Callbacks */
/**********************************************************************************************************************
 *  Csm_HashCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_HashCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service Hash
 *                 with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23043
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_HashCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_HashServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_HashServiceFinishNotification.
 *  \details       This function shall set the state of the service Hash to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23043
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_HashServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_MacGenerateCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_MacGenerateCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 MacGenerate with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23049
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_MacGenerateCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_MacGenerateServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_MacGenerateServiceFinishNotification.
 *  \details       This function shall set the state of the service MacGenerate to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23049
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_MacGenerateServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_MacVerifyCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_MacVerifyCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 MacVerify with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23050
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_MacVerifyCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_MacVerifyServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_MacVerifyServiceFinishNotification.
 *  \details       This function shall set the state of the service MacVerify to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23050
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_MacVerifyServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_RandomSeedCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_RandomSeedCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 RandomSeed with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23052
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_RandomSeedCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_RandomSeedServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_RandomSeedServiceFinishNotification.
 *  \details       This function shall set the state of the service RandomSeed to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23052
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_RandomSeedServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_RandomGenerateCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_RandomGenerateCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 RandomGenerate with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23051
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_RandomGenerateCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_RandomGenerateServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_RandomGenerateServiceFinishNotification.
 *  \details       This function shall set the state of the service RandomGenerate to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23051
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_RandomGenerateServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_SymBlockEncryptCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymBlockEncryptCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 SymBlockEncrypt with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23056
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymBlockEncryptCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_SymBlockEncryptServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymBlockEncryptServiceFinishNotification.
 *  \details       This function shall set the state of the service SymBlockEncrypt to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23056
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymBlockEncryptServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_SymBlockDecryptCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymBlockDecryptCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 SymBlockDecrypt with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23055
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymBlockDecryptCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_SymBlockDecryptServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymBlockDecryptServiceFinishNotification.
 *  \details       This function shall set the state of the service SymBlockDecrypt to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23055
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymBlockDecryptServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_SymEncryptCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymEncryptCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 SymEncrypt with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23058
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymEncryptCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_SymEncryptServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymEncryptServiceFinishNotification.
 *  \details       This function shall set the state of the service SymEncrypt to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23058
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymEncryptServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_SymDecryptCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymDecryptCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 SymDecrypt with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23057
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymDecryptCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_SymDecryptServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymDecryptServiceFinishNotification.
 *  \details       This function shall set the state of the service SymDecrypt to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23057
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymDecryptServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_AsymEncryptCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_AsymEncryptCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 AsymEncrypt with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23036
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_AsymEncryptCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_AsymEncryptServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_AsymEncryptServiceFinishNotification.
 *  \details       This function shall set the state of the service AsymEncrypt to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23036
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_AsymEncryptServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_AsymDecryptCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_AsymDecryptCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 AsymDecrypt with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23037
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_AsymDecryptCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_AsymDecryptServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_AsymDecryptServiceFinishNotification.
 *  \details       This function shall set the state of the service AsymDecrypt to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23037
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_AsymDecryptServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_SignatureGenerateCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SignatureGenerateCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 SignatureGenerate with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23053
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SignatureGenerateCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_SignatureGenerateServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SignatureGenerateServiceFinishNotification.
 *  \details       This function shall set the state of the service SignatureGenerate to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23053
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SignatureGenerateServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_SignatureVerifyCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SignatureVerifyCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 SignatureVerify with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23054
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SignatureVerifyCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_SignatureVerifyServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SignatureVerifyServiceFinishNotification.
 *  \details       This function shall set the state of the service SignatureVerify to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23054
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SignatureVerifyServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_ChecksumCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_ChecksumCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service Checksum
 *                 with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23042
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_ChecksumCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_ChecksumServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_ChecksumServiceFinishNotification.
 *  \details       This function shall set the state of the service Checksum to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23042
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_ChecksumServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_KeyDeriveCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_KeyDeriveCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 KeyDerive with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23044
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_KeyDeriveCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_KeyDeriveServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_KeyDeriveServiceFinishNotification.
 *  \details       This function shall set the state of the service KeyDerive to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23044
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_KeyDeriveServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_KeyDeriveSymKeyCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_KeyDeriveSymKeyCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 KeyDeriveSymKey with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23045
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_KeyDeriveSymKeyCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_KeyDeriveSymKeyServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_KeyDeriveSymKeyServiceFinishNotification.
 *  \details       This function shall set the state of the service KeyDeriveSymKey to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23045
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_KeyDeriveSymKeyServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcPubValCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_KeyExchangeCalcPubValCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 KeyExchangeCalcPubVal with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23046
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_KeyExchangeCalcPubValCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcPubValServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_KeyExchangeCalcPubValServiceFinishNotification.
 *  \details       This function shall set the state of the service KeyExchangeCalcPubVal to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23046
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_KeyExchangeCalcPubValServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSecretCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_KeyExchangeCalcSecretCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 KeyExchangeCalcSecret with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23047
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_KeyExchangeCalcSecretCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSecretServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_KeyExchangeCalcSecretServiceFinishNotification.
 *  \details       This function shall set the state of the service KeyExchangeCalcSecret to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23047
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_KeyExchangeCalcSecretServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSymKeyCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_KeyExchangeCalcSymKeyCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 KeyExchangeCalcSymKey with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23048
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_KeyExchangeCalcSymKeyCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_KeyExchangeCalcSymKeyServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_KeyExchangeCalcSymKeyServiceFinishNotification.
 *  \details       This function shall set the state of the service KeyExchangeCalcSymKey to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23048
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_KeyExchangeCalcSymKeyServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_SymKeyExtractCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymKeyExtractCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 SymKeyExtract with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23059
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymKeyExtractCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_SymKeyExtractServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymKeyExtractServiceFinishNotification.
 *  \details       This function shall set the state of the service SymKeyExtract to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23059
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymKeyExtractServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_SymKeyWrapSymCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymKeyWrapSymCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 SymKeyWrapSym with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23061
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymKeyWrapSymCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_SymKeyWrapSymServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymKeyWrapSymServiceFinishNotification.
 *  \details       This function shall set the state of the service SymKeyWrapSym to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23061
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymKeyWrapSymServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_SymKeyWrapAsymCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymKeyWrapAsymCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 SymKeyWrapAsym with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23060
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymKeyWrapAsymCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_SymKeyWrapAsymServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_SymKeyWrapAsymServiceFinishNotification.
 *  \details       This function shall set the state of the service SymKeyWrapAsym to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23060
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_SymKeyWrapAsymServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_AsymPublicKeyExtractCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_AsymPublicKeyExtractCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 AsymPublicKeyExtract with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23041
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_AsymPublicKeyExtractCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_AsymPublicKeyExtractServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_AsymPublicKeyExtractServiceFinishNotification.
 *  \details       This function shall set the state of the service AsymPublicKeyExtract to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23041
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_AsymPublicKeyExtractServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyExtractCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_AsymPrivateKeyExtractCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 AsymPrivateKeyExtract with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23038
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_AsymPrivateKeyExtractCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyExtractServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_AsymPrivateKeyExtractServiceFinishNotification.
 *  \details       This function shall set the state of the service AsymPrivateKeyExtract to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23038
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_AsymPrivateKeyExtractServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapSymCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_AsymPrivateKeyWrapSymCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 AsymPrivateKeyWrapSym with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23040
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_AsymPrivateKeyWrapSymCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapSymServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_AsymPrivateKeyWrapSymServiceFinishNotification.
 *  \details       This function shall set the state of the service AsymPrivateKeyWrapSym to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23040
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_AsymPrivateKeyWrapSymServiceFinishNotification( void );

/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapAsymCallbackNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_AsymPrivateKeyWrapAsymCallbackNotification.
 *  \details       This function shall call the callback function as given in the configuration of the service
 *                 AsymPrivateKeyWrapAsym with the argument given by "Result".
 *  \param[in]     Result Contains the result of a cryptographic operation.
 *                        CSM_E_OK: request successful
 *                        CSM_E_NOT_OK: request failed
 *                        CSM_E_BUSY: request failed, service is still busy
 *                        CSM_E_SMALL_BUFFER: the provided buffer is too small to store the result
 *                        CSM_E_ENTROPY_EXHAUSTION: request failed, entropy of randum number generator is exhausted.
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23039
 *  \trace         SPEC-47302
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_AsymPrivateKeyWrapAsymCallbackNotification( Csm_ReturnType Result );

/**********************************************************************************************************************
 *  Csm_AsymPrivateKeyWrapAsymServiceFinishNotification()
 *********************************************************************************************************************/
/*! \brief         Implements Csm_AsymPrivateKeyWrapAsymServiceFinishNotification.
 *  \details       This function shall set the state of the service AsymPrivateKeyWrapAsym to "idle".
 *  \context       TASK
 *  \reentrant     FALSE
 *  \synchronous   FALSE
 *  \pre           Service is started.
 *  \trace         DSGN-Csm23039
 *  \trace         SPEC-47211
 *********************************************************************************************************************/
extern FUNC( void, CSM_CODE ) Csm_AsymPrivateKeyWrapAsymServiceFinishNotification( void );

#define CSM_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif  /* CSM_CBK_H */

/**********************************************************************************************************************
 *  END OF FILE: CSM_CBK.H
 *********************************************************************************************************************/

