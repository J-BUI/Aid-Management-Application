// Final Project Milestone 2
//
// Version 1.0
// Date:		Mar 20, 2018
// Author:		Jameson Bui #123160178
// Description:	ErrorState.cpp
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include <cstring>
#include "ErrorState.h"
using namespace std;

namespace AMA {

// Constructors
ErrorState::ErrorState(const char* errorMessage)
{
	if (errorMessage != nullptr) {
		eMsg = nullptr;
		message(errorMessage);
	}
	else { eMsg = nullptr; }
}

// destructor
ErrorState::~ErrorState()
{
	if (eMsg != nullptr) {
		delete [] eMsg;
	}
}

// clears any message stored by the current object and initializes the object to a safe empty state.
void ErrorState::clear()
{
	if (eMsg != nullptr) {
		delete [] eMsg;
		eMsg = nullptr;
	}

}

bool ErrorState::isClear() const
{
	int flag = 0;
	if (eMsg == nullptr || eMsg[0] == '\0') { flag = 1; }
	return flag;
}

// this function is basically a set function
void ErrorState::message(const char* str)
{
	// de-allocates any memory allocated for a previously stored message
	clear();
	// allocate enough memory for str + null terminator
	eMsg =  new (nothrow) char [strlen(str) + 1];
	// copy
	if (eMsg != nullptr) {
		strncpy(eMsg, str, strlen(str));
		eMsg[strlen(str)] = '\0';

	}
}

const char* ErrorState::message() const
{
	return eMsg;
}

std::ostream& operator<< (std::ostream& os, const ErrorState& es)
{
	if (!es.isClear())
	{
		os << es.message();
	}

	return os;
}










}