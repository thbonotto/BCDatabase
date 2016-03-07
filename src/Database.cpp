/*
 * Database.cpp
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#include "Database.h"
#include <stdlib.h>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
namespace bcd29008 {

Database::Database(const std::string& host, const std::string& schema,
		const std::string& user, const std::string& pass) :
		host { host }, schema { schema }, user { user }, pass { pass } {

	/* Create a connection */
	driver = get_driver_instance();

	//"tcp://127.0.0.1:3306"
	con = driver->connect(host, user, pass);
	bool myTrue = true;
	con->setClientOption("CLIENT_MULTI_STATEMENTS", &myTrue);
	/* Connect to the MySQL test database */
	con->setSchema(schema);

}
void Database::executeSQL(std::string sql) {
	std::cout << sql << std::endl;
	sql::Statement *stmt;
	stmt = con->createStatement();
	stmt->execute(sql);
	std::cout << "Ok" << std::endl;
	delete stmt;
}
void Database::cadastrarPessoa(std::string nome, std::string documento,
		std::string endereco) {
	std::string sql { "INSERT INTO pessoa (nome,documento,endereco) "
			"VALUES ('" + nome + "','" + documento + "','" + endereco + "');" };

	executeSQL(sql);

}
void Database::cadastrarOperadora(std::string nome, std::string cnpj) {

	std::string sql { "INSERT INTO operadora (cnpj,nome) "
			"VALUES ('" + cnpj + "','" + nome + "');" };
	executeSQL(sql);

}
void Database::cadastrarNumero(std::string numero) {
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::vector<int> ids;
	std::vector<string> nomes;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT id,nome from operadora;");
	while (res->next()) {
		nomes.push_back(res->getString("nome"));
		ids.push_back(res->getInt("id"));
	}
	if (ids.empty()) {
		delete res;
		delete stmt;
		throw "É necessário ter ao menos uma Operadora cadastrada";
	}

	for (size_t i = 0; i < ids.size(); i++) {
		std::cout << "Id: " << ids.at(i) << " Operadora: " << nomes.at(i)
				<< std::endl;
	}
	std::cout << "Digite o id para quem deseja atribuir o Número" << std::endl;
	std::string read;
	std::string serial;
	std::getline(std::cin, read);
	int item = atoi(read.c_str());
	if (std::find(ids.begin(), ids.end(), item) != ids.end()) {
		stmt->execute("INSERT INTO numero (numero,operadora) "
				"VALUES ('" + numero + "','" + read + "');");
	} else {
		delete res;
		delete stmt;
		throw "Opção invalida";
	}
	delete res;
	delete stmt;
}
void Database::cadastrarIMEI(std::string imei) {
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::vector<int> ids;
	std::vector<string> nomes;
	std::vector<string> cpfs;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT id, nome, documento from pessoa;");
	while (res->next()) {
		cpfs.push_back(res->getString("documento"));
		nomes.push_back(res->getString("nome"));
		ids.push_back(res->getInt("id"));
	}
	if (ids.empty()) {
		delete res;
		delete stmt;
		throw "É necessário ter ao menos uma pessoa cadastrada";
	}

	std::cout << "Digite o id para quem deseja atribuir o imei" << std::endl;
	for (size_t i = 0; i < ids.size(); i++) {
		std::cout << "Id: " << ids.at(i) << " Nome: " << nomes.at(i) << " CPF: "
				<< cpfs.at(i) << std::endl;
	}
	std::string read, id;
	std::getline(std::cin, read);
	int item = atoi(read.c_str());
	if (std::find(ids.begin(), ids.end(), item) != ids.end()) {
		stmt->execute("INSERT INTO imei (proprietario,numeroSerial) "
				"VALUES ('" + read + "','" + imei + "');");
	} else {
		delete res;
		delete stmt;
		throw "Opção invalida";
	}
	delete res;
	delete stmt;
}
void Database::cadastrarChip(std::string iccid) {
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::vector<int> ids;
	std::vector<string> imeis;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT id,numeroSerial from imei;");
	while (res->next()) {
		imeis.push_back(res->getString("numeroSerial"));
		ids.push_back(res->getInt("id"));
	}
	if (ids.empty()) {
		delete res;
		delete stmt;
		throw "É necessário ter ao menos um IMEI cadastrado";
	}

	for (size_t i = 0; i < ids.size(); i++) {
		std::cout << "Id: " << ids.at(i) << " IMEI: " << imeis.at(i)
				<< std::endl;
	}
	std::cout << "Digite o id do IMEI para qual deseja atribuir o Chip"
			<< std::endl;
	std::string read;
	std::string serial;
	std::string imeiId;
	std::getline(std::cin, read);
	int item = atoi(read.c_str());
	if (std::find(ids.begin(), ids.end(), item) != ids.end()) {
		imeiId = read;
		delete res;
		delete stmt;
	} else {
		delete res;
		delete stmt;
		throw "Opção invalida";
	}
	ids.clear();
	imeis.clear();
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT id, numero from numero;");
	while (res->next()) {
		imeis.push_back(res->getString("numero"));
		ids.push_back(res->getInt("id"));
	}
	if (ids.empty()) {
		delete res;
		delete stmt;
		throw "É necessário ter ao menos um Número cadastrado";
	}

	for (size_t i = 0; i < ids.size(); i++) {
		std::cout << "Id: " << ids.at(i) << " Número: " << imeis.at(i)
				<< std::endl;
	}
	std::cout << "Digite o id do Número para qual deseja atribuir o Chip"
			<< std::endl;
	std::getline(std::cin, read);
	item = atoi(read.c_str());
	if (std::find(ids.begin(), ids.end(), item) != ids.end()) {
		stmt->execute("INSERT INTO chip (iccid,vinculo,associacao) "
				"VALUES ('" + iccid + "','" + read + "','" + imeiId + "');");
	} else {
		delete res;
		delete stmt;
		throw "Opção invalida";
	}
	delete res;
	delete stmt;

}
void Database::cadastrarPlano(std::string plano) {
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::vector<int> ids;
	std::vector<string> nomes;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT id,nome from operadora;");
	while (res->next()) {
		nomes.push_back(res->getString("nome"));
		ids.push_back(res->getInt("id"));
	}
	if (ids.empty()) {
		delete res;
		delete stmt;
		throw "É necessário ter ao menos uma Operadora cadastrada";
	}

	for (size_t i = 0; i < ids.size(); i++) {
		std::cout << "Id: " << ids.at(i) << " Operadora: " << nomes.at(i)
				<< std::endl;
	}
	std::cout << "Digite o id para quem deseja atribuir o Plano" << std::endl;
	std::string read;
	std::string serial;
	std::getline(std::cin, read);
	int item = atoi(read.c_str());
	if (std::find(ids.begin(), ids.end(), item) != ids.end()) {
		stmt->execute("INSERT INTO plano (operadora,tipo) "
				"VALUES ('" + read + "','" + plano + "');");
	} else {
		delete res;
		delete stmt;
		throw "Opção invalida";
	}
	delete res;
	delete stmt;

}

