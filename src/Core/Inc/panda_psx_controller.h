/**
  ******************************************************************************
  * @file panda_psx_controller.h
  * @brief This file contains all the functions prototypes for the panda_psx_controller.c file.
  *
  *	It provides an interface for interacting with a PSX (PlayStation) controller.
  *
  *	It includes the necessary structures, enumerations, and function prototypes
  *	to initialize and control the PSX controller.
  *
  *	It provides a convenient and structured way to control and retrieve information
  *	from the controller.
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
#ifndef INC_PANDA_PSX_CONTROLLER_H_
#define INC_PANDA_PSX_CONTROLLER_H_

#include "spi.h"
#include "gpio.h"
#include <stdio.h>
#include "usart.h"


/**
 * @brief Enumeration for the PSX controller status.
 */
typedef enum
{
  PSX_OK       = 0, /**< OK status */
  PSX_ERROR    = -1 /**< Error status */
} PSX_StatusTypeDef;


/**
 * @brief Enumeration for the analog/digital mode.
 */
typedef enum
{
	PSX_Analog = 1,
	PSX_Digital = 0
} PSX_Mode;


/**
 * @brief Structure for the PSX controller.
 */
typedef struct{
	SPI_HandleTypeDef* spi; /**< Pointer to the SPI structure */
	GPIO_TypeDef* gpio_att_port; /**< GPIO port */
	uint16_t gpio_att_pin; /**< GPIO pin */
	uint8_t RX[9]; /**< Reception array */
}psx_t;


/**
 * @brief Enumeration for the PSX controller buttons.
 */
typedef enum
{
  SELECT = 24, /**< Select button */
  L3_PUSH = 25, /**< L3 Push button */
  R3_PUSH = 26, /**< R3 Push button */
  START = 27, /**< Start button */
  DPAD_UP = 28, /**< D-pad up */
  DPAD_RIGHT = 29, /**< D-pad right */
  DPAD_DOWN = 30, /**< D-pad down */
  DPAD_LEFT = 31, /**< D-pad left */
  L2 = 32, /**< L2 button */
  R2 = 33, /**< R2 button */
  L1 = 34, /**< L1 button */
  R1 = 35, /**< R1 button */
  TRIANGLE = 36, /**< Triangle button */
  CIRCLE = 37, /**< Circle button */
  CROSS = 38, /**< Cross button */
  SQUARE = 39 /**< Square button */
} PSX_ButtonsTypeDef;


/**
 * @brief Enumeration for the PSX controller analogs.
 */
typedef enum
{
  LEFT_X_AXIS = 7, /**< Left X-axis */
  LEFT_Y_AXIS = 8, /**< Left Y-axis */
  RIGHT_X_AXIS = 5, /**< Right X-axis */
  RIGHT_Y_AXIS = 6 /**< Right Y-axis */
} PSX_AnalogTypeDef;



/**
 * @brief Initializes the PSX controller.
 *
 * This function initializes the PSX controller by setting up the SPI handle and the GPIO port and pin for the ATT (attention) signal. It also sets the ATT pin to high.
 *
 * @param psx Pointer to the PSX controller structure.
 * @param spi Pointer to the SPI handle.
 * @param gpio_att_port Pointer to the GPIO port used for the ATT signal.
 * @param gpio_att_pin The pin number used for the ATT signal.
 * @return PSX_StatusTypeDef Returns PSX_OK after successful initialization.
 */
PSX_StatusTypeDef panda_psx_init(psx_t* psx, SPI_HandleTypeDef* spi, GPIO_TypeDef* gpio_att_port, uint16_t gpio_att_pin);


/**
 * @brief Reads data from the PSX controller.
 *
 * This function reads data from the PSX controller by sending a command via SPI and receiving the response. The ATT signal is toggled before and after the SPI transmission.
 *
 * @param psx Pointer to the PSX controller structure.
 * @return PSX_StatusTypeDef Returns PSX_OK if the data was successfully read, or PSX_ERROR if there was an error.
 */
PSX_StatusTypeDef panda_psx_read_gamepad(psx_t* psx);


/**
 * @brief Prints the received data from the PSX controller for debugging purposes.
 *
 * This function prints the received data from the PSX controller in either hexadecimal or decimal format, depending on the mode parameter.
 *
 * @param psx Pointer to the PSX controller structure.
 * @param mode The print mode (0 for hexadecimal, 1 for decimal).
 */
void panda_psx_debug_print(psx_t* psx, int mode);


/**
 * @brief Gets the state of a specific button on the PSX controller.
 *
 * This function gets the state of a specific button on the PSX controller by checking the corresponding bit in the received data.
 *
 * @param psx Pointer to the PSX controller structure.
 * @param button The button to check.
 * @return uint8_t Returns 1 if the button is pressed, or 0 if it is not.
 */
uint8_t panda_psx_get_command(psx_t* psx, PSX_ButtonsTypeDef button);


/**
 * @brief Gets the intensity of an analog input on the PSX controller.
 *
 * This function gets the intensity of an analog input on the PSX controller by reading the corresponding value in the received data.
 *
 * @param psx Pointer to the PSX controller structure.
 * @param analog The analog input to check.
 * @return uint8_t Returns the intensity of the analog input.
 */
uint8_t panda_psx_get_analog_intensity(psx_t* psx, PSX_AnalogTypeDef analog);


/**
 * @brief Checks if the PSX controller is on.
 *
 * This function checks if the PSX controller is on by checking a specific value in the received data.
 *
 * @param psx Pointer to the PSX controller structure.
 * @return PSX_StatusTypeDef Returns PSX_OK if the controller is on, or PSX_ERROR if it is not.
 */
PSX_StatusTypeDef panda_psx_is_on(psx_t* psx);


/**
 * @brief Checks if the PSX controller is in analog mode.
 *
 * This function checks if the PSX controller is in analog mode by checking a specific value in the received data.
 *
 * @param psx Pointer to the PSX controller structure.
 * @return PSX_Mode Returns PSX_Analog if the controller is in analog mode, or PSX_Digital if it is in digital mode.
 */
PSX_Mode panda_psx_is_analog(psx_t* psx);

#endif /* INC_PANDA_PSX_CONTROLLER_H_ */

