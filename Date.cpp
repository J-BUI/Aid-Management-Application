// Final Project Milestone 1
//
// Version 1.0
// Date:		Mar 11, 2018
// Author:		Jameson Bui #123160178
// Description:	Date.cpp
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#include "Date.h"
#include <cstring>
#include <iostream>
#include <iomanip>


namespace AMA {
// Constructors
Date::Date()
{
	year = 0000;
	mon = 00;
	day = 00;
	cmp = 0;
	errCode(NO_ERROR);
}
Date::Date(int y, int m, int d)
{
	if (y > max_year || y < min_year) { errCode(YEAR_ERROR); }
	else if (m > 12 || m < 1)  { errCode(MON_ERROR); }
	else if (d > mdays(m, y) || d < 1) { errCode(DAY_ERROR); }
	else
	{
		year = y;
		mon = m;
		day = d;
		errCode(NO_ERROR);
		cmp = (y * 374 + m * 13 + d);
	}

	if (bad()) { *this = Date(); }
}

// Member Functions
int Date::mdays(int mon, int year)const {
	int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
	int month = mon >= 1 && mon <= 12 ? mon : 13;
	month--;
	return days[month] + int((month == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}
void Date::errCode(int errorCode) {
	eCode = errorCode;
}
// Operators
bool Date::operator==(const Date& rhs)const {
	int flag = 0;
	if (this->cmp == 0 || rhs.cmp == 0) { flag = 0; }
	else if (this->cmp == rhs.cmp) { flag = 1; }
	return flag;
}
bool Date::operator!=(const Date& rhs)const {
	int flag = 0;
	if (this->cmp == 0 || rhs.cmp == 0) { flag = 0; }
	else if (this->cmp != rhs.cmp) { flag = 1; }
	return flag;
}
bool Date::operator<(const Date& rhs)const {
	int flag = 0;
	if (this->cmp == 0 || rhs.cmp == 0) { flag = 0; }
	else if (this->cmp < rhs.cmp) { flag = 1; }
	return flag;
}
bool Date::operator>(const Date& rhs)const {
	int flag = 0;
	if (this->cmp == 0 || rhs.cmp == 0) { flag = 0; }
	else if (this->cmp > rhs.cmp) { flag = 1; }
	return flag;
}
bool Date::operator<=(const Date& rhs)const {
	int flag = 0;
	if (this->cmp == 0 || rhs.cmp == 0) { flag = 0; }
	else if (this->cmp <= rhs.cmp) { flag = 1; }
	return flag;
}
bool Date::operator>=(const Date& rhs)const {
	int flag = 0;
	if (this->cmp == 0 || rhs.cmp == 0) { flag = 0; }
	else if (this->cmp >= rhs.cmp) { flag = 1; }
	return flag;
}

//	Queries and modifier
int Date::errCode() const {
	return eCode;
}
bool Date::bad() const {
	int flag;
	(eCode != 0) ? flag = 1 : flag = 0;
	return flag;
}
std::istream& Date::read(std::istream& istr) {

	istr >> year;
	if (istr.fail()) { eCode = CIN_FAILED; }
	else if (year > max_year || year < min_year) { errCode(YEAR_ERROR); }

	istr.ignore();

	istr >> mon;
	if (istr.fail()) { eCode = CIN_FAILED; }
	else if (mon > 12 || mon < 1) { errCode(MON_ERROR); }

	istr.ignore();

	istr >> day;
	if (istr.fail()) { eCode = CIN_FAILED; }
	else if (mon <= 12 && mon >= 1) {
		if (day > mdays(mon, year) || day < 1) { errCode(DAY_ERROR); }
	}

	if (bad()) {
		year = 0000;
		mon = 00;
		day = 00;
		cmp = 0;
	}

	return istr;
}
std::ostream& Date::write(std::ostream& ostr)const {
	ostr << year << "/"
		// Make sure day and month are 2 digit to match yyyy/mm/dd format
	     << std::setfill('0') << std::setw(2) << mon << "/"
	     << std::setfill('0') << std::setw(2) << day << std::setfill(' ');
	return ostr;
}

//	Helper functions
std::ostream& operator<< (std::ostream & os, const Date & date) {
	date.write(os);
	return os;
}
std::istream& operator>> (std::istream & is, Date & date) {
	date.read(is);
	return is;
}

// Destructor
Date::~Date() {}

}
