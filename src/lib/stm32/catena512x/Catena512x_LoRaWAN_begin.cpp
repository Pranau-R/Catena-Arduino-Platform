/*

Module:  Catena512x_LoRaWAN_begin.cpp

Function:
        Catena512x::LoRaWAN::begin()

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	April 2022

*/

#ifdef ARDUINO_ARCH_STM32

#include "Catena512x.h"

#include "Catena_Log.h"
#include "mcciadk_baselib.h"

using namespace McciCatena;

/*

Name:	Catena512x::LoRaWAN::begin()

Function:
	Record linkage to main Catena object and set up LoRaWAN.

Definition:
	bool Catena512x::LoRaWAN::begin(
		Catena512x *pParent
		);

Description:
	We record parent pointers, and other useful things for later.

Returns:
	true for success, false for failure.

*/

bool
Catena512x::LoRaWAN::begin(
	Catena512x *pParent
	)
	{
	gLog.printf(gLog.kTrace, "+Catena512x::LoRaWAN::begin()\n");

	/* call the base begin */
	if (! this->Super::begin(pParent))
		{
		gLog.printf(
			gLog.kBug,
			"?Catena512x::LoRaWAN::begin: Super::begin() failed\n"
			);
		return false;
		}

	/* indicate success to the client */
	return true;
	}

#endif // ARDUINO_ARCH_STM32

/**** end of Catena512x_LoRaWAN_begin.cpp ****/