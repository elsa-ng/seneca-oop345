/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: January 1, 2018				**
** OOP345 Section C - Workshop 9		**
** Element.h							**
*****************************************/

// Workshop 9 - Smart Pointers
// Element.h

#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

extern const int FWC;
extern const int FWD;
extern const int FWP;

namespace w9 {

	struct Description {
		unsigned code;
		std::string desc;
		bool load(std::ifstream& f) {
			f >> code >> desc;
			return f.good();
		}
		void display(std::ostream& os) const {
			os << std::setw(FWC) << code << std::setw(FWD)
				<< desc << std::endl;
		}
	};

	struct Price {
		unsigned code;
		double price;
		bool load(std::ifstream& f) {
			f >> code >> price;
			return f.good();
		}
		void display(std::ostream& os) const {
			os << std::setw(FWC) << code << std::setw(FWP)
				<< price << std::endl;
		}
	};

	struct Product {
		std::string desc;
		double price;
		Product() {}
		Product(const std::string& str, double p) : desc(str), price(p) {}
		void display(std::ostream& os) const {
			os << std::setw(FWD) << desc << std::setw(FWP)
				<< price << std::endl;
		}

		void validate() {
			if (price < 0) {
				throw "*** Negative prices are invalid ***";
			}
		}
	};
}