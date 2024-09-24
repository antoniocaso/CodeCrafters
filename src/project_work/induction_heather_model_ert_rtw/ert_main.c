#include "induction_heather_model.h"
#include "rtwtypes.h"
#include "MW_target_hardware_resources.h"

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;
void rt_OneStep(void)
{
  /* Check for overrun. Protect OverrunFlag against preemption */
  if (OverrunFlag++) {
    IsrOverrun = 1;
    OverrunFlag--;
    return;
  }

  __enable_irq();
  induction_heather_model_step();

  /* Get model outputs here */
  __disable_irq();
  OverrunFlag--;
}

volatile boolean_T stopRequested;
volatile boolean_T runModel;
int main(void)
{
  float modelBaseRate = 0.001;
  float systemClock = 84;

  /* Initialize variables */
  stopRequested = false;
  runModel = false;

#if defined(MW_MULTI_TASKING_MODE) && (MW_MULTI_TASKING_MODE == 1)

  MW_ASM (" SVC #1");

#endif

  ;
  (void)systemClock;
  HAL_Init();
  bootloaderInit();
  SystemCoreClockUpdate();
  rtmSetErrorStatus(induction_heather_model_M, 0);
  induction_heather_model_initialize();
  ;
  ARMCM_SysTick_Config(modelBaseRate);
  runModel = rtmGetErrorStatus(induction_heather_model_M) == (NULL);
  __enable_irq();
  ;
  while (runModel) {
    stopRequested = !(rtmGetErrorStatus(induction_heather_model_M) == (NULL));
    runModel = !(stopRequested);
  }

  /* Terminate model */
  induction_heather_model_terminate();
  ;
  return 0;
}
