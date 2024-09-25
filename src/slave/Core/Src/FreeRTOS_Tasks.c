/**
  ******************************************************************************
  * @file FreeRTOS_Tasks.c
  * @brief This file contains the tasks of a real-time system using FreeRTOS.
  * The system includes several tasks that are scheduled and synchronized using FreeRTOS functionalities.
  * The tasks include Battery_Sensor, Encoder, Temperature_Sensor, Communication, and Execution.
  * The system uses a mutex for synchronization to ensure safe access to shared resources.
  *
  ******************************************************************************
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component. If no LICENSE file comes with this software,
  * it is provided AS-IS.
  *
  ******************************************************************************
  */
#include "FreeRTOS_Tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "scheduler.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "i2c.h"
#include "tim.h"
#include "panda_comunication.h"
#include "panda_encoder.h"
#include "panda_motor_driver.h"
#include "adc.h"



/* Define for critical values. */
#define CRITICAL_DISTANCE 70
#define CRITICAL_BATTERY 23
#define MAX_TEMPERATURE 80

/* Global struct containing all the values which define the global state of the system */
extern Global_Struct_t Global_Struct[PANDA_STRUCT_GLOBAL_SIZE];
extern Global_Struct_t Global_Struct_From_Master[PANDA_STRUCT_MASTER_SIZE];
extern Global_Struct_t Global_Struct_Slave[PANDA_STRUCT_SLAVE_SIZE];
extern encoder_t EncoderFL;
extern encoder_t EncoderFR;
extern encoder_t EncoderBL;
extern encoder_t EncoderBR;


#define LED_SX_READ Global_Struct[BitVariables] & 0x01
#define LED_DX_READ Global_Struct[BitVariables] & 0x02
#define LED_BOTH_WHITE_READ Global_Struct[BitVariables] & 0x04
#define LED_BOTH_RED_READ Global_Struct[BitVariables] & 0x08



uint8_t counter_stop_master=0;
uint8_t degradato = 0;
float temp = 0;
float rawValue=0;





TaskHandle_t xHandle1 = NULL; ///< Task handle for the Battery_Sensor task.
TaskHandle_t xHandle2 = NULL; ///< Task handle for the Encoder task.
TaskHandle_t xHandle3 = NULL; ///< Task handle for the Temperature_Sensor task.
TaskHandle_t xHandle4 = NULL; ///< Task handle for the Comunication task.
TaskHandle_t xHandle5 = NULL; ///< Task handle for the Execution task.


