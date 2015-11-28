/*
 * Contrato.h
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#pragma once 

#include "Database.h"

namespace bcd29008 {

class Contrato {
public:
	Contrato();
	virtual ~Contrato();
private:
	uint32_t mNumeroContrato;
	std::string mEnderecoCobranca;
	uint32_t mPlanoFK;
	uint32_t mContratanteFK;
};

} /* namespace bcd29008 */

/* CONTRATO_H_ */
