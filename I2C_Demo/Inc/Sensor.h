#ifndef __SENSOR_H
#define __SENSOR_H
#include "stm32f1xx_hal.h"
#include "SerialTransmit.h"

void SensorCommunication(void);
void AM2315UpdateValue(void); 								// TEMPERATURE_AIR + HUMIDITY_AIR
void BH1750UpdateValue(void); 								// AMBIENT_LIGHT


#endif
