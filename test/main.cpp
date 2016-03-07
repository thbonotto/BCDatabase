/*
 * main.cpp
 *
 *  Created on: Mar 6, 2016
 *      Author: thiago.b
 */

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>
#include "Database.h"

using namespace std;
using namespace bcd29008;

int main(int argc, char** argv) {
	if (argc < 5) {
		cout << "Uso: ./BCDatabase host schema user pass" << endl;
		exit(-1);
	}
	try {
		/**
		 * Host, schema, user, pass;
		 */
		cout << "Conectando ao banco de dados;" << endl;
		Database db { argv[1], argv[2], argv[3], argv[4] };
		cout << "Conectado ao banco de dados;" << endl;

		int choice;

		do {
			try {
				cout << "0 - Criar estrutura de banco a partir de arquivo SQL"
						<< endl;
				cout << "1 - Cadastrar pessoa" << endl;
				cout << "2 - Cadastrar operadora" << endl;
				cout << "3 - Cadastrar numero" << endl;
				cout << "4 - Cadastrar imei" << endl;
				cout << "5 - Cadastrar chip" << endl;
				cout << "6 - Cadastrar plano" << endl;
				cout << "7 - Cadastrar contrato" << endl;
				cout << "8 - Atualizar contrato" << endl;
				cout << "9 - Drop tables" << endl;
				cout << "10 - Sair" << endl;

				std::string read;

				std::string nome, documento;

				std::getline(std::cin, read);
				choice = atoi(read.c_str());

				switch (choice) {
				case 0:
					std::cout << "Digite o caminho do arquivo" << std::endl;
					std::getline(std::cin, read);
					db.importFromFile(read);
					break;
				case 1:
					std::cout << "Digite o nome" << std::endl;
					std::getline(std::cin, nome);
					std::cout << "Digite o documento" << std::endl;
					std::getline(std::cin, documento);
					db.cadastrarPessoa(nome, documento);
					break;
				case 2:
					std::cout << "Digite o nome" << std::endl;
					std::getline(std::cin, nome);
					std::cout << "Digite o documento" << std::endl;
					std::getline(std::cin, documento);
					db.cadastrarOperadora(nome, documento);
					break;
				case 3:
					std::cout << "Digite o número de telefone:" << std::endl;
					std::getline(std::cin, read);
					db.cadastrarNumero(read);

					break;
				case 4:
					std::cout << "Digite o número Serial - IMEI:" << std::endl;
					std::getline(std::cin, read);
					db.cadastrarIMEI(read);
					break;
				case 5:
					std::cout << "Digite o iccid:" << std::endl;
					std::getline(std::cin, read);
					db.cadastrarChip(read);
					break;
				case 6:
					std::cout << "Digite o tipo:" << std::endl;
					std::getline(std::cin, read);
					db.cadastrarPlano(read);
					break;
				case 7:
					db.cadastrarContrato();
					break;
				case 8:
					db.atualizarContrato();
					break;
				case 9:
					db.executeSQL("DROP TABLE if exists contrato");
					db.executeSQL("DROP TABLE if exists plano");
					db.executeSQL("DROP TABLE if exists chip");
					db.executeSQL("DROP TABLE if exists imei");
					db.executeSQL("DROP TABLE if exists numero");
					db.executeSQL("DROP TABLE if exists central");
					db.executeSQL("DROP TABLE if exists erb");
					db.executeSQL("DROP TABLE if exists pessoa");
					db.executeSQL("DROP TABLE if exists operadora");
					break;
				case 10:
					cout << "Bye" << endl;
					break;
				default:
					cout << "Opção invalida" << endl;
					break;
				}
			} catch (sql::SQLException &e) {
				cout << "# ERR: SQLException in " << __FILE__;
				cout << "(" << __FUNCTION__ << ") on line »" << __LINE__
						<< endl;
				cout << "# ERR: " << e.what();
				cout << " (MySQL error code: " << e.getErrorCode();
				cout << ", SQLState: " << e.getSQLState() << " )" << endl;
			} catch (const char * ex) {
				cout << ex << endl;
			} catch (std::exception &e) {
				cout << e.what() << endl;
				;
			}
		} while (choice != 10);

		exit(0);

	} catch (sql::SQLException &e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line »" << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		exit(1);
	}
}
