/*
 * Telefone.h
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#pragma once 

#include "Database.h"

namespace bcd29008 {

class Telefone {
public:
	Telefone();
	const std::string& print();
	virtual ~Telefone();

private:

	uint64_t mIMEI;
	uint32_t mPessoaFK;
	uint32_t mChipFK;

};

} /* namespace bcd29008 */

/* TELEFONE_H_ */
