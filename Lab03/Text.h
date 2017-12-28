/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: September 20, 2017				**
** OOP345 Section C - Workshop 3		**
** Text.h								**
*****************************************/

#pragma once

#include <string>

namespace w3 {
	class Text {
		size_t count = 0;
		std::string* sArray = nullptr;
	public:
		Text();									// default constructor
		Text(char* filename);					// overloaded constructor
		Text(const Text& t);					// copy constructor
		Text& operator=(const Text& t);			// copy assignment operator
		Text(Text&& t);							// move constructor
		Text&& operator=(Text&& t);				// move assignment operator
		~Text();								// destructor
		size_t size() const;					// member function that returns the number of records of text data
	}; // class Text
} // namespace w3

