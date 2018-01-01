/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: October 30, 2017				**
** OOP345 Section C - Workshop 7		**
** Product.h							**
*****************************************/

#pragma once

#include "iProduct.h"

namespace w7 {

	class Product : public iProduct {
		std::string id;
		double price;
	public:
		Product();
		Product(std::string, double);
		double getCharge() const;
		void display(std::ostream&) const;
	}; // class Product

} // namespace w7
