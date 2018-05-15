#include "RspHandle.h"
#include "SerialTransmit.h"
#include "SlaveDefine.h"
#include "FlashRW.h"
#include <stdlib.h>

uint16_t u16TemperatureAir;
uint16_t u16HumidityAir;
uint16_t u16TemperatureSoil;
uint16_t u16MoistureSoil;
uint16_t u16AmbientLight;
uint16_t u16EcWater;
uint16_t u16PhWater;
uint16_t u16TemperatureWater;
uint16_t u16LevelWater;
uint16_t u16EcSoil;
uint16_t u16PhSoil;
uint16_t u16BuoyWater;

uint8_t u8Port1;
uint8_t u8Port2;
uint8_t u8Port3;
uint8_t u8Port4;

uint8_t u8Port1_channel1;
uint8_t u8Port2_channel1;
uint8_t u8Port3_channel1;
uint8_t u8Port4_channel1;
uint8_t u8Port1_channel2;
uint8_t u8Port2_channel2;
uint8_t u8Port3_channel2;
uint8_t u8Port4_channel2;

bool RspHandleMessage(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	DebugPutString("\r\nRspHandleMessage\r\n");
	/*check minimal message length*/
	if(u16Dlen<P_EOF_OFFSET)
	return false;
	DebugPutString("\r\nstep 1\r\n");		
	/*check preamble bytes*/
	if(pu8Data[P_PREAM_B1] != 0x55 || pu8Data[P_PREAM_B2] != 0x55) 
	return false;
DebugPutString("\r\nstep 2\r\n");	
	/*Cal data length */
	uint16_t DataLeng = pu8Data[P_DLEN_B1];
	DataLeng = (DataLeng<<8) + pu8Data[P_DLEN_B2];
	/*Check if message is not finish*/
	if((DataLeng+P_EOF_OFFSET)>u16Dlen) 
	return false;
DebugPutString("\r\nstep 3\r\n");	
	/*Check CRCH and CRCD*/
	uint8_t CRCH = CalCRC8(&pu8Data[P_DLEN_B1],8);
	if(CRCH!=pu8Data[P_CRCH])
	return false;
	DebugPutString("\r\nstep 4\r\n");	
	uint16_t CRCD = CalculateCRC16(&pu8Data[P_CRCH],DataLeng+1);
	if(	(CRCD>>8)	!=	pu8Data[P_CRCD_B1_OFFSET+DataLeng] ||	(CRCD&0x00FF) != pu8Data[P_CRCD_B2_OFFSET+DataLeng] ) 
		return false;
DebugPutString("\r\nstep 5\r\n");	
	/*check addr*/
	uint16_t DstAddr = pu8Data[P_DEST_B1];
	DstAddr = (DstAddr<<8) + pu8Data[P_DEST_B2];
DebugPutString("\r\nstep 6\r\n");
	DebugPutHex(DstAddr);
	DebugPutString("\nSensorBoxAddress\r\n");
	DebugPutHex(SensorBoxAddress);
	if(DstAddr==SensorBoxAddress) {
		DebugPutString("\r\nSensorBoxAddress\r\n");
		return RspHandleDirectMessage(&pu8Data[P_DATA_B1], DataLeng, msg);
		
	} else if (DstAddr == SLAVE_BROADCAST_ADDRESS) {
		DebugPutString("\r\SLAVE_BROADCAST_ADDRESS\r\n");	
		return RspHandleBroadcastMessage(&pu8Data[P_DATA_B1],DataLeng, msg);
	} else return false;
	DebugPutString("OK ");
}

