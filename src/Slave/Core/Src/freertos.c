/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "scheduler.h"
#include "usart.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


/* Define for critical values. */
#define CRITICAL_DISTANCE 70
#define CRITICAL_BATTERY 23
/* Set this to 1 to print the ms of input and output for each task. */

#define VERBOSE 1


void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;
TaskHandle_t xHandle3 = NULL;
TaskHandle_t xHandle4 = NULL;
TaskHandle_t xHandle5 = NULL;





/* Global struct containing all the values which define the global state of the system */
struct Struct_s{

    float Distance;
    int64_t Encoder_PastReading;
    int64_t Encoder_Steps;
    int16_t Battery_Sensor;
    int16_t PSX[9];
    int16_t Accelerometer;
    int16_t Temperature_Sensor;
    int8_t Control_Var;
};

typedef struct Struct_s Struct_t;
Struct_t Global_Struct;



/*
    Mutex used for checking the accessing of the Control_Var
    and Battery_Sensor attributes of the Global Struct
*/
osMutexId_t MutexHandle;
const osMutexAttr_t Mutex_attributes = {
  .name = "Mutex"
};



static void Battery_Sensor( void *pvParameters )
{

    #if(VERBOSE == 1)
        printf("Begin Battery_Sensor at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif


    /* Dummy value for the battery. */
    if(Global_Struct.Battery_Sensor > 0)
        Global_Struct.Battery_Sensor = Global_Struct.Battery_Sensor - 1 ;

    /* Checks the mutex before trying to edit the value for the battery. */
    osMutexAcquire(MutexHandle, osWaitForever);
    if(Global_Struct.Battery_Sensor < CRITICAL_BATTERY){
            Global_Struct.Battery_Sensor = 100;
    }
    osMutexRelease(MutexHandle);



    #if(VERBOSE == 1)
        printf("Exit Battery_Sensor at %ld. Battery Level: %d\r\n", pdMS_TO_TICKS(xTaskGetTickCount()), Global_Struct.Battery_Sensor);
    #endif


}



static void Encoder( void *pvParameters )
{

    #if(VERBOSE == 1)
        printf("Begin Encoder at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif


    /* Dummy value for the encoder. */
    int64_t lectura=1000;
    Global_Struct.Encoder_Steps = lectura - Global_Struct.Encoder_PastReading;
    Global_Struct.Encoder_PastReading = lectura;




    #if(VERBOSE == 1)
        printf("Exit Encoder at %ld. Encoder Value: %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()), Global_Struct.Encoder_Steps);
    #endif


}




static void Temperature_Sensor( void *pvParameters )
{
    #if(VERBOSE == 1)
        printf("Begin Temperature_Sensor at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif


    /* Dummy value for temperature sensor. */
    Global_Struct.Temperature_Sensor = 30;



    #if(VERBOSE == 1)
        printf("Exit Temperature_Sensor at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

}






static void Communication( void *pvParameters )
{
    #if(VERBOSE == 1)
        printf("Begin Communication at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif


    /*
        This delay is bigger than the normal comunication but we've considered some errors
        during the communication.
    */
    HAL_Delay(20);

    /*
        Dummy condition which sets 0 or 1 to the control_var, based on the tick count,
        if it's even or odd.
    */
    if(pdMS_TO_TICKS(xTaskGetTickCount()) % 2 == 0)
        Global_Struct.Control_Var = 0;
    else
        Global_Struct.Control_Var = 1;



    #if(VERBOSE == 1)
        printf("Exit Communication at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

}


static void Execution( void *pvParameters )
{
    #if(VERBOSE == 1)
        printf("Begin Execution at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif


    /*
        This is where the magic happens. Based on the control_var, the execution
        is different.

        In case of emergency stop (1):
            the rover turns on the leds for visibility purposes,
            sets the speed to 0,
            resets the control_var back to 0.
    */

    if(Global_Struct.Control_Var == 1){         //Emergency Stop
        int8_t led = 1;
        int64_t velocita = 0;
        Global_Struct.Control_Var = 0;
    }


    #if(VERBOSE == 1)
        printf("Exit Execution at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

}




/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
    vSchedulerInit();

    printf("------------Hello From FreeRTOS------------\r\n");


    vSchedulerInit();


    /*
        Creation of both periodic tasks, Ultrasound and Check_Danger.
        Check the doc for more details.
    */
    vSchedulerPeriodicTaskCreate(Encoder, "Encoder", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle2,
            pdMS_TO_TICKS(0),   //phase
            pdMS_TO_TICKS(160), //period
            pdMS_TO_TICKS(10),  //WCET
            pdMS_TO_TICKS(30)); //Deadline
    vSchedulerPeriodicTaskCreate(Battery_Sensor, "Battery_Sensor", configMINIMAL_STACK_SIZE, NULL, 2, &xHandle1,
            pdMS_TO_TICKS(10),  //phase
            pdMS_TO_TICKS(160), //period
            pdMS_TO_TICKS(10),  //WCET
            pdMS_TO_TICKS(30)); //Deadline

    vSchedulerPeriodicTaskCreate(Temperature_Sensor, "Temperature_Sensor", configMINIMAL_STACK_SIZE, NULL, 3, &xHandle3,
            pdMS_TO_TICKS(10),  //phase
            pdMS_TO_TICKS(160), //period
            pdMS_TO_TICKS(10),  //WCET
            pdMS_TO_TICKS(30)); //Deadline

    vSchedulerPeriodicTaskCreate(Communication, "Communication", configMINIMAL_STACK_SIZE, NULL, 4, &xHandle4,
            pdMS_TO_TICKS(80),  //phase
            pdMS_TO_TICKS(160), //period
            pdMS_TO_TICKS(50),  //WCET
            pdMS_TO_TICKS(130));//Deadline
    vSchedulerPeriodicTaskCreate(Execution, "Execution", configMINIMAL_STACK_SIZE, NULL, 5, &xHandle5,
            pdMS_TO_TICKS(130), //phase
            pdMS_TO_TICKS(160), //period
            pdMS_TO_TICKS(10),  //WCET
            pdMS_TO_TICKS(140));//Deadline

    /* Global struct initialization. */
    Global_Struct.Distance = 0;
    Global_Struct.Encoder_PastReading = 0;
    Global_Struct.Encoder_Steps = 0;
    Global_Struct.Battery_Sensor = 100;
    Global_Struct.PSX[0] = 0;
    Global_Struct.PSX[1] = 0;
    Global_Struct.PSX[2] = 0;
    Global_Struct.PSX[3] = 0;
    Global_Struct.PSX[4] = 0;
    Global_Struct.PSX[5] = 0;
    Global_Struct.PSX[6] = 0;
    Global_Struct.PSX[7] = 0;
    Global_Struct.PSX[8] = 0;
    Global_Struct.Accelerometer = 0;
    Global_Struct.Temperature_Sensor = 0;
    Global_Struct.Control_Var = 0;

    /* Initializes the mutex */
    MutexHandle = osMutexNew(&Mutex_attributes);

}
