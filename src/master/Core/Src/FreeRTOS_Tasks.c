/**
  ******************************************************************************
  * @file FreeRTOS_Tasks.c
  * @brief This file contains the tasks of a real-time system using FreeRTOS.
  * The system includes several tasks that are scheduled and synchronized using FreeRTOS functionalities.
  * The tasks include Ultrasound, Check_Danger, Accelerometer, Psx, Communication, and Execution.
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
#include <panda_comunication.h>
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
#include "panda_motor_driver.h"
#include "panda_psx_controller.h"
#include "panda_hcsr04_driver.h"
#include "panda_mpu6050.h"
#include "led.h"
#include "i2c.h"

#define CRITICAL_DISTANCE 70 ///< Critical distance value. If the measured distance is less than this, the control variable is set to 1.
#define INTERMEDIATE_DISTANCE 200
#define CRITICAL_BATTERY 23 ///< Critical battery level. Used to monitor the battery status.


extern Global_Struct_t Global_Struct_Master[PANDA_STRUCT_MASTER_SIZE];
extern Global_Struct_t Global_Struct[PANDA_STRUCT_GLOBAL_SIZE];

#define LED_SX_SET Global_Struct_Master[BitVariables] | 0x01
#define LED_SX_RESET Global_Struct_Master[BitVariables] & 0xFE

#define LED_DX_SET Global_Struct_Master[BitVariables] | 0x02
#define LED_DX_RESET Global_Struct_Master[BitVariables] & 0xFD

#define LED_BOTH_WHITE_SET Global_Struct_Master[BitVariables] | 0x04
#define LED_BOTH_WHITE_RESET Global_Struct_Master[BitVariables] & 0xFB

#define LED_BOTH_RED_SET Global_Struct_Master[BitVariables] | 0x08
#define LED_BOTH_RED_RESET Global_Struct_Master[BitVariables] & 0xF7



uint8_t counter_checksum=0;
uint8_t degradato=0;


extern psx_t psx;
extern HCSR04_t ultrasound_left;
extern HCSR04_t ultrasound_middle;
extern HCSR04_t ultrasound_right;
extern MPU6050_t MPU6050;

uint16_t ultrasound_value_middle;
uint16_t ultrasound_value_left;
uint16_t ultrasound_value_right;

uint8_t attempts=0;


HAL_StatusTypeDef res=0;

osMutexId_t MutexHandle; ///< Mutex handle. Used to ensure safe access to shared resources.
const osMutexAttr_t Mutex_attributes = {
  .name = "Mutex"
};


TaskHandle_t xHandle1 = NULL; ///< Task handle for the Ultrasound task.
TaskHandle_t xHandle2 = NULL; ///< Task handle for the Check_Danger task.



void Ultrasound( void *pvParameters )
{


    #if(VERBOSE == 1)
        printf("\r\nBegin Ultrasound at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif


    panda_HCSR04_reset(&ultrasound_left, &ultrasound_middle, &ultrasound_right);
    //panda_mpu6050_read(&MPU6050);
    panda_psx_read_gamepad(&psx);

    #if(VERBOSE == 1)
        printf("Exit Ultrasound at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif


}



void Check_Danger( void *pvParameters )
{


    #if(VERBOSE == 1)
        printf("Begin Check Danger at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

	Global_Struct_Master[BitVariables] = 0x00;

    ultrasound_value_left = panda_HCSR04_get_distance(&ultrasound_left);
	Global_Struct_Master[DistanceLeft_High] = (uint8_t) ((ultrasound_value_left & 0xFF00) >> 8);
	Global_Struct_Master[DistanceLeft_Low] = (uint8_t) (ultrasound_value_left & 0x00FF);



    ultrasound_value_middle = panda_HCSR04_get_distance(&ultrasound_middle);
	Global_Struct_Master[DistanceMiddle_High] = (uint8_t) ((ultrasound_value_middle & 0xFF00) >> 8);
	Global_Struct_Master[DistanceMiddle_Low] = (uint8_t) (ultrasound_value_middle & 0x00FF);


    ultrasound_value_right = panda_HCSR04_get_distance(&ultrasound_right);
	Global_Struct_Master[DistanceRight_High] = (uint8_t) ((ultrasound_value_right & 0xFF00) >> 8);
	Global_Struct_Master[DistanceRight_Low] = (uint8_t) (ultrasound_value_right & 0x00FF);



    /*
        As previously said, checks the mutex before trying to edit the value.

        This task creates the aperiodic tasks, based on the control var value.
        This variable was set to 1 in case of critical values detected by the sensors;
        if set to 1, it directly proceeds to execution,
        otherwise, it continues normally with the "standard" control cycle.
    */
	vSchedulerAperiodicJobCreate(Psx, "Psx", NULL, pdMS_TO_TICKS( 3 ) );
	//vSchedulerAperiodicJobCreate(Accelerometer, "Accelerometer", NULL, pdMS_TO_TICKS( 1 ) ); //xSaba17:
	vSchedulerAperiodicJobCreate(Comunication, "Comunication", NULL, pdMS_TO_TICKS( 10 ) );
	vSchedulerAperiodicJobCreate(Execution, "Execution", NULL, pdMS_TO_TICKS( 7 ) );





    #if(VERBOSE == 1)
        printf("Exit Check Danger at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

}

