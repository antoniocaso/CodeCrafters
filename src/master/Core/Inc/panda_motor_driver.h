/**
  ******************************************************************************
  * @file panda_motor_driver.h
  * @brief This file contains all the functions prototypes for the panda_motor_driver.c file.
  *
  *	It provides an interface for interacting with the Sabertooth 2x12 Motor Driver.
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


#ifndef INC_PANDA_MOTOR_DRIVER_H_
#define INC_PANDA_MOTOR_DRIVER_H_

#include "usart.h"
#include "gpio.h"


/**
 * @brief Enum for specifying the motor of interest.
 */
typedef enum
{
  MOTOR_1 = 0, /**< Motor 1 */
  MOTOR_2 = 4  /**< Motor 2 */
} Driver_MotorTypeDef;


/**
 * @brief Enum for specifying the dead axis value.
 */
typedef enum
{
	DEAD_AXIS_127 = 127, /**< Dead Axis value is 127 */
	DEAD_AXIS_128 = 128  /**< Dead Axis value is 128 */
} Driver_DeadAxisDef;



/**
 * @brief Sends a command to a motor via UART.
 *
 * This function is designed to control a motor by sending a command via UART. The command includes an address, a command code, and a speed value. A checksum is also calculated and included in the command to ensure data integrity.
 *
 * The command sending process is as follows:
 * - A checksum is calculated by adding the address, command, and speed values together, and then taking the result modulo 128. This ensures the checksum fits within a single byte.
 * - The address, command, speed, and checksum values are stored in a data array.
 * - The data array is transmitted via UART using the `HAL_UART_Transmit` function.
 *
 * This function is particularly useful in scenarios where a microcontroller needs to control a motor via UART. By sending commands, the microcontroller can control the motor's speed and direction.
 *
 * @param huart Pointer to the UART handle. This handle is used by the `HAL_UART_Transmit` function to send the command via UART.
 * @param address The address of the motor to which the command is being sent. This allows multiple motors to be controlled independently.
 * @param command The command code to be sent to the motor. The command code determines what action the motor will take.
 * @param speed The speed value to be sent to the motor. This determines how fast the motor will spin.
 */
void motor_send_command(UART_HandleTypeDef *huart, uint8_t address, uint8_t command, uint8_t speed);


/**
 * @brief Drives a specific motor forward at a given speed.
 *
 * This function is designed to control a specific motor's forward movement via UART. It does this by calling the `motor_send_command` function with the provided parameters.
 *
 * The process of driving the motor forward is as follows:
 * - The `motor_send_command` function is called with the provided UART handle, motor address, motor type, and speed value.
 *
 * This function is particularly useful in scenarios where a microcontroller needs to control the forward movement of a motor via UART. By calling this function, the microcontroller can drive the motor forward at the desired speed.
 *
 * @param huart Pointer to the UART handle. This handle is used by the `motor_send_command` function to send the command via UART.
 * @param address The address of the motor to be driven forward. This allows multiple motors to be controlled independently.
 * @param speed The speed value for the forward movement of the motor. This determines how fast the motor will spin.
 * @param motor The type of the motor to be driven forward. This helps in identifying the specific motor in a system with multiple motors.
 */
void motor_independent_drive_forward(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed, Driver_MotorTypeDef motor);


/**
 * @brief Drives a specific motor backward at a given speed.
 *
 * This function is designed to control a specific motor's backward movement via UART. It does this by calling the `motor_send_command` function with the provided parameters and an adjusted motor type.
 *
 * The process of driving the motor backward is as follows:
 * - The `motor_send_command` function is called with the provided UART handle, motor address, and speed value. The motor type is incremented by 1 before being passed to the function. This is based on the assumption that the command set for the motor has the backward commands offset by 1 from the forward commands.
 *
 * This function is particularly useful in scenarios where a microcontroller needs to control the backward movement of a motor via UART. By calling this function, the microcontroller can drive the motor backward at the desired speed.
 *
 * @param huart Pointer to the UART handle. This handle is used by the `motor_send_command` function to send the command via UART.
 * @param address The address of the motor to be driven backward. This allows multiple motors to be controlled independently.
 * @param speed The speed value for the backward movement of the motor. This determines how fast the motor will spin.
 * @param motor The type of the motor to be driven backward. This helps in identifying the specific motor in a system with multiple motors.
 */
