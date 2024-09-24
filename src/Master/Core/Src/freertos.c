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


/*Define for critical values*/
#define CRITICAL_DISTANCE 70
#define CRITICAL_BATTERY 23

/*Set this to 1 to print the ms of input and output for each task.*/
#define VERBOSE 1


void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

TaskHandle_t xHandle1 = NULL;
TaskHandle_t xHandle2 = NULL;
TaskHandle_t xHandle3 = NULL;
TaskHandle_t xHandle4 = NULL;

/* Task declaration */
static void Psx( void *pvParameters );
static void Accelerometer( void *pvParameters );
static void Communication( void *pvParameters );
static void Execution( void *pvParameters );

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



/* Mutex used for checking the accessing of the Control_Var attribute of the Global Struct */
osMutexId_t MutexHandle;
const osMutexAttr_t Mutex_attributes = {
  .name = "Mutex"
};


static void Ultrasound( void *pvParameters )
{


    #if(VERBOSE == 1)
        printf("Begin Ultrasound at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif


    /*
        The value 60.010 is chosen because of the Ultrasound's behavior: it needs to wait
        60 ms in order to receive the echo signal and 10 microseconds because of putting
        down the trigger from 1 to 0
    */
    HAL_Delay(60.010);

    /*
        Randomly chooses the distance of the obstacle, according to the
        value of the tick count, if even or odd.
    */
    if(pdMS_TO_TICKS(xTaskGetTickCount()) % 2 == 0)
        Global_Struct.Distance = 80;
    else
        Global_Struct.Distance = 60;


    /*
        As previously said, checks the mutex before trying to edit the value.
    */
    osMutexAcquire(MutexHandle, osWaitForever);
    if(Global_Struct.Distance < CRITICAL_DISTANCE)
        Global_Struct.Control_Var = 1;
    osMutexRelease(MutexHandle);




    #if(VERBOSE == 1)
        printf("Exit Ultrasound at %ld. Distance Value: %f\r\n", pdMS_TO_TICKS(xTaskGetTickCount()), Global_Struct.Distance);
    #endif


}



static void Check_Danger( void *pvParameters )
{


    #if(VERBOSE == 1)
        printf("Begin Check Danger at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif


    /*
        As previously said, checks the mutex before trying to edit the value.

        This task creates the aperiodic tasks, based on the control var value.
        This variable was set to 1 in case of critical values detected by the sensors;
        if set to 1, it directly proceeds to execution,
        otherwise, it continues normally with the "standard" control cycle.
    */
    osMutexAcquire(MutexHandle, osWaitForever);
    if(Global_Struct.Control_Var == 0){
        vSchedulerAperiodicJobCreate(Psx, "Psx", NULL, pdMS_TO_TICKS( 10 ) );
        vSchedulerAperiodicJobCreate(Accelerometer, "Accelerometer", NULL, pdMS_TO_TICKS( 10 ) );
        vSchedulerAperiodicJobCreate(Communication, "Communication", NULL, pdMS_TO_TICKS(30 ) );
        vSchedulerAperiodicJobCreate(Execution, "Execution", NULL, pdMS_TO_TICKS(10 ) );
    }
    else{
        vSchedulerAperiodicJobCreate(Execution, "Execution", NULL, pdMS_TO_TICKS(10 ) );
    }
    osMutexRelease(MutexHandle);



    #if(VERBOSE == 1)
        printf("Exit Check Danger at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

}

//--------------------------APERIODICI---------------------------------


static void Accelerometer( void *pvParameters )
{
    #if(VERBOSE == 1)
        printf("Begin Accelerometer at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif


    /* Dummy value for the accelerometer. */
    Global_Struct.Accelerometer = 10;


    #if(VERBOSE == 1)
        printf("Exit Accelerometer at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

}



static void Psx( void *pvParameters )
{
    #if(VERBOSE == 1)
        printf("Begin Psx at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
    #endif

    /*
        Delay used to express the spi comunication between controller and stm
        The result comes from the following formula: Number_Of_Bits/SPI_Frequency = 72/62.500
    */
    HAL_Delay(1.5);

    /* Dummy value for the PSX Controller. */

    Global_Struct.PSX[0]=255;
    Global_Struct.PSX[1]=255;
    Global_Struct.PSX[2]=255;
    Global_Struct.PSX[3]=255;
    Global_Struct.PSX[4]=1;
    Global_Struct.PSX[5]=255;
    Global_Struct.PSX[6]=255;
    Global_Struct.PSX[7]=255;
    Global_Struct.PSX[8]=255;


    #if(VERBOSE == 1)
        printf("Exit Psx at %ld\r\n", pdMS_TO_TICKS(xTaskGetTickCount()));
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

        In case of normal drive (0):
            the rover drives the leds based on the user directive,
            sets the speed according to the value on the analog of the PSX Controller.
    */

    if(Global_Struct.Control_Var == 1){         //Emergency Stop
        int8_t led = 1;
        int64_t velocita = 0;
        Global_Struct.Control_Var = 0;
    }else{                                      //Normal drive
        int8_t led = Global_Struct.PSX[4];      //Suppose that in PSX[4] there is the value that represents the on/off of the led
        int64_t velocita = Global_Struct.PSX[6];//Suppose that in PSX[6] there is the velocity of the rover given from the controller
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
    vSchedulerPeriodicTaskCreate(Ultrasound, "Ultrasound", configMINIMAL_STACK_SIZE, NULL, 1, &xHandle1,
            pdMS_TO_TICKS(0),   //phase
            pdMS_TO_TICKS(160), //period
            pdMS_TO_TICKS(70),  //WCET
            pdMS_TO_TICKS(70)); //Deadline
    vSchedulerPeriodicTaskCreate(Check_Danger, "Check_Danger", configMINIMAL_STACK_SIZE, NULL, 4, &xHandle4,
            pdMS_TO_TICKS(70),  //phase
            pdMS_TO_TICKS(160), //period
            pdMS_TO_TICKS(10),  //WCET
            pdMS_TO_TICKS(80)); //Deadline

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
