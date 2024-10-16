// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Game_Object.cpp

#include "Cart_Point.h"
#include "Game_Object.h"
#include "Model.h"
#include <iostream>
#include <fstream>

using namespace std;

/*****************************************************************/
/* CONSTRUCTORS:                                                 */
/*****************************************************************/


// Game_Object()
//-----------------------------------------	
// default constructor

Game_Object::Game_Object()
{
	display_code = ' ';
	state = 's';
	id_num = 0;
	cout << "    Game_Object default constructed." << endl;
}


// Game_Object()
//-----------------------------------------	
// restore constructor

Game_Object::Game_Object(char in_code, int in_id)
{
	// restore from file
	display_code = in_code;
	state = 's';
	id_num = in_id;
	cout << "    Game_Object constructed." << endl;
}

// Game_Object()
//-----------------------------------------	
// initialize with display_code, id_num, and location

Game_Object::Game_Object(char in_code, int in_id, Cart_Point in_loc)
{
	display_code = in_code;
	state = 's';
	id_num = in_id;
	location = in_loc;
	cout << "    Game_Object constructed." << endl;
}

// ~Game_Object()
//-----------------------------------------	
// destructor

Game_Object::~Game_Object()
{
	cout << "    Game_Object destructed." << endl;
}

/*****************************************************************/
/* PUBLIC MEMBER FUNCTIONS:                                      */
/*****************************************************************/

// Game_Object.get_location()
//-----------------------------------------	
// return the location of the object

Cart_Point Game_Object::get_location()
{
	return location;
}

// Game_Object.get_id()
//-----------------------------------------	
// return the id_num of the object

int Game_Object::get_id()
{
	return id_num;
}

// Game_Object.get_display_code()
//-----------------------------------------	
// return the display_code of the object

char Game_Object::get_display_code()
{
	return display_code;
}

// Game_Object.show_status()
//-----------------------------------------	
// print the status of the Game_Object

void Game_Object::show_status()
{
	cout << display_code << id_num
		 << " at location " << location << " ";
}

// Game_Object.drawself()
//-----------------------------------------	
// add object display_code and id_num
// to provided location in View char grid

void Game_Object::drawself(char *ptr)
{
	// Assign display code
	*ptr = display_code;

	if (id_num > 10)
		// Cannot display entire ID number
		*(ptr + 1) = '+'; // '+' means the ID is > 10
	else
	{
		// convert integer id_num to ASCII character equivalent
		char char_id = (char)(id_num + (int)'0');

		// Assign character id_num
		*(ptr + 1) = char_id;
	}
}

// Game_Object.is_alive()
//-----------------------------------------	
// default, return true

bool Game_Object::is_alive()
{
	return true;
}

// Game_Object.save()
//-----------------------------------------	
// save the state of all member variables

void Game_Object::save(ofstream &file)
{
	// write display_code and id_num, e.g. M1
	file << display_code << endl << id_num << endl;

	// write (x,y) coordinates of location
	file << location.x << endl << location.y << endl;

	// write state
	file << state << endl;
}

void Game_Object::restore(ifstream &file, Model &model)
{
	// read display_code
	file >> display_code;

	// read id_num
	file >> id_num;

	// read location
	file >> location.x;
	file >> location.y;

	// read state
	file >> state;
}
