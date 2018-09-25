// Final Project Milestone 2
//
// Version 1.0
// Date:		Mar 20, 2018
// Author:		Jameson Bui #123160178
// Description:	ErrorState.h
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef AMA_ErrorState_H
#define AMA_ErrorState_H
#include <iostream>

namespace AMA {

class ErrorState
{
	char* eMsg;

public:
	// Constructor
	explicit ErrorState(const char* errorMessage = nullptr);

	// Destructor
	virtual ~ErrorState();

	// these prevent the assignment to the object or copying
	ErrorState(const ErrorState& em) = delete;
	ErrorState& operator=(const ErrorState& em) = delete;
	
	// member functions
	void clear();
	bool isClear() const;
	void message(const char* str);
	const char* message()const;

	// Helper operators
	friend std::ostream& operator<< (std::ostream& os, const ErrorState& es);

};

}

#endif