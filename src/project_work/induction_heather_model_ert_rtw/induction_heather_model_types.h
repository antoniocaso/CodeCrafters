/*
 * induction_heather_model_types.h
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

#ifndef RTW_HEADER_induction_heather_model_types_h_
#define RTW_HEADER_induction_heather_model_types_h_
#include "rtwtypes.h"
#include "MW_SVD.h"

/* Custom Type definition for MATLABSystem: '<Root>/Digital Write2' */
#include "MW_SVD.h"
#ifndef struct_tag_5FwKk6wA1XPbMoI1XCDeDF
#define struct_tag_5FwKk6wA1XPbMoI1XCDeDF

struct tag_5FwKk6wA1XPbMoI1XCDeDF
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  MW_Handle_Type MW_DIGITALIO_HANDLE;
  real_T SampleTime;
};

#endif                                 /* struct_tag_5FwKk6wA1XPbMoI1XCDeDF */

#ifndef typedef_mbed_DigitalRead_induction_he_T
#define typedef_mbed_DigitalRead_induction_he_T

typedef struct tag_5FwKk6wA1XPbMoI1XCDeDF mbed_DigitalRead_induction_he_T;

#endif                             /* typedef_mbed_DigitalRead_induction_he_T */

#ifndef struct_tag_KxFW01GBdhqk5JOEHU3GlD
#define struct_tag_KxFW01GBdhqk5JOEHU3GlD

struct tag_KxFW01GBdhqk5JOEHU3GlD
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  MW_Handle_Type MW_DIGITALIO_HANDLE;
};

#endif                                 /* struct_tag_KxFW01GBdhqk5JOEHU3GlD */

#ifndef typedef_mbed_DigitalWrite_induction_h_T
#define typedef_mbed_DigitalWrite_induction_h_T

typedef struct tag_KxFW01GBdhqk5JOEHU3GlD mbed_DigitalWrite_induction_h_T;

#endif                             /* typedef_mbed_DigitalWrite_induction_h_T */

/* Parameters (default storage) */
typedef struct P_induction_heather_model_T_ P_induction_heather_model_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_induction_heather_mod_T RT_MODEL_induction_heather_mo_T;

#endif                         /* RTW_HEADER_induction_heather_model_types_h_ */
