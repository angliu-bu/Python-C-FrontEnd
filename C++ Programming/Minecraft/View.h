// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// View.h

#ifndef VIEW_H
#define VIEW_H

#include "Cart_Point.h"
#include "Game_Object.h"

using namespace std;

// defines maximum size of the view grid
const int view_maxsize = 20;

class View
{
	public:

	// constructors:
	View();

	// public member functions:
	void clear();
	void plot(Game_Object *);
	void draw();

	private:

	// private member variables:
	int size;
	double scale;
	Cart_Point origin;
	char grid[view_maxsize][view_maxsize][2]; // 2 char array

	// private member functions:
	bool get_subscripts(int &, int &, Cart_Point);
};

#endif