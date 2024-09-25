/**
  ******************************************************************************
  * @file comunication.c
  * @brief This file provides code for the proper communication between two STM boards.
  *        
  * It includes the implementation of the communication protocol.
  * The communication protocol is designed to ensure a reliable data
  * exchange between the two STM boards. It also includes a 
  * handshake mechanism with the master device.
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
#include "gpio.h"
#include "main.h"
#if (VERBOSE == 1)
	#include "usart.h"
#endif

void Global_Struct_Master_Init(Global_Struct_t* Global_Struct_Master){
	Global_Struct_Master[AccelerometerX_High] = 0;
	Global_Struct_Master[AccelerometerX_Low] = 0;
	Global_Struct_Master[AccelerometerY_High] = 0;
	Global_Struct_Master[AccelerometerY_Low] = 0;
	Global_Struct_Master[AccelerometerZ_High] = 0;
	Global_Struct_Master[AccelerometerZ_Low] = 0;
	Global_Struct_Master[GyroscopeX_High] = 0;
	Global_Struct_Master[GyroscopeX_Low] = 0;
	Global_Struct_Master[GyroscopeY_High] = 0;
	Global_Struct_Master[GyroscopeY_Low] = 0;
	Global_Struct_Master[GyroscopeZ_High] = 0;
	Global_Struct_Master[GyroscopeZ_Low] = 0;
	Global_Struct_Master[DistanceMiddle_High] = 0;
	Global_Struct_Master[DistanceMiddle_Low] = 127;
	Global_Struct_Master[DistanceLeft_High] = 0;
	Global_Struct_Master[DistanceLeft_Low] = 127;
	Global_Struct_Master[DistanceRight_High] = 0;
	Global_Struct_Master[DistanceRight_Low] = 127;
	Global_Struct_Master[DriveSpeed] = 128;
	Global_Struct_Master[TurnSpeed] = 128;
	Global_Struct_Master[BitVariables] = 0x00;
}

void Global_Struct_Init(Global_Struct_t* Global_Struct){
	Global_Struct[AccelerometerX_High] = 0;
	Global_Struct[AccelerometerX_Low] = 0;
	Global_Struct[AccelerometerY_High] = 0;
	Global_Struct[AccelerometerY_Low] = 0;
	Global_Struct[AccelerometerZ_High] = 0;
	Global_Struct[AccelerometerZ_Low] = 0;
	Global_Struct[GyroscopeX_High] = 0;
	Global_Struct[GyroscopeX_Low] = 0;
	Global_Struct[GyroscopeY_High] = 0;
	Global_Struct[GyroscopeY_Low] = 0;
	Global_Struct[GyroscopeZ_High] = 0;
	Global_Struct[GyroscopeZ_Low] = 0;
	Global_Struct[DistanceMiddle_High] = 0;
	Global_Struct[DistanceMiddle_Low] = 127;
	Global_Struct[DistanceLeft_High] = 0;
	Global_Struct[DistanceLeft_Low] = 127;
	Global_Struct[DistanceRight_High] = 0;
	Global_Struct[DistanceRight_Low] = 127;
	Global_Struct[DriveSpeed] = 128;
	Global_Struct[TurnSpeed] = 128;
	Global_Struct[BitVariables] = 0x00;
	Global_Struct[BatterySensor] = 100;
	Global_Struct[EncoderFLSpeed] = 0;
	Global_Struct[EncoderFRSpeed] = 0;
	Global_Struct[EncoderBLSpeed] = 0;
	Global_Struct[EncoderBRSpeed] = 0;
}

void Global_Struct_Slave_Init(Global_Struct_t* Global_Struct){
	Global_Struct[BatterySensor-(PANDA_STRUCT_MASTER_SIZE-1)] = 100;
	Global_Struct[EncoderFLSpeed-(PANDA_STRUCT_MASTER_SIZE-1)] = 0;
	Global_Struct[EncoderFRSpeed-(PANDA_STRUCT_MASTER_SIZE-1)] = 0;
	Global_Struct[EncoderBLSpeed-(PANDA_STRUCT_MASTER_SIZE-1)] = 0;
	Global_Struct[EncoderBRSpeed-(PANDA_STRUCT_MASTER_SIZE-1)] = 0;
}


HAL_StatusTypeDef panda_comunication_init_sync(I2C_HandleTypeDef* i2c, GPIO_TypeDef* sync_input_port, uint16_t sync_input_pin){
	#if (VERBOSE == 0)
		printf("Sono Slave NEW\r\n");
	#endif

	uint8_t RX_Buffer[PANDA_STRUCT_MASTER_SIZE];

	do{

		HAL_I2C_Slave_Receive(i2c , RX_Buffer, PANDA_STRUCT_MASTER_SIZE, HAL_MAX_DELAY); //Receiving in Blocking mode

	}while(RX_Buffer[BitVariables] != ALIVE_MASTER);

	#if (VERBOSE == 0)
		printf("Alive Ricevuto\r\n");
	#endif
	
	HAL_I2C_Master_Transmit(i2c,(MASTER_ADDRESS<<1), (uint8_t[]) {ALIVE_SLAVE}, 1, HAL_MAX_DELAY);
	
	#if (VERBOSE == 0)
		printf("Alive Inviato\r\n");
	#endif
	
	//Waiting for the pin from the master
	while(HAL_GPIO_ReadPin(sync_input_port, sync_input_pin) == GPIO_PIN_RESET);

	#if (VERBOSE == 0)
		printf("Start Scheduler\r\n");
	#endif
	return HAL_OK;

}


HAL_StatusTypeDef panda_comunication_init_checksum(Global_Struct_t *Global_Struct){
	uint16_t checksum = 0;
	for(int i = 0; i< PANDA_STRUCT_GLOBAL_SIZE-1; i++){
		checksum += Global_Struct[i];
	}
	Global_Struct[PANDA_STRUCT_GLOBAL_SIZE-1] = (uint8_t)(checksum % 256);
	return HAL_OK;
}

HAL_StatusTypeDef panda_comunication_validate_checksum(Global_Struct_t *Global_Struct){
	uint16_t checksum = 0;
	for(int i = 0; i< PANDA_STRUCT_MASTER_SIZE-1; i++){
		checksum += Global_Struct[i];
	}
	if (Global_Struct[PANDA_STRUCT_MASTER_SIZE-1] == (uint8_t)(checksum % 256)) return HAL_OK;
	else return HAL_ERROR;
}

void panda_merge_structs(Global_Struct_t *Global_Struct_From_Master, Global_Struct_t *Global_Struct_Slave, Global_Struct_t *Global_Struct){
	for(int i = 0; i < PANDA_STRUCT_MASTER_SIZE-1; i++){
		Global_Struct[i] = Global_Struct_From_Master[i];
	}
	for(int i = 0; i < PANDA_STRUCT_SLAVE_SIZE-1; i++){
		Global_Struct[i+PANDA_STRUCT_MASTER_SIZE-1] = Global_Struct_Slave[i];
	}
}
