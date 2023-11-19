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
 *         File:  Cry_30_LibCv.c
 *    Component:  SysService_AsrCry
 *       Module:  MICROSAR Cryptographic library module (Cry)
 *    Generator:  -
 *
 *  Description:  Implements the Cry API for the ASR CSM
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

#define CRY_30_LIBCV_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Cry_30_LibCv.h"

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/
/* vendor specific version information is BCD coded */
#if (  (CRY_30_LIBCV_SW_MAJOR_VERSION != (0x03)) \
    || (CRY_30_LIBCV_SW_MINOR_VERSION != (0x00)) \
    || (CRY_30_LIBCV_SW_PATCH_VERSION != (0x01)) )
  #error "Vendor specific version numbers of Cry_30_LibCv.c and Cry_30_LibCv.h are inconsistent"
#endif

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 **********************************************************************************************************************/

#if !defined (CRY_30_LIBCV_LOCAL)
# define CRY_30_LIBCV_LOCAL static
#endif

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 **********************************************************************************************************************/

/**********************************************************************************************************************
 * Cry_30_LibCv_Init
**********************************************************************************************************************/
/*! \brief      Initialization function
 *  \context    Function could be called from task level only
 *  \note       Called by application
**********************************************************************************************************************/
FUNC (void, CRY_30_LIBCV_CODE) Cry_30_LibCv_Init( void )
{
  /* Initialize AES-128 encrypt */
# if ( CRY_30_LIBCV_AESENCRYPT128CONFIG == STD_ON )
  Cry_30_LibCv_AesEncrypt128Init();
# endif

  /* Initialize AES-128 decrypt */
# if ( CRY_30_LIBCV_AESDECRYPT128CONFIG == STD_ON )
  Cry_30_LibCv_AesDecrypt128Init();
# endif

  /* Initialize HMAC SHA-1 */
# if ( CRY_30_LIBCV_HMACSHA1VERIFYCONFIG == STD_ON )
  Cry_30_LibCv_HmacSha1Init();
# endif

  /* Initialize FIPS-186 */
# if ( CRY_30_LIBCV_FIPS186CONFIG == STD_ON )
  Cry_30_LibCv_Fips186Init();
# endif

  /* Initialize CmacAes128Gen */
# if ( CRY_30_LIBCV_CMACAES128GENCONFIG == STD_ON )
  Cry_30_LibCv_CmacAes128GenInit();
# endif

  /* Initialize CmacAes128Ver */
# if ( CRY_30_LIBCV_CMACAES128VERCONFIG == STD_ON )
  Cry_30_LibCv_CmacAes128VerInit();
# endif

}  /* PRQA S 6050 */ /* MD_MSR_STCAL */

/**********************************************************************************************************************
 * Cry_30_LibCv_InitMemory
**********************************************************************************************************************/
/*! \brief      Memory initialization function
 *  \context    Function could be called from task level only
 *  \note       Called by application
**********************************************************************************************************************/
FUNC (void, CRY_30_LIBCV_CODE) Cry_30_LibCv_InitMemory( void )
{

}

#if ( CRY_30_LIBCV_VERSION_INFO_API == STD_ON )
/**********************************************************************************************************************
 * Cry_30_LibCv_GetVersionInfo
**********************************************************************************************************************/
/*! \brief      This service returns the version information of this module.
 *  \param[out] cryVerInfoPtr          Pointer where to store the version information of this module.
 *  \context    Function could be called from task level only
 *  \note       Called by application
**********************************************************************************************************************/
FUNC( void, CRY_30_LIBCV_CODE ) Cry_30_LibCv_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, CRY_30_LIBCV_APPL_VAR ) cryVerInfoPtr )
{
  if( cryVerInfoPtr != NULL_PTR )
  {
    cryVerInfoPtr->vendorID = (uint16)CRY_30_LIBCV_VENDOR_ID;
    cryVerInfoPtr->moduleID = (uint8)CRY_30_LIBCV_MODULE_ID;
    cryVerInfoPtr->sw_major_version = (uint8)CRY_30_LIBCV_SW_MAJOR_VERSION;
    cryVerInfoPtr->sw_minor_version = (uint8)CRY_30_LIBCV_SW_MINOR_VERSION;
    cryVerInfoPtr->sw_patch_version = (uint8)CRY_30_LIBCV_SW_PATCH_VERSION;
  }
}
#endif /* ( CRY_30_LIBCV_VERSION_INFO_API == STD_ON ) */

/**********************************************************************************************************************
 *  END OF FILE: CRY_30_LIBCV.C
 *********************************************************************************************************************/
