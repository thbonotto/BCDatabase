/*
 * Plano.h
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#pragma once 

#include "Database.h"

namespace bcd29008 {

class Plano {
public:
	Plano();
	virtual ~Plano();
private:
	uint32_t mPlanoId;
	uint64_t mVigencia;
	uint32_t mTipo;
	uint32_t mCadencia;
	uint32_t mCustoCadencia;
	uint32_t mFidelidade;
};

} /* namespace bcd29008 */

/* PLANO_H_ */
