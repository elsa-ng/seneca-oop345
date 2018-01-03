/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: January 1, 2018				**
** OOP345 Section C - Milestone			**
** csvdump.cpp							**
*****************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " csv-file csv-separator\n";
		return 1;
	}

	std::string filename = argv[1];
	char sep = argv[2][0];

	try {
		std::vector<std::vector<std::string>> csvData;
		csvRead(filename, sep, csvData);
		csvPrint(csvData);
		return 0;
	}
	catch (const std::string& e) {
		std::cerr << "It threw --> " << e << "\n";
	}

	return 1;
}