/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Dcm_CoreInt.h
 *        \brief  Private data type definition and interface of DCM
 *
 *      \details  MICROSAR DCM based on AR 4.0.3
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
#if !defined(DCM_COREINT_H)
# define DCM_COREINT_H
/* ----------------------------------------------
 ~&&&   Versions
---------------------------------------------- */

/*! Implementation version */
# define DCM_COREINT_MAJOR_VERSION                                   7u
# define DCM_COREINT_MINOR_VERSION                                   2u
# define DCM_COREINT_PATCH_VERSION                                   0u
/* ----------------------------------------------
 ~&&&   Switches
---------------------------------------------- */
/* Verify supported valid AR BSW environments */
# if (DCM_BSW_ENV_ASR_VERSION_4XX_ENABLED == STD_ON) || \
     (DCM_BSW_ENV_ASR_VERSION_3XX_ENABLED == STD_ON) || \
     (DCM_BSW_ENV_ASR_VERSION_401_ENABLED == STD_ON)                                                                                                 /* COV_DCM_SUPPORT_PARTIALLY TX tf xf tf */
/* everything OK */
# else
#  error "Unknown Autosar BSW environment version!"
# endif
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) || \
     (DCM_DIAG_VIRTUAL_REQUEST_ENABLED == STD_ON)                                                                                                    /* COV_DCM_UNSUPPORTED TF xf tf */
#  define DCM_NET_INTERNAL_REQ_ENABLED                               STD_ON
# else
#  define DCM_NET_INTERNAL_REQ_ENABLED                               STD_OFF
# endif

# if (DCM_NET_MULTI_PROTOCOL_ENABLED == STD_ON) || \
     (DCM_NET_MONITOR_FOREIGN_N_TA_ENABLED    == STD_ON)
#  define DCM_NET_TASK_RX_ENABLED                                    STD_ON
# else
#  define DCM_NET_TASK_RX_ENABLED                                    STD_OFF
# endif
# if (DCM_MODEMGR_SUPPORT_ENABLED == STD_ON)                                                                                                         /* COV_DCM_SUPPORT_ALWAYS TX */
#  if (DCM_MODE_CTRLDTCSETTING_MONITOR_ENABLED == STD_ON) || \
      (DCM_MODE_COMMCTRL_MONITOR_ENABLED == STD_ON)
#   define DCM_MODEMGR_MONITORING_ENABLED                            STD_ON
#  else
#   define DCM_MODEMGR_MONITORING_ENABLED                            STD_OFF
#  endif
# endif /* (DCM_MODEMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_DEMAPIMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_SVC_14_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_UDS_CLEAR_DTC_ENABLED                          STD_ON
#  else
#   define DCM_DEMAPI_UDS_CLEAR_DTC_ENABLED                          STD_OFF
#  endif

#  if (DCM_SVC_04_SUPPORT_ENABLED == STD_ON)                                                                                                         /* COV_DCM_UNSUPPORTED XF */
#   define DCM_DEMAPI_OBD_CLEAR_DTC_ENABLED                          STD_ON
#  else
#   define DCM_DEMAPI_OBD_CLEAR_DTC_ENABLED                          STD_OFF
#  endif

#  if (DCM_SVC_19_01_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_07_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_11_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_12_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED     STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED     STD_OFF
#  endif

#  if (DCM_SVC_19_02_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0A_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0F_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_13_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_15_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_17_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED         STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED         STD_OFF
#  endif

#  if (DCM_SVC_19_06_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_10_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_19_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_READ_DTC_EXT_DATA_BY_DTC_NUM_ENABLED    STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_READ_DTC_EXT_DATA_BY_DTC_NUM_ENABLED    STD_OFF
#  endif

#  if (DCM_SVC_19_0B_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0C_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0D_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0E_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_READ_DTC_BY_OCCUR_TIME_ENABLED          STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_READ_DTC_BY_OCCUR_TIME_ENABLED          STD_OFF
#  endif

#  if (DCM_SVC_19_04_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_18_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_READ_DTC_FFR_BY_DTC_ENABLED             STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_READ_DTC_FFR_BY_DTC_ENABLED             STD_OFF
#  endif

/* DEM API usage optimization */
#  if (DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED     == STD_ON) || \
      (DCM_SVC_19_08_SUPPORT_ENABLED                  == STD_ON) || \
      (DCM_SVC_19_14_SUPPORT_ENABLED                  == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETNUMFILTEREDDTC_ENABLED               STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETNUMFILTEREDDTC_ENABLED               STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED     == STD_ON)
#   define DCM_SVC_19_SETDTCFILTER_INFO_CLASS_ENABLED                STD_ON
#  else
#   define DCM_SVC_19_SETDTCFILTER_INFO_CLASS_ENABLED                STD_OFF
#  endif