void Database::cadastrarContrato() {
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::vector<int> ids;
	std::vector<string> PessoaPlanoOperadora;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT id,nome from pessoa;");
	while (res->next()) {
		PessoaPlanoOperadora.push_back(res->getString("nome"));
		ids.push_back(res->getInt("id"));
	}
	if (ids.empty()) {
		delete res;
		delete stmt;
		throw "É necessário ter ao menos uma Pessoa cadastrada cadastrado";
	}

	for (size_t i = 0; i < ids.size(); i++) {
		std::cout << "Id: " << ids.at(i) << " Nome: "
				<< PessoaPlanoOperadora.at(i) << std::endl;
	}
	std::cout << "Digite o id da pessoa que será o contratante." << std::endl;
	std::string read;
	std::string pessoaId;
	std::getline(std::cin, read);
	int item = atoi(read.c_str());
	if (std::find(ids.begin(), ids.end(), item) != ids.end()) {
		pessoaId = read;
		delete res;
		delete stmt;
	} else {
		delete res;
		delete stmt;
		throw "Opção invalida";
	}
	ids.clear();
	PessoaPlanoOperadora.clear();
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT id, tipo from plano;");
	while (res->next()) {
		PessoaPlanoOperadora.push_back(res->getString("tipo"));
		ids.push_back(res->getInt("id"));
	}
	if (ids.empty()) {
		delete res;
		delete stmt;
		throw "É necessário ter ao menos um Plano cadastrado";
	}

	for (size_t i = 0; i < ids.size(); i++) {
		std::cout << "Id: " << ids.at(i) << " Plano: "
				<< PessoaPlanoOperadora.at(i) << std::endl;
	}
	std::string planoId;
	std::cout << "Digite o id do Plano que será contratado." << std::endl;
	std::getline(std::cin, read);
	item = atoi(read.c_str());
	if (std::find(ids.begin(), ids.end(), item) != ids.end()) {
		planoId = read;
	} else {
		delete res;
		delete stmt;
		throw "Opção invalida";
	}
	ids.clear();
	PessoaPlanoOperadora.clear();
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT id, nome from operadora;");
	while (res->next()) {
		PessoaPlanoOperadora.push_back(res->getString("nome"));
		ids.push_back(res->getInt("id"));
	}
	if (ids.empty()) {
		delete res;
		delete stmt;
		throw "É necessário ter ao menos uma Operadora cadastrada";
	}

	for (size_t i = 0; i < ids.size(); i++) {
		std::cout << "Id: " << ids.at(i) << " Operadora: "
				<< PessoaPlanoOperadora.at(i) << std::endl;
	}
	std::cout << "Digite o id da Operadora que será contratada." << std::endl;
	std::getline(std::cin, read);
	item = atoi(read.c_str());
	if (std::find(ids.begin(), ids.end(), item) != ids.end()) {
		stmt->execute(
				"INSERT INTO contrato (contratante, contratado, plano) "
						"VALUES ('" + pessoaId + "','" + read + "','" + planoId
						+ "');");
	} else {
		delete res;
		delete stmt;
		throw "Opção invalida";
	}

	delete res;
	delete stmt;

}
void Database::atualizarContrato() {
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::vector<int> ids;
	std::vector<string> contratante;
	std::vector<string> operadora;
	std::vector<string> plano;
	stmt = con->createStatement();
	res = stmt->executeQuery(
			"SELECT id,contratante,contratado,plano from contrato;");
	while (res->next()) {
		contratante.push_back(res->getString("contratante"));
		operadora.push_back(res->getString("contratado"));
		plano.push_back(res->getString("plano"));
		ids.push_back(res->getInt("id"));
	}
	delete res;
	delete stmt;
	if (ids.empty()) {
		throw "É necessário ter ao menos um Contrato cadastrado";
	}

	for (size_t i = 0; i < ids.size(); i++) {
		std::cout << "Id: " << ids.at(i) << " Contratante: "
				<< getPessoaNameFromId(contratante.at(i)) << std::endl
				<< " Operadora: " << getOperadoraNameFromId(operadora.at(i))
				<< std::endl << " Plano: " << getPlanoTipoFromId(plano.at(i))
				<< std::endl;
	}

	std::cout << "Digite o Id do contrato que deseja alterar" << std::endl;
	std::string read;
	std::string contratoId;
	std::getline(std::cin, read);
	int item = atoi(read.c_str());
	if (std::find(ids.begin(), ids.end(), item) != ids.end()) {
		contratoId=read;
		std::cout << "Alterar:" << std::endl;
		std::cout << "1 - Contratante" << std::endl;
		std::cout << "2 - Operadora" << std::endl;
		std::cout << "3 - Plano" << std::endl;
		std::getline(std::cin, read);
		int choice = atoi(read.c_str());
		std::vector<string> cpfs;
		switch (choice) {
		case 1:
			cpfs.clear();
			contratante.clear();
			ids.clear();
			stmt = con->createStatement();
			res = stmt->executeQuery(
					"SELECT id, nome, documento from pessoa;");
			while (res->next()) {
				cpfs.push_back(res->getString("documento"));
				contratante.push_back(res->getString("nome"));
				ids.push_back(res->getInt("id"));
			}
			delete res;
			delete stmt;
			if (ids.empty()) {
				throw "É necessário ter ao menos uma pessoa cadastrada";
			}
			for (size_t i = 0; i < ids.size(); i++) {
				std::cout << "Id: " << ids.at(i) << " Nome: "
						<< contratante.at(i) << " CPF: " << cpfs.at(i)
						<< std::endl;
			}
			std::cout << "Digite o id do novo Contratante" << std::endl;
			std::getline(std::cin, read);
			item = atoi(read.c_str());
			if (std::find(ids.begin(), ids.end(), item) != ids.end())
				executeSQL(
						"UPDATE contrato set contratante = '" + read
								+ "' where id ='" + contratoId + "';");
			else
				throw "Opção invalida";
			break;
		case 2:
			ids.clear();
			operadora.clear();
			stmt = con->createStatement();
			res = stmt->executeQuery("SELECT id, nome from operadora;");
			while (res->next()) {
				operadora.push_back(res->getString("nome"));
				ids.push_back(res->getInt("id"));
			}
			delete res;
			delete stmt;
			if (ids.empty()) {

				throw "É necessário ter ao menos uma Operadora cadastrada";
			}

			for (size_t i = 0; i < ids.size(); i++) {
				std::cout << "Id: " << ids.at(i) << " Operadora: "
						<< operadora.at(i) << std::endl;
			}
			std::cout << "Digite o id da Nova Operadora" << std::endl;
			std::getline(std::cin, read);
			item = atoi(read.c_str());
			if (std::find(ids.begin(), ids.end(), item) != ids.end())
				executeSQL(
						"UPDATE contrato set contratado = '" + read
								+ "' where id ='" + contratoId + "';");
			else
				throw "Opção invalida";
			break;
		case 3:
			ids.clear();
			plano.clear();
			stmt = con->createStatement();
			res = stmt->executeQuery("SELECT id, tipo from plano;");
			while (res->next()) {
				plano.push_back(res->getString("tipo"));
				ids.push_back(res->getInt("id"));
			}
			delete res;
			delete stmt;
			if (ids.empty()) {
				throw "É necessário ter ao menos um Plano cadastrado";
			}

			for (size_t i = 0; i < ids.size(); i++) {
				std::cout << "Id: " << ids.at(i) << " Plano: " << plano.at(i)
						<< std::endl;
			}
			std::cout << "Digite o id do novo Plano" << std::endl;
			std::getline(std::cin, read);
			item = atoi(read.c_str());
			if (std::find(ids.begin(), ids.end(), item) != ids.end())
				executeSQL(
						"UPDATE contrato set plano = '" + read
								+ "' where id ='" + contratoId + "';");
			else
				throw "Opção invalida";
			break;

		default:
			delete res;
			delete stmt;
			throw "Opção invalida";
			break;
		}
	} else {
		throw "Opção invalida";
	}
}

