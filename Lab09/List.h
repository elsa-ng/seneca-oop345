/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: January 1, 2018				**
** OOP345 Section C - Workshop 9		**
** List.h								**
*****************************************/

// Workshop 9 - Smart Pointers
// List.h

#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <memory>

namespace w9 {
	template <typename T>
	class List {
		std::vector<T> list;
	public:
		List() { }
		
		List(const char* fn) {
			std::ifstream file(fn);
			if (!file)
				throw std::string("*** Failed to open file ") +
				std::string(fn) + std::string(" ***");
			while (file) {
				T e;
				if (e.load(file))
					list.push_back(*new T(e));
			}
		}
		size_t size() const { return list.size(); }
		
		const T& operator[](size_t i) const { return list[i]; }
		
		void operator+=(std::unique_ptr<T> p) {
			list.push_back(std::move(*p));
		}
		
		void display(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : list)
				e.display(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const List<T>& l) {
		l.display(os);
		return os;
	}
}