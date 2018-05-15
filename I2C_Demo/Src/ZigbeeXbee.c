#include "ZigbeeXbee.h"
#include "RspHandle.h"

bool ZigbeeXbeeHandleMessage(uint8_t* pu8Data, uint16_t u16Dlen){
	uint16_t startIndex = 0;
	while(pu8Data[startIndex]==NULL){
		if(startIndex++>=u16Dlen) break;
	}
	return RspHandleMessage(&pu8Data[startIndex], u16Dlen - startIndex, MESSAGE_TYPE_RF);
}
