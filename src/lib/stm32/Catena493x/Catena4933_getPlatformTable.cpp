/*

Module:  Catena4933_getPlatformTable.cpp

Function:
        Catena4933::getPlatformTable()

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	October 2023

*/

#ifdef ARDUINO_ARCH_STM32

#include "Catena4933.h"

#include "Catena_Log.h"
#include "Catena_Platforms.h"
#include "Catena_Guids.h"

/****************************************************************************\
|
|	Read-only data.
|
\****************************************************************************/

namespace McciCatena {

const CATENA_PLATFORM gkPlatformCatena4933 =
	{
	Guid: GUID_HW_CATENA_4933_BASE(WIRE),
	pParent: &gkPlatformCatena4933,
	PlatformFlags:
		CatenaBase::fHasLoRa |
		CatenaBase::fHasTtnNycLoRa |
		CatenaBase::fHasSHT3x |
		CatenaBase::fHasBme680 |
		CatenaBase::fHasADS131M04 |
		CatenaBase::fHasFRAM |
		CatenaBase::fHasFlash
	};

const CATENA_PLATFORM (* const Catena4933::vPlatforms[]) =
	{
	// entry 0 is the default
	&gkPlatformCatena4933,
	};

const size_t Catena4933::nvPlatforms = sizeof(Catena4933::vPlatforms) / sizeof(Catena4933::vPlatforms[0]);

/*

Name:   Catena4933::getPlatformTable()

Function:
        Get the known platform table.

Definition:
        public: virtual
            void Catena4933::getPlatformTable(
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
Catena4933::getPlatformTable(
        const CATENA_PLATFORM * const * &result_vPlatforms,
        size_t &result_nvPlatforms
        )
	{
        result_vPlatforms = vPlatforms;
        result_nvPlatforms = nvPlatforms;
	}

} /* namespace McciCatena */

#endif // ARDUINO_ARCH_STM32