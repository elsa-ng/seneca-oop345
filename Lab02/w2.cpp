/***************************************** 
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: September 18, 2017				**
** OOP345 Section C - Workshop 2		**
** w2.cpp								**
*****************************************/

#include <iostream>
#include "Station.h"
#include "Stations.h"

int main(int argc, char* argv[]) {
	std::cout << "\nCommand Line : ";
	for (int i = 0; i < argc; i++)
		std::cout << argv[i] << ' ';

	std::cout << std::endl;
	if (argc != 2) {
		std::cerr << "\nIncorrect number of arguments\n";
		return 1;
	}

	w2::Stations stations(argv[1]);
	stations.update();
	stations.restock();
	stations.report();

	return 0;
}