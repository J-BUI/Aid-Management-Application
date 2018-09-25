// Final Project Milestone 1
//
// Version 1.0
// Date:		Mar 11, 2018
// Author:		Jameson Bui #123160178
// Description:	Date.h
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef AMA_DATE_H
#define AMA_DATE_H
#include <iostream>

namespace AMA {
const int min_year = 2000;
const int max_year = 2030;
const int NO_ERROR = 0;		// No error - the date is valid
const int CIN_FAILED = 1;	// istream failed on information entry
const int YEAR_ERROR = 2;	// Year value is invalid
const int MON_ERROR = 3;	// Month value is invalid
const int DAY_ERROR = 4;	// Day value is invalid

class Date {
	int year;
	int mon;
	int day;
	int eCode;
	int cmp;

	int mdays(int, int)const;
	void errCode(int errorCode);
public:
// 	Constructors
	Date();
	Date(int y, int m, int d);
//	Deconstructor
	~Date();
//	Operators
	bool operator==(const Date& rhs) const;
	bool operator!=(const Date& rhs) const;
	bool operator<(const Date& rhs) const;
	bool operator>(const Date& rhs) const;
	bool operator<=(const Date& rhs) const;
	bool operator>=(const Date& rhs) const;
//	Queries and modifier
	int errCode() const;
	bool bad() const;
	std::istream& read(std::istream& istr);
	std::ostream& write(std::ostream& ostr) const;
};

// Helper functions
 std::ostream& operator<< (std::ostream& os, const Date& date);
 std::istream& operator>> (std::istream& is, Date& date);


}
#endif