#include "LedDriver.h"

enum {ALL_LEDS_ON = -1, ALL_LEDS_OFF = 0};

static uint16_t * ledsAddress;
static uint16_t ledsImage;

void LedDriver_Create(uint16_t * address)
{
	ledsAddress = address;
	ledsImage = ALL_LEDS_OFF;
	*ledsAddress = ledsImage;
}

void LedDriver_Destory(void)
{
}

static uint16_t convertLedNumberToBit(int ledNumber)
{
	return 1 << (ledNumber - 1);
}

static void updateHardware(void)
{
	*ledsAddress = ledsImage;
}

void LedDriver_TurnOn(int ledNumber)
{
	if (ledNumber <= 0 || ledNumber > 16)
		return;

	ledsImage |= convertLedNumberToBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
	if (ledNumber <= 0 || ledNumber > 16)
		return;

	ledsImage &= ~(convertLedNumberToBit(ledNumber));
	updateHardware();
}

void LedDriver_TurnAllOn(void)
{
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}
