/**
  ******************************************************************************
  * @file panda_mpu6050.c
  * @brief This file provides code for interacting with a MPU6050 module.
  *
  * The library is designed to interact with a MPU6050 module.
  *
  * It includes functions to initialize the module and read data from the module.
  *
  *
  * The functions interact with theMPU6050 module using I2C communication.
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



#include "panda_mpu6050.h"

MPU6050_StatusTypeDef panda_mpu6050_init(MPU6050_t *MPU6050, I2C_HandleTypeDef *hi2c){

	MPU6050->hi2c=hi2c;

	MPU6050->Acc_x=0;
	MPU6050->Acc_y=0;
	MPU6050->Acc_z=0;

	MPU6050->Gyro_x=0;
	MPU6050->Gyro_y=0;
	MPU6050->Gyro_z=0;

	MPU6050->Acc_X_RAW=0;
	MPU6050->Acc_Y_RAW=0;
	MPU6050->Acc_Z_RAW=0;

	MPU6050->Gyro_X_RAW=0;
	MPU6050->Gyro_Y_RAW=0;
	MPU6050->Gyro_Z_RAW=0;

	MPU6050->Temperature=0;

	uint8_t check,data;

	HAL_I2C_Mem_Read(MPU6050->hi2c, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1 , 1000);
	if (check == 104)
	{
		data = 0;
		HAL_I2C_Mem_Write(MPU6050->hi2c,MPU6050_ADDR, PWR_MGMT_1_REG, 1, &data, 1, 1000);
		data = 0x07;
		HAL_I2C_Mem_Write(MPU6050->hi2c, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &data, 1, 1000);
		data = 0x00;
		HAL_I2C_Mem_Write(MPU6050->hi2c, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &data, 1, 1000);

		data = 0x00;
		HAL_I2C_Mem_Write(MPU6050->hi2c, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &data, 1, 1000);

		return MPU6050_OK;
	}

	return MPU6050_ERROR;
}

void panda_mpu6050_read(MPU6050_t *MPU6050){

	uint8_t Rec_Data[14];
	int16_t temp;

	HAL_I2C_Mem_Read(MPU6050->hi2c, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 14, 1000);

	MPU6050->Acc_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
	MPU6050->Acc_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
	MPU6050->Acc_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

	temp = (int16_t)(Rec_Data[6] << 8 | Rec_Data[7]);

	MPU6050->Gyro_X_RAW = (int16_t)(Rec_Data[8] << 8 | Rec_Data[9]);
	MPU6050->Gyro_Y_RAW = (int16_t)(Rec_Data[10] << 8 | Rec_Data[11]);
	MPU6050->Gyro_Z_RAW = (int16_t)(Rec_Data[12] << 8 | Rec_Data[13]);

	MPU6050->Acc_x = MPU6050->Acc_X_RAW / 16384.0;
	MPU6050->Acc_y = MPU6050->Acc_Y_RAW / 16384.0;
	MPU6050->Acc_z = MPU6050->Acc_Z_RAW / 14418.0;

	MPU6050->Temperature = (float)((int16_t)temp / (float)340.0 + (float)36.53);

	MPU6050->Gyro_x = MPU6050->Gyro_X_RAW / 131.0;
	MPU6050->Gyro_y = MPU6050->Gyro_Y_RAW / 131.0;
	MPU6050->Gyro_z = MPU6050->Gyro_Z_RAW / 131.0;

}
