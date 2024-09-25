/**
  ******************************************************************************
  * @file panda_hcsr04_driver.c
  * @brief This file contains the implementation of the panda_HCSR04 library.
  *
  * The library is designed to interact with a HCSR04 module.
  *
  * It includes functions to initialize the module and
  * read the module state
  *
  *
  ******************************************************************************
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "panda_hcsr04_driver.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "gpio.h"
#include <stdint.h>
#include <stdio.h>



HCSR04_StatusTypeDef panda_HCSR04_init(HCSR04_t* ultrasound, TIM_HandleTypeDef *timer, GPIO_TypeDef* port_trigger, uint16_t pin_trigger){

	int8_t res = HCSR04_ERR;

	ultrasound->port_trigger = port_trigger;
	ultrasound->pin_trigger = pin_trigger;
	ultrasound->timer = timer;
	ultrasound->IC_Val1 =  0;
	ultrasound->IC_Val2 = 0;
	ultrasound->Difference =0;
	ultrasound->Is_First_Captured = 0;
	ultrasound->Distance = 0;

	res = HCSR04_OK;

	return res;
}






HCSR04_StatusTypeDef panda_HCSR04_callback_evaluations(HCSR04_t* ultrasound, uint32_t Channel){

	uint8_t res = HCSR04_ERR;

	if (ultrasound->Is_First_Captured==0)
	{
		ultrasound->IC_Val1 = HAL_TIM_ReadCapturedValue(ultrasound->timer, Channel);
		ultrasound->Is_First_Captured = 1;
		__HAL_TIM_SET_CAPTUREPOLARITY(ultrasound->timer, Channel, TIM_INPUTCHANNELPOLARITY_FALLING);
	}

	else if (ultrasound->Is_First_Captured==1)
	{
		ultrasound->IC_Val2 = HAL_TIM_ReadCapturedValue(ultrasound->timer, Channel);
		__HAL_TIM_SET_COUNTER(ultrasound->timer, 0);

		if (ultrasound->IC_Val2 > ultrasound->IC_Val1)
		{
			ultrasound->Difference = ultrasound->IC_Val2-ultrasound->IC_Val1;
		}

		else if (ultrasound->IC_Val1 > ultrasound->IC_Val2)
		{
			ultrasound->Difference = (0xffff - ultrasound->IC_Val1) + ultrasound->IC_Val2;
		}
		ultrasound->Distance = ultrasound->Difference *0.017;

		ultrasound->Is_First_Captured = 0;

		__HAL_TIM_SET_CAPTUREPOLARITY(ultrasound->timer, Channel, TIM_INPUTCHANNELPOLARITY_RISING);


		res = HCSR04_OK;
	}
	return res;
}


HCSR04_StatusTypeDef panda_HCSR04_reset(HCSR04_t* ultrasound_left, HCSR04_t* ultrasound_middle, HCSR04_t* ultrasound_right)
{
	uint8_t res = HCSR04_ERR;

	for(int i = 0; i<4; i++) HAL_GPIO_WritePin(ultrasound_left->port_trigger, ultrasound_left->pin_trigger, GPIO_PIN_SET);

	HAL_GPIO_WritePin(ultrasound_left->port_trigger, ultrasound_left->pin_trigger, GPIO_PIN_RESET);
	__HAL_TIM_ENABLE_IT(ultrasound_left->timer, TIM_IT_CC1);
	__HAL_TIM_SET_COUNTER(ultrasound_left->timer, 0);
	__HAL_TIM_ENABLE_IT(ultrasound_middle->timer, TIM_IT_CC1);
	__HAL_TIM_SET_COUNTER(ultrasound_middle->timer, 0);
	__HAL_TIM_ENABLE_IT(ultrasound_right->timer, TIM_IT_CC1);
	__HAL_TIM_SET_COUNTER(ultrasound_right->timer, 0);
	res = HCSR04_OK;

	return res;
}


uint16_t panda_HCSR04_get_distance(HCSR04_t* ultrasound){
	if(ultrasound->Is_First_Captured == 0 && ultrasound->Distance > 9){
		return ultrasound->Distance;
	}else{
		return 999;
	}
	__HAL_TIM_DISABLE_IT(ultrasound->timer, TIM_IT_CC1);
}

