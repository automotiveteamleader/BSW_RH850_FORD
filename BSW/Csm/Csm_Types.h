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
/**        \file  Csm_Types.h
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

#if !defined (CSM_TYPES_H)
#define CSM_TYPES_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Rte_Csm_Type.h"
#include "Csm_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/* --- Component Version Information ------------------------------------------------------------------------------- */
# define CSM_TYPES_MAJOR_VERSION     (2u)
# define CSM_TYPES_MINOR_VERSION     (2u)
# define CSM_TYPES_PATCH_VERSION     (3u)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
#ifndef Rte_TypeDef_Csm_ConfigIdType /* COV_CSM_NON_RTE */
typedef uint16 Csm_ConfigIdType;
#endif

#ifndef Rte_TypeDef_Csm_ReturnType /* COV_CSM_NON_RTE */
typedef uint8 Csm_ReturnType;
#endif

#ifndef CSM_E_OK /* COV_CSM_NON_RTE */
# define CSM_E_OK                  (0x00u)
#endif

#ifndef CSM_E_NOT_OK /* COV_CSM_NON_RTE */
# define CSM_E_NOT_OK              (0x01u)
#endif

#ifndef CSM_E_BUSY /* COV_CSM_NON_RTE */
# define CSM_E_BUSY                (0x02u)
#endif

#ifndef CSM_E_SMALL_BUFFER /* COV_CSM_NON_RTE */
# define CSM_E_SMALL_BUFFER        (0x03u)
#endif

#ifndef CSM_E_ENTROPY_EXHAUSTION /* COV_CSM_NON_RTE */
# define CSM_E_ENTROPY_EXHAUSTION  (0x04u)
#endif

typedef P2FUNC(Std_ReturnType, CSM_APPL_CODE, Csm_CallbackType)(Csm_ReturnType);

#if ( CSM_MAX_ALIGN_SCALAR_TYPE == 8 )
typedef uint8  Csm_AlignType;
#else
# if ( CSM_MAX_ALIGN_SCALAR_TYPE == 16 )
typedef uint16 Csm_AlignType;
# else
typedef uint32 Csm_AlignType;
# endif
#endif

#ifndef Rte_TypeDef_Csm_VerifyResultType /* COV_CSM_NON_RTE */
typedef uint8 Csm_VerifyResultType;
#endif

#ifndef CSM_E_VER_OK /* COV_CSM_NON_RTE */
# define CSM_E_VER_OK              (0x00u)
#endif

#ifndef CSM_E_VER_NOT_OK /* COV_CSM_NON_RTE */
# define CSM_E_VER_NOT_OK          (0x01u)
#endif

typedef struct
{
    uint32 length;
    Csm_AlignType data[CSM_ASYM_PUB_KEY_MAX_SIZE];
} Csm_AsymPublicKeyType;

typedef struct
{
    uint32 length;
    Csm_AlignType data[CSM_ASYM_PRIV_KEY_MAX_SIZE];
} Csm_AsymPrivateKeyType;

typedef struct
{
    uint32 length;
    Csm_AlignType data[CSM_SYM_KEY_MAX_SIZE];
} Csm_SymKeyType;

typedef struct
{
    uint32 length;
    Csm_AlignType data[CSM_KEY_EX_BASE_MAX_SIZE];
} Csm_KeyExchangeBaseType;

typedef struct
{
    uint32 length;
    Csm_AlignType data[CSM_KEY_EX_PRIV_MAX_SIZE];
} Csm_KeyExchangePrivateType;


