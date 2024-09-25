/*
 * panda_encoder.h
 *
 *  Created on: Dec 6, 2023
 *      Author: Giuseppe
 */

#ifndef INC_PANDA_ENCODER_H_
#define INC_PANDA_ENCODER_H_

#include "stm32f4xx_hal.h"
#include "usart.h"
#include "stdbool.h"
#include "tim.h"

#define ENCODER_OK 		(0)
#define ENCODER_ERROR 	(-1)

#define PPR 12

#define CPR 48

#define RATIO 51
#define HYPERCYCLE 0.042
struct encoder_s {

	TIM_HandleTypeDef *timer;
	uint16_t diff;
	uint8_t rpm;
	uint8_t dir;
	uint16_t cnt1, cnt2;
};
typedef struct encoder_s encoder_t;

typedef int8_t ENCODER_StatusTypeDef;

ENCODER_StatusTypeDef panda_encoder_init(encoder_t *encoder, TIM_HandleTypeDef *htim);

void panda_encoder_read(encoder_t *encoder);

uint8_t panda_encoder_get_rpm(encoder_t *encoder);
uint8_t panda_encoder_get_speed(encoder_t *encoder);

#endif
