/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: October 20, 2017				**
** OOP345 Section C - Workshop 6		**
** Grades.h								**
*****************************************/

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <vector>
#include <iomanip>

class Grades {
	std::vector<std::vector<std::string>> m_myGrades;		// 2-D vector-vector table of strings
public:
	Grades() {
	} // default constructor

	Grades(const char* filename) {
		std::ifstream in(filename, std::ios::in);			// open file

		if (in.is_open()) {
			
			std::string readLine;
			std::string storeLine;

			// read all records of file until end of file
			while (!in.eof()) {	
				std::vector<std::string> stringTable;

				getline(in, readLine);

				if (!readLine.empty()) {
					for (unsigned int i = 0; i < readLine.size() + 1; i++) {
						if (readLine[i] == ' ' || i == readLine.size()) {
							stringTable.push_back(storeLine);
							storeLine = "";
						}
						else {
							storeLine += readLine[i];
						}
					}
					this->m_myGrades.push_back(stringTable);
				}
			}
		}
		else {
			std::cerr << "Fail to open file\n";
			exit(99);
		}	
	} // overloaded constructor

	void displayGrades(std::ostream& os, std::function<std::string(double)>g) {
		std::vector<std::string>::iterator innerV;
		std::vector<std::vector<std::string>>::iterator outerV;

		for (outerV = m_myGrades.begin(); outerV != m_myGrades.end(); outerV++) {
			int i = 0;
			double numGrade = 0;
			std::string grade;

			for (innerV = outerV->begin(); innerV != outerV->end(); innerV++) {
				if (i == 0) {
					os << *innerV;
				}

				if (i == 1) {
					numGrade = std::stod(*innerV);
					os << std::fixed << std::setprecision(2) << numGrade;
				}
				
				i++;
				os << " ";
			}

			grade = g(numGrade);
			os << grade << std::endl;
		}
	}

}; // class Grades