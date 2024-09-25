/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "panda_psx_controller.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "math.h"
#include <errno.h>
#include <sys/unistd.h>
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SATURATE(x, min, max) ((x) < (min) ? (min) : ((x) > (max) ? (max) : (x)))

#define WAITING 0.180

#define ASX 0
#define ADX 1
#define PSX 2
#define PDX 3

#define FRONT_AXIS_SYNC 0
#define REAR_AXIS_SYNC 1

#define GAIN 0.9

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


double lastTicks[4] = {0,0,0,0};
double currentTicks[4] = {0,0,0,0};

double speed[4] = {0,0,0,0};
double speed_last[4] = {0,0,0,0};
double speed_filtered[4] = {0,0,0,0};
double speed_filtered_last[4] = {0,0,0,0};

double uZQGamma[4] = {0,0,0,0};
double eZQGamma[4] = {0,0,0,0};
double eZQGamma_last[4] = {0,0,0,0};

double uSat[4] = {0,0,0,0};

double uAntiWind[4] = {0,0,0,0};

//Sync
double uZQGamma_Sync[2] = {0,0};
double eZQGamma_Sync[2] = {0,0};
double eZQGamma_Sync_last[2] = {0,0};

double uSat_Sync[2] = {0,0};

double uAntiWind_Sync[2] = {0,0};


double y_Sync[2] = {0,0};
//End Sync

double y[4] = {0,0,0,0};

uint32_t ticControlStep;
uint32_t tocControlStep;
uint32_t controlComputationDuration;
uint32_t startTick, endTick;

double Ts = 0.045;
double referenceVals[34] = {0, 200, 150, 130, 120, 100, 20, 19, 18, 17, 16, 15, 0, 30, -30, 100, -70, 0, -150, -150, 0, -200, 0, -130, 0, -100, 0, -50, 0, -30, 70, -20, 120, 100};
double referenceVal = 0;
int referenceIndex = 0;
uint32_t k_controller = -1;

psx_t psx;


int cycleduration;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
typedef struct circular_buffer {
	void *buffer;     // data buffer
	void *buffer_end; // end of data buffer
	size_t capacity;  // maximum number of items in the buffer
	size_t count;     // number of items in the buffer
	size_t sz;        // size of each item in the buffer
	void *head;       // pointer to head
	void *tail;       // pointer to tail
	bool writing;  // signals if the buffer is being written
} circular_buffer;

void cb_init(circular_buffer *cb, size_t capacity, size_t sz) {
	cb->buffer = calloc(capacity, sz);
	if (cb->buffer == NULL)
		printf("ALLOCATED NULL\n\r");
	// handle error
	cb->buffer_end = (char*) cb->buffer + capacity * sz;
	cb->capacity = capacity;
	cb->count = 0;
	cb->sz = sz;
	cb->head = cb->buffer;
	cb->tail = cb->buffer;
	cb->writing = false;

}

void cb_free(circular_buffer *cb) {
	free(cb->buffer);
	// clear out other fields too, just to be safe
}

void cb_push_back(circular_buffer *cb, const void *item) {
	if (cb->count == cb->capacity) {
		printf("ERROR PUSH BACK \n\r");
		// handle error
	}
	cb->writing = true;
	memmove(cb->head, item, cb->sz);
	cb->head = (char*) cb->head + cb->sz;
	if (cb->head == cb->buffer_end)
		cb->head = cb->buffer;
	cb->count++;
	cb->writing = false;
}

void cb_pop_front(circular_buffer *cb, void *item) {
	if (cb->count == 0) {
		printf("ERROR PUSH BACK \n\r");
		// handle error
	}
	memmove(item, cb->tail, cb->sz);
	cb->tail = (char*) cb->tail + cb->sz;
	if (cb->tail == cb->buffer_end)
		cb->tail = cb->buffer;
	while ((cb->writing))
		;
	cb->count--;
}

circular_buffer myBuff;

