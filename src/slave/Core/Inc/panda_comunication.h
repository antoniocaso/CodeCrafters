/**
  ******************************************************************************
  * @file comunication.h
  * @brief This file contains all the functions prototypes for the comunication.c file.
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

#include "gpio.h"


/**
 * @brief Messages for communication between master and slave.
 */
typedef enum{
	ALIVE_MASTER = 10, 		/**< Message indicating the master is alive. */
	ALIVE_SLAVE = 11   		/**< Message indicating the slave is alive. */
}Messages;

#define MASTER_ADDRESS 1 	/**< I2C address of the master device. */
#define MAX_NUMBER_OF_ATTEMPTS 3 /**< Maximum number of attempts to be made contextually to a single communication. */
#define PANDA_STRUCT_GLOBAL_SIZE 27
#define PANDA_STRUCT_MASTER_SIZE 22
#define PANDA_STRUCT_SLAVE_SIZE 6
#define COMUNICATION_DELAY 2 /**< The amount of time the Slave will await information from the Master.*/
#define MAX_PIN_WAIT 1 /**< The amount of time the Slave will wait for the master to rise the synch pin.*/
/**
 * @brief Enumeration that allows the use of the associative array for the structure that holds essential information.
 */
typedef enum{
	AccelerometerX_High = 0,
	AccelerometerX_Low = 1,
	AccelerometerY_High = 2,
	AccelerometerY_Low = 3,
	AccelerometerZ_High = 4,
	AccelerometerZ_Low = 5,
	GyroscopeX_High = 6,
	GyroscopeX_Low = 7,
	GyroscopeY_High = 8,
	GyroscopeY_Low = 9,
	GyroscopeZ_High = 10,
	GyroscopeZ_Low = 11,
	DistanceMiddle_High = 12,
	DistanceMiddle_Low = 13,
	DistanceLeft_High = 14,
	DistanceLeft_Low = 15,
	DistanceRight_High = 16,
	DistanceRight_Low = 17,
	DriveSpeed = 18,
	TurnSpeed = 19,
	BitVariables = 20,
	BatterySensor = 21,
	EncoderFLSpeed = 22,
	EncoderFRSpeed = 23,
	EncoderBLSpeed = 24,
	EncoderBRSpeed = 25,
	Checksum = 26,
	Checksum_Master = 21
}Global_Struct_Enum;
typedef uint8_t Global_Struct_t; /**< Simply re-write differently the good old uint8_t type.*/


/**
 * @brief Initializes the associative array that will contain the global and shared information.
 *
 */
void Global_Struct_Master_Init(Global_Struct_t* Global_Struct);
void Global_Struct_Init(Global_Struct_t* Global_Struct);
void Global_Struct_Slave_Init(Global_Struct_t* Global_Struct);

/**
 * @brief Initializes the communication protocol for the slave device, also providing the means for the synchronization of the two,
 * essential for the proficient use of the ESFree scheduler.
 * 
 * This function initializes the communication protocol by setting up the I2C interface.
 * It also performs a handshake with the master device to ensure it is ready to send data.
 * 
 * @param i2c Pointer to the I2C handle.
 * @param sync_input_port Pointer to the GPIO port used for the sync input signal.
 * @param sync_input_pin Pin number for the sync input signal.
 * 
 * @return HAL_StatusTypeDef Returns HAL_OK if the initialization was successful, otherwise returns an error code.
 */
HAL_StatusTypeDef panda_comunication_init_sync(I2C_HandleTypeDef* i2c,
		GPIO_TypeDef* sync_input_port,
		uint16_t sync_input_pin);



/**
 * @brief Allows for the structure to be shared amongst the two devices, the Master beginning the act.
 *
 * First of all, a series of variables is defined to be used         in the function. Then, as long as the "flag" is not 0, several        * (blocking) attempts at receiving something from the master are made, waiting for a maximum of COMUNICATION_DELAY ms and trying for * at max MAX_NUMBER_OF_ATTEMPTS times. While waiting for something from the master, the synch_pin is also checked in order to * * *phisically verify the well being of the master. When something is received correctly, and the pin is indeed high, the slave goes on *to execute the communication initialization. Otherwise, the checksum is verified and if validated, the Slave replies to the master
 * sending his own amount of information. After that, the Slave waits for the Master to signal the correct reception of the Structure
 * from the Slave.
 *
 * @param i2c Pointer to the I2C handle.
 * @param sync_input_port Pointer to the GPIO port used for the sync input signal.
 * @param sync_input_pin Pin number for the sync input signal.
 * @param Global_Struct holds the pointer to the the array containing the structure.
 *
 * @return HAL_StatusTypeDef Returns HAL_OK if the exchange was successful, otherwise returns an error code.
 */
