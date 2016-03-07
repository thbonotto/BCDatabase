/*
 * Database.cpp
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */

#include "Database.h"
#include <fstream>
#include <streambuf>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;
namespace bcd29008 {

Database::Database(const std::string& host, const std::string& schema, const std::string&  user,const std::string&  pass) {


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
void Database::cadastrarPessoa(std::string nome, std::string documento, std::string endereco){
	std::string sql{"INSERT INTO bonotto_pessoa (nome,documento,endereco) "
				"VALUES ('"+nome+"','"+documento+"','"+endereco+"');"};

		executeSQL(sql);

}
void Database::cadastrarOperadora(std::string nome, std::string cnpj){

	std::string sql{"INSERT INTO bonotto_operadora (cnpj,nome) "
			"VALUES ('"+cnpj+"','"+nome+"');"};
	executeSQL(sql);

}
void Database::cadastrarIMEI(std::string imei) {
	std::string pessoa;
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::vector<int> ids;
	std::vector<string> nomes;
	std::vector<string> cpfs;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT id, nome, documento from bonotto_pessoa;");
	while (res->next()) {
		cpfs.push_back(res->getString("documento"));
		nomes.push_back(res->getString("nome"));
		ids.push_back(res->getInt("id"));
	}
	if(ids.empty()){
		delete res;
			delete stmt;
		throw "É necessário ter ao menos uma pessoa cadastrada";
	}

	std::cout << "Digite o id para quem deseja atribuir o imei" <<  std::endl;
	for(size_t i=0; i < ids.size(); i++){
		std::cout << "Id: " << ids.at(i) << " Nome: " << nomes.at(i) << " CPF: "<< cpfs.at(i) << std::endl;
	}
	std::string read,id;
	std::getline(std::cin,read);
	int item= atoi(read.c_str());
	if(std::find(ids.begin(), ids.end(), item) != ids.end()){
		stmt->execute("INSERT INTO bonotto_imei (proprietario,numeroSerial) "
				"VALUES ('"+read+"','"+imei+"');");
	} else {
		delete res;
		delete stmt;
		throw "Opção invalida";
	}
	delete res;
	delete stmt;
}
void Database::cadastrarChip(std::string iccid) {
	std::string pessoa;
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::vector<int> ids;
	std::vector<string> imeis;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT id,numeroSerial from bonotto_imei;");
	while (res->next()) {
		imeis.push_back(res->getString("numeroSerial"));
		ids.push_back(res->getInt("id"));
	}
	if(ids.empty()){
		delete res;
		delete stmt;
		throw "É necessário ter ao menos um IMEI cadastrado";
	}

	for(size_t i=0; i < ids.size(); i++){
		std::cout << "Id: " << ids.at(i) << " IMEI: " << imeis.at(i) << std::endl;
	}
	std::cout << "Digite o id para quem deseja atribuir o Chip" <<  std::endl;
	std::string read;
	std::string serial;
	std::getline(std::cin,read);
	int item= atoi(read.c_str());
	if(std::find(ids.begin(), ids.end(), item) != ids.end()){
		stmt->execute("INSERT INTO bonotto_chip (associacao,iccid) "
				"VALUES ('"+read+"','"+iccid+"');");
	} else {
		delete res;
		delete stmt;
		throw "Opção invalida";
	}
	delete res;
	delete stmt;

}
void Database::cadastrarPlano(std::string plano) {
	std::string pessoa;
	sql::Statement *stmt;
	sql::ResultSet *res;
	std::vector<int> ids;
	std::vector<string> nomes;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT id,nome from bonotto_operadora;");
	while (res->next()) {
		nomes.push_back(res->getString("nome"));
		ids.push_back(res->getInt("id"));
	}
	if(ids.empty()){
		delete res;
		delete stmt;
		throw "É necessário ter ao menos uma Operadora cadastrada";
	}

	for(size_t i=0; i < ids.size(); i++){
		std::cout << "Id: " << ids.at(i) << " Operadora: " << nomes.at(i) << std::endl;
	}
	std::cout << "Digite o id para quem deseja atribuir o Plano" <<  std::endl;
	std::string read;
	std::string serial;
	std::getline(std::cin,read);
	int item= atoi(read.c_str());
	if(std::find(ids.begin(), ids.end(), item) != ids.end()){
		stmt->execute("INSERT INTO bonotto_plano (operadora,tipo) "
				"VALUES ('"+read+"','"+plano+"');");
	} else {
		delete res;
		delete stmt;
		throw "Opção invalida";
	}
	delete res;
	delete stmt;

}
void Database::importFromFile(const std::string& filePath){
	sql::Statement *stmt;
	std::ifstream sqlFile(filePath.c_str());
	std::stringstream buffer;
	buffer << sqlFile.rdbuf();
	std::string sql{buffer.str()};
	sql.erase (std::remove(sql.begin(), sql.end(), '\n'), sql.end());
	stmt = con->createStatement();
	std::cout << sql << std::endl;
	stmt->execute(sql);
	delete stmt;

}

int Database::getOperadoraIdFromName(const std::string& nome) {
	sql::Statement *stmt;
	sql::ResultSet *res;
	int id;
	stmt = con->createStatement();
	res = stmt->executeQuery("SELECT id from bonotto_operadora where bonotto_operadora ='"+nome+"'");
	if (res->next()) {
		id = res->getInt("id");
	}
	delete res;
	delete stmt;
	return id;

}

Database::~Database() {
	  delete con;
	// TODO Auto-generated destructor stub
}

} /* namespace bcd29008 */
