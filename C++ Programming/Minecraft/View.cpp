// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// View.cpp

#include "View.h"
#include "Cart_Point.h"
#include "Game_Object.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

/*****************************************************************/
/* CONSTRUCTORS:                                                 */
/*****************************************************************/

// View()
//-----------------------------------------	
// default constructor

View::View()
{
	size = 11;
	scale = 2;
	origin = Cart_Point(0,0);
}

/*****************************************************************/
/* PUBLIC MEMBER FUNCTIONS:                                      */
/*****************************************************************/

// View.clear()
//-----------------------------------------	
// clear grid of all plotted objects

void View::clear()
{
	// reset grid to only dots
	for (int x = 0; x < view_maxsize; x++)
	{
		for (int y = 0; y < view_maxsize; y++)
		{
			// empty grid element
			grid[x][y][0] = '.';
			grid[x][y][1] = ' ';
		}
	}
}

// View.plot()
//-----------------------------------------	
// plot specified Game_Object to view grid

void View::plot(Game_Object *ptr)
{
	int ix;
	int iy;
	// if location is within the game grid
	if (get_subscripts(ix, iy, ptr->get_location()))
	{
		// check to see if grid location is already occupied
		if (grid[ix][iy][0] != '.')
		{
			// '*' multiple objects in same grid location
			grid[ix][iy][0] = '*';
			grid[ix][iy][1] = ' ';
		}
		else
		{
			// draw Game_Object in grid location
			ptr->drawself(grid[ix][iy]);
		}
	}
}

// View.draw()
//-----------------------------------------	
// print grid and axes

void View::draw()
{
	// draw grid using stdout
	for (int y = (size - 1); y >= 0; y--)
	{
		// print y-index number on every other row
		if ((y%(int)scale) == 0)
			cout << setw(2) << left << (y * scale);
		else
			cout << "  "; // print leading spaces

		for (int x = 0; x < size; x++)
		{
			cout << grid[x][y][0];
			cout << grid[x][y][1];
		}
		// newline
		cout << endl;
	}

	// print x-indeces
	cout << "  ";
	for (int i = 0; i < size; i++)
	{
		if ((i%(int)scale) == 0)
			cout << setw(4) << left << i * scale;
	}
	// newline
	cout << left << endl;
}

/*****************************************************************/
/* PRIVATE MEMBER FUNCTIONS:                                     */
/*****************************************************************/

// get_subscripts()
//-----------------------------------------	
// get x and y indeces of grid based on
// location of object to be plotted

bool View::get_subscripts(int &ix, int &iy, Cart_Point location)
{
	// calculate distance to location from origin
	Cart_Vector dist_to_pos;
	dist_to_pos = (location - origin);

	// scale to the current grid size
	dist_to_pos = dist_to_pos/scale;

	// extract x and y grid indeces
	ix = (int)dist_to_pos.x;
	iy = (int)dist_to_pos.y;

	// error check indeces (w/in size of current display)
	if (ix < 0 || iy < 0 || ix > size || iy > size)
	{
		cout << "An object is outside the display." << endl;
		return false;
	}
	else
		return true;
}