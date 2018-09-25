// Final Project - Milestone 5 - Perishable Class
// Version 3.3
// Date	2018-03-25
// Perishable.h
// Author	Jameson Bui
//
/////////////////////////////////////////////////////////////////
#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H

#include<iostream>
#include<cstring>
#include<fstream>

#include "Date.h"
#include "Product.h"

namespace AMA {

class Perishable: public Product
{
	Date Date_Obj;

public:
	Perishable();

	const Date& expiry() const;
	// function override
	virtual std::fstream& store(std::fstream& file, bool newLine=true) const;
	virtual std::fstream& load(std::fstream& file);
	virtual std::ostream& write(std::ostream& os, bool linear) const;
	virtual std::istream& read(std::istream& is);
};


}

#endif