/*
 * Central.h
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#pragma once 

#include "Database.h"

namespace bcd29008 {

class Central {
public:
	Central();
	virtual ~Central();

private:
	uint32_t mCentralId;
	uint32_t mRegiao;
	uint32_t mCapacidadeLigacoes;
	uint32_t mOperadoraFK;
};

} /* namespace bcd29008 */

/* CENTRAL_H_ */
