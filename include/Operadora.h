/*
 * Operadora.h
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#pragma once

#include "Database.h"

namespace bcd29008 {

class Operadora {
public:
	Operadora();
	virtual ~Operadora();
private:
	std::string mNome;
	uint64_t mCNPJ;
	uint32_t mPlanoFK;

};

}
/* namespace bcd29008 */

