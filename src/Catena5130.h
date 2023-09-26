/*

Module:  Catena5130.h

Function:
        class Catena5130: CatenaBase Platform to represent a Catena 5130

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	September 2023

*/

#ifndef _Catena5130_H_	/* prevent multiple includes */
#define _Catena5130_H_

#pragma once

#ifndef _CATENA513x_H_
# include "Catena513x.h"
#endif

namespace McciCatena {

class Catena5130 : public Catena513x
    {
public:
        using Super = Catena5130;

        // no specific constructor.
        Catena5130() {};

    // uses default destructor

    // neither copyable nor movable
    Catena5130(const Catena5130&) = delete;
    Catena5130& operator=(const Catena5130&) = delete;
    Catena5130(const Catena5130&&) = delete;
    Catena5130& operator=(const Catena5130&&) = delete;

    virtual const char *CatenaName() const override { return "Catena 5130"; };
    virtual float ReadVbat(void) const override;
    virtual float ReadVbus(void) const override;

    protected:
    // we are required to provide a table of platforms
    virtual void getPlatformTable(
        const CATENA_PLATFORM * const * &vPlatforms,
        size_t &nvPlatforms
        ) override;

    private:
    // the known platforms
    static const CATENA_PLATFORM(* const vPlatforms[]);
    static const size_t nvPlatforms;
    };

} // namespace McciCatena

/**** end of Catena5130.h ****/
#endif /* _Catena5130_H_ */