bool RspHandleDirectMessage(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	DebugPutString("\r\nRspHandleDirectMessage\r\n");
	if(pu8Data[0]==MODE01)	{
		if(u16Dlen<2) return false;
		switch (pu8Data[1]) {
			case READ_SENSOR_ADDRESS:
				return RspHandleReadSlaveAddress(pu8Data+2,u16Dlen-2, msg);
				break;
			case READ_ALL_VALUE:
				return RspHandleReadSensorValue(pu8Data+2,u16Dlen-2, msg);
				break;
			case READ_RELAY_STATE:
				break;
			case READ_DIGITAL_INPUT_STATE:
				break;
			case READ_RTC_TIME:
				return RspHandleReadRtcTime(pu8Data+2,u16Dlen-2, msg);
				break;
			case WRITE_RTC_TIME:
				return RspHandleWriteRtcTime(pu8Data+2,u16Dlen-2, msg);
				break;
			case READ_RTC_DATE:
				return RspHandleReadRtcDate(pu8Data+2,u16Dlen-2, msg);
				break;
			case WRITE_RTC_DATE:
				return RspHandleWriteRtcDate(pu8Data+2,u16Dlen-2, msg);
				break;
			case GET_SENSORS_ON_PORT:
				return RspHandleGetSensorsOnPort(pu8Data+2,u16Dlen-2, msg);
				break;
			case SET_SENSORS_ON_PORT:
				return RspHandleSetSensorsOnPort(pu8Data+2,u16Dlen-2, msg);
				break;
			case CHANGE_SLAVE_ADDRESS:
				return RspHandleChangeSlaveAddress(pu8Data+2,u16Dlen-2, msg);
				break;
			case CHANGE_SENSOR_OFFSET:
				//return RspHandleChangeSensorsOffset(pu8Data+2,u16Dlen-2, msg);
				break;
			case READ_SENSOR_OFFSET:
				//return RspHandleReadSensorOffset(pu8Data+2,u16Dlen-2, msg);
				break;
			default: break;
		}
	}
	return false;
}

bool RspHandleBroadcastMessage(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	return false;
}


