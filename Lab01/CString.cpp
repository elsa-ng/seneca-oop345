/* Name: Wai Chi Ng
** Student ID: 140634163
** Email: wcng1@myseneca.ca
** Date: September 9, 2017
** OOP345 Section C - Workshop 1
** CString.cpp
*/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "CString.h"

namespace w1 {
	CString::CString(char* s) {
		if (s[0] == '\0') {
			str[0] = '\0';
		}
		else {
			strncpy(str, s, MAX);
			str[MAX] = '\0';
		}
	}

	void CString::display(std::ostream& os) const {
		os << str;
	}

	std::ostream& operator<<(std::ostream& os, w1::CString& cs) {
		static int count = 0;
		os << count << ": ";
		cs.display(os);
		count++;
		return os;
	}
} // namespace w1

