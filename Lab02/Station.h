/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: September 18, 2017				**
** OOP345 Section C - Workshop 2		**
** Station.h							**
*****************************************/


#pragma once
#include <string>

namespace w2 {
	enum PassType { PASS_STUDENT, PASS_ADULT, PASS_COUNT };

	class Station {
		std::string stationName;
		unsigned passes[PASS_COUNT];
	public:
		Station();
		void set(const std::string& s, unsigned int st, unsigned int ad);
		void update(PassType pt, int no);
		void update();
		void restock();
		void report();
		void write(std::ostream& os);
		unsigned inStock(PassType pt);
		const std::string& getName() const;
	}; // class Station
} // namespace w2
