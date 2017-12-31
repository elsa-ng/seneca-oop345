/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: October 20, 2017				**
** OOP345 Section C - Workshop 6		**
** w6.cpp								**
*****************************************/

// Workshop 6 - Lambda Expression
// w6.cpp

#include <iostream>
#include <string>

#include "Grades.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cerr << argv[0] <<
			": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name\n";
		return 1;
	}

	Grades grades(argv[1]);

	auto letter = [](double grade) -> std::string {
		if (grade >= 90.00 && grade <= 100.00)
			return "A+";
		else if (grade >= 80.00 && grade <= 89.99)
			return "A";
		else if (grade >= 75.00 && grade <= 79.99)
			return "B+";
		else if (grade >= 70.00 && grade <= 74.99)
			return "B";
		else if (grade >= 65.00 && grade <= 69.99)
			return "C+";
		else if (grade >= 60.00 && grade <= 64.99)
			return "C";
		else if (grade >= 55.00 && grade <= 59.99)
			return "D+";
		else if (grade >= 50.00 && grade <= 54.99)
			return "D";
		else 
			return "F";
	};

	grades.displayGrades(std::cout, letter);




	std::cout << "Press any key to continue ... ";
	std::cin.get();

	return 0;
}
