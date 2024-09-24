/*
 * induction_heather_model.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "induction_heather_model".
 *
 * Model version              : 37
 * Simulink Coder version : 9.9 (R2023a) 19-Nov-2022
 * C source code generated on : Sat Jun 17 16:27:33 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "induction_heather_model.h"
#include "rtwtypes.h"
#include "induction_heather_model_private.h"
#include <math.h>
#include "induction_heather_model_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Named constants for Chart: '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
#define induction_he_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define induction_heathe_IN_longpressed ((uint8_T)1U)
#define induction_heather_mo_IN_pressed ((uint8_T)2U)
#define induction_heather_mode_RELEASED (true)
#define induction_heather_model_IN_wait ((uint8_T)3U)
#define induction_heather_model_PRESSED (false)

/* Named constants for Chart: '<S1>/INDUCTION_STOVE.INPUTS.PRESENCE' */
#define induction__IN_NO_ACTIVE_CHILD_j ((uint8_T)0U)
#define induction_heather__IN_pressed_o ((uint8_T)1U)
#define induction_heather_mod_IN_wait_m ((uint8_T)2U)

/* Named constants for Chart: '<Root>/Chart' */
#define induction_he_IN_LONGPRESSED_OFF ((uint8_T)1U)
#define induction_hea_IN_LONGPRESSED_ON ((uint8_T)2U)
#define induction_heather_m_IN_WAIT_OFF ((uint8_T)5U)
#define induction_heather_mo_IN_ANOMALY ((uint8_T)1U)
#define induction_heather_mo_IN_COOKING ((uint8_T)1U)
#define induction_heather_mo_IN_WAITING ((uint8_T)4U)
#define induction_heather_mo_IN_WAIT_ON ((uint8_T)6U)
#define induction_heather_mod_IN_OFF_gt ((uint8_T)1U)
#define induction_heather_mode_IN_OFF_g ((uint8_T)3U)
#define induction_heather_mode_IN_ON_ie ((uint8_T)2U)
#define induction_heather_mode_IN_POWER ((uint8_T)2U)
#define induction_heather_mode_IN_READY ((uint8_T)3U)
#define induction_heather_model_IN_OFF ((uint8_T)2U)
#define induction_heather_model_IN_ON  ((uint8_T)3U)
#define induction_heather_model_IN_ON_i ((uint8_T)4U)
#define induction_heather_model_LED_OFF (false)
#define induction_heather_model_LED_ON (true)

/* Block signals (default storage) */
B_induction_heather_model_T induction_heather_model_B;

/* Block states (default storage) */
DW_induction_heather_model_T induction_heather_model_DW;

/* Real-time model */
static RT_MODEL_induction_heather_mo_T induction_heather_model_M_;
RT_MODEL_induction_heather_mo_T *const induction_heather_model_M =
  &induction_heather_model_M_;

/* Forward declaration for local functions */
static void induction_heather_model_HEATER(void);

/* Function for Chart: '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
void induction_heather_button_during(boolean_T B1, boolean_T *button_state,
  real_T rtp_BUTTONDURATION, DW_INDUCTION_STOVEINPUTSBUTTO_T *localDW)
{
  switch (localDW->is_c4_library) {
   case induction_heathe_IN_longpressed:
    if (B1) {
      localDW->is_c4_library = induction_heather_model_IN_wait;
      *button_state = induction_heather_mode_RELEASED;
    }
    break;

   case induction_heather_mo_IN_pressed:
    if ((!*button_state) && (!B1)) {
      localDW->is_c4_library = induction_heathe_IN_longpressed;
      *button_state = induction_heather_mode_RELEASED;
    } else if (B1) {
      localDW->is_c4_library = induction_heather_model_IN_wait;
      *button_state = induction_heather_mode_RELEASED;
    } else if (localDW->temporalCounter_i1 >= (uint32_T)ceil(rtp_BUTTONDURATION *
                1000.0)) {
      *button_state = induction_heather_model_PRESSED;
    }
    break;

   default:
    /* case IN_wait: */
    if (!B1) {
      localDW->is_c4_library = induction_heather_mo_IN_pressed;
      localDW->temporalCounter_i1 = 0U;
      *button_state = induction_heather_mode_RELEASED;
    }
    break;
  }
}

