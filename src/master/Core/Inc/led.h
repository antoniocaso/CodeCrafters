/**
  ******************************************************************************
  * @file led.h
  * @brief This file contains all the functions prototypes for the led.c file.
  *
  *	It includes the implementation for the led control.
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

#ifndef INC_LED_H_
#define INC_LED_H_

/**
 * @brief Enum for LED status.
 */
typedef enum
{
  LED_OFF = 0,
  LED_FLASH = 1,
  LED_ON = 2
} Led_TypeDef;

#endif /* INC_LED_H_ */
