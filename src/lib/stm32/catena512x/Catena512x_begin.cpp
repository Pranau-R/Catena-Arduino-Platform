/*

Module:  Catena512x_begin.cpp

Function:
        Catena512x::begin().

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	July 2022

*/

#ifdef ARDUINO_ARCH_STM32

#include "Catena512x.h"

#include "Catena_Log.h"

using namespace McciCatena;

/*

Name:	Catena512x::begin()

Function:
	Set up all the well-known board peripherals.

Definition:
	bool Catena512x::begin();

Description:
	Issues begin() for all the Catena512x things.

Returns:
	true for success, false for failure.

*/

bool Catena512x::begin()
	{
	Serial.begin(115200);
	Wire.begin();
	delay(1000);
	gLog.begin(cLog::DebugFlags(gLog.kError | gLog.kBug));
	gLog.printf(
		gLog.kTrace,
		"\n+Catena512x::begin() for %s\n",
		CatenaName()
		);

	// do the platform selection.
	if (! this->Super::begin())
		return false;

	return true;
	}

#endif // ARDUINO_ARCH_STM32

/**** end of Catena512x_begin.cpp ****/