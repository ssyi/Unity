#include "LedDriver.h"
#include "RuntimeError.h"

enum {ALL_LEDS_ON = -1, ALL_LEDS_OFF = 0};
enum {FIRST_LED = 1, LAST_LED = 16};

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

static BOOL IsLedOutOfBounds(int ledNumber)
{
	return (ledNumber < FIRST_LED) || (ledNumber > LAST_LED);
}

static void setLedImageBit(int ledNumber)
{
	ledsImage |= convertLedNumberToBit(ledNumber);
}

static void clearLedImageBit(int ledNumber)
{
	ledsImage &= ~(convertLedNumberToBit(ledNumber));
}

void LedDriver_TurnOn(int ledNumber)
{
	if (IsLedOutOfBounds(ledNumber))
	{
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
		return;
	}

	setLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
	if (IsLedOutOfBounds(ledNumber))
	{
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", -1);
		return;
	}

	clearLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnAllOn(void)
{
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}

void LedDriver_TurnAllOff(void)
{
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}

BOOL LedDriver_IsOn(int ledNumber)
{
	if (IsLedOutOfBounds(ledNumber))
		return FALSE;

	return ledsImage & (convertLedNumberToBit(ledNumber));
}

BOOL LedDriver_IsOff(int ledNumber)
{
	return !LedDriver_IsOn(ledNumber); 
}

