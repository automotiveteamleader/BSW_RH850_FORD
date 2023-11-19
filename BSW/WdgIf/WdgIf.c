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
/*!        \file  WdgIf.c
 *        \brief  WdgIf source file
 *
 *      \details  This is the implementation of the module WdgIf
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

#define WDGIF_SOURCE

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "WdgIf.h"
#if (WDGIF_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"
#endif /* (WDGIF_DEV_ERROR_DETECT == STD_ON) */

/**********************************************************************************************************************
 *  VERSION CHECK
 *********************************************************************************************************************/

#define WDGIF_SW_MAJOR_VERSION_SOURCE             (5u)
#define WDGIF_SW_MINOR_VERSION_SOURCE             (2u)
#define WDGIF_SW_PATCH_VERSION_SOURCE             (0u)

/* Protection against incorrect include file version (WdgIf.h) */
#if ( (WDGIF_SW_MAJOR_VERSION != WDGIF_SW_MAJOR_VERSION_SOURCE) \
   || (WDGIF_SW_MINOR_VERSION != WDGIF_SW_MINOR_VERSION_SOURCE) \
   || (WDGIF_SW_PATCH_VERSION != WDGIF_SW_PATCH_VERSION_SOURCE) )
# error "Version mismatch! Incorrect version of WdgIf.h"
#endif

#if (WDGIF_USE_STATECOMBINER == STD_ON)

/**********************************************************************************************************************
 *  LOCAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Status for the Watchdog Interface - StateCombiner */
# define WDGIF_STATECOMBINER_OK                   (0u)      /*!< StateCombiner status OK */
# define WDGIF_STATECOMBINER_NOT_OK               (1u)      /*!< StateCombiner status NOT OK */
# define WDGIF_STATECOMBINER_RESET                (2u)      /*!< StateCombiner status issue a RESET */

# define SYNC_COUNT_INIT_VAL                      (0xFFFFu) /*!< Invalid counter value */

/**********************************************************************************************************************
 *  LOCAL FUNCTION MACROS
 *********************************************************************************************************************/

# if (WDGIF_STATECOMBINER_USE_OS_SPIN_LOCK == STD_ON)
#  define STATECOMBINER_GETSPINLOCK(_id) (void)GetSpinlock(_id) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define STATECOMBINER_RELEASESPINLOCK(_id) (void)ReleaseSpinlock(_id) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# else
#  define STATECOMBINER_GETSPINLOCK(_id) (void)Appl_GetSpinlock(_id) /* PRQA S 3453 */ /* MD_MSR_19.7 */
#  define STATECOMBINER_RELEASESPINLOCK(_id) (void)Appl_ReleaseSpinlock(_id) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# endif /* (WDGIF_STATECOMBINER_USE_OS_SPIN_LOCK == STD_ON) */

/**********************************************************************************************************************
 *  LOCAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

# if !defined (WDGIF_LOCAL) /* COV_WDGIF_COMPATIBILITY */
#  define WDGIF_LOCAL static
# endif

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

# define WDGIF_START_SEC_VAR_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087  */ /* MD_MSR_19.1  */

/*! Global variable to save the current state combiner status of the Watchdog */
WDGIF_LOCAL VAR(uint8, WDGIF_VAR) g_wdgif_sc_status = WDGIF_STATECOMBINER_OK;

/*! Global variable to save the inverted value of the current state combiner status of the Watchdog */
WDGIF_LOCAL VAR(uint8, WDGIF_VAR) g_wdgif_sc_status_INV = (uint8)~WDGIF_STATECOMBINER_OK;

# define WDGIF_STOP_SEC_VAR_INIT_8BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define WDGIF_START_SEC_VAR_INIT_16BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/*! Global variable to save the cycle counter of the master SC device */
WDGIF_LOCAL VAR(uint16, WDGIF_VAR) g_wdgif_sc_cycle_counter[WDGIF_MAX_SUPPORTED_CORES - 1] = /* PRQA S 3218 */ /* MD_WdgIf_3218 */
{
  0u,
  0u,
  0u
};

/*! Global variable to save the inverted value of the cycle counter of the master SC device */
WDGIF_LOCAL VAR(uint16, WDGIF_VAR) g_wdgif_sc_cycle_counter_INV[WDGIF_MAX_SUPPORTED_CORES - 1] = /* PRQA S 3218 */ /* MD_WdgIf_3218 */
{
  (uint16)~0u,
  (uint16)~0u,
  (uint16)~0u
};

/*! Global variable to save the synchronization cycle count */
WDGIF_LOCAL VAR(uint16, WDGIF_VAR) g_wdgif_sc_sync_count = SYNC_COUNT_INIT_VAL; /* PRQA S 3218 */ /* MD_WdgIf_3218 */

