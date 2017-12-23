/* Name: Wai Chi Ng
** Student ID: 140634163
** Email: wcng1@myseneca.ca
** Date: September 9, 2017
** OOP345 Section C - Workshop 1
** w1.cpp
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "CString.h"
#include "process.h"

int main(int argc, char* argv[]) {
	std::cout << "Command Line :";
	
	for (int arg = 0; arg < argc; arg++) {
		std::cout << " " << argv[arg];
	}
	std::cout << std::endl;

	if (argc == 1) { // This will run when the nothing is supplied in the command line
		std::cout << "Insufficient number of arguments (min 1)" << std::endl;
		return 1;
	}
	else {
		std::cout << "Maximum number of characters stored : " << w1::MAX << std::endl;
		for (int arg2 = 1; arg2 < argc; arg2++) {
			process(argv[arg2]);
		}
	}
	
	return 0;
}