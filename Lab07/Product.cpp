/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: October 30, 2017				**
** OOP345 Section C - Workshop 7		**
** Product.cpp							**
*****************************************/

#include <fstream>
#include <string>
#include "Product.h"
#include "TaxableProduct.h"

namespace w7 {
	
	Product::Product() {
		price = 0;
	} // default constructor

	Product::Product(std::string s, double p) {
		id = s;
		price = p;
	}

	double Product::getCharge() const {
		return price;
	}

	void Product::display(std::ostream& os) const {
		os << std::setw(10) << id;
		os << std::setw(10) << std::fixed << std::setprecision(2) << getCharge() << "\n";
	}

	std::ostream& operator<<(std::ostream& os, const iProduct& p) {
		p.display(os);
		return os;
	}

	iProduct* readProduct(std::ifstream& is) {
		iProduct* temp = nullptr;
		std::string line;

		getline(is, line, '\n');

		if (line.size() <= 1) {
			throw "File has an empty line in the end";
		}
		else {
			std::string id;
			std::string sPrice;
			char tax;
			size_t index = 0;



			// read product id as string
			while (index < line.size() && line[index] != ' ') {
				id += line[index];
				index++;
			}

			// skip a space if present
			if (line[index] == ' ')
				index++;

			// read price as string then converts to double
			while (index < line.size() && line[index] != ' ') {
				sPrice += line[index];
				index++;
			}

			// if it is the end of file create a new Product
			// else keep reading and get tax character
			if (index == line.size() || line[index] == '\n') {
				temp = new Product(id, std::stod(sPrice));
			}
			else {
				if (line[index] == ' ') {
					index++;
				}
				tax = line[index];
				temp = new TaxableProduct(id, std::stod(sPrice), tax);
			}

			return temp;
		}
	} // readProduct()

} // namespace w7
