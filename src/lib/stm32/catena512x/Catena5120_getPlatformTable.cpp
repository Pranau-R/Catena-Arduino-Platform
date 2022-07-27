/*

Module:  Catena5120_getPlatformTable.cpp

Function:
        Catena5120::getPlatformTable()

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	July 2022

*/

#ifdef ARDUINO_ARCH_STM32

#include "Catena5120.h"

#include "Catena_Log.h"
#include "Catena_Platforms.h"
#include "Catena_Guids.h"

/****************************************************************************\
|
|	Read-only data.
|
\****************************************************************************/

namespace McciCatena {

const CATENA_PLATFORM gkPlatformCatena5120 =
	{
	Guid: GUID_HW_CATENA_5120_BASE(WIRE),
	pParent: &gkPlatformCatena5120,
	PlatformFlags:
		CatenaBase::fHasLoRa |
		CatenaBase::fHasTtnNycLoRa |
		CatenaBase::fHasSHT3x |
		CatenaBase::fHasLTR329 |
		CatenaBase::fHasFRAM |
		CatenaBase::fHasFlash
	};

const CATENA_PLATFORM (* const Catena5120::vPlatforms[]) =
	{
	// entry 0 is the default
	&gkPlatformCatena5120,
	};

const size_t Catena5120::nvPlatforms = sizeof(Catena5120::vPlatforms) / sizeof(Catena5120::vPlatforms[0]);

/*

Name:	Catena5120::getPlatformTable()

Function:
	Get the known platform table.

Definition:
	public: virtual
		void Catena5120::getPlatformTable(
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
Catena5120::getPlatformTable(
        const CATENA_PLATFORM * const * &result_vPlatforms,
        size_t &result_nvPlatforms
        )
	{
        result_vPlatforms = vPlatforms;
        result_nvPlatforms = nvPlatforms;
	}

} /* namespace McciCatena */

#endif // ARDUINO_ARCH_STM32
