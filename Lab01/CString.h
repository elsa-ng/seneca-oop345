/* Name: Wai Chi Ng
** Student ID: 140634163
** Email: wcng1@myseneca.ca
** Date: September 9, 2017
** OOP345 Section C - Workshop 1
** CString.h
*/

#pragma once

#include <iostream>

namespace w1 {
	const int MAX = 3;

	class CString {
		char str[MAX + 1];
	public:
		CString(char* s);
		void display(std::ostream& os) const;
	}; // class CString

	std::ostream& operator<<(std::ostream& os, w1::CString& cs);
} // namespace w1