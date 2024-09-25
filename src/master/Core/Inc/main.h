/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define VERBOSE 0
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void Global_Struct_Master_Init();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Sync_Input_Pin GPIO_PIN_2
#define Sync_Input_GPIO_Port GPIOC
#define Sync_Output_Pin GPIO_PIN_3
#define Sync_Output_GPIO_Port GPIOC
#define Battery_Sensor_ADC_Pin GPIO_PIN_0
#define Battery_Sensor_ADC_GPIO_Port GPIOA
#define UltraSound3_RX_Pin GPIO_PIN_1
#define UltraSound3_RX_GPIO_Port GPIOA
#define PSX_SCK_Pin GPIO_PIN_5
#define PSX_SCK_GPIO_Port GPIOA
#define PSX_MISO_Pin GPIO_PIN_6
#define PSX_MISO_GPIO_Port GPIOA
#define PSX_MOSI_Pin GPIO_PIN_7
#define PSX_MOSI_GPIO_Port GPIOA
#define PSX_Att_Pin GPIO_PIN_8
#define PSX_Att_GPIO_Port GPIOC
#define Accelerometer_SDA_Pin GPIO_PIN_9
#define Accelerometer_SDA_GPIO_Port GPIOC
#define Accelerometer_SCL_Pin GPIO_PIN_8
#define Accelerometer_SCL_GPIO_Port GPIOA
#define UltraSound1_RX_Pin GPIO_PIN_9
#define UltraSound1_RX_GPIO_Port GPIOA
#define Turn_Off_Slave_Pin GPIO_PIN_10
#define Turn_Off_Slave_GPIO_Port GPIOC
#define UltraSound2_RX_Pin GPIO_PIN_3
#define UltraSound2_RX_GPIO_Port GPIOB
#define MotorDriver_TX_Pin GPIO_PIN_6
#define MotorDriver_TX_GPIO_Port GPIOB
#define Comunication_SDA_Pin GPIO_PIN_7
#define Comunication_SDA_GPIO_Port GPIOB
#define Comunication_SCL_Pin GPIO_PIN_8
#define Comunication_SCL_GPIO_Port GPIOB
#define Ultrasound_Trigger_Pin GPIO_PIN_9
#define Ultrasound_Trigger_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
