/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: September 20, 2017				**
** OOP345 Section C - Workshop 3		**
** Text.cpp								**
*****************************************/

#include <utility>
#include <iostream>
#include <fstream>
#include "Text.h"

namespace w3 {
	Text::Text() {
	} // default constructor

	Text::Text(char* filename) {
		std::fstream in(filename, std::ios::in);
		
		if (!in.is_open()) {
			std::cerr << "Cannot open file '" << filename << "'\n";
			exit(99);
		}
		else {
			std::string line;

			// count the number of records
			while (getline(in, line)) {
				count++;
			}

			// allocate dynamic resource for the number of records stored in file
			sArray = new std::string[count];
		}

		// clear end of file error state
		in.clear();

		// position cursor at the beginning of file
		in.seekp(0);

		// assign records to sArray
		for (size_t i = 0; i < count; i++) {
			getline(in, sArray[i]);
		}

		in.close();
	} // overloaded constructor

	Text& Text::operator=(const Text& t) {
		if (this != &t) {
			delete[] sArray;
			sArray = nullptr;
			count = 0;

			if (t.sArray){
				count = t.count;
				sArray = new std::string[count];
				for (size_t i = 0; i < count; i++) {
					sArray[i] = t.sArray[i];
				}
			}
		}

		return *this;
	} // copy assignment operator

	Text::Text(const Text& t) {
		*this = t;
	} // copy constructor

	Text&& Text::operator=(Text&& t) {
		if (this != &t) {
			delete[] sArray;
			sArray = t.sArray;
			count = t.count;
			t.sArray = nullptr;
			t.count = 0;
		}

		return std::move(*this);
	} // move assignment operator

	Text::Text(Text&& t) {
		sArray = nullptr;
		*this = std::move(t);
	} // move constructor

	Text::~Text() {
		delete[] sArray;
	} // destructor

	size_t Text::size() const {
		return count;
	} // size()
} // namespace w3