/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: January 1, 2018				**
** OOP345 Section C - Milestone			**
** item.cpp								**
*****************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"

class Item {
	std::string name, installer, remover, sequenceNumer, description;
public:
	Item(){}

	Item(std::vector<std::string>& line) {
		switch (line.size()) {
		case 5:
			description = line[4];
		case 4:
			if (validSequenceNumber(line[3]))
				sequenceNumer = line[3];
			else
				throw std::string("sequence number not understood -->") + line[3] + "<--";

			if (validTaskName(line[2]))
				remover = line[2];
			else
				throw std::string("remover task name not understood -->") + line[2] + "<--";

			if (validTaskName(line[1]))
				installer = line[1];
			else
				throw std::string("installer task name not understood -->") + line[1] + "<--";

			if (validItemName(line[0]) && !line[0].empty())
				name = line[0];
			else
				throw std::string("item name not understand -->") + line[0] + "<--";
			
			break;
		default:
			throw std::string("expected 4, or 5 fields, found ") + std::to_string(line.size());
		}
	}

	void print() {
		std::cout << "|name|installer|remover|sequenceNumber|description| = "
			<< "|" << name
			<< "|" << installer
			<< "|" << remover
			<< "|" << sequenceNumer
			<< "|\n";
	}

	void graph(std::fstream& gv) {
		gv << '"' << "Item " << name << '"' << "\n"
			<< " -> "
			<< '"' << "Installer " << installer << '"'
			<< "[color=green];" << "\n";

		gv << '"' << "Item " << name << '"' << "\n"
			<< " -> "
			<< '"' << "Remover " << remover << '"'
			<< "[color=red];" << "\n";
	}
}; // class Item

class ItemManager {
	std::vector<Item> itemList;
public:
	ItemManager(std::vector<std::vector<std::string>>& csvData) {
		for (auto& line : csvData) {
			try {
				itemList.push_back(Item(line));
			}
			catch (const std::string& e) {
				std::cerr << "problem: " << e << "\n";
			}
		}
	}

	void print() {
		for (auto& item : itemList)
			item.print();
	}

	void graph(std::string& filename) {
		std::fstream gv(filename + ".gv", std::ios::out | std::ios::trunc);
		if (gv.is_open()) {
			gv << "digraph itemGraph {\n";
			for (auto& item : itemList)
				item.graph(gv);
			gv << "}\n";
			gv.close();

			std::vector<std::string> dotLocations{
				"/usr/bin/dot",
				"usr/local/bin/dot",
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

}; // class ItemManager

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " item-csv-file item-csv-seperater\n";
		return 1;
	}

	std::string filename = argv[1];
	char sep = argv[2][0];

	try {
		std::vector<std::vector<std::string>> csvData;
		csvRead(filename, sep, csvData);
		csvPrint(csvData);

		ItemManager im(csvData);
		im.print();
		im.graph(filename);

		return 0;
	}
	catch (const std::string& e) {
		std::cerr << "It threw --> " << e << "\n";
	}

	return 1;
}
