/**
  ******************************************************************************
  * @file panda_comunication.h
  * @brief This file contains all the functions prototypes for the panda_comunication.c file.
  *
  *	It includes the implementation of the communication protocol.
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

#ifndef INC_PANDA_COMUNICATION_H_
#define INC_PANDA_COMUNICATION_H_

#include "stm32f4xx_hal.h"
#include "gpio.h"
/**
 * @brief Messages for communication between master and slave.
 */
typedef enum{
	ALIVE_MASTER = 10, 		/**< Message indicating the master is alive. */
	ALIVE_SLAVE = 11   		/**< Message indicating the slave is alive. */
}Messages;


#define SLAVE_ADDRESS 89 			/**< I2C address of the slave device. */
#define MAX_NUMBER_OF_ATTEMPTS 2	/**< Max number of retry for a comunication. */
#define PANDA_STRUCT_GLOBAL_SIZE 27 /**< Size of Total Struct. */
#define PANDA_STRUCT_MASTER_SIZE 22 /**<Size of Master Struct. */
#define PANDA_STRUCT_SLAVE_SIZE 6   /**<Size of Slave Struct. */
#define COMUNICATION_DELAY 2		/**<Delay for one Trasmitt in ms. */

/**
 * @brief Enum for global structure.
 */
typedef enum{
	AccelerometerX_High = 0, /**< High byte of the X-axis accelerometer reading. */
	AccelerometerX_Low = 1, /**< Low byte of the X-axis accelerometer reading. */
	AccelerometerY_High = 2, /**< High byte of the Y-axis accelerometer reading. */
	AccelerometerY_Low = 3, /**< Low byte of the Y-axis accelerometer reading. */
	AccelerometerZ_High = 4, /**< High byte of the Z-axis accelerometer reading. */
	AccelerometerZ_Low = 5, /**< Low byte of the Z-axis accelerometer reading. */
	GyroscopeX_High = 6, /**< High byte of the X-axis gyroscope reading. */
	GyroscopeX_Low = 7, /**< Low byte of the X-axis gyroscope reading. */
	GyroscopeY_High = 8, /**< High byte of the Y-axis gyroscope reading. */
	GyroscopeY_Low = 9, /**< Low byte of the Y-axis gyroscope reading. */
	GyroscopeZ_High = 10, /**< High byte of the Z-axis gyroscope reading. */
	GyroscopeZ_Low = 11, /**< Low byte of the Z-axis gyroscope reading. */
	DistanceMiddle_High = 12, /**< High byte of the middle distance sensor reading. */
	DistanceMiddle_Low = 13, /**< Low byte of the middle distance sensor reading. */
	DistanceLeft_High = 14, /**< High byte of the left distance sensor reading. */
	DistanceLeft_Low = 15, /**< Low byte of the left distance sensor reading. */
	DistanceRight_High = 16, /**< High byte of the right distance sensor reading. */
	DistanceRight_Low = 17, /**< Low byte of the right distance sensor reading. */
	DriveSpeed = 18, /**< Drive speed. */
	TurnSpeed = 19, /**< Turn speed. */
	BitVariables = 20, /**< Bit variables. */
	BatterySensor = 21, /**< Battery sensor reading. */
	EncoderFLSpeed = 22, /**< High byte of the front left encoder speed. */
	EncoderFRSpeed = 23, /**< High byte of the front right encoder speed. */
	EncoderBLSpeed = 24, /**< High byte of the back left encoder speed. */
	EncoderBRSpeed = 25, /**< High byte of the back right encoder speed. */
	Checksum = 26, /**< Checksum. */
	Checksum_Master = 21
}Global_Struct_Enum;



typedef uint8_t Global_Struct_t;


/**
 * @brief Initializes the global structure.
 * @param Global_Struct Pointer to the global structure.
 */
void Global_Struct_Master_Init(Global_Struct_t* Global_Struct);


/**
 * @brief Initializes the communication protocol.
 *
 * @details This function initializes the communication protocol by setting up the necessary GPIO pins and I2C interface. It also performs a handshake with the slave device to ensure it is ready to receive data.
 *
 * @param i2c Pointer to the I2C handle.
 * @param sync_output_port Pointer to the GPIO port used for the sync output signal.
 * @param sync_output_pin Pin number for the sync output signal.
 * @param sync_input_port Pointer to the GPIO port used for the sync input signal.
 * @param sync_input_pin Pin number for the sync input signal.
 *
 * @return HAL_StatusTypeDef Returns HAL_OK if the initialization was successful, otherwise returns an error code.
 */
HAL_StatusTypeDef panda_comunication_init_sync(I2C_HandleTypeDef* i2c,
		GPIO_TypeDef* sync_output_port,
		uint16_t sync_output_pin,
		GPIO_TypeDef* sync_input_port,
		uint16_t sync_input_pin);



/**
 * @brief Initializes the communication protocol.
 *
 * @details This function initializes the communication protocol by setting up the necessary GPIO pins and I2C interface. It also performs a handshake with the slave device to ensure it is ready to receive data.
 *
 * @param i2c Pointer to the I2C handle.
 * @param Global_Struct_Master Pointer to the Master's Struct.
 * @param Global_Struct Pointer to the Global's Struct.
 * @param counter_checksum Pointer to the counter_checksum that will be modified.
 *
 */
void panda_exchange_struct(I2C_HandleTypeDef* i2c,  Global_Struct_t *Global_Struct_Master, Global_Struct_t* Global_Struct, uint8_t *counter_checksum);



/**
 * @brief Calculate Checksum for the struct.
 * @details This function sum all fields of the struct.
 * @param Global_Struct_From_Master Pointer to the master's struct .
 */
void panda_comunication_init_checksum(Global_Struct_t *Global_Struct_From_Master);

/**
 * @brief Validate Checksum recived from the slave.
 * @param Global_Struct_From_Slave Pointer to the slave's struct .
 * @return HAL_StatusTypeDef Returns HAL_OK if the check was successful, otherwise returns an error code.
 */
HAL_StatusTypeDef panda_comunication_validate_checksum(Global_Struct_t *Global_Struct_From_Slave);



#endif /* INC_PANDA_COMUNICATION_H_ */
