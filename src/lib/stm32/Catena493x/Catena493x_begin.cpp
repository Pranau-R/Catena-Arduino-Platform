/*

Module:  Catena493x_begin.cpp

Function:
        Catena493x::begin().

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	November 2023

*/

#ifdef ARDUINO_ARCH_STM32

#include "Catena493x.h"

#include "Catena_Log.h"

using namespace McciCatena;

/*

Name:   Catena493x::begin()

Function:
        Set up all the well-known board peripherals.

Definition:
        bool Catena493x::begin();

Description:
        Issues begin() for all the Catena493x things.

Returns:
        true for success, false for failure.

*/

bool Catena493x::begin()
	{
	Serial.begin(115200);
	Wire.begin();
	delay(1000);
	gLog.begin(cLog::DebugFlags(gLog.kError | gLog.kBug));
	gLog.printf(
		gLog.kTrace,
		"\n+Catena493x::begin() for %s\n",
		CatenaName()
		);

	// do the platform selection.
	if (! this->Super::begin())
		return false;

	return true;
	}

#endif // ARDUINO_ARCH_STM32

/**** end of Catena493x_begin.cpp ****/