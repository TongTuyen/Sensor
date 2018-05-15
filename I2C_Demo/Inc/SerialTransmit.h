#ifndef __SERIAL_TRANSMIT_H
#define __SERIAL_TRANSMIT_H 

#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "DeviceDefine.h"

extern UART_HandleTypeDef huart1;
extern I2C_HandleTypeDef hi2c1;

#define DEBUG 									huart1
#define UART_DEBUG_INSTANCE 		USART1
#define DEBUG_BAUDRATE 					115200

#define RS485										huart3
#define UART_RS485_INSTANCE 		USART3
#define RS485_BAUDRATE					9600

#define ZIGBEE									huart2

#define I2C 										hi2c1
#define I2C_INSTANCE 						I2C1
#define I2C_SPEED_FASTMODE 		 	400000
#define I2C_SPEED_STANDARDMODE 	100000 
#define I2C_SPEED_SLOWMODE			50000

void I2cInit(void);

void DebugPutString(char* pu8String);
void DebugPutChar(char u8Char);
void UartDebugInit(void);
void DebugPutHex(uint8_t u8Hex);

void Rs485PutString(char* pu8String);
void Rs485PutChar(char u8Char);
void UartRs485Init(void);

void ZigbeePutString(char* pu8String);
void ZigbeePutChar(char u8Char);
void ZigbeeInit(void);
char LastDigitToChar(uint8_t u8Digit);
#endif