/**
  ******************************************************************************
  * @file panda_mpu6050.h
  * @brief This file contains all the functions prototypes for the panda_mpu6050.c file.
  *
  *	It provides an interface for interacting with Mpu6050 , Accelerometer Gyroscope Sensor Module.
  *
  *	It includes the necessary structures, enumerations, and function prototypes
  *	to initialize and read the mpu6050 Module.
  *
  *	It provides a convenient and structured way to retrieve information
  *	from the module.
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
#ifndef INC_MPU6050_DRIVER_H_
#define INC_MPU6050_DRIVER_H_

#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "i2c.h"
#include "usart.h"


/**
 * @brief Enumeration for the Mpu6050 module status.
 */
typedef enum
{
	MPU6050_OK       = 0, /**< OK status */
	MPU6050_ERROR    = -1 /**< Error status */
} MPU6050_StatusTypeDef;


/**
 * @brief Enumeration for the Mpu6050 module addresses.
 */
typedef enum
{
	MPU6050_ADDR      = 0xD0, 	 /**< MPU6050 Address 0xD0 */
	SMPLRT_DIV_REG    = 0x19, 	 /**< SMPLRT_DIV_REG 0x19 */
	GYRO_CONFIG_REG   = 0x1B,	 /**< Dead Axis 0x1B */
	ACCEL_CONFIG_REG  = 0x1C,	 /**< ACCEL_CONFIG_REG 0x1C */
	ACCEL_XOUT_H_REG  = 0x3B, 	 /**< ACCEL_XOUT_H_REG 0x3B */
	TEMP_OUT_H_REG    = 0x41,	 /**< TEMP_OUT_H_REG 0x41 */
	GYRO_XOUT_H_REG   = 0x43,	 /**< GYRO_XOUT_H_REG  0x43 */
	PWR_MGMT_1_REG    = 0x6B,	 /**< PWR_MGMT_1_REG 0x6B */
	WHO_AM_I_REG      = 0x75	 /**< WHO_AM_I_REG 0x75 */
} MPU6050_AddressTypeDef;


/**
 * @brief Structure for the Mpu6050 module data.
 */
typedef struct  {

	I2C_HandleTypeDef *hi2c;

	int16_t Acc_X_RAW;
	int16_t Acc_Y_RAW;
	int16_t Acc_Z_RAW;

	int16_t Gyro_X_RAW;
	int16_t Gyro_Y_RAW;
	int16_t Gyro_Z_RAW;

	double Acc_x;
	double Acc_y;
	double Acc_z;

	double Gyro_x;
	double Gyro_y;
	double Gyro_z;

	float Temperature;

}MPU6050_t;


/**
 * @brief Initialize the MPU6050 sensor.
 * @param MPU6050 A pointer to an `MPU6050_t` structure.
 * @param hi2c1 A handle to an I2C peripheral.
 * @return MPU6050_StatusTypeDef status of the initialization.
 * This function initializes the MPU6050 sensor. It sets the initial values of the accelerometer, gyroscope, and temperature readings to 0.
 * It then reads the WHO_AM_I register of the MPU6050 sensor to check if the sensor is present.
 * If the sensor is present, it configures the power management to all 0's, sample rate to 1 KHz, accelerometer configuration, and gyroscope configuration registers to 0's.
 */
MPU6050_StatusTypeDef panda_mpu6050_init(MPU6050_t *MPU6050, I2C_HandleTypeDef *hi2c1);

/**
 * @brief Read the accelerometer, gyroscope, and temperature data from the MPU6050 sensor.
 * @param MPU6050 A pointer to an `MPU6050_t` structure.
 * This function reads the accelerometer, gyroscope, and temperature data from the MPU6050 sensor.
 * It reads 14 bytes of data starting from the ACCEL_XOUT_H register.
 * The raw accelerometer and gyroscope readings are converted to g and degrees per second, respectively.
 * The raw temperature reading is converted to degrees Celsius.
 */

void panda_mpu6050_read(MPU6050_t *MPU6050);


#endif