/* Function for Chart: '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
void induction_heather__button_enter(boolean_T *button_state,
  DW_INDUCTION_STOVEINPUTSBUTTO_T *localDW)
{
  /* Chart: '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
  localDW->is_c4_library = induction_heather_model_IN_wait;
  *button_state = induction_heather_mode_RELEASED;
}

/* Function for Chart: '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
void induction_heathe_button_gateway(DW_INDUCTION_STOVEINPUTSBUTTO_T *localDW)
{
  if (localDW->temporalCounter_i1 < MAX_uint32_T) {
    localDW->temporalCounter_i1++;
  }
}

/* Function for Chart: '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
void induction_heather_m_button_init(DW_INDUCTION_STOVEINPUTSBUTTO_T *localDW)
{
  localDW->temporalCounter_i1 = 0U;
  localDW->is_c4_library = induction_he_IN_NO_ACTIVE_CHILD;
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T tmp;
  real_T tmp_0;
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = fabs(u0);
    tmp_0 = fabs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Function for Chart: '<Root>/Chart' */
static void induction_heather_model_HEATER(void)
{
  real_T tmp;
  boolean_T guard1;
  boolean_T guard2;
  guard1 = false;
  guard2 = false;
  switch (induction_heather_model_DW.is_HEATER) {
   case induction_heather_mo_IN_COOKING:
    if (!induction_heather_model_DW.b1s) {
      induction_heather_model_DW.is_COOKING = induction__IN_NO_ACTIVE_CHILD_j;
      induction_heather_model_DW.is_HEATER = induction_heather_model_IN_OFF;
      induction_heather_model_B.L1 = induction_heather_model_LED_OFF;
      induction_heather_model_B.L2 = induction_heather_model_LED_OFF;
      induction_heather_model_DW.l3s = induction_heather_model_LED_OFF;
      induction_heather_model_DW.period = 1;
    } else {
      switch (induction_heather_model_DW.is_COOKING) {
       case induction_heather_mo_IN_ANOMALY:
        if (!induction_heather_model_DW.ps) {
          induction_heather_model_B.L2 = induction_heather_model_LED_OFF;
          induction_heather_model_DW.is_COOKING =
            induction_heather_mode_IN_POWER;
          induction_heather_model_DW.l3s = induction_heather_model_LED_ON;
          tmp = rt_roundd_snf(2000.0 / rt_powd_snf(2.0,
            induction_heather_model_DW.next_level - 1.0));
          if (tmp < 2.147483648E+9) {
            induction_heather_model_DW.period = (int32_T)tmp;
          } else {
            induction_heather_model_DW.period = MAX_int32_T;
          }
        } else if (induction_heather_model_DW.temporalCounter_i1 >= 10000U) {
          induction_heather_model_DW.is_COOKING =
            induction__IN_NO_ACTIVE_CHILD_j;
          induction_heather_model_DW.is_HEATER = induction_heather_model_IN_ON;
          induction_heather_model_B.L1 = induction_heather_model_LED_ON;
          induction_heather_model_B.L2 = induction_heather_model_LED_OFF;
          induction_heather_model_DW.l3s = induction_heather_model_LED_OFF;
        }
        break;

       case induction_heather_mode_IN_POWER:
        if (induction_heather_model_DW.ps) {
          induction_heather_model_DW.is_COOKING =
            induction_heather_mo_IN_ANOMALY;
          induction_heather_model_DW.temporalCounter_i1 = 0U;
          induction_heather_model_B.L2 = induction_heather_model_LED_ON;
        } else if ((!induction_heather_model_DW.b2s) &&
                   (induction_heather_model_DW.next_level < 4.0)) {
          induction_heather_model_DW.next_level++;
          guard2 = true;
        } else if ((!induction_heather_model_DW.b3s) &&
                   (induction_heather_model_DW.next_level > 0.0)) {
          induction_heather_model_DW.next_level--;
          guard2 = true;
        }
        break;

       case induction_heather_mode_IN_READY:
        if (induction_heather_model_DW.ps) {
          induction_heather_model_DW.is_COOKING =
            induction__IN_NO_ACTIVE_CHILD_j;
          induction_heather_model_DW.is_HEATER = induction_heather_model_IN_ON;
          induction_heather_model_B.L1 = induction_heather_model_LED_ON;
          induction_heather_model_B.L2 = induction_heather_model_LED_OFF;
          induction_heather_model_DW.l3s = induction_heather_model_LED_OFF;
        } else if (!induction_heather_model_DW.b2s) {
          induction_heather_model_DW.next_level++;
          induction_heather_model_DW.is_COOKING =
            induction_heather_mo_IN_WAITING;
          induction_heather_model_DW.temporalCounter_i1 = 0U;
          induction_heather_model_DW.ready = false;
        }
        break;

       default:
        /* case IN_WAITING: */
        if ((!induction_heather_model_DW.b2s) &&
            (induction_heather_model_DW.next_level < 4.0)) {
          induction_heather_model_DW.next_level++;
          guard1 = true;
        } else if (induction_heather_model_DW.ps) {
          induction_heather_model_DW.is_COOKING =
            induction_heather_mo_IN_ANOMALY;
          induction_heather_model_DW.temporalCounter_i1 = 0U;
          induction_heather_model_B.L2 = induction_heather_model_LED_ON;
        } else if ((!induction_heather_model_DW.b3s) &&
                   (induction_heather_model_DW.next_level > 0.0)) {
          induction_heather_model_DW.next_level--;
          guard1 = true;
        } else if (induction_heather_model_DW.ready &&
                   (induction_heather_model_DW.next_level != 0.0)) {
          induction_heather_model_DW.is_COOKING =
            induction_heather_mode_IN_POWER;
          induction_heather_model_DW.l3s = induction_heather_model_LED_ON;
          tmp = rt_roundd_snf(2000.0 / rt_powd_snf(2.0,
            induction_heather_model_DW.next_level - 1.0));
          if (tmp < 2.147483648E+9) {
            induction_heather_model_DW.period = (int32_T)tmp;
          } else {
            induction_heather_model_DW.period = MAX_int32_T;
          }
        } else if (induction_heather_model_DW.ready &&
                   (induction_heather_model_DW.next_level == 0.0)) {
          induction_heather_model_DW.is_COOKING =
            induction_heather_mode_IN_READY;
          induction_heather_model_DW.next_level = 0.0;
          induction_heather_model_DW.l3s = induction_heather_model_LED_OFF;
          induction_heather_model_DW.period = 0;
        } else {
          induction_heather_model_DW.ready =
            (induction_heather_model_DW.temporalCounter_i1 >= 5000U);
        }
        break;
      }
    }
    break;

   case induction_heather_model_IN_OFF:
    induction_heather_model_B.L1 = induction_heather_model_LED_OFF;
    if (!induction_heather_model_DW.b1s) {
      induction_heather_model_DW.is_HEATER = induction_heather_model_IN_ON;
      induction_heather_model_B.L1 = induction_heather_model_LED_ON;
      induction_heather_model_B.L2 = induction_heather_model_LED_OFF;
      induction_heather_model_DW.l3s = induction_heather_model_LED_OFF;
    }
    break;

   default:
    /* case IN_ON: */
    induction_heather_model_B.L1 = induction_heather_model_LED_ON;
    if (!induction_heather_model_DW.ps) {
      induction_heather_model_DW.is_HEATER = induction_heather_mo_IN_COOKING;
      induction_heather_model_DW.is_COOKING = induction_heather_mode_IN_READY;
      induction_heather_model_DW.next_level = 0.0;
      induction_heather_model_DW.l3s = induction_heather_model_LED_OFF;
      induction_heather_model_DW.period = 0;
    } else if (!induction_heather_model_DW.b1s) {
      induction_heather_model_DW.is_HEATER = induction_heather_model_IN_OFF;
      induction_heather_model_B.L1 = induction_heather_model_LED_OFF;
      induction_heather_model_B.L2 = induction_heather_model_LED_OFF;
      induction_heather_model_DW.l3s = induction_heather_model_LED_OFF;
      induction_heather_model_DW.period = 1;
    }
    break;
  }

  if (guard2) {
    induction_heather_model_DW.is_COOKING = induction_heather_mo_IN_WAITING;
    induction_heather_model_DW.temporalCounter_i1 = 0U;
    induction_heather_model_DW.ready = false;
  }

  if (guard1) {
    induction_heather_model_DW.is_COOKING = induction_heather_mo_IN_WAITING;
    induction_heather_model_DW.temporalCounter_i1 = 0U;
    induction_heather_model_DW.ready = false;
  }
}

