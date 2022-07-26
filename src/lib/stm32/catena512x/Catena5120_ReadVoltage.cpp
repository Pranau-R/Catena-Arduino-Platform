/*

Module:  Catena5120_ReadAnalog.cpp

Function:
        Catena5120::ReadVbat() and Catena5120::ReadVbus()

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	July 2022

*/

#ifdef ARDUINO_ARCH_STM32

#include "Catena5120.h"
#include "Catena_Log.h"

#include <Arduino.h>
using namespace McciCatena;

/****************************************************************************\
|
|	Manifest constants & typedefs.
|
\****************************************************************************/



/****************************************************************************\
|
|	Read-only data.
|
\****************************************************************************/



/****************************************************************************\
|
|	Variables.
|
\****************************************************************************/

float
Catena5120::ReadVbat(void) const
	{
	float volt = this->ReadAnalog(Catena512x::ANALOG_CHANNEL_VBAT, 1, 2);
	return volt / 1000;
	}

float
Catena5120::ReadVbus(void) const
	{
	float volt = this->ReadAnalog(Catena512x::ANALOG_CHANNEL_VBUS, 1, 3);
	return volt / 1000;
	}

#if defined(ARDUINO_MCCI_CATENA_5120) && defined(USBD_LL_ConnectionState_WEAK)

extern "C" {

uint32_t USBD_LL_ConnectionState(void)
	{
	uint32_t vBus;
	bool fStatus;

	fStatus = CatenaStm32L0_ReadAnalog(
			Catena512x::ANALOG_CHANNEL_VBUS, 1, 3, &vBus
			);
	return (fStatus && vBus < 3000) ? 0 : 1;
	}

}

#endif // ARDUINO_MCCI_CATENA_5120

#endif // ARDUINO_ARCH_STM32

/**** end of Catena5120_ReadAnalog.cpp ****/