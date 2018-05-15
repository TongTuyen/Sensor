#include "SerialTransmit.h" 
void DebugPutString(char* pu8String) {
	while (*pu8String!=NULL) {
		HAL_UART_Transmit(&DEBUG, (uint8_t*)pu8String,1,0xff);
		pu8String++;
	}
}
void DebugPutChar(char u8Char) {
	HAL_UART_Transmit(&DEBUG, (uint8_t*)&u8Char,1,0xff);
}
void UartDebugInit(void){
	DEBUG.Instance = UART_DEBUG_INSTANCE;
  DEBUG.Init.BaudRate = DEBUG_BAUDRATE;
  DEBUG.Init.WordLength = UART_WORDLENGTH_8B;
  DEBUG.Init.StopBits = UART_STOPBITS_1;
  DEBUG.Init.Parity = UART_PARITY_NONE;
  DEBUG.Init.Mode = UART_MODE_TX_RX;
  DEBUG.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  DEBUG.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&DEBUG);
}
/**
* @ref DebugPutHex
* @param u8Hex: 8bit data
* @todo send string show hex value of u8Hex
*/
void DebugPutHex(uint8_t u8Hex){
	#ifdef DEBUG_ENABLE
	DebugPutString("0x");
	DebugPutChar(LastDigitToChar(u8Hex>>4));
	DebugPutChar(LastDigitToChar(u8Hex));	
	#endif
}
/**
* @ref Rs485PutString
* @param pu8String: point to string to send
* @todo send a string to RS485
*/
void Rs485PutString(char* pu8String) {
	#ifdef RS485_ENABLE
	while (*pu8String!=NULL) {
		HAL_UART_Transmit(&RS485, (uint8_t*)pu8String,1,0xff);
		pu8String++;
	}
	#endif
}
/**
*	@ref Rs485PutChar
* @param u8Char: character to send
* @todo	send 1 character to RS485
*/
void Rs485PutChar(char u8Char) {
	#ifdef RS485_ENABLE
	HAL_UART_Transmit(&RS485, (uint8_t*)&u8Char, 1, 0xff);
	#endif
}
/**
* @ref UartRs485Init
* @todo Init Uart RS485
*/
void UartRs485Init(void){
	#ifdef RS485_ENABLE
	RS485.Instance = UART_RS485_INSTANCE;
  RS485.Init.BaudRate = RS485_BAUDRATE;
  RS485.Init.WordLength = UART_WORDLENGTH_9B;
  RS485.Init.StopBits = UART_STOPBITS_1;
  RS485.Init.Parity = UART_PARITY_EVEN;
  RS485.Init.Mode = UART_MODE_TX_RX;
  RS485.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  RS485.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&RS485)!=HAL_OK){
		DebugPutString("\r\nRs485 cannot innit");
	}
	#endif
}
/**
* @ref ZigbeePutString
* @param pu8String: point to string to send 
* @todo send 1 string to zigbee
*/
void ZigbeePutString(char* pu8String){
	#ifdef ZIGBEE_ENABLE
	while(*pu8String){
		HAL_UART_Transmit(&ZIGBEE, (uint8_t*)pu8String,1,0xff);
		pu8String++;
	}
	#endif
}
/**
* @ref ZigbeePutChar
* @param u8Char: character to send 
* @todo send 1 character to zigbee
*/
void ZigbeePutChar(char u8Char){
	#ifdef ZIGBEE_ENABLE
	HAL_UART_Transmit(&ZIGBEE,(uint8_t*)&u8Char,1,0xff);
	#endif
}
/**
* @ref ZigbeeInit
* @todo Init Uart Zigbee
*/
void ZigbeeInit(void){
	#ifdef ZIGBEE_ENABLE
	ZIGBEE.Instance = UART_ZIGBEE_INSTANCE;
  ZIGBEE.Init.BaudRate = ZIGBEE_BAUDRATE;
  ZIGBEE.Init.WordLength = UART_WORDLENGTH_8B;
  ZIGBEE.Init.StopBits = UART_STOPBITS_1;
  ZIGBEE.Init.Parity = UART_PARITY_NONE;
  ZIGBEE.Init.Mode = UART_MODE_TX_RX;
  ZIGBEE.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  ZIGBEE.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&ZIGBEE)!=HAL_OK){
		DebugPutString("\r\nZIGBEE cannot innit");
	}
	#endif
}
void I2cInit(void){
	I2C.Instance = I2C_INSTANCE;
  I2C.Init.ClockSpeed = I2C_SPEED_SLOWMODE;
  I2C.Init.DutyCycle = I2C_DUTYCYCLE_2;
  I2C.Init.OwnAddress1 = 1;
  I2C.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  I2C.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  I2C.Init.OwnAddress2 = 1;
  I2C.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  I2C.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
    DebugPutString("I2C cannot init\r\n");
  }
}
/**
* @ref LastDigitToChar
* @param u8Digit 
* @return Character '0' to '9' or 'A' to 'F' 
* @todo show hex value of 4 last bit of u8Digit in character form
*/
char LastDigitToChar(uint8_t u8Digit){
	u8Digit &= 0x0f;
	char ret = 0;
	if(u8Digit<10){
		ret = u8Digit + '0';
	} else {
		ret = u8Digit - 10 + 'A';
	}
	return ret;
}