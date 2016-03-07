all:
	g++ src/Database.cpp test/main.cpp -I include/ -std=c++0x -lmysqlcppconn -o BCDatabase

	@echo "Uso: ./BCDatabase host schema user pass"

clean: 
	rm -f BCDatabase
