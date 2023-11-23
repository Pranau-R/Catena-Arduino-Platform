/*

Module:  Catena493x_LoRaWAN_begin.cpp

Function:
        Catena493x::LoRaWAN::begin()

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	November 2023

*/

#ifdef ARDUINO_ARCH_STM32

#include "Catena493x.h"

#include "Catena_Log.h"
#include "mcciadk_baselib.h"

using namespace McciCatena;

/*

Name:   Catena493x::LoRaWAN::begin()

Function:
        Record linkage to main Catena object and set up LoRaWAN.

Definition:
        bool Catena493x::LoRaWAN::begin(
        Catena493x *pParent
        );
Description:
        We record parent pointers, and other useful things for later.
Returns:
        true for success, false for failure.
*/

bool
Catena493x::LoRaWAN::begin(
	Catena493x *pParent
	)
	{
	gLog.printf(gLog.kTrace, "+Catena493x::LoRaWAN::begin()\n");

	/* call the base begin */
	if (! this->Super::begin(pParent))
		{
		gLog.printf(
			gLog.kBug,
			"?Catena493x::LoRaWAN::begin: Super::begin() failed\n"
			);
		return false;
		}

	/* indicate success to the client */
	return true;
	}

#endif // ARDUINO_ARCH_STM32

/**** end of Catena493x_LoRaWAN_begin.cpp ****/