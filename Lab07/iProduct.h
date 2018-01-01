/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: October 30, 2017				**
** OOP345 Section C - Workshop 7		**
** iProduct.h							**
*****************************************/

#pragma once

// Workshop 7 - STL Containers
// iProduct.h

namespace w7 {

	class iProduct {
	public:
		virtual double getCharge() const = 0;
		virtual void display(std::ostream&) const = 0;
	}; // class iProduct

	std::ostream& operator<<(std::ostream& os, const iProduct& p);
	iProduct* readProduct(std::ifstream& is);

} // namespace w7
