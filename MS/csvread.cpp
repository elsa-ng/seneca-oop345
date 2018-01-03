/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: January 1, 2018				**
** OOP345 Section C - Milestone			**
** csvread.cpp							**
*****************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void trimSpace(std::string& s) {
	while (!s.empty() && s[0] == ' ')
		s.erase(0, 1);

	while (!s.empty() && s[s.size() - 1] == ' ')
		s.erase(s.size() - 1, 1);
}

void csvPrint(std::vector<std::vector<std::string>>& csvData) {
	std::cout << "range-based for print\n";
	for (auto& line : csvData) {
		for (auto& field : line) {
			std::cout << " (" << field << ")";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	std::cout << "index print\n";
	for (size_t line = 0; line < csvData.size(); line++) {
		for (size_t field = 0; field < csvData[line].size(); field++) {
			std::cout << " <" << csvData[line][field] << ">";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	std::cout << "iterator print\n";
	for (auto line = csvData.begin(); line != csvData.end(); line++) {
		for (auto field = line->begin(); field != line->end(); field++) {
			std::cout << " {" << *field << "}";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

void csvRead(std::string& filename, char sep, std::vector<std::vector<std::string>>& csvData) {
	std::fstream in(filename, std::ios::in);
	if (!in.is_open()) {
		throw std::string("Cannot open file '") + filename + "'";
	}

	std::string line;
	while (getline(in, line)) {
		auto cr = line.find('\r');
		if (cr != std::string::npos)
			line.erase(cr, 1);

		std::string field;
		std::vector<std::string> fields;
		for (size_t index = 0; index < line.size(); index++) {
			if (line[index] != sep) {
				field += line[index];
			}
			else {
				trimSpace(field);
				fields.push_back(std::move(field));
			}
		}
		trimSpace(field);
		fields.push_back(std::move(field));
		
		csvData.push_back(std::move(fields));
	}
	in.close();
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << "csv-file csv-separate\n";
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
		std::cerr << "It threa --> " << e << "\n";
	}

	return 1;
}