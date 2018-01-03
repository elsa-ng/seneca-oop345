/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: January 1, 2018				**
** OOP345 Section C - Milestone			**
** task.cpp								**
*****************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"

class Task {
	std::string name, pass, fail, slots;
public:
	Task() {}
	Task(std::vector<std::string>& line) {
		switch (line.size()) {
		case 4:
			if (validTaskName(line[3]))
				fail = line[3];
			else
				throw std::string("fail task name not understood -->") + line[3] + "<--";

		case 3:
			if (validTaskName(line[2]))
				pass = line[2];
			else 
				throw std::string("pass task name not understood -->") + line[2] + "<--";

		case 2:
			if (validSlots(line[1]))
				slots = line[1];
			else 
				throw std::string("slots not understood -->") + line[1] + "<--";

		case 1:
			if (validTaskName(line[0]) && !line[0].empty())
				name = line[0];
			else 
				throw std::string("task name not understood -->") + line[0] + "<--";

			if (slots.empty())
				slots = "1";
			break;

		default:
			throw std::string("expected 1, 2, 3, or 4 fields, found ") + std::to_string(line.size());
		}
	}

	void print() {
		std::cout << "|name|slots|pass|fail| = "
			<< "|" << name
			<< "|" << slots
			<< "|" << pass
			<< "|" << fail
			<< "|\n";
	}

	void graph(std::fstream& gv) {
		if (pass.empty() && fail.empty())
			gv << '"' << name << '"' << "[shape=box];\n";

		if (!pass.empty())
			gv << '"' << name << '"'
				<< " -> "
				<< '"' << pass << '"'
				<< "[color=green];\n";

		if (!fail.empty())
			gv << '"' << name << '"'
			<< " -> "
			<< '"' << fail << '"'
			<< "[color=red];\n";
	}

}; // class Task

class TaskManager {
	std::vector<Task> taskList;
public:
	TaskManager(std::vector<std::vector<std::string>>& csvData) {
		for (auto& line : csvData) {
			try {
				taskList.push_back(Task(line));
			}
			catch (const std::string& e) {
				std::cerr << "problem: " << e << "\n";
			}
		}
	}

	void print() {
		for (auto& t : taskList)
			t.print();
	}

	void graph(std::string& filename) {
		std::fstream gv(filename + ".gv", std::ios::out | std::ios::trunc);
		if (gv.is_open()) {
			gv << "digraph taskGraph {\n";
			for (auto& t : taskList)
				t.graph(gv);
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

}; // class TaskManager

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " task-csv-file task-csv-separator\n";
		return 1;
	}

	std::string filename = argv[1];
	char sep = argv[2][0];

	try {
		std::vector<std::vector<std::string>> csvData;
		csvRead(filename, sep, csvData);
		csvPrint(csvData);

		TaskManager tm(csvData);
		tm.print();
		tm.graph(filename);

		return 0;
	}
	catch (const std::string& e) {
		std::cerr << "It threw --> " << e << "\n";
	}
	return 1;
}