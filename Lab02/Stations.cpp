#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include "Stations.h"

namespace w2 {
	Stations::Stations() {}

	Stations::Stations(char* file) {
		filename = std::string(file);
		std::fstream in(filename, std::ios::in);
		if (!in.is_open()) {
			std::cerr << "Cannot open file '" << filename << "'\n";
			exit(10);
		}
		else {
			std::string line;
			getline(in, line);

			unsigned int index = 0;
			unsigned int num = 0;
			char d;

			// check bounds of index and whether first character is a digit
			// use arithmetics on character which is converted to Dec code on ASCII table
			// increment index by 1
			while (index < line.size() && isdigit(line[index])) {
				num = num * 10 + line[index] - '0';
				index++;
			}

			// assign num to noStations
			noStations = num;

			// check if index is at the end of line
			if (index == line.size()) {
				std::cerr << "missing delimit character ';' on line -->" << line << "<--" << std::endl;
				exit(11);
			}
			else if (line[index] != ';') {
				std::cerr << "expected ';' on line -->" << line << "<<-, found '" << line[index] << std::endl;
				exit(12);
			}
			else {
				d = line[index];
				index++;
			}

			if (index < line.size()) {
				std::cerr << "extra characters after delimit character '" << d << "' on line -->" << line << "<--" << std::endl;
				exit(13);
			}

			// initialize StationManager
			unsigned int noAPass, noSPass;
			StationManager = new Station[noStations];
			for (unsigned int i = 0; i < noStations; i++) {
				getline(in, line, ';');
				in >> noSPass;
				in.ignore();
				in >> noAPass;
				in.ignore();
				StationManager[i].set(line, noSPass, noAPass);
			}

			in.close();
		}
	}

	Stations::~Stations() {
		std::ofstream os(filename, std::ios::trunc);

		if (os.is_open()) {
			os << noStations << ';' << std::endl;
			for (unsigned int i = 0; i < noStations; i++) {
				StationManager[i].write(os);
			}

			os.close();
		}
		else {
			std::cerr << "Cannot open file '" << filename << "'\n";
			exit(10);
		}

		delete[] StationManager;
	}

	void Stations::update() const {
		std::cout << std::endl;
		std::cout << "Passes Sold :" << std::endl;
		std::cout << "-------------" << std::endl;
		for (unsigned int i = 0; i < noStations; i++) {
			StationManager[i].update();
		}

	}

	void Stations::restock() const {
		std::cout << std::endl;
		std::cout << "Passes Added :" << std::endl;
		std::cout << "--------------" << std::endl;
		for (unsigned int i = 0; i < noStations; i++) {
			StationManager[i].restock();
		}
	}

	void Stations::report() const {
		std::cout << std::endl;
		std::cout << "Passes in Stock : Student Adult" << std::endl;
		std::cout << "-------------------------------" << std::endl;
		for (unsigned int i = 0; i < noStations; i++) {
			StationManager[i].report();
		}

	}
} // namespace w2