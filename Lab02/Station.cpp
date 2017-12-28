/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: September 18, 2017				**
** OOP345 Section C - Workshop 2		**
** Station.cpp							**
*****************************************/


#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"

namespace w2 {
	Station::Station() {}

	void Station::set(const std::string& s, unsigned int st, unsigned int ad) {
		stationName = s;
		passes[PASS_STUDENT] = st;
		passes[PASS_ADULT] = ad;
	}

	void Station::update(PassType pt, int no) {
		if ((signed)passes[pt] >= -no) {
			passes[pt] += no;
		}
	}

	void Station::update() {
		int numS, numA;

		std::cout << getName() << std::endl;
		std::cout << " Student Passes sold : ";
		std::cin >> numS;
		update(PASS_STUDENT, -(numS));
		std::cin.ignore();

		std::cout << " Adult   Passes sold : ";
		std::cin >> numA;
		update(PASS_ADULT, -(numA));
		std::cin.ignore();
	}

	void Station::restock() {
		int numS, numA;
		std::cout << getName() << std::endl;
		std::cout << " Student Passes added : ";
		std::cin >> numS;
		update(PASS_STUDENT, numS);
		std::cin.ignore();

		std::cout << " Adult   Passes added : ";
		std::cin >> numA;
		update(PASS_ADULT, numA);
		std::cin.ignore();
	}

	void Station::report() {
		std::cout << std::setw(19) << std::left << getName()
			<< std::setw(6) << std::right << inStock(PASS_STUDENT)
			<< std::setw(6) << std::right << inStock(PASS_ADULT) << "\n";
	}

	void Station::write(std::ostream& os) {
		os << getName() << ";" << inStock(PASS_STUDENT) << " " << inStock(PASS_ADULT) << "\n";
	}

	unsigned Station::inStock(PassType pt) {
		return passes[pt];
	}

	const std::string& Station::getName() const {
		return stationName;
	}
} // namespace w2