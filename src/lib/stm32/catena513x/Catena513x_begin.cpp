/*
Module:  Catena513x_begin.cpp

Function:
        Catena513x::begin().

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	September 2023

*/

#ifdef ARDUINO_ARCH_STM32

#include "Catena513x.h"

#include "Catena_Log.h"

using namespace McciCatena;

/*

Name:   Catena513x::begin()

Function:
        Set up all the well-known board peripherals.

Definition:
        bool Catena513x::begin();

Description:
        Issues begin() for all the Catena513x things.

Returns:
        true for success, false for failure.

*/

bool Catena513x::begin()
    {
    Serial.begin(115200);
    Wire.begin();
    delay(1000);
    gLog.begin(cLog::DebugFlags(gLog.kError | gLog.kBug));
    gLog.printf(
        gLog.kTrace,
        "\n+Catena513x::begin() for %s\n",
        CatenaName()
        );

    // do the platform selection.
    if (! this->Super::begin())
        return false;

    return true;
    }

#endif // ARDUINO_ARCH_STM32

/**** end of Catena513x_begin.cpp ****/