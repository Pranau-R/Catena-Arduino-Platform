/*

Module:	Catena_AppObjects.h

Function:
	Common application objects for use by Catena apps.

Copyright and License:
	This file copyright (C) 2021 by

		MCCI Corporation
		3520 Krums Corners Road
		Ithaca, NY  14850

	See accompanying LICENSE file for copyright and license information.

Author:
	Terry Moore, MCCI Corporation	November 2021

*/

/// \file

#ifndef _Catena_AppObjects_h_
/// \cond
#define _Catena_AppObjects_h_	/* prevent multiple includes */
/// \endcond

#pragma once

#include <Catena.h>
#include <Catena_Serial.h>

namespace McciCatena {

   ///
   /// \brief the "second" SPI bus.
   ///
   extern SPIClass gSPI2;

   class cFlash;
   class cDownload;
   class cBootloaderApi;
   class StatusLed;

   ///
   /// \brief the primary on-board SPI flash device.
   ///
   /// \note We use a reference because it's otherwise ugly to refer to a global
   ///		of abstract type.
   ///
   extern cFlash &gFlash;

   ///
   /// \brief the download object for the command processor.
   ///
   extern cDownload gDownload;

   ///
   /// \brief the abstract wrapper for the main serial port.
   ///
   extern cSerial<decltype(Serial)> gSerial;

   ///
   /// \brief the status LED
   ///
   extern StatusLed gLed;

   ///
   /// \brief the bootloader API object
   ///
   extern cBootloaderApi gBootloaderApi;

} // end namespace McciCatena

// compute compile-time variables that are used to control things
// This parallels settings in Catena.h

#define	CATENA_PLATFORM_FLASH_TYPE_UNSPECIFIED	0	///< type of on-board flash is not specified.
#define	CATENA_PLATFORM_FLASH_TYPE_AS25SF081	1	///< On-board flash is a AS25SF081 1-Mbyte flash.
#define	CATENA_PLATFORM_FLASH_TYPE_MX25V8035F	2	///< On-board flash is an MX25V8035F 1-Mbyte flash.

