/*

Module:  Catena512x.h

Function:
        class Catena512x: CatenaBase Platform to represent a Catena 512x
        (such as the 5120).

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	July 2022

*/

#ifndef _CATENA512X_H_	/* prevent multiple includes */
#define _CATENA512X_H_

#pragma once

#ifndef _CATENASTM32L0_H_
# include "CatenaStm32L0.h"
#endif

namespace McciCatena {

class Catena512x : public CatenaStm32L0
    {
public:
    using Super = CatenaStm32L0;

    // no specific constructor.
    Catena512x() {};

    // uses default destructor

    // neither copyable nor movable
    Catena512x(const Catena512x&) = delete;
    Catena512x& operator=(const Catena512x&) = delete;
    Catena512x(const Catena512x&&) = delete;
    Catena512x& operator=(const Catena512x&&) = delete;

    // LoRaWAN binding
    class LoRaWAN /* forward */;

    enum ANALOG_PINS
        {
        APIN_VBAT_SENSE = 2,
        APIN_VBUS_SENSE = 3,
        };

    enum ANALOG_CHANNELS
        {
        ANALOG_CHANNEL_A0 = 0,
        ANALOG_CHANNEL_A1 = 5,
        ANALOG_CHANNEL_A2 = 4,
        ANALOG_CHANNEL_A3 = PC0,
        ANALOG_CHANNEL_A4 = PC1,
        ANALOG_CHANNEL_A5 = PB0,
        ANALOG_CHANNEL_A9 = 6,
        ANALOG_CHANNEL_A10 = 7,
        ANALOG_CHANNEL_A11 = 2,
        ANALOG_CHANNEL_A12 = 3,
        ANALOG_CHANNEL_VBAT = ANALOG_CHANNEL_A11,
        ANALOG_CHANNEL_VBUS = ANALOG_CHANNEL_A12,
        ANALOG_CHANNEL_VREF = 17,
        };

    enum DIGITAL_PINS
        {
        PIN_STATUS_LED = D13,
        PIN_SPI2_FLASH_SS = D19,
        PIN_SPI2_MOSI = D23,
        PIN_SPI2_MISO = D22,
        PIN_SPI2_SCK = D24,
        };

    // methods
    virtual bool begin() override;

protected:

private:
    };

/*
|| The LoRaWAN class for the Catena 455x. Assumes The Things Network
*/
class Catena512x::LoRaWAN : public CatenaStm32L0::LoRaWAN
    {
public:
    using Super = CatenaStm32L0::LoRaWAN;

    /*
    || the constructor. We don't do anything at this level, the
    || Super constructor does most of the work.
    */
    LoRaWAN() {};

    bool begin(Catena512x *pParent);

protected:

private:
    };

} // namespace McciCatena

/**** end of Catena512x.h ****/
#endif /* _CATENA512X_H_ */