/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: January 1, 2018				**
** OOP345 Section C - Milestone			**
** order.cpp							**
*****************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"

class Order {
	std::string customer, product;
	std::vector<std::string> itemList;
public:
	Order() {}

	Order(std::vector<std::string>& line) {
		if (line.size() < 3)
			throw std::string("expected 3 or more fields, found ") + std::to_string(line.size());

		customer = line[0];
		product = line[1];

		for (size_t item = 2; item < line.size(); item++) {
			if (line[item].empty())
				continue;

			if (validItemName(line[item]))
				itemList.push_back(std::move(line[item]));
			else
				throw std::string("item name not understood -->") + line[item] + "<--";

		}
	}

	void print() {
		std::cout << "|customer|product|item 1|item 2|...| = "
			<< "|" << customer
			<< "|" << product;
		for (auto& item : itemList)
			std::cout << "|" << item;
		std::cout << "|\n";
	}

	void graph(std::fstream& gv) {
		for (auto& item : itemList) {
			gv << '"' << customer << '"' << "\n"
				<< " -> "
				<< '"' << product << '"' << "[color=red];" << "\n";
			
			gv	<< '"' << product << '"' << "\n"
				<< " -> "
				<< '"' << "Item " << item << '"'
				<< "[color=blue];" << "\n";

			
		}
	}

}; // class Order

class OrderManager {
	std::vector<Order> orderList;
public:
	OrderManager(std::vector<std::vector<std::string>>& csvData) {
		for (auto& line : csvData) {
			try {
				orderList.push_back(Order(line));
			}
			catch (const std::string& e) {
				std::cerr << "problem: " << e << "\n";
			}
		}
	}

	void print() {
		for (auto& order : orderList)
			order.print();
	}

	void graph(std::string& filename) {
		std::fstream gv(filename + ".gv", std::ios::out | std::ios::trunc);
		if (gv.is_open()) {
			gv << "digraph orderGraph {\n";
			for (auto& order : orderList)
				order.graph(gv);
			gv << "}\n";
			gv.close();

			std::vector<std::string> dotLocations{
				"/usr/bin/dot",
				"/usr/local/bin/dot",
				"C:/\"Program Files (x86)\"/Graphviz2.38/bin/dot.exe"
			};

			std::string dot;
			for (auto& e : dotLocations) {
				auto fileexist = [](std::string file) {std::fstream f(file, std::ios::in); return f.is_open(); };
				if (fileexist(e)) {
					dot = std::move(e);
					break;
				}
			}

			if (dot.empty()) {
				std::cerr << R"foo(Graphviz program "dot" not found! Package "graphviz" is not isntalled.)foo";
				return;
			}
			std::string cmd = dot;
			cmd += " -Tpng -O " + filename + ".gv";
			std::cout << "Running command -->" << cmd << "<--\n";
			int result = system(cmd.c_str());
			std::cout << "It returned " << result << (result ? "'(command failed)\n" : "'(command passed)\n");
		}
	}

}; // class OrderManager

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " order-csv-file order-csv-separator\n";
		return 1;
	}

	std::string filename = argv[1];
	char sep = argv[2][0];
	try {
		std::vector<std::vector<std::string>> csvData;
		csvRead(filename, sep, csvData);
		csvPrint(csvData);

		OrderManager om(csvData);
		om.print();
		om.graph(filename);

		return 0;
	}
	catch (const std::string& e) {
		std::cerr << "It threw --> " << e << "\n";
	}
	return 1;
}