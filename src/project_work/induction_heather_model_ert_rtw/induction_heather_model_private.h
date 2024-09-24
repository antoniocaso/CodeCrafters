/*
 * induction_heather_model_private.h
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

#ifndef RTW_HEADER_induction_heather_model_private_h_
#define RTW_HEADER_induction_heather_model_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "induction_heather_model.h"
#include "induction_heather_model_types.h"

/* Exported functions */
extern void induction_heather_button_during(boolean_T B1, boolean_T
  *button_state, real_T rtp_BUTTONDURATION, DW_INDUCTION_STOVEINPUTSBUTTO_T
  *localDW);
extern void induction_heather__button_enter(boolean_T *button_state,
  DW_INDUCTION_STOVEINPUTSBUTTO_T *localDW);
extern void induction_heathe_button_gateway(DW_INDUCTION_STOVEINPUTSBUTTO_T
  *localDW);
extern void induction_heather_m_button_init(DW_INDUCTION_STOVEINPUTSBUTTO_T
  *localDW);
extern real_T rt_powd_snf(real_T u0, real_T u1);
extern real_T rt_roundd_snf(real_T u);

#endif                       /* RTW_HEADER_induction_heather_model_private_h_ */