/* BEGIN RECORD TYPEDEF*/
typedef struct record {
	double current_u[4]; // value of the current controller output
	double current_y[4]; // value of the current motor output (speed)
	uint32_t cycleCoreDuration; // time needed to read, compute and actuate
	uint32_t cycleBeginDelay; // difference between the actual and the expected absolute start time of the cycle
	uint32_t currentTimestamp; // current timestamp in millis
} record;

int _write(int file, char *data, int len) {
	if ((file != STDOUT_FILENO) && (file != STDERR_FILENO)) {
		errno = EBADF;
		return -1;
	}

	// arbitrary timeout 1000
	HAL_StatusTypeDef status = HAL_UART_Transmit(&huart2, (uint8_t*) data, len,
			1000);

	// return # of bytes written - as best we can tell
	return (status == HAL_OK ? len : 0);
}

void setPulseFromDutyValue(TIM_HandleTypeDef *htim, uint32_t Channel, double dutyVal) {
	__HAL_TIM_SET_COMPARE(htim, Channel,
			(abs(dutyVal) * ((double )htim->Init.Period)) / 100); //cast integer value to double to correctly perform division between decimal numbers
}

double getSpeedByDelta(double ticksDelta, double Ts) {
	return ticksDelta * 60 / (2448 * Ts);
}

