/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: October 30, 2017				**
** OOP345 Section C - Workshop 7		**
** Sale.cpp								**
*****************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Sale.h"

namespace w7 {

	Sale::Sale() {
	} // default constructor

	Sale::Sale(const char* filename) {
		std::ifstream in(filename, std::ios::in);
		
		try
		{
			if (in.is_open()) {
				while (in.good()) {
					iProduct* product = readProduct(in);
					productList.push_back(product);
				}
				in.close();
			}
			else {
				std::cerr << "Cannot open file\n";
				exit(99);
			}
		}
		catch (const char* msg)
		{
			std::cout << msg << std::endl;
		}
	} // overloaded constructor

	void Sale::display(std::ostream& os) const {
		double total = 0;

		os << "Product No";
		os << std::setw(10) << std::right << "Cost";
		os << " Taxable\n";

		for (auto index : productList) {
			index->display(os);
			total += index->getCharge();
		}

		os << std::setw(10) << "Total";
		os << std::setw(10) << std::fixed << std::right;
		os << total << "\n";
	}

} // namespace w7