void Database::importFromFile(const std::string& filePath) {
	std::string comando { "mysql -h " + host + " -u " + user + " -p" + pass
			+ " " + schema + " < " + filePath };
	if (system(comando.c_str()) == 0)
		std::cout << "Ok" << std::endl;
	else
		throw "Erro ao executar script";
}

int Database::getOperadoraIdFromName(const std::string& nome) {
	sql::Statement *stmt;
	sql::ResultSet *res;
	int id;
	stmt = con->createStatement();
	res = stmt->executeQuery(
			"SELECT id from operadora where operadora ='" + nome
					+ "'");
	if (res->next()) {
		id = res->getInt("id");
	}
	delete res;
	delete stmt;
	return id;

}

std::string Database::getOperadoraNameFromId(std::string id) {
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::string nome;
	stmt = con->createStatement();
	res = stmt->executeQuery(
			"SELECT nome from operadora where id ='" + id + "' ;");
	if (res->next()) {
		nome = res->getString("nome");
	}
	delete res;
	delete stmt;
	return nome;
}
std::string Database::getPlanoTipoFromId(std::string id) {
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::string tipo;
	stmt = con->createStatement();
	res = stmt->executeQuery(
			"SELECT tipo from plano where id ='" + id + "' ;");
	if (res->next()) {
		tipo = res->getString("tipo");
	}
	delete res;
	delete stmt;
	return tipo;

}
std::string Database::getPessoaNameFromId(std::string id) {
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::string nome;
	stmt = con->createStatement();
	res = stmt->executeQuery(
			"SELECT nome from pessoa where id ='" + id + "' ;");
	if (res->next()) {
		nome = res->getString("nome");
	}
	delete res;
	delete stmt;
	return nome;

}

Database::~Database() {
	delete con;
}

} /* namespace bcd29008 */