double getTicksDelta(double currentTicks, double lastTicks, double Ts, uint8_t power) {
	double delta;

	if (abs(currentTicks - lastTicks) <= ceil(7630 * Ts))
		delta = currentTicks - lastTicks;

	else {
		if (lastTicks > currentTicks)
			delta = currentTicks + pow(2, power) - 1 - lastTicks;
		else
			delta = currentTicks - pow(2, power) + 1 - lastTicks;
	}

	return delta;
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim == &htim11) {
		k_controller = k_controller + 1;
		if (k_controller == 0) {
			ticControlStep = HAL_GetTick();
		}

		tocControlStep = HAL_GetTick();
		//printf("%d\r\n", tocControlStep);
		//printf("%f, %f\r\n", currentTicks[PDX], lastTicks[PDX]);
		currentTicks[ASX] = (double) __HAL_TIM_GET_COUNTER(&htim2);
		currentTicks[ADX] = (double) __HAL_TIM_GET_COUNTER(&htim3);
		currentTicks[PSX] = (double) __HAL_TIM_GET_COUNTER(&htim4);
		currentTicks[PDX] = (double) __HAL_TIM_GET_COUNTER(&htim5);
		speed[ASX] = getSpeedByDelta(
						getTicksDelta(currentTicks[ASX], lastTicks[ASX], Ts, 16), Ts);
		speed[ADX] = getSpeedByDelta(
						getTicksDelta(currentTicks[ADX], lastTicks[ADX], Ts, 16), Ts);
		speed[PSX] = getSpeedByDelta(
						getTicksDelta(currentTicks[PSX], lastTicks[PSX], Ts, 16), Ts);
		speed[PDX] = getSpeedByDelta(
						getTicksDelta(currentTicks[PDX], lastTicks[PDX], Ts, 16), Ts);

		speed_filtered[ASX] = 0.1837 * speed[ASX] + 0.1837 * speed_last[ASX] + 0.6327 * speed_filtered_last[ASX];
		speed_filtered[ADX] = 0.1837 * speed[ADX] + 0.1837 * speed_last[ADX] + 0.6327 * speed_filtered_last[ADX];
		speed_filtered[PSX] = 0.1837 * speed[PSX] + 0.1837 * speed_last[PSX] + 0.6327 * speed_filtered_last[PSX];
		speed_filtered[PDX] = 0.1837 * speed[PDX] + 0.1837 * speed_last[PDX] + 0.6327 * speed_filtered_last[PDX];


		panda_psx_read_gamepad(&psx);
		referenceVal = (double)((panda_psx_get_analog_intensity(&psx, LEFT_Y_AXIS) -128) * 1.17);
		//printf("ref %.2f -  %.2f, %.2f, %.2f, %.2f\r\n", referenceVal, speed_filtered[ASX], speed_filtered[ADX], speed_filtered[PSX], speed_filtered[PDX]);

		eZQGamma[ASX] = referenceVal - speed_filtered[ASX];
		eZQGamma[ADX] = referenceVal - speed_filtered[ADX];
		eZQGamma[PSX] = referenceVal - speed_filtered[PSX];
		eZQGamma[PDX] = referenceVal - speed_filtered[PDX];

		uZQGamma[ASX] = GAIN * (0.08400 * eZQGamma[ASX] - 0.06600 * eZQGamma_last[ASX]);
		uZQGamma[ADX] = GAIN * (0.08367 * eZQGamma[ADX] - 0.06567 * eZQGamma_last[ADX]);
		uZQGamma[PSX] = GAIN * (0.08674 * eZQGamma[PSX] - 0.06874 * eZQGamma_last[PSX]);
		uZQGamma[PDX] = GAIN * (0.08422 * eZQGamma[PDX] - 0.06622 * eZQGamma_last[PDX]);


		uSat[ASX] = SATURATE(uZQGamma[ASX] + uAntiWind[ASX], -12, 12);
		uSat[ADX] = SATURATE(uZQGamma[ADX] + uAntiWind[ADX], -12, 12);
		uSat[PSX] = SATURATE(uZQGamma[PSX] + uAntiWind[PSX], -12, 12);
		uSat[PDX] = SATURATE(uZQGamma[PDX] + uAntiWind[PDX], -12, 12);

		eZQGamma_Sync[FRONT_AXIS_SYNC] = speed_filtered[ASX] - speed_filtered[ADX];
		eZQGamma_Sync[REAR_AXIS_SYNC] = speed_filtered[PSX] - speed_filtered[PDX];

		uZQGamma_Sync[FRONT_AXIS_SYNC] =  GAIN * ( 0.08400 * eZQGamma_Sync[FRONT_AXIS_SYNC] - 0.06600 * eZQGamma_Sync_last[FRONT_AXIS_SYNC]);
		uZQGamma_Sync[REAR_AXIS_SYNC] =  GAIN * ( 0.08674 * eZQGamma_Sync[REAR_AXIS_SYNC] - 0.06874 * eZQGamma_Sync_last[REAR_AXIS_SYNC]);

		uSat_Sync[FRONT_AXIS_SYNC] = SATURATE(uZQGamma_Sync[FRONT_AXIS_SYNC] + uAntiWind_Sync[FRONT_AXIS_SYNC], -12, 12);
		uSat_Sync[REAR_AXIS_SYNC] = SATURATE(uZQGamma_Sync[REAR_AXIS_SYNC] + uAntiWind_Sync[REAR_AXIS_SYNC], -12, 12);

		y[ASX] = SATURATE(uSat[ASX] - uSat_Sync[FRONT_AXIS_SYNC], -12, 12);
		y[PSX] = SATURATE(uSat[PSX] - uSat_Sync[REAR_AXIS_SYNC], -12, 12);

		setPulseFromDutyValue(&htim1, TIM_CHANNEL_1, y[ASX]    * 1.5 + 75.2);
	    setPulseFromDutyValue(&htim1, TIM_CHANNEL_2, uSat[ADX] * 1.5 + 75.2);
	    setPulseFromDutyValue(&htim1, TIM_CHANNEL_3, y[PSX]    * 1.5 + 75.2);
	    setPulseFromDutyValue(&htim1, TIM_CHANNEL_4, uSat[PDX] * 1.5 + 75.2);


	    uAntiWind[ASX] = uSat[ASX];
		uAntiWind[ADX] = uSat[ADX];
		uAntiWind[PSX] = uSat[PSX];
		uAntiWind[PDX] = uSat[PDX];

	    eZQGamma_last[ASX] = eZQGamma[ASX];
		eZQGamma_last[ADX] = eZQGamma[ADX];
		eZQGamma_last[PSX] = eZQGamma[PSX];
		eZQGamma_last[PDX] = eZQGamma[PDX];

		speed_last[ASX] = speed[ASX];
		speed_last[ADX] = speed[ADX];
		speed_last[PSX] = speed[PSX];
		speed_last[PDX] = speed[PDX];

		speed_filtered_last[ASX] = speed_filtered[ASX];
		speed_filtered_last[ADX] = speed_filtered[ADX];
		speed_filtered_last[PSX] = speed_filtered[PSX];
		speed_filtered_last[PDX] = speed_filtered[PDX];

		eZQGamma_Sync_last[FRONT_AXIS_SYNC] = eZQGamma_Sync[FRONT_AXIS_SYNC];
		eZQGamma_Sync_last[REAR_AXIS_SYNC] = eZQGamma_Sync[REAR_AXIS_SYNC];
		uAntiWind_Sync[FRONT_AXIS_SYNC] = uSat_Sync[FRONT_AXIS_SYNC];
		uAntiWind_Sync[REAR_AXIS_SYNC] = uSat_Sync[REAR_AXIS_SYNC];

		controlComputationDuration = HAL_GetTick() - tocControlStep;

		lastTicks[ASX] = currentTicks[ASX];
		lastTicks[ADX] = currentTicks[ADX];
		lastTicks[PSX] = currentTicks[PSX];
		lastTicks[PDX] = currentTicks[PDX];

		record r;
		r.current_u[ASX] = y[ASX];
		r.current_u[ADX] = uSat[ADX];
		r.current_u[PSX] = y[PSX];
		r.current_u[PDX] = uSat[PDX];

		r.current_y[ASX] = speed_filtered[ASX];
		r.current_y[ADX] = speed_filtered[ADX];
		r.current_y[PSX] = speed_filtered[PSX];
		r.current_y[PDX] = speed_filtered[PDX];
		r.cycleCoreDuration = controlComputationDuration;
		r.cycleBeginDelay = tocControlStep - ticControlStep
				- (k_controller * Ts * 1000);
		r.currentTimestamp = HAL_GetTick();

		cb_push_back(&myBuff, &r);



	}
}