void motor_independent_drive_backward(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed, Driver_MotorTypeDef motor);


/**
 * @brief Drives all motors forward at a given speed.
 *
 * This function sends a command to all motors to drive forward at a specified speed. It does this by calling the `motor_send_command` function with the provided parameters and a command code of 8, which corresponds to forward movement in mixed mode.
 *
 * @param huart Pointer to the UART handle used to send the command.
 * @param address The address of the motor controller.
 * @param speed The speed at which the motors should move forward.
 */
void motor_mixed_drive_forward(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed);


/**
 * @brief Drives all motors backward at a given speed.
 *
 * This function sends a command to all motors to drive backward at a specified speed. It does this by calling the `motor_send_command` function with the provided parameters and a command code of 9, which corresponds to backward movement in mixed mode.
 *
 * @param huart Pointer to the UART handle used to send the command.
 * @param address The address of the motor controller.
 * @param speed The speed at which the motors should move backward.
 */
void motor_mixed_drive_backward(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed);


/**
 * @brief Turns all motors to the right at a given speed.
 *
 * This function sends a command to all motors to turn right at a specified speed. It does this by calling the `motor_send_command` function with the provided parameters and a command code of 10, which corresponds to right turn in mixed mode.
 *
 * @param huart Pointer to the UART handle used to send the command.
 * @param address The address of the motor controller.
 * @param speed The speed at which the motors should turn right.
 */
void motor_mixed_turn_right(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed);


/**
 * @brief Turns all motors to the left at a given speed.
 *
 * This function sends a command to all motors to turn left at a specified speed. It does this by calling the `motor_send_command` function with the provided parameters and a command code of 11, which corresponds to left turn in mixed mode.
 *
 * @param huart Pointer to the UART handle used to send the command.
 * @param address The address of the motor controller.
 * @param speed The speed at which the motors should turn left.
 */
void motor_mixed_turn_left(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed);


/**
 * @brief Stops a specific motor.
 *
 * This function sends a command to a specific motor to stop. It does this by calling the `motor_independent_drive_forward` function with a speed of 0, which corresponds to stopping the motor.
 *
 * @param huart Pointer to the UART handle used to send the command.
 * @param address The address of the motor controller.
 * @param motor The type of the motor to be stopped.
 */
void motor_independent_stop(UART_HandleTypeDef *huart, uint8_t address, Driver_MotorTypeDef motor);


/**
 * @brief Stops all motors.
 *
 * This function sends commands to all motors to stop. It does this by calling the `motor_mixed_drive_forward` and `motor_mixed_turn_right` functions with a speed of 0, which corresponds to stopping the motors.
 *
 * @param huart Pointer to the UART handle used to send the command.
 * @param address The address of the motor controller.
 */
void motor_mixed_stop(UART_HandleTypeDef *huart, uint8_t address);


/**
 * @brief Drives all motors in a specified direction at a given speed.
 *
 * This function sends a command to all motors to drive in a specified direction at a certain speed. The direction is determined by the speed value: if the speed is less than 128, the motors drive forward; if the speed is greater than or equal to 128, the motors drive backward.
 *
 * @param huart Pointer to the UART handle used to send the command.
 * @param address The address of the motor controller.
 * @param speed The speed and direction at which the motors should move. Values less than 128 correspond to forward movement, while values greater than or equal to 128 correspond to backward movement.
 */
void motor_mixed_drive(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed);


/**
 * @brief Turns all motors in a specified direction at a given speed.
 *
 * This function sends a command to all motors to turn in a specified direction at a certain speed. The direction is determined by the speed value: if the speed is less than 128, the motors turn right; if the speed is greater than or equal to 128, the motors turn left.
 *
 * @param huart Pointer to the UART handle used to send the command.
 * @param address The address of the motor controller.
 * @param speed The speed and direction at which the motors should turn. Values less than 128 correspond to right turns, while values greater than or equal to 128 correspond to left turns.
 */
void motor_mixed_turn(UART_HandleTypeDef *huart, uint8_t address, uint8_t speed);

#endif /* INC_PANDA_MOTOR_DRIVER_H_ */

