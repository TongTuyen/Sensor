#ifndef __FLASH_RW_H
#define __FLASH_RW_H
#include "SerialTransmit.h"

uint8_t ReadByteFromFlash(uint32_t Data_adr);
uint16_t ReadHalfWorldFromFlash(uint32_t Data_adr);
uint32_t ReadWordFromFlash(uint32_t Data_adr);

void WriteByte2Flash(uint32_t Data_adr, uint8_t Data);
void WriteHalfWord2Flash(uint32_t Data_adr, uint16_t Data);
void WriteWord2Flash(uint32_t Data_adr, uint32_t Data);

void ErasePage( uint8_t pageNumber);

#endif
