#include "LedDriver.h"

static uint16_t * ledsAddress;
void LedDriver_Create(uint16_t * address)
{
	ledsAddress = address;
	ledsAddress = 0;
}

void LedDriver_Destory(void)
{
}

void LedDriver_TurnOn(int ledNumber)
{
	//*ledsAddress = 1;	//Segmentation fault: 11
}