/* Model step function */
void induction_heather_model_step(void)
{
  boolean_T DigitalRead3;
  boolean_T L3;

  /* MATLABSystem: '<Root>/Digital Read' */
  if (induction_heather_model_DW.obj_h.SampleTime !=
      induction_heather_model_P.DigitalRead_SampleTime) {
    induction_heather_model_DW.obj_h.SampleTime =
      induction_heather_model_P.DigitalRead_SampleTime;
  }

  L3 = MW_digitalIO_read(induction_heather_model_DW.obj_h.MW_DIGITALIO_HANDLE);

  /* MATLABSystem: '<Root>/Digital Read1' */
  if (induction_heather_model_DW.obj_b.SampleTime !=
      induction_heather_model_P.DigitalRead1_SampleTime) {
    induction_heather_model_DW.obj_b.SampleTime =
      induction_heather_model_P.DigitalRead1_SampleTime;
  }

  /* MATLABSystem: '<Root>/Digital Read1' */
  induction_heather_model_B.DigitalRead1 = MW_digitalIO_read
    (induction_heather_model_DW.obj_b.MW_DIGITALIO_HANDLE);

  /* MATLABSystem: '<Root>/Digital Read2' */
  if (induction_heather_model_DW.obj_m.SampleTime !=
      induction_heather_model_P.DigitalRead2_SampleTime) {
    induction_heather_model_DW.obj_m.SampleTime =
      induction_heather_model_P.DigitalRead2_SampleTime;
  }

  /* MATLABSystem: '<Root>/Digital Read2' */
  induction_heather_model_B.DigitalRead2 = MW_digitalIO_read
    (induction_heather_model_DW.obj_m.MW_DIGITALIO_HANDLE);

  /* MATLABSystem: '<Root>/Digital Read3' */
  if (induction_heather_model_DW.obj.SampleTime !=
      induction_heather_model_P.DigitalRead3_SampleTime) {
    induction_heather_model_DW.obj.SampleTime =
      induction_heather_model_P.DigitalRead3_SampleTime;
  }

  DigitalRead3 = MW_digitalIO_read
    (induction_heather_model_DW.obj.MW_DIGITALIO_HANDLE);

  /* Chart: '<Root>/Chart' incorporates:
   *  Chart: '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2'
   *  Chart: '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_3'
   *  MATLABSystem: '<Root>/Digital Read'
   *  MATLABSystem: '<Root>/Digital Read3'
   */
  if (induction_heather_model_DW.temporalCounter_i1 < 16383U) {
    induction_heather_model_DW.temporalCounter_i1++;
  }

  if (induction_heather_model_DW.temporalCounter_i2 < 1023U) {
    induction_heather_model_DW.temporalCounter_i2++;
  }

  if (induction_heather_model_DW.temporalCounter_i3 < MAX_uint32_T) {
    induction_heather_model_DW.temporalCounter_i3++;
  }

  induction_heathe_button_gateway
    (&induction_heather_model_DW.sf_INDUCTION_STOVEINPUTSBUTTO_m);
  induction_heathe_button_gateway
    (&induction_heather_model_DW.sf_INDUCTION_STOVEINPUTSBUTTON_);
  if (induction_heather_model_DW.temporalCounter_i1_d < 511U) {
    induction_heather_model_DW.temporalCounter_i1_d++;
  }

  if (induction_heather_model_DW.is_active_c2_induction_heather_ == 0U) {
    induction_heather_model_DW.is_active_c2_induction_heather_ = 1U;
    induction_heather_model_DW.is_HEATER = induction_heather_model_IN_OFF;
    induction_heather_model_B.L1 = induction_heather_model_LED_OFF;
    induction_heather_model_B.L2 = induction_heather_model_LED_OFF;
    induction_heather_model_DW.l3s = induction_heather_model_LED_OFF;
    induction_heather_model_DW.period = 1;
    induction_heather_model_DW.is_active_BUTTON_2 = 1U;
    induction_heather__button_enter(&induction_heather_model_DW.b2s,
      &induction_heather_model_DW.sf_INDUCTION_STOVEINPUTSBUTTON_);
    induction_heather_model_DW.is_active_PRESENCE = 1U;

    /* Chart: '<S1>/INDUCTION_STOVE.INPUTS.PRESENCE' */
    induction_heather_model_DW.is_c1_library = induction_heather_mod_IN_wait_m;
    induction_heather_model_DW.ps = true;
    induction_heather_model_DW.tp_BUTTON_1 = 1U;
    induction_heather_model_DW.is_BUTTON_1 = induction_heather_mode_IN_OFF_g;
    induction_heather_model_DW.b1s = true;
    induction_heather_model_DW.is_active_BUTTON_3 = 1U;
    induction_heather__button_enter(&induction_heather_model_DW.b3s,
      &induction_heather_model_DW.sf_INDUCTION_STOVEINPUTSBUTTO_m);
    induction_heather_model_DW.is_POWER_LED = induction_heather_mod_IN_OFF_gt;
    induction_heather_model_DW.temporalCounter_i3 = 0U;
    L3 = induction_heather_model_LED_OFF;
  } else {
    induction_heather_model_HEATER();
    induction_heather_button_during(induction_heather_model_B.DigitalRead1,
      &induction_heather_model_DW.b2s,
      induction_heather_model_P.INDUCTION_STOVEINPUTSBUTTON_2_B,
      &induction_heather_model_DW.sf_INDUCTION_STOVEINPUTSBUTTON_);
    if (induction_heather_model_DW.is_c1_library ==
        induction_heather__IN_pressed_o) {
      if (DigitalRead3) {
        induction_heather_model_DW.is_c1_library =
          induction_heather_mod_IN_wait_m;
        induction_heather_model_DW.ps = true;
      } else {
        induction_heather_model_DW.ps =
          ((induction_heather_model_DW.temporalCounter_i1_d < 500U) &&
           induction_heather_model_DW.ps);
      }

      /* case IN_wait: */
    } else if (!DigitalRead3) {
      induction_heather_model_DW.is_c1_library = induction_heather__IN_pressed_o;
      induction_heather_model_DW.temporalCounter_i1_d = 0U;
      induction_heather_model_DW.ps = true;
    }

    switch (induction_heather_model_DW.is_BUTTON_1) {
     case induction_he_IN_LONGPRESSED_OFF:
      if (L3) {
        induction_heather_model_DW.is_BUTTON_1 = induction_heather_mode_IN_OFF_g;
        induction_heather_model_DW.b1s = true;
      }
      break;

     case induction_hea_IN_LONGPRESSED_ON:
      if (L3) {
        induction_heather_model_DW.is_BUTTON_1 = induction_heather_model_IN_ON_i;
        induction_heather_model_DW.b1s = true;
      }
      break;

     case induction_heather_mode_IN_OFF_g:
      if (!L3) {
        induction_heather_model_DW.is_BUTTON_1 = induction_heather_mo_IN_WAIT_ON;
        induction_heather_model_DW.temporalCounter_i2 = 0U;
      }
      break;

     case induction_heather_model_IN_ON_i:
      if (!L3) {
        induction_heather_model_DW.is_BUTTON_1 = induction_heather_m_IN_WAIT_OFF;
        induction_heather_model_DW.temporalCounter_i2 = 0U;
      }
      break;

     case induction_heather_m_IN_WAIT_OFF:
      if ((!L3) && (!induction_heather_model_DW.b1s)) {
        induction_heather_model_DW.is_BUTTON_1 = induction_he_IN_LONGPRESSED_OFF;
        induction_heather_model_DW.b1s = true;
      } else if (L3) {
        induction_heather_model_DW.is_BUTTON_1 = induction_heather_model_IN_ON_i;
        induction_heather_model_DW.b1s = true;
      } else {
        induction_heather_model_DW.b1s =
          ((induction_heather_model_DW.temporalCounter_i2 < 1000U) &&
           induction_heather_model_DW.b1s);
      }
      break;

     default:
      /* case IN_WAIT_ON: */
      if ((!L3) && (!induction_heather_model_DW.b1s)) {
        induction_heather_model_DW.is_BUTTON_1 = induction_hea_IN_LONGPRESSED_ON;
        induction_heather_model_DW.b1s = true;
      } else if (L3) {
        induction_heather_model_DW.is_BUTTON_1 = induction_heather_mode_IN_OFF_g;
        induction_heather_model_DW.b1s = true;
      } else {
        induction_heather_model_DW.b1s =
          ((induction_heather_model_DW.temporalCounter_i2 < 200U) &&
           induction_heather_model_DW.b1s);
      }
      break;
    }

    induction_heather_button_during(induction_heather_model_B.DigitalRead2,
      &induction_heather_model_DW.b3s,
      induction_heather_model_P.INDUCTION_STOVEINPUTSBUTTON_3_B,
      &induction_heather_model_DW.sf_INDUCTION_STOVEINPUTSBUTTO_m);
    if (induction_heather_model_DW.is_POWER_LED ==
        induction_heather_mod_IN_OFF_gt) {
      L3 = induction_heather_model_LED_OFF;
      if ((induction_heather_model_DW.temporalCounter_i3 >= (uint32_T)
           rt_roundd_snf((real_T)induction_heather_model_DW.period / 2.0)) &&
          induction_heather_model_DW.l3s) {
        induction_heather_model_DW.is_POWER_LED =
          induction_heather_mode_IN_ON_ie;
        induction_heather_model_DW.temporalCounter_i3 = 0U;
        L3 = induction_heather_model_LED_ON;
      }
    } else {
      /* case IN_ON: */
      L3 = induction_heather_model_LED_ON;
      if ((!induction_heather_model_DW.l3s) ||
          (induction_heather_model_DW.temporalCounter_i3 >= (uint32_T)
           rt_roundd_snf((real_T)induction_heather_model_DW.period / 2.0))) {
        induction_heather_model_DW.is_POWER_LED =
          induction_heather_mod_IN_OFF_gt;
        induction_heather_model_DW.temporalCounter_i3 = 0U;
        L3 = induction_heather_model_LED_OFF;
      }
    }
  }

  /* End of Chart: '<Root>/Chart' */

  /* MATLABSystem: '<Root>/Digital Write' */
  MW_digitalIO_write(induction_heather_model_DW.obj_bs.MW_DIGITALIO_HANDLE,
                     induction_heather_model_B.L1);

  /* MATLABSystem: '<Root>/Digital Write1' */
  MW_digitalIO_write(induction_heather_model_DW.obj_ac.MW_DIGITALIO_HANDLE,
                     induction_heather_model_B.L2);

  /* MATLABSystem: '<Root>/Digital Write2' */
  MW_digitalIO_write(induction_heather_model_DW.obj_a.MW_DIGITALIO_HANDLE, L3);
}