/*! Global variable to save the inverted value of the synchronization cycle count */
WDGIF_LOCAL VAR(uint16, WDGIF_VAR) g_wdgif_sc_sync_count_INV = (uint16)~SYNC_COUNT_INIT_VAL; /* PRQA S 3218 */ /* MD_WdgIf_3218 */

# define WDGIF_STOP_SEC_VAR_INIT_16BIT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

# define WDGIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *  wdgif_statecombiner_check_slave_timing()
 *********************************************************************************************************************/
/*! \brief        Checks the slave timing in case of enabled state combiner
 *  \details      wdgif_check_slave_timing monitors the timing of the configured slave State Combiner instance(s)
 *                execution and reports its state to the upper layer.
 *  \param[in]    StateCombinerConfigPtr     Pointer to the WdgIf configuration
 *  \return       WDGIF_STATECOMBINER_OK      State Combiner function executed successfully
 *  \return       WDGIF_STATECOMBINER_NOT_OK  Timing error for slave(s) detected
 *  \return       WDGIF_STATECOMBINER_RESET   Unrecoverable error detected, reset issued
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \config       WDGIF_USE_STATECOMBINER is STD_ON
 *  \trace        DSGN-WdgIf22756, DSGN-WdgIf22804, DSGN-WdgIf22805
 */
WDGIF_LOCAL FUNC(uint8, WDGIF_CODE) wdgif_statecombiner_check_slave_timing(
  P2CONST(WdgIf_StateCombinerConfigType, AUTOMATIC, WDGIF_APPL_CONST) StateCombinerConfigPtr
  );

/**********************************************************************************************************************
 *  wdgif_statecombiner_setmode()
 *********************************************************************************************************************/
/*! \brief        Sets the watchdog mode in case of enabled state combiner
 *  \details      wdgif_statecombiner_setmode switches the watchdog mode of the corresponding State Combiner instance
 *                according to the parameter DeviceIndex.
 *  \param[in]    WdgInstance   Index of the State Combiner instance for which the function is called
 *  \param[in]    Mode          Watchdog mode which is being requested
 *  \return       E_OK      State Combiner function invoked and executed successfully
 *  \return       E_NOT_OK  Error detected or driver function returned an error
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \config       WDGIF_USE_STATECOMBINER is STD_ON
 *  \trace        DSGN-WdgIf22749
 */
WDGIF_LOCAL FUNC(Std_ReturnType, WDGIF_CODE) wdgif_statecombiner_setmode(
  VAR(uint8, AUTOMATIC) WdgInstance,
  VAR(WdgIf_ModeType, AUTOMATIC) Mode
  );

/**********************************************************************************************************************
 *  wdgif_statecombiner_settriggerwindow()
 *********************************************************************************************************************/
/*! \brief        Sets the trigger window in case of enabled state combiner
 *  \details      wdgif_statecombiner_settriggerwindow sets a new timeout and new window start and services the
 *                corresponding State Combiner instance according to the parameter DeviceIndex.\n
 *                It sets a new timeout and new window start for the watchdog unit.
 *  \param[in]    WdgInstance
 *  \param[in]    Timeout
 *  \return       E_OK      State Combiner function invoked and executed successfully
 *  \return       E_NOT_OK  Error detected or driver function returned an error
 *  \pre          -
 *  \context      TASK
 *  \reentrant    FALSE
 *  \synchronous  TRUE
 *  \config       WDGIF_USE_STATECOMBINER is STD_ON
 *  \trace        DSGN-WdgIf22756, DSGN-WdgIf22804, DSGN-WdgIf22805
 */