#  if (DCM_SVC_19_09_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETSEVERITYOFDTC_ENABLED                STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETSEVERITYOFDTC_ENABLED                STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_FFR_BY_DTC_ENABLED          == STD_ON) || \
      (DCM_SVC_19_05_SUPPORT_ENABLED                   == STD_ON) || \
      (DCM_SVC_19_09_SUPPORT_ENABLED                   == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_BY_OCCUR_TIME_ENABLED       == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_EXT_DATA_BY_DTC_NUM_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETSTATUSOFDTC_ENABLED                  STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETSTATUSOFDTC_ENABLED                  STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_EXT_DATA_BY_DTC_NUM_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETSIZEOFEXTRECORD_ENABLED              STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETSIZEOFEXTRECORD_ENABLED              STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_EXT_DATA_BY_DTC_NUM_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETEXTRECORD_ENABLED                    STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETEXTRECORD_ENABLED                    STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_FFR_BY_DTC_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETSIZEOFFFRECORD_ENABLED               STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETSIZEOFFFRECORD_ENABLED               STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_FFR_BY_DTC_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETFFRECORD_ENABLED                     STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETFFRECORD_ENABLED                     STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_FFR_BY_DTC_ENABLED          == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_EXT_DATA_BY_DTC_NUM_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_ANYABLERECORDUPDATE_ENABLED             STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_ANYABLERECORDUPDATE_ENABLED             STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_BY_OCCUR_TIME_ENABLED == STD_ON) || \
      (DCM_SVC_19_14_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_08_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_09_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETDTCSAM_ENABLED                       STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETDTCSAM_ENABLED                       STD_OFF
#  endif

#  if (DCM_SVC_19_42_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETDTCSEVAM_ENABLED                     STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETDTCSEVAM_ENABLED                     STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_READ_DTC_CNT_BY_STATUS_MASK_ENABLED == STD_ON) || \
      (DCM_SVC_19_14_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_08_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_42_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_SETDTCFILTER_ENABLED                    STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_SETDTCFILTER_ENABLED                    STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_BY_STATUS_MASK_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTC_ENABLED              STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTC_ENABLED              STD_OFF
#  endif

#  if (DCM_OBDDTCMGR_SUPPORT_ENABLED == STD_ON)                                                                                                      /* COV_DCM_UNSUPPORTED XF */
#   define DCM_DEMAPI_OBD_GETNEXTFILTEREDDTC_ENABLED                 STD_ON
#  else
#   define DCM_DEMAPI_OBD_GETNEXTFILTEREDDTC_ENABLED                 STD_OFF
#  endif

#  if (DCM_SVC_19_08_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_42_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTCANDSEV_ENABLED        STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTCANDSEV_ENABLED        STD_OFF
#  endif

#  if (DCM_SVC_19_14_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTCANDFDC_ENABLED        STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTCANDFDC_ENABLED        STD_OFF
#  endif

#  if (DCM_SVC_19_03_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDRECORD_ENABLED           STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETNEXTFILTEREDRECORD_ENABLED           STD_OFF
#  endif

#  if (DCM_SVC_19_03_SUPPORT_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_SETFFRECORDFILTER_ENABLED               STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_SETFFRECORDFILTER_ENABLED               STD_OFF
#  endif

#  if (DCM_DEMAPI_SVC_19_READ_DTC_BY_OCCUR_TIME_ENABLED == STD_ON)
#   define DCM_DEMAPI_SVC_19_GETDTCOCCURTIME_ENABLED                 STD_ON
#  else
#   define DCM_DEMAPI_SVC_19_GETDTCOCCURTIME_ENABLED                 STD_OFF
#  endif

#  if (DCM_OBDDTCMGR_SUPPORT_ENABLED == STD_ON)                                                                                                      /* COV_DCM_UNSUPPORTED XF */
#   define DCM_DEMAPI_OBD_SETDTCFILTER_ENABLED                       STD_ON
#  else
#   define DCM_DEMAPI_OBD_SETDTCFILTER_ENABLED                       STD_OFF
#  endif

#  if (DCM_DEMAPI_UDS_CLEAR_DTC_ENABLED == STD_ON) || \
      (DCM_DEMAPI_OBD_CLEAR_DTC_ENABLED == STD_ON)                                                                                                   /* COV_DCM_UNSUPPORTED TF tf xf */
#   define DCM_DEMAPI_CLEAR_DTC_ENABLED                              STD_ON
#  else
#   define DCM_DEMAPI_CLEAR_DTC_ENABLED                              STD_OFF
#  endif

#  if (DCM_DEM_API_430_ENABLED == STD_ON) && \
      ((DCM_SVC_14_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_04_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_05_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_06_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_09_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0B_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0C_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0D_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_0E_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_10_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_18_SUPPORT_ENABLED == STD_ON) || \
      (DCM_SVC_19_19_SUPPORT_ENABLED == STD_ON))
#   define DCM_DEM_API_SELECT_DTC_ENABLED                            STD_ON
#  else
#   define DCM_DEM_API_SELECT_DTC_ENABLED                            STD_OFF
#  endif

#  if (DCM_DEM_API_430_ENABLED == STD_ON) && \
      (DCM_DEMAPI_SVC_19_GETFFRECORD_ENABLED == STD_ON)
#   define DCM_DEM_API_SELECT_FFR_ENABLED                            STD_ON
#  else
#   define DCM_DEM_API_SELECT_FFR_ENABLED                            STD_OFF
#  endif

#  if (DCM_DEM_API_430_ENABLED == STD_ON) && \
      (DCM_DEMAPI_SVC_19_GETSIZEOFEXTRECORD_ENABLED == STD_ON)
#   define DCM_DEM_API_SELECT_EDR_ENABLED                            STD_ON
#  else
#   define DCM_DEM_API_SELECT_EDR_ENABLED                            STD_OFF
#  endif

#  if (DCM_DEMAPI_CLEAR_DTC_ENABLED == STD_ON) || \
      (DCM_DEMAPI_OBD_SETDTCFILTER_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_SETDTCFILTER_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_SETFFRECORDFILTER_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETDTCOCCURTIME_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETDTCSAM_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_ANYABLERECORDUPDATE_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETSTATUSOFDTC_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETSIZEOFFFRECORD_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETSIZEOFEXTRECORD_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETSEVERITYOFDTC_ENABLED == STD_ON)  || \
      (DCM_DEMAPI_SVC_19_GETFFRECORD_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETEXTRECORD_ENABLED == STD_ON)                                                                                             /* COV_DCM_UNSUPPORTED TF tf xf tf tf tf tf tf tf tf tf tf tf tf */
#   define DCM_DEMAPI_RETVAL_TO_NRC_MAP_ENABLED                      STD_ON
#  else
#   define DCM_DEMAPI_RETVAL_TO_NRC_MAP_ENABLED                      STD_OFF
#  endif

#  if (DCM_DEMAPI_OBD_GETNEXTFILTEREDDTC_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTC_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTCANDSEV_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETNEXTFILTEREDDTCANDFDC_ENABLED == STD_ON) || \
      (DCM_DEMAPI_SVC_19_GETNEXTFILTEREDRECORD_ENABLED == STD_ON)                                                                                    /* COV_DCM_UNSUPPORTED TF xf tf tf tf tf */
#   define DCM_DEMAPI_GETNEXTFILTEREDITEM_ENABLED                    STD_ON
#  else
#   define DCM_DEMAPI_GETNEXTFILTEREDITEM_ENABLED                    STD_OFF
#  endif
# endif /* (DCM_DEMAPIMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON)                                                                                                          /* COV_DCM_UNSUPPORTED XF */
#  if (DCM_SVC_2E_SUPPORT_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPE_WRITE_ENABLED                           STD_ON
#  else
#   define DCM_DIDMGR_OPTYPE_WRITE_ENABLED                           STD_OFF
#  endif

#  if (DCM_DIDMGR_OPCLS_READ_ASYNC_ENABLED == STD_ON) || \
      (DCM_DIDMGR_OPCLS_READ_SYNC_ENABLED  == STD_ON)
#   define DCM_DIDMGR_OPTYPE_READ_ENABLED                            STD_ON
#  else
#   define DCM_DIDMGR_OPTYPE_READ_ENABLED                            STD_OFF
#  endif

#  if (DCM_DIDMGR_OPCLS_READ_ASYNC_ENABLED == STD_ON) || \
      (DCM_DIDMGR_OPCLS_READ_SYNC_ENABLED  == STD_ON)
#   define DCM_DIDMGR_OPTYPE_READ_CHECKCOND_ENABLED                  STD_ON
#  else
#   define DCM_DIDMGR_OPTYPE_READ_CHECKCOND_ENABLED                  STD_OFF
#  endif

#  if (DCM_SVC_24_SUPPORT_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPE_GETSCALINGINFO_ENABLED                  STD_ON
#  else
#   define DCM_DIDMGR_OPTYPE_GETSCALINGINFO_ENABLED                  STD_OFF
#  endif

#  if (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPE_DEFINE_ENABLED                          STD_ON
#  else
#   define DCM_DIDMGR_OPTYPE_DEFINE_ENABLED                          STD_OFF
#  endif

#  if (DCM_DIDMGR_OPTYPE_IO_RETCTRL2ECU_ENABLED   == STD_ON) || \
      (DCM_DIDMGR_OPTYPE_IO_RST2DEFAULT_ENABLED   == STD_ON) || \
      (DCM_DIDMGR_OPTYPE_IO_FRZCURSTATE_ENABLED   == STD_ON) || \
      (DCM_DIDMGR_OPTYPE_IO_SHRTTERMADJ_ENABLED   == STD_ON)
#   define DCM_DIDMGR_OPTYPE_IO_ANY_ENABLED                          STD_ON
#  else
#   define DCM_DIDMGR_OPTYPE_IO_ANY_ENABLED                          STD_OFF
#  endif

#  if (DCM_DIDMGR_MSIG_OPTYPE_IO_RETCTRL2ECU_ENABLED   == STD_ON) || \
      (DCM_DIDMGR_MSIG_OPTYPE_IO_RST2DEFAULT_ENABLED   == STD_ON) || \
      (DCM_DIDMGR_MSIG_OPTYPE_IO_FRZCURSTATE_ENABLED   == STD_ON) || \
      (DCM_DIDMGR_MSIG_OPTYPE_IO_SHRTTRMADJ_ENABLED   == STD_ON)
#   define DCM_DIDMGR_MSIG_OPTYPE_IO_ANY_ENABLED                     STD_ON
#  else
#   define DCM_DIDMGR_MSIG_OPTYPE_IO_ANY_ENABLED                     STD_OFF
#  endif

#  if (DCM_SVC_2C_SUPPORT_ENABLED == STD_ON) && \
      ((DCM_SVC_2C_02_SUPPORT_ENABLED  == STD_ON) || \
      ((DCM_SVC_2C_01_SUPPORT_ENABLED == STD_ON) && (DCM_DIDMGR_STATIC_DID_ASYNC_SUPPORT_ENABLED == STD_ON)))
#   define DCM_DIDMGR_DYNDID_ASYNC_SUPPORT_ENABLED                   STD_ON
#  else
#   define DCM_DIDMGR_DYNDID_ASYNC_SUPPORT_ENABLED                   STD_OFF
#  endif

#  if (DCM_DIDMGR_OPCLS_WRITE_LEN_SYNC_NRES_ERROR_ENABLED  == STD_ON) || \
      (DCM_DIDMGR_OPCLS_WRITE_LEN_ASYNC_NRES_ERROR_ENABLED == STD_ON) || \
      (DCM_DIDMGR_OPCLS_WRITE_RANGE_ENABLED == STD_ON) || \
      (DCM_DIDMGR_OPCLS_WRITE_LEN_SYNC_RES_ERROR_ENABLED == STD_ON)
#   define DCM_DIDMGR_WRITE_DYNLEN_DID_SUPPORT_ENABLED               STD_ON
#  else
#   define DCM_DIDMGR_WRITE_DYNLEN_DID_SUPPORT_ENABLED               STD_OFF
#  endif

#  if (DCM_DIDMGR_DYNDID_SRCITEM_CHECK_STATE_ENABLED == STD_ON) && \
      (DCM_DIDMGR_DYNDID_CLR_ON_STATE_CHG_ENABLED    == STD_OFF)
#   define DCM_DIDMGR_DYNDID_DEEP_CHECK_ON_READ_ENABLED              STD_ON
#  else
#   define DCM_DIDMGR_DYNDID_DEEP_CHECK_ON_READ_ENABLED              STD_OFF
#  endif

#  if (DCM_DIDMGR_MULTISIGNAL_ENABLED == STD_ON) || \
      (DCM_DIDMGR_OPCLS_READ_PAGED_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPECONTEXT_READ_ENABLED                     STD_ON
#  else
#   define DCM_DIDMGR_OPTYPECONTEXT_READ_ENABLED                     STD_OFF
#  endif

#  if (DCM_DIDMGR_RANGE_SUPPORT_ENABLED   == STD_ON) || \
      (DCM_DIDMGR_EXTENDED_LOOKUP_ENABLED == STD_ON)
#   define DCM_DIDMGR_ASYNC_LOOKUP_ENABLED                           STD_ON
#  else
#   define DCM_DIDMGR_ASYNC_LOOKUP_ENABLED                           STD_OFF
#  endif

#  if (DCM_DIDMGR_ASYNC_LOOKUP_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPECONTEXT_LOOKUP_ENABLED                   STD_ON
#  else
#   define DCM_DIDMGR_OPTYPECONTEXT_LOOKUP_ENABLED                   STD_OFF
#  endif

#  if (DCM_DIDMGR_IO_MASKRECORD_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPECONTEXT_IO_ENABLED                       STD_ON
#  else
#   define DCM_DIDMGR_OPTYPECONTEXT_IO_ENABLED                       STD_OFF
#  endif

#  if(DCM_DIDMGR_MSIG_OPTYPE_GETSCALINGINFO_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPECONTEXT_GETSCALING_ENABLED               STD_ON
#  else
#   define DCM_DIDMGR_OPTYPECONTEXT_GETSCALING_ENABLED               STD_OFF
#  endif

#  if (DCM_DIDMGR_OPTYPECONTEXT_IO_ENABLED == STD_ON) || \
      (DCM_DIDMGR_OPTYPECONTEXT_READ_ENABLED == STD_ON) || \
      (DCM_DIDMGR_OPTYPECONTEXT_GETSCALING_ENABLED == STD_ON) || \
      (DCM_DIDMGR_OPTYPECONTEXT_LOOKUP_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPECONTEXT_SHARED_ENABLED                   STD_ON
#  else
#   define DCM_DIDMGR_OPTYPECONTEXT_SHARED_ENABLED                   STD_OFF
#  endif

#  if (DCM_DIDMGR_MULTISIGNAL_ENABLED == STD_ON) || \
      (DCM_DIDMGR_OPTYPECONTEXT_SHARED_ENABLED == STD_ON)
#   define DCM_DIDMGR_OPTYPECONTEXT_ENABLED                          STD_ON
#  else
#   define DCM_DIDMGR_OPTYPECONTEXT_ENABLED                          STD_OFF
#  endif

#  if (DCM_DIDMGR_OPCLS_READ_PAGED_ENABLED == STD_ON) && \
      (DCM_DIDMGR_OPCLS_READ_VID_ENABLED == STD_ON) && \
      (DCM_DCM_AR_VERSION >= DCM_DCM_AR_VERSION_422)
#   error "Paged DIDs are not allowed if any OBD2 VID DIDs as per AR4.2.2 are enabled!"
#  endif

#  if (DCM_DIDMGR_RANGE_SUPPORT_ENABLED == STD_ON) && \
      (DCM_DIDMGR_OPCLS_READ_PAGED_ENABLED == STD_ON)
#   error "DID ranges are not allowed if any paged DID is configured!"
#  endif

#  if (DCM_DIDMGR_OPCLS_READ_PAGED_ENABLED == STD_ON) || \
      (DCM_DIAG_CANCEL_OP_ENABLED == STD_ON)
#   define DCM_DIDMGR_CANCEL_OP_READ_ENABLED                         STD_ON
#  else
#   define DCM_DIDMGR_CANCEL_OP_READ_ENABLED                         STD_OFF
#  endif

#  if (DCM_DIDMGR_CANCEL_OP_READ_ENABLED == STD_ON) || \
      (DCM_DIAG_CANCEL_OP_ENABLED == STD_ON)
#   define DCM_DIDMGR_CANCEL_OP_ENABLED                              STD_ON
#  else
#   define DCM_DIDMGR_CANCEL_OP_ENABLED                              STD_OFF
#  endif

#  if (DCM_DIDMGR_OPCLS_READ_PAGED_ENABLED == STD_ON)
#   define DCM_DIDMGR_PAGED_DID_SUPPORT_ENABLED                      STD_ON
#  else
#   define DCM_DIDMGR_PAGED_DID_SUPPORT_ENABLED                      STD_OFF
#  endif
# endif /* (DCM_DIDMGR_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Defines
---------------------------------------------- */
/*! Template for number of iterations limitation pattern */
# define DCM_UTIRTLMTR_CTR_TYPE                                      uint8_least
# define DCM_UTIRTLMTR_CTR_NAME                                      lRtLimiterCntr

# if(DCM_RUNTIME_USAGE_LIMIT_ENABLED == STD_ON)
/*! Iterations limitation for exactly one loop (otherwise compiler warnings for condition always true will occur) */
#  if (DCM_RUNTIME_USAGE_LIMIT_SINGLE_LOOP_ENABLED == STD_ON)
/*! Local definition of the iteration counter */
#   define DCM_UTIRTLMTR_CTR_DEF                                     /* not used */
/*! Initialization of the iteration counter prior iteration start */
#   define DCM_UTIRTLMTR_CTR_INIT                                    /* not used */
/*! Registers a single iteration */
#   define DCM_UTIRTLMTR_CTR_NEXT                                    /* not used */
/*! Signals iteration limitation handling without an explicit break. Additionally a specific iteration result will be set */
#   define DCM_UTIRTLMTR_CTR_HANDLE_NO_BREAK(retVariable, retValue)  {(retVariable) = (retValue);}                                                   /* PRQA S 3412, 3458 */ /* MD_MSR_19.4 */
/*! Signals iteration limitation handling with an explicit break. Additionally a specific iteration result will be set */
#   define DCM_UTIRTLMTR_CTR_HANDLE_AND_BREAK(retVariable, retValue) {(retVariable) = (retValue); break;}                                            /* PRQA S 3412, 3458 */ /* MD_MSR_19.4 */
#  else
/*! Iteration limitations for more than one loop (otherwise compiler warnings for condition always true will occur) */
/*! Local definition of the iteration counter */
#   define DCM_UTIRTLMTR_CTR_DEF                                     DCM_UTIRTLMTR_CTR_TYPE DCM_UTIRTLMTR_CTR_NAME;                                  /* PRQA S 3412 */ /* MD_MSR_19.4 */
/*! Initialization of the iteration counter prior iteration start */
#   define DCM_UTIRTLMTR_CTR_INIT                                    DCM_UTIRTLMTR_CTR_NAME = DCM_RUNTIME_USAGE_ITERATIONS;                          /* PRQA S 3412 */ /* MD_MSR_19.4 */
/*! Registers a single iteration */
#   define DCM_UTIRTLMTR_CTR_NEXT                                    --DCM_UTIRTLMTR_CTR_NAME;                                                       /* PRQA S 3412 */ /* MD_MSR_19.4 */
/*! Signals iteration limitation handling without an explicit break. Additionally a specific iteration result will be set */
#   define DCM_UTIRTLMTR_CTR_HANDLE_NO_BREAK(retVariable, retValue)  if(DCM_UTIRTLMTR_CTR_NAME == 0u) { (retVariable) = (retValue); }                /* PRQA S 3412, 3458 */ /* MD_MSR_19.4 */
/*! Signals iteration limitation handling with an explicit break. Additionally a specific iteration result will be set */
#   define DCM_UTIRTLMTR_CTR_HANDLE_AND_BREAK(retVariable, retValue) if(DCM_UTIRTLMTR_CTR_NAME == 0u) { (retVariable) = (retValue); break; }         /* PRQA S 3412, 3458 */ /* MD_MSR_19.4 */
#  endif
# else
/*! No iterations limitation needed */
/*! Local definition of the iteration counter */
#  define DCM_UTIRTLMTR_CTR_DEF                                      /* not used */
/*! Initialization of the iteration counter prior iteration start */
#  define DCM_UTIRTLMTR_CTR_INIT                                     /* not used */
/*! Registers a single iteration */
#  define DCM_UTIRTLMTR_CTR_NEXT                                     /* not used */
/*! Signals iteration limitation handling without an explicit break. Additionally a specific iteration result will be set */
#  define DCM_UTIRTLMTR_CTR_HANDLE_NO_BREAK(retVariable, retValue)   /* not used */
/*! Signals iteration limitation handling with an explicit break. Additionally a specific iteration result will be set */
#  define DCM_UTIRTLMTR_CTR_HANDLE_AND_BREAK(retVariable, retValue)  /* not used */
# endif
/*! Debug sub-component initialization states */
# define DCM_DEBUG_INITSTATE_UNINIT                                  (Dcm_DebugInitStateType)0x00u     /*!< DCM is not or partially initialized. In this state DCM is completely isolated from the other BSWs/SW-C in the ECU */
# define DCM_DEBUG_INITSTATE_INIT                                    (Dcm_DebugInitStateType)0x01u     /*!< DCM is initialized. In this state DCM is fully operable */

/*! Buffer overflow detection pattern configuration */
# define DCM_DEBUG_BUFFEROVFLPATTERN_SIZE                            2                /*!< Pattern length in bytes. To be added to the total size of the buffer to be monitored for overflow */
# define DCM_DEBUG_BUFFEROVFLPATTERN                                 (uint16)0xBEDAu  /*!< The pattern value itself. To be written at the end (i.e. after the original size) of the buffer to be monitor for overflow */
/*! Calculate the maximum number of events related to USDT transport objects, needed by a network related task */
# if (DCM_VARMGR_MODE_POSTBUILD_LOAD_ENABLED == STD_ON)
#  define DCM_NET_MAX_NUM_EVENT_TRANSP_OBJECTS                       32u                                  /*!< Take the worst case, limited to 32 for a bit mask usage (i.e. task events) */
# else
#  define DCM_NET_MAX_NUM_EVENT_TRANSP_OBJECTS                       DCM_NET_MAX_NUM_TRANSP_OBJECTS_CONST /*!< Allocate as many as needed by the concrete configuration */
# endif

/*! Network variant/non-variant configuration abstraction */
# if (DCM_VARMGR_MULTI_COM_ENABLED == STD_ON)
#  define Dcm_NetCfgGetNumRxPduIds(comVariant)                       ((comVariant)->NumRxPduIds)                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetNumTxPduIds(comVariant)                       ((comVariant)->NumTxPduIds)                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetMinCanTpRxPduId(comVariant)                   ((comVariant)->CanTpRxPduIdMin)                                                 /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetMaxCanTpRxPduId(comVariant)                   ((comVariant)->CanTpRxPduIdMax)                                                 /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetNumCanRxPduIds(comVariant)                    ((comVariant)->NumCanTpRxPduIds)                                                /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetNumPerTxObjects(comVariant)                   ((comVariant)->NumPerTxObjects)                                                 /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetNumConnections(comVariant)                    ((comVariant)->NumConnections)                                                  /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetNumProtocols(comVariant)                      ((comVariant)->NumProtocols)                                                    /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetNumComMChannels(comVariant)                   ((comVariant)->NumComMChannels)                                                 /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetNumBuffers(comVariant)                        ((comVariant)->NumBuffers)                                                      /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetNumTranspObjects(comVariant)                  ((comVariant)->NumTranspObjects)                                                /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetNumAllComMChannels(comVariant)                ((comVariant)->NumAllComMChannels)                                              /* PRQA S 3453 */ /* MD_MSR_19.7 */

#  define Dcm_NetCfgGetRxPduInfo(comVariant)                         ((comVariant)->RxPduIdTable)                                                    /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetConnectionInfo(comVariant)                    ((comVariant)->ConnectionTable)                                                 /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetProtocolInfo(comVariant)                      ((comVariant)->ProtocolTable)                                                   /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetNetConnComMChannelMap(comVariant)             ((comVariant)->NetConnComMChannelMap)                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetNetworkHdlLookUp(comVariant)                  ((comVariant)->NetworkHandleLookUpTable)                                        /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetTxPdu2ConnMap(comVariant)                     ((comVariant)->TxPduIdMap)                                                      /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetPerTxPdu2RsrsMap(comVariant)                  ((comVariant)->PerTxPduIdMap)                                                   /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetPerTxPduIdInfo(comVariant)                    ((comVariant)->PerTxPduIdTable)                                                 /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetComCtrlChannelListAll(comVariant)             ((comVariant)->ComCtrlChannelListAll)                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetNetAllComMChannelMap(comVariant)              ((comVariant)->NetAllComMChannelMap)                                            /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define Dcm_NetCfgGetCanTp2DcmRxPduIdMap(comVariant)               ((comVariant)->CanTp2DcmRxPduIdMap)                                             /* PRQA S 3453 */ /* MD_MSR_19.7 */
# else
#  define Dcm_NetCfgGetNumRxPduIds(comVariant)                       DCM_NET_NUM_RX_PDUIDS
#  define Dcm_NetCfgGetNumTxPduIds(comVariant)                       DCM_NET_NUM_TX_PDUIDS
#  define Dcm_NetCfgGetMinCanTpRxPduId(comVariant)                   DCM_NET_CANTP_RX_PDUID_MIN
#  define Dcm_NetCfgGetMaxCanTpRxPduId(comVariant)                   DCM_NET_CANTP_RX_PDUID_MAX
#  define Dcm_NetCfgGetNumCanRxPduIds(comVariant)                    DCM_NET_NUM_CANTP_RX_PDUIDS
#  define Dcm_NetCfgGetNumPerTxObjects(comVariant)                   DCM_NET_MAX_NUM_PERIODIC_TX_OBJ
#  define Dcm_NetCfgGetNumConnections(comVariant)                    DCM_NET_MAX_NUM_CONNECTIONS
#  define Dcm_NetCfgGetNumProtocols(comVariant)                      DCM_NET_NUM_PROTOCOLS
#  define Dcm_NetCfgGetNumComMChannels(comVariant)                   DCM_NET_MAX_NUM_COMM_CHANNELS
#  define Dcm_NetCfgGetNumBuffers(comVariant)                        DCM_NET_NUM_BUFFERS
#  define Dcm_NetCfgGetNumTranspObjects(comVariant)                  DCM_NET_MAX_NUM_TRANSP_OBJECTS
#  define Dcm_NetCfgGetNumAllComMChannels(comVariant)                DCM_NET_MAX_NUM_ALL_COMM_CHANNELS

#  define Dcm_NetCfgGetRxPduInfo(comVariant)                         Dcm_CfgNetRxPduInfo
#  define Dcm_NetCfgGetConnectionInfo(comVariant)                    Dcm_CfgNetConnectionInfo
#  define Dcm_NetCfgGetProtocolInfo(comVariant)                      Dcm_CfgNetProtocolInfo
#  define Dcm_NetCfgGetNetConnComMChannelMap(comVariant)             Dcm_CfgNetConnComMChannelMap
#  define Dcm_NetCfgGetNetworkHdlLookUp(comVariant)                  Dcm_CfgNetNetworkHandleLookUpTable
#  define Dcm_NetCfgGetTxPdu2ConnMap(comVariant)                     Dcm_CfgNetTxPduInfo
#  define Dcm_NetCfgGetPerTxPdu2RsrsMap(comVariant)                  Dcm_CfgNetPeriodicTxPduInfo
#  define Dcm_NetCfgGetPerTxPduIdInfo(comVariant)                    Dcm_CfgNetPeriodicTxPduIds
#  define Dcm_NetCfgGetComCtrlChannelListAll(comVariant)             Dcm_CfgNetComCtrlChannelListAll
#  define Dcm_NetCfgGetNetAllComMChannelMap(comVariant)              Dcm_CfgNetAllComMChannelMap
#  define Dcm_NetCfgGetCanTp2DcmRxPduIdMap(comVariant)               Dcm_CfgNetCanTp2DcmRxPduIdMap
# endif

/*! Returns the diagnostic client connection ID from a DcmRxPduID */
# define Dcm_NetCfgGetConnIdOfRxPduId(comVariant, rxPduId)           (Dcm_NetCfgGetRxPduInfo(comVariant)[(rxPduId)].ConnRef)                         /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns the diagnostic client's network address from its connection ID */
# define Dcm_NetCfgGetTesterAddressOfConnId(comVariant, connId)      (Dcm_NetCfgGetConnectionInfo(comVariant)[(connId)].ClientSrcAddr)               /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns the diagnostic client's network address from one of its DcmRxPduIDs */
# define Dcm_NetCfgGetTesterAddressOfRxPduId(comVariant, rxPduId)    (Dcm_NetCfgGetTesterAddressOfConnId((comVariant), Dcm_NetCfgGetConnIdOfRxPduId((comVariant), (rxPduId)))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! ComM channel message communication ability states */
# define DCM_NET_COMM_STATE_FLAG_RX_DIS                              ((Dcm_NetComMStateType)0x00u ) /*!< Message reception is disabled */
# define DCM_NET_COMM_STATE_FLAG_TX_DIS                              ((Dcm_NetComMStateType)0x00u ) /*!< Message transmission is disabled */
# define DCM_NET_COMM_STATE_FLAG_TX_EN                               ((Dcm_NetComMStateType)0x01u ) /*!< Message transmission is enabled */
# define DCM_NET_COMM_STATE_FLAG_RX_EN                               ((Dcm_NetComMStateType)0x02u ) /*!< Message reception is enabled */

/*! Calculates a combined reception and transmission message communication state */
# define DCM_NET_COMM_STATE_COMPOSER(rx,tx)                          ((Dcm_NetComMStateType)((rx)|(tx)))                                             /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Presets of all possible message communication states in both directions (Rx and Tx) */
# define DCM_NET_COMM_STATE_RX_DIS_TX_DIS                            (DCM_NET_COMM_STATE_COMPOSER(DCM_NET_COMM_STATE_FLAG_RX_DIS,DCM_NET_COMM_STATE_FLAG_TX_DIS)) /*!< Message reception and transmission are disabled (NoCommunicationMode) */
# define DCM_NET_COMM_STATE_RX_DIS_TX_EN                             (DCM_NET_COMM_STATE_COMPOSER(DCM_NET_COMM_STATE_FLAG_RX_DIS,DCM_NET_COMM_STATE_FLAG_TX_EN))  /*!< Message reception is disabled, but transmission is enabled */
# define DCM_NET_COMM_STATE_RX_EN_TX_DIS                             (DCM_NET_COMM_STATE_COMPOSER(DCM_NET_COMM_STATE_FLAG_RX_EN, DCM_NET_COMM_STATE_FLAG_TX_DIS)) /*!< Message reception is enabled, but transmission is disabled (SilentCommunicationMode) */
# define DCM_NET_COMM_STATE_RX_EN_TX_EN                              (DCM_NET_COMM_STATE_COMPOSER(DCM_NET_COMM_STATE_FLAG_RX_EN, DCM_NET_COMM_STATE_FLAG_TX_EN))  /*!< Message reception and transmission are enabled (FullCommunicationMode)*/
# define DCM_REPEATER_EXT_CNTXT_SVC86                                (Dcm_RepeaterSvcContextHandleType)0
/*! Represents the initial (default) value of the diagnostic state group "DiagnosticSession": "DefaultSession" */
# define DCM_STATE_VALUE_SESSION_INIT                                ((Dcm_CfgStateGroupMemType)0x01u)
/*! Represents the initial (default) value of the diagnostic state group "SecurityAccess": "Locked" */
# define DCM_STATE_VALUE_SECURITY_INIT                               ((Dcm_CfgStateGroupMemType)0x01u)
/**
 * Definition and calculation the total number of system tasks
 */

# define DCM_TSK_NUM_TIMER                                           1  /*!< A single timer task (Dcm_TmrTaskTimer()) is always needed (manages all system timers) */
# define DCM_TSK_NUM_NET_TX                                          1  /*!< A network tasks for managing the message transmission is always available */
# define DCM_TSK_NUM_DIAG_TX                                         1  /*!< A diagnostic tasks for managing the response message preparation is always available */

# if (DCM_NET_TASK_RX_ENABLED == STD_ON)
#  define DCM_TSK_NUM_NET_RX                                         1  /*!< A message reception network task (Dcm_NetTaskRx) is needed (i.e. for message prioritization before starting its processing) */
# else
#  define DCM_TSK_NUM_NET_RX                                         0  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif

/*! Dcm_ExtSvc86Task() configuration */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)                                                                                                          /* COV_DCM_UNSUPPORTED XF */
#  if defined (DCM_EXT_TSK_NUM_ROE)
#   define DCM_TSK_NUM_ROE                                           DCM_EXT_TSK_NUM_ROE       /*!< Inherits the Diagnostic service 0x86 needs for a dedicated task (Dcm_ExtSvc86Task()) for additional jobs to be executed out of service execution context */
#   if defined (DCM_EXT_TSK_ATR_ROE_EXEC)
#    define DCM_TSK_ATR_ROE_EXEC                                     DCM_EXT_TSK_ATR_ROE_EXEC  /*!< Inherits the attributes of the external RoE task */
#   else
#    error "Missing DCM extension value: DCM_EXT_TSK_ATR_ROE_EXEC!"
#   endif
#  else
#   error "Missing DCM extension value: DCM_EXT_TSK_NUM_ROE!"
#  endif

#  if defined (DCM_EXT_TSK_EV_ROE_MSB)
#   define DCM_TSK_EV_ROE_MSB                                        DCM_EXT_TSK_EV_ROE_MSB  /*!< Inherits the event register width of the external RoE task */
#  else
#   error "Missing DCM extension value: DCM_EXT_TSK_EV_ROE_MSB!"
#  endif
# else
#  define DCM_TSK_NUM_ROE                                            0      /*!< Just a bridge to accomplish the amount of tasks calculation */
#  define DCM_TSK_EV_ROE_MSB                                         0x00u  /*!< No RoE task, no events, no MSB of the events available */
# endif /*(DCM_SVC_86_SUPPORT_ENABLED == STD_ON)*/

# if(DCM_PAGED_BUFFER_ENABLED == STD_ON)
#  define DCM_TSK_NUM_PGDBUF                                         1  /*!< The paged-buffer task (Dcm_PagedBufferTask()) is required */
# else
#  define DCM_TSK_NUM_PGDBUF                                         0  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif
# define DCM_TSK_NUM_DIAG_WORK                                       1  /*!< A diagnostic tasks (Dcm_DiagTaskWorker()) for diagnostic service processing is always available */
# if (DCM_SVC_27_SUPPORT_ENABLED == STD_ON) && \
     (DCM_STATE_SEC_RETRY_ENABLED == STD_ON) && \
     (DCM_STATE_SEC_ATT_CNTR_EXT_STORAGE_ENABLED == STD_ON)                                                                                          /* COV_DCM_UNSUPPORTED XF xf xf xf */
#  define DCM_TSK_NUM_SVC27                                          1  /*!< Diagnostic service 0x27 needs dedicated task (Dcm_Svc27Task()) for additional jobs to be executed out of service execution context */
# else
#  define DCM_TSK_NUM_SVC27                                          0  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif
# if (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
#  define DCM_TSK_NUM_DIAG_FBLRES                                    1  /*!< One task (Dcm_DiagTaskFblRes()) for the final response after an FBL to APPL and vice versa transition */
# else
#  define DCM_TSK_NUM_DIAG_FBLRES                                    0  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif
# if (DCM_MODEMGR_MONITORING_ENABLED == STD_ON)
#  define DCM_TSK_NUM_MODE_MONITOR                                   1  /*!< One task (Dcm_ModeTaskMonitor()) for the background monitoring of mode changes that shall reset the ECU to its default state */
# else
#  define DCM_TSK_NUM_MODE_MONITOR                                   0  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif
# if (DCM_SVC_2A_SUPPORT_ENABLED == STD_ON)                                                                                                          /* COV_DCM_UNSUPPORTED XF */
#  define DCM_TSK_NUM_SVC2A_SCHEDULER                                1  /*!< Diagnostic service 0x2A needs dedicated task (Dcm_Svc2ATaskSchdProcess()) for additional jobs to be executed out of service execution context */
# else
#  define DCM_TSK_NUM_SVC2A_SCHEDULER                                0 /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif
# define DCM_TSK_NUM_DIAG_RX                                         1  /*!< One task (Dcm_DiagTaskRx()) for the diagnostic message reception synchronization is always required */

# if (DCM_NET_MONITOR_FOREIGN_N_TA_ENABLED == STD_ON)
#  define DCM_TSK_NUM_NET_TA_MONITOR                                 1  /*!< One task (Dcm_ModeTaskMonitor()) for the background monitoring of diagnostic requests to other ECUs */
# else
#  define DCM_TSK_NUM_NET_TA_MONITOR                                 0  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif

# if (DCM_DIAG_STATE_RECOVERY_ENABLED == STD_ON)                                                                                                     /* COV_DCM_UNSUPPORTED XF */
#  define DCM_TSK_NUM_DIAG_RECOVERY                                  1  /*!< One task (Dcm_DiagTaskRecovery()) for the full diagnostic state recovery after ECU reset /power down */
# else
#  define DCM_TSK_NUM_DIAG_RECOVERY                                  0  /*!< Just a bridge to accomplish the amount of tasks calculation */
# endif

# if (DCM_DIAG_GARB_COL_ENABLED == STD_ON)
#  define DCM_TSK_NUM_DIAG_GARB_COL                                  1
# else
#  define DCM_TSK_NUM_DIAG_GARB_COL                                  0 /* just a bridge */
# endif

/*! Pre-compile total number of system tasks calculation */
# define DCM_TSK_NUM_TASKS                                           ((Dcm_TskTaskIdMemType)( DCM_TSK_NUM_TIMER \
                                                                     + DCM_TSK_NUM_DIAG_RX \
                                                                     + DCM_TSK_NUM_MODE_MONITOR \
                                                                     + DCM_TSK_NUM_DIAG_FBLRES \
                                                                     + DCM_TSK_NUM_DIAG_WORK \
                                                                     + DCM_TSK_NUM_PGDBUF \
                                                                     + DCM_TSK_NUM_SVC27 \
                                                                     + DCM_TSK_NUM_ROE \
                                                                     + DCM_TSK_NUM_DIAG_TX \
                                                                     + DCM_TSK_NUM_NET_TX \
                                                                     + DCM_TSK_NUM_NET_RX \
                                                                     + DCM_TSK_NUM_SVC2A_SCHEDULER \
                                                                     + DCM_TSK_NUM_NET_TA_MONITOR \
                                                                     + DCM_TSK_NUM_DIAG_RECOVERY \
                                                                     + DCM_TSK_NUM_DIAG_GARB_COL) )
/*! Calculation of all system tasks IDs.
  Note: The order is important since it determines the order of task activations in the corresponding scheduler! Lowest Id will be executed first.
        The same order defined here must be kept during the initialization of the table Dcm_TskTaskInfo */
# define DCM_TSK_ID_DIAG_RECOVERY                                    ((Dcm_TskTaskIdMemType)(0 + 0))                                                    /*!< The task ID of the Dcm_DiagTaskRecovery() task */
# define DCM_TSK_ID_NET_TA_MONITOR                                   ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_DIAG_RECOVERY + DCM_TSK_NUM_DIAG_RECOVERY))     /*!< The task ID of the Dcm_NetTaskTaMonitor() task */
# define DCM_TSK_ID_NET_RX                                           ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_NET_TA_MONITOR + DCM_TSK_NUM_NET_TA_MONITOR))   /*!< The task ID of the Dcm_NetTaskRx task() */
# define DCM_TSK_ID_TIMER                                            ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_NET_RX + DCM_TSK_NUM_NET_RX))                   /*!< The task ID of the Dcm_TmrTaskTimer() task */
# define DCM_TSK_ID_DIAG_RX                                          ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_TIMER + DCM_TSK_NUM_TIMER))                     /*!< The task ID of the Dcm_DiagTaskRx() task */
# define DCM_TSK_ID_MODE_MONITOR                                     ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_DIAG_RX + DCM_TSK_NUM_DIAG_RX))                 /*!< The task ID of the Dcm_ModeTaskMonitor() task */
# define DCM_TSK_ID_DIAG_FBLRES                                      ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_MODE_MONITOR + DCM_TSK_NUM_MODE_MONITOR))       /*!< The task ID of the Dcm_DiagTaskFblRes() task */
# define DCM_TSK_ID_SVC27                                            ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_DIAG_FBLRES + DCM_TSK_NUM_DIAG_FBLRES))         /*!< The task ID of the Dcm_Svc27Task() task */
# define DCM_TSK_ID_DIAG_WORK                                        ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_SVC27 + DCM_TSK_NUM_SVC27))                     /*!< The task ID of the Dcm_DiagTaskWorker() task */
# define DCM_TSK_ID_PGDBUF                                           ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_DIAG_WORK + DCM_TSK_NUM_DIAG_WORK))             /*!< The task ID of the Dcm_PagedBufferTask() task */
# define DCM_TSK_ID_ROE                                              ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_PGDBUF + DCM_TSK_NUM_PGDBUF))
# define DCM_TSK_ID_DIAG_GARB_COL                                    ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_ROE + DCM_TSK_NUM_ROE))
# define DCM_TSK_ID_DIAG_TX                                          ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_DIAG_GARB_COL + DCM_TSK_NUM_DIAG_GARB_COL))     /*!< The task ID of the Dcm_DiagTaskTx() task */
# define DCM_TSK_ID_SVC2A_SCHEDULER                                  ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_DIAG_TX + DCM_TSK_NUM_DIAG_TX))
# define DCM_TSK_ID_NET_TX                                           ((Dcm_TskTaskIdMemType)(DCM_TSK_ID_SVC2A_SCHEDULER + DCM_TSK_NUM_SVC2A_SCHEDULER)) /*!< The task ID of the Dcm_NetTaskTx() task */

/**
 * Definition of all sub-components' tasks related events
 */

/*! Events of the Dcm_TmrTaskTimer() */
# define DCM_TSK_EV_TIMER_ACTIVE                                     ((Dcm_TskTaskEvMemType)0x01u)  /*!< Activate the task (on any timer activation and as long as a timer is running) */

/*! Registers the most significant bit in the event mask of the Dcm_TmrTaskTimer() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
# define DCM_TSK_EV_TIMER_MSB                                        0x01u

/*! Events of the Dcm_DiagTaskRx() */
# define DCM_TSK_EV_DIAG_RX_TMR_P2_TO                                ((Dcm_TskTaskEvMemType)0x01u)  /*!< Time-out of the P2 timer occurred */
# define DCM_TSK_EV_DIAG_RX_NEW_REQ                                  ((Dcm_TskTaskEvMemType)0x02u)  /*!< New request has been received and is ready for processing */

/*! Registers the most significant bit in the event mask of the Dcm_DiagTaskRx() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
# define DCM_TSK_EV_DIAG_RX_MSB                                      0x02u

/*! Events of the Dcm_DiagTaskWorker() */
# define DCM_TSK_EV_DIAG_WORK_TX_END_FINAL                           ((Dcm_TskTaskEvMemType)0x01u)  /*!< Current diagnostic service processing just finished */
# define DCM_TSK_EV_DIAG_WORK_TX_END_RCRRP                           ((Dcm_TskTaskEvMemType)0x02u)  /*!< A RCR-RP response transmission just finished */
# define DCM_TSK_EV_DIAG_WORK_EXT_SET2DEF                            ((Dcm_TskTaskEvMemType)0x04u)  /*!< An external request for entering default-session (via Dcm_ResetToDefaultSession()) */
# define DCM_TSK_EV_DIAG_WORK_INT_SET2DEF                            ((Dcm_TskTaskEvMemType)0x08u)  /*!< An internal request for entering default session (e.g. on protocol preemption) */
# define DCM_TSK_EV_DIAG_WORK_REPEAT                                 ((Dcm_TskTaskEvMemType)0x10u)  /*!< A diagnostic request operation needs to be (re-)executed */
# define DCM_TSK_EV_DIAG_WORK_NEW_REQ                                ((Dcm_TskTaskEvMemType)0x20u)  /*!< A new diagnostic request is to be processed */
# define DCM_TSK_EV_DIAG_WORK_CANCEL_OP                              ((Dcm_TskTaskEvMemType)0x40u)  /*!< A background diagnostic request operation (e.g. PagedBuffer processing) cancelation */
# define DCM_TSK_EV_DIAG_WORK_KILL_JOBS                              ((Dcm_TskTaskEvMemType)0x80u)  /*!< Any diagnostic service processing currently in progress has to be terminated */

/*! Registers the most significant bit in the event mask of the Dcm_DiagTaskWorker() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
# define DCM_TSK_EV_DIAG_WORK_MSB                                    0x80u

/*! Events of the Dcm_Svc27Task() */
# define DCM_TSK_EV_SVC_27_ATTEMPT_CNTR_READ                         ((Dcm_TskTaskEvMemType)0x01u)  /*!< Initiate attempt counter reading */
# define DCM_TSK_EV_SVC_27_ATTEMPT_CNTR_WRITE                        ((Dcm_TskTaskEvMemType)0x02u)  /*!< Initiate attempt counter writing */

/*! Registers the most significant bit in the event mask of the Dcm_Svc27Task() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
# define DCM_TSK_EV_SVC_27_MSB                                       0x02u

/*! Events of the Dcm_PagedBufferTask() */
# if (DCM_TSK_NUM_PGDBUF > 0)
#  define DCM_TSK_EV_PGDBUF_UPDATE_PAGE                              ((Dcm_TskTaskEvMemType)0x01u)  /*!< Request of next data portion of the paged-buffer response */
/*! Registers the most significant bit in the event mask of the Dcm_PagedBufferTask() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
#  define DCM_TSK_EV_PGDBUF_MSB                                      0x01u
# else
#  define DCM_TSK_EV_PGDBUF_MSB                                      0x00u
# endif

/*! Events of the Dcm_DiagTaskRecovery() */
# if (DCM_TSK_NUM_DIAG_RECOVERY > 0)                                                                                                                 /* COV_DCM_UNSUPPORTED XF */
#  define DCM_TSK_EV_DIAG_RECOVERY_GETSTATE                          ((Dcm_TskTaskEvMemType)0x01u)  /*!< Initiate recovery state retrieval */
#  define DCM_TSK_EV_DIAG_RECOVERY_PROCESS                           ((Dcm_TskTaskEvMemType)0x02u)  /*!< Processing of recovery info */
#  define DCM_TSK_EV_DIAG_RECOVERY_FINISH                            ((Dcm_TskTaskEvMemType)0x04u)  /*!< Gathering recovery information finished */

/*! Registers the most significant bit in the event mask of the Dcm_DiagTaskRecovery() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
#  define DCM_TSK_EV_DIAG_RECOVERY_MSB                               0x02u
# else
#  define DCM_TSK_EV_DIAG_RECOVERY_MSB                               0x00u
# endif

/*! Events of the Dcm_DiagTaskFblRes() */
# if (DCM_TSK_NUM_DIAG_FBLRES > 0)
#  define DCM_TSK_EV_DIAG_FBLRES_SEND                                ((Dcm_TskTaskEvMemType)0x01u)  /*!< Initiate FBL/APPL final response activity processing */
#  define DCM_TSK_EV_DIAG_FBLRES_CANCEL                              ((Dcm_TskTaskEvMemType)0x02u)  /*!< Cancels any further final response processing */
#  define DCM_TSK_EV_DIAG_FBLRES_WAITTXCOMM                          ((Dcm_TskTaskEvMemType)0x04u)  /*!< Waiting for ComM feedback */
#  define DCM_TSK_EV_DIAG_FBLRES_RSTFLAGS                            ((Dcm_TskTaskEvMemType)0x08u)  /*!< Reset the relevant flags to avoid re-sending of the response next boot */
#  define DCM_TSK_EV_DIAG_FBLRES_TXCONF                              ((Dcm_TskTaskEvMemType)0x10u)  /*!< Final response is sent */
/*! Registers the most significant bit in the event mask of the Dcm_DiagTaskFblRes() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
#  define DCM_TSK_EV_DIAG_FBLRES_MSB                                 0x10u
# else
#  define DCM_TSK_EV_DIAG_FBLRES_MSB                                 0x00u
# endif

/*! Events of the Dcm_DiagTaskTx() */
# define DCM_TSK_EV_DIAG_TX_SEND_LINEAR                              ((Dcm_TskTaskEvMemType)0x01u)  /*!< Initiate final positive response using linear buffer data provision */
# define DCM_TSK_EV_DIAG_TX_SEND_PAGED                               ((Dcm_TskTaskEvMemType)0x02u)  /*!< Initiate final positive response using paged-buffer data provision */
# define DCM_TSK_EV_DIAG_TX_SEND_RCRRP                               ((Dcm_TskTaskEvMemType)0x04u)  /*!< Initiate RCR-RP response transmission */
/*! Registers the most significant bit in the event mask of the Dcm_DiagTaskTx() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
# define DCM_TSK_EV_DIAG_TX_MSB                                      0x04u

/*! Events of the Dcm_NetTaskTx() */
# define DCM_TSK_EV_NET_TX_SEND                                      ((Dcm_TskTaskEvMemType)0x01u)  /*!< Activate the task by notifying at least one response transmission request is available */
/*! Registers the most significant bit in the event mask of the Dcm_NetTaskTx() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
# define DCM_TSK_EV_NET_TX_MSB                                       0x01u

/*! Events of the Dcm_NetTaskRx() */
# if (DCM_TSK_NUM_NET_RX > 0)
/*! Registers the most significant bit in the event mask of the Dcm_NetTaskRx() (used by the DCM core to determine the width of the task event registers)
    The MSB depends on the number of transport objects that receive diagnostic messages simultaneously.
    Note: Since used in a preprocessor calculation, do not use casted values */
#  define DCM_TSK_EV_NET_RX_MSB                                      (0x01UL << (DCM_NET_MAX_NUM_EVENT_TRANSP_OBJECTS - 1))
# else
#  define DCM_TSK_EV_NET_RX_MSB                                      0x00u
# endif

/* DiagGarbCol Task - identical  to Dcm_NetRxTask() */
# define DCM_TSK_EV_DIAG_GARB_COL_MSB                                DCM_TSK_EV_NET_RX_MSB
# define DCM_TSK_EV_DIAG_GARB_COL_MASK                               DCM_TSK_EV_NET_RX_MASK

/*! Events of the Dcm_ModeTaskMonitor() */
# if (DCM_TSK_NUM_MODE_MONITOR > 0)
#  define DCM_TSK_EV_MODE_MON_SVC85                                  ((Dcm_TskTaskEvMemType)0x01u)  /*!< Initiate monitoring on the auto-recovery mode rule for diagnostic service 0x85 */
#  define DCM_TSK_EV_MODE_MON_SVC28                                  ((Dcm_TskTaskEvMemType)0x02u)  /*!< Initiate monitoring on the auto-recovery mode rule for diagnostic service 0x28 */
/*! Registers the most significant bit in the event mask of the Dcm_ModeTaskMonitor() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
#  define DCM_TSK_EV_MODE_MON_MSB                                    0x02u
# else
#  define DCM_TSK_EV_MODE_MON_MSB                                    0x00u
# endif

/*! Events of the Dcm_Svc2ATaskSchdProcess() */
# if (DCM_TSK_NUM_SVC2A_SCHEDULER > 0)                                                                                                               /* COV_DCM_UNSUPPORTED XF */
#  define DCM_TSK_EV_SVC2A_SCHEDULER_PROCESS                         ((Dcm_TskTaskEvMemType)0x01u)  /*!< At lest one periodic DID timed out and shall be processed */
#  define DCM_TSK_EV_SVC2A_SCHEDULER_TMR_UPD                         ((Dcm_TskTaskEvMemType)0x02u)  /*!< All periodic DID timers shall be updated by one tick */
/*! Registers the most significant bit in the event mask of the Dcm_Svc2ATaskSchdProcess() (used by the DCM core to determine the width of the task event registers)
    Note: Since used in a preprocessor calculation, do not use casted values (i.e. the event with the highest value above) */
#  define DCM_TSK_EV_SVC2A_SCHEDULER_MSB                             0x02u
# else
#  define DCM_TSK_EV_SVC2A_SCHEDULER_MSB                             0x00u
# endif

/*! Summary of all tasks' event MSB used to calculated the optimal event mask data type (Dcm_TskTaskEvMemType/Dcm_TskTaskEvOptType) */
# define DCM_TSK_EV_SUM_OF_MSB                                       (DCM_TSK_EV_TIMER_MSB | \
                                                                     DCM_TSK_EV_ROE_MSB | \
                                                                     DCM_TSK_EV_DIAG_RX_MSB | \
                                                                     DCM_TSK_EV_DIAG_WORK_MSB | \
                                                                     DCM_TSK_EV_SVC_27_MSB | \
                                                                     DCM_TSK_EV_PGDBUF_MSB | \
                                                                     DCM_TSK_EV_DIAG_FBLRES_MSB |\
                                                                     DCM_TSK_EV_DIAG_TX_MSB | \
                                                                     DCM_TSK_EV_NET_TX_MSB | \
                                                                     DCM_TSK_EV_MODE_MON_MSB | \
                                                                     DCM_TSK_EV_SVC2A_SCHEDULER_MSB | \
                                                                     DCM_TSK_EV_NET_RX_MSB | \
                                                                     DCM_TSK_EV_DIAG_GARB_COL_MSB)

