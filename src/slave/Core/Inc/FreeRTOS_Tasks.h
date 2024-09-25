/**
  ******************************************************************************
  * @file FreeRTOS_Tasks.h
  * @brief This file contains all the functions prototypes for the FreeRTOS_Tasks.c file.
  *
  *	It provides all the slave's tasks.
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


#ifndef INC_FREERTOS_TASKS_H_
#define INC_FREERTOS_TASKS_H_



/**
 * @brief Battery Sensor task
 * @param pvParameters Parameters for the task
 */
void Battery_Sensor( void *pvParameters );


/**
 * @brief Encoder task
 * @param pvParameters Parameters for the task
 */
void Encoder( void *pvParameters );


/**
 * @brief Temperature Sensor task
 * @param pvParameters Parameters for the task
 */
void Temperature_Sensor( void *pvParameters );


/**
 * @brief Communication task
 * @param pvParameters Parameters for the task
 */
void Comunication( void *pvParameters );


/**
 * @brief Execution task
 * @param pvParameters Parameters for the task
 */
void Execution( void *pvParameters );


/**
 * @brief Initialize FreeRTOS tasks
 */
void FreeRTOS_Tasks_Init();


#endif /* INC_FREERTOS_TASKS_H_ */
