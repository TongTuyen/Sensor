#include "CommonGpio.h"

void CommonGpioInit(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	/*INIT INPUT PIN BEGIN*/
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	/*Init channel 1 input pin*/
	GPIO_InitStruct.Pin =	CHANNEL_1_INPUT_PIN;
	HAL_GPIO_Init(CHANNEL_1_INPUT_PORT,&GPIO_InitStruct);
	/*Init channel 2 input pin*/
	GPIO_InitStruct.Pin =	CHANNEL_2_INPUT_PIN;
	HAL_GPIO_Init(CHANNEL_2_INPUT_PORT,&GPIO_InitStruct);
	/*Init channel 3 input pin*/
	GPIO_InitStruct.Pin =	CHANNEL_3_INPUT_PIN;
	HAL_GPIO_Init(CHANNEL_3_INPUT_PORT,&GPIO_InitStruct);
	/*Init channel 4 input pin*/
	GPIO_InitStruct.Pin =	CHANNEL_4_INPUT_PIN;
	HAL_GPIO_Init(CHANNEL_4_INPUT_PORT,&GPIO_InitStruct);
	/*INIT INPUT PIN END*/
	/*INIT OUTPUT PIN BEGIN*/
//	ADC_ENABLE();
//	ADC_SELECT_CH1();
	//I2C_ENABLE();
	//I2C_SELECT_CH1();
	//I2C_SELECT_CH2();
	CHANNEL_1_PWR_ON();
	CHANNEL_2_PWR_ON();
	CHANNEL_3_PWR_ON();
	CHANNEL_4_PWR_ON();
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	/*Init adc enable pin*/
//	GPIO_InitStruct.Pin = ADC_ENABLE_PIN;
//	HAL_GPIO_Init(ADC_ENABLE_PORT,&GPIO_InitStruct);
//	/*Init adc sl0 pin*/
//	GPIO_InitStruct.Pin = ADC_SL0_PIN;
//	HAL_GPIO_Init(ADC_SL0_PORT,&GPIO_InitStruct);
//	/*Init adc sl1 pin*/
//	GPIO_InitStruct.Pin = ADC_SL1_PIN;
//	HAL_GPIO_Init(ADC_SL1_PORT,&GPIO_InitStruct);
	/*Init I2c enable pin*/
	GPIO_InitStruct.Pin = I2C_ENABLE_PIN;
	HAL_GPIO_Init(I2C_ENABLE_PORT,&GPIO_InitStruct);
	/*Init I2c sl0 pin*/
	GPIO_InitStruct.Pin = I2C_SL0_PIN;
	HAL_GPIO_Init(I2C_SL0_PORT,&GPIO_InitStruct);
	/*Init I2c sl1 pin*/
	GPIO_InitStruct.Pin = I2C_SL1_PIN;
	HAL_GPIO_Init(I2C_SL1_PORT,&GPIO_InitStruct);
	/*Init channel 1 power control pin*/
	GPIO_InitStruct.Pin = CHANNEL_1_PWR_CONTROL_PIN;
	HAL_GPIO_Init(CHANNEL_1_PWR_CONTROL_PORT,&GPIO_InitStruct);
	/*Init channel 2 power control pin*/
	GPIO_InitStruct.Pin = CHANNEL_2_PWR_CONTROL_PIN;
	HAL_GPIO_Init(CHANNEL_2_PWR_CONTROL_PORT,&GPIO_InitStruct);
	/*Init channel 3 power control pin*/
	GPIO_InitStruct.Pin = CHANNEL_3_PWR_CONTROL_PIN;
	HAL_GPIO_Init(CHANNEL_3_PWR_CONTROL_PORT,&GPIO_InitStruct);
	/*Init channel 4 power control pin*/
	GPIO_InitStruct.Pin = CHANNEL_4_PWR_CONTROL_PIN;
	HAL_GPIO_Init(CHANNEL_4_PWR_CONTROL_PORT,&GPIO_InitStruct);
	/*INIT OUTPUT PIN END*/
}