/* Model initialize function */
void induction_heather_model_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(induction_heather_model_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &induction_heather_model_B), 0,
                sizeof(B_induction_heather_model_T));

  /* states (dwork) */
  (void) memset((void *)&induction_heather_model_DW, 0,
                sizeof(DW_induction_heather_model_T));

  {
    uint32_T pinname;
    mbed_DigitalRead_induction_he_T *obj;
    mbed_DigitalWrite_induction_h_T *obj_0;

    /* Start for MATLABSystem: '<Root>/Digital Read' */
    induction_heather_model_DW.obj_h.matlabCodegenIsDeleted = false;
    induction_heather_model_DW.objisempty_i = true;
    induction_heather_model_DW.obj_h.SampleTime =
      induction_heather_model_P.DigitalRead_SampleTime;
    obj = &induction_heather_model_DW.obj_h;
    induction_heather_model_DW.obj_h.isInitialized = 1;
    pinname = PC_13;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 0);
    induction_heather_model_DW.obj_h.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Read1' */
    induction_heather_model_DW.obj_b.matlabCodegenIsDeleted = false;
    induction_heather_model_DW.objisempty_o = true;
    induction_heather_model_DW.obj_b.SampleTime =
      induction_heather_model_P.DigitalRead1_SampleTime;
    obj = &induction_heather_model_DW.obj_b;
    induction_heather_model_DW.obj_b.isInitialized = 1;
    pinname = PC_2;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 0);
    induction_heather_model_DW.obj_b.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Read2' */
    induction_heather_model_DW.obj_m.matlabCodegenIsDeleted = false;
    induction_heather_model_DW.objisempty_b = true;
    induction_heather_model_DW.obj_m.SampleTime =
      induction_heather_model_P.DigitalRead2_SampleTime;
    obj = &induction_heather_model_DW.obj_m;
    induction_heather_model_DW.obj_m.isInitialized = 1;
    pinname = PC_3;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 0);
    induction_heather_model_DW.obj_m.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Read3' */
    induction_heather_model_DW.obj.matlabCodegenIsDeleted = false;
    induction_heather_model_DW.objisempty_g = true;
    induction_heather_model_DW.obj.SampleTime =
      induction_heather_model_P.DigitalRead3_SampleTime;
    obj = &induction_heather_model_DW.obj;
    induction_heather_model_DW.obj.isInitialized = 1;
    pinname = PC_10;
    obj->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 0);
    induction_heather_model_DW.obj.isSetupComplete = true;

    /* Start for DataStoreMemory: '<S1>/ ' incorporates:
     *  Chart: '<Root>/Chart'
     */
    induction_heather_model_DW.b2s = induction_heather_model_P._InitialValue;

    /* Start for DataStoreMemory: '<S1>/ 1' incorporates:
     *  Chart: '<Root>/Chart'
     */
    induction_heather_model_DW.b3s = induction_heather_model_P.u_InitialValue;

    /* Start for DataStoreMemory: '<S1>/ 2' incorporates:
     *  Chart: '<Root>/Chart'
     */
    induction_heather_model_DW.ps = induction_heather_model_P.u_InitialValue_i;

    /* Start for MATLABSystem: '<Root>/Digital Write' */
    induction_heather_model_DW.obj_bs.matlabCodegenIsDeleted = false;
    induction_heather_model_DW.objisempty_l = true;
    obj_0 = &induction_heather_model_DW.obj_bs;
    induction_heather_model_DW.obj_bs.isInitialized = 1;
    pinname = PA_5;
    obj_0->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 1);
    induction_heather_model_DW.obj_bs.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write1' */
    induction_heather_model_DW.obj_ac.matlabCodegenIsDeleted = false;
    induction_heather_model_DW.objisempty_n = true;
    obj_0 = &induction_heather_model_DW.obj_ac;
    induction_heather_model_DW.obj_ac.isInitialized = 1;
    pinname = PA_7;
    obj_0->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 1);
    induction_heather_model_DW.obj_ac.isSetupComplete = true;

    /* Start for MATLABSystem: '<Root>/Digital Write2' */
    induction_heather_model_DW.obj_a.matlabCodegenIsDeleted = false;
    induction_heather_model_DW.objisempty = true;
    obj_0 = &induction_heather_model_DW.obj_a;
    induction_heather_model_DW.obj_a.isInitialized = 1;
    pinname = PA_6;
    obj_0->MW_DIGITALIO_HANDLE = MW_digitalIO_open(pinname, 1);
    induction_heather_model_DW.obj_a.isSetupComplete = true;
  }

  /* SystemInitialize for Chart: '<Root>/Chart' */
  induction_heather_m_button_init
    (&induction_heather_model_DW.sf_INDUCTION_STOVEINPUTSBUTTO_m);
  induction_heather_m_button_init
    (&induction_heather_model_DW.sf_INDUCTION_STOVEINPUTSBUTTON_);
  induction_heather_model_DW.temporalCounter_i1_d = 0U;
  induction_heather_model_DW.is_c1_library = induction__IN_NO_ACTIVE_CHILD_j;
  induction_heather_model_DW.is_HEATER = induction__IN_NO_ACTIVE_CHILD_j;
  induction_heather_model_DW.is_COOKING = induction__IN_NO_ACTIVE_CHILD_j;
  induction_heather_model_DW.temporalCounter_i1 = 0U;
  induction_heather_model_DW.is_BUTTON_1 = induction__IN_NO_ACTIVE_CHILD_j;
  induction_heather_model_DW.tp_BUTTON_1 = 0U;
  induction_heather_model_DW.temporalCounter_i2 = 0U;
  induction_heather_model_DW.is_active_BUTTON_2 = 0U;
  induction_heather_model_DW.is_active_BUTTON_3 = 0U;
  induction_heather_model_DW.is_active_PRESENCE = 0U;
  induction_heather_model_DW.is_POWER_LED = induction__IN_NO_ACTIVE_CHILD_j;
  induction_heather_model_DW.temporalCounter_i3 = 0U;
  induction_heather_model_DW.is_active_c2_induction_heather_ = 0U;
  induction_heather_model_DW.b1s = false;
  induction_heather_model_DW.ps = false;
  induction_heather_model_DW.b3s = false;
  induction_heather_model_DW.b2s = false;
  induction_heather_model_DW.l3s = false;
  induction_heather_model_DW.period = 0;
  induction_heather_model_DW.next_level = 0.0;
  induction_heather_model_DW.ready = false;
  induction_heather_model_B.L1 = false;
  induction_heather_model_B.L2 = false;
}

