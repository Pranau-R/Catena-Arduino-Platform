/*

Module:  Catena5120.h

Function:
        class Catena5120: CatenaBase Platform to represent a Catena 5120

Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	July 2022

*/

#ifndef _Catena5120_H_	/* prevent multiple includes */
#define _Catena5120_H_

#pragma once

#ifndef _CATENA512x_H_
# include "Catena512x.h"
#endif

namespace McciCatena {

class Catena5120 : public Catena512x
	{
public:
        using Super = Catena5120;

        // no specific constructor.
        Catena5120() {};

	// uses default destructor

	// neither copyable nor movable
	Catena5120(const Catena5120&) = delete;
	Catena5120& operator=(const Catena5120&) = delete;
	Catena5120(const Catena5120&&) = delete;
	Catena5120& operator=(const Catena5120&&) = delete;

	virtual const char *CatenaName() const override { return "Catena 5120"; };
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

/**** end of Catena5120.h ****/
#endif /* _Catena5120_H_ */