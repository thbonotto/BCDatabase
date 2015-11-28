/*
 * Test.cpp
 *
 *  Created on: Nov 28, 2015
 *      Author: thiago.b
 */
#include <iostream>
#include <exception>

using namespace std;


int main() {
	try{

	} catch (const exception& e) {
		cout << e.what() << endl;
	}
return 0;
}


