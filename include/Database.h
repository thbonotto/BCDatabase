/*
 * Database.h
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#pragma once
#include <stdint.h>
#include <string>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

namespace bcd29008 {

class Database {
public:
	Database(const std::string& host, const std::string& schema, const std::string&  user, const std::string&  pass);
	void importFromFile(const std::string& filePath);
	void cadastrarPessoa(std::string nome, std::string documento, std::string endereco="No Where");
	void cadastrarOperadora(std::string nome, std::string cnpj);
	void cadastrarNumero(std::string numero);
	void cadastrarIMEI(std::string imei);
	void cadastrarChip(std::string iccid);
	void cadastrarPlano(std::string plano);
	void cadastrarContrato();
	void atualizarContrato();
	void executeSQL(std::string sql);
	int getOperadoraIdFromName(const std::string& nome);
	int getOperadoraIdFromCnpj(const std::string& cnpj);
	std::string getOperadoraNameFromId(std::string id);
	std::string getPlanoTipoFromId(std::string id);
	std::string getPessoaNameFromId(std::string id);
	virtual ~Database();
private:
	sql::Driver *driver;
	sql::Connection *con;
	std::string host;
	std::string schema;
	std::string user;
	std::string pass;
};

}
/* namespace bcd29008 */

