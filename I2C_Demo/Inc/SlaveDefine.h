/**
	* @file name: SlaveDefine.h
	* @writen by: L.A.Binh email binhl.ahg@gmail.com 
	* @from date  
	* @to date
	*/
#ifndef __SLAVE_DEFINE_H
#define __SLAVE_DEFINE_H
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "SensorDelcoDefine.h"

/* brief:
 * this file include the constant value using for slave divices using in RSP
 *
*/
/*
 * define datapage is page 63, 
 * start at register number 24 of page 63 --> just because i like
*/

#define DATA_PAGE_NUMBER 					63 					//	last Page to store data
#define P_SLAVE_ADDRESS 					0x0800FC24	//	pointer to slave_address
#define P_AIR_TEMP_OFFSET					0x0800FC26  //	pointer to air_temp_offset
#define P_AIR_HUMI_OFFSET					0x0800FC28	//	pointer to air_humi_offset 
#define P_SOIL_TEMP_OFFSET				0x0800FC2A	//	pointer to soil_temp_offset
#define P_SOIL_MOIS_OFFSET				0x0800FC2C	//	pointer to soil_mois_offset
#define P_LIGHT_AMBI_OFFSET				0x0800FC2E	//	pointer to light_ambi_offset
#define P_WATER_EC_OFFSET					0x0800FC30	//	pointer to water_EC_offset
#define P_WATER_PH_OFFSET					0x0800FC32	//	pointer to water_PH_offset
#define P_WATER_TEMP_OFFSET				0x0800FC34	//	pointer to water_temp_offset
#define P_WATER_LEVEL_OFFSET			0x0800FC36	//	pointer to water_level_offset
#define P_SOIL_EC_OFFSET					0x0800FC38	//	pointer to soil_ec_offsetz
#define P_SOIL_PH_OFFSET					0x0800FC3A	//	pointer to soil_ph_offset 58
#define P_WATER_LEVEL_RATIO				0x0800FC3C	//	pointer to water_level_ratio 60
#define P_WATER_EC_RATIO					0x0800FC3E	//	pointer to water_EC_ratio 62
#define P_WATER_EC_PROBE					0x0800FC40	//	pointer to water_EC_probe

//Tuyen define 2018/05/14 
#define P_Port1_OFFSET 						0x0800FC64 
#define P_Port2_OFFSET 						0x0800FC66
#define P_Port3_OFFSET 						0x0800FC68
#define P_Port4_OFFSET 						0x0800FC70
#define P_Port1_channel_1					0x0800FC72
#define P_Port1_channel_2					0x0800FC74
#define P_Port2_channel_1					0x0800FC76
#define P_Port2_channel_2					0x0800FC78
#define P_Port3_channel_1					0x0800FC80
#define P_Port3_channel_2					0x0800FC82
#define P_Port4_channel_1					0x0800FC84
#define P_Port4_channel_2					0x0800FC86




#define DEFAULT_SLAVE_ADDRESS		0x0001
#define DEFAULT_MASTER_ADDRESS	0x00ff

#define MASTER_ADD_B1		0x00
#define MASTER_ADD_B2		0xff
#define SLAVE_ADD_B1		0x00
#define SLAVE_ADD_B2		0x01
#define SLAVE_ADD_BROADCAST_B1	0xff
#define SLAVE_ADD_BROADCAST_B2	0xff



//#define TEST_CASE
//#define DEBUG_ACTIVE
//#define ERASE_FLASH_DATA

#ifdef TEST_CASE

#define AM2315_ACTIVE 		// air temperature + humidity
#define DS18B20_ACTIVE		// water temperature
//#define BH1750_ACTIVE			// light ambient
//#define MC3204_ACTIVE			// scan 4 ADC channel
//#define DFR0300_ACTIVE    // water EC
#define HI7634_ACTIVE			// water EC
//#define SEN0161_ACTIVE    // water PH
//#define RK520_01_ACTIVE   // soil temperature + moisture
//#define RK500_02_ACTIVE   // soil PH
#define RK500_03_ACTIVE   // soil EC
//#define UA18CAD22_ACTIVE	// water Level

#define AIR_TEMP_HUMI
#define SOIL_TEMP_MOISTURE
#define LIGHT_AMBI
#define WATER_EC
#define WATER_PH
#define WATER_TEMP
#define WATER_LEVEL
#define SOIL_EC
#define SOIL_PH
#define WATER_BUOY
#endif

//Tuyen define 2018/05/14
//#define AM2315 = 0x0001;
//#define SHT71  = 2;
//#define SHT11  = 3;
//#define BH1750 = 4;

typedef struct s_flashData{
	uint16_t slaveAddress;				
	uint16_t airTempOffset;
	uint16_t airHumiOffset;
	uint16_t soilTempOffset;
	uint16_t soilMoisOffset;
	uint16_t lightAmbiOffset;
	uint16_t waterEcOffset;
	uint16_t waterPhOffset;
	uint16_t waterTempOffset;
	uint16_t waterLevelOffset;
	uint16_t soilEcOffset;
	uint16_t soilPhOffset;
	uint16_t waterLevelRatio;
	uint16_t waterECRatio;
	uint16_t waterECProbe;
	uint8_t port1;
	uint8_t port2;
	uint8_t port3;
	uint8_t port4;
	uint8_t port1_channel1;
	uint8_t port2_channel1;
	uint8_t port3_channel1;
	uint8_t port4_channel1;
	uint8_t port1_channel2;
	uint8_t port2_channel2;
	uint8_t port3_channel2;
	uint8_t port4_channel2;	
}flashData;
extern flashData g_FlashData;
extern uint8_t g_SlaveReset;


#endif