WDGIF_LOCAL FUNC(Std_ReturnType, WDGIF_CODE) wdgif_statecombiner_settriggerwindow(
  VAR(uint8, AUTOMATIC) WdgInstance,
  VAR(uint16, AUTOMATIC) Timeout
  );

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  wdgif_statecombiner_check_slave_timing()
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
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
WDGIF_LOCAL FUNC(uint8, WDGIF_CODE) wdgif_statecombiner_check_slave_timing(
  P2CONST(WdgIf_StateCombinerConfigType, AUTOMATIC, WDGIF_APPL_CONST) StateCombinerConfigPtr
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR(uint8, AUTOMATIC) status_sc;
  VAR(uint8, AUTOMATIC) ret_sc;
  VAR(uint8, AUTOMATIC) i;
  VAR(uint32, AUTOMATIC) slave_counter_value;
  VAR(uint32, AUTOMATIC) min_increments;
  VAR(uint32, AUTOMATIC) max_increments;
  VAR(WdgIf_StateCombinerSpinlockIdType, AUTOMATIC) spinlock_id;
  P2VAR(WdgIf_StateCombinerSharedMemory, AUTOMATIC, WDGIF_APPL_DATA) cfg_sdata;
  P2VAR(WdgIf_StateCombinerSharedMemory, AUTOMATIC, WDGIF_APPL_DATA) slave_sdata;
  P2CONST(WdgIf_StateCombinerSlaveTriggerPatternType, AUTOMATIC, WDGIF_APPL_CONST) slave_trigger_pattern;

  /* ----- Implementation ----------------------------------------------- */
  spinlock_id = StateCombinerConfigPtr->WdgIfStateCombinerSpinlockId;
  cfg_sdata = StateCombinerConfigPtr->WdgIfStateCombinerSData;

  /* #10 Check if global variables are valid (bit flipping) */
  if ( ((uint8)~g_wdgif_sc_status != g_wdgif_sc_status_INV)
    || ((uint16)~g_wdgif_sc_sync_count != g_wdgif_sc_sync_count_INV)
     )
  {
    /* #11 Aborted and return WDGIF_STATECOMBINER_RESET */
    ret_sc = WDGIF_STATECOMBINER_RESET;
  }
  else
  {
    /* #20 Check if global variable for storing the synchronization start-up cycles is set to its initial value */
    if (g_wdgif_sc_sync_count == SYNC_COUNT_INIT_VAL)
    {
      /* #21 Global variable for storing the synchronization start-up cycles is set to value
       *     WdgIfStateCombinerStartUpSyncCycles specified in the configuration structure */
      g_wdgif_sc_sync_count = StateCombinerConfigPtr->WdgIfStateCombinerStartUpSyncCycles + 1u;
      g_wdgif_sc_sync_count_INV = (uint16)~(g_wdgif_sc_sync_count);
    }

    /* #30 Check if the global variable for storing the synchronization start-up cycles is greater than zero */
    if (g_wdgif_sc_sync_count > 0u)
    {
      /* #31 Decrement global variable for storing the synchronization start-up cycles */
      g_wdgif_sc_sync_count--;
      g_wdgif_sc_sync_count_INV = (uint16)~(g_wdgif_sc_sync_count);
    }
    
    /* #40 Repeat the following steps for all slave devices */
    status_sc = WDGIF_STATECOMBINER_OK;
    ret_sc = g_wdgif_sc_status;
    i = 0u;
    
    do
    {
      slave_sdata = (&cfg_sdata[i]);
      slave_trigger_pattern = StateCombinerConfigPtr->WdgIfStateCombinerSlaveTriggerPattern[i];

      /* #50 Get the spin lock */
      STATECOMBINER_GETSPINLOCK (spinlock_id);

      slave_counter_value = slave_sdata->SlaveCounterValue;
      
      /* #70 Check if global shared variable values are corrupted */
      if ( ((uint16)~g_wdgif_sc_cycle_counter[i] != g_wdgif_sc_cycle_counter_INV[i]) 
        || ((uint32)~slave_counter_value != slave_sdata->SlaveCounterValue_INV)
         )
      {
        /* #71 Release the spinlock */
        STATECOMBINER_RELEASESPINLOCK (spinlock_id);

        /* #72 Aborted and return WDGIF_STATECOMBINER_RESET */
        status_sc = WDGIF_STATECOMBINER_RESET;
      }
      /* #80 Check if global synchronization start-up cycles counter is greater than zero */
      else if (g_wdgif_sc_sync_count > 0u)
      {
        /* #81 Reset value of the slave instance trigger counter to zero */
        slave_sdata->SlaveCounterValue = 0u; /* SBSW_WDGIF_002 */
        slave_sdata->SlaveCounterValue_INV = (uint32)~0u; /* SBSW_WDGIF_002 */

        /* #82 Release the spinlock */
        STATECOMBINER_RELEASESPINLOCK (spinlock_id);
      }
      /* #100 Do the following in all other cases */
      else
      {
        /* #110 Release the spinlock */
        STATECOMBINER_RELEASESPINLOCK (spinlock_id);

        /* #120 Increment the number of elapsed master cycles since the last timing check of the slave instance */
        g_wdgif_sc_cycle_counter[i]++; /* SBSW_WDGIF_003 */
        g_wdgif_sc_cycle_counter_INV[i] = (uint16)~g_wdgif_sc_cycle_counter[i]; /* SBSW_WDGIF_003 */

        /* #130 Check if counter is equal to the predefined State Combiner Reference Cycle of the particular slave */
        if (g_wdgif_sc_cycle_counter[i] == slave_trigger_pattern->WdgIfStateCombinerReferenceCycle)
        {
          /* #140 Read the expected minimum / maximum State Combiner Slave Increments */
          min_increments = slave_trigger_pattern->WdgIfStateCombinerSlaveIncrementsMin;
          max_increments = slave_trigger_pattern->WdgIfStateCombinerSlaveIncrementsMax;

          /* #150 Check if the trigger counter of slave State Combiner instance is inside of the min / max range of the
           *      allowed trigger number */
          if ( (slave_counter_value < min_increments)
            || (slave_counter_value > max_increments)
             )
          {
            /* #151 Set the State Combiner status to WDGIF_STATECOMBINER_NOT_OK if outside of the min / max range */
            status_sc = WDGIF_STATECOMBINER_NOT_OK;
          }
          else /* #160 Do the following if the trigger counter of slave State Combiner instance is inside of the
                *      min / max range */
          {
            /* #161 Get the spin lock */
            STATECOMBINER_GETSPINLOCK (spinlock_id);

            /* #162 Reset slave trigger counter value to zero */
            slave_sdata->SlaveCounterValue = 0u; /* SBSW_WDGIF_002 */
            slave_sdata->SlaveCounterValue_INV = (uint32)~0u; /* SBSW_WDGIF_002 */

            /* #163 Release the spinlock */
            STATECOMBINER_RELEASESPINLOCK (spinlock_id);

            /* #164 Reset counters for particular slave instance */
            g_wdgif_sc_cycle_counter[i] = 0u; /* SBSW_WDGIF_003 */
            g_wdgif_sc_cycle_counter_INV[i] = (uint16)~0u; /* SBSW_WDGIF_003 */
          }
        }
      }

      /* check status (with priority), save it if higher than current */
      ret_sc = ((status_sc > ret_sc) ? status_sc : ret_sc);
      /* check next slave instance */
      i++;
    } while ( (i < StateCombinerConfigPtr->WdgIfStateCombinerNumberOfSlaves) && (ret_sc != WDGIF_STATECOMBINER_RESET) );
  }

  /* #170 Return currently determined State Combiner status value */
  return ret_sc;
} /* PRQA S 6080 */ /* MD_MSR_STMIF  */

