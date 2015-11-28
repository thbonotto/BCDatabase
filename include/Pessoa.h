/*
 * Pessoa.h
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#pragma once 

#include "Database.h"

namespace bcd29008 {

class Pessoa {
public:
	Pessoa();
	virtual ~Pessoa();
private:
	uint32_t mPessoaId;
	std::string mNome;
	std::string mEndereco;
	uint32_t mTipoDocumento;
	std::string mDocumento;
};

} /* namespace bcd29008 */

/* PESSOA_H_ */