# if (DCM_TSK_EV_SUM_OF_MSB < 0x100u)                                                                                                                /* COV_DCM_SUPPORT_ALWAYS TX */
/*! System task event register mask value for up to 8 bits */
#  define DCM_TSK_EV_MASK                                            ((Dcm_TskTaskEvMemType)0xFFu)
/*! System task event register size for up to 8 bits */
#  define DCM_TSK_EV_NUM_BITS                                        8u
# else
#  if (DCM_TSK_EV_SUM_OF_MSB < 0x10000UL)
/*! System task event register mask value for up to 16 bits */
#   define DCM_TSK_EV_MASK                                           ((Dcm_TskTaskEvMemType)0xFFFFu)
/*! System task event register size for up to 16 bits */
#   define DCM_TSK_EV_NUM_BITS                                       16u
#  else
/*! 64bit platforms not yet considered! */
/*! System task event register mask value for up to 32 bits */
#   define DCM_TSK_EV_MASK                                           ((Dcm_TskTaskEvMemType)0xFFFFFFFFUL)
/*! System task event register size for up to 32 bits */
#   define DCM_TSK_EV_NUM_BITS                                       32u
#  endif
# endif

/*! All events of a system task event register (e.g. can be used for clearing all events of a task without exactly knowing which task and which events it supports) */
# define DCM_TSK_EV_ALL_EVENTS                                       DCM_TSK_EV_MASK

/*! Represents the most significant bit of a task register (task independent value) */
# define DCM_TSK_EV_MSB                                              (Dcm_UtiGetBitFromIndex(Dcm_TskTaskEvMemType,  (DCM_TSK_EV_NUM_BITS-1)))
/*! Calculation of all system timer IDs.
  Note: The same order defined here must be kept during the initialization of the table Dcm_TmrTimerInfo */
# define DCM_TMR_ID_P2                                               ((Dcm_TmrTimerIdMemType)(0 + 0))                                                                   /*!< The timer ID of the P2 timer */
# define DCM_TMR_ID_S3                                               ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_P2 + DCM_TMR_NUM_P2))                                          /*!< The timer ID of the S3 timer */
# define DCM_TMR_ID_FBLRES                                           ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_S3 + DCM_TMR_NUM_S3))                                          /*!< The timer ID of the ComM going to FullCommMode after ECU power-on/reset timer */
# define DCM_TMR_ID_SECURITY_0                                       ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_FBLRES + DCM_TMR_NUM_FBLRES))                                  /*!< The timer ID of the diagnostic service 0x27 failed attempt delay base timer */
# define DCM_TMR_ID_SECURITY_1                                       ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_SECURITY_0 + DCM_TMR_NUM_SECURITY_0))
# define DCM_TMR_ID_PERIODIC_TX                                      ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_SECURITY_1 + DCM_TMR_NUM_SECURITY_1))                          /*!< The timer ID of the periodic message transmission base timer */
# define DCM_TMR_ID_SVC2A_SCHEDULER                                  ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_PERIODIC_TX + DCM_TMR_NUM_PERIODIC_TX))                        /*!< The timer ID of the diagnostic service 0x2A periodic DID scheduler base timer */
# define DCM_TMR_ID_SVC86_INTERMESSAGETIME                           ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_SVC2A_SCHEDULER + DCM_TMR_NUM_SVC2A_SCHEDULER))                /*!< The timer ID of the diagnostic service 0x86 intermessage timer */
# define DCM_TMR_ID_KEEP_ALIVE                                       ((Dcm_TmrTimerIdMemType)(DCM_TMR_ID_SVC86_INTERMESSAGETIME + DCM_TMR_NUM_SVC86_INTERMESSAGETIME))  /*!< The timer ID of the extended keep-alive timer */

