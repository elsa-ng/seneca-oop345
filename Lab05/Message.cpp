/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: October 10, 2017				**
** OOP345 Section C - Workshop 5		**
** Message.cpp							**
*****************************************/

#include <iomanip>
#include "Message.h"

namespace w5 {

	Message::Message() {
	}// default constructor

	// retrieve a record from file object "in"
	// parse record and store its components in messageManager
	Message::Message(std::ifstream& in, char c) {
		std::string line;
		getline(in, line, c);

		auto cr = line.find('\r');
		if (cr != std::string::npos) {
			line.erase(cr);
		} // npos = no position, position not found

		size_t index = 0;

		// process username
		while (index < line.size() && line[index] != ' ') {
			name += line[index];
			index++;
		} // username

		// skip a space if present
		if (line[index] == ' ')
			index++;

		// process @reply if present
		if (index < line.size() && line[index] == '@') {
			index++; // skip the '@'
			while (index < line.size() && line[index] != ' ') {
				reply += line[index];
				index++;
			}
		} // @reply

		// skip a space if present
		if (line[index] == ' ')
			index++;

		// process tweet
		while (index < line.size()) {
			tweet += line[index];
			index++;
		} // tweet

	} // overloaded constructor
	
	bool Message::empty() const {
		return tweet.empty();
	} // empty()
	
	void Message::display(std::ostream& os) const {
		if (!empty()) {
			os << "Message\n";
			os << " " << std::setw(5) << std::setiosflags(std::ios::left) << "User" << " : " << name << "\n";
			if (!reply.empty()) {
				os << " " << "Reply" << " : " << reply << "\n";
			}
			os << " " << "Tweet" << " : " << tweet << "\n";
		}
	} // display()
	
	// clear Message
	void Message::reset() {
		name.clear();
		reply.clear();
		tweet.clear();
	} // reset()

} // namespace w5