#if defined(MCCI_CATENA_4450)
# define CATENA_PLATFORM_HAS_BOOTLOADER	0
# define CATENA_PLATFORM_HAS_FLASH	0
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	2048
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	0
# define CATENA_PLATFORM_HAS_DOWNLOAD	0
#elif defined(MCCI_CATENA_4460)
# define CATENA_PLATFORM_HAS_BOOTLOADER	0
# define CATENA_PLATFORM_HAS_FLASH	0
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	2048
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	0
# define CATENA_PLATFORM_HAS_DOWNLOAD	0
#elif defined(MCCI_CATENA_4470)
# define CATENA_PLATFORM_HAS_BOOTLOADER	0
# define CATENA_PLATFORM_HAS_FLASH	1
# define CATENA_PLATFORM_FLASH_TYPE	CATENA_PLATFORM_FLASH_TYPE_AS25SF081
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	2048
# define CATENA_PLATFORM_HAS_DOWNLOAD	0
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	0
#elif defined(MCCI_CATENA_4410)
# define CATENA_PLATFORM_HAS_BOOTLOADER	0
# define CATENA_PLATFORM_HAS_FLASH	0
# define CATENA_PLATFORM_HAS_FRAM	0
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	0
# define CATENA_PLATFORM_HAS_DOWNLOAD	0
#elif defined(MCCI_CATENA_4420)
# define CATENA_PLATFORM_HAS_BOOTLOADER	0
# define CATENA_PLATFORM_HAS_FLASH	0
# define CATENA_PLATFORM_HAS_FRAM	0
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	0
# define CATENA_PLATFORM_HAS_DOWNLOAD	0
#elif defined(ARDUINO_MCCI_CATENA_4551) || defined(ARDUINO_CATENA_4551)
# define CATENA_PLATFORM_HAS_BOOTLOADER	0
# define CATENA_PLATFORM_HAS_FLASH	1
# define CATENA_PLATFORM_FLASH_TYPE	CATENA_PLATFORM_FLASH_TYPE_MX25V8035F
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	8192
# define CATENA_PLATFORM_HAS_DOWNLOAD	0
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	1
#elif defined(ARDUINO_MCCI_CATENA_4610)
# define CATENA_PLATFORM_HAS_BOOTLOADER	1
# define CATENA_PLATFORM_HAS_FLASH	1
# define CATENA_PLATFORM_FLASH_TYPE	CATENA_PLATFORM_FLASH_TYPE_MX25V8035F
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	8192
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	1
# define CATENA_PLATFORM_HAS_DOWNLOAD	1
#elif defined(ARDUINO_MCCI_CATENA_4611)
# define CATENA_PLATFORM_HAS_BOOTLOADER	1
# define CATENA_PLATFORM_HAS_FLASH	1
# define CATENA_PLATFORM_FLASH_TYPE	CATENA_PLATFORM_FLASH_TYPE_MX25V8035F
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	8192
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	1
# define CATENA_PLATFORM_HAS_DOWNLOAD	1
#elif defined(ARDUINO_MCCI_CATENA_4612)
# define CATENA_PLATFORM_HAS_BOOTLOADER	1
# define CATENA_PLATFORM_HAS_FLASH	1
# define CATENA_PLATFORM_FLASH_TYPE	CATENA_PLATFORM_FLASH_TYPE_MX25V8035F
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	8192
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	1
# define CATENA_PLATFORM_HAS_DOWNLOAD	1
#elif defined(ARDUINO_MCCI_CATENA_4617)
# define CATENA_PLATFORM_HAS_BOOTLOADER	1
# define CATENA_PLATFORM_HAS_FLASH	1
# define CATENA_PLATFORM_FLASH_TYPE	CATENA_PLATFORM_FLASH_TYPE_MX25V8035F
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	8192
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	1
# define CATENA_PLATFORM_HAS_DOWNLOAD	1
#elif defined(ARDUINO_MCCI_CATENA_4618)
# define CATENA_PLATFORM_HAS_BOOTLOADER	1
# define CATENA_PLATFORM_HAS_FLASH	1
# define CATENA_PLATFORM_FLASH_TYPE	CATENA_PLATFORM_FLASH_TYPE_MX25V8035F
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	8192
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	1
# define CATENA_PLATFORM_HAS_DOWNLOAD	1
#elif defined(ARDUINO_MCCI_CATENA_4630)
# define CATENA_PLATFORM_HAS_BOOTLOADER	1
# define CATENA_PLATFORM_HAS_FLASH	1
# define CATENA_PLATFORM_FLASH_TYPE	CATENA_PLATFORM_FLASH_TYPE_MX25V8035F
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	8192
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	1
# define CATENA_PLATFORM_HAS_DOWNLOAD	1
#elif defined(ARDUINO_MCCI_CATENA_4801) || defined(ARDUINO_CATENA_4801)
# define CATENA_PLATFORM_HAS_BOOTLOADER	1
# define CATENA_PLATFORM_HAS_FLASH	1
# define CATENA_PLATFORM_FLASH_TYPE	CATENA_PLATFORM_FLASH_TYPE_MX25V8035F
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	2048
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	1
# define CATENA_PLATFORM_HAS_DOWNLOAD	1
#elif defined(ARDUINO_MCCI_CATENA_4802)
# define CATENA_PLATFORM_HAS_BOOTLOADER	1
# define CATENA_PLATFORM_HAS_FLASH	1
# define CATENA_PLATFORM_FLASH_TYPE	CATENA_PLATFORM_FLASH_TYPE_MX25V8035F
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	8192
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	1
# define CATENA_PLATFORM_HAS_DOWNLOAD	1
#elif defined(ARDUINO_MCCI_CATENA_5001)
# define CATENA_PLATFORM_HAS_BOOTLOADER	1
# define CATENA_PLATFORM_HAS_FLASH	1
# define CATENA_PLATFORM_FLASH_TYPE	CATENA_PLATFORM_FLASH_TYPE_MX25V8035F
# define CATENA_PLATFORM_HAS_FRAM	1
# define CATENA_PLATFORM_FRAM_SIZE	8192
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	1
# define CATENA_PLATFORM_HAS_DOWNLOAD	1
#elif defined(ARDUINO_SAMD_FEATHER_M0)
# define CATENA_PLATFORM_HAS_BOOTLOADER	0
# define CATENA_PLATFORM_HAS_FLASH	0
# define CATENA_PLATFORM_HAS_FRAM	0
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	0
# define CATENA_PLATFORM_HAS_DOWNLOAD	0
#elif defined(ARDUINO_ARCH_SAMD)
# define CATENA_PLATFORM_HAS_BOOTLOADER	0
# define CATENA_PLATFORM_HAS_FLASH	0
# define CATENA_PLATFORM_HAS_FRAM	0
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	0
# define CATENA_PLATFORM_HAS_DOWNLOAD	0
#elif defined(ARDUINO_ARCH_STM32)
# define CATENA_PLATFORM_HAS_BOOTLOADER	0
# define CATENA_PLATFORM_HAS_FLASH	0
# define CATENA_PLATFORM_HAS_FRAM	0
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	0
# define CATENA_PLATFORM_HAS_DOWNLOAD	0
#else
# define CATENA_PLATFORM_HAS_BOOTLOADER	0
# define CATENA_PLATFORM_HAS_FLASH	0
# define CATENA_PLATFORM_HAS_FRAM	0
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	0
# define CATENA_PLATFORM_HAS_DOWNLOAD	0
#endif

//
// postcondition: CATENA_PLATFORM_HAS_BOOTLOADER,
// CATENA_PLATFORM_HAS_FLASH, CATENA_PLATFORM_FLASH_TYPE
// CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL, and CATENA_PLATFORM_HAS_DOWNLOAD are defiend
//
#ifndef	CATENA_PLATFORM_HAS_BOOTLOADER
# define CATENA_PLATFORM_HAS_BOOTLOADER	0
#endif

#ifndef CATENA_PLATFORM_HAS_FLASH
# define CATENA_PLATFORM_HAS_FLASH	0
#endif

#ifndef CATENA_PLATFORM_FLASH_TYPE
# define CATENA_PLATFORM_FLASH_TYPE	CATENA_PLATFORM_FLASH_TYPE_UNSPECIFIED
#endif

#ifndef CATENA_PLATFORM_HAS_FRAM
# define CATENA_PLATFORM_HAS_FRAM	0
#endif

#ifndef CATENA_PLATFORM_FRAM_SIZE
# define CATENA_PLATFORM_FRAM_SIZE	0
#endif

#ifndef CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL
# define CATENA_PLATFORM_HAS_SPI2_AS_EXTERNAL	0
#endif

#ifndef CATENA_PLATFORM_HAS_DOWNLOAD
# define CATENA_PLATFORM_HAS_DOWNLOAD	0
#endif

//
// error checking
//
#if CATENA_PLATFORM_HAS_DOWNLOAD && !(CATENA_PLATFORM_HAS_BOOTLOADER && CATENA_PLATFORM_HAS_FLASH)
# error CATENA_PLATFORM_HAS_DOWNLOAD requires CATENA_PLATFORM_HAS_BOOTLOADER and CATENA_PLATFORM_HAS_FLASH
#endif


#endif /* _Catena_AppObjects_h_ */
