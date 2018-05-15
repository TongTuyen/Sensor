#ifndef __COMMON_GPIO_H
#define __COMMON_GPIO_H
#include "DeviceDefine.h"

#define CHANNEL_1_READ_INPUT()			(HAL_GPIO_ReadPin(CHANNEL_1_INPUT_PORT,CHANNEL_1_INPUT_PIN)==GPIO_PIN_SET) ? 1:0
#define CHANNEL_2_READ_INPUT()			(HAL_GPIO_ReadPin(CHANNEL_2_INPUT_PORT,CHANNEL_2_INPUT_PIN)==GPIO_PIN_SET) ? 1:0
#define CHANNEL_3_READ_INPUT()			(HAL_GPIO_ReadPin(CHANNEL_3_INPUT_PORT,CHANNEL_3_INPUT_PIN)==GPIO_PIN_SET) ? 1:0
#define CHANNEL_4_READ_INPUT()			(HAL_GPIO_ReadPin(CHANNEL_4_INPUT_PORT,CHANNEL_4_INPUT_PIN)==GPIO_PIN_SET) ? 1:0

//#define ADC_SL0_HIGH()							HAL_GPIO_WritePin(ADC_SL0_PORT,ADC_SL0_PIN,GPIO_PIN_SET)
//#define ADC_SL0_LOW()								HAL_GPIO_WritePin(ADC_SL0_PORT,ADC_SL0_PIN,GPIO_PIN_RESET)
//#define ADC_SL1_HIGH()							HAL_GPIO_WritePin(ADC_SL1_PORT,ADC_SL1_PIN,GPIO_PIN_SET)
//#define ADC_SL1_LOW()								HAL_GPIO_WritePin(ADC_SL1_PORT,ADC_SL1_PIN,GPIO_PIN_RESET)

#define I2C_SLO_HIGH()							HAL_GPIO_WritePin(I2C_SL0_PORT,I2C_SL0_PIN,GPIO_PIN_SET)
#define I2C_SL0_LOW()								HAL_GPIO_WritePin(I2C_SL0_PORT,I2C_SL0_PIN,GPIO_PIN_RESET)
#define I2C_SL1_HIGH()							HAL_GPIO_WritePin(I2C_SL1_PORT,I2C_SL1_PIN,GPIO_PIN_SET)
#define I2C_SL1_LOW()								HAL_GPIO_WritePin(I2C_SL1_PORT,I2C_SL1_PIN,GPIO_PIN_RESET)

/*74HC4052
===========================================
||  Input                ||              ||  
||=======================||  Channel on  ||
||  E  ||  SL1  ||  SL0  ||              ||
||=====||=======||=======||==============||
||  L  ||   L   ||   L   || Channel 1    ||
||=====||=======||=======||==============||
||  L  ||   L   ||   H   || Channel 2    ||
||=====||=======||=======||==============||
||  L  ||   H   ||   L   || Channel 3    ||
||=====||=======||=======||==============||
||  L  ||   H   ||   H   || Channel 4    ||
||=====||=======||=======||==============||
||  H  ||   X   ||   X   || none         ||
||=====||=======||=======||==============||
*/

//#define ADC_ENABLE()								HAL_GPIO_WritePin(ADC_ENABLE_PORT,ADC_ENABLE_PIN,GPIO_PIN_RESET)
//#define ADC_DISABLE()								HAL_GPIO_WritePin(ADC_ENABLE_PORT,ADC_ENABLE_PIN,GPIO_PIN_SET)
//#define ADC_SELECT_CH1()						ADC_SL0_LOW();			ADC_SL1_LOW();
//#define ADC_SELECT_CH2()						ADC_SL0_HIGH();			ADC_SL1_LOW();
//#define ADC_SELECT_CH3()						ADC_SL0_LOW();			ADC_SL1_HIGH();
//#define ADC_SELECT_CH4()						ADC_SL0_HIGH();			ADC_SL1_HIGH();

#define I2C_ENABLE()								HAL_GPIO_WritePin(I2C_ENABLE_PORT,I2C_ENABLE_PIN,GPIO_PIN_RESET)
#define I2C_DISABLE()								HAL_GPIO_WritePin(I2C_ENABLE_PORT,I2C_ENABLE_PIN,GPIO_PIN_SET)
#define I2C_SELECT_CH1()						I2C_SL0_LOW();			I2C_SL1_LOW();
#define I2C_SELECT_CH2()						I2C_SLO_HIGH();			I2C_SL1_LOW();
#define I2C_SELECT_CH3()						I2C_SL0_LOW();			I2C_SL1_HIGH();
#define I2C_SELECT_CH4()						I2C_SLO_HIGH();			I2C_SL1_HIGH();

#define CHANNEL_1_PWR_ON()					HAL_GPIO_WritePin(CHANNEL_1_PWR_CONTROL_PORT,CHANNEL_1_PWR_CONTROL_PIN,GPIO_PIN_SET)
#define CHANNEL_1_PWR_OFF()					HAL_GPIO_WritePin(CHANNEL_1_PWR_CONTROL_PORT,CHANNEL_1_PWR_CONTROL_PIN,GPIO_PIN_RESET)
#define CHANNEL_2_PWR_ON()					HAL_GPIO_WritePin(CHANNEL_2_PWR_CONTROL_PORT,CHANNEL_2_PWR_CONTROL_PIN,GPIO_PIN_SET)
#define CHANNEL_2_PWR_OFF()					HAL_GPIO_WritePin(CHANNEL_2_PWR_CONTROL_PORT,CHANNEL_2_PWR_CONTROL_PIN,GPIO_PIN_RESET)
#define CHANNEL_3_PWR_ON()					HAL_GPIO_WritePin(CHANNEL_3_PWR_CONTROL_PORT,CHANNEL_3_PWR_CONTROL_PIN,GPIO_PIN_SET)
#define CHANNEL_3_PWR_OFF()					HAL_GPIO_WritePin(CHANNEL_3_PWR_CONTROL_PORT,CHANNEL_3_PWR_CONTROL_PIN,GPIO_PIN_RESET)
#define CHANNEL_4_PWR_ON()					HAL_GPIO_WritePin(CHANNEL_4_PWR_CONTROL_PORT,CHANNEL_4_PWR_CONTROL_PIN,GPIO_PIN_SET)
#define CHANNEL_4_PWR_OFF()					HAL_GPIO_WritePin(CHANNEL_4_PWR_CONTROL_PORT,CHANNEL_4_PWR_CONTROL_PIN,GPIO_PIN_RESET)

void CommonGpioInit(void);

#endif
