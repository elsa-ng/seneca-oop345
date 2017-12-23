#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "CString.h"
#include "process.h"


void process(char* s) {
	w1::CString cs(s);
	std::cout << cs << std::endl;
}