/*
 * Numero.h
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#pragma once 

#include "Database.h"

namespace bcd29008 {

class Numero {
public:
	Numero();
	virtual ~Numero();
private:
	uint64_t mNumero;
	int32_t mSaldo;
	uint64_t mOperadoraFK;
	uint64_t mTelefoneFK;
	int32_t mPlano;
};

} /* namespace bcd29008 */

/* NUMERO_H_ */
