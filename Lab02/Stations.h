/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: September 18, 2017				**
** OOP345 Section C - Workshop 2		**
** Stations.h							**
*****************************************/


#pragma once
#include <string>
#include "Station.h"

namespace w2 {
	class Stations {
		std::string filename;
		unsigned int noStations;
		Station* StationManager;
	public:
		Stations();
		Stations(char* filename);
		~Stations();
		void update() const;
		void restock() const;
		void report() const;
	}; // class Stations
} // namespace w2