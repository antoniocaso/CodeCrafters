#include "panda_encoder.h"


ENCODER_StatusTypeDef panda_encoder_init(encoder_t *encoder, TIM_HandleTypeDef *htim){

	if(encoder && htim){
		encoder->timer=htim;
		encoder->diff=0;
		encoder->rpm=0;
		encoder->dir = 0;
		HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL);
		return ENCODER_OK;
	}
	return ENCODER_ERROR;
}

void panda_encoder_read(encoder_t *encoder){

	encoder->cnt2 = __HAL_TIM_GET_COUNTER(encoder->timer);

	if (__HAL_TIM_IS_TIM_COUNTING_DOWN(encoder->timer)) {
		encoder->diff = encoder->cnt1 - encoder->cnt2;
	} else {
		encoder->diff = encoder->cnt2 - encoder->cnt1;
	}

	encoder->rpm = encoder->diff * 60 / 48 * (1/HYPERCYCLE) / 51;
	encoder->dir = __HAL_TIM_IS_TIM_COUNTING_DOWN(encoder->timer);
	encoder->cnt1 = encoder->cnt2;
}

uint8_t panda_encoder_get_rpm(encoder_t *encoder){
	return encoder->rpm;
}

uint8_t panda_encoder_get_speed(encoder_t *encoder){
	return 128 + encoder->dir * (encoder->rpm / 170.0) * 127 - (1 - encoder->dir) * (encoder->rpm / 170.0) * 128;
}

