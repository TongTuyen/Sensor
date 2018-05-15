/**
	* @file name:
	* @writen by: L.A.Binh email binhl.ahg@gmail.com 
	* @from date  
	* @to date
	*/

#ifndef __SENSOR_DELCO_DEFINE_H
#define __SENSOR_DELCO_DEFINE_H
/*
SN_type_1	
	EC nuoc		MCP3204 - CH0
	pH nuoc		MCP3204 - CH1
	nhiet do nuoc				GPIO - PIN ???
	phao bao muc nuoc		GPIO - PIN ???
SN_type_2	
	nhiet do, do am khong khi	I2C
	cuong do ánh sáng		I2C
SN_type_3	
	EC nuoc		MCP3204 - CH0
	Sieu am do muc nuoc		MCP3204 - CH3
SN_type_4	
	nhiet do, do am dat		MCP3204 - CH0 + MCP3204 - CH1
	EC dat		MCP3204 - CH2
	pH dat		MCP3204 - CH3
SN_type_5	
	nhiet do, do am dat		MCP3204 - CH0 + MCP3204 - CH1
	EC dat		MCP3204 - CH2
	pH dat		MCP3204 - CH3
	nhiet do, do am không khí		I2C
	cuong do ánh sáng		I2C
SN_type_6	
	pH nuoc		MCP3204 - CH1
*/

//#define SN_TYPE_1
//#define SN_TYPE_2
//#define SN_TYPE_3
//#define SN_TYPE_4
//#define SN_TYPE_5
//#define SN_TYPE_6

#ifdef SN_TYPE_1
#define WATER_EC
#define WATER_PH
#define WATER_TEMP
#define WATER_BUOY
#endif

#ifdef SN_TYPE_2
#define AIR_TEMP_HUMI
#define LIGHT_AMBI
#endif

#ifdef SN_TYPE_3
#define WATER_TEMP
#define WATER_EC
#define WATER_LEVEL
#endif

#ifdef SN_TYPE_4
#define SOIL_TEMP_MOISTURE
#define SOIL_EC
#define SOIL_PH
#endif

#ifdef SN_TYPE_5
#define SOIL_TEMP_MOISTURE
#define SOIL_EC
#define SOIL_PH
#define AIR_TEMP_HUMI
#define LIGHT_AMBI
#endif

#ifdef SN_TYPE_6
#define WATER_PH
#endif

#endif