/* Service Config Types */
typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      uint32 dataLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) resultLengthPtr,
      boolean truncationIsAllowed );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_HashConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      uint32 dataLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) resultLengthPtr,
      boolean truncationIsAllowed );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_MacGenerateConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      uint32 dataLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) MacPtr,
      uint32 MacLength,
      P2VAR( Csm_VerifyResultType, AUTOMATIC, CSM_APPL_VAR ) resultPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_MacVerifyConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) seedPtr,
      uint32 seedLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_RandomSeedConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
      uint32 resultLength );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_RandomGenerateConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
      uint32 plainTextLength,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_SymBlockEncryptConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
      uint32 cipherTextLength,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_SymBlockDecryptConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) InitVectorPtr,
      uint32 InitVectorLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
      uint32 plainTextLength,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_SymEncryptConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) InitVectorPtr,
      uint32 InitVectorLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
      uint32 cipherTextLength,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_SymDecryptConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
      uint32 plainTextLength,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) cipherTextLengthPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_AsymEncryptConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) cipherTextPtr,
      uint32 cipherTextLength,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) plainTextPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) plainTextLengthPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_AsymDecryptConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      uint32 dataLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) resultLengthPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_SignatureGenerateConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      uint32 dataLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) signaturePtr,
      uint32 signatureLength,
      P2VAR( Csm_VerifyResultType, AUTOMATIC, CSM_APPL_VAR ) resultPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_SignatureVerifyConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      uint32 dataLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) resultPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) resultLengthPtr,
      boolean truncationIsAllowed );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_ChecksumConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      uint32 keyLength,
      uint32 iterations );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) passwordPtr,
      uint32 passwordLength,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) saltPtr,
      uint32 saltLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_KeyDeriveConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) baseKeyPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) customisationValPtr,
      uint32 customisationValLength,
      P2VAR( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) derivedKeyPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_KeyDeriveSymKeyConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_KeyExchangeBaseType, AUTOMATIC, CSM_APPL_VAR ) basePtr,
      P2CONST( Csm_KeyExchangePrivateType, AUTOMATIC, CSM_APPL_VAR ) privateValuePtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) publicValuePtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) publicValueLengthPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_KeyExchangeCalcPubValConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_KeyExchangeBaseType, AUTOMATIC, CSM_APPL_VAR ) basePtr,
      P2CONST( Csm_KeyExchangePrivateType, AUTOMATIC, CSM_APPL_VAR ) privateValuePtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) partnerPublicValuePtr,
      uint32 partnerPublicValueLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) sharedSecretPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) sharedSecretLengthPtr,
      boolean truncationIsAllowed );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_KeyExchangeCalcSecretConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_KeyExchangeBaseType, AUTOMATIC, CSM_APPL_VAR ) basePtr,
      P2CONST( Csm_KeyExchangePrivateType, AUTOMATIC, CSM_APPL_VAR ) privateValuePtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) partnerPublicValuePtr,
      uint32 partnerPublicValueLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) sharedKeyPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_KeyExchangeCalcSymKeyConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      uint32 dataLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_SymKeyExtractConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) wrappingkeyPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) dataLengthPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_SymKeyWrapSymConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
      P2CONST( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) wrappingkeyPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) dataLengthPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_SymKeyWrapAsymConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      uint32 dataLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_AsymPublicKeyExtractConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      uint32 dataLength );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_AsymPrivateKeyExtractConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
      P2CONST( Csm_SymKeyType, AUTOMATIC, CSM_APPL_VAR ) wrappingkeyPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) dataLengthPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_AsymPrivateKeyWrapSymConfigType;

typedef struct
{
  Csm_ConfigIdType  ConfigId;
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  Csm_CallbackType  CallbackFct;
# endif
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveStartFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2CONST( Csm_AsymPrivateKeyType, AUTOMATIC, CSM_APPL_VAR ) keyPtr,
      P2CONST( Csm_AsymPublicKeyType, AUTOMATIC, CSM_APPL_VAR ) wrappingkeyPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveUpdateFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr,
      P2VAR( uint8, AUTOMATIC, CSM_APPL_VAR ) dataPtr,
      P2VAR( uint32, AUTOMATIC, CSM_APPL_VAR ) dataLengthPtr );
  P2FUNC(Csm_ReturnType, CSM_CODE, PrimitiveFinishFct)
    ( P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) cfgPtr );
# if ( CSM_USE_SYNC_JOB_PROCESSING == STD_OFF )
  P2FUNC( void, CSM_CODE, PrimitiveMainFct)( void );
# endif
  P2CONST( void, AUTOMATIC, CSM_APPL_VAR ) PrimitiveConfigPtr;
} Csm_AsymPrivateKeyWrapAsymConfigType;

/* End of Service Config Types */

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

#endif  /* CSM_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: CSM_TYPES.H
 *********************************************************************************************************************/

