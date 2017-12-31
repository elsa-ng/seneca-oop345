/*****************************************
** Name: Wai Chi Ng						**
** Student ID: 140634163				**
** Email: wcng1@myseneca.ca				**
** Date: October 10, 2017				**
** OOP345 Section C - Workshop 5		**
** Notifications.h						**
*****************************************/

#pragma once

#include <iostream>
#include "Message.h"

namespace w5 {

	const size_t MAX_MESSAGE = 10;

	class Notifications {
		Message messageManager[MAX_MESSAGE];
		size_t count = 0;
	public:
		Notifications();
		Notifications(const Notifications&);
		Notifications& operator=(const Notifications&);
		Notifications(Notifications&&);
		Notifications&& operator=(Notifications&&);
		~Notifications();
		void operator+=(const Message& msg);
		void display(std::ostream& os) const;
	}; // class Notifications

} // namespace w5