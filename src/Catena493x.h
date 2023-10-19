/*

Module:  Catena493x.h

Function:
        class Catena493x: CatenaBase Platform to represent a Catena 493x
        (such as the 4933).

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	October 2023

*/

#ifndef _CATENA493x_H_	/* prevent multiple includes */
#define _CATENA493x_H_

#pragma once

#ifndef _CATENASTM32L0_H_
# include "CatenaStm32L0.h"
#endif

namespace McciCatena {

class Catena493x : public CatenaStm32L0
    {
public:
    using Super = CatenaStm32L0;

    // no specific constructor.
    Catena493x() {};

    // uses default destructor

    // neither copyable nor movable
    Catena493x(const Catena493x&) = delete;
    Catena493x& operator=(const Catena493x&) = delete;
    Catena493x(const Catena493x&&) = delete;
    Catena493x& operator=(const Catena493x&&) = delete;

    // LoRaWAN binding
    class LoRaWAN /* forward */;

    enum ANALOG_PINS
        {
        APIN_VBAT_SENSE = A1,
        APIN_VBUS_SENSE = A0,
        };

    enum ANALOG_CHANNELS
        {
        ANALOG_CHANNEL_A0 = 0;
        ANALOG_CHANNEL_A1 = 5,
        ANALOG_CHANNEL_A2 = 4,
        ANALOG_CHANNEL_A3 = 3,
        ANALOG_CHANNEL_A4 = 2,
        ANALOG_CHANNEL_VBAT = ANALOG_CHANNEL_A1,
		ANALOG_CHANNEL_VBUS = ANALOG_CHANNEL_A0,
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
class Catena493x::LoRaWAN : public CatenaStm32L0::LoRaWAN
    {
public:
    using Super = CatenaStm32L0::LoRaWAN;

    /*
    || the constructor. We don't do anything at this level, the
    || Super constructor does most of the work.
    */
    LoRaWAN() {};

    bool begin(Catena493x *pParent);

protected:

private:
    };

} // namespace McciCatena

/**** end of Catena493x.h ****/
#endif /* _CATENA493x_H_ */