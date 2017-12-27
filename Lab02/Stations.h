#pragma once
#include <string>
#include "Station.h"

namespace w2 {
	class Stations {
		std::string filename;
		unsigned int noStations;
		Station* StationManager = nullptr;
	public:
		Stations();
		Stations(char* filename);
		~Stations();
		void update() const;
		void restock() const;
		void report() const;
	}; // class Stations
} // namespace w2