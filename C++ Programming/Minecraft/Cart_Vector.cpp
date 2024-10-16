// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Cart_Vector.cpp

#include "Cart_Vector.h"
#include <iostream>

using namespace std;

/*****************************************************************/
/* CONSTRUCTORS:                                                 */
/*****************************************************************/

// Cart_Vector()
//-----------------------------------------	
// default constructor

Cart_Vector::Cart_Vector()
{
	x = 0.0;
	y = 0.0;
}

// Cart_Vector()
//-----------------------------------------	
// initialize to specific values

Cart_Vector::Cart_Vector(double inputx, double inputy)
{
	x = inputx;
	y = inputy;
}
	
/*****************************************************************/
/* NON-MEMBER OPERATORS:                                         */
/*****************************************************************/
	
// output stream operator (<<)
//-----------------------------------------
// prints Cartesian vector <x, y>

ostream &operator<<(ostream &out, Cart_Vector &v1)
{
	out << "<" << v1.x << ", " << v1.y << ">";
	return out;
}

// multiplication operator (*)
//-----------------------------------------
// multiplies a Cartesian vector by a scalar

Cart_Vector operator*(Cart_Vector &v1, double &d)
{
	double new_x = v1.x * d;
	double new_y = v1.y * d;
	return Cart_Vector(new_x, new_y);
}
	
// division operator (/)
//-----------------------------------------
// divides a Cartesian vector by a scalar

Cart_Vector operator/(Cart_Vector &v1, double &d)
{
	double new_x = v1.x / d;
	double new_y = v1.y / d;
	return Cart_Vector(new_x, new_y);
}
	