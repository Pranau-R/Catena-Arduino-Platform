/*

Module:  Catena5130_getPlatformTable.cpp

Function:
        Catena5130::getPlatformTable()

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	September 2023

*/

#ifdef ARDUINO_ARCH_STM32

#include "Catena5130.h"

#include "Catena_Log.h"
#include "Catena_Platforms.h"
#include "Catena_Guids.h"

/****************************************************************************\
|
|	Read-only data.
|
\****************************************************************************/

namespace McciCatena {

const CATENA_PLATFORM gkPlatformCatena5130 =
    {
    Guid: GUID_HW_CATENA_5130_BASE(WIRE),
    pParent: &gkPlatformCatena5130,
    PlatformFlags:
        CatenaBase::fHasFRAM |
        CatenaBase::fHasFlash
    };

const CATENA_PLATFORM (* const Catena5130::vPlatforms[]) =
    {
    // entry 0 is the default
    &gkPlatformCatena5130,
    };

const size_t Catena5130::nvPlatforms = sizeof(Catena5130::vPlatforms) / sizeof(Catena5130::vPlatforms[0]);

/*

Name:   Catena5130::getPlatformTable()

Function:
        Get the known platform table.

        Definition:
        public: virtual
            void Catena5130::getPlatformTable(
                const CATENA_PLATFORM * const * &vPlatforms,
                size_t &nvPlatforms
                ) override;

Description:
        This override for getPlatformTable() returns the vector of platform
        GUIDs for this Catena.

Returns:
        vPlatforms is set to the base of the array of pointers to platform
        stuctures; and nvPlatforms is set to the number of entries in
        the table.

*/

/* public virtual override */
void
Catena5130::getPlatformTable(
        const CATENA_PLATFORM * const * &result_vPlatforms,
        size_t &result_nvPlatforms
        )
    {
        result_vPlatforms = vPlatforms;
        result_nvPlatforms = nvPlatforms;
    }

} /* namespace McciCatena */

#endif // ARDUINO_ARCH_STM32