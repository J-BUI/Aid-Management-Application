// Final Project - Milestone 5 - Perishable Class
// Version 3.3
// Date	2018-03-25
// Perishable.cpp
// Author	Jameson Bui
//
/////////////////////////////////////////////////////////////////
#include "Perishable.h"
namespace AMA
{

Perishable::Perishable() : Product('P') {
	Date_Obj = Date();
}

std::fstream& Perishable::store(std::fstream& file, bool newLine) const
{
	if (!isEmpty()) {
		Product::store(file, false);

		file << "," << Date_Obj;

		if (newLine) {
			file << std::endl;
		}
	}
	//file.clear();
	//file.close();

	return file;
}

std::fstream& Perishable::load(std::fstream& file)
{
	Product::load(file);
	//file.ignore();
	

	Date_Obj.read(file);
	//Date_Obj.read(file);

	file << Date_Obj;
	return file;
}

std::ostream& Perishable::write(std::ostream& os, bool linear) const
{

	Product::write(os, linear);
	if (!Date_Obj.bad())
	{
		if (!linear) {
			os << std::endl << " Expiry date: ";
			os << Date_Obj;
		}
		else
		{
			os << Date_Obj;
		}
	}
	return os;
}

std::istream& Perishable::read(std::istream& is)
{
	Product::read(is);
	if (is.fail()) {
		is.ignore(2000, '\n');
		return is;
	}

	std::cout << " Expiry date (YYYY/MM/DD): ";

	Date temp;
	temp.read(is);


	if (temp.bad())
	{
		is.setstate(std::ios::failbit);
		*this = Perishable();

		switch (temp.errCode()) {
		case CIN_FAILED: {
			message("Invalid Date Entry");
			is.setstate(std::ios::failbit);
			break;
		}
		case YEAR_ERROR: {
			message("Invalid Year in Date Entry");
			is.setstate(std::ios::failbit);
			break;
		}
		case MON_ERROR: {
			message("Invalid Month in Date Entry");
			is.setstate(std::ios::failbit);
			break;
		}
		case DAY_ERROR: {
			message("Invalid Day in Date Entry");
			is.setstate(std::ios::failbit);
			break;
		}

		case NO_ERROR: {
			Date_Obj = temp;
			break;
		}
		}

	}

	Date_Obj = temp;

	return is;

}

const Date& Perishable::expiry() const
{
	return Date_Obj;
}









}