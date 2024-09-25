/**
  ******************************************************************************
  * @file panda_hcsr04_driver.h
  * @brief This file contains all the functions prototypes for the panda_hcsr04_driver.c file.
  *
  * It provides an interface for interacting with the HCSR04 ultrasonic sensor module.
  *
  * It includes the necessary structures, enumerations, and function prototypes to initialize and read the HCSR04 Module.
  * It provides a convenient and structured way to retrieve information from the module.
  *
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
#ifndef INC_PANDA_HCSR04_DRIVER_H_
#define INC_PANDA_HCSR04_DRIVER_H_


#include <stdint.h>
#include "gpio.h"

#define Trigger_Pin GPIO_PIN_9
#define Trigger_GPIO_Port GPIOB


/**
 * @brief Enumeration for the HCSR04 module status.
 */
typedef enum{
	HCSR04_OK = 0, /**< OK status */
	HCSR04_ERR = 1 /**< Error status */
}HCSR04_StatusTypeDef;


/**
 * @brief Structure for the HCSR04 module data.
 */
typedef struct{
	GPIO_TypeDef* port_trigger;
	uint16_t pin_trigger;
	GPIO_TypeDef* port_echo;
	uint16_t pin_echo;
	TIM_HandleTypeDef* timer;

	uint32_t IC_Val1;
	uint32_t IC_Val2;
	uint32_t Difference;
	uint8_t Is_First_Captured;
	uint16_t Distance;
}HCSR04_t;


/**
 * @brief Initializes the HCSR04 ultrasonic sensor.
 *
 * This function initializes the HCSR04 ultrasonic sensor by setting up the timer handle, GPIO port and pin for the trigger signal. It also initializes the internal variables of the HCSR04 structure.
 *
 * @param ultrasound Pointer to the HCSR04 structure.
 * @param timer Pointer to the timer handle.
 * @param port_trigger Pointer to the GPIO port used for the trigger signal.
 * @param pin_trigger The pin number used for the trigger signal.
 * @return HCSR04_StatusTypeDef Returns HCSR04_OK after successful initialization.
 */
HCSR04_StatusTypeDef panda_HCSR04_init(HCSR04_t* ultrasound, TIM_HandleTypeDef *timer, GPIO_TypeDef* port_trigger, uint16_t pin_trigger);


/**
 * @brief Evaluates the callback from the HCSR04 ultrasonic sensor.
 *
 * This function evaluates the callback from the HCSR04 ultrasonic sensor by reading the captured values from the timer and calculating the distance based on these values.
 *
 * @param ultrasound Pointer to the HCSR04 structure.
 * @param Channel The timer channel.
 * @return HCSR04_StatusTypeDef Returns HCSR04_OK if the callback was successfully evaluated, or HCSR04_ERROR if there was an error.
 */
HCSR04_StatusTypeDef panda_HCSR04_callback_evaluations(HCSR04_t* ultrasound, uint32_t Channel);

/**
 * @brief Resets the HCSR04 ultrasonic sensors.
 *
 * This function resets the HCSR04 ultrasonic sensors by setting the trigger pin to high and then to low, and enabling the timer interrupt.
 *
 * @param ultrasound_left Pointer to the left HCSR04 structure.
 * @param ultrasound_middle Pointer to the middle HCSR04 structure.
 * @param ultrasound_right Pointer to the right HCSR04 structure.
 * @return HCSR04_StatusTypeDef Returns HCSR04_OK after successful reset.
 */
HCSR04_StatusTypeDef panda_HCSR04_reset(HCSR04_t* ultrasound_left, HCSR04_t* ultrasound_middle, HCSR04_t* ultrasound_right);

/**
 * @brief Gets the distance measured by the HCSR04 ultrasonic sensor.
 *
 * This function gets the distance measured by the HCSR04 ultrasonic sensor. If the sensor is still capturing, it returns a default value of 999.
 *
 * @param ultrasound Pointer to the HCSR04 structure.
 * @return uint16_t Returns the distance measured by the sensor, or 999 if the sensor is still capturing.
 */
uint16_t panda_HCSR04_get_distance(HCSR04_t* ultrasound);
#endif /* INC_PANDA_HCSR04_DRIVER_H_ */