bool RspHandleReadSlaveAddress(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	char tmpStr[256];
	uint16_t Slaveaddress = SensorBoxAddress;
	//uint16_t Slaveaddress = ReadHalfWorldFromFlash(P_SLAVE_ADDRESS);
	uint8_t dataBuff[2] = {Slaveaddress>>8,Slaveaddress };
	RspResponseMessage(MODE01, READ_SENSOR_ADDRESS, dataBuff , 2 , msg);
	DebugPutString("\r\n RSP handle READ_SLAVE_ADDRESS");
	sprintf(tmpStr,"\r\n%0.4x",Slaveaddress);
	DebugPutString(tmpStr);
	return true;
}
bool RspHandleReadSensorValue(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	uint8_t pu8ValueSend[50];
	uint8_t u8NoBytes = 0;
	//pu8ValueSend[u8NoBytes++] = MODE01;
	//pu8ValueSend[u8NoBytes++] = READ_ALL_VALUE;

//#ifdef AIR_TEMP_HUMI
	pu8ValueSend[u8NoBytes++] = SENSOR_AIR_TEMPERATURE;
	pu8ValueSend[u8NoBytes++] = u16TemperatureAir >> 8;//Temperature_air_B1;
	pu8ValueSend[u8NoBytes++] = u16TemperatureAir & 0x00ff;//Temperature_air_B2;
	pu8ValueSend[u8NoBytes++] = SENSOR_AIR_HUMIDITY;
	pu8ValueSend[u8NoBytes++] = u16HumidityAir >> 8;//Humidity_air_B1;
	pu8ValueSend[u8NoBytes++] = u16HumidityAir & 0x00ff;//Humidity_air_B2;
//#endif

//#ifdef SOIL_TEMP_MOISTURE
	pu8ValueSend[u8NoBytes++] = SENSOR_SOIL_TEMPERATURE;
	pu8ValueSend[u8NoBytes++] = u16TemperatureSoil >> 8;//Temperature_soil_B1; 
	pu8ValueSend[u8NoBytes++] = u16TemperatureSoil & 0x00ff;//Temperature_soil_B2;
	pu8ValueSend[u8NoBytes++] = SENSOR_SOIL_MOISTURE;
	pu8ValueSend[u8NoBytes++] = u16MoistureSoil >> 8;//Moisture_soil_B1;
	pu8ValueSend[u8NoBytes++] = u16MoistureSoil & 0x00ff;//Moisture_soil_B2;
//#endif

//#ifdef LIGHT_AMBI
	pu8ValueSend[u8NoBytes++] = SENSOR_LIGHT_AMBIENT;
	pu8ValueSend[u8NoBytes++] = u16AmbientLight >> 8;//Ambient_light_B1;
	pu8ValueSend[u8NoBytes++] = u16AmbientLight & 0x00ff;//Ambient_light_B2;
//#endif

//#ifdef WATER_EC
	pu8ValueSend[u8NoBytes++] = SENSOR_WATER_EC;
	pu8ValueSend[u8NoBytes++] = u16EcWater >> 8;//EC_water_B1;
	pu8ValueSend[u8NoBytes++] = u16EcWater & 0x00ff;//EC_water_B2;
//#endif

//#ifdef WATER_PH
	pu8ValueSend[u8NoBytes++] = SENSOR_WATER_PH;
	pu8ValueSend[u8NoBytes++] = u16PhWater >> 8;//PH_water_B1;
	pu8ValueSend[u8NoBytes++] = u16PhWater & 0x00ff;//PH_water_B2;
//#endif

//#ifdef WATER_TEMP
	pu8ValueSend[u8NoBytes++] = SENSOR_WATER_TEMPERATURE;
	pu8ValueSend[u8NoBytes++] = u16TemperatureWater >> 8;//Temperature_water_B1;
	pu8ValueSend[u8NoBytes++] = u16TemperatureWater & 0x00ff;//Temperature_water_B2;
//#endif

//#ifdef WATER_LEVEL
	pu8ValueSend[u8NoBytes++] = SENSOR_WATER_LEVEL;
	pu8ValueSend[u8NoBytes++] = u16LevelWater >> 8;//Level_water_B1;
	pu8ValueSend[u8NoBytes++] = u16LevelWater & 0x00ff;//Level_water_B2;
//#endif

//#ifdef SOIL_EC
	pu8ValueSend[u8NoBytes++] = SENSOR_SOIL_EC;
	pu8ValueSend[u8NoBytes++] = u16EcSoil >> 8;//EC_soil_B1;
	pu8ValueSend[u8NoBytes++] = u16EcSoil & 0x00ff;//EC_soil_B2;
//#endif

//#ifdef SOIL_PH
	pu8ValueSend[u8NoBytes++] = SENSOR_SOIL_PH;
	pu8ValueSend[u8NoBytes++] = u16PhSoil >> 8;//PH_soil_B1;
	pu8ValueSend[u8NoBytes++] = u16PhSoil & 0x00ff;//PH_soil_B2;
//#endif

//#ifdef WATER_BUOY
	pu8ValueSend[u8NoBytes++] = SENSOR_WATER_BUOY;
	pu8ValueSend[u8NoBytes++] = u16BuoyWater >> 8;//PH_soil_B1;
	pu8ValueSend[u8NoBytes++] = u16BuoyWater & 0x00ff;//PH_soil_B2;
//#endif
	osDelay(10);
	RspResponseMessage(MODE01, READ_ALL_VALUE, pu8ValueSend , u8NoBytes , msg);
	DebugPutString("\r\n RSP handle READ_SLAVE_VALUES\n");
	char tmpStr[256];
	sprintf (tmpStr,"air_temp %d\r\n air_humidity %d\r\n soil_temp %d\r\n soil_mois %d\r\n light_ambi %d\r\n water_EC %d\r\n water_PH %d\r\n water_tmp %d\r\n water_level %d\r\n soil_EC %d\r\n soil_PH %d\r\n water_Buoy %d\r\n",
								u16TemperatureAir,
								u16HumidityAir,
								u16TemperatureSoil,
								u16MoistureSoil,
								u16AmbientLight,
								u16EcWater,
								u16PhWater,
								u16TemperatureWater,
								u16LevelWater,
								u16EcSoil,
								u16PhSoil,
								u16BuoyWater);
	DebugPutString(tmpStr);
	sprintf(tmpStr,"\nbytevalues %d",u8NoBytes);
	DebugPutString(tmpStr);
	for(int i=0;i<u8NoBytes;i++)
	{
		sprintf(tmpStr,"\nvalues %.2x",pu8ValueSend[i]);
		DebugPutString(tmpStr);
	}
	return true;
}

