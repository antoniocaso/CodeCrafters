/**
  ******************************************************************************
  * @file panda_psx_controller.c
  * @brief This file provides code for interacting with a PSX controller.
  *
  * The library is designed to interact with a PSX (PlayStation) controller.
  *
  * It includes functions to initialize the controller,
  * read the gamepad state, turn on the analog mode, print debug information,
  * get commands from the controller, and get the analog intensity.
  *
  * The functions interact with the PSX controller using SPI communication.
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

#include "panda_psx_controller.h"


PSX_StatusTypeDef panda_psx_init(psx_t* psx, SPI_HandleTypeDef* spi, GPIO_TypeDef* gpio_att_port, uint16_t gpio_att_pin){
	psx->spi = spi;
	psx->gpio_att_port = gpio_att_port;
	psx->gpio_att_pin = gpio_att_pin;
	HAL_GPIO_WritePin(psx->gpio_att_port, psx->gpio_att_pin, GPIO_PIN_SET);
	return PSX_OK;
}


PSX_StatusTypeDef panda_psx_read_gamepad(psx_t* psx){
	uint8_t TX[21] = {0x01, 0x42};
	HAL_GPIO_TogglePin(psx->gpio_att_port, psx->gpio_att_pin);
	if ( HAL_SPI_TransmitReceive(psx->spi, TX, psx->RX, 9, 10)!= HAL_OK ) return PSX_ERROR;
	HAL_GPIO_TogglePin(psx->gpio_att_port, psx->gpio_att_pin);
	return PSX_OK;
}


void panda_psx_debug_print(psx_t* psx, int mode){
	uint8_t newline[2]="\r\n";
	for(int i = 0; i<9; i++){
	  char hexString[5];
	  if(mode == 0){
		  sprintf(hexString, "%02X ", psx->RX[i]);
		  HAL_UART_Transmit(&huart2, (uint8_t*)hexString, 4, 10);
	  }else if (mode == 1){
		  sprintf(hexString, "%d  ", psx->RX[i]);
		  HAL_UART_Transmit(&huart2, (uint8_t*)hexString, 4, 10);
	  }
	}
	HAL_UART_Transmit(&huart2, newline, 2, 10);
}


uint8_t panda_psx_get_command(psx_t* psx, PSX_ButtonsTypeDef button){
	int byte = button / 8;
	int bit = button % 8;
	int value = psx->RX[byte];
	unsigned char mask = 1 << bit;
	return (value & mask) == 0;
}


uint8_t panda_psx_get_analog_intensity(psx_t* psx, PSX_AnalogTypeDef analog){
	if(panda_psx_is_on(psx) == PSX_ERROR) return 128;
	if(panda_psx_is_analog(psx) == PSX_Analog){
		if(analog == LEFT_Y_AXIS || analog == RIGHT_Y_AXIS){ 	//127
			return 255 - psx->RX[analog];
		}else{													//128
			return psx->RX[analog];
		}
	}else{
		return 128;
	}
}

PSX_StatusTypeDef panda_psx_is_on(psx_t* psx){
	if(psx->RX[2] == 90) return PSX_OK;
	else return PSX_ERROR;
}

PSX_Mode panda_psx_is_analog(psx_t* psx){
	if(psx->RX[1] == 115) return PSX_Analog;
	else if (psx->RX[1] == 65) return PSX_Digital;
}
