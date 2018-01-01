/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: October 30, 2017				**
** OOP345 Section C - Workshop 7		**
** Sale.h								**
*****************************************/

#pragma once

#include <vector>
#include "iProduct.h"

namespace w7 {

	class Sale {
		std::vector<iProduct*> productList;
	public: 
		Sale();
		Sale(const char*);
		void display(std::ostream&) const;
	}; // class Sale

} // namespace w7