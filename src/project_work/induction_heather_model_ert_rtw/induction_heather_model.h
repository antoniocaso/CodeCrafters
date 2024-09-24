/*
 * induction_heather_model.h
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

#ifndef RTW_HEADER_induction_heather_model_h_
#define RTW_HEADER_induction_heather_model_h_
#ifndef induction_heather_model_COMMON_INCLUDES_
#define induction_heather_model_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_MbedPinInterface.h"
#include "MW_digitalIO.h"
#endif                            /* induction_heather_model_COMMON_INCLUDES_ */

#include "induction_heather_model_types.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include <stddef.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
typedef struct {
  boolean_T button_state;           /* '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
} B_INDUCTION_STOVEINPUTSBUTTON_T;

/* Block states (default storage) for system '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
typedef struct {
  uint32_T temporalCounter_i1;      /* '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
  uint8_T is_c4_library;            /* '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
} DW_INDUCTION_STOVEINPUTSBUTTO_T;

/* Block signals (default storage) */
typedef struct {
  boolean_T DigitalRead2;              /* '<Root>/Digital Read2' */
  boolean_T DigitalRead1;              /* '<Root>/Digital Read1' */
  boolean_T L1;                        /* '<Root>/Chart' */
  boolean_T L2;                        /* '<Root>/Chart' */
  boolean_T presence_state;         /* '<S1>/INDUCTION_STOVE.INPUTS.PRESENCE' */
  B_INDUCTION_STOVEINPUTSBUTTON_T sf_INDUCTION_STOVEINPUTSBUTTO_m;
                                    /* '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_3' */
  B_INDUCTION_STOVEINPUTSBUTTON_T sf_INDUCTION_STOVEINPUTSBUTTON_;
                                    /* '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
} B_induction_heather_model_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  mbed_DigitalRead_induction_he_T obj; /* '<Root>/Digital Read3' */
  mbed_DigitalRead_induction_he_T obj_m;/* '<Root>/Digital Read2' */
  mbed_DigitalRead_induction_he_T obj_b;/* '<Root>/Digital Read1' */
  mbed_DigitalRead_induction_he_T obj_h;/* '<Root>/Digital Read' */
  mbed_DigitalWrite_induction_h_T obj_a;/* '<Root>/Digital Write2' */
  mbed_DigitalWrite_induction_h_T obj_ac;/* '<Root>/Digital Write1' */
  mbed_DigitalWrite_induction_h_T obj_bs;/* '<Root>/Digital Write' */
  real_T next_level;                   /* '<Root>/Chart' */
  int32_T period;                      /* '<Root>/Chart' */
  uint32_T temporalCounter_i3;         /* '<Root>/Chart' */
  uint16_T temporalCounter_i1;         /* '<Root>/Chart' */
  uint16_T temporalCounter_i2;         /* '<Root>/Chart' */
  uint16_T temporalCounter_i1_d;    /* '<S1>/INDUCTION_STOVE.INPUTS.PRESENCE' */
  uint8_T is_active_c2_induction_heather_;/* '<Root>/Chart' */
  uint8_T is_HEATER;                   /* '<Root>/Chart' */
  uint8_T is_COOKING;                  /* '<Root>/Chart' */
  uint8_T is_active_BUTTON_2;          /* '<Root>/Chart' */
  uint8_T is_active_PRESENCE;          /* '<Root>/Chart' */
  uint8_T tp_BUTTON_1;                 /* '<Root>/Chart' */
  uint8_T is_BUTTON_1;                 /* '<Root>/Chart' */
  uint8_T is_active_BUTTON_3;          /* '<Root>/Chart' */
  uint8_T is_POWER_LED;                /* '<Root>/Chart' */
  uint8_T is_c1_library;            /* '<S1>/INDUCTION_STOVE.INPUTS.PRESENCE' */
  boolean_T objisempty;                /* '<Root>/Digital Write2' */
  boolean_T objisempty_n;              /* '<Root>/Digital Write1' */
  boolean_T objisempty_l;              /* '<Root>/Digital Write' */
  boolean_T objisempty_g;              /* '<Root>/Digital Read3' */
  boolean_T objisempty_b;              /* '<Root>/Digital Read2' */
  boolean_T objisempty_o;              /* '<Root>/Digital Read1' */
  boolean_T objisempty_i;              /* '<Root>/Digital Read' */
  boolean_T b1s;                       /* '<Root>/Chart' */
  boolean_T l3s;                       /* '<Root>/Chart' */
  boolean_T ready;                     /* '<Root>/Chart' */
  boolean_T b2s;                       /* '<Root>/Chart' */
  boolean_T b3s;                       /* '<Root>/Chart' */
  boolean_T ps;                        /* '<Root>/Chart' */
  DW_INDUCTION_STOVEINPUTSBUTTO_T sf_INDUCTION_STOVEINPUTSBUTTO_m;
                                    /* '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_3' */
  DW_INDUCTION_STOVEINPUTSBUTTO_T sf_INDUCTION_STOVEINPUTSBUTTON_;
                                    /* '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2' */
} DW_induction_heather_model_T;

/* Parameters (default storage) */
struct P_induction_heather_model_T_ {
  real_T INDUCTION_STOVEINPUTSBUTTON_2_B;
                              /* Mask Parameter: INDUCTION_STOVEINPUTSBUTTON_2_B
                               * Referenced by: '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2'
                               */
  real_T INDUCTION_STOVEINPUTSBUTTON_3_B;
                              /* Mask Parameter: INDUCTION_STOVEINPUTSBUTTON_3_B
                               * Referenced by: '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_3'
                               */
  real_T DigitalRead_SampleTime;       /* Expression: 0.001
                                        * Referenced by: '<Root>/Digital Read'
                                        */
  real_T DigitalRead1_SampleTime;      /* Expression: 0.001
                                        * Referenced by: '<Root>/Digital Read1'
                                        */
  real_T DigitalRead2_SampleTime;      /* Expression: 0.001
                                        * Referenced by: '<Root>/Digital Read2'
                                        */
  real_T DigitalRead3_SampleTime;      /* Expression: 0.001
                                        * Referenced by: '<Root>/Digital Read3'
                                        */
  boolean_T _InitialValue;             /* Computed Parameter: _InitialValue
                                        * Referenced by: '<Root>/Chart'
                                        */
  boolean_T u_InitialValue;            /* Computed Parameter: u_InitialValue
                                        * Referenced by: '<Root>/Chart'
                                        */
  boolean_T u_InitialValue_i;          /* Computed Parameter: u_InitialValue_i
                                        * Referenced by: '<Root>/Chart'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_induction_heather_mod_T {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
extern P_induction_heather_model_T induction_heather_model_P;

/* Block signals (default storage) */
extern B_induction_heather_model_T induction_heather_model_B;

/* Block states (default storage) */
extern DW_induction_heather_model_T induction_heather_model_DW;

/* Model entry point functions */
extern void induction_heather_model_initialize(void);
extern void induction_heather_model_step(void);
extern void induction_heather_model_terminate(void);

/* Real-time Model object */
extern RT_MODEL_induction_heather_mo_T *const induction_heather_model_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'induction_heather_model'
 * '<S1>'   : 'induction_heather_model/Chart'
 * '<S2>'   : 'induction_heather_model/Chart/INDUCTION_STOVE.INPUTS.BUTTON_2'
 * '<S3>'   : 'induction_heather_model/Chart/INDUCTION_STOVE.INPUTS.BUTTON_3'
 * '<S4>'   : 'induction_heather_model/Chart/INDUCTION_STOVE.INPUTS.PRESENCE'
 */
#endif                               /* RTW_HEADER_induction_heather_model_h_ */
