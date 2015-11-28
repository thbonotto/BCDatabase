/*
 * Chamada.h
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#pragma once 

#include "Database.h"

namespace bcd29008 {

class Chamada {
public:
	Chamada();
	virtual ~Chamada();

private:
	uint32_t mChamadaId;
	uint64_t mHoraEstabelecida;
	uint64_t mOrigem;
	uint64_t mDestino;
	uint64_t mDuracao;
	uint32_t mPlanoFK;
	uint32_t mNumeroFK;
};

} /* namespace bcd29008 */

/* CHAMADA_H_ */