/**********************************************************************************************************************
 *  wdgif_statecombiner_setmode()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 */
WDGIF_LOCAL FUNC(Std_ReturnType, WDGIF_CODE) wdgif_statecombiner_setmode(
  VAR(uint8, AUTOMATIC) WdgInstance,
  VAR(WdgIf_ModeType, AUTOMATIC) Mode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR(Std_ReturnType, AUTOMATIC) ret;
  P2CONST(WdgIf_StateCombinerConfigType, AUTOMATIC, WDGIF_APPL_CONST) state_combiner_config_ptr;

  /* ----- Implementation ----------------------------------------------- */
  ret = E_OK;
  state_combiner_config_ptr = WdgIf_Interface.WdgIfStateCombinerConfig;
  /* #10 Check if WdgInstance is equal to zero (master State Combiner instance) */
  if (WdgInstance == 0u)
  {
    /* #11 Call the driver function for performing a mode change */
    ret = state_combiner_config_ptr->WdgIfStateCombinerFunctions->Wdg_SetMode_AR (Mode); /* SBSW_WDGIF_005 */
    /* #12 Return the return value provided by the driver */
  }
  /* #20 Check if WdgInstance is not equal to zero (slave State Combiner instance) */
  /* #21 Return E_OK */
  return ret;
}