bool RspHandleReadRtcTime(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	char tmpStr[256];
	RTC_TimeTypeDef time;
	HAL_RTC_GetTime(&hrtc,&time,RTC_FORMAT_BIN);
	uint8_t dataBuff[3] = {time.Hours, time.Minutes, time.Seconds};
	RspResponseMessage(MODE01, READ_RTC_TIME, dataBuff , 3 , msg);
	DebugPutString("\r\nRSP handle READ_RTC_TIME");
	sprintf(tmpStr,"\r\n\tTime:\t%02u:%02u:%02u",time.Hours, time.Minutes, time.Seconds);
	DebugPutString(tmpStr);
	return true;
}
bool RspHandleWriteRtcTime(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	char tmpStr[256];
	if(u16Dlen<3) return false;
	RTC_TimeTypeDef time;
	if(pu8Data[0] > 23) return false;
	if(pu8Data[1] > 59) return false;
	if(pu8Data[2] > 59) return false;
	time.Hours = pu8Data[0];
	time.Minutes = pu8Data[1];
	time.Seconds = pu8Data[2];
	HAL_RTC_SetTime(&hrtc,&time,RTC_FORMAT_BIN);
	RspResponseMessage(MODE01, WRITE_RTC_TIME, pu8Data, 3, msg);
	DebugPutString("\r\nRSP Handle WRITE_RTC_TIME");
	sprintf(tmpStr,"\r\n\tTime\t%02u:%02u:%02u",time.Hours, time.Minutes, time.Seconds);
	DebugPutString(tmpStr);
	return true;
}

bool RspHandleReadRtcDate(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	RTC_DateTypeDef date;
	HAL_RTC_GetDate(&hrtc,&date,RTC_FORMAT_BIN);
	uint8_t dataBuff[4] = {date.WeekDay, date.Date , date.Month, date.Year};
	RspResponseMessage(MODE01, READ_RTC_DATE, dataBuff, 4, msg);
	DebugPutString("\r\nRSP Handle READ_RTC_DATE");
	DebugPutString("\r\n\tDate\t");
	switch(date.WeekDay){
		case RTC_WEEKDAY_SUNDAY:
			DebugPutString("SUN"); break;
		case RTC_WEEKDAY_MONDAY:
			DebugPutString("MON"); break;
		case RTC_WEEKDAY_TUESDAY:
			DebugPutString("TUE"); break;
		case RTC_WEEKDAY_WEDNESDAY:
			DebugPutString("WED"); break;
		case RTC_WEEKDAY_THURSDAY:
			DebugPutString("THU"); break;
		case RTC_WEEKDAY_FRIDAY:
			DebugPutString("FRI"); break;
		case RTC_WEEKDAY_SATURDAY:
			DebugPutString("SAT"); break;
		default: 
			DebugPutString("ERROR"); break;
	}
	char tmpStr[256];
	sprintf(tmpStr," %02u/%02u/%02u",date.Date,date.Month,date.Year);
	DebugPutString(tmpStr);
	return true;
}


bool RspHandleWriteRtcDate(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	char tmpStr[256];
	if(u16Dlen<4) return false;
//	if(pu8Data[0]>=7) return false;
//	if(pu8Data[1]==0 || pu8Data[1]>31) return false;
//	if(pu8Data[2]==0 || pu8Data[2]>12) return false;
//	if(pu8Data[3]>99) return false;
	RTC_DateTypeDef date;
	date.WeekDay = pu8Data[0];
	date.Date = pu8Data[1];
	date.Month = pu8Data[2];
	date.Year = pu8Data[3];
	HAL_RTC_SetDate(&hrtc,&date,RTC_FORMAT_BIN);
	RspResponseMessage(MODE01,WRITE_RTC_DATE,pu8Data,4,msg);
	uint32_t dateToStore;
	memcpy(&dateToStore,&hrtc.DateToUpdate,4);
	BKP->DR2 = dateToStore >> 16;
	BKP->DR3 = dateToStore & 0xffff;
	DebugPutString("\r\nRSP Handle message WRITE_RTC_DATE");
	DebugPutString("\r\n\tDate\t");
	switch(date.WeekDay){
		case RTC_WEEKDAY_SUNDAY:
			DebugPutString("SUN"); break;
		case RTC_WEEKDAY_MONDAY:
			DebugPutString("MON"); break;
		case RTC_WEEKDAY_TUESDAY:
			DebugPutString("TUE"); break;
		case RTC_WEEKDAY_WEDNESDAY:
			DebugPutString("WED"); break;
		case RTC_WEEKDAY_THURSDAY:
			DebugPutString("THU"); break;
		case RTC_WEEKDAY_FRIDAY:
			DebugPutString("FRI"); break;
		case RTC_WEEKDAY_SATURDAY:
			DebugPutString("SAT"); break;
		default: 
			DebugPutString("ERROR"); break;
	}
	sprintf(tmpStr," %02u/%02u/%02u",date.Date,date.Month,date.Year);
	DebugPutString(tmpStr);
	
	return true;
}



