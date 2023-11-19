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
 *         File:  Cry_30_Rh850Icum.c
 *    Component:  DrvCry_Rh850Icum
 *       Module:  MICROSAR Cryptographic library module (CRY)
 *    Generator:  -
 *
 *  Description:  Implements the CRY API for the ICUM.
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

#define CRY_30_RH850ICUM_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_Rh850Icum.h"
#include "Cry_30_Rh850Icum_CommonUtil.h"
#include "r_icumif.api.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if (  (CRY_30_RH850ICUM_SW_MAJOR_VERSION != (0x01)) \
    || (CRY_30_RH850ICUM_SW_MINOR_VERSION != (0x00)) \
    || (CRY_30_RH850ICUM_SW_PATCH_VERSION != (0x00)) )
  #error "Vendor specific version numbers of Cry_Rh850Icum.c and Cry_30_Rh850Icum.h are inconsistent"
#endif


/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

#if !defined (CRY_30_RH850ICUM_LOCAL)
# define CRY_30_RH850ICUM_LOCAL static
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Cry_Init
**********************************************************************************************************************/
/*! \brief      Initialization function
 *  \context    Function could be called from task level only
 *  \note       Called by application
**********************************************************************************************************************/
FUNC (void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_Init( void )
{
  r_icumif_isd_t * p_ISD = &ISD;
  uint8 buffer[16u];

  /* Initialize interface to ICU-M (is unmasking the interrupt from the ICU-M) */
  R_ICUMIF_Init();

  p_ISD->service_id = SERVICE_00_GET_INFO;
  p_ISD->p_callbackfunc = 0u;
  p_ISD->job_id = 0u;
  p_ISD->prm.GET_INFO.info_id = INFO_RUN_TIME_MODE;
  p_ISD->prm.GET_INFO.p_info = buffer;

  Cry_30_Rh850Icum_TriggerServiceAndWait(p_ISD);

  /* Initialize AES-128 encrypt */
#if ( CRY_30_RH850ICUM_AESENCRYPT128CONFIG == STD_ON )
  Cry_30_Rh850Icum_AesEncrypt128Init();
#endif

  /* Initialize AES-128 decrypt */
#if ( CRY_30_RH850ICUM_AESDECRYPT128CONFIG == STD_ON )
  Cry_30_Rh850Icum_AesDecrypt128Init();
#endif

  /* Initialize CMAC Generation */
#if ( CRY_30_RH850ICUM_CMACAES128GENCONFIG == STD_ON )
  Cry_30_Rh850Icum_CmacAes128GenInit();
#endif

  /* Initialize CMAC Verification */
#if ( CRY_30_RH850ICUM_CMACAES128VERCONFIG == STD_ON )
  Cry_30_Rh850Icum_CmacAes128VerInit();
#endif

  /* Initialize PRNG */
#if ( CRY_30_RH850ICUM_RNGCONFIG == STD_ON )
  Cry_30_Rh850Icum_RngInit();
#endif

  /* Initialize KeyExtract */
#if ( CRY_30_RH850ICUM_KEYEXTRACTCONFIG == STD_ON )
  Cry_30_Rh850Icum_KeyExtractInit();
#endif

  /* Initialize KeyWrapSym */
#if ( CRY_30_RH850ICUM_KEYWRAPSYMCONFIG == STD_ON )
  Cry_30_Rh850Icum_KeyWrapSymInit();
#endif

#if ( (CRY_30_RH850ICUM_AESDECRYPT128CONFIG == STD_ON) \
   || (CRY_30_RH850ICUM_AESENCRYPT128CONFIG == STD_ON) \
   || (CRY_30_RH850ICUM_CMACAES128GENCONFIG == STD_ON) \
   || (CRY_30_RH850ICUM_CMACAES128VERCONFIG == STD_ON) \
   || (CRY_30_RH850ICUM_KEYEXTRACTCONFIG == STD_ON) \
   || (CRY_30_RH850ICUM_KEYWRAPSYMCONFIG == STD_ON) \
   || (CRY_30_RH850ICUM_RNGCONFIG == STD_ON) )
  Cry_30_Rh850Icum_ServiceState = CRY_30_RH850ICUM_SERVICE_IDLE;
#endif
}  /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 * Cry_InitMemory
**********************************************************************************************************************/
/*! \brief      Memory initialization function
 *  \context    Function could be called from task level only
 *  \note       Called by application
**********************************************************************************************************************/
FUNC (void, CRY_30_RH850ICUM_CODE) Cry_30_Rh850Icum_InitMemory( void )
{

}

#if ( CRY_30_RH850ICUM_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 * Cry_30_Rh850Icum_GetVersionInfo
**********************************************************************************************************************/
/*! \brief      This service returns the version information of this module.
 *  \param[out] cryVerInfoPtr          Pointer where to store the version information of this module.
 *  \context    Function could be called from task level only
 *  \note       Called by application
**********************************************************************************************************************/
FUNC( void, CRY_30_RH850ICUM_CODE ) Cry_30_Rh850Icum_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, CRY_30_RH850ICUM_APPL_VAR ) cryVerInfoPtr )
{
  if( cryVerInfoPtr != NULL_PTR )
  {
    cryVerInfoPtr->vendorID = (uint16)CRY_30_RH850ICUM_VENDOR_ID;
    cryVerInfoPtr->moduleID = (uint8)CRY_30_RH850ICUM_MODULE_ID;
    cryVerInfoPtr->sw_major_version = (uint8)CRY_30_RH850ICUM_SW_MAJOR_VERSION;
    cryVerInfoPtr->sw_minor_version = (uint8)CRY_30_RH850ICUM_SW_MINOR_VERSION;
    cryVerInfoPtr->sw_patch_version = (uint8)CRY_30_RH850ICUM_SW_PATCH_VERSION;
  }
}
#endif /* ( CRY_30_RH850ICUM_VERSION_INFO_API == STD_ON ) */

/**********************************************************************************************************************
 *  END OF FILE: CRY.C
 *********************************************************************************************************************/