HAL_StatusTypeDef panda_exchange(I2C_HandleTypeDef* i2c,
		GPIO_TypeDef* sync_input_port,
		uint16_t sync_input_pin,
		Global_Struct_t* Global_Struct);

/**
 * @brief Calculates and initializes the checksum for a given structure.
 *
 * This function is designed to ensure the integrity of the data contained in a `Global_Struct_t` structure. It does this by calculating a checksum, which is a simple yet effective method for detecting errors in data transmission or storage.
 *
 * The checksum is calculated as follows:
 * - A `checksum` variable is initialized to 0.
 * - A loop iterates over each element in the `Global_Struct` array, excluding the last element. For each element, its value is added to `checksum`.
 * - The final value of `checksum` is then reduced modulo 256 to ensure it fits within a single byte. This value is stored in the last element of the `Global_Struct` array.
 *
 * This function is particularly useful in communication scenarios where the `Global_Struct_t` structure is being sent between devices. By including a checksum, the receiving device can recalculate the checksum on the received data and compare it to the received checksum. If the two checksums match, the data is assumed to be error-free.
 *
 * @param Global_Struct Pointer to the `Global_Struct_t` structure for which the checksum is to be calculated. This structure should be an array of bytes, with the last byte reserved for storing the checksum.
 *
 * @return HAL_StatusTypeDef This function always returns `HAL_OK` to indicate successful execution. However, in a more complex implementation, different return values could be used to indicate different error conditions or statuses.
 */
HAL_StatusTypeDef panda_comunication_init_checksum(Global_Struct_t *Global_Struct_From_Master);

/**
 * @brief Validates the checksum of a given structure.
 *
 * This function is designed to verify the integrity of the data contained in a `Global_Struct_t` structure. It does this by calculating a checksum and comparing it to the existing checksum stored in the structure.
 *
 * The checksum validation process is as follows:
 * - A `checksum` variable is initialized to 0.
 * - A loop iterates over each element in the `Global_Struct` array, excluding the last element. For each element, its value is added to `checksum`.
 * - The final value of `checksum` is then reduced modulo 256 to ensure it fits within a single byte. This value is compared to the last element of the `Global_Struct` array, which should contain the previously calculated checksum.
 * - If the calculated checksum matches the stored checksum, the function returns `HAL_OK` to indicate that the data is assumed to be error-free. If the checksums do not match, the function returns `HAL_ERROR` to indicate a potential error in the data.
 *
 * This function is particularly useful in communication scenarios where the `Global_Struct_t` structure is being received from another device. By validating the checksum, the receiving device can determine whether the data was transmitted correctly.
 *
 * @param Global_Struct Pointer to the `Global_Struct_t` structure whose checksum is to be validated. This structure should be an array of bytes, with the last byte containing the checksum.
 *
 * @return HAL_StatusTypeDef Returns `HAL_OK` if the checksum is validated successfully, indicating that the data is assumed to be error-free. Returns `HAL_ERROR` if the checksums do not match, indicating a potential error in the data.
 */
HAL_StatusTypeDef panda_comunication_validate_checksum(Global_Struct_t *Global_Struct_From_Slave);

/**
 * @brief Merges data from the Master structure into the Slave structure.
 *
 * This function is designed to synchronize data between two `Global_Struct_t` structures. It does this by copying each element from the Master structure to the corresponding element in the Slave structure.
 *
 * The merging process is as follows:
 * - A loop iterates over each element in the `Global_Struct_From_Master` array up to `PANDA_STRUCT_MASTER_SIZE`.
 * - For each element, its value is copied to the corresponding element in the `Global_Struct_From_Slave` array.
 *
 * This function is particularly useful in communication scenarios where the `Global_Struct_t` structure is being shared between a Master device and a Slave device. By merging the structures, the Slave device can update its data to match the Master's data.
 *
 * @param Global_Struct_From_Master Pointer to the `Global_Struct_t` structure that contains the data to be copied. This structure should be an array of bytes.
 * @param Global_Struct_From_Slave Pointer to the `Global_Struct_t` structure that will receive the copied data. This structure should be an array of bytes.
 */
void panda_merge_structs(Global_Struct_t *Global_Struct_From_Master,
		Global_Struct_t *Global_Struct_Slave,
		Global_Struct_t *Global_Struct);
#endif /* INC_PANDA_COMUNICATION_H_ */