void Encoder( void *pvParameters )
{

    #if(VERBOSE == 1)
        printf("Begin Encoder at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

    panda_encoder_read(&EncoderFL);
    panda_encoder_read(&EncoderFR);
    panda_encoder_read(&EncoderBL);
	panda_encoder_read(&EncoderBR);

	Global_Struct_Slave[EncoderFLSpeed-(PANDA_STRUCT_MASTER_SIZE-1)] = panda_encoder_get_speed(&EncoderFL);
	Global_Struct_Slave[EncoderFRSpeed-(PANDA_STRUCT_MASTER_SIZE-1)] = panda_encoder_get_speed(&EncoderFR);
	Global_Struct_Slave[EncoderBLSpeed-(PANDA_STRUCT_MASTER_SIZE-1)] = panda_encoder_get_speed(&EncoderBL);
	Global_Struct_Slave[EncoderBRSpeed-(PANDA_STRUCT_MASTER_SIZE-1)] = panda_encoder_get_speed(&EncoderBR);

    #if(VERBOSE == 1)
        printf("Exit Encoder at %ld. Encoder Value: %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()), Global_Struct.Encoder_Steps);
    #endif


}


void Battery_Sensor( void *pvParameters )
{

    #if(VERBOSE == 1)
        printf("Begin Battery_Sensor at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif




//		HAL_ADC_PollForConversion(&hadc2, 1);
//
//		rawValue = HAL_ADC_GetValue(&hadc1);
//		float batteryPercentage = ((float)rawValue / 4095.0) * 100.0;
//		Global_Struct_Slave[BatterySensor] = (uint8_t) batteryPercentage;
//		printf("Batteria: %d\r\n", Global_Struct_Slave[BatterySensor]);

    /* Checks the mutex before trying to edit the value for the battery. */




    #if(VERBOSE == 1)
        printf("Exit Battery_Sensor at %ld. Battery Level: %d\r\n", pdMS_TO_TICKS(xTaskGetTickCount()), Global_Struct.Battery_Sensor);
    #endif


}


void Temperature_Sensor( void *pvParameters )
{
    #if(VERBOSE == 1)
        printf("Begin Temperature_Sensor at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif


	HAL_ADC_PollForConversion(&hadc1, 3);

	rawValue = HAL_ADC_GetValue(&hadc1);
	temp = (rawValue) / 4095 * 3300;
	temp = ((temp - 760.0) / 2.5) + 25;


    #if(VERBOSE == 1)
        printf("Exit Temperature_Sensor at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

}


void Comunication( void *pvParameters )
{
    #if(VERBOSE == 1)
        printf("Begin Communication at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

    counter_stop_master++;
    if(counter_stop_master >= 4){ //Stop Master
    	HAL_I2C_DisableListen_IT(&hi2c1);
    	degradato = 1;
    }else{
    	HAL_I2C_Slave_Receive_IT(&hi2c1, Global_Struct_From_Master, PANDA_STRUCT_MASTER_SIZE);
    }

	#if(VERBOSE == 1)
        printf("Exit Communication at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	uint8_t counter = 0;
	if(panda_comunication_validate_checksum(Global_Struct_From_Master) == HAL_OK){

		panda_merge_structs(Global_Struct_From_Master, Global_Struct_Slave, Global_Struct);
		panda_comunication_init_checksum(Global_Struct);
		while(counter < MAX_NUMBER_OF_ATTEMPTS && HAL_I2C_Master_Transmit(&hi2c1,(MASTER_ADDRESS<<1), Global_Struct, PANDA_STRUCT_GLOBAL_SIZE, HAL_MAX_DELAY) != HAL_OK){
			counter++;
		}
		if(counter >= MAX_NUMBER_OF_ATTEMPTS){
			counter_stop_master++;
		}else{
			counter_stop_master=0;
		}

	}else{
		Global_Struct_t Wrong[PANDA_STRUCT_GLOBAL_SIZE] = {255, 255, 255, 255, 255, 255,255, 255, 255,255, 255, 255,255, 255, 255,255, 255, 255,255, 255, 255,255, 255, 255,255, 255, 255,255, 255, 255, 255};
		while(counter < MAX_NUMBER_OF_ATTEMPTS && HAL_I2C_Master_Transmit(&hi2c1,(MASTER_ADDRESS<<1), Wrong, PANDA_STRUCT_GLOBAL_SIZE, HAL_MAX_DELAY) != HAL_OK){
			counter++;
		}
		if(counter >= MAX_NUMBER_OF_ATTEMPTS){
			counter_stop_master++;
		}else{
			counter_stop_master=0;
		}

	}

}


void Execution( void *pvParameters )
{
    #if(VERBOSE == 1)
        printf("Begin Execution at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

    uint8_t led_sx_white = LED_SX_READ;
    uint8_t led_dx_white = LED_DX_READ;
    uint8_t led_both_red = LED_BOTH_RED_READ;
    uint8_t led_both_white = LED_BOTH_WHITE_READ;


    //printf("%d - %d - %d\r\n", led_dx_white, led_both_white, led_both_red);

    if(led_dx_white > 0 || led_both_white > 0){
    	HAL_GPIO_WritePin(LED1___2_WHITE_GPIO_Port, LED1___2_WHITE_Pin, GPIO_PIN_SET);
    }else{
    	HAL_GPIO_WritePin(LED1___2_WHITE_GPIO_Port, LED1___2_WHITE_Pin, GPIO_PIN_RESET);
    }

    if(led_both_red > 0){
    	HAL_GPIO_WritePin(LED_1___2_RED_GPIO_Port, LED_1___2_RED_Pin, GPIO_PIN_SET);
    }else{
    	HAL_GPIO_WritePin(LED_1___2_RED_GPIO_Port, LED_1___2_RED_Pin, GPIO_PIN_RESET);
    }



    if(degradato == 1 || temp > MAX_TEMPERATURE){
    	//CODICE Spengo master
        //printf("SLAVE DEGRADATO\r\n");
    	HAL_GPIO_WritePin(Turn_Off_Master_GPIO_Port, Turn_Off_Master_Pin, GPIO_PIN_SET);
		motor_mixed_stop(&huart6, 128);
		motor_mixed_stop(&huart6, 129);
		//CODICE Spengo slave
    }




    #if(VERBOSE == 1)
        printf("Exit Execution at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

}


void FreeRTOS_Tasks_Init(){


    /*
        Creation of both periodic tasks, Ultrasound and Check_Danger.
        Check the doc for more details.
    */
    vSchedulerPeriodicTaskCreate(Encoder, "Encoder", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle2,
            pdMS_TO_TICKS(0),   //phase
            pdMS_TO_TICKS(42), //period
            pdMS_TO_TICKS(10),  //WCET
            pdMS_TO_TICKS(20)); //Deadline
    vSchedulerPeriodicTaskCreate(Battery_Sensor, "Battery_Sensor", configMINIMAL_STACK_SIZE, NULL, 2, &xHandle1,
            pdMS_TO_TICKS(10),  //phase
            pdMS_TO_TICKS(42), //period
            pdMS_TO_TICKS(2),  //WCET
            pdMS_TO_TICKS(20)); //Deadline
    vSchedulerPeriodicTaskCreate(Temperature_Sensor, "Temperature_Sensor", configMINIMAL_STACK_SIZE, NULL, 3, &xHandle3,
            pdMS_TO_TICKS(10),  //phase
            pdMS_TO_TICKS(42), //period
            pdMS_TO_TICKS(8),  //WCET
            pdMS_TO_TICKS(20)); //Deadline
    vSchedulerPeriodicTaskCreate(Comunication, "Comunication", configMINIMAL_STACK_SIZE, NULL, 4, &xHandle4,
            pdMS_TO_TICKS(20),  //phase
            pdMS_TO_TICKS(42), //period
            pdMS_TO_TICKS(2),  //WCET
            pdMS_TO_TICKS(22));//Deadline
    vSchedulerPeriodicTaskCreate(Execution, "Execution", configMINIMAL_STACK_SIZE, NULL, 5, &xHandle5,
            pdMS_TO_TICKS(34), //phase
            pdMS_TO_TICKS(42), //period
            pdMS_TO_TICKS(8),  //WCET
            pdMS_TO_TICKS(42));//Deadline

    /* Initializes the mutex */

}
