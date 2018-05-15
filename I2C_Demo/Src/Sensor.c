#include "Sensor.h"
#include "string.h"
#include "SlaveDefine.h"
#include "RspHandle.h"
#include "FlashRW.h"
uint8_t pu8DataSend[256];
uint8_t pu8DataRequest[10]={0xB8, 0x03, 0x00, 0x04, 0xD5, 0x74};
HAL_StatusTypeDef I2C_Check;
uint8_t u8BH1750_CF;
uint8_t pu8BH1750_rx[2];
static char temp[256];
/* AM2315 cam bien do am va nhiet do moi truong
	 * nhiet do + do am
	 * do phan giai 16bit  
	 * nhiet do 
	 * dai do -40 den 125"C 
	 * do phan giai 0.1"C
	 * do chinh xac 0.1"C
	 * do am
	 * do phan giai 0.1RH
	 * do chinh xac 2RH */

void SensorCommunication(void) {
	
	//AM2315UpdateValue();
	//BH1750UpdateValue();
//	
//	if(u16Port1 ==1)
//		{
//		I2C_ENABLE();
//		I2C_SELECT_CH1();
//		AM2315UpdateValue();
//		I2C_SELECT_CH2();
//		BH1750UpdateValue();
//		}
	return; 
	}
void AM2315UpdateValue(void){											// TEMPERATURE_AIR + HUMIDITY_AIR
		DebugPutString("AM2315\r\n");
//uint16_t u16TemperatureAir;
//uint16_t u16HumidityAir;
		u16TemperatureAir=0xffff;u16HumidityAir=0xffff;
		I2C_Check=HAL_I2C_Master_Transmit(&hi2c1, 0xB8, &pu8DataRequest[1],3,0x01);
//		if(I2C_Check != HAL_ERROR) {
//			DebugPutString("step 1 failed\r\n");
//		}
		osDelay(2);
		// I2C_Check must be HAL_ERROR because sensor is in sleeping mode
		// after that sensor is out of sleep mode, transmit again 
		I2C_Check = HAL_I2C_Master_Transmit(&hi2c1, 0xB8, &pu8DataRequest[1],3,0x01);
//		if(I2C_Check != HAL_OK) {
//			DebugPutString("step 2 failed\r\n");
//		}
		osDelay(2);//delay 2ms
	  HAL_I2C_Master_Receive(&hi2c1, 0xB8, pu8DataSend, 8,0x0f);
		u16TemperatureAir = (pu8DataSend[4]*256+pu8DataSend[5])*10 ;
		u16HumidityAir	= (pu8DataSend[2]*256+pu8DataSend[3])*10 ;
		sprintf(temp,"%d do C, do am %d  \r\n",u16TemperatureAir,u16HumidityAir);
		DebugPutString(temp);
		memset(pu8DataSend,0x00,8);
		return;
}
/* BH1750 cam bien cuong do anh sang  */
void BH1750UpdateValue(void){ 										// AMBIENT_LIGHT
		DebugPutString("BH1750 \r\n");
//	uint16_t u16AmbientLight;
		u8BH1750_CF = 0x01;
		I2C_Check = HAL_I2C_Master_Transmit(&hi2c1, 0x46, &u8BH1750_CF,1,0x01);
		osDelay(180);
		u8BH1750_CF = 0x10;
		I2C_Check = HAL_I2C_Master_Transmit(&hi2c1, 0x46, &u8BH1750_CF,1,0x01);
		osDelay(180);
		pu8BH1750_rx[0]=0;
		pu8BH1750_rx[1]=0;
		I2C_Check=HAL_I2C_Master_Receive(&hi2c1, 0x47, pu8BH1750_rx, 2,0x0f);
		u16AmbientLight = (pu8BH1750_rx[0]*256+pu8BH1750_rx[1])/1.2 ;
		sprintf(temp,"cam bien light is %d lux\r\n",u16AmbientLight);
		DebugPutString(temp);
		memset(pu8BH1750_rx,0x00,2);
		return;
}



