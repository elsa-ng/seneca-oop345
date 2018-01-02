/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: January 1, 2018				**
** OOP345 Section C - Workshop 10		**
** SecureData.cpp						**
*****************************************/

// Workshop 10 - Multi-Threading
// SecureData.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <thread>
#include "SecureData.h"

namespace w10 {

	void converter(char* t, char key, int n, const Cryptor& c) {
		for (int i = 0; i < n; i++)
			t[i] = c(t[i], key);
	}

	SecureData::SecureData(const char* file, char key) {
		// open text file
		std::fstream input(file, std::ios::in);
		if (!input)
			throw std::string("\n***Failed to open file ") +
			std::string(file) + std::string(" ***\n");

		// copy from file into memory
		nbytes = 0;
		input >> std::noskipws;
		while (input.good()) {
			char c;
			input >> c;
			nbytes++;
		}
		nbytes--;
		input.clear();
		input.seekg(0, std::ios::beg);
		text = new char[nbytes + 1];

		int i = 0;
		while (input.good())
			input >> text[i++];
		text[--i] = '\0';
		std::cout << "\n" << nbytes << " bytes copied from text "
			<< file << " into memory (null byte added)\n";
		encoded = false;

		// encode using key
		code(key);
		std::cout << "Data encrypted in memory\n";
	}

	SecureData::~SecureData() {
		delete[] text;
	}

	void SecureData::display(std::ostream& os) const {
		if (text && !encoded)
			os << text << std::endl;
		else if (encoded)
			throw std::string("\n***Data is encoded***\n");
		else
			throw std::string("\n***No data stored***\n");
	}

	void SecureData::code(char key) {
		auto convert = std::bind(converter, text, key, nbytes, Cryptor());

		std::thread t1(convert);
		std::thread t2(convert);
		std::thread t3(convert);

		t1.join();
		t2.join();
		t3.join();

		encoded = !encoded;
	}

	void SecureData::backup(const char* file) {
		if (!text)
			throw std::string("\n***No data stored***\n");
		else if (!encoded)
			throw std::string("\n***Data is not encoded***\n");
		else {
			// open binary file
			std::fstream bf(file, std::ios::out | std::ios::binary | std::ios::trunc);

			// write binary file here
			bf.write(text, nbytes);
			bf.close();

		}
	}

	void SecureData::restore(const char* file, char key) {
		delete[] text;
		nbytes = 0;
		// open binary file
		std::fstream bf(file, std::ios::in | std::ios::binary);

		// get length of file
		if (bf) {
			nbytes = 0;
			bf >> std::noskipws;
			while (!bf.eof()) {
				char temp;
				bf >> temp;
				nbytes++;
			}

			// allocate memory here
			nbytes--;
			bf.clear();
			bf.seekg(0, std::ios::beg);
			text = new char[nbytes + 1];

			// read binary file here
			bf.read(text, nbytes);
			text[nbytes] = '\0';

			std::cout << "\n" << nbytes + 1 << " bytes copied from binary file "
				<< file << " into memory (null byte included)\n";
			
			encoded = true;

			// decode using key
			code(key);
			std::cout << "Data decrypted in memory\n\n";

			bf.close();
		}
		else {
			throw std::string("Cannot read from file");
		}
	}

	std::ostream& operator<<(std::ostream& os, const SecureData& sd) {
		sd.display(os);
		return os;
	}

}