/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/*!        \file  wdgm_verifier_types.h
 *        \brief  wdgm_verifier_types header file
 *
 *      \details  This is the header file of WdgMVerifier typed
 *
 *********************************************************************************************************************/


#ifndef _WDGM_VERIFIER_TYPES_H_
#define _WDGM_VERIFIER_TYPES_H_

#include <stdbool.h>
#include "WdgM_Cfg.h"
#define MAX_IDENTIFIER_LENGTH 128


typedef const char short_name [MAX_IDENTIFIER_LENGTH];

typedef struct
{
    int major;
    int minor;
    int patch;
} data_version_t;


typedef struct
{
    short_name source_se;
    short_name source_cp;
    short_name dest_se;
    short_name dest_cp;
} local_transition_t;


typedef struct
{
  short_name   source_se;
  short_name   source_cp;
  short_name   dest_se;
  short_name   dest_cp;
  double dl_min;
  double dl_max;
} dl_supervision_t;


typedef local_transition_t global_transition_t;

typedef struct
{
    int se_id;
    int cp_id;
    short_name se_name;
    short_name cp_name;
} cp_id_data_t;


typedef struct
{
    int                               id;
    short_name                        name;
    int                               cp_cnt;         /* number of checkpoints */
    cp_id_data_t *                    checkpoint_list;
    int                               OSApplication;
    void (*WdgM_LocalStateChangeCbk) (WdgM_LocalStatusType);
    Std_ReturnType (*WdgM_StatusReportToRte) (WdgM_LocalStatusType);
    bool                              autosar_3_1_compatibility;
    short_name app_task_ref;
} entity_struct_t;


typedef struct
{
    short_name name;
    int        OsApplicationCoreAssignment;
} os_application_t;


typedef struct
{
    short_name WdgMTriggerWatchdogRef;
    int  WdgMTriggerModeId;
    int  WdgMWatchdogMode;
    int  WdgMTriggerWindowStart;
    int  WdgMTriggerConditionValue;
} wdgm_trigger_t;


typedef struct
{
    int                    core_id;
    double                 ticks_per_second;
    double                 supervision_cycle;
    int                    initial_trigger_mode_id;
    wdgm_trigger_t const * triggers;
    int                    trigger_cnt;
    void (*WdgM_GlobalStateChangeCbk) (WdgM_GlobalStatusType);
    Std_ReturnType (*WdgM_StatusReportToRte) (WdgM_LocalStatusType);
} wdgm_mode_t;


typedef struct
{
  short_name se;
  short_name cp;
  int  WdgMExpectedAliveIndications;
  int  WdgMMaxMargin;
  int  WdgMMinMargin;
  int  WdgMSupervisionReferenceCycle;
} alive_supervision_t;


typedef struct
{
  short_name se;
  int  WdgMFailedSupervisionRefCycleTol;
  int  WdgMFailedDeadlineRefCycleTol;
  int  WdgMDeadlineReferenceCycle;
  int  WdgMFailedProgramFlowRefCycleTol;
  int  WdgMProgramFlowReferenceCycle;
  int  WdgMSupervisedEntityInitialMode;
} local_status_param_t;


typedef struct
{
    bool global_transitions;
    bool autosar_3_1_compatibility;
    bool multiple_trigger_modes;
} wdgm_computed_features_t;


typedef struct
{
    bool version_info_api;
    bool dev_error_detect;
    bool dem_report;
    bool defensive_behavior;
    bool immediate_reset;
    bool off_mode_enabled;
    bool use_os_suspend_interrupt;
    int  timebase_source;
    bool second_reset_path;
    bool tick_overrun_correction;
    bool entity_deactivation_enabled;
    int status_reporting_mechanism;
    bool use_rte;
    bool dem_supervision_report;
    bool firstcycle_alive_counter_reset;
    wdgm_computed_features_t const * computed_features;
} wdgm_features_t;


typedef struct
{
    local_transition_t const           * local_transitions;
    int                                  local_trans_cnt;
    global_transition_t const          * global_transitions;
    int                                  global_trans_cnt;
    dl_supervision_t const             * dl_supervision_list;
    int                                  dl_supervision_cnt;
    alive_supervision_t                * alive_supervision_list;
    int                                  alive_supervision_cnt;
    entity_struct_t const              * entity_list;
    int                                  entity_cnt;
    WdgM_EntityStatusLType const      ** entity_status_l_array;
    WdgM_EntityStatusGType const      ** entity_status_g_array;
    WdgM_SupervisedEntityIdType        * entity_id_array;
    int                                  WdgMTimebaseSource;
    local_status_param_t const         * lsp_list;
    int                                  lsp_cnt;
    wdgm_features_t const              * edf_features;
    wdgm_features_t const              * cfg_features;
    wdgm_mode_t const                  * mode_info;
    int                                  wdgm_mode_cnt;
    os_application_t const             * os_application_array;
    int                                  os_application_cnt;
    data_version_t const               * version_info;
} verifier_main_struct_t;

#endif