/**
 * Definition and calculation the total number of system timers
 */
# define DCM_TMR_NUM_P2                                              1u /*!< A single timer for P2 monitoring is always needed */
# define DCM_TMR_NUM_S3                                              1u /*!< A single timer for S3 monitoring is always needed */
# if (DCM_DIAG_JUMPFROMFBL_ENABLED == STD_ON)
#  define DCM_TMR_NUM_FBLRES                                         1u /*!< A single timer for monitoring the time between ECU start up and ComM going into FullComMode is needed */
# else
#  define DCM_TMR_NUM_FBLRES                                         0u /*!< Just a bridge to accomplish the amount of timers calculation */
# endif
# if (DCM_STATE_SEC_RETRY_ENABLED == STD_ON)                                                                                                         /* COV_DCM_UNSUPPORTED XF */
#  define DCM_TMR_NUM_SECURITY_0                                     1u /*!< A single timer for monitoring all security access delay times is needed */
# else
#  define DCM_TMR_NUM_SECURITY_0                                     0u /*!< Just a bridge to accomplish the amount of timers calculation */
# endif
# if (DCM_STATE_SEC_TIMER_1_ENABLED == STD_ON)                                                                                                       /* COV_DCM_UNSUPPORTED XF */
#  define DCM_TMR_NUM_SECURITY_1                                     1u
# else
#  define DCM_TMR_NUM_SECURITY_1                                     0u
# endif
# if (DCM_NET_PERIODIC_TX_ENABLED == STD_ON)                                                                                                         /* COV_DCM_UNSUPPORTED XF */
#  define DCM_TMR_NUM_PERIODIC_TX                                    1u /*!< A single timer for monitoring all periodic message transmission times is needed */
# else
#  define DCM_TMR_NUM_PERIODIC_TX                                    0u /*!< Just a bridge to accomplish the amount of timers calculation */
# endif
# if (DCM_SVC_2A_SUPPORT_ENABLED == STD_ON) && \
     (DCM_SPLIT_TASKS_ENABLED    == STD_ON)                                                                                                          /* COV_DCM_UNSUPPORTED XF xf tf */
#  define DCM_TMR_NUM_SVC2A_SCHEDULER                                1u /*!< A single timer for monitoring periodic DID scheduler timers is needed */
# else
#  define DCM_TMR_NUM_SVC2A_SCHEDULER                                0u /*!< Just a bridge to accomplish the amount of timers calculation */
# endif
# if (DCM_SVC_86_TIMER_ENABLED == STD_ON)                                                                                                            /* COV_DCM_UNSUPPORTED XF */
#  define DCM_TMR_NUM_SVC86_INTERMESSAGETIME                         1u /*!< A single timer for managing the RoE transmission intermessage time is needed */
# else
#  define DCM_TMR_NUM_SVC86_INTERMESSAGETIME                         0u /*!< Just a bridge to accomplish the amount of timers calculation */
# endif
# if (DCM_NET_KEEP_ALIVE_TIME_ENABLED == STD_ON)
#  define DCM_TMR_NUM_KEEP_ALIVE                                     1u /*!< A single timer for monitoring the extended keep-alive delay time is needed */
# else
#  define DCM_TMR_NUM_KEEP_ALIVE                                     0u /*!< Just a bridge to accomplish the amount of timers calculation */
# endif

/*! Pre-compile total number of system timers calculation.
    Note: Do not cast the sum, since it is used within a pre-processor arithmetic expression (refer to Dcm_TmrMaskMemType definition section) */
# define DCM_TMR_NUM_TIMERS                                          ( DCM_TMR_NUM_P2 \
                                                                     + DCM_TMR_NUM_S3 \
                                                                     + DCM_TMR_NUM_FBLRES \
                                                                     + DCM_TMR_NUM_SECURITY_0 \
                                                                     + DCM_TMR_NUM_SECURITY_1 \
                                                                     + DCM_TMR_NUM_PERIODIC_TX \
                                                                     + DCM_TMR_NUM_SVC2A_SCHEDULER \
                                                                     + DCM_TMR_NUM_SVC86_INTERMESSAGETIME \
                                                                     + DCM_TMR_NUM_KEEP_ALIVE)
/*! The casted version of the DCM_TMR_NUM_TIMERS within the C-code */
# define DCM_TMR_NUM_TIMERS_CASTED                                   ((Dcm_TmrTimerIdMemType) DCM_TMR_NUM_TIMERS)
# if (DCM_DEMAPIMGR_SUPPORT_ENABLED == STD_ON)
/*! Standard ISO 14229-1:2013 (UDS) DTC status bit representation */
#  define DCM_DTC_BIT_DONT_CARE                                      ((uint8)0x00u)
#  define DCM_DTC_BIT_TST_FLD                                        ((uint8)0x01u)
#  define DCM_DTC_BIT_TST_FLD_CYCL                                   ((uint8)0x02u)
#  define DCM_DTC_BIT_PNDG_DTC                                       ((uint8)0x04u)
#  define DCM_DTC_BIT_CONF_DTC                                       ((uint8)0x08u)
#  define DCM_DTC_BIT_TST_NOT_COMPL_CLR                              ((uint8)0x10u)
#  define DCM_DTC_BIT_TST_FLD_CLR                                    ((uint8)0x20u)
#  define DCM_DTC_BIT_TST_NOT_COMPL_CYCL                             ((uint8)0x40u)
#  define DCM_DTC_BIT_WARN_IND_REQ                                   ((uint8)0x80u)
# endif /* (DCM_DEMAPIMGR_SUPPORT_ENABLED == STD_ON) */
/*! The diagnostic sub-component internal states
  Note: Bit-mapped states chose, since multiple states can be active at a time (e.g. an still in processing and on transmission for paged-buffer responses) */
# define DCM_DIAG_STATE_IDLE                                         ((Dcm_DiagProcessorStateType)0x00u) /*!< No diagnostic service processing in progress (yet) */
# define DCM_DIAG_STATE_PROCESS                                      ((Dcm_DiagProcessorStateType)0x01u) /*!< A diagnostic request is in processing */
# define DCM_DIAG_STATE_ON_TX                                        ((Dcm_DiagProcessorStateType)0x02u) /*!< A diagnostic response is on transmission */
# define DCM_DIAG_STATE_POST_PROCESS                                 ((Dcm_DiagProcessorStateType)0x04u) /*!< A diagnostic request is in the post-processing phase */
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)                                                                                                          /* COV_DCM_UNSUPPORTED XF */
#  if (DCM_DCM_AR_VERSION == DCM_DCM_AR_VERSION_403)
#   define DCM_ROE_AR_STATE_ACTIVE                                   DCM_ROE_ACTIVE
#   define DCM_ROE_AR_STATE_INACTIVE                                 DCM_ROE_UNACTIVE
#   define Dcm_RoEOnEventStateChange(eventId, state)                 ((void)Dcm_ActivateEvent((eventId), (state)))                                   /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  elif (DCM_DCM_AR_VERSION == DCM_DCM_AR_VERSION_421) || \
        (DCM_DCM_AR_VERSION == DCM_DCM_AR_VERSION_422)
#   define DCM_ROE_AR_STATE_ACTIVE                                   RTE_MODE_DcmResponseOnEvent_EVENT_STARTED
#   define DCM_ROE_AR_STATE_INACTIVE                                 RTE_MODE_DcmResponseOnEvent_EVENT_STOPPED
#   define DCM_ROE_AR_STATE_CLEARED                                  RTE_MODE_DcmResponseOnEvent_EVENT_CLEARED
#   define Dcm_RoEOnEventStateChange(eventId, state)                 (Dcm_ModeSwitchRoE((state)))                                                    /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  else
#   error "Not supported AR version for RoE!"
#  endif
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
/* ----------------------------------------------
 ~&&&   Function-like macros
---------------------------------------------- */
/*! Endless loop pattern */
# define DCM_UTI_LOOP_FOR_EVER                                       for(;;)                                                                         /* PRQA S 3412 */ /* MD_MSR_19.4 */
/*! Bit scanner loop pattern (for atomic bit-sets with up to 32 bits) */
# define DCM_UTI_LOOP_BIT_SCAN(bitRegister)                          for(;(bitRegister) != 0; (bitRegister) >>= 1u)                                  /* PRQA S 3412 */ /* MD_MSR_19.4 */

/*! Move forward on pointer of abstract data */
# define Dcm_UtiNextItemByPtr(ptr, step)                             ((ptr)=&(ptr)[(step)])                                                          /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Promotes the sum of two integer arguments to a bigger integer data type to avoid result overflow */
# define Dcm_UtiPromotedSum(promoType, add1, add2)                   ((promoType)(((promoType)(add1)) + ((promoType)(add2))))                        /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Verifies if sum of two integer values is safe (will not cause result overflow) */
# define Dcm_UtiIsAdditionSafe(baseValueType, baseValue, add2)       (Dcm_UtiPromotedSum(baseValueType,(baseValue),(add2)) >= ((baseValueType)(baseValue))) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Sets single or multiple bits in an atomic bit-set */
# define Dcm_UtiBitOpSet(bitRegisterType, bitRegister, bits)         ((bitRegister) |= (bitRegisterType)(bits))                                      /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Clears single or multiple bits in an atomic bit-set */
# define Dcm_UtiBitOpClr(bitRegisterType, bitRegister, bits)         ((bitRegister) &= (bitRegisterType)(~(bits)))                                   /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns TRUE if at least one bit in an atomic bit-set is set */
# define Dcm_UtiBitOpTest(bitRegisterType, bitRegister, bits)        (((bitRegister) & (bitRegisterType)(bits)) != 0)                                /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Macros used instead of a function to avoid different memory pointer types and warnings for unused local functions! */

/*! Generic memory copy operation for array of elements (i.e. arrays of any data type) */
# define Dcm_UtiMemCopy(srcPtr, tgtPtr, length)                      {Dcm_CfgNetBufferSizeOptType memIter = (Dcm_CfgNetBufferSizeOptType)(length);while(memIter != 0u){--memIter; (tgtPtr)[memIter] = (srcPtr)[memIter];}} /* PRQA S 3453, 3458 */ /* MD_MSR_19.7, MD_MSR_19.4 */
/*! Generic RAM to RAM byte-wise memory copy operation */
# define Dcm_UtiByteMemCopy(srcPtr, tgtPtr, numBytes)                Dcm_UtiMemCopy((Dcm_Uint8VarDataPtrType)(srcPtr),(Dcm_Uint8VarDataPtrType)(tgtPtr), (numBytes)) /* PRQA S 3453, 3458 */ /* MD_MSR_19.7, MD_MSR_19.4 */
/*! Generic byte-wise memory copy operation from constant memory area */
# define Dcm_UtiConstByteMemCopy(srcPtr, tgtPtr, numBytes)           Dcm_UtiMemCopy((Dcm_Uint8ConstDataPtrType)(srcPtr),(Dcm_Uint8VarDataPtrType)(tgtPtr), (numBytes)) /* PRQA S 3453, 3458 */ /* MD_MSR_19.7, MD_MSR_19.4 */
/*! Generic memory set operation for array of elements (i.e. arrays of any data type) */
# define Dcm_UtiMemSetUintX(tgtPtr, uintType, uintValue, elements)   {Dcm_CfgNetBufferSizeOptType memIter = (Dcm_CfgNetBufferSizeOptType)(elements);while(memIter != 0u){--memIter; (tgtPtr)[memIter] = (uintType)(uintValue);}} /* PRQA S 3453, 3458 */ /* MD_MSR_19.7, MD_MSR_19.4 */
/*! Generic byte-wise direct memory set operation (i.e. writing to a physical address) */
# define Dcm_UtiMemSet(memAddr, uintValue, memSize, memLoc)          {uint16_least memIter; for(memIter = 0; memIter < (uint16_least)(memSize); ++memIter) {((P2VAR(uint8, TYPEDEF, memLoc))(memAddr))[memIter] = (uint8)(uintValue);}} /* PRQA S 3453, 3458 */ /* MD_MSR_19.7, MD_MSR_19.4 */

/*! For debug purpose only: RAM shredding to catch any uninitialized memory location */
# if (DCM_DEV_RAM_SHREDDER_ENABLED == STD_ON)                                                                                                        /* COV_DCM_UNSUPPORTED XF */
/*! A variable of any type located in RAM will be shredded */
#  define Dcm_UtiRamShredder(ramObject, memLoc)                      Dcm_UtiRamShredderByPoniter(&(ramObject), Dcm_UtiGetNumElementsOfTable(ramObject, uint8), memLoc) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! An array of a specific type located in RAM will be shredded */
#  define Dcm_UtiRamShredderArray(memAddr, baseType, numEl, memLoc)  {uint16_least arrayIter; for(arrayIter = 0; arrayIter < (uint16_least)(numEl); ++arrayIter) { Dcm_UtiRamShredderByPoniter(&((memAddr)[arrayIter]),sizeof(baseType), memLoc);}} /* PRQA S 3453, 3458 */ /* MD_MSR_19.7, MD_MSR_19.4 */
/*! A generic RAM shredder of RAM data located at a specific physical address */
#  define Dcm_UtiRamShredderByPoniter(memAddr, memSize, memLoc)      Dcm_UtiMemSet((P2VAR(uint8, TYPEDEF, memLoc))(memAddr), 0xAAu, memSize, memLoc) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# else
/*! No RAM shredding needed */
#  define Dcm_UtiRamShredder(ramObject, memLoc)                      /* not used */
/*! No RAM shredding needed */
#  define Dcm_UtiRamShredderArray(memAddr, baseType, numEl, memLoc)  /* not used */
/*! No RAM shredding needed */
#  define Dcm_UtiRamShredderByPoniter(memAddr, memSize, memLoc)      /* not used */
# endif

/* Assignment operator of struct data objects to workaround any possible compiler issues */
# if (DCM_UTI_STRUCT_ASSIGNMENT_ENABLED == STD_ON)
/*! Assign a value of structure data type per simple assignment operator (i.e. let the compiler do the job) */
#  define Dcm_UtiAssignStruct(strLhs, strRhs )                       ((strLhs) = (strRhs))                                                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
# else
/*! Assign a value of structure data type per byte-wise memory copy operation (i.e. serialize the data structure) */
#  define Dcm_UtiAssignStruct(strLhs, strRhs)                        Dcm_UtiByteMemCopy(&(strRhs), &(strLhs), sizeof(strLhs))                        /* PRQA S 3453 */ /* MD_MSR_19.7 */
# endif

/*! Returns the number of bits within any signed/unsigned integer data type */
# define Dcm_UtiGetNumBitsOfXintType(xintType)                       ((uint8)( sizeof(xintType) * 8u ))                                              /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns a value of an unsigned integer type with a specific number of bits set starting with bit0 */
# define Dcm_UtiGetMaskFromXintType(uintType, numBits)               ( (uintType)(((uintType)((1uL << ((numBits)-1)) -1uL)) | ((uintType)( 1uL << ((numBits)-1)))) ) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Returns the maximum possible unsigned integer value that can be stored in a specific unsigned integer data type */
# define Dcm_UtiMaxValueOfUintType(uintType)                         (Dcm_UtiGetMaskFromXintType(uintType,Dcm_UtiGetNumBitsOfXintType(uintType)))    /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns the maximum possible signed integer value that can be stored in a specific signed integer data type */
# define Dcm_UtiMaxValueOfSintType(sintType)                         ( (sintType)( (sintType)((1uL << (Dcm_UtiGetNumBitsOfXintType(sintType)-1)) -1uL)) ) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Returns an atomic bit-set with just one bit set at specific position */
# define Dcm_UtiGetBitFromIndex(bitsetBaseType, bitIdx)              ((bitsetBaseType)(((bitsetBaseType)0x01u)<<(bitIdx)))                           /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns TRUE if the atomic bit-set contains exactly one bit set, otherwise returns FALSE */
# define Dcm_UtiIsPowerOfTwo(bitsetBaseType, bitSet)                 (((bitSet) != 0) && (((bitSet) & ((bitsetBaseType)((bitSet) - 1))) == 0))       /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Generic bit-set pattern (with unlimited size) represented as array of bit registers of a specific (platform optimized) width */
/*! Returns the row number in the bit-set that contains a specific bit */
# define Dcm_UtiBitSetGetRowIdx(bitsetBaseType, bit)                 ( (bit) / Dcm_UtiGetNumBitsOfXintType(bitsetBaseType) )                         /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns the position in a row where the bit-set contains a specific bit */
# define Dcm_UtiBitSetGetColIdx(bitsetBaseType, bit)                 ( (bit) % Dcm_UtiGetNumBitsOfXintType(bitsetBaseType) )                         /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns the bit mask corresponding to a specific bit within a single bit-set row */
# define Dcm_UtiBitSetBitAt(bitsetBaseType, bit)                     ( (bitsetBaseType)(Dcm_UtiGetBitFromIndex(bitsetBaseType, Dcm_UtiBitSetGetColIdx(bitsetBaseType, (bit))) ) ) /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns the bit-set row that contains a specific bit  */
# define Dcm_UtiBitSetAtRow(bitSet, bitsetBaseType, bit)             ( (bitSet)[ Dcm_UtiBitSetGetRowIdx(bitsetBaseType, (bit)) ] )                   /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Returns the number of elements a bit-set array needs to fit given amount of bit */
# define Dcm_UtiBitSetCalcSize(bitsetBaseType, bits)                 ( ( ((bits) - 1u) / Dcm_UtiGetNumBitsOfXintType(bitsetBaseType) ) + 1u )        /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns TRUE if a specific bit in a bit-set is set */
# define Dcm_UtiBitSetTestBit(bitsetBaseType, bitSet, bit)           ( Dcm_UtiBitOpTest(bitsetBaseType, Dcm_UtiBitSetAtRow((bitSet), bitsetBaseType, (bit)), Dcm_UtiBitSetBitAt(bitsetBaseType, (bit))) ) /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Sets a specific bit in a bit-set */
# define Dcm_UtiBitSetSetBit(bitsetBaseType, bitSet, bit)            ( Dcm_UtiBitOpSet( bitsetBaseType, Dcm_UtiBitSetAtRow((bitSet), bitsetBaseType, (bit)), Dcm_UtiBitSetBitAt(bitsetBaseType, (bit))) ) /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Clears a specific bit in a bit-set */
# define Dcm_UtiBitSetClrBit(bitsetBaseType, bitSet, bit)            ( Dcm_UtiBitOpClr( bitsetBaseType, Dcm_UtiBitSetAtRow((bitSet), bitsetBaseType, (bit)), Dcm_UtiBitSetBitAt(bitsetBaseType, (bit))) ) /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Template for set/unset bits in a general purpose bit-set */
# define Dcm_UtiGenericBitSetCalcSize(bits)                          (Dcm_UtiBitSetCalcSize(Dcm_UtiBitSetBaseType, (bits)))                          /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_UtiGenericBitSetTestBit(bitSet, bit)                    (Dcm_UtiBitSetTestBit(Dcm_UtiBitSetBaseType, (bitSet), (bit)))                  /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_UtiGenericBitSetSetBit(bitSet, bit)                     (Dcm_UtiBitSetSetBit(Dcm_UtiBitSetBaseType, (bitSet), (bit)))                   /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_UtiGenericBitSetClrBit(bitSet, bit)                     (Dcm_UtiBitSetClrBit(Dcm_UtiBitSetBaseType, (bitSet), (bit)))                   /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Returns the argument with the lower value */
# define Dcm_UtiMathMin(a, b)                                        (((a)<=(b))?(a):(b))                                                            /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Returns the number of elements of a table */
# define Dcm_UtiGetNumElementsOfTable(table, baseType)               (sizeof(table)/sizeof(baseType))                                                /* PRQA S 3453 */ /* MD_MSR_19.7 */

/* Template for classic stack implementation stackVar must of type Dcm_UtiStackType */