/**********************************************************************************************************************
 *  wdgif_statecombiner_settriggerwindow()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
WDGIF_LOCAL FUNC(Std_ReturnType, WDGIF_CODE) wdgif_statecombiner_settriggerwindow(
  VAR(uint8, AUTOMATIC) WdgInstance,
  VAR(uint16, AUTOMATIC) Timeout
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  P2VAR(WdgIf_StateCombinerSharedMemory, AUTOMATIC, WDGIF_APPL_DATA) slave_sdata;
  P2CONST(WdgIf_StateCombinerConfigType, AUTOMATIC, WDGIF_APPL_CONST) state_combiner_config_ptr;
  VAR(Std_ReturnType, AUTOMATIC) ret;
  VAR(uint8, AUTOMATIC) ret_sc;
  VAR(WdgIf_StateCombinerSpinlockIdType, AUTOMATIC) spinlock_id;

  /* ----- Implementation ----------------------------------------------- */
  state_combiner_config_ptr = WdgIf_Interface.WdgIfStateCombinerConfig;
  spinlock_id = state_combiner_config_ptr->WdgIfStateCombinerSpinlockId;
  /* #10 Check if WdgInstance is not equal to zero (slave State Combiner instance) */
  if (WdgInstance != 0u)   /* not SC master instance */
  {
    /* #20 Read the address of the appropriate slave State Combiner shared data */
    slave_sdata = &(state_combiner_config_ptr->WdgIfStateCombinerSData[WdgInstance - 1u]);
    /* #30 Get the spinlock */
    STATECOMBINER_GETSPINLOCK (spinlock_id);

    /* #40 Check if Timeout is equal to zero (immediate reset), or shared memory corruption occurred */
    if ( (Timeout == 0u) || ((uint32)~slave_sdata->SlaveCounterValue != slave_sdata->SlaveCounterValue_INV)
       )
    {
      /* #41 Corrupt slave timeout value (request for the master to issue a reset) */
      slave_sdata->SlaveCounterValue = 0u; /* SBSW_WDGIF_002 */
      slave_sdata->SlaveCounterValue_INV = 0u; /* SBSW_WDGIF_002 */
    }
    /* #50 Check if Timeout is not equal to zero and no shared memory corruption occurred */
    else
    {
      /* #51 Increment current slaves trigger counter value */
      slave_sdata->SlaveCounterValue++; /* SBSW_WDGIF_002 */
      slave_sdata->SlaveCounterValue_INV = (uint32)~slave_sdata->SlaveCounterValue; /* SBSW_WDGIF_002 */
    }
    ret = E_OK;

    /* #60 Release the spinlock */
    STATECOMBINER_RELEASESPINLOCK (spinlock_id);
  }
  /* #70 Check if WdgInstance is equal to zero (master State Combiner instance) */
  else /* (WdgInstance == 0u) */
  {
    /* #80 Check the timing of all slave devices */
    ret_sc = wdgif_statecombiner_check_slave_timing (state_combiner_config_ptr); /* SBSW_WDGIF_001 */

    /* #90 Check if timeout is equal to zero (immediate reset) or State Combiner status is WDGIF_STATECOMBINER_RESET */
    if ( (Timeout == 0u)
      || (ret_sc == WDGIF_STATECOMBINER_RESET)
       )
    {
      /* #91 Call the "master" wdg function with zero values - "immediate reset" */
      ret = E_OK;
      state_combiner_config_ptr->WdgIfStateCombinerFunctions->Wdg_SetTriggerCondition_AR (0u); /* SBSW_WDGIF_005 */
      /* #92 Set the State Combiner status to WDGIF_STATECOMBINER_NOT_OK */
      ret_sc = WDGIF_STATECOMBINER_NOT_OK;
    }
    /* #100 Check if State Combiner status is WDGIF_STATECOMBINER_OK */
    else if (ret_sc == WDGIF_STATECOMBINER_OK)
    {
      /* #101 Call the "master" wdg function - service wdg */
      ret = E_OK;
      state_combiner_config_ptr->WdgIfStateCombinerFunctions->Wdg_SetTriggerCondition_AR (Timeout); /* SBSW_WDGIF_005 */
    }
    /* #110 Check if State Combiner status is WDGIF_STATECOMBINER_NOT_OK */
    else
    {
      /* #111 Skip wdg servicing and return E_OK */
      ret = E_OK;
    }

    /* #120 Update global State Combiner status */
    g_wdgif_sc_status = ret_sc;
    g_wdgif_sc_status_INV = (uint8)~ret_sc; /* PRQA S 0291 */ /* MD_WdgIf_0291 */
  }

  /* #130 Return the value of the wdg servicing */
  return ret;
}

#else /* if (WDGIF_USE_STATECOMBINER == STD_OFF) */

# define WDGIF_START_SEC_CODE
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* (WDGIF_USE_STATECOMBINER == STD_ON) */

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  WdgIf_SetMode()
 *********************************************************************************************************************/
/*!
 *
 * Internal comment removed.
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, WDGIF_CODE) WdgIf_SetMode(
  VAR(uint8, AUTOMATIC) DeviceIndex,
  VAR(WdgIf_ModeType, AUTOMATIC) WdgMode
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR(Std_ReturnType, AUTOMATIC) ret;
#if (WDGIF_USE_STATECOMBINER == STD_ON)
  P2CONST(WdgIf_InterfaceFunctionsType, AUTOMATIC, WDGIF_APPL_CONST) wdg_function_address;
#endif /* (WDGIF_USE_STATECOMBINER == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the configuration is invalid (whether the array with function pointers per driver is a NULL_PTR) or
   *     if the parameter DeviceIndex is not plausible or
   *     if the function pointer for the selected driver is a NULL_PTR */
  if ( (WdgIf_Interface.WdgFunctionsPerDevice == NULL_PTR)
    || (DeviceIndex >= WdgIf_Interface.NumOfWdgs)
#if (WDGIF_USE_STATECOMBINER == STD_OFF)
    || (WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgFunctions == NULL_PTR)
#else /* if (WDGIF_USE_STATECOMBINER == STD_ON) */
    || (WdgIf_Interface.WdgIfStateCombinerConfig == NULL_PTR)
    || (WdgIf_Interface.WdgIfStateCombinerConfig->WdgIfStateCombinerSlaveTriggerPattern == NULL_PTR)
#endif /* (WDGIF_USE_STATECOMBINER == STD_OFF) */
     )
  {
    /* #11 Check if WDGIF_DEV_ERROR_DETECT is set to STD_ON */
#if (WDGIF_DEV_ERROR_DETECT == STD_ON)
    /* #12 Raise the development error with error code WDGIF_E_PARAM_DEVICE */
    Det_ReportError (WDGIF_MODULE_ID, WDGIF_INSTANCE_ID, WDGIF_SID_SET_MODE, WDGIF_E_PARAM_DEVICE);
#endif /* WDGIF_DEV_ERROR_DETECT == STD_ON */
    /* #13 Abort and return E_NOT_OK */
    ret = E_NOT_OK;
  }
  /* #20 Check if the configuration is valid */
  else
  {
    /* #21 Check if WDGIF_USE_STATECOMBINER is set to STD_ON */
#if (WDGIF_USE_STATECOMBINER == STD_ON)
    wdg_function_address = WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgFunctions;

    /* #22 Check if the function pointer for the selected driver is invalid (NULL_PTR) - WdgIf instance has its own
     *     underlying Wdg */
    if (wdg_function_address == NULL_PTR)
    {
      /* #23 Perform mode change for the addressed State Combiner instance with input parameter values */
      ret = wdgif_statecombiner_setmode (WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgInstance, WdgMode);
    }
    /* #24 Check if the function pointer for the selected driver is a valid function address */
    else
    {
#endif /* (WDGIF_USE_STATECOMBINER == STD_ON) */
      /* #25 Call the corresponding platform-specific implementation */
      ret = WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgFunctions->Wdg_SetMode_AR (WdgMode); /* SBSW_WDGIF_005 */
#if (WDGIF_USE_STATECOMBINER == STD_ON)
    }
#endif /* (WDGIF_USE_STATECOMBINER == STD_ON) */
  }

  /* #26 Return the value of the wdg servicing */
  return ret;
}