//--------------------------APERIODICI---------------------------------


//void Accelerometer( void *pvParameters ) //xSaba17:
//{
//    #if(VERBOSE == 1)
//        printf("Begin Accelerometer at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
//    #endif
//
//
//
//
//    #if(VERBOSE == 1)
//        printf("Exit Accelerometer at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
//    #endif
//
//}



void Psx( void *pvParameters )
{
    #if(VERBOSE == 1)
        printf("Begin Psx at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

	if(panda_psx_is_on(&psx) == PSX_OK){
		if(panda_psx_get_command(&psx, TRIANGLE)){
			Global_Struct_Master[DriveSpeed] = 128;
			Global_Struct_Master[TurnSpeed] = 128;
		}else{
			if(panda_psx_is_analog(&psx)==PSX_Analog){
				Global_Struct_Master[DriveSpeed] = panda_psx_get_analog_intensity(&psx, LEFT_Y_AXIS);
				Global_Struct_Master[TurnSpeed] = panda_psx_get_analog_intensity(&psx, LEFT_X_AXIS);
			}else{
				if(degradato == 0){
					if (panda_psx_get_command(&psx, CROSS) && Global_Struct_Master[DriveSpeed] < 254){
						Global_Struct_Master[DriveSpeed] += 2;
					}
					if (panda_psx_get_command(&psx, SQUARE) && Global_Struct_Master[DriveSpeed] > 0 ){
						Global_Struct_Master[DriveSpeed] -= 2;
					}
					if (panda_psx_get_command(&psx, DPAD_LEFT) || panda_psx_get_command(&psx, DPAD_RIGHT)){
						if (panda_psx_get_command(&psx, DPAD_LEFT) && Global_Struct_Master[TurnSpeed] > 0){
							Global_Struct_Master[TurnSpeed] -= 2;
						}
						if (panda_psx_get_command(&psx, DPAD_RIGHT) && Global_Struct_Master[TurnSpeed] < 254){
							Global_Struct_Master[TurnSpeed] += 2;
						}
					}else{
						Global_Struct_Master[TurnSpeed] = 128;
					}
				}else{

					if(Global_Struct_Master[DriveSpeed] >= 191)
						Global_Struct_Master[DriveSpeed] = 191;
					if(Global_Struct_Master[TurnSpeed] >= 191)
						Global_Struct_Master[TurnSpeed] = 191;

					if(Global_Struct_Master[DriveSpeed] <= 64)
						Global_Struct_Master[DriveSpeed] = 64;
					if(Global_Struct_Master[TurnSpeed] <= 64)
						Global_Struct_Master[TurnSpeed] = 64;

					if (panda_psx_get_command(&psx, CROSS) && Global_Struct_Master[DriveSpeed] < 191){
						Global_Struct_Master[DriveSpeed] += 2;
					}
					if (panda_psx_get_command(&psx, SQUARE) && Global_Struct_Master[DriveSpeed] > 65 ){
						Global_Struct_Master[DriveSpeed] -= 2;
					}
					if (panda_psx_get_command(&psx, DPAD_LEFT) || panda_psx_get_command(&psx, DPAD_RIGHT)){
						if (panda_psx_get_command(&psx, DPAD_LEFT) && Global_Struct_Master[TurnSpeed] > 65){
							Global_Struct_Master[TurnSpeed] -= 2;
						}
						if (panda_psx_get_command(&psx, DPAD_RIGHT) && Global_Struct_Master[TurnSpeed] < 191){
							Global_Struct_Master[TurnSpeed] += 2;
						}
					}else{
						Global_Struct_Master[TurnSpeed] = 128;
					}
				}
			}
		}
		Global_Struct_Master[BitVariables] = 0;

		if(panda_psx_get_command(&psx, L1)){
			Global_Struct_Master[BitVariables] = LED_SX_SET ;
		}else{
			Global_Struct_Master[BitVariables] = LED_SX_RESET;
		}
		if(panda_psx_get_command(&psx, R1)){
			Global_Struct_Master[BitVariables] = LED_DX_SET;
		}else{
			Global_Struct_Master[BitVariables] = LED_DX_RESET;
		}
		if(panda_psx_get_command(&psx, L2)){
			Global_Struct_Master[BitVariables] = LED_BOTH_WHITE_SET;
		}else{
			Global_Struct_Master[BitVariables] = LED_BOTH_WHITE_RESET;
		}
		if(panda_psx_get_command(&psx, R2)){
			Global_Struct_Master[BitVariables] = LED_BOTH_RED_SET;
		}else{
			Global_Struct_Master[BitVariables] = LED_BOTH_RED_RESET;

		}

	}else{
		Global_Struct_Master[DriveSpeed] = 128;
		Global_Struct_Master[TurnSpeed] = 128;
	}


    #if(VERBOSE == 1)
        printf("Exit Psx at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

}


void Comunication( void *pvParameters )
{

    #if(VERBOSE == 1)
		printf("Begin Communication at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

	if(counter_checksum >= 4 ){
		degradato=1;
	}else{
		panda_exchange_struct(&hi2c1, Global_Struct_Master, Global_Struct, &counter_checksum);
	}


    #if(VERBOSE == 1)
        printf("Exit Communication at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

}


void Execution( void *pvParameters )
{
    #if(VERBOSE == 	1)
        printf("Begin Execution at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif


	if(degradato == 1){
			//Spengo Slave
		HAL_GPIO_WritePin(Turn_Off_Slave_GPIO_Port,Turn_Off_Slave_Pin, GPIO_PIN_SET);
	}

    ultrasound_value_middle = ((uint16_t)Global_Struct_Master[DistanceMiddle_High] << 8) | Global_Struct_Master[DistanceMiddle_Low];
    ultrasound_value_left = ((uint16_t)Global_Struct_Master[DistanceLeft_High] << 8) | Global_Struct_Master[DistanceLeft_Low];
    ultrasound_value_right = ((uint16_t)Global_Struct_Master[DistanceRight_High] << 8) | Global_Struct_Master[DistanceRight_Low];


    if(ultrasound_value_middle < CRITICAL_DISTANCE){
    	if(Global_Struct_Master[DriveSpeed] < 128){
    		motor_mixed_drive(&huart1, 128, Global_Struct_Master[DriveSpeed]);
			motor_mixed_drive(&huart1, 129, Global_Struct_Master[DriveSpeed]);
			motor_mixed_turn(&huart1, 128, Global_Struct_Master[TurnSpeed]);
			motor_mixed_turn(&huart1, 129, Global_Struct_Master[TurnSpeed]);
    	}else{
    		if(attempts == 0){
				motor_mixed_stop(&huart1, 128);
				motor_mixed_stop(&huart1, 129);
				Global_Struct_Master[DriveSpeed] = 128;
				Global_Struct_Master[TurnSpeed] = 128;
    		}

    		if(Global_Struct[EncoderFLSpeed] == 128 && attempts == 0) attempts=10;

			if(attempts > 0 ){
				attempts--;
				if(ultrasound_value_left < CRITICAL_DISTANCE - 50 && ultrasound_value_right > CRITICAL_DISTANCE - 50){
					motor_mixed_turn(&huart1, 128, 160);
					motor_mixed_turn(&huart1, 129, 160);
				}else if(ultrasound_value_right < CRITICAL_DISTANCE - 40 && ultrasound_value_left > CRITICAL_DISTANCE - 40){
					motor_mixed_turn(&huart1, 128, 96);
					motor_mixed_turn(&huart1, 129, 96);
				}
			}

    	}


    }else if((ultrasound_value_middle>= CRITICAL_DISTANCE && ultrasound_value_middle<= INTERMEDIATE_DISTANCE) /*|| (ultrasound_value_left>= CRITICAL_DISTANCE && ultrasound_value_left<= INTERMEDIATE_DISTANCE) || (ultrasound_value_right>= CRITICAL_DISTANCE && ultrasound_value_right <= INTERMEDIATE_DISTANCE)*/){

    	if(Global_Struct_Master[DriveSpeed] < 128){
			motor_mixed_drive(&huart1, 128, Global_Struct_Master[DriveSpeed]);
			motor_mixed_drive(&huart1, 129, Global_Struct_Master[DriveSpeed]);
			motor_mixed_turn(&huart1, 128, Global_Struct_Master[TurnSpeed]);
			motor_mixed_turn(&huart1, 129, Global_Struct_Master[TurnSpeed]);
		}else{
			uint8_t stop;
			stop = Global_Struct[EncoderFLSpeed] - 5;
			if(stop < 128) stop=128;
    		if(attempts == 0){

				motor_mixed_drive(&huart1, 128, stop);
				motor_mixed_drive(&huart1, 129, stop);
				motor_mixed_turn(&huart1, 128, 128);
				motor_mixed_turn(&huart1, 129, 128);
				Global_Struct_Master[DriveSpeed] = stop;
				Global_Struct_Master[TurnSpeed] = stop;
    		}
		}

    	if(Global_Struct[EncoderFLSpeed] == 128) attempts=10;

		if(attempts > 0 ){
			attempts--;
			if(ultrasound_value_left < INTERMEDIATE_DISTANCE - 50 && ultrasound_value_right > INTERMEDIATE_DISTANCE - 50){

				motor_mixed_turn(&huart1, 128, 160);
				motor_mixed_turn(&huart1, 129, 160);
			}else if(ultrasound_value_right < INTERMEDIATE_DISTANCE + 40 && ultrasound_value_left > INTERMEDIATE_DISTANCE + 40 ){

				motor_mixed_turn(&huart1, 128, 96);
				motor_mixed_turn(&huart1, 129, 96);
			}
		}




    }else{
    	attempts=0;
    	if(degradato == 0){
			motor_mixed_drive(&huart1, 128, Global_Struct_Master[DriveSpeed]);
			motor_mixed_drive(&huart1, 129, Global_Struct_Master[DriveSpeed]);
			motor_mixed_turn(&huart1, 128, Global_Struct_Master[TurnSpeed]);
			motor_mixed_turn(&huart1, 129, Global_Struct_Master[TurnSpeed]);
    	}else{
    		if(panda_psx_is_analog(&psx)){

				if(Global_Struct_Master[DriveSpeed] > 128){
					Global_Struct_Master[DriveSpeed] = (Global_Struct_Master[DriveSpeed] - 129) * (192 - 129) / (255 - 129) + 129;
				}else if(Global_Struct_Master[DriveSpeed] < 128 ){
					Global_Struct_Master[DriveSpeed] = (Global_Struct_Master[DriveSpeed] - 0) * (127 - 64) / (127 - 0) + 64;
				}else{
					Global_Struct_Master[DriveSpeed] = 128;
				}

				if(Global_Struct_Master[TurnSpeed] > 128){
					Global_Struct_Master[TurnSpeed] = (Global_Struct_Master[TurnSpeed] - 129) * (192 - 129) / (255 - 129) + 129;
				}else if(Global_Struct_Master[TurnSpeed] < 128 ){
					Global_Struct_Master[TurnSpeed] = (Global_Struct_Master[TurnSpeed] - 0) * (127 - 64) / (127 - 0) + 64;
				}else{
					Global_Struct_Master[TurnSpeed] = 128;
				}
    		}
    		motor_mixed_drive(&huart1, 128,  Global_Struct_Master[DriveSpeed]);
			motor_mixed_drive(&huart1, 129,  Global_Struct_Master[DriveSpeed]);
			motor_mixed_turn(&huart1, 128,   Global_Struct_Master[TurnSpeed]);
			motor_mixed_turn(&huart1, 129,   Global_Struct_Master[TurnSpeed]);
    	}
    }

//    motor_mixed_drive(&huart1, 128,  Global_Struct_Master[DriveSpeed]);
//	motor_mixed_drive(&huart1, 129,  Global_Struct_Master[DriveSpeed]);
//	motor_mixed_turn(&huart1, 128,   Global_Struct_Master[TurnSpeed]);
//	motor_mixed_turn(&huart1, 129,   Global_Struct_Master[TurnSpeed]);

    #if(VERBOSE == 1)
        printf("Exit Execution at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

}







void FreeRTOS_Tasks_Init(){


	vSchedulerPeriodicTaskCreate(Ultrasound, "Ultrasound", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle1,
	             pdMS_TO_TICKS(0),   //phase
	             pdMS_TO_TICKS(42), //period
	             pdMS_TO_TICKS(19),  //WCET
	             pdMS_TO_TICKS(19)); //Deadline
	vSchedulerPeriodicTaskCreate(Check_Danger, "Check_Danger", configMINIMAL_STACK_SIZE, NULL, 4, &xHandle2,
	             pdMS_TO_TICKS(19),  //phase
	             pdMS_TO_TICKS(42), //period
	             pdMS_TO_TICKS(2),  //WCET
	             pdMS_TO_TICKS(21)); //Deadline
	MutexHandle = osMutexNew(&Mutex_attributes);

}
