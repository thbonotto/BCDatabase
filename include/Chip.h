/*
 * Chip.h
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#pragma once 

#include "Database.h"

namespace bcd29008 {

class Chip {
public:
	Chip();
	virtual ~Chip();
private:
	uint64_t mICCID;
	uint64_t mNumeroFK;
};

} /* namespace bcd29008 */

/* CHIP_H_ */