bool RspHandleChangeSlaveAddress(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	char tmpStr[256];
	uint16_t newSlaveAddress = (pu8Data[0]<<8) + pu8Data[1];
	ErasePage( DATA_PAGE_NUMBER );
	g_FlashData.slaveAddress = newSlaveAddress;
	uint8_t pu8SuscessResponse[7] = { 0x01, 0x25, 0xC0, 0xFF, 0xEE, 0x25, 0x07};
	updateFlashData();
	RspResponseMessage(MODE01,CHANGE_SLAVE_ADDRESS,pu8SuscessResponse,7,msg);
	sprintf(tmpStr,"slave was changed address to 0x%04x \r\n", newSlaveAddress);
	DebugPutString(tmpStr);
	return true;
}

bool RspHandleGetSensorsOnPort(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	
	uint8_t pu8ValueSend[50];
	uint8_t u8NoBytes = 0;
	pu8ValueSend[u8NoBytes++] = u8Port1;
	pu8ValueSend[u8NoBytes++] = u8Port1_channel1;
	pu8ValueSend[u8NoBytes++] = u8Port1_channel2;
	pu8ValueSend[u8NoBytes++] = u8Port2;
	pu8ValueSend[u8NoBytes++] = u8Port2_channel1;
	pu8ValueSend[u8NoBytes++] = u8Port2_channel2;
	pu8ValueSend[u8NoBytes++] = u8Port3;
	pu8ValueSend[u8NoBytes++] = u8Port3_channel1;
	pu8ValueSend[u8NoBytes++] = u8Port3_channel2;
	pu8ValueSend[u8NoBytes++] = u8Port4;
	pu8ValueSend[u8NoBytes++] = u8Port4_channel1;
	pu8ValueSend[u8NoBytes++] = u8Port4_channel2;
	
	osDelay(10);
	RspResponseMessage(MODE01, GET_SENSORS_ON_PORT, pu8ValueSend , u8NoBytes , msg);
	DebugPutString("\r\nGet Sensor On Port\r\n");
	return true;
}

bool RspHandleSetSensorsOnPort(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	ErasePage( DATA_PAGE_NUMBER );
	if(pu8Data[0]==u8Port1)
		{
			DebugPutString("\r\nSet Port 1\r\n");
			g_FlashData.port1_channel1=pu8Data[1];
			g_FlashData.port1_channel2=pu8Data[2];
		}
	else if(pu8Data[0]==u8Port2)
		{
			DebugPutString("\r\nSet Port 2\r\n");
			g_FlashData.port2_channel1=pu8Data[1];
			g_FlashData.port2_channel2=pu8Data[2];
		}
	else if(pu8Data[0]==u8Port3)
		{
			DebugPutString("\r\nSet Port 3\r\n");
			g_FlashData.port3_channel1=pu8Data[1];
			g_FlashData.port3_channel2=pu8Data[2];
		}
	else if(pu8Data[0]==u8Port4)
		{
			DebugPutString("\r\nSet Port 4\r\n");
			g_FlashData.port4_channel1=pu8Data[1];
			g_FlashData.port4_channel2=pu8Data[2];
		}
	
	updateFlashData();
	uint8_t pu8SuscessResponse[7] = { 0x01, 0x25, 0xC0, 0xFF, 0xEE, 0x25, 0x07};
	RspResponseMessage(MODE01,SET_SENSORS_ON_PORT,pu8SuscessResponse,7,msg);
	
	return true;
}

