/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: January 1, 2018				**
** OOP345 Section C - Milestone			**
** util.cpp								**
*****************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"

void trimSpace(std::string& s) {
	while (!s.empty() && s[0] == ' ')
		s.erase(0, 1);

	while (!s.empty() && s[s.size() - 1] == ' ')
		s.erase(s.size() - 1, 1);
}

void csvPrint(std::vector<std::vector<std::string>>& csvData) {
	for (auto& line : csvData) {
		for (auto& field : line) {
			std::cout << " (" << field << ")";
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

bool validTaskName(std::string& s) {
	for (auto c : s)
		if (!(isalnum(c) || c == ' '))
			return false;
	return true;
}

bool validSlots(std::string& s) {
	for (auto c : s)
		if (!isdigit(c))
			return false;
	return true;
}

bool validItemName(std::string& s) {
	for (auto c : s)
		if (!(isalnum(c) || c == ' '))
			return false;
	return true;
}

bool validSequenceNumber(std::string& s) {
	for (auto c : s)
		if (!isdigit(c))
			return false;
	return true;
}