/**
	* @file name: RspProtocol.h
	* @writen by: L.A.Binh email binhl.ahg@gmail.com 
	* @from date  
	* @to date
	* @intruction:  https://drive.google.com/file/d/0B0lOCyzINV8BWno1UHBRWU5sUFE/view
	* @password: 		ahg@2017
	*/

#ifndef __RSP_PROTOCOL_H
#define __RSP_PROTOCOL_H
/*
---------------------------------------------------------------------------------------------------------------------
| preamble 	| DLEN      | FLAG		|	SEQ     	|	DEST      | SRC     	| CRCH    	| DATA 				|	CRCD     	|	EOF		|
| 2 bytes		|	2 bytes		|	1 byte	|	1 byte		|	2 bytes		|	2 bytes		|	1 byte		|	dlen bytes	|	2 bytes		| 1byte	|
---------------------------------------------------------------------------------------------------------------------
| 0x55;0x55 | data leng |         | sequence  |destination| source    | CRC from  | data        | CRC from  |  0xff |
|           |           |         |           |address    | address   | DLEN      |             | CRCH      |       |
---------------------------------------------------------------------------------------------------------------------
flag
------------------------------------------------------------------------------
| bit |   0   		|   1  		 |   2   |   3   |   4   |   5   |   6   |   7   |
------------------------------------------------------------------------------
|  0  | DATA MESS |  no ACK  |   r   |   r   |   r   |   r   |   r   |   r   |
------------------------------------------------------------------------------
|  1  | CMD MESS  |   ACK    |   r   |   r   |   r   |   r   |   r   |   r   |
------------------------------------------------------------------------------
*/

#include "CRC16.h"
#include "CRC8.h"

#define P_PREAM_B1				0
#define P_PREAM_B2				1
#define P_DLEN_B1					2
#define P_DLEN_B2					3
#define P_FLAG						4
#define P_SEQ							5
#define P_DEST_B1					6
#define P_DEST_B2					7
#define P_SRC_B1					8
#define P_SRC_B2					9
#define P_CRCH						10
#define P_DATA_B1					11
#define P_CRCD_B1_OFFSET	11
#define P_CRCD_B2_OFFSET	12
#define P_EOF_OFFSET			13

#define ENDOF						0xff
#define PREAMBLE				0x55
#define FLAG						0x00
#define FLAG_CMD_MESS 	0x80
#define FLAG_ACK				0x40

/*
	cmd mode 01
*/
#define MODE01  								0x01
#define READ_SENSOR_ADDRESS			0x01
#define READ_ALL_VALUE 					0x02
#define READ_RELAY_STATE				0x03
#define READ_DIGITAL_INPUT_STATE	0x04
#define READ_RTC_TIME						0x05
#define WRITE_RTC_TIME					0x06
#define READ_RTC_DATE						0x07
#define WRITE_RTC_DATE					0x08
#define GET_SENSORS_ON_PORT			0x09
#define SET_SENSORS_ON_PORT			0x0A
#define CHANGE_SLAVE_ADDRESS 		0x25
#define CHANGE_SENSOR_OFFSET		0x28
#define READ_SENSOR_OFFSET			0x29

/*
	cmd mode 03
*/
#define MODE03									0x03
#define PING										0x01
#define PONG										0x02
/*
	cmd mode 06
*/
#define MODE06									0x06
#define WRITE_ALL_RELAY					0x01
#define WRITE_SINGLE_RELAY			0x02

/*
	sensor type
*/

#define SENSOR_AIR_TEMPERATURE		0x01
#define SENSOR_AIR_HUMIDITY				0x02
#define SENSOR_SOIL_TEMPERATURE		0x03
#define SENSOR_SOIL_MOISTURE			0x04
#define SENSOR_LIGHT_AMBIENT			0x05
#define SENSOR_WATER_EC						0x06
#define SENSOR_WATER_PH						0x07
#define SENSOR_WATER_TEMPERATURE 	0x08
#define SENSOR_WATER_LEVEL				0x09
#define SENSOR_SOIL_EC						0x0A
#define SENSOR_SOIL_PH						0x0B
#define SENSOR_WATER_BUOY					0x0C
#define SENSOR_WATER_LEVEL_RATIO  0x0D
#define SENSOR_WATER_EC_RATIO			0x0E
#define SENSOR_WATER_EC_PROBE			0x0F

//#define DEFAULT_SLAVE_ADDRESS		0x0001
//#define DEFAULT_MASTER_ADDRESS	0x00ff
#define SLAVE_BROADCAST_ADDRESS	0xffff

#define MASTER_ADD_B1		0x00
#define MASTER_ADD_B2		0xff
#define SLAVE_ADD_B1		0x00
#define SLAVE_ADD_B2		0x01
#define SLAVE_ADD_BROADCAST_B1	0xff
#define SLAVE_ADD_BROADCAST_B2	0xff

#endif
