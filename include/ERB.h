/*
 * ERB.h
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#pragma once 

#include "Database.h"

namespace bcd29008 {

class ERB {
public:
	ERB();
	virtual ~ERB();
private:
	uint32_t mERBId;
	uint32_t mLimite;
	uint32_t mArea;
	float mLatitude;
	float mLongitude;
	uint32_t mQoS;
	uint64_t mCentralFK;
	uint64_t mOperadoraFK;
	uint64_t mChipFK;
};

} /* namespace bcd29008 */

/* ERB_H_ */