/*! Initializes a stack object */
# define Dcm_UtiStackInit(stackVar)                                  ((stackVar).StackTop=-1)                                                        /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Pushes a single element to a stack */
# define Dcm_UtiStackPush(stackVar, value)                           ((stackVar).Stack[++((stackVar).StackTop)]=(value))                             /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Pops a single element from a stack */
# define Dcm_UtiStackPop(stackVar)                                   (--((stackVar).StackTop))                                                       /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns the element on the top of a stack */
# define Dcm_UtiStackTop(stackVar)                                   ((stackVar).Stack[(stackVar).StackTop])                                         /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns TRUE if stack is full, otherwise returns FALSE */
# define Dcm_UtiStackIsFull(stackVar, stackBaseType)                 (((stackVar).StackTop) >= (Dcm_UtiStackCntrType)(Dcm_UtiGetNumElementsOfTable((stackVar).Stack, stackBaseType) - 1)) /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Returns TRUE if stack is empty, otherwise returns FALSE */
# define Dcm_UtiStackIsEmpty(stackVar)                               (((stackVar).StackTop) < 0)                                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
# if (DCM_BSW_ENV_ASR_VERSION_3XX_ENABLED == STD_ON)                                                                                                 /* COV_DCM_UNSUPPORTED XF */
/*! AR 3.x DET API Det_ReportError adapter */
#  define Dcm_DebugCallDetReportError(apiId, errId)                  (Det_ReportError((uint16)(DCM_MODULE_ID), (uint8)0, (uint8)(apiId), (uint8)(errId))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# endif /* (DCM_BSW_ENV_ASR_VERSION_3XX_ENABLED == STD_ON) */
# if (DCM_BSW_ENV_ASR_VERSION_4XX_ENABLED == STD_ON) || \
     (DCM_BSW_ENV_ASR_VERSION_401_ENABLED == STD_ON)
/*! AR 4.x DET API Det_ReportError adapter */
#  define Dcm_DebugCallDetReportError(apiId, errId)                  ((void)Det_ReportError((uint16)(DCM_MODULE_ID), (uint8)0, (uint8)(apiId), (uint8)(errId))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# endif /* (DCM_BSW_ENV_ASR_VERSION_4XX_ENABLED == STD_ON) || \
 (DCM_BSW_ENV_ASR_VERSION_401_ENABLED == STD_ON) */
/*! Optional development error reporting */
# if(DCM_DEV_ERROR_REPORT == STD_ON)
/* If DET is enabled, a MISRA-C:2004 analysis will yield deviations to the rules:
 *  - 14.3 Before pre-processing, a null statement shall only occur on a line by itself; it may be followed by a comment provided that the first character following the null statement is a white-space character.
 *  - 19.4 C macros shall only expand to a braced initializer, a constant, a parenthesized expression, a type qualifier, a storage class specifier, or a do-while-zero construct.
 *  - 19.7 A function should be used in preference to a function-like macro.
 *  These deviations are caused by design of the runtime/resource optimized DET handling and are globally justified.
 */
#  define Dcm_DebugReportError(apiId, errId)                         (Dcm_DebugCallDetReportError((apiId), (errId)))                                 /* PRQA S 3453 */ /* MD_MSR_19.7 */
# else
#  define Dcm_DebugReportError(apiId, errId)                         /* not used */
# endif

/* Optional SW-C/Callout API return value checks */
# define Dcm_DebugApiCheckRte(cond, apiId, errId)                    /* Not used */
# define Dcm_DebugApiCheckRteAlways(apiId, errId)                    /* Not used */

/*! Optional DCM internal debugging support for additional, deeper analysis */
# if(DCM_DEBUG_ERROR_DETECT == STD_ON)                                                                                                               /* COV_DCM_DEV_DEBUG TX */
#  define Dcm_DebugAssertAlways(apiId, errId)                        { Dcm_DebugAssertReport((apiId),(errId)); }                                     /* PRQA S 3458 */ /* MD_MSR_19.4 */
#  define Dcm_DebugAssert(cond, apiId, errId)                        if(!(cond)) Dcm_DebugAssertAlways((apiId), (errId))                             /* PRQA S 3412 */ /* MD_MSR_19.4 */
# else
#  define Dcm_DebugAssert(cond, apiId, errId)                        /* not used */
#  define Dcm_DebugAssertAlways(apiId, errId)                        /* not used */
# endif
/*! Tests whether at least one event specified by ev is set in task local register evReg */
# define Dcm_TskIsLocalEventSet(evReg, ev)                           (Dcm_UtiBitOpTest(Dcm_TskTaskEvOptType, (evReg), (ev)))                         /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Sets task local event(s) (for global setting use Dcm_TskSetEvent()) */
# define Dcm_TskSetLocalEvent(evReg, ev)                             (Dcm_UtiBitOpSet( Dcm_TskTaskEvOptType, (evReg), (ev)))                         /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Clears task local event(s) (for global clearing use Dcm_TskClrEvent()) */
# define Dcm_TskClrLocalEvent(evReg, ev)                             (Dcm_UtiBitOpClr( Dcm_TskTaskEvOptType, (evReg), (ev)))                         /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! A generic task event scanner/iterator */
# define DCM_TSK_EVENT_SCAN_LOOP(evReg)                              DCM_UTI_LOOP_BIT_SCAN(evReg)                                                    /* PRQA S 3453 */ /* MD_MSR_19.7 */
/*! Converts a time value in milliseconds to system internal time base unit */
# define Dcm_TmrMillisecondsToTicks(ms)                              ((Dcm_TmrTimerCntrMemType)((ms)/DCM_TASK_CYCLE_MS))                             /* PRQA S 3453 */ /* MD_MSR_19.7 */
# if (DCM_DEMAPIMGR_SUPPORT_ENABLED == STD_ON)
#  if (DCM_DEM_API_403_ENABLED == STD_ON)                                                                                                            /* COV_DCM_UNSUPPORTED XF */
/*! AR 4.0.3 DEM API compliant return values */

/*! Return values for Dem_ReturnGetFreezeFrameByDTCType */
#   define DCM_DEM_RET_FFDATABYDTC_OK                                DEM_GET_FFDATABYDTC_OK
#   define DCM_DEM_RET_FFDATABYDTC_W_DTC                             DEM_GET_FFDATABYDTC_WRONG_DTC
#   define DCM_DEM_RET_FFDATABYDTC_W_ORIGIN                          DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN
#   define DCM_DEM_RET_FFDATABYDTC_W_RNUM                            DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER
#   define DCM_DEM_RET_FFDATABYDTC_W_BUFSIZE                         DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE
#   define DCM_DEM_RET_FFDATABYDTC_PENDING                           DEM_GET_FFDATABYDTC_PENDING

/*! Return values for Dcm_DemReturnGetFreezeFrameDataByRecordType */
#   define DCM_DEM_RET_FFBYRECORD_OK                                 DEM_GET_FFBYRECORD_OK
#   define DCM_DEM_RET_FFBYRECORD_NO_DTC                             DEM_GET_FFBYRECORD_NO_DTC_FOR_RECORD

/*! Return values for Dcm_DemReturnGetSizeOfEDRByDTCType */
#   define DCM_DEM_RET_SIZEOFEDR_OK                                  DEM_GET_SIZEOFEDRBYDTC_OK
#   define DCM_DEM_RET_SIZEOFEDR_W_DTC                               DEM_GET_SIZEOFEDRBYDTC_W_DTC
#   define DCM_DEM_RET_SIZEOFEDR_W_ORIGIN                            DEM_GET_SIZEOFEDRBYDTC_W_DTCOR
#   define DCM_DEM_RET_SIZEOFEDR_W_RNUM                              DEM_GET_SIZEOFEDRBYDTC_W_RNUM
#   define DCM_DEM_RET_SIZEOFEDR_PENDING                             DEM_GET_SIZEOFEDRBYDTC_PENDING

/*! Return values for Dem_ReturnGetSizeOfFreezeFrameByDTCType */
#   define DCM_DEM_RET_SIZEOFFFR_OK                                  DEM_GET_SIZEOFFF_OK
#   define DCM_DEM_RET_SIZEOFFFR_W_DTC                               DEM_GET_SIZEOFFF_WRONG_DTC
#   define DCM_DEM_RET_SIZEOFFFR_W_ORIGIN                            DEM_GET_SIZEOFFF_WRONG_DTCOR
#   define DCM_DEM_RET_SIZEOFFFR_W_RNUM                              DEM_GET_SIZEOFFF_WRONG_RNUM
#   define DCM_DEM_RET_SIZEOFFFR_PENDING                             DEM_GET_SIZEOFFF_PENDING

/*! Return values for Dem_ReturnGetDTCByOccurrenceType */
#   define DCM_DEM_RET_OCCURR_OK                                     DEM_OCCURR_OK
#   define DCM_DEM_RET_OCCURR_NOT_AVAILABLE                          DEM_OCCURR_NOT_AVAILABLE

/*! Return values for Dem_ReturnGetNextFilteredDTCType */
#   define DCM_DEM_RET_FILTERED_OK                                   DEM_FILTERED_OK
#   define DCM_DEM_RET_FILTERED_NO_ITEMS                             DEM_FILTERED_NO_MATCHING_DTC
#   define DCM_DEM_RET_FILTERED_PENDING                              DEM_FILTERED_PENDING
/*
Shall not be used:
#define DCM_DEM_RET_FILTERED_BUFFER_TOO_SMALL
 */

/*! Return values for Dcm_DemReturnGetSeverityOfDTCType */
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_OK                        DEM_GET_SEVERITYOFDTC_OK
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_WRONG_DTC                 DEM_GET_SEVERITYOFDTC_WRONG_DTC
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_NOSEVERITY                DEM_GET_SEVERITYOFDTC_NOSEVERITY
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_PENDING                   DEM_GET_SEVERITYOFDTC_PENDING

/*! Return values for Dcm_DemReturnGetFunctionalUnitOfDTCType */
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_OK                    DEM_GET_FUNCTIONALUNITOFDTC_OK
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_WRONG_DTC             DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC

/*! Return values for Dcm_DemReturnSetFilterType */
#   define DCM_DEM_RET_FILTER_ACCEPTED                               DEM_FILTER_ACCEPTED
#   define DCM_DEM_RET_WRONG_FILTER                                  DEM_WRONG_FILTER

/*! Return values for Dem_ReturnClearDTCType */
#   define DCM_DEM_RET_CLEAR_OK                                      DEM_CLEAR_OK
#   define DCM_DEM_RET_CLEAR_W_DTC                                   DEM_CLEAR_WRONG_DTC
#   define DCM_DEM_RET_CLEAR_W_ORIGIN                                DEM_CLEAR_WRONG_DTCORIGIN
#   define DCM_DEM_RET_CLEAR_FAILED                                  DEM_CLEAR_FAILED
#   define DCM_DEM_RET_CLEAR_PENDING                                 DEM_CLEAR_PENDING
/*
Shall not be used:
#define DCM_DEM_RET_CLEAR_BUSY
#define DCM_DEM_RET_CLEAR_MEMORY_ERROR
 */

/*! Return values for Dem_GetStatusOfDTCType */
#   define DCM_DEM_RET_STATUS_OK                                     DEM_STATUS_OK
#   define DCM_DEM_RET_STATUS_PENDING                                DEM_STATUS_PENDING
#   define DCM_DEM_RET_STATUS_WRONG_DTC                              DEM_STATUS_WRONG_DTC
#   define DCM_DEM_RET_STATUS_FAILED                                 DEM_STATUS_FAILED
#   define DCM_DEM_RET_STATUS_WRONG_DTCORIGIN                        DEM_STATUS_WRONG_DTCORIGIN

/* Return values for Dem_ReturnGetNumberOfFilteredDTCType */
#   define DCM_DEM_RET_NUMBER_OK                                     DEM_NUMBER_OK
#   define DCM_DEM_RET_NUMBER_PENDING                                DEM_NUMBER_PENDING

/* Return values for Dem_ReturnControlDTCSettingType */
#   define DCM_DEM_RET_CONTROL_DTC_SETTING_OK                        DEM_CONTROL_DTC_SETTING_OK
#   define DCM_DEM_RET_CONTROL_DTC_SETTING_N_OK                      DEM_CONTROL_DTC_SETTING_N_OK
#   define DCM_DEM_RET_CONTROL_DTC_WRONG_DTCGROUP                    DEM_CONTROL_DTC_WRONG_DTCGROUP

/* Return values for Dem_ReturnGetExtendedDataRecoredByDTCType */
#   define DCM_DEM_RET_GET_EXT_DATA_REC_OK                           DEM_RECORD_OK
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_DTC                    DEM_RECORD_WRONG_DTC
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_DTCORIGIN              DEM_RECORD_WRONG_DTCORIGIN
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_NUMBER                 DEM_RECORD_WRONG_NUMBER
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_BUFFERSIZE             DEM_RECORD_WRONG_BUFFERSIZE
#   define DCM_DEM_RET_GET_EXT_DATA_REC_PENDING                      DEM_RECORD_PENDING

#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_OK                         DEM_DISABLE_DTCRECUP_OK
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_WRONG_DTC                  DEM_DISABLE_DTCRECUP_WRONG_DTC
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_WRONG_DTCORIGIN            DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_PENDING                    DEM_DISABLE_DTCRECUP_PENDING

/*! AR 4.0.3 DEM API compliant return types */
#   define Dcm_DemReturnGetNextFilteredItemType                      Dem_ReturnGetNextFilteredDTCType
#   define Dcm_DemReturnGetSizeOfFFRByDTCType                        Dem_ReturnGetSizeOfFreezeFrameByDTCType
#   define Dcm_DemReturnGetSizeOfEDRByDTCType                        Dem_ReturnGetSizeOfExtendedDataRecordByDTCType
#   define Dcm_DemReturnGetFreezeFrameDataByRecordType               Dem_ReturnGetFreezeFrameDataByRecordType

/*! AR 4.0.3 DEM API function name substitutions - generic rename */
#   define Dcm_DemAPI(name)                                          Dem_ ## name                                                                    /* PRQA S 0342 */ /* MD_Dcm_Consistency_0342 */

/*! AR 4.0.3 DEM API function name substitutions - special cases */
#   define Dcm_DemAPI_CancelOperation                                Dem_DcmCancelOperation
#   define Dcm_DemAPI_GetOBDFreezeFrameData(recNum, dtcOrigin, dtc, buffer, bufferSize) (Dem_GetFreezeFrameDataByRecord((recNum), (dtcOrigin), (dtc), (buffer), (bufferSize))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#   define Dcm_DemAPI_ControlDTCStatusChangedNotification(active)    Dem_DcmControlDTCStatusChangedNotification((active))                            /* PRQA S 3453 */ /* MD_MSR_19.7 */

#  elif (DCM_DEM_API_412_ENABLED == STD_ON) || \
        (DCM_DEM_API_421_ENABLED == STD_ON)                                                                                                          /* COV_DCM_SUPPORT_RESTRICTED TX tf tf */
/*! AR 4.1.2+ DEM API compliant return values */

/*! Return values for Dem_ReturnGetFreezeFrameByDTCType */
#   define DCM_DEM_RET_FFDATABYDTC_OK                                DEM_GET_FFDATABYDTC_OK
#   define DCM_DEM_RET_FFDATABYDTC_W_DTC                             DEM_GET_FFDATABYDTC_WRONG_DTC
#   define DCM_DEM_RET_FFDATABYDTC_W_ORIGIN                          DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN
#   define DCM_DEM_RET_FFDATABYDTC_W_RNUM                            DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER
#   define DCM_DEM_RET_FFDATABYDTC_W_BUFSIZE                         DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE
#   define DCM_DEM_RET_FFDATABYDTC_PENDING                           DEM_GET_FFDATABYDTC_PENDING

/*! Return values for Dcm_DemReturnGetFreezeFrameDataByRecordType */
#   define DCM_DEM_RET_FFBYRECORD_OK                                 E_OK
#   define DCM_DEM_RET_FFBYRECORD_NO_DTC                             E_NOT_OK

/*! Return values for Dcm_DemReturnGetSizeOfFFRByDTCType (ED) */
#   define DCM_DEM_RET_SIZEOFEDR_OK                                  DEM_GETSIZEBYDTC_OK
#   define DCM_DEM_RET_SIZEOFEDR_W_DTC                               DEM_GETSIZEBYDTC_WRONG_DTC
#   define DCM_DEM_RET_SIZEOFEDR_W_ORIGIN                            DEM_GETSIZEBYDTC_WRONG_DTCORIGIN
#   define DCM_DEM_RET_SIZEOFEDR_W_RNUM                              DEM_GETSIZEBYDTC_WRONG_RECNUM
#   define DCM_DEM_RET_SIZEOFEDR_PENDING                             DEM_GETSIZEBYDTC_PENDING

/*! Return values for Dcm_DemReturnGetSizeOfFFRByDTCType (FF) */
#   define DCM_DEM_RET_SIZEOFFFR_OK                                  DEM_GETSIZEBYDTC_OK
#   define DCM_DEM_RET_SIZEOFFFR_W_DTC                               DEM_GETSIZEBYDTC_WRONG_DTC
#   define DCM_DEM_RET_SIZEOFFFR_W_ORIGIN                            DEM_GETSIZEBYDTC_WRONG_DTCORIGIN
#   define DCM_DEM_RET_SIZEOFFFR_W_RNUM                              DEM_GETSIZEBYDTC_WRONG_RECNUM
#   define DCM_DEM_RET_SIZEOFFFR_PENDING                             DEM_GETSIZEBYDTC_PENDING

/*! Return values for Dem_ReturnGetDTCByOccurrenceType */
#   define DCM_DEM_RET_OCCURR_OK                                     DEM_OCCURR_OK
#   define DCM_DEM_RET_OCCURR_NOT_AVAILABLE                          DEM_OCCURR_NOT_AVAILABLE

/*! Return values for Dcm_DemReturnGetNextFilteredElementType */
#   define DCM_DEM_RET_FILTERED_OK                                   DEM_FILTERED_OK
#   define DCM_DEM_RET_FILTERED_NO_ITEMS                             DEM_FILTERED_NO_MATCHING_ELEMENT
#   define DCM_DEM_RET_FILTERED_PENDING                              DEM_FILTERED_PENDING
#   define DCM_DEM_RET_FILTERED_BUFFER_TOO_SMALL                     DEM_FILTERED_BUFFER_TOO_SMALL

/*! Return values for Dcm_DemReturnGetSeverityOfDTCType */
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_OK                        DEM_GET_SEVERITYOFDTC_OK
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_WRONG_DTC                 DEM_GET_SEVERITYOFDTC_WRONG_DTC
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_NOSEVERITY                DEM_GET_SEVERITYOFDTC_NOSEVERITY
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_PENDING                   DEM_GET_SEVERITYOFDTC_PENDING

/*! Return values for Dcm_DemReturnGetFunctionalUnitOfDTCType */
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_OK                    DEM_GET_FUNCTIONALUNITOFDTC_OK
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_WRONG_DTC             DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC

/*! Return values for Dcm_DemReturnSetFilterType */
#   define DCM_DEM_RET_FILTER_ACCEPTED                               DEM_FILTER_ACCEPTED
#   define DCM_DEM_RET_WRONG_FILTER                                  DEM_WRONG_FILTER

/*! Return values for Dem_ReturnClearDTCType */
#   define DCM_DEM_RET_CLEAR_OK                                      DEM_CLEAR_OK
#   define DCM_DEM_RET_CLEAR_W_DTC                                   DEM_CLEAR_WRONG_DTC
#   define DCM_DEM_RET_CLEAR_W_ORIGIN                                DEM_CLEAR_WRONG_DTCORIGIN
#   define DCM_DEM_RET_CLEAR_FAILED                                  DEM_CLEAR_FAILED
#   define DCM_DEM_RET_CLEAR_PENDING                                 DEM_CLEAR_PENDING
#   define DCM_DEM_RET_CLEAR_BUSY                                    DEM_CLEAR_BUSY
/* Keep temporary DEM AR 4.2.1 compatibility */
#   if (DCM_DEM_API_421_ENABLED == STD_ON)
#    define DCM_DEM_RET_CLEAR_MEMORY_ERROR                           DEM_CLEAR_MEMORY_ERROR
#   else
 /* shall not be used */
#   endif

/*! Return values for Dem_GetStatusOfDTCType */
#   define DCM_DEM_RET_STATUS_OK                                     DEM_STATUS_OK
#   define DCM_DEM_RET_STATUS_PENDING                                DEM_STATUS_PENDING
#   define DCM_DEM_RET_STATUS_WRONG_DTC                              DEM_STATUS_WRONG_DTC
#   define DCM_DEM_RET_STATUS_FAILED                                 DEM_STATUS_FAILED
#   define DCM_DEM_RET_STATUS_WRONG_DTCORIGIN                        DEM_STATUS_WRONG_DTCORIGIN

/* Std_ReturnType */
#   define DCM_DEM_RET_NUMBER_OK                                     DEM_NUMBER_OK
#   define DCM_DEM_RET_NUMBER_PENDING                                DEM_NUMBER_PENDING

