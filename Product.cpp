// Final Project - Milestone 3 - Product Class
// Version 3.3
// Date	2018-03-25
// Product.cpp
// Author	Jameson Bui
//
/////////////////////////////////////////////////////////////////
#include<iostream>
#include<cstring>
#include<fstream>

#include "Product.h"

using namespace std;
namespace AMA {


// Constructors
Product::Product(char t)
{
	// Setting object to safe empty state. Default for type is 'N' defined in constructor prototype
	m_type = t;
	m_sku[0] = '\0';
	m_unit[0] = '\0';
	m_name = nullptr;
	m_qty_have = 0;
	m_qty_need = 0;
	m_price = 0.0;
	m_taxible = false;
}

Product::Product(const char* sku, const char* n, const char* unit, int qty_have, bool taxible, double price, int qty_need)
{
	// use name function to set name.
	name(n);
	strncpy(m_sku, sku, max_sku_length);
	m_sku[max_sku_length] = '\0';
	strncpy(m_unit, unit, max_unit_length);
	m_unit[max_unit_length] = '\0';
	m_qty_have = qty_have;
	m_qty_need = qty_need;
	m_price = price;
	m_taxible = taxible;
}

// Copies constructor
Product::Product(const Product &rhs)
{
	// Using our assignment operator to copy
	*this = rhs;
}

Product& Product::operator=(const Product & rhs)
{
	if ( this != &rhs) {
		//call name function to assign name.
		name(rhs.m_name);
		strncpy(m_sku, rhs.m_sku, max_sku_length);
		m_sku[max_sku_length] = '\0';
		strncpy(m_unit, rhs.m_unit, max_unit_length);
		m_unit[max_unit_length] = '\0';
		m_qty_have = rhs.m_qty_have;
		m_taxible = rhs.m_taxible;
		m_price = rhs.m_price;
		m_qty_need = rhs.m_qty_need;
	}
	return *this;
}

// Destructor, clear allocated memory!
Product::~Product()
{
	if (m_name != nullptr)
	{
		delete [] m_name;
	}
}
// Protected Functions
void Product::name(const char* n)
{
	// Dynamically allocate memory for name
	if (n != nullptr) {
		m_name = new (nothrow) char [strlen(n) + 1];
		strncpy(m_name, n, strlen(n));
		m_name[strlen(n)] = '\0';
	}
	// if n does hold nullptr address, removes the name of the product if any from memory
	else { m_name = nullptr; }
}

const char* Product::name() const
{
	return m_name;
}

const char* Product::sku() const
{
	return m_sku;
}

const char* Product::unit() const
{
	return m_unit;
}

bool Product::taxed() const
{
	return m_taxible;
}

double Product::price() const
{
	return m_price;
}

// This function returns the calculated price if the item is taxed.
double Product::cost() const
{
	double i_cost;
	i_cost = m_price;
	if (taxed())
	{
		i_cost += (m_price * TAX_RATE);
	}
	return i_cost;
}

void Product::message(const char* e)
{	// access error object function to store error message.
	error.message(e);
}

bool Product::isClear() const
{
	return error.isClear();
}

// we are using fstream to store the object informtion into a text file with the data seperated by comma.
std::fstream& Product::store(std::fstream & file, bool newLine) const
{
	// If object not empty, we shall proceed with store
	if (!isEmpty()) {
		file << m_type << "," << m_sku << "," << m_name << "," << m_unit << "," <<  m_taxible
		     << "," << m_price
		     << "," << m_qty_have << "," << m_qty_need;
		// if newLine is true (default is yes) then we shall insert a newline at the end of store.
		if (newLine) {
			file << std::endl;
		}
	}

	return file;
}

std::fstream& Product::load(std::fstream & file)
{
	// Creating temp values to store into a temp object to make sure they are OK before
	// assigning into current object.
	char t_sku[max_sku_length + 1];
	char t_name[max_name_length + 1];
	char t_unit[max_unit_length + 1];
	int t_qty;
	int t_qty_need;
	bool t_tax;
	double t_price;

	file.getline(t_sku, max_sku_length + 1, ',');
	file.getline(t_name, max_name_length + 1, ',');
	file.getline(t_unit, max_unit_length + 1, ',');
	file >> t_tax;
	file.ignore();
	file >> t_price;
	file.ignore();
	file >> t_qty;
	file.ignore();
	file >> t_qty_need;
	file.ignore();

	Product temp(t_sku, t_name, t_unit, t_qty, t_tax, t_price, t_qty_need);

	if (!temp.isEmpty()) {
		*this = temp;
	}

	return file;
}


std::ostream& Product::write(std::ostream & os, bool linear) const
{
	if (isEmpty())
	{	// If the object is empty (or if there is some kind of error, an object will
	    // be set to empty) we display error message.
		os << error.message();
	}
	else
	{
		if (linear)
		{	// set the width for formatting of displaing information in a linear fashion.
			os.width (max_sku_length);
			os << std::left << sku() << "|";

			os.width (20);
			os << name() << "|";

			os.setf (ios::fixed);
			os.setf (ios::right);
			os.width(7);
			os.precision(2);
			os << cost() << "|";

			os.width(4);
			os << quantity() << "|";

			os.width(10);
			os << std::left << unit() << "|";

			os.width(4);
			os << std::right << qtyNeeded() << "|";
		}
		else
		{
			os << " Sku: " << sku() << endl;
			os << " Name (no spaces): " << name() << endl;
			os << " Price: " << price() << endl;
			if (taxed())
			{ os << " Price after tax: " << cost() << endl; }
			else
			{ os << " Price after tax:  N/A" << endl; }
			os << " Quantity on Hand: " << quantity() << " " << unit() << endl;
			os << " Quantity needed: " << qtyNeeded();
		}
	}
	return os;
}


// read function used to get input from user
std::istream& Product::read(std::istream & is)
{
	char t_sku[max_sku_length + 1];
	char t_name[max_name_length + 1];
	char t_unit[max_unit_length + 1];
	char t_tax;
	double t_price;
	int t_qty;
	int t_qty_need;

	cout << " Sku: ";
	// getting input and storing into temp
	is.getline(t_sku, max_sku_length + 1);
	// if fail we exit out of read and return is right away.
	if (is.fail()) {
		is.ignore(2000, '\n');
		return is;
	}

	cout << " Name (no spaces): ";
	is.getline(t_name, max_name_length + 1);
	if (is.fail()) {
		is.ignore(2000, '\n');
		return is;
	}

	cout << " Unit: ";
	is.getline(t_unit, max_unit_length + 1);
	if (is.fail()) {
		is.ignore(2000, '\n');
		return is;
	}

	cout << " Taxed? (y/n): ";
	is >> t_tax;
	if (!(t_tax == 'Y' || t_tax == 'y' || t_tax == 'N' || t_tax == 'n' || is.fail()))
	{
		is.setstate(ios::failbit);
		error.message("Only (Y)es or (N)o are acceptable");
		return is;
	}
	else
	{
		if (t_tax == 'y' || t_tax == 'Y')
		{
			t_tax = true;
		}
		else if (t_tax == 'n' || t_tax == 'N')
		{
			t_tax = false;
		}
	}
	is.ignore(2000, '\n');

	cout << " Price: ";
	is >> t_price;
	if (is.fail()) {
		error.message("Invalid Price Entry");
		is.ignore(2000, '\n');
		return is;
	}
	is.ignore(2000, '\n');

	cout << " Quantity on hand: ";
	is >> t_qty;
	if (is.fail()) {
		error.message("Invalid Quantity Entry");
		is.ignore(2000, '\n');
		return is;
	}
	is.ignore(2000, '\n');

	cout << " Quantity needed: ";
	is >> t_qty_need;
	if (is.fail()) {
		error.message("Invalid Quantity Needed Entry");
		is.ignore(2000, '\n');
		return is;
	}
	is.ignore(2000, '\n');

	// after all is added and no errors has occured, we can put into temporary object
	// and copy to current
	Product temp(t_sku, t_name, t_unit, t_qty, t_tax, t_price, t_qty_need);

	*this = temp;
	return is;
}

bool Product::operator==(const char* s) const
{
	int flag = 0;
	if (strcmp(m_sku, s) == 0)
	{
		flag = 1;
	}
	return flag;
}

// total_cost function calculates the price of item, with tax by quantity
double Product::total_cost() const
{
	double total;
	total = (m_qty_have * m_price);

	if (taxed())
	{
		total += (total * TAX_RATE);
	}
	return total;
}

void Product::quantity(int qty)
{
	m_qty_have = qty;
}

bool Product::isEmpty() const
{
	int flag = 0;
	if ((m_sku[0] == '\0') && (m_unit[0] == '\0') && (m_name == nullptr) && (m_qty_have == 0) && (m_qty_need == 0) && (m_price == 0))
	{
		flag = 1;
	}
	return flag;
}

int Product::qtyNeeded() const
{
	return m_qty_need;
}

int Product::quantity() const
{
	return m_qty_have;
}

bool Product::operator>(const char* sku) const
{
	return (strcmp(m_sku, sku) > 0);
}

bool Product::operator>(const iProduct & pr) const
{
	return (strcmp(m_name, pr.name()) > 0);
}

int Product::operator+=(int add)
{
	if (add > 0)
	{
		m_qty_have += add;
	}
	return m_qty_have;
}

// overloaded function operator to read
std::istream &operator>>(std::istream & is, iProduct & re)
{
	re.read(is);
	return is;
}

// overloaded function operator to write
std::ostream &operator<<(std::ostream & os, const iProduct & wr)
{
	wr.write(os, true);
	return os;
}

double operator+=(double & add, const iProduct & p)
{
	return (add + p.total_cost() );
}

}