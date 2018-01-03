/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: January 1, 2018				**
** OOP345 Section C - Milestone			**
** util.h								**
*****************************************/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void trimSpace(std::string& s);
void csvPrint(std::vector<std::vector<std::string>>& csvData);
void csvRead(std::string& filename, char sep, std::vector<std::vector<std::string>>& csvData);
bool validTaskName(std::string &s);
bool validSlots(std::string &s);
bool validItemName(std::string &s);
bool validSequenceNumber(std::string &s);