/*

Module:  Catena4933.h

Function:
        class Catena4933: CatenaBase Platform to represent a Catena 4933
 
Copyright notice:
        See accompanying LICENSE file.

Author:
        Pranau R, MCCI Corporation	October 2023

*/

#ifndef _Catena4933_H_	/* prevent multiple includes */
#define _Catena4933_H_

#pragma once

#ifndef _CATENA493x_H_
# include "Catena493x.h"
#endif

namespace McciCatena {

class Catena4933 : public Catena493x
	{
public:
        using Super = Catena4933;

        // no specific constructor.
        Catena4933() {};

	// uses default destructor

	// neither copyable nor movable
	Catena4933(const Catena4933&) = delete;
	Catena4933& operator=(const Catena4933&) = delete;
	Catena4933(const Catena4933&&) = delete;
	Catena4933& operator=(const Catena4933&&) = delete;

	virtual const char *CatenaName() const override { return "Catena 4933"; };
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

/**** end of Catena4933.h ****/
#endif /* _Catena4933_H_ */