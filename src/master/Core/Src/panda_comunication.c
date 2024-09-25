/**
  ******************************************************************************
  * @file panda_comunication.c
  * @brief This file provides code for the proper communication between two STM boards.
  *        
  * It includes the implementation of the communication protocol and the initialization
  * of the necessary GPIO pins and I2C interface. The communication protocol is designed
  * to ensure a reliable data exchange between the two STM boards. It also includes a 
  * handshake mechanism with the slave device to ensure it is ready to receive data.
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

HAL_StatusTypeDef panda_comunication_init_sync(I2C_HandleTypeDef* i2c, GPIO_TypeDef* sync_output_port, uint16_t sync_output_pin, GPIO_TypeDef* sync_input_port, uint16_t sync_input_pin){

	HAL_StatusTypeDef res = HAL_ERROR;

	#if (VERBOSE == 0)
		printf("Sono Master NEW\r\n");
	#endif

	HAL_GPIO_WritePin(sync_output_port, sync_output_pin, GPIO_PIN_RESET);

	uint8_t RX_Buffer;
	uint8_t Alive_Master[PANDA_STRUCT_MASTER_SIZE] = {ALIVE_MASTER};
	Alive_Master[BitVariables] = ALIVE_MASTER;
	do{
		RX_Buffer=0;
		do{
			HAL_I2C_Master_Transmit(i2c,(SLAVE_ADDRESS<<1), Alive_Master, PANDA_STRUCT_MASTER_SIZE, HAL_MAX_DELAY);
			#if (VERBOSE == 0)
				printf("Alive Inviato\r\n");
			#endif
		//Receive Alive Slave
	}while(HAL_I2C_Slave_Receive(i2c ,&RX_Buffer, 1, 50) == HAL_ERROR); //Receiving in Blocking mode



		#if (VERBOSE == 0)
			if(RX_Buffer == ALIVE_SLAVE){
				printf("Alive Ricevuto\r\n");
			}else{
				printf("Alive NON Ricevuto\r\n");
			}
		#endif

	}while(RX_Buffer != ALIVE_SLAVE);

	HAL_GPIO_WritePin(sync_output_port, sync_output_pin, GPIO_PIN_SET);

	while(HAL_GPIO_ReadPin(sync_input_port, sync_input_pin) == GPIO_PIN_RESET);
	#if (VERBOSE == 0)
		printf("Start Scheduler\r\n");
	#endif
	HAL_GPIO_WritePin(sync_output_port, sync_output_pin, GPIO_PIN_RESET);

	return res;
}




void panda_exchange_struct(I2C_HandleTypeDef* i2c, Global_Struct_t *Global_Struct_Master, Global_Struct_t* Global_Struct, uint8_t *counter_checksum){



	uint8_t counter = 0;
	Global_Struct_t Global_Struct_From_Slave[PANDA_STRUCT_GLOBAL_SIZE];
	uint8_t flag = 0;

	panda_comunication_init_checksum(Global_Struct_Master);

	while(counter < MAX_NUMBER_OF_ATTEMPTS && (HAL_I2C_Master_Transmit(i2c, (SLAVE_ADDRESS<<1), Global_Struct_Master, PANDA_STRUCT_MASTER_SIZE, HAL_MAX_DELAY) != HAL_OK)){
		counter++;
	}

	if( counter >= MAX_NUMBER_OF_ATTEMPTS ){
		*counter_checksum+=2;
	}


	if(HAL_I2C_Slave_Receive(i2c, Global_Struct_From_Slave, PANDA_STRUCT_GLOBAL_SIZE, COMUNICATION_DELAY*2) == HAL_OK){
		//CONTROLLO CHECKSUM
		if(Global_Struct_From_Slave[BitVariables] == 255 || panda_comunication_validate_checksum(Global_Struct_From_Slave) != HAL_OK ){
			*counter_checksum++;
		}else{
			*counter_checksum=0;

			for(int i = 0; i < PANDA_STRUCT_MASTER_SIZE-1; i++){
				Global_Struct[i] = Global_Struct_Master[i];
			}
			for(int i = 0; i < PANDA_STRUCT_SLAVE_SIZE-1; i++){
				Global_Struct[i+PANDA_STRUCT_MASTER_SIZE-1] = Global_Struct_From_Slave[i+PANDA_STRUCT_MASTER_SIZE-1];
			}

		}
	}else{
	}

	return;


}

void panda_comunication_init_checksum(Global_Struct_t *Global_Struct){
	uint16_t checksum = 0;
	for(int i = 0; i< PANDA_STRUCT_MASTER_SIZE-1; i++){
		checksum += Global_Struct[i];
	}
	Global_Struct[PANDA_STRUCT_MASTER_SIZE-1] = (uint8_t)(checksum % 256);
}

HAL_StatusTypeDef panda_comunication_validate_checksum(Global_Struct_t *Global_Struct){
	uint16_t checksum = 0;
	for(int i = 0; i< PANDA_STRUCT_GLOBAL_SIZE-1; i++){
		checksum += Global_Struct[i];
	}
	if (Global_Struct[PANDA_STRUCT_GLOBAL_SIZE-1] == (uint8_t)(checksum % 256)) return HAL_OK;
	else return HAL_ERROR;
}
