#ifndef __RSP_HANDLE_H
#define __RSP_HANDLE_H

#include "DeviceDefine.h"
#include "RspProtocol.h"

extern QueueHandle_t xRxRspQueue;
extern uint16_t u16TemperatureAir;
extern uint16_t u16HumidityAir;
extern uint16_t u16TemperatureSoil;
extern uint16_t u16MoistureSoil;
extern uint16_t u16AmbientLight;
extern uint16_t u16EcWater;
extern uint16_t u16PhWater;
extern uint16_t u16TemperatureWater;
extern uint16_t u16LevelWater;
extern uint16_t u16EcSoil;
extern uint16_t u16PhSoil;
extern uint16_t u16BuoyWater;

extern uint8_t u8Port1;
extern uint8_t u8Port2;
extern uint8_t u8Port3;
extern uint8_t u8Port4;
extern uint8_t u8Port1_channel1;
extern uint8_t u8Port2_channel1;
extern uint8_t u8Port3_channel1;
extern uint8_t u8Port4_channel1;
extern uint8_t u8Port1_channel2;
extern uint8_t u8Port2_channel2;
extern uint8_t u8Port3_channel2;
extern uint8_t u8Port4_channel2;



bool RspHandleMessage(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);
bool RspHandleDirectMessage(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);
bool RspHandleBroadcastMessage(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);

bool RspHandleReadSlaveAddress(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);
bool RspHandleChangeSlaveAddress(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);
bool RspHandleReadSensorValue(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);
bool RspHandleReadRtcTime(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);
bool RspHandleWriteRtcTime(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);
bool RspHandleReadRtcDate(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);
bool RspHandleWriteRtcDate(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);
bool RspHandleGetSensorsOnPort(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);
bool RspHandleSetSensorsOnPort(uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);
bool RspResponseMessage(uint8_t u8Cmd, uint8_t u8Subcmd, uint8_t* pu8Data, uint16_t u16Dlen, MESSAGE_TYPE msg);
void initFlashData(void);
void updateFlashData(void);
uint16_t GetSlaveAddress(void);
#endif
