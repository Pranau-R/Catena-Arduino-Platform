/*

Module:  Catena4931.h

Function:
        class Catena4931: CatenaBase Platform to represent a Catena 4931
 
Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	November 2023

*/

#ifndef _Catena4931_H_	/* prevent multiple includes */
#define _Catena4931_H_

#pragma once

#ifndef _CATENA493x_H_
# include "Catena493x.h"
#endif

namespace McciCatena {

class Catena4931 : public Catena493x
	{
public:
        using Super = Catena4931;

        // no specific constructor.
        Catena4931() {};

	// uses default destructor

	// neither copyable nor movable
	Catena4931(const Catena4931&) = delete;
	Catena4931& operator=(const Catena4931&) = delete;
	Catena4931(const Catena4931&&) = delete;
	Catena4931& operator=(const Catena4931&&) = delete;

	virtual const char *CatenaName() const override { return "Catena 4931"; };
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

/**** end of Catena4931.h ****/
#endif /* _Catena4931_H_ */