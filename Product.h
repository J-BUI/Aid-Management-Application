// Final Project - Milestone 3 - Product Class
// Version 3.3
// Date	2018-03-25
// Product.h
// Author	Jameson Bui
//
/////////////////////////////////////////////////////////////////

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include "ErrorState.h"
#include "iProduct.h"

namespace AMA {

#define max_sku_length 7
#define max_unit_length 10
#define max_name_length 75
#define TAX_RATE 0.13

class Product: public iProduct
{
	char m_type;
	char m_sku[max_sku_length + 1];
	char m_unit[max_unit_length + 1];
	char* m_name;
	int m_qty_have;
	int m_qty_need;
	double m_price;
	bool m_taxible;

	ErrorState error;

protected:
	void name(const char* n);
	const char* name() const;
	const char* sku() const;
	const char* unit() const;
	bool taxed() const;
	double price() const;
	double cost() const;
	void message(const char*);
	bool isClear() const;

public:
	// Constructor
	Product(char t = 'N');
	Product(const char* sku, const char* n, const char* unit, int qty_have = 0, bool taxible = true, double price = 0.0, int qty_need = 0);
	// Copy Constructor
	Product(const Product &rhs);
	Product& operator=(const Product &rhs);
	// Destructor
	~Product();

	bool operator==(const char*) const;
	double total_cost() const;
	void quantity(int);
	bool isEmpty() const;
	int qtyNeeded() const;
	int quantity() const;

	bool operator>(const char*) const;
	bool operator>(const iProduct&) const;
	int operator+=(int);

	std::fstream& store(std::fstream& file, bool newLine = true) const;
	std::fstream& load(std::fstream& file);
	std::ostream& write(std::ostream& os, bool linear) const;
	std::istream& read(std::istream& is);
};

std::istream &operator>>(std::istream &is, iProduct &re);
std::ostream &operator<<(std::ostream &os, const iProduct &wr);
double operator+=(double&, const iProduct&);
}


#endif