/* Dem_ReturnControlDTCSettingType */
#   define DCM_DEM_RET_CONTROL_DTC_SETTING_OK                        DEM_CONTROL_DTC_SETTING_OK
#   define DCM_DEM_RET_CONTROL_DTC_SETTING_N_OK                      DEM_CONTROL_DTC_SETTING_N_OK
#   define DCM_DEM_RET_CONTROL_DTC_WRONG_DTCGROUP                    DEM_CONTROL_DTC_WRONG_DTCGROUP

/* Return values for Dem_ReturnGetExtendedDataRecoredByDTCType */
#   define DCM_DEM_RET_GET_EXT_DATA_REC_OK                           DEM_RECORD_OK
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_DTC                    DEM_RECORD_WRONG_DTC
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_DTCORIGIN              DEM_RECORD_WRONG_DTCORIGIN
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_NUMBER                 DEM_RECORD_WRONG_NUMBER
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_BUFFERSIZE             DEM_RECORD_WRONG_BUFFERSIZE
#   define DCM_DEM_RET_GET_EXT_DATA_REC_PENDING                      DEM_RECORD_PENDING

#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_OK                         DEM_DISABLE_DTCRECUP_OK
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_WRONG_DTC                  DEM_DISABLE_DTCRECUP_WRONG_DTC
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_WRONG_DTCORIGIN            DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_PENDING                    DEM_DISABLE_DTCRECUP_PENDING

/*! AR 4.1.2+ DEM API compliant return types */
#   define Dcm_DemReturnGetNextFilteredItemType                      Dem_ReturnGetNextFilteredElementType
#   define Dcm_DemReturnGetSizeOfFFRByDTCType                        Dem_ReturnGetSizeOfDataByDTCType
#   define Dcm_DemReturnGetSizeOfEDRByDTCType                        Dem_ReturnGetSizeOfDataByDTCType
#   define Dcm_DemReturnGetFreezeFrameDataByRecordType               Std_ReturnType

/*! AR 4.1.2+ DEM API function name substitutions - generic rename */
#   define Dcm_DemAPI(name)                                          Dem_Dcm ## name                                                                 /* PRQA S 0342 */ /* MD_Dcm_Consistency_0342 */

/*! AR 4.1.2+ DEM API function name substitutions - special cases */
#   define Dcm_DemAPI_CancelOperation                                Dem_DcmCancelOperation
#   define Dcm_DemAPI_GetOBDFreezeFrameData(recNum, dtcOrigin, dtc, buffer, bufferSize) (Dem_DcmGetOBDFreezeFrameData((dtc), (buffer), (bufferSize))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#   define Dcm_DemAPI_ControlDTCStatusChangedNotification(active)    Dem_DcmControlDTCStatusChangedNotification((active))                            /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  elif (DCM_DEM_API_430_ENABLED == STD_ON)
/* return values */

/* Std_ReturnType */
#   define DCM_DEM_RET_FFDATABYDTC_OK                                E_OK
#   define DCM_DEM_RET_FFDATABYDTC_W_DTC                             DEM_WRONG_DTC
#   define DCM_DEM_RET_FFDATABYDTC_W_ORIGIN                          DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_FFDATABYDTC_W_RNUM                            DEM_NO_SUCH_ELEMENT
#   define DCM_DEM_RET_FFDATABYDTC_W_BUFSIZE                         DEM_BUFFER_TOO_SMALL
#   define DCM_DEM_RET_FFDATABYDTC_PENDING                           DEM_PENDING

/* Std_ReturnType */
#   define DCM_DEM_RET_FFBYRECORD_OK                                 E_OK
#   define DCM_DEM_RET_FFBYRECORD_NO_DTC                             E_NOT_OK

/* Std_ReturnType */
#   define DCM_DEM_RET_SIZEOFEDR_OK                                  E_OK
#   define DCM_DEM_RET_SIZEOFEDR_N_OK                                E_NOT_OK
#   define DCM_DEM_RET_SIZEOFEDR_W_DTC                               DEM_WRONG_DTC
#   define DCM_DEM_RET_SIZEOFEDR_W_ORIGIN                            DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_SIZEOFEDR_W_RNUM                              DEM_NO_SUCH_ELEMENT
#   define DCM_DEM_RET_SIZEOFEDR_PENDING                             DEM_PENDING

/* Std_ReturnType */
#   define DCM_DEM_RET_SIZEOFFFR_OK                                  E_OK
#   define DCM_DEM_RET_SIZEOFFFR_N_OK                                E_NOT_OK
#   define DCM_DEM_RET_SIZEOFFFR_W_DTC                               DEM_WRONG_DTC
#   define DCM_DEM_RET_SIZEOFFFR_W_ORIGIN                            DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_SIZEOFFFR_W_RNUM                              DEM_NO_SUCH_ELEMENT
#   define DCM_DEM_RET_SIZEOFFFR_PENDING                             DEM_PENDING

/* Std_ReturnType */
#   define DCM_DEM_RET_OCCURR_OK                                     E_OK
#   define DCM_DEM_RET_OCCURR_N_OK                                   E_NOT_OK
#   define DCM_DEM_RET_OCCURR_NO_SUCH_ELEMENT                        DEM_NO_SUCH_ELEMENT

/* Std_ReturnType */
#   define DCM_DEM_RET_FILTERED_OK                                   E_OK
#   define DCM_DEM_RET_FILTERED_NO_ITEMS                             DEM_NO_SUCH_ELEMENT
#   define DCM_DEM_RET_FILTERED_PENDING                              DEM_PENDING
#   define DCM_DEM_RET_FILTERED_BUFFER_TOO_SMALL                     DEM_BUFFER_TOO_SMALL

/* Std_ReturnType */
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_OK                        E_OK
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_WRONG_DTC                 DEM_WRONG_DTC
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_WRONG_DTCORIGIN           DEM_WRONG_DTCORIGIN
/* # define DCM_DEM_RET_GET_SEVERITY_OF_DTC_NOSEVERITY */            /* not used anymore */
#   define DCM_DEM_RET_GET_SEVERITY_OF_DTC_PENDING                   DEM_PENDING

/* Std_ReturnType */
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_OK                    E_OK
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_PENDING               DEM_PENDING
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_WRONG_DTC             DEM_WRONG_DTC
#   define DCM_DEM_RET_GET_FUNCTIONALUNITOFDTC_WRONG_DTCORIGIN       DEM_WRONG_DTCORIGIN

/* Std_ReturnType */
#   define DCM_DEM_RET_FILTER_ACCEPTED                               E_OK
#   define DCM_DEM_RET_WRONG_FILTER                                  E_NOT_OK

/* Std_ReturnType */
#   define DCM_DEM_RET_CLEAR_OK                                      E_OK
#   define DCM_DEM_RET_CLEAR_PENDING                                 DEM_PENDING
#   define DCM_DEM_RET_CLEAR_BUSY                                    DEM_CLEAR_BUSY
#   define DCM_DEM_RET_CLEAR_MEMORY_ERROR                            DEM_CLEAR_MEMORY_ERROR
#   define DCM_DEM_RET_CLEAR_FAILED                                  DEM_CLEAR_FAILED
#   define DCM_DEM_RET_CLEAR_W_DTC                                   DEM_WRONG_DTC
#   define DCM_DEM_RET_CLEAR_W_ORIGIN                                DEM_WRONG_DTCORIGIN

/* Std_ReturnType */
#   define DCM_DEM_RET_STATUS_OK                                     E_OK
#   define DCM_DEM_RET_STATUS_PENDING                                DEM_PENDING
#   define DCM_DEM_RET_STATUS_WRONG_DTC                              DEM_WRONG_DTC
#   define DCM_DEM_RET_STATUS_WRONG_DTCORIGIN                        DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_STATUS_NO_SUCH_ELEMENT                        DEM_NO_SUCH_ELEMENT
/* # define DCM_DEM_RET_STATUS_FAILED */                             /* not used anymore */

/* Std_ReturnType */
#   define DCM_DEM_RET_NUMBER_OK                                     E_OK
#   define DCM_DEM_RET_NUMBER_PENDING                                DEM_PENDING

/* Std_ReturnType */
#   define DCM_DEM_RET_CONTROL_DTC_SETTING_OK                        E_OK
#   define DCM_DEM_RET_CONTROL_DTC_SETTING_PENDING                   DEM_PENDING

/* Return values for Dem_ReturnGetExtendedDataRecoredByDTCType */
#   define DCM_DEM_RET_GET_EXT_DATA_REC_OK                           E_OK
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_DTC                    DEM_WRONG_DTC
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_DTCORIGIN              DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_NUMBER                 DEM_NO_SUCH_ELEMENT
#   define DCM_DEM_RET_GET_EXT_DATA_REC_WRONG_BUFFERSIZE             DEM_BUFFER_TOO_SMALL
#   define DCM_DEM_RET_GET_EXT_DATA_REC_PENDING                      DEM_PENDING

#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_OK                         E_OK
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_WRONG_CONDITION            DEM_E_WRONG_CONDITION
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_WRONG_DTC                  DEM_WRONG_DTC
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_WRONG_DTCORIGIN            DEM_WRONG_DTCORIGIN
#   define DCM_DEM_RET_DISABLE_DTC_REC_UP_PENDING                    DEM_PENDING

/* types */
#   define Dem_ReturnGetStatusOfDTCType                              Std_ReturnType
#   define Dcm_DemReturnGetNextFilteredItemType                      Std_ReturnType
#   define Dcm_DemReturnGetSizeOfFFRByDTCType                        Dem_ReturnGetSizeOfDataByDTCType
#   define Dcm_DemReturnGetSizeOfEDRByDTCType                        Dem_ReturnGetSizeOfDataByDTCType
#   define Dcm_DemReturnGetFreezeFrameDataByRecordType               Std_ReturnType
#   define Dem_ReturnDisableDTCRecordUpdateType                      Std_ReturnType
#   define Dem_ReturnGetSeverityOfDTCType                            Std_ReturnType
#   define Dem_ReturnGetFunctionalUnitOfDTCType                      Std_ReturnType
#   define Dem_ReturnGetSizeOfDataByDTCType                          Std_ReturnType
#   define Dem_ReturnGetDTCByOccurrenceTimeType                      Std_ReturnType
#   define Dem_ReturnClearDTCType                                    Std_ReturnType
#   define Dem_ReturnControlDTCSettingType                           Std_ReturnType
#   define Dem_ReturnSetFilterType                                   Std_ReturnType
#   define Dem_ReturnGetNextFilteredElementType                      Std_ReturnType
#   define Dem_ReturnGetNumberOfFilteredDTCType                      Std_ReturnType

/* functions - generic rename */
#   define Dcm_DemAPI(name)                                          Dem_ ## name                                                                    /* PRQA S 0342 */ /* MD_Dcm_Consistency_0342 */

/* functions - special cases */
#   define Dcm_DemAPI_CancelOperation()                              /* Not used */
#   define Dcm_DemAPI_GetOBDFreezeFrameData(recNum, dtcOrigin, dtc, buffer, bufferSize) (Dem_DcmGetOBDFreezeFrameData((dtc), (buffer), (bufferSize))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#   define Dcm_DemAPI_ControlDTCStatusChangedNotification(active)    /* Not used */
#  else
#   error "Unknown DEM AR API interface!"
#  endif
# endif /* (DCM_DEMAPIMGR_SUPPORT_ENABLED == STD_ON) */
/*! Updates request message length by specific amount of data already processed */
# define Dcm_DiagUpdateReqLength(msgContextPtr, step)                ((msgContextPtr)->reqDataLen -= (Dcm_MsgLenType)(step))                         /* PRQA S 3453 */ /* MD_MSR_19.7 */

# define Dcm_DiagGetReqDataAt(msgContextPtr, index)                  ((Dcm_MsgType)&((msgContextPtr)->reqData[(index)]))                             /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_DiagGetReqDataRel(msgContextPtr, index)                 (Dcm_DiagGetReqDataAt((msgContextPtr), ((msgContextPtr)->reqIndex) + (index)))  /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_DiagGetReqData(msgContextPtr)                           (Dcm_DiagGetReqDataRel((msgContextPtr), 0))                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */

# define Dcm_DiagGetReqDataAsU8At(msgContextPtr, index)              (*(Dcm_DiagGetReqDataAt((msgContextPtr), (index))))                             /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_DiagGetReqDataAsU16At(msgContextPtr, index)             (Dcm_UtiMake16Bit((msgContextPtr)->reqData[(index) + 0], (msgContextPtr)->reqData[(index) + 1])) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_DiagGetReqDataAsU24At(msgContextPtr, index)             (Dcm_UtiMake32Bit(0, (msgContextPtr)->reqData[(index) + 0], (msgContextPtr)->reqData[(index) + 1], (msgContextPtr)->reqData[(index) + 2])) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_DiagGetReqDataAsU32At(msgContextPtr, index)             (Dcm_UtiMake32Bit((msgContextPtr)->reqData[(index) + 0], (msgContextPtr)->reqData[(index) + 1], (msgContextPtr)->reqData[(index) + 2], (msgContextPtr)->reqData[(index) + 3])) /* PRQA S 3453 */ /* MD_MSR_19.7 */

# define Dcm_DiagGetReqDataAsU8Rel(msgContextPtr, index)             (Dcm_DiagGetReqDataAsU8At((msgContextPtr), ((msgContextPtr)->reqIndex + (index)))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_DiagGetReqDataAsU16Rel(msgContextPtr, index)            (Dcm_DiagGetReqDataAsU16At((msgContextPtr), ((msgContextPtr)->reqIndex + (index)))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_DiagGetReqDataAsU24Rel(msgContextPtr, index)            (Dcm_DiagGetReqDataAsU24At((msgContextPtr), ((msgContextPtr)->reqIndex + (index)))) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_DiagGetReqDataAsU32Rel(msgContextPtr, index)            (Dcm_DiagGetReqDataAsU32At((msgContextPtr), ((msgContextPtr)->reqIndex + (index)))) /* PRQA S 3453 */ /* MD_MSR_19.7 */

# define Dcm_DiagGetReqDataAsU8(msgContextPtr)                       (Dcm_DiagGetReqDataAsU8Rel((msgContextPtr), 0))                                 /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_DiagGetReqDataAsU16(msgContextPtr)                      (Dcm_DiagGetReqDataAsU16Rel((msgContextPtr), 0))                                /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_DiagGetReqDataAsU24(msgContextPtr)                      (Dcm_DiagGetReqDataAsU24Rel((msgContextPtr), 0))                                /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_DiagGetReqDataAsU32(msgContextPtr)                      (Dcm_DiagGetReqDataAsU32Rel((msgContextPtr), 0))                                /* PRQA S 3453 */ /* MD_MSR_19.7 */

/*! Return pointer to response buffer */
# define Dcm_DiagGetResDataRel(msgContextPtr, index)                 (Dcm_DiagGetResDataAt((msgContextPtr), ((msgContextPtr)->resIndex) + (index)))  /* PRQA S 3453 */ /* MD_MSR_19.7 */
# define Dcm_DiagGetResData(msgContextPtr)                           (Dcm_DiagGetResDataRel((msgContextPtr), 0))                                     /* PRQA S 3453 */ /* MD_MSR_19.7 */
/* ----------------------------------------------
 ~&&&   Typedefs
---------------------------------------------- */
/*! Stack size data type for up to 32768 elements */
typedef sint16       Dcm_UtiStackCntrType;
/*! Platform optimized base data type for bit-sets */
typedef uint8_least  Dcm_UtiBitSetBaseType;
/*! Data type for the DCM initialization state */
typedef uint8 Dcm_DebugInitStateType;
typedef P2FUNC (Std_ReturnType, DCM_CODE, Dcm_RepeaterProxyFuncType) (Dcm_OpStatusType, Dcm_MsgContextPtrType);
typedef uint8 Dcm_RepeaterSvcContextHandleType;
/*! Base data type for a task identifier (Valid values: DCM_TSK_ID_*) */
typedef uint8        Dcm_TskTaskIdMemType;
typedef uint8_least  Dcm_TskTaskIdOptType;

# if (DCM_TSK_EV_NUM_BITS <= 8)                                                                                                                      /* COV_DCM_SUPPORT_ALWAYS TX */
/*! Base data type for a task event when all configured tasks do need no more than 8 events (Valid values: DCM_TSK_EV_*) */
typedef uint8        Dcm_TskTaskEvMemType;
typedef uint8_least  Dcm_TskTaskEvOptType;
# else
#  if (DCM_TSK_EV_NUM_BITS <= 16)
/*! Base data type for a task event when all configured tasks do need no more than 16 events (Valid values: DCM_TSK_EV_*) */
typedef uint16        Dcm_TskTaskEvMemType;
typedef uint16_least  Dcm_TskTaskEvOptType;
#  else                                                                                                                                              /* COV_DCM_UNSUPPORTED XF */
/*! Base data type for a task event when all configured tasks do need no more than 32 events (Valid values: DCM_TSK_EV_*)
    Note: (the limit of 32 is verified during the calculation of DCM_TSK_EV_NUM_BITS)  */
typedef uint32        Dcm_TskTaskEvMemType;
typedef uint32_least  Dcm_TskTaskEvOptType;
#  endif
# endif
/*! Base data type for a generic pointer to a task event register */
typedef P2VAR(Dcm_TskTaskEvOptType, TYPEDEF, AUTOMATIC) Dcm_TskTaskEvPtrType;
/*! Base data type for system timer handles  (no more than 32 timers supported for now: see Dcm_TmrMaskMemType definition section)*/
typedef uint8        Dcm_TmrTimerIdMemType;
typedef uint8_least  Dcm_TmrTimerIdOptType;

# if (DCM_TMR_NUM_TIMERS <= 8u)                                                                                                                      /* COV_DCM_SUPPORT_ALWAYS TX */
/*! Base data type (memory consumption and runtime optimized) for a timer-pool bitmap when no more than 8 system timers are needed */
typedef uint8        Dcm_TmrMaskMemType;
typedef uint8_least  Dcm_TmrMaskOptType;
# elif (DCM_TMR_NUM_TIMERS <= 16u)
/*! Base data type (memory consumption and runtime optimized) for a timer-pool bitmap when no more than 16 system timers are needed */
typedef uint16        Dcm_TmrMaskMemType;
typedef uint16_least  Dcm_TmrMaskOptType;
# elif (DCM_TMR_NUM_TIMERS <= 32u)
/*! Base data type (memory consumption and runtime optimized) for a timer-pool bitmap when no more than 32 system timers are needed */
typedef uint32        Dcm_TmrMaskMemType;
typedef uint32_least  Dcm_TmrMaskOptType;
# else
#  error "Too many system timers!"
# endif
/*! A sub-service length (i.e. sub-function and eventually some data byte) must always fit the linear buffer size (no paged-buffer request reception) */
typedef Dcm_CfgNetBufferSizeMemType Dcm_DiagSubServiceLengthType;
/*! A sub-service (also called sub-function) reference cannot exceed 255 (even 127) since all services having sub-functions do support the SPRMIB which limits the value range of a single byte to 0x7Fu = 127 */
typedef uint8 Dcm_DiagSubServiceRefMemType;
typedef uint8_least Dcm_DiagSubServiceRefOptType;
typedef P2VAR(Dcm_DiagSubServiceRefOptType, TYPEDEF, DCM_VAR_NOINIT)  Dcm_DiagSubServiceRefOptPtrType;
/*! Base data type for the diagnostic sub-component internal state machine */
typedef uint8 Dcm_DiagProcessorStateType;
/* ----------------------------------------------
 ~&&&   Module internal inlined function declarations
---------------------------------------------- */
# define DCM_START_SEC_CODE
/*lint -save -esym(961, 19.1)*/
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*lint -restore*/
/**********************************************************************************************************************
 *  Dcm_UtiMemCopyBuffer()
 *********************************************************************************************************************/
/*! \brief          Copies data from the given source pointer to the target pointer.
 *  \details        This function is a wrapper for Dcm_UtiMemCopy with additional checks of the input parameter.
 *  \param[in]      sourcePtr    Pointer to the source buffer
 *  \param[in]      targetPtr    Pointer to the target buffer
 *  \param[in]      targetPos    Buffer position where the data should be written to
 *  \param[in]      targetSize   Size of the target buffer
 *  \param[in]      length       Amount of data which should be written
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiMemCopyBuffer(Dcm_ConstReadOnlyMsgType sourcePtr
                                                          ,Dcm_ConstMsgType targetPtr
                                                          ,Dcm_CfgNetBufferSizeOptType targetPos
                                                          ,Dcm_CfgNetBufferSizeOptType targetSize
                                                          ,Dcm_CfgNetBufferSizeOptType length);
/**********************************************************************************************************************
 *  Dcm_DiagHandleApplNrc()
 *********************************************************************************************************************/