/**********************************************************************************************************************
 *  WdgIf_SetTriggerCondition()
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
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, WDGIF_CODE) WdgIf_SetTriggerCondition(
  VAR(uint8, AUTOMATIC) DeviceIndex,
  VAR(uint16, AUTOMATIC) Timeout
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR(Std_ReturnType, AUTOMATIC) ret;
#if (WDGIF_USE_STATECOMBINER == STD_ON)
  P2CONST(WdgIf_InterfaceFunctionsType, AUTOMATIC, WDGIF_APPL_CONST) wdg_function_address;
#endif /* (WDGIF_USE_STATECOMBINER == STD_ON) */
    
  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the configuration is invalid (whether the array with function pointers per driver is a NULL_PTR) or
   *     if the parameter DeviceIndex is not plausible or
   *     if the function pointer for the selected driver is a NULL_PTR */
  if ( (WdgIf_Interface.WdgFunctionsPerDevice == NULL_PTR)
    || (DeviceIndex >= WdgIf_Interface.NumOfWdgs)
#if (WDGIF_USE_STATECOMBINER == STD_OFF)
    || (WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgFunctions == NULL_PTR)
#else /* if (WDGIF_USE_STATECOMBINER == STD_ON) */
    || (WdgIf_Interface.WdgIfStateCombinerConfig == NULL_PTR)
    || (WdgIf_Interface.WdgIfStateCombinerConfig->WdgIfStateCombinerSlaveTriggerPattern == NULL_PTR)
#endif /* (WDGIF_USE_STATECOMBINER == STD_OFF) */
     )
  {
    /* #11 Check if WDGIF_DEV_ERROR_DETECT is set to STD_ON */
#if (WDGIF_DEV_ERROR_DETECT == STD_ON)
    /* #12 Raise the development error with error code WDGIF_E_PARAM_DEVICE */
    Det_ReportError (WDGIF_MODULE_ID, WDGIF_INSTANCE_ID, WDGIF_SID_SET_TRIGGER_CONDITION, WDGIF_E_PARAM_DEVICE);
#endif /* WDGIF_DEV_ERROR_DETECT == STD_ON */
    /* #13 Abort and return E_NOT_OK */
    ret = E_NOT_OK;
  }
  /* #20 Check if the configuration is valid */
  else
  {
    /* #21 Check if WDGIF_USE_STATECOMBINER is set to STD_ON */
#if (WDGIF_USE_STATECOMBINER == STD_ON)
    wdg_function_address = WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgFunctions;

    /* #22 Check if the function pointer for the selected driver is invalid (NULL_PTR) - WdgIf instance has its own
     *     underlying Wdg */
    if (wdg_function_address == NULL_PTR)
    {
      /* #23 Call state combiner function */
      ret = wdgif_statecombiner_settriggerwindow( WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgInstance,
                                                  Timeout
                                                );
    }
    /* #24 Check if the function pointer for the selected driver is a valid function address */
    else
    {
#endif /* (WDGIF_USE_STATECOMBINER == STD_ON) */
      /* #25 Call the corresponding platform-specific implementation with input parameter values */
      ret = E_OK;
      WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgFunctions->Wdg_SetTriggerCondition_AR (Timeout); /* SBSW_WDGIF_005 */
#if (WDGIF_USE_STATECOMBINER == STD_ON)
    }
#endif /* (WDGIF_USE_STATECOMBINER == STD_ON) */
  }

  /* #30 Return the value of the wdg servicing */
  return ret;
}