static uint8_t pu8TxRspBuff[128];
bool RspResponseMessage(uint8_t u8Cmd, uint8_t u8Subcmd, uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg){
	memset(pu8TxRspBuff,0,128);
	pu8TxRspBuff[P_PREAM_B1] = 0x55;
	pu8TxRspBuff[P_PREAM_B2] = 0x55;
	pu8TxRspBuff[P_DLEN_B1] = (u16Dlen+2) >> 8;
	pu8TxRspBuff[P_DLEN_B2] = (u16Dlen+2) & 0x00ff;
	pu8TxRspBuff[P_FLAG] = 0;
	pu8TxRspBuff[P_SEQ] = 0;
	pu8TxRspBuff[P_DEST_B1] = DEFAULT_MASTER_ADDRESS >> 8;
	pu8TxRspBuff[P_DEST_B2] = DEFAULT_MASTER_ADDRESS & 0x00ff;
	pu8TxRspBuff[P_SRC_B1] = SensorBoxAddress >> 8;
	pu8TxRspBuff[P_SRC_B2] = SensorBoxAddress & 0x00ff;
	pu8TxRspBuff[P_CRCH] = CalCRC8(&pu8TxRspBuff[P_DLEN_B1],8);
	pu8TxRspBuff[P_DATA_B1] = u8Cmd;
	pu8TxRspBuff[P_DATA_B1+1]  = u8Subcmd;
	for(int i = 0; i< u16Dlen; i++) {
		pu8TxRspBuff[P_DATA_B1+i+2] = pu8Data[i];
	}
	uint16_t CRCD = CalculateCRC16(&pu8TxRspBuff[P_CRCH],u16Dlen+3);
	pu8TxRspBuff[P_CRCD_B1_OFFSET + 2 + u16Dlen] =  CRCD >> 8;
	pu8TxRspBuff[P_CRCD_B2_OFFSET + 2 + u16Dlen] =  CRCD & 0x00ff;
	pu8TxRspBuff[P_EOF_OFFSET + 2 + u16Dlen] = 0xFF;
	
	for(int i=0;i<(P_EOF_OFFSET + 3 + u16Dlen);i++){
		if(msg==MESSAGE_TYPE_RF) ZigbeePutChar(pu8TxRspBuff[i]);
		else if(msg==MESSAGE_TYPE_RS485) Rs485PutChar(pu8TxRspBuff[i]);
	}
	for(int i=0;i<(P_EOF_OFFSET+3+u16Dlen);i++)
	{
		DebugPutHex(pu8TxRspBuff[i]);
	}
	return true;
}


//uint16_t GetSlaveAddress(void){
//	//return ReadHalfWorldFromFlash(P_SLAVE_ADDRESS);
//	return SensorBoxAddress;
//}

