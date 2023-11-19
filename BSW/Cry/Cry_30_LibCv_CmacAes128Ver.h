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
 *         File:  Cry_30_LibCv_CmacAes128Ver.h
 *    Component:  SysService_AsrCry
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  This header file implements the CmacAes128Ver CRY API for the ASR CSM
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

#if !defined (CRY_CMACAES128VER_H)
#define CRY_CMACAES128VER_H

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Csm_Types.h"

/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#define CRY_30_LIBCV_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern FUNC( void, CRY_30_LIBCV_CODE) Cry_30_LibCv_CmacAes128VerInit( void );
extern FUNC( void, CRY_30_LIBCV_CODE) Cry_30_LibCv_CmacAes128VerMainFunction( void );

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
extern FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128VerStart( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                  P2CONST( Csm_SymKeyType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) keyPtr);

extern FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128VerUpdate( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                   P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) dataPtr,
                                                                                   uint32 dataLength);

extern FUNC( Csm_ReturnType, CRY_30_LIBCV_CODE ) Cry_30_LibCv_CmacAes128VerFinish( P2CONST( void, AUTOMATIC, CRY_30_LIBCV_APPL_VAR) cfgPtr,
                                                                                   P2CONST( uint8, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) MacPtr,
                                                                                   uint32 MacLength,
                                                                                   P2VAR( Csm_VerifyResultType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) resultPtr);

#define CRY_30_LIBCV_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif  /* CRY_CMACAES128VER_H */
/**********************************************************************************************************************
 *  END OF FILE: CRY_CMACAES128VER.H
 *********************************************************************************************************************/