/**********************************************************************************************************************
 *  WdgIf_SetTriggerWindow()
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
 *
 *
 *
 *
 *
 *
 *
 *
 */
FUNC(Std_ReturnType, WDGIF_CODE) WdgIf_SetTriggerWindow(
  VAR(uint8, AUTOMATIC) DeviceIndex,
  VAR(uint16, AUTOMATIC) WindowStart,
  VAR(uint16, AUTOMATIC) Timeout
  )
{
  /* ----- Local Variables ---------------------------------------------- */
  VAR(Std_ReturnType, AUTOMATIC) ret;
#if (WDGIF_USE_STATECOMBINER == STD_ON)
  P2CONST(WdgIf_InterfaceFunctionsType, AUTOMATIC, WDGIF_APPL_CONST) wdg_function_address;
#endif /* (WDGIF_USE_STATECOMBINER == STD_ON) */

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Check if the configuration is invalid (whether the array with function pointers per driver is a NULL_PTR) or
   *     if the parameter DeviceIndex is not plausible or
   *     if the function pointer for the selected driver is a NULL_PTR */
  if ( (WdgIf_Interface.WdgFunctionsPerDevice == NULL_PTR)
    || (DeviceIndex >= WdgIf_Interface.NumOfWdgs)
#if (WDGIF_USE_STATECOMBINER == STD_OFF)
    || (WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgFunctions == NULL_PTR)
#else /* if (WDGIF_USE_STATECOMBINER == STD_ON) */
    || (WdgIf_Interface.WdgIfStateCombinerConfig == NULL_PTR)
    || (WdgIf_Interface.WdgIfStateCombinerConfig->WdgIfStateCombinerSlaveTriggerPattern == NULL_PTR)
#endif /* (WDGIF_USE_STATECOMBINER == STD_OFF) */
     )
  {
    /* #11 Check if WDGIF_DEV_ERROR_DETECT is set to STD_ON */
#if (WDGIF_DEV_ERROR_DETECT == STD_ON)
    /* #12 Raise the development error with error code WDGIF_E_PARAM_DEVICE */
    Det_ReportError (WDGIF_MODULE_ID, WDGIF_INSTANCE_ID, WDGIF_SID_SET_TRIGGER_WINDOW, WDGIF_E_PARAM_DEVICE);
#endif /* WDGIF_DEV_ERROR_DETECT == STD_ON */
    /* #13 Abort and return E_NOT_OK */
    ret = E_NOT_OK;
  }
  /* #20 Check if the configuration is valid */
  else
  {
    /* #21 Check if WDGIF_USE_STATECOMBINER is set to STD_ON */
#if (WDGIF_USE_STATECOMBINER == STD_ON)
    wdg_function_address = WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgFunctions;

    /* #22 Check if the function pointer for the selected driver is invalid (NULL_PTR) - WdgIf instance has its own
     *     underlying Wdg */
    if (wdg_function_address == NULL_PTR)
    {
      /* #23 Call state combiner function */
      ret = wdgif_statecombiner_settriggerwindow( WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgInstance,
                                                  Timeout
                                                );
    }
    /* #24 Check if the function pointer for the selected driver is a valid function address */
    else
    {
#endif /* (WDGIF_USE_STATECOMBINER == STD_ON) */
      /* #25 Call the corresponding platform-specific implementation with input parameter values */
      /* Note: in this case the parameter WindowStart is ignored. */
      ret = E_OK;
      WindowStart = WindowStart; /* PRQA S 3199 */ /* MD_WdgIf_3199 */
      WdgIf_Interface.WdgFunctionsPerDevice[DeviceIndex].WdgFunctions->Wdg_SetTriggerCondition_AR (Timeout); /* SBSW_WDGIF_005 */
#if (WDGIF_USE_STATECOMBINER == STD_ON)
    }
#endif /* (WDGIF_USE_STATECOMBINER == STD_ON) */
  }

  /* #30 Return the value of the wdg servicing */
  return ret;
}

