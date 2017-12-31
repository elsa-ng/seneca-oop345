/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: October 10, 2017				**
** OOP345 Section C - Workshop 5		**
** Message.h							**
*****************************************/

#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace w5 {
	
	class Message {
		std::string name;
		std::string reply;
		std::string tweet;
	public:
		Message();
		Message(std::ifstream& in, char c);
		bool empty() const;
		void display(std::ostream& os) const;
		void reset();
	}; // class Message

} // namespace w5