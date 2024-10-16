// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Cart_Point.h

#ifndef CART_POINT_H
#define CART_POINT_H

#include "Cart_Vector.h"
#include <iostream>

using namespace std;

class Cart_Point
{	
	public:
	
	// public member variables:
	double x;
	double y;
	
	// constructors:
	Cart_Point();
	Cart_Point(double, double);
};
	
// overloaded non-member operators:
ostream &operator<<(ostream &, Cart_Point &);
Cart_Point operator+(Cart_Point &, Cart_Vector &);
Cart_Vector operator-(Cart_Point &, Cart_Point &);
bool operator==(Cart_Point &p1, Cart_Point& p2);

// public non-member functions:
double cart_distance(Cart_Point, Cart_Point);

#endif