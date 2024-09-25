/**
  ******************************************************************************
  * @file panda_motor_driver.c
  * @brief This file provides code for interacting with a Sabertooth 2x12 motor driver.
  *
  * The library is designed to interact with a Sabertooth 2x12 motor driver.
  *
  * It includes functions to:
  *
  * send a command to the motor driver,
  * drive and stop indipendently the motors (forward and backward),
  * drive, stop and turn the rover by acting on both the motors.
  *
  * The functions interact with the Sabertooth 2x12 using UART communication.
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

#include "panda_motor_driver.h"

/** @brief Last direction of the motor */
uint8_t last_direction = 0;



void motor_send_command(UART_HandleTypeDef *huart, uint8_t address, uint8_t command, uint8_t speed){
	uint8_t checksum = (address+command+speed) & 127;
	uint8_t data[4] = {address, command, speed, checksum};
	HAL_UART_Transmit(huart, data, 4, 10);
}


void motor_independent_drive_forward(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed, Driver_MotorTypeDef motor){
	motor_send_command(huart, address, motor, speed);
}


void motor_independent_drive_backward(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed, Driver_MotorTypeDef motor){
	motor_send_command(huart, address, motor+1, speed);
}


void motor_mixed_drive_forward(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed){
	motor_send_command(huart, address, 8, speed);
}


void motor_mixed_drive_backward(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed){
	motor_send_command(huart, address, 9, speed);
}


void motor_mixed_turn_right(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed){
	motor_send_command(huart, address, 10, speed);
}


void motor_mixed_turn_left(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed){
	motor_send_command(huart, address, 11, speed);
}


void motor_independent_stop(UART_HandleTypeDef *huart, uint8_t address, Driver_MotorTypeDef motor){
	motor_independent_drive_forward(huart, address, 0, motor);
}


void motor_mixed_stop(UART_HandleTypeDef *huart, uint8_t address){
	motor_mixed_drive_forward(huart, address, 0);
	motor_mixed_turn_right(huart, address, 0);
}


void motor_mixed_drive(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed){

	uint8_t dead_axis = 128;
	uint8_t direction = speed / (dead_axis);
	if(direction == 0) speed = -(speed-dead_axis)-1;
	else if (direction == 1) speed = speed - dead_axis;

	if (direction != last_direction){
		//motor_independent_stop(huart, address, motor);
	}
	motor_send_command(huart, address, 9 - direction, speed);

	last_direction = direction;
}


void motor_mixed_turn(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed){
	uint8_t dead_axis = 128;
	uint8_t direction = speed / (dead_axis);
	if(direction == 0) speed = -(speed-dead_axis)-1;
	else if (direction == 1) speed = speed - dead_axis;

	if (direction != last_direction){
		//motor_independent_stop(huart, address, motor);
	}
	motor_send_command(huart, address, 11 - direction, speed);

	last_direction = direction;
}