/*! \brief          Verifies application feedback plausibility and corrects NRC if needed.
 *  \details        Provides default NRC handling in case an application callout has "forgotten" to do it
 *  \param[in]      StdResultAppl   The callout result from the application
 *  \param[in,out]  ErrorCodeAppl   The NRC from the application callout (in) and corrected one (out)
 *  \param[in]      DefaultNrc      The NRC to be used for correction in case application has not set any appropriate one
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagHandleApplNrc(Std_ReturnType StdResultAppl
                                                           ,Dcm_NegativeResponseCodePtrType ErrorCodeAppl
                                                           ,Dcm_NegativeResponseCodeType DefaultNrc);

/**********************************************************************************************************************
 *  Dcm_DiagSetReqDataAsU8At()
 *********************************************************************************************************************/
/*! \brief          Set request value in response buffer at a particular position.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      index         Index to response buffer
 *  \param[in]      value         Value to copy to response buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagSetReqDataAsU8At(Dcm_MsgContextPtrType pMsgContext
                                                              ,Dcm_DiagBufferIndexType index
                                                              ,uint8 value);

/**********************************************************************************************************************
 *  Dcm_DiagSetReqDataAsU8()
 *********************************************************************************************************************/
/*! \brief          Set request value in response buffer at current position.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      value         Value to copy to response buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagSetReqDataAsU8(Dcm_MsgContextPtrType pMsgContext
                                                            ,uint8 value);

/**********************************************************************************************************************
 *  Dcm_DiagSetResDataAsU8At()
 *********************************************************************************************************************/
/*! \brief          Set response value in response buffer.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      index         Index to response buffer
 *  \param[in]      value         Value to copy to response buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagSetResDataAsU8At(Dcm_MsgContextPtrType pMsgContext
                                                              ,Dcm_DiagBufferIndexType index
                                                              ,uint8 value);

/**********************************************************************************************************************
 *  Dcm_DiagUpdateResLength()
 *********************************************************************************************************************/
/*! \brief          Updates response length and remaining size of response buffer
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      numBytes      Number of bytes
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagUpdateResLength(Dcm_MsgContextPtrType pMsgContext
                                                             ,Dcm_MsgLenType numBytes);

/**********************************************************************************************************************
 *  Dcm_DiagProvideResData()
 *********************************************************************************************************************/
/*! \brief          Moves index of response buffer and updates response buffer parameters
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      numBytes      Number of bytes
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideResData(Dcm_MsgContextPtrType pMsgContext
                                                            ,Dcm_MsgLenType numBytes);

/**********************************************************************************************************************
 *  Dcm_DiagProvideResDataAsU8()
 *********************************************************************************************************************/
/*! \brief          Sets UINT8 Value in response buffer and updates response buffer parameters
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      value         Value to be written tor response buffer
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideResDataAsU8(Dcm_MsgContextPtrType pMsgContext
                                                                ,uint8 value);

/**********************************************************************************************************************
 *  Dcm_DiagProvideResDataAsU16()
 *********************************************************************************************************************/
/*! \brief          Sets UINT16 Value in response buffer and updates response buffer parameters
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      value         Value to be written tor response buffer
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideResDataAsU16(Dcm_MsgContextPtrType pMsgContext
                                                                ,uint16 value);

/**********************************************************************************************************************
 *  Dcm_DiagProvideResDataAsU24()
 *********************************************************************************************************************/
/*! \brief          Sets UINT24 Value in response buffer and updates response buffer parameters
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      value         Value to be written tor response buffer
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideResDataAsU24(Dcm_MsgContextPtrType pMsgContext
                                                                 ,uint32 value);

/**********************************************************************************************************************
 *  Dcm_DiagProvideResDataAsU32()
 *********************************************************************************************************************/
/*! \brief          Sets UINT32 Value in response buffer and updates response buffer parameters
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      value         Value to be written tor response buffer
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideResDataAsU32(Dcm_MsgContextPtrType pMsgContext
                                                                 ,uint32 value);

/**********************************************************************************************************************
 *  Dcm_DiagProvideResDataAsUN()
 *********************************************************************************************************************/
/*! \brief          Copies response data to response buffer and updates response buffer parameters
 *  \details        Copy given number of bytes from source buffer to response buffer
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      pSource       Pointer to source buffer
 *  \param[in]      size          Size of response data that shall be copied
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideResDataAsUN(Dcm_MsgContextPtrType pMsgContext
                                                                ,Dcm_ConstReadOnlyMsgType pSource
                                                                ,Dcm_MsgLenType size);

/**********************************************************************************************************************
 *  Dcm_DiagGetResDataAt()
 *********************************************************************************************************************/
/*! \brief          Returns pointer to response buffer.
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      index         Index to response buffer
 *  \return         Pointer to requested index of response buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Dcm_MsgType, DCM_CODE) Dcm_DiagGetResDataAt(Dcm_ReadOnlyMsgContextPtrType pMsgContext
                                                                 ,Dcm_DiagBufferIndexType index);

/**********************************************************************************************************************
 *  Dcm_DiagGetRemainingResLenWithOffset()
*********************************************************************************************************************/
/*! \brief          Returns remaining response buffer size reduced by given offset
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      offset        Offset value
 *  \return         Remaining buffer size reduced by offset
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
*********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Dcm_MsgLenType, DCM_CODE) Dcm_DiagGetRemainingResLenWithOffset(
                                                                             Dcm_ReadOnlyMsgContextPtrType pMsgContext
                                                                            ,Dcm_MsgLenType offset);

/**********************************************************************************************************************
 *  Dcm_DiagConsumeReqData()
 *********************************************************************************************************************/
/*! \brief          Moves index of request buffer and updates response length
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[in]      numBytes      Number of bytes
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagConsumeReqData(Dcm_MsgContextPtrType pMsgContext
                                                            ,Dcm_MsgLenType numBytes);

/**********************************************************************************************************************
 *  Dcm_DiagConsumeReqDataAsU8()
 *********************************************************************************************************************/
/*! \brief          Returns UINT8 value from request and updates request buffer parameter
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[out]     pValue        Pointer where value is written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagConsumeReqDataAsU8(Dcm_MsgContextPtrType pMsgContext
                                                                ,P2VAR(uint8, AUTOMATIC, AUTOMATIC) pValue);

/**********************************************************************************************************************
 *  Dcm_DiagConsumeReqDataAsU16()
 *********************************************************************************************************************/
/*! \brief          Returns UINT16 value from request and updates request buffer parameter
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[out]     pValue        Pointer where value is written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagConsumeReqDataAsU16(Dcm_MsgContextPtrType pMsgContext
                                                                 ,P2VAR(uint16, AUTOMATIC, AUTOMATIC) pValue);

/**********************************************************************************************************************
 *  Dcm_DiagConsumeReqDataAsU24()
 *********************************************************************************************************************/
/*! \brief          Returns UINT24 value from request and updates request buffer parameter
 *  \details        -
 *  \param[in,out]  pMsgContext   Current message context
 *  \param[out]     pValue        Pointer where value is written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagConsumeReqDataAsU24(Dcm_MsgContextPtrType pMsgContext
                                                                 ,P2VAR(uint32, AUTOMATIC, AUTOMATIC) pValue);

/**********************************************************************************************************************
 *  Dcm_DiagConsumeReqDataAsUN()
 *********************************************************************************************************************/
/*! \brief          Returns specified number of bytes from request buffer and updates request buffer parameters
 *  \details        -
 *  \param[in,out]  pMsgContext         Current message context
 *  \param[out]     pTarget             Pointer to target buffer
 *  \param[in]      sizeOfTargetBuffer  Size of target buffer
 *  \param[in]      numBytes            Number of bytes to be copied
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagConsumeReqDataAsUN(Dcm_MsgContextPtrType pMsgContext
                                                                ,P2VAR(uint8, AUTOMATIC, AUTOMATIC) pTarget
                                                                ,Dcm_MsgLenType sizeOfTargetBuffer
                                                                ,Dcm_MsgLenType numBytes);

/**********************************************************************************************************************
 *  Dcm_DiagInitDataContext()
 *********************************************************************************************************************/
/*! \brief          Initializes managed buffer data context.
 *  \param[out]     pDataContext    Pointer to the data context to be initialized
 *  \param[in]      Buffer          The buffer to be managed
 *  \param[in]      BufferSize      The size of the buffer to be managed
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagInitDataContext(Dcm_DiagDataContextPtrType pDataContext
                                                             ,Dcm_MsgType    Buffer
                                                             ,Dcm_MsgLenType BufferSize);

/**********************************************************************************************************************
 *  Dcm_DiagCommitData()
 *********************************************************************************************************************/
/*! \brief          Commits the data usage to a data context.
 *  \details        Updates only the usage information, no data will be changed.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      length          Number of bytes to commit
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagCommitData(Dcm_DiagDataContextPtrType pDataContext
                                                        ,Dcm_MsgLenType length);

/**********************************************************************************************************************
 *  Dcm_DiagRevertData()
 *********************************************************************************************************************/
/*! \brief          Reverts a specific amount of the data from a data context.
 *  \details        Updates only the usage information, no data will be changed.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      length          Number of bytes to commit
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagRevertData(Dcm_DiagDataContextPtrType  pDataContext
                                                        ,Dcm_MsgLenType length);

/**********************************************************************************************************************
 *  Dcm_DiagGetDataContextBuffer()
 *********************************************************************************************************************/
/*! \brief          Provides pointer to data context buffer
 *  \details        Provides pointer to current usage position of data context buffer
 *  \param[in]      pDataContext    Pointer to the data context
 *  \return         Pointer to current usage position of data context buffer
 *  \context        TASK
 *  \reentrant      TRUE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Dcm_MsgType, DCM_CODE) Dcm_DiagGetDataContextBuffer(Dcm_DiagDataContextPtrType pDataContext);

/**********************************************************************************************************************
 *  Dcm_DiagProvideDataAsU8()
 *********************************************************************************************************************/
/*! \brief          Provides data to the current data context.
 *  \details        Updates the usage information after writing to the buffer.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      value           Value to be written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideDataAsU8(Dcm_DiagDataContextPtrType pDataContext, uint8 value);

/**********************************************************************************************************************
 *  Dcm_DiagProvideDataAsU24()
 *********************************************************************************************************************/
/*! \brief          Provides data to the current data context.
 *  \details        Updates the usage information after writing to the buffer. Only the three lower bytes are written.
 *  \param[in,out]  pDataContext    Pointer to the data context
 *  \param[in]      value           Value to be written
 *  \context        TASK
 *  \reentrant      FALSE
 *  \pre            -
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideDataAsU24(Dcm_DiagDataContextPtrType pDataContext, uint32 value);
# define DCM_STOP_SEC_CODE
/*lint -save -esym(961, 19.1)*/
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*lint -restore*/
/* ----------------------------------------------
 ~&&&   Module internal API function declarations
---------------------------------------------- */
# define DCM_START_SEC_CODE
/*lint -save -esym(961, 19.1)*/
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*lint -restore*/
/**********************************************************************************************************************
 *  Dcm_UtiLookUpUint8()
 *********************************************************************************************************************/
/*! \brief          Searches a byte table for an element.
 *  \details        -
 *  \param[in]      lookUpTable    Pointer to the table to be scanned
 *  \param[in]      value          Value to be found (first element is table-size!)
 *  \return         -1             Look up failed (no match)
 *  \return         >=0            Success, index of the matched position
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(sint16_least, DCM_CODE) Dcm_UtiLookUpUint8(Dcm_Uint8ConstDataPtrType lookUpTable, uint8 value);

# if(DCM_UTI_NVM_READ_ENABLED == STD_ON)                                                                                                             /* COV_DCM_UNSUPPORTED XF */
/**********************************************************************************************************************
 *  Dcm_UtiNvMRead()
 *********************************************************************************************************************/
/*! \brief          Reads a NvM data block
 *  \details        -
 *  \param[in]      opStatus     The operation status
 *  \param[out]     data         Data buffer for the result
 *  \param[in]      blockId      Id of the NvRam block
 *  \return         DCM_E_OK        Read operation finished successfully.
 *  \return         DCM_E_NOT_OK    Read operation finished with error or got canceled.
 *  \return         DCM_E_PENDING   Read operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiNvMRead(Dcm_OpStatusType                opStatus
                                             ,Dcm_GenericDcmRamNoInitPtrType  data
                                             ,uint16                          blockId);
# endif

# if(DCM_UTI_NVM_WRITE_ENABLED == STD_ON)                                                                                                            /* COV_DCM_UNSUPPORTED XF */
/**********************************************************************************************************************
 *  Dcm_UtiNvMWrite()
 *********************************************************************************************************************/
/*! \brief          Writes a NvM data block
 *  \details        -
 *  \param[in]      opStatus     The operation status
 *  \param[in]      data         Data buffer of the content to be written
 *  \param[in]      blockId      Id of the NvRam block
 *  \return         DCM_E_OK        Write operation finished successfully.
 *  \return         DCM_E_NOT_OK    Write operation finished with error or got canceled.
 *  \return         DCM_E_PENDING   Write operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiNvMWrite(Dcm_OpStatusType                     opStatus
                                              ,Dcm_GenericDcmConstRamNoInitPtrType  data
                                              ,uint16                               blockId);
# endif

# if(DCM_UTI_NVM_SWCDATA_WRITE_ENABLED == STD_ON)                                                                                                    /* COV_DCM_UNSUPPORTED XF */
/**********************************************************************************************************************
 *  Dcm_UtiNvMSwcDataWrite()
 *********************************************************************************************************************/
/*! \brief          Writes a NvM data block that is used by a SW-C.
 *  \details        -
 *  \param[in]      opStatus     The operation status
 *  \param[in]      data         Data buffer of the content to be written
 *  \param[in]      blockId      Id of the NvRam block
 *  \return         DCM_E_OK        Write operation finished successfully.
 *  \return         DCM_E_NOT_OK    Write operation finished with error or got canceled.
 *  \return         DCM_E_PENDING   Write operation needs more time to be accomplished.
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    FALSE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_UtiNvMSwcDataWrite(Dcm_OpStatusType                     opStatus
                                                     ,Dcm_GenericDcmConstRamNoInitPtrType  data
                                                     ,uint16                               blockId);
# endif
# if(DCM_EXT_NEED_API_DEBUGISMODULEINITIALIZED_ENABLED == STD_ON)                                                                                    /* COV_DCM_UNSUPPORTED XF */
/**********************************************************************************************************************
 *  Dcm_DebugIsModuleInitialized()
 *********************************************************************************************************************/
/*! \brief          Checks whether the DCM is initialized.
 *  \details        -
 *  \return         TRUE     The module is initialized
 *  \return         FALSE    The module is not initialized
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(boolean, DCM_CODE) Dcm_DebugIsModuleInitialized(void);
# endif

# if (DCM_DEV_RUNTIME_CHECKS == STD_ON)                                                                                                              /* COV_DCM_REQUIRED_BY_SAFEBSW TX */
/**********************************************************************************************************************
 *  Dcm_DebugCatchCriticalError()
 *********************************************************************************************************************/
/*! \brief          Catches critical errors by re-initializing DCM.
 *  \details        -
 *  \param[in]      extApiSid    Extended API Service ID
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_DebugCatchCriticalError(Dcm_ExtendedSidType extApiSid);
# endif
# if (DCM_NET_INTERNAL_REQ_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_NetRxIndInternal()
 *********************************************************************************************************************/
/*! \brief          Provides a means for virtual/internal diagnostic request.
 *  \details        This API is generally used for RoE (SID 0x86) purposes.
 *  \param[in]      rxPduId            The RxPDUID of the request
 *  \param[in]      data               The data of the request
 *  \param[in]      length             The length of the request
 *  \return         DCM_E_OK           Reception was successful
 *  \return         DCM_E_NOT_OK       Reception was not successful
 *  \context        ISR1|ISR2|TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_NetRxIndInternal(PduIdType     rxPduId
                                                   ,Dcm_MsgType   data
                                                   ,PduLengthType length);
# endif

# if (DCM_EXT_NEED_API_NETGETCOMSTATE_ENABLED == STD_ON)                                                                                             /* COV_DCM_UNSUPPORTED XF */
/**********************************************************************************************************************
 *  Dcm_NetGetComState()
 *********************************************************************************************************************/
/*! \brief          Returns the communication state for the given RxPduId.
 *  \details        -
 *  \param[in]      rxPduId    The RxPDUID of the request
 *  \return         The communication state
 *  \context        ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_NetComMStateType, DCM_CODE) Dcm_NetGetComState(PduIdType rxPduId);
# endif
# if (DCM_REPEATER_EXT_CONTEXT_GETTER_ENABLED == STD_ON)                                                                                             /* COV_DCM_UNSUPPORTED XF */
/**********************************************************************************************************************
 *  Dcm_RepeaterGetExtSvcContext()
 *********************************************************************************************************************/
/*! \brief          Returns the service context for a specific service context handle.
 *  \details        -
 *  \param[in]      handle    Abstract service handle
 *  \return         The service context
 *  \context        ISR1|ISR2
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_GenericDcmRamNoInitPtrType, DCM_CODE) Dcm_RepeaterGetExtSvcContext(Dcm_RepeaterSvcContextHandleType handle);
# endif
# if (DCM_MODEMGR_SUPPORT_ENABLED == STD_ON)                                                                                                         /* COV_DCM_SUPPORT_ALWAYS TX */
#  if (DCM_MODE_ROE_ENABLED == STD_ON)                                                                                                               /* COV_DCM_UNSUPPORTED XF */
/**********************************************************************************************************************
 *  Dcm_ModeSwitchRoE()
 *********************************************************************************************************************/
/*! \brief          Mode switching for RoE activation state change.
 *  \details        -
 *  \param[in]      mode    The mode
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_ModeSwitchRoE(Rte_ModeType_DcmResponseOnEvent mode);
#  endif
# endif /* (DCM_MODEMGR_SUPPORT_ENABLED == STD_ON) */
# if (DCM_TSK_NUM_ROE > 0)                                                                                                                           /* COV_DCM_UNSUPPORTED XF */
/**********************************************************************************************************************
 *  Dcm_ExtSvc86Task()
 *********************************************************************************************************************/
/*! \brief          Service 0x86 task.
 *  \details        Low priority task of the RoE sub-module.
 *  \param[in]      ev         The active event(s) of the task
 *  \param[in,out]  pPostEv    The event(s) to be processed next task activation
 *  \context        TASK
 *  \reentrant      FALSE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExtSvc86Task(Dcm_TskTaskEvOptType ev
                                     ,Dcm_TskTaskEvPtrType pPostEv);
# endif

/**********************************************************************************************************************
 *  Dcm_TskClrEvent()
 *********************************************************************************************************************/
/*! \brief          Clears event(s) of a task.
 *  \details        Clears the given events for a specific task.
 *  \param[in]      taskId    The task handle
 *  \param[in]      ev        The event(s) to be cleared
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_TskClrEvent(Dcm_TskTaskIdOptType taskId
                                    ,Dcm_TskTaskEvMemType ev);

/**********************************************************************************************************************
 *  Dcm_TskSetEvent()
 *********************************************************************************************************************/
/*! \brief          Notifies a task for events.
 *  \details        Sets an event for a specific task.
 *  \param[in]      taskId    The task handle
 *  \param[in]      ev        The event(s) to be cleared
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_TskSetEvent(Dcm_TskTaskIdOptType taskId
                                    ,Dcm_TskTaskEvMemType ev);
/**********************************************************************************************************************
 *  Dcm_TmrStopTimer()
 *********************************************************************************************************************/
/*! \brief          Stops a timer.
 *  \details        Stops a timer with the given timer ID.
 *  \param[in]      timerId    The timer handle
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_TmrStopTimer(Dcm_TmrTimerIdOptType timerId);

/**********************************************************************************************************************
 *  Dcm_TmrStopTimer()
 *********************************************************************************************************************/
/*! \brief          Starts a timer with a given time value.
 *  \details        Starts a timer with the given timer ID with the given time value.
 *  \param[in]      timerId      The timer handle
 *  \param[in]      timeTicks    The concrete time to elapse
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_TmrStartTimer(Dcm_TmrTimerIdOptType timerId
                                      ,Dcm_TmrTimerCntrMemType timeTicks);
/* --- Timer notification functions -------------------------------------------------------------------------------- */
# if (DCM_TMR_NUM_SVC86_INTERMESSAGETIME > 0)                                                                                                        /* COV_DCM_UNSUPPORTED XF */
/**********************************************************************************************************************
 *  Dcm_ExtOnTimeoutSvc86InterMessageTime()
 *********************************************************************************************************************/
