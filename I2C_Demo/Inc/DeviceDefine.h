#ifndef __DEVICE_DEFINE_H
#define __DEVICE_DEFINE_H
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "stdbool.h"
#include "string.h"

#define SYSTEM_CLK		64MHZ

#define DEBUG_ENABLE
#define RS485_ENABLE
#define ZIGBEE_ENABLE
//#define SPI_ENABLE
#define I2C_SENSOR_ENABLE

#ifdef DEBUG_ENABLE
#define UART_DEBUG_INSTANCE 			USART1
#define DEBUG_BAUDRATE 						115200
#endif 

#ifdef RS485_ENABLE
#define UART_RS485_INSTANCE 			USART3
#define RS485_BAUDRATE						9600
#endif

#ifdef ZIGBEE_ENABLE
#define UART_ZIGBEE_INSTANCE			USART2
#define ZIGBEE_BAUDRATE						9600
#endif

#ifdef SPI_ENABLE
#define SPI_INSTANCE							SPI2
#endif

#ifdef I2C_SENSOR_ENABLE
#define I2C_INSTANCE 						I2C1
#define I2C_SPEED_FASTMODE 		 	400000
#define I2C_SPEED_STANDARDMODE 	100000 
#define I2C_SPEED_SLOWMODE			50000
#endif

#define CHANNEL_1_INPUT_PORT			GPIOB
#define CHANNEL_1_INPUT_PIN				GPIO_PIN_1
#define CHANNEL_2_INPUT_PORT			GPIOB
#define CHANNEL_2_INPUT_PIN				GPIO_PIN_0
#define CHANNEL_3_INPUT_PORT			GPIOA
#define CHANNEL_3_INPUT_PIN				GPIO_PIN_7
#define CHANNEL_4_INPUT_PORT			GPIOA
#define CHANNEL_4_INPUT_PIN				GPIO_PIN_6

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

//#define ADC_ENABLE_PORT						GPIOA
//#define ADC_ENABLE_PIN						GPIO_PIN_15
//#define ADC_SL0_PORT							GPIOB
//#define ADC_SL0_PIN								GPIO_PIN_3
//#define ADC_SL1_PORT							GPIOB
//#define ADC_SL1_PIN								GPIO_PIN_4
#define I2C_ENABLE_PORT						GPIOB
#define I2C_ENABLE_PIN						GPIO_PIN_5
#define I2C_SL0_PORT							GPIOB
#define I2C_SL0_PIN								GPIO_PIN_8
#define I2C_SL1_PORT							GPIOB
#define I2C_SL1_PIN								GPIO_PIN_9

#define CHANNEL_1_PWR_CONTROL_PORT				GPIOB
#define CHANNEL_1_PWR_CONTROL_PIN					GPIO_PIN_12
#define CHANNEL_2_PWR_CONTROL_PORT				GPIOB
#define CHANNEL_2_PWR_CONTROL_PIN					GPIO_PIN_13
#define CHANNEL_3_PWR_CONTROL_PORT				GPIOB
#define CHANNEL_3_PWR_CONTROL_PIN					GPIO_PIN_14
#define CHANNEL_4_PWR_CONTROL_PORT				GPIOB
#define CHANNEL_4_PWR_CONTROL_PIN					GPIO_PIN_15

typedef enum  __MESSAGE_TYPE{
	MESSAGE_TYPE_NONE,
	MESSAGE_TYPE_RS485,
	MESSAGE_TYPE_RF,
}MESSAGE_TYPE;

void __delay_us(uint16_t us);

extern I2C_HandleTypeDef 		hi2c1;
extern UART_HandleTypeDef 	huart1;
extern UART_HandleTypeDef 	huart2;
extern UART_HandleTypeDef 	huart3;
extern RTC_HandleTypeDef hrtc;

extern uint16_t SensorBoxAddress;

#endif
