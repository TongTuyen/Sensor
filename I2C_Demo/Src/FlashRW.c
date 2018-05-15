/**
	* @file name: FlashRW.c
	* @writen by: L.A.Binh email binhl.ahg@gmail.com 
	* @from date  
	* @to date
	*/
#include "FlashRW.h"
/* brief:
 * this file includes functions to read and write flash on stm32F103C8T6
 * 64 kbytes --> medium-density devices
 * 64 pages, 1 Kbyte per page
 * page 0 start at 0x0800 0000
 * page x start at 0x0800 0000 + 0x0000 0400 * x
*/

uint8_t ReadByteFromFlash(uint32_t Data_adr)
{
	return *(uint8_t*) Data_adr;
}
uint16_t ReadHalfWorldFromFlash(uint32_t Data_adr)
{
	return *(uint16_t*) Data_adr;
}
uint32_t ReadWordFromFlash(uint32_t Data_adr)
{
	return *(uint32_t*) Data_adr;
}
void WriteByte2Flash(uint32_t Data_adr, uint8_t Data){
}

//FLASH_Program_HalfWord(uint32_t Address, uint16_t Data);
void WriteHalfWord2Flash(uint32_t Data_adr, uint16_t Data){
}
void WriteWord2Flash(uint32_t Data_adr, uint32_t Data){	
}

void ErasePage( uint8_t pageNumber){
	uint32_t SectorError=0;
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.Banks = FLASH_BANK1_END;//FLASH_BANK_1;
	EraseInitStruct.NbPages = 1;
	EraseInitStruct.PageAddress = 0x08000000 + pageNumber * 0x400 ;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	HAL_FLASHEx_Erase(&EraseInitStruct,&SectorError);
	HAL_FLASH_Lock();
}