/* Model terminate function */
void induction_heather_model_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Digital Read' */
  if (!induction_heather_model_DW.obj_h.matlabCodegenIsDeleted) {
    induction_heather_model_DW.obj_h.matlabCodegenIsDeleted = true;
    if ((induction_heather_model_DW.obj_h.isInitialized == 1) &&
        induction_heather_model_DW.obj_h.isSetupComplete) {
      MW_digitalIO_close(induction_heather_model_DW.obj_h.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Read' */

  /* Terminate for MATLABSystem: '<Root>/Digital Read1' */
  if (!induction_heather_model_DW.obj_b.matlabCodegenIsDeleted) {
    induction_heather_model_DW.obj_b.matlabCodegenIsDeleted = true;
    if ((induction_heather_model_DW.obj_b.isInitialized == 1) &&
        induction_heather_model_DW.obj_b.isSetupComplete) {
      MW_digitalIO_close(induction_heather_model_DW.obj_b.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Read1' */

  /* Terminate for MATLABSystem: '<Root>/Digital Read2' */
  if (!induction_heather_model_DW.obj_m.matlabCodegenIsDeleted) {
    induction_heather_model_DW.obj_m.matlabCodegenIsDeleted = true;
    if ((induction_heather_model_DW.obj_m.isInitialized == 1) &&
        induction_heather_model_DW.obj_m.isSetupComplete) {
      MW_digitalIO_close(induction_heather_model_DW.obj_m.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Read2' */

  /* Terminate for MATLABSystem: '<Root>/Digital Read3' */
  if (!induction_heather_model_DW.obj.matlabCodegenIsDeleted) {
    induction_heather_model_DW.obj.matlabCodegenIsDeleted = true;
    if ((induction_heather_model_DW.obj.isInitialized == 1) &&
        induction_heather_model_DW.obj.isSetupComplete) {
      MW_digitalIO_close(induction_heather_model_DW.obj.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Read3' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write' */
  if (!induction_heather_model_DW.obj_bs.matlabCodegenIsDeleted) {
    induction_heather_model_DW.obj_bs.matlabCodegenIsDeleted = true;
    if ((induction_heather_model_DW.obj_bs.isInitialized == 1) &&
        induction_heather_model_DW.obj_bs.isSetupComplete) {
      MW_digitalIO_close(induction_heather_model_DW.obj_bs.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write1' */
  if (!induction_heather_model_DW.obj_ac.matlabCodegenIsDeleted) {
    induction_heather_model_DW.obj_ac.matlabCodegenIsDeleted = true;
    if ((induction_heather_model_DW.obj_ac.isInitialized == 1) &&
        induction_heather_model_DW.obj_ac.isSetupComplete) {
      MW_digitalIO_close(induction_heather_model_DW.obj_ac.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write1' */

  /* Terminate for MATLABSystem: '<Root>/Digital Write2' */
  if (!induction_heather_model_DW.obj_a.matlabCodegenIsDeleted) {
    induction_heather_model_DW.obj_a.matlabCodegenIsDeleted = true;
    if ((induction_heather_model_DW.obj_a.isInitialized == 1) &&
        induction_heather_model_DW.obj_a.isSetupComplete) {
      MW_digitalIO_close(induction_heather_model_DW.obj_a.MW_DIGITALIO_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Digital Write2' */
}
