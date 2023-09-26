/*

Module:  Catena513x.h

Function:
        class Catena513x: CatenaBase Platform to represent a Catena 513x
        (such as the 5130).

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	September 2022

*/

#ifndef _CATENA513x_H_	/* prevent multiple includes */
#define _CATENA513x_H_

#pragma once

#ifndef _CATENASTM32L0_H_
# include "CatenaStm32L0.h"
#endif

namespace McciCatena {

class Catena513x : public CatenaStm32L0
    {
public:
    using Super = CatenaStm32L0;

    // no specific constructor.
    Catena513x() {};

    // uses default destructor

    // neither copyable nor movable
    Catena513x(const Catena513x&) = delete;
    Catena513x& operator=(const Catena513x&) = delete;
    Catena513x(const Catena513x&&) = delete;
    Catena513x& operator=(const Catena513x&&) = delete;

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

} // namespace McciCatena

/**** end of Catena513x.h ****/
#endif /* _CATENA513x_H_ */