#if (WDGIF_VERSION_INFO_API == STD_ON)
/**********************************************************************************************************************
 *  WdgIf_GetVersionInfo()
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
FUNC(void, WDGIF_CODE) WdgIf_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, WDGIF_APPL_DATA) versioninfo)
{
  /* ----- Development Error Checks ------------------------------------- */
  /* #10 Check if out parameter is a NULL_PTR */
  if (versioninfo == NULL_PTR)
  {
    /* #11 Check if WDGIF_DEV_ERROR_DETECT is set to STD_ON */
#if (WDGIF_DEV_ERROR_DETECT == STD_ON)
    /* #12 Raise the development error with error code WDGIF_E_INV_POINTER */
    Det_ReportError (WDGIF_MODULE_ID, WDGIF_INSTANCE_ID, WDGIF_SID_GET_VERSION_INFO, WDGIF_E_INV_POINTER);
#endif /* WDGIF_DEV_ERROR_DETECT == STD_ON */
  }
  /* #20 Check if out parameter is a valid pointer (not equal to NULL_PTR) */
  else
  {
    /* ----- Implementation ----------------------------------------------- */
    /* #21 Store the version info in the memory cell referenced by the out parameter */
    versioninfo->vendorID = (WDGIF_VENDOR_ID); /* SBSW_WDGIF_004 */
    versioninfo->moduleID = (WDGIF_MODULE_ID); /* SBSW_WDGIF_004 */
    versioninfo->sw_major_version = (WDGIF_SW_MAJOR_VERSION); /* SBSW_WDGIF_004 */
    versioninfo->sw_minor_version = (WDGIF_SW_MINOR_VERSION); /* SBSW_WDGIF_004 */
    versioninfo->sw_patch_version = (WDGIF_SW_PATCH_VERSION); /* SBSW_WDGIF_004 */
  }
  return;
}
#endif /* WDGIF_VERSION_INFO_API == STD_ON */

#define WDGIF_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Justification for module-specific MISRA deviations:

  MD_WdgIf_0291: rule 21.1
    Reason:     This deviation is inherited by the migrated WdgIf and cannot be changed currently.
    Risk:       None
    Prevention: None

  MD_WdgIf_3218: rule 8.7
    Reason:     This deviation is inherited by the migrated WdgIf and cannot be changed currently.
    Risk:       None
    Prevention: None

  MD_WdgIf_3199: rule
    Reason:     This statement is placed to avoid a compiler warning and explicitly mark that 'WindowStart' is not used
                on purpose.
    Risk:       None - see reason
    Prevention: None, because no risk
    
*/

/* SBSW_JUSTIFICATION_BEGIN

\ID SBSW_WDGIF_001
 \DESCRIPTION     Function call with config pointer as parameter
 \COUNTERMEASURE  \S The user has to validate the generated configuration as described in the Safety Manual.

\ID SBSW_WDGIF_002
 \DESCRIPTION     Pointer write access to target config pointer
 \COUNTERMEASURE  \S The user has to validate the generated configuration as described in the Safety Manual.

\ID SBSW_WDGIF_003
 \DESCRIPTION     Array write access
 \COUNTERMEASURE  \R The arrays g_wdgif_sc_cycle_counter, g_wdgif_sc_cycle_counter_INV, g_wdgif_sc_sum_ws,
                     g_wdgif_sc_sum_ws_INV, g_wdgif_sc_sum_to, g_wdgif_sc_sum_to_INV are global arrays with the same
                     length (WDGIF_MAX_SUPPORTED_CORES-1). This define is statically set to 4. A runtime check confirms
                     that only valid array elements of these arrays can be retrieved. The implementation accesses the
                     arrays with an index from 0 to a maximum WdgIfStateCombinerNumberOfSlaves - which is a generated
                     element within the configuration structure. The generator itself does not allow to configure more
                     than three slaves.
                  \S The Safety Manual also tells the user to check that the generated number
                     WdgIfStateCombinerNumberOfSlaves is correct.

\ID SBSW_WDGIF_004
 \DESCRIPTION     Pointer write access to target pointer given as parameter
 \COUNTERMEASURE  \N The given pointer must be valid. The user has to ensure that a valid pointer is given.
                     Additionally, the pointer versioninfo is checked if it is valid.

\ID SBSW_WDGIF_005
 \DESCRIPTION     Function Pointer Call to the underlying watchdog hardware
 \COUNTERMEASURE  \S The generated, configured function pointer must be valid. The user has to ensure that a valid
                     function pointer is generated.
                     The Safety Manual tells the user how to check that function pointers.

SBSW_JUSTIFICATION_END */

/*
\CM CM_WDGIF_001 The given config pointer must be valid. The user has to ensure that a valid pointer is given. The
                 pointer cannot be an arbitrary one, but a generated pointer. The user has to check the generated
                 configuration structure as described in the Safety Manual.
*/

/* COV_JUSTIFICATION_BEGIN

\ID COV_WDGIF_COMPATIBILITY
 \ACCEPT TX
 \REASON [COV_MSR_COMPATIBILITY]

\ID COV_WDGIF_NULL_PTR_DEFINE
 \ACCEPT XF
 \REASON If the NULL_PTR is not defined, the pointer is defined by the WdgIf itself. In all configs the NULL_PTR is
         already defined via Compiler.h.

COV_JUSTIFICATION_END */

/**********************************************************************************************************************
 *  END OF FILE: WdgIf.c
 *********************************************************************************************************************/