inline void updateFlashData(void){
	//DebugPutString("\r\nUpdateFlash");
	char temp[256];
	ErasePage(DATA_PAGE_NUMBER);
	HAL_FLASH_Unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_SLAVE_ADDRESS, 			g_FlashData.slaveAddress		);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_AIR_TEMP_OFFSET, 		g_FlashData.airTempOffset		);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_AIR_HUMI_OFFSET,		g_FlashData.airHumiOffset		);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_SOIL_TEMP_OFFSET,		g_FlashData.soilTempOffset	);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_SOIL_MOIS_OFFSET, 	g_FlashData.soilMoisOffset	);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_LIGHT_AMBI_OFFSET,	g_FlashData.lightAmbiOffset	);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_WATER_EC_OFFSET, 		g_FlashData.waterEcOffset		);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_WATER_PH_OFFSET,		g_FlashData.waterPhOffset		);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_WATER_TEMP_OFFSET,	g_FlashData.waterTempOffset	);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_WATER_LEVEL_OFFSET, g_FlashData.waterLevelOffset);	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_SOIL_EC_OFFSET,			g_FlashData.soilEcOffset		);	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_SOIL_PH_OFFSET,			g_FlashData.soilPhOffset		);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_WATER_LEVEL_RATIO,	g_FlashData.waterLevelRatio	);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_WATER_EC_RATIO,			g_FlashData.waterECRatio		);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_WATER_EC_PROBE,			g_FlashData.waterECProbe		);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_Port1_OFFSET,				g_FlashData.port1);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_Port2_OFFSET,				g_FlashData.port2);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_Port3_OFFSET,				g_FlashData.port3);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_Port4_OFFSET,				g_FlashData.port4);
	
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_Port1_channel_1,				g_FlashData.port1_channel1);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_Port1_channel_2,				g_FlashData.port1_channel2);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_Port2_channel_1,				g_FlashData.port2_channel1);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_Port2_channel_2,				g_FlashData.port2_channel2);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_Port3_channel_1,				g_FlashData.port3_channel1);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_Port3_channel_2,				g_FlashData.port3_channel2);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_Port4_channel_1,				g_FlashData.port4_channel1);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, P_Port4_channel_2,				g_FlashData.port4_channel2);
	
	
	sprintf ( temp, "\r\nport 1 =  0x%02x\r\n",ReadHalfWorldFromFlash(P_Port1_OFFSET));
	DebugPutString(temp);
	sprintf ( temp, "\r\nport 1 channel 1=  0x%02x\r\n",ReadHalfWorldFromFlash(P_Port1_channel_1));
	DebugPutString(temp);
	sprintf ( temp, "\r\nport 1 channel 2=  0x%02x\r\n",ReadHalfWorldFromFlash(P_Port1_channel_2));
	DebugPutString(temp);
	
	sprintf ( temp, "\r\nport 2 =  0x%02x\r\n",ReadHalfWorldFromFlash(P_Port2_OFFSET));
	DebugPutString(temp);
	sprintf ( temp, "\r\nport 2 channel 1=  0x%02x\r\n",ReadHalfWorldFromFlash(P_Port2_channel_1));
	DebugPutString(temp);
	sprintf ( temp, "\r\nport 2 channel 2=  0x%02x\r\n",ReadHalfWorldFromFlash(P_Port2_channel_2));
	DebugPutString(temp);
	
	sprintf ( temp, "\r\nport 3 =  0x%02x\r\n",ReadHalfWorldFromFlash(P_Port3_OFFSET));
	DebugPutString(temp);
	
	sprintf ( temp, "\r\nport 3 channel 1=  0x%02x\r\n",ReadHalfWorldFromFlash(P_Port3_channel_1));
	DebugPutString(temp);
	sprintf ( temp, "\r\nport 3 channel 2=  0x%02x\r\n",ReadHalfWorldFromFlash(P_Port3_channel_2));
	DebugPutString(temp);
	
	sprintf ( temp, "\r\nport 4 =  0x%02x\r\n",ReadHalfWorldFromFlash(P_Port4_OFFSET));
	DebugPutString(temp);
	
	sprintf ( temp, "\r\nport 4 channel 1=  0x%02x\r\n",ReadHalfWorldFromFlash(P_Port4_channel_1));
	DebugPutString(temp);
	sprintf ( temp, "\r\nport 4 channel 2=  0x%02x\r\n",ReadHalfWorldFromFlash(P_Port4_channel_2));
	DebugPutString(temp);
	
	
	HAL_FLASH_Lock();
	#ifdef DEBUG_ACTIVE
	sprintf ( temp, "slave address 0x%04x\r\n"
									"air temp offset 0x%04x\r\n"
									"air humi offset 0x%04x\r\n"
									"soil temp offset 0x%04x\r\n"
									"soil mois offset 0x%04x\r\n"
									"light ambi offset 0x%04x\r\n"
									"water Ec offset 0x%04x\r\n"
									"water Ph offset 0x%04x\r\n"
									"water temp offset 0x%04x\r\n"
									"water level offset 0x%04x\r\n"
									"soil Ec offset 0x%04x\r\n"
									"soil Ph offset 0x%04x\r\n"
									"water Level ratio 0x%04x\r\n"
									"water EC ratio 0x%04x\r\n"
									"water EC probe 0x%04x\r\n",
									ReadHalfWorldFromFlash(P_SLAVE_ADDRESS), ReadHalfWorldFromFlash(P_AIR_TEMP_OFFSET), ReadHalfWorldFromFlash(P_AIR_HUMI_OFFSET), 
									ReadHalfWorldFromFlash(P_SOIL_TEMP_OFFSET), ReadHalfWorldFromFlash(P_SOIL_MOIS_OFFSET), ReadHalfWorldFromFlash(P_LIGHT_AMBI_OFFSET),
									ReadHalfWorldFromFlash(P_WATER_EC_OFFSET), ReadHalfWorldFromFlash(P_WATER_PH_OFFSET), ReadHalfWorldFromFlash(P_WATER_TEMP_OFFSET),
									ReadHalfWorldFromFlash(P_WATER_LEVEL_OFFSET), ReadHalfWorldFromFlash(P_SOIL_EC_OFFSET), ReadHalfWorldFromFlash(P_SOIL_PH_OFFSET),
									ReadHalfWorldFromFlash(P_WATER_LEVEL_RATIO), ReadHalfWorldFromFlash(P_WATER_EC_RATIO),ReadHalfWorldFromFlash(P_WATER_EC_PROBE));
	DebugPutString(temp);
	#endif
}
void initFlashData(void){
	g_FlashData.slaveAddress=ReadHalfWorldFromFlash(P_SLAVE_ADDRESS);
	
if (g_FlashData.slaveAddress==0xffff) {
	SensorBoxAddress =	g_FlashData.slaveAddress 			= DEFAULT_SLAVE_ADDRESS;
		g_FlashData.airTempOffset 		= 0x0000;
		g_FlashData.airHumiOffset 		= 0x0000;
		g_FlashData.soilTempOffset 		= 0x0000;
		g_FlashData.soilMoisOffset 		= 0x0000;
		g_FlashData.lightAmbiOffset 	= 0x0000;
		g_FlashData.waterEcOffset 		= 0x0000;
		g_FlashData.waterPhOffset 		= 0x0000;
		g_FlashData.waterTempOffset 	= 0x0000;
		g_FlashData.waterLevelOffset 	= 0x00C8; // 200mm
		g_FlashData.soilEcOffset 			= 0x0000;
		g_FlashData.soilPhOffset 			= 0x0000;
		g_FlashData.waterLevelRatio   = 0x00C8;	// 200 mm/V
		g_FlashData.waterECRatio			= 0x0064;	// 100%
		g_FlashData.waterECProbe			= 0x0000;
	
		u8Port1 = g_FlashData.port1 	= 1;
		u8Port2 = g_FlashData.port2  = 2;
		u8Port3 = g_FlashData.port3 	= 3;
		u8Port4 = g_FlashData.port4  = 4;
		DebugPutString("\r\nslaveAddress==0xffff\r\n");
	}	
	SensorBoxAddress = g_FlashData.slaveAddress;
	g_FlashData.airTempOffset 		= 	u16TemperatureAir;
	g_FlashData.airHumiOffset 		= 	u16HumidityAir;
	g_FlashData.soilTempOffset		=  	u16TemperatureSoil;
	g_FlashData.soilMoisOffset 		=  	u16MoistureSoil; 
	g_FlashData.lightAmbiOffset 	= 	u16AmbientLight;
	g_FlashData.waterEcOffset 		= 	u16EcWater;
	g_FlashData.waterPhOffset 		=  	u16PhWater;
	g_FlashData.waterTempOffset 	= 	u16TemperatureWater;
	g_FlashData.waterLevelOffset 	= 	u16LevelWater;
	g_FlashData.soilEcOffset 			= 	u16EcSoil;
	g_FlashData.soilPhOffset 			= 	u16PhSoil;
	g_FlashData.waterLevelRatio   = 	u16BuoyWater;
	g_FlashData.waterECRatio			= 	ReadHalfWorldFromFlash(P_WATER_EC_RATIO);
	g_FlashData.waterECProbe			= 	ReadHalfWorldFromFlash(P_WATER_EC_PROBE);
	//port
//	u8Port1 = g_FlashData.port1 	=   ReadHalfWorldFromFlash(P_Port1_OFFSET);
//	u8Port2 = g_FlashData.port2 	=   ReadHalfWorldFromFlash(P_Port2_OFFSET);
//	u8Port3 = g_FlashData.port3 	=   ReadHalfWorldFromFlash(P_Port3_OFFSET);
//	u8Port4 = g_FlashData.port4 	=   ReadHalfWorldFromFlash(P_Port4_OFFSET);
	u8Port1 = g_FlashData.port1 	=   1;
	u8Port2 = g_FlashData.port2 	=   2;
	u8Port3 = g_FlashData.port3 	=   3;
	u8Port4 = g_FlashData.port4 	=   4;
	// channel 
	u8Port1_channel1 = g_FlashData.port1_channel1 = ReadHalfWorldFromFlash(P_Port1_channel_1);
	u8Port1_channel2 = g_FlashData.port1_channel2 = ReadHalfWorldFromFlash(P_Port1_channel_2);
	u8Port2_channel1 = g_FlashData.port2_channel1 = ReadHalfWorldFromFlash(P_Port2_channel_1);
	u8Port2_channel2 = g_FlashData.port2_channel2 = ReadHalfWorldFromFlash(P_Port2_channel_2);
	u8Port3_channel1 = g_FlashData.port3_channel1 = ReadHalfWorldFromFlash(P_Port3_channel_1);
	u8Port3_channel2 = g_FlashData.port3_channel2 = ReadHalfWorldFromFlash(P_Port3_channel_2);
	u8Port4_channel1 = g_FlashData.port4_channel1 = ReadHalfWorldFromFlash(P_Port4_channel_1);
	u8Port4_channel2 = g_FlashData.port4_channel2 = ReadHalfWorldFromFlash(P_Port4_channel_2);
	
	updateFlashData();

}