/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_TIM1_Init();
  setPulseFromDutyValue(&htim1, TIM_CHANNEL_1, 75.2);
  setPulseFromDutyValue(&htim1, TIM_CHANNEL_2, 75.2);
  setPulseFromDutyValue(&htim1, TIM_CHANNEL_3, 75.2);
  setPulseFromDutyValue(&htim1, TIM_CHANNEL_4, 75.2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
  MX_GPIO_Init();
  MX_TIM11_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_SPI3_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Start(&htim3);
  HAL_TIM_Base_Start(&htim4);
  HAL_TIM_Base_Start(&htim5);

  size_t bufferSize = (size_t)ceil(2 * WAITING / Ts);
  cb_init(&myBuff, bufferSize, sizeof(record));


  HAL_Delay(1000);

  panda_psx_init(&psx, &hspi3, PSX_ATT_GPIO_Port, PSX_ATT_Pin);
  HAL_TIM_Base_Start_IT(&htim11);
  printf("INIT\n\r"); // initialize the Matlab tool for COM data acquiring

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	size_t nEntriesToSend = myBuff.count; //number of samples not read yet
	record retrieved; //buffer entry

	for (size_t count = 0; count < nEntriesToSend; count++) {
		cb_pop_front(&myBuff, &retrieved); //take entry from the buffer
		printf("T{%lu}, CycleT{%lu}, ASX{%.3f, %.3f} ADX{%.3f, %.3f} PSX{%.3f, %.3f} PDX{%.3f, %.3f}\n\r",
		retrieved.currentTimestamp, retrieved.cycleCoreDuration, retrieved.current_u[ASX], retrieved.current_y[ASX],
		retrieved.current_u[ADX], retrieved.current_y[ADX], retrieved.current_u[PSX], retrieved.current_y[PSX],
		retrieved.current_u[PDX], retrieved.current_y[PDX]
			); // send values via USART using format: value1, value2, value3, ... valuen \n \r
	}

	HAL_Delay(WAITING*1000); // takes a time value in ms


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
