/*

Module:  Catena4931_ReadVoltage.cpp

Function:
        Catena4931::ReadVbat() and Catena4931::ReadVbus()

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	November 2023

*/

#ifdef ARDUINO_ARCH_STM32

#include "Catena4931.h"
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
Catena4931::ReadVbat(void) const
	{
	float volt = this->ReadAnalog(Catena493x::ANALOG_CHANNEL_VBAT, 1, 2);
	return volt / 1000;
	}

float
Catena4931::ReadVbus(void) const
	{
	float volt = this->ReadAnalog(Catena493x::ANALOG_CHANNEL_VBUS, 1, 3);
	return volt / 1000;
	}

#endif // ARDUINO_ARCH_STM32

/**** end of Catena4931_ReadVoltage.cpp ****/