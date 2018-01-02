/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: January 1, 2018				**
** OOP345 Section C - Workshop 8		**
** DataTable.h							**
*****************************************/

#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <iostream>


namespace w8 {

	template <class T>
	class DataTable {
		std::vector<T> x, y;
		int width;
		int decimal;
	public:
		DataTable() : width(0), decimal(0){
		} // default constructor

		DataTable(std::ifstream& in, int w, int d) : width(w), decimal(d) {
			while (in.good()) {
				std::string line;
				std::stringstream temp; // to use stream operator >>
				T fx, fy;				// to store x, y values
				
				getline(in, line);
				
				if (!line.empty()) {
					temp.str(line);
					temp >> fx >> fy;

					x.push_back(fx);
					y.push_back(fy);
				}
			}
		}

		// return mean value of the y coordinate
		T mean() const {
			T result = std::accumulate(y.begin(), y.end(), (T)0.) / (T)y.size();
			return result;
		}

		// return the stadnard deviation of the y coordinate
		T sigma() const {
			T sum = std::accumulate(y.begin(), y.end(), (T)0.);
			T mean = std::accumulate(y.begin(), y.end(), (T)0.) / (T)y.size();

			T acc = 0.0;

			// formula obtained from Stack Overflow
			std::for_each(y.begin(), y.end(), [&](const T d) {
				acc += (d - mean) * (d - mean);
			});

			T result = sqrt(acc / ((T)y.size() - 1));

			return result;
		}

		// return median of y coordinate
		T median() const {
			
			// sort a copy of y so not to temper with the original container
			std::vector<T> temp = y;
			sort(temp.begin(), temp.end());
			return temp[temp.size() / 2];
		}

		// calculate the slop and y_intercept of a line
		// formula obtained from Stack Overflow
		void regression(T& slope, T& y_intercept) const {
			// line: y = mx + b
			// slope = (Y2 - Y1) / (X2 - X1)
			// y-intercept: b = y - mx
			T xSize = (T)x.size();
			T SX = std::accumulate(x.begin(), x.end(), (T)0.);
			T SY = std::accumulate(y.begin(), y.end(), (T)0.);
			T SXX = std::inner_product(x.begin(), x.end(), x.begin(), (T)0.);
			T SXY = std::inner_product(x.begin(), x.end(), y.begin(), (T)0.);
			
			slope = (xSize * SXY - SX * SY) / (xSize * SXX - SX * SX);
			y_intercept = mean() - slope * (SX / xSize);
		}

		// output the value from x and y to console when there are more than 2 command line arguments
		void display(std::ostream& os) const {
			os << std::setw(width) << std::right << "x";
			os << std::setw(width+1) << std::right << "y\n";
			
			for (unsigned i = 0; i < x.size(); i++) {
				os << std::setw(width) << std::fixed << std::setprecision(decimal) << x[i];
				os << std::setw(width) << std::fixed << std::setprecision(decimal) << y[i] << std::endl;
			}
		}

	}; // class DataTable

	template <class T>
	std::ostream& operator<<(std::ostream& os, const DataTable<T> &d) {
		d.display(os);
		return os;
	}

} // namespace w8