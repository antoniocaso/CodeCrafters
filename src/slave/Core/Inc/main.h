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

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Sync_Input_Pin GPIO_PIN_2
#define Sync_Input_GPIO_Port GPIOC
#define Encoder_POST_DX1_Pin GPIO_PIN_0
#define Encoder_POST_DX1_GPIO_Port GPIOA
#define Encoder_POST_DX2_Pin GPIO_PIN_1
#define Encoder_POST_DX2_GPIO_Port GPIOA
#define Turn_Off_Master_Pin GPIO_PIN_4
#define Turn_Off_Master_GPIO_Port GPIOC
#define MotorDriver_TX_Pin GPIO_PIN_6
#define MotorDriver_TX_GPIO_Port GPIOC
#define Encoder_ANT_DX2_Pin GPIO_PIN_7
#define Encoder_ANT_DX2_GPIO_Port GPIOC
#define Encoder_ANT_SX1_Pin GPIO_PIN_15
#define Encoder_ANT_SX1_GPIO_Port GPIOA
#define LED1___2_WHITE_Pin GPIO_PIN_10
#define LED1___2_WHITE_GPIO_Port GPIOC
#define LED_1___2_RED_Pin GPIO_PIN_12
#define LED_1___2_RED_GPIO_Port GPIOC
#define Encoder_ANT_SX2_Pin GPIO_PIN_3
#define Encoder_ANT_SX2_GPIO_Port GPIOB
#define Encoder_ANT_DX1_Pin GPIO_PIN_4
#define Encoder_ANT_DX1_GPIO_Port GPIOB
#define Encoder_POST_SX1_Pin GPIO_PIN_6
#define Encoder_POST_SX1_GPIO_Port GPIOB
#define Encoder_POST_SX2_Pin GPIO_PIN_7
#define Encoder_POST_SX2_GPIO_Port GPIOB
#define Comunication_SCL_Pin GPIO_PIN_8
#define Comunication_SCL_GPIO_Port GPIOB
#define Comunication_SDA_Pin GPIO_PIN_9
#define Comunication_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define VERBOSE 0
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
