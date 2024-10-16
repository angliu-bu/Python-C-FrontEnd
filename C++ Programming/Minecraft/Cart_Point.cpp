// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Cart_Point.cpp

#include "Cart_Point.h"
#include "Cart_Vector.h"
#include <iostream>
#include <cmath>

using namespace std;

/*****************************************************************/
/* CONSTRUCTORS:                                                 */
/*****************************************************************/

// Cart_Point()
//-----------------------------------------	
// default constructor

Cart_Point::Cart_Point()
{
	x = 0.0;
	y = 0.0;
}

// Cart_Point()
//-----------------------------------------
// initialize a specific point

Cart_Point::Cart_Point(double inputx, double inputy)
{
	x = inputx;
	y = inputy;
}
	
/*****************************************************************/
/* NON-MEMBER OPERATORS:                                         */
/*****************************************************************/

// output stream operator (<<)
//-----------------------------------------
// prints (x,y) Cartesian coordinate point

ostream &operator<<(ostream &out, Cart_Point &p1)
{
	out << "(" << p1.x << ", " << p1.y << ")";
	return out;
}

// addition operator (+)
//-----------------------------------------
// adds two Cartesian points

Cart_Point operator+(Cart_Point &p1, Cart_Vector &v1)
{
	double new_x = p1.x + v1.x;
	double new_y = p1.y + v1.y;
	return Cart_Point(new_x, new_y);
}

// subtraction operator (-)
//-----------------------------------------
// subtracts two Cartesian points to generate
// a Cartesian vector
	
Cart_Vector operator-(Cart_Point &p1, Cart_Point &p2)
{
	double new_x = p1.x - p2.x;
	double new_y = p1.y - p2.y;
	return Cart_Vector(new_x, new_y);
}

// equation operator (==)
//-----------------------------------------
// compares two Cartesian points for equality

bool operator==(Cart_Point &p1, Cart_Point& p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
		return true;
	else
		return false;
}

/*****************************************************************/
/* NON-MEMBER FUNCTIONS:                                         */
/*****************************************************************/

// cart_distance()
//-----------------------------------------
// returns numeric distance between two Cartesian points

double cart_distance(Cart_Point p1, Cart_Point p2)
{
	// distance formula
	return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}