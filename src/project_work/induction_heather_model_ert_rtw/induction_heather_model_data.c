/*
 * induction_heather_model_data.c
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

/* Block parameters (default storage) */
P_induction_heather_model_T induction_heather_model_P = {
  /* Mask Parameter: INDUCTION_STOVEINPUTSBUTTON_2_B
   * Referenced by: '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_2'
   */
  1.0,

  /* Mask Parameter: INDUCTION_STOVEINPUTSBUTTON_3_B
   * Referenced by: '<S1>/INDUCTION_STOVE.INPUTS.BUTTON_3'
   */
  1.0,

  /* Expression: 0.001
   * Referenced by: '<Root>/Digital Read'
   */
  0.001,

  /* Expression: 0.001
   * Referenced by: '<Root>/Digital Read1'
   */
  0.001,

  /* Expression: 0.001
   * Referenced by: '<Root>/Digital Read2'
   */
  0.001,

  /* Expression: 0.001
   * Referenced by: '<Root>/Digital Read3'
   */
  0.001,

  /* Computed Parameter: _InitialValue
   * Referenced by: '<Root>/Chart'
   */
  false,

  /* Computed Parameter: u_InitialValue
   * Referenced by: '<Root>/Chart'
   */
  false,

  /* Computed Parameter: u_InitialValue_i
   * Referenced by: '<Root>/Chart'
   */
  false
};
