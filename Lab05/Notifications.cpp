/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: October 10, 2017				**
** OOP345 Section C - Workshop 5		**
** Notifications.cpp					**
*****************************************/

#include <iostream>
#include "Notifications.h"

namespace w5 {
	Notifications::Notifications() {
	} // default constructor

	Notifications::Notifications(const Notifications& src) {
		*this = src;
	} // copy constructor

	Notifications& Notifications::operator=(const Notifications& src) {
		if (this != &src) {

			// delete our brains
			for (size_t i = 0; i < count; i++) {
				messageManager[i].reset();
			}
			count = 0;

			// steal brains from src
			if (src.messageManager) {
				count = src.count;
				for (size_t i = 0; i < count; i++) {
					messageManager[i] = src.messageManager[i];
				}
			}
		}

		return *this;
	} // copy assignment operator

	Notifications::Notifications(Notifications&& src) {
		*this = std::move(src);
	} // move constructor

	Notifications&& Notifications::operator=(Notifications&& src) {
		if (this != &src) {

			// kill our brains
			for (size_t i = 0; i < count; i++) {
				messageManager[i].reset();
			}
			count = 0;

			// move src to *this
			count = src.count;
			for (size_t i = 0; i < count; i++) {
				messageManager[i] = src.messageManager[i];
				src.messageManager[i].reset();	// turn src into zombie
			}
			src.count = 0;
		}

		return std::move(*this);
	} // move assignment operator

	Notifications::~Notifications() {
	} // destructor

	// add msg to the set
	void Notifications::operator+=(const Message& msg) {
		if (count < MAX_MESSAGE) {
			messageManager[count] = std::move(msg);
			count++;
		}
		else {
			std::cerr << __FILE__ << ":" << __LINE__
				<< " compiled on " << __DATE__ << " at " << __TIME__
				<< " messageTable FULL!" << std::endl
				<< "increase MESSAGE_MAX and recompile" << std::endl;
			exit(99);
		}
	} // operator+=

	// inserts the Message objects to the os output stream
	void Notifications::display(std::ostream& os) const {
		for (size_t i = 0; i < count; i++) {
			messageManager[i].display(os);
		}
	} // display()

} // namespace w5

