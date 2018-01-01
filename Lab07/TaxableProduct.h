/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: October 30, 2017				**
** OOP345 Section C - Workshop 7		**
** TaxableProduct.h						**
*****************************************/

#pragma once

#include <iomanip>
#include "Product.h"

namespace w7 {

	class TaxableProduct : public Product {
		std::string id;
		double price;
		char tax;
	public:
		TaxableProduct() {
			price = 0;
		} // default constructor

		TaxableProduct(std::string s, double p, char t) {
			id = s;
			price = p;
			tax = t;
		} // overloaded constructor

		double getCharge() const {
			double rate;

			if (tax == 'H') rate = 1.13;
			else if (tax == 'P') rate = 1.08;
			else rate = 1;

			return (price * rate);
		}

		void display(std::ostream& os) const {
			os << std::setw(10) << id;
			os << std::setw(10) << std::fixed << std::setprecision(2) << getCharge() << " ";
			if (tax == 'H') os << "HST\n";
			else if (tax == 'P') os << "PST\n";
			else os << "\n";
		}

	}; // class TaxableProduct

} // namespace w7