/*! \brief          Service 0x86 timer function to trigger sampling for onDTCStatusChange events.
 *  \details        -
 *  \return         Returns always 0
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_TmrTimerCntrMemType, DCM_CODE) Dcm_ExtOnTimeoutSvc86InterMessageTime(void);
# endif
# if (DCM_EXT_NEED_API_DIAGGETACTIVITYSTATE_ENABLED == STD_ON)                                                                                       /* COV_DCM_UNSUPPORTED XF */
/**********************************************************************************************************************
 *  Dcm_DiagGetActivityState()
 *********************************************************************************************************************/
/*! \brief          Returns the DCM diagnostic sub-module activity state.
 *  \details        -
 *  \return         The current activity state
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(Dcm_DiagProcessorStateType, DCM_CODE) Dcm_DiagGetActivityState(void);
# endif
# if (DCM_EXT_NEED_API_VARMGRGETACTIVECOMVARIANT_ENABLED == STD_ON)                                                                                  /* COV_DCM_UNSUPPORTED XF */
/**********************************************************************************************************************
 *  Dcm_VarMgrGetActiveComVariant()
 *********************************************************************************************************************/
/*! \brief          Returns currently set variant.
 *  \details        Returns currently active communication variant.
 *  \return         Operation result
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC (Dcm_CfgVarMgrComVariantType, DCM_CODE) Dcm_VarMgrGetActiveComVariant(void);
# endif
# if (DCM_SVC_86_SUPPORT_ENABLED == STD_ON)                                                                                                          /* COV_DCM_UNSUPPORTED XF */
#  if (DCM_SVC_86_RST_ON_DSC_ENABLED == STD_ON)
/**********************************************************************************************************************
 *  Dcm_ExtSvc86OnChangeSession()
 *********************************************************************************************************************/
/*! \brief          Service 0x86 utility function to notify RoE about a session change.
 *  \details        -
 *  \param[in]      oldSession    The old session
 *  \param[in]      newSession    The old session
 *  \context        TASK
 *  \reentrant      TRUE
 *  \synchronous    TRUE
 *  \pre            -
 *********************************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_ExtSvc86OnChangeSession(Dcm_CfgStateGroupOptType oldSession
                                                ,Dcm_CfgStateGroupOptType newSession);
#  endif
# endif /* (DCM_SVC_86_SUPPORT_ENABLED == STD_ON) */
# define DCM_STOP_SEC_CODE
/*lint -save -esym(961, 19.1)*/
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*lint -restore*/
/* ----------------------------------------------
 ~&&&   Inlined function implementations
---------------------------------------------- */
# define DCM_START_SEC_CODE
/*lint -save -esym(961, 19.1)*/
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*lint -restore*/
/**********************************************************************************************************************
 *  Dcm_UtiMemCopyBuffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_UtiMemCopyBuffer(Dcm_ConstReadOnlyMsgType sourcePtr
                                                          ,Dcm_ConstMsgType targetPtr
                                                          ,Dcm_CfgNetBufferSizeOptType targetPos
                                                          ,Dcm_CfgNetBufferSizeOptType targetSize
                                                          ,Dcm_CfgNetBufferSizeOptType length)
{
  DCM_IGNORE_UNREF_PARAM(targetSize);                                                                                                                /* PRQA S 3112 */ /* MD_Dcm_3112 */

# if (DCM_DEV_RUNTIME_CHECKS == STD_ON)                                                                                                              /* COV_DCM_REQUIRED_BY_SAFEBSW TX */
  /* targetSize and targetPos are in not trusted relation (passed separately) so must be verified for correct relation, so the subtraction can be assumed valid. */
  if(  (targetSize < targetPos)
     ||((targetSize - targetPos) < length) )
  {
    Dcm_DebugCatchCriticalError(DCM_EXT_SID_UTIMEMCOPYBUFFER);
  }
  else
# endif
  {
    Dcm_UtiMemCopy(sourcePtr, &(targetPtr[targetPos]), length)                                                                                       /* SBSW_DCM_POINTER_MEMCPY_BUFFER */
  }
}
/**********************************************************************************************************************
 *  Dcm_DiagHandleApplNrc()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagHandleApplNrc(Std_ReturnType StdResultAppl                                                             /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                           ,Dcm_NegativeResponseCodePtrType ErrorCodeAppl
                                                           ,Dcm_NegativeResponseCodeType DefaultNrc)
{
  if( ( StdResultAppl == DCM_E_NOT_OK)
    &&(*ErrorCodeAppl == DCM_E_POSITIVERESPONSE) )
  {
    *ErrorCodeAppl = DefaultNrc;                                                                                                                     /* SBSW_DCM_PARAM_PTR_WRITE */
    Dcm_DebugReportError(DCM_SID_INTERNAL, DCM_E_PARAM);
  }
}

/**********************************************************************************************************************
 *  Dcm_DiagSetReqDataAsU8At()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagSetReqDataAsU8At(Dcm_MsgContextPtrType pMsgContext                                                     /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                              ,Dcm_DiagBufferIndexType index
                                                              ,uint8 value)
{
# if (DCM_DEV_RUNTIME_CHECKS == STD_ON)                                                                                                              /* COV_DCM_REQUIRED_BY_SAFEBSW TX */
  if (index >= pMsgContext->reqBufSize)
  {
    Dcm_DebugCatchCriticalError(DCM_EXT_SID_DIAGSETREQDATAASU8AT);
  }
  else
# endif
  {
    pMsgContext->reqData[index] = value;                                                                                                             /* SBSW_DCM_POINTER_WRITE_MESSAGE_CONTEXT_REQBUFFER */
  }
}

/**********************************************************************************************************************
 *  Dcm_DiagSetReqDataAsU8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagSetReqDataAsU8(Dcm_MsgContextPtrType pMsgContext                                                       /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                            ,uint8 value)
{
  Dcm_DiagSetReqDataAsU8At(pMsgContext, pMsgContext->reqIndex, value);                                                                               /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_DiagSetResDataAsU8At()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagSetResDataAsU8At(Dcm_MsgContextPtrType pMsgContext
                                                             ,Dcm_DiagBufferIndexType index
                                                             ,uint8 value)
{
# if (DCM_DEV_RUNTIME_CHECKS == STD_ON)                                                                                                              /* COV_DCM_REQUIRED_BY_SAFEBSW TX */
  if (index >= pMsgContext->resBufSize)
  {
    Dcm_DebugCatchCriticalError(DCM_EXT_SID_DIAGSETRESDATAASU8AT);
  }
  else
# endif
  {
    pMsgContext->resData[index] = value;                                                                                                             /* SBSW_DCM_POINTER_WRITE_MESSAGE_CONTEXT_RESBUFFER */
  }
}

/**********************************************************************************************************************
 *  Dcm_DiagUpdateResLength()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagUpdateResLength(Dcm_MsgContextPtrType pMsgContext
                                                             ,Dcm_MsgLenType numBytes)
{
# if (DCM_DEV_RUNTIME_CHECKS == STD_ON)                                                                                                              /* COV_DCM_REQUIRED_BY_SAFEBSW TX */
  /* pMsgContext->resMaxDataLen = pDataContext->resBufferSize - pDataContext->resIndex and is a trusted value.
   * All MsgContext values must be trusted values since modified only via the dedicated APIs, keeping them consistent. So the comparison is always valid.
   * Otherwise, nothing can help preventing buffer overflows
   * The only not trusted parameter is "numBytes".
   */
  if(pMsgContext->resMaxDataLen < numBytes)
  {
    Dcm_DebugCatchCriticalError(DCM_EXT_SID_DIAGUPDATERESLENGTH);
  }
  else
# endif
  {
    pMsgContext->resDataLen += numBytes;                                                                                                             /* SBSW_DCM_PARAM_PTR_WRITE */
    pMsgContext->resMaxDataLen -= numBytes;                                                                                                          /* SBSW_DCM_PARAM_PTR_WRITE */
  }
}

/**********************************************************************************************************************
 *  Dcm_DiagProvideResData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideResData(Dcm_MsgContextPtrType pMsgContext
                                                            ,Dcm_MsgLenType numBytes)
{
# if (DCM_DEV_RUNTIME_CHECKS == STD_ON)                                                                                                              /* COV_DCM_REQUIRED_BY_SAFEBSW TX */
  /* pMsgContext->resMaxDataLen = pDataContext->resBufferSize - pDataContext->resIndex and is a trusted value.
   * All MsgContext values must be trusted values since modified only via the dedicated APIs, keeping them consistent. So the comparison is always valid.
   * Otherwise, nothing can help preventing buffer overflows
   * The only not trusted parameter is "numBytes".
   */
  if(pMsgContext->resMaxDataLen < numBytes)
  {
    Dcm_DebugCatchCriticalError(DCM_EXT_SID_DIAGPROVIDERESDATA);
  }
  else
# endif
  {
    pMsgContext->resIndex += numBytes;                                                                                                               /* SBSW_DCM_PARAM_PTR_WRITE */
    Dcm_DiagUpdateResLength(pMsgContext, numBytes);                                                                                                  /* SBSW_DCM_PARAM_PTR_FORWARD */
  }
}

/**********************************************************************************************************************
 *  Dcm_DiagProvideResDataAsU8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideResDataAsU8(Dcm_MsgContextPtrType pMsgContext                                                   /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                                ,uint8 value)
{
  Dcm_DiagSetResDataAsU8At(pMsgContext, pMsgContext->resIndex, value);                                                                               /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagProvideResData(pMsgContext, 1);                                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_DiagProvideResDataAsU16()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideResDataAsU16(Dcm_MsgContextPtrType pMsgContext                                                  /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                                 ,uint16 value)
{
  Dcm_DiagSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 0), Dcm_UtiGetHiByte(value));                                                       /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 1), Dcm_UtiGetLoByte(value));                                                       /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagProvideResData(pMsgContext, 2);                                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_DiagProvideResDataAsU24()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideResDataAsU24(Dcm_MsgContextPtrType pMsgContext                                                  /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                                 ,uint32 value)
{
  Dcm_DiagSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 0), Dcm_UtiGetHiLoByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 1), Dcm_UtiGetLoHiByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 2), Dcm_UtiGetLoLoByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagProvideResData(pMsgContext, 3);                                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_DiagProvideResDataAsU32()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideResDataAsU32(Dcm_MsgContextPtrType pMsgContext                                                  /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                                 ,uint32 value)
{
  Dcm_DiagSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 0), Dcm_UtiGetHiHiByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 1), Dcm_UtiGetHiLoByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 2), Dcm_UtiGetLoHiByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagSetResDataAsU8At(pMsgContext, (pMsgContext->resIndex + 3), Dcm_UtiGetLoLoByte(value));                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagProvideResData(pMsgContext, 4);                                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_DiagProvideResDataAsUN()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideResDataAsUN(Dcm_MsgContextPtrType pMsgContext                                                   /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                                ,Dcm_ConstReadOnlyMsgType pSource
                                                                ,Dcm_MsgLenType size)
{
  Dcm_UtiMemCopyBuffer(pSource
                      ,pMsgContext->resData
                      ,(Dcm_CfgNetBufferSizeOptType)pMsgContext->resIndex
                      ,(Dcm_CfgNetBufferSizeOptType)pMsgContext->resBufSize
                      ,(Dcm_CfgNetBufferSizeOptType)size);                                                                                           /* SBSW_DCM_PARAM_PTR_FORWARD */

  Dcm_DiagProvideResData(pMsgContext, size);                                                                                                         /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_DiagGetResDataAt()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Dcm_MsgType, DCM_CODE) Dcm_DiagGetResDataAt(Dcm_ReadOnlyMsgContextPtrType pMsgContext                                          /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                                 ,Dcm_DiagBufferIndexType index)
{
  Dcm_MsgType pResData;
# if (DCM_DEV_RUNTIME_CHECKS == STD_ON)                                                                                                              /* COV_DCM_REQUIRED_BY_SAFEBSW TX */
  if (index >= pMsgContext->resBufSize)
  {
    Dcm_DebugCatchCriticalError(DCM_EXT_SID_DIAGGETRESDATAAT);
    pResData = (Dcm_MsgType)&pMsgContext->resData[0];
  }
  else
# endif
  {
    pResData = (Dcm_MsgType)&pMsgContext->resData[index];
  }

  return pResData;
}

/**********************************************************************************************************************
 *  Dcm_DiagGetRemainingResLenWithOffset()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Dcm_MsgLenType, DCM_CODE) Dcm_DiagGetRemainingResLenWithOffset(                                                                /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                                              Dcm_ReadOnlyMsgContextPtrType pMsgContext
                                                                             ,Dcm_MsgLenType offset)
{
  Dcm_MsgLenType lResMaxLen;

# if (DCM_DEV_RUNTIME_CHECKS == STD_ON)                                                                                                              /* COV_DCM_REQUIRED_BY_SAFEBSW TX */
  if (offset > pMsgContext->resMaxDataLen)
  {
    Dcm_DebugCatchCriticalError(DCM_EXT_SID_DIAGGETREAMINGRESLENWITHOFFSET);
    lResMaxLen = 0;
  }
  else
# endif
  {
    lResMaxLen = pMsgContext->resMaxDataLen - offset;
  }

  return lResMaxLen;
}

/**********************************************************************************************************************
 *  Dcm_DiagConsumeReqData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagConsumeReqData(Dcm_MsgContextPtrType pMsgContext
                                                            ,Dcm_MsgLenType numBytes)
{
  pMsgContext->reqIndex += (Dcm_DiagBufferIndexType)numBytes;                                                                                        /* SBSW_DCM_PARAM_PTR_WRITE */
  Dcm_DiagUpdateReqLength(pMsgContext, numBytes);                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
}

/**********************************************************************************************************************
 *  Dcm_DiagConsumeReqDataAsU8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagConsumeReqDataAsU8(Dcm_MsgContextPtrType pMsgContext                                                   /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                                ,P2VAR(uint8, AUTOMATIC, AUTOMATIC) pValue)
{
  *pValue = Dcm_DiagGetReqDataAsU8(pMsgContext);                                                                                                     /* SBSW_DCM_PARAM_PTR_WRITE */
  Dcm_DiagConsumeReqData(pMsgContext, 1);                                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_DiagConsumeReqDataAsU16()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagConsumeReqDataAsU16(Dcm_MsgContextPtrType pMsgContext                                                  /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                                 ,P2VAR(uint16, AUTOMATIC, AUTOMATIC) pValue)
{
  *pValue = Dcm_DiagGetReqDataAsU16(pMsgContext);                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
  Dcm_DiagConsumeReqData(pMsgContext, 2);                                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_DiagConsumeReqDataAsU24()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagConsumeReqDataAsU24(Dcm_MsgContextPtrType pMsgContext                                                  /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                                 ,P2VAR(uint32, AUTOMATIC, AUTOMATIC) pValue)
{
  *pValue = Dcm_DiagGetReqDataAsU24(pMsgContext);                                                                                                    /* SBSW_DCM_PARAM_PTR_WRITE */
  Dcm_DiagConsumeReqData(pMsgContext, 3);                                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_DiagConsumeReqDataAsUN()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
*********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagConsumeReqDataAsUN(Dcm_MsgContextPtrType pMsgContext                                                   /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                                ,P2VAR(uint8, AUTOMATIC, AUTOMATIC) pTarget
                                                                ,Dcm_MsgLenType sizeOfTargetBuffer
                                                                ,Dcm_MsgLenType numBytes)
{
  Dcm_UtiMemCopyBuffer(Dcm_DiagGetReqData(pMsgContext)
                      ,pTarget
                      ,0u
                      ,(Dcm_CfgNetBufferSizeOptType)sizeOfTargetBuffer
                      ,(Dcm_CfgNetBufferSizeOptType)numBytes);                                                                                       /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagConsumeReqData(pMsgContext, numBytes);                                                                                                     /* SBSW_DCM_PARAM_PTR_FORWARD */
}

/**********************************************************************************************************************
 *  Dcm_DiagInitDataContext()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagInitDataContext(Dcm_DiagDataContextPtrType pDataContext                                                /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                             ,Dcm_MsgType    Buffer
                                                             ,Dcm_MsgLenType BufferSize)
{
  pDataContext->Buffer    = Buffer;                                                                                                                  /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
  pDataContext->Size      = BufferSize;                                                                                                              /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
  pDataContext->Usage     = 0;                                                                                                                       /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
  pDataContext->AvailLen  = BufferSize;                                                                                                              /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
}

/**********************************************************************************************************************
 *  Dcm_DiagCommitData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagCommitData(Dcm_DiagDataContextPtrType pDataContext                                                     /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                        ,Dcm_MsgLenType length)
{
# if (DCM_DEV_RUNTIME_CHECKS == STD_ON)                                                                                                              /* COV_DCM_REQUIRED_BY_SAFEBSW TX */
  /* pDataContext->AvailLen = pDataContext->Size - pDataContext->Usage and is a trusted value.
   * All DataContext values must be trusted values since modified only via the dedicated APIs, keeping them consistent. So the comparison is always valid.
   * Otherwise, nothing can help preventing buffer overflows
   * The only not trusted parameter is "length".
   */
  if(pDataContext->AvailLen < length)
  {
    Dcm_DebugCatchCriticalError(DCM_EXT_SID_DIAGCOMMITDATA);
  }
  else
# endif
  {
    pDataContext->Usage    += length;                                                                                                                /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
    pDataContext->AvailLen -= length;                                                                                                                /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
  }
}

/**********************************************************************************************************************
 *  Dcm_DiagRevertData()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagRevertData(Dcm_DiagDataContextPtrType  pDataContext                                                    /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                        ,Dcm_MsgLenType length)
{
# if (DCM_DEV_RUNTIME_CHECKS == STD_ON)                                                                                                              /* COV_DCM_REQUIRED_BY_SAFEBSW TX */
  /* All DataContext values must be trusted values since modified only via the dedicated APIs, keeping them consistent. So the comparison is always valid.
   * Otherwise, nothing can help preventing buffer overflows
   * The only not trusted parameter is "length".
   */
  if(pDataContext->Usage < length)
  {
    Dcm_DebugCatchCriticalError(DCM_EXT_SID_DIAGREVERTDATA);
  }
  else
# endif
  {
    pDataContext->Usage    -= length;                                                                                                                /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
    pDataContext->AvailLen += length;                                                                                                                /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
  }
}

/**********************************************************************************************************************
 *  Dcm_DiagGetDataContextBuffer()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(Dcm_MsgType, DCM_CODE) Dcm_DiagGetDataContextBuffer(Dcm_DiagDataContextPtrType pDataContext)                                   /* PRQA S 3219, 3673 */ /* MD_Dcm_3219, MD_Dcm_Design_3673 */
{
  return &pDataContext->Buffer[pDataContext->Usage];
}

/**********************************************************************************************************************
 *  Dcm_DiagProvideDataAsU8()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideDataAsU8(Dcm_DiagDataContextPtrType pDataContext                                                /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                             ,uint8 value)
{
# if (DCM_DEV_RUNTIME_CHECKS == STD_ON)                                                                                                              /* COV_DCM_REQUIRED_BY_SAFEBSW TX */
  if(pDataContext->Usage >= pDataContext->Size)
  {
    Dcm_DebugCatchCriticalError(DCM_EXT_SID_DIAGPROVIDEDATAASU8);
  }
  else
# endif
  {
    pDataContext->Buffer[pDataContext->Usage] = value;                                                                                               /* SBSW_DCM_POINTER_WRITE_DATA_CONTEXT */
    Dcm_DiagCommitData(pDataContext, 1u);                                                                                                            /* SBSW_DCM_PARAM_PTR_FORWARD */
  }
}

/**********************************************************************************************************************
 *  Dcm_DiagProvideDataAsU24()
 *********************************************************************************************************************/
/*!
 * Internal comment removed.
 *
 *
 *********************************************************************************************************************/
DCM_LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_DiagProvideDataAsU24(Dcm_DiagDataContextPtrType pDataContext                                               /* PRQA S 3219 */ /* MD_Dcm_3219 */
                                                              ,uint32 value)
{
  Dcm_DiagProvideDataAsU8(pDataContext, Dcm_UtiGetHiLoByte(value));                                                                                  /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagProvideDataAsU8(pDataContext, Dcm_UtiGetLoHiByte(value));                                                                                  /* SBSW_DCM_PARAM_PTR_FORWARD */
  Dcm_DiagProvideDataAsU8(pDataContext, Dcm_UtiGetLoLoByte(value));                                                                                  /* SBSW_DCM_PARAM_PTR_FORWARD */
}
# define DCM_STOP_SEC_CODE
/*lint -save -esym(961, 19.1)*/
# include "MemMap.h"                                                                                                                                 /* PRQA S 5087 */ /* MD_MSR_19.1 */
/*lint -restore*/
#endif /* !defined(DCM_COREINT_H) */
/* ********************************************************************************************************************
 * END OF FILE: Dcm_CoreInt.h
 * ******************************************************************************************************************** */
