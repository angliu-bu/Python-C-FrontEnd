// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Cart_Vector.h

#ifndef CART_VECTOR_H
#define CART_VECTOR_H

#include <iostream>

using namespace std;

class Cart_Vector
{
	public:
	
	// public member variables:
	double x;
	double y;
	
	// constructors:
	Cart_Vector();
	Cart_Vector(double, double);
};

// overloaded non-member operators:
ostream &operator<<(ostream &, Cart_Vector &);
Cart_Vector operator*(Cart_Vector &, double &);
Cart_Vector operator/(Cart_Vector &, double &);

#endif