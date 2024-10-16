// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Person.cpp

#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Person.h"
#include "Model.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <cctype>

using namespace std;

/*****************************************************************/
/* CONSTRUCTORS:                                                 */
/*****************************************************************/

// Person()
//-----------------------------------------	
// default constructor

Person::Person()
	:Game_Object()
{
	health = 5;
	speed = 5;
	cout << "    Person default constructed." << endl;
}

// Person()
//-----------------------------------------	
// restore constructor

Person::Person(char in_code, int in_id)
	:Game_Object(in_code, in_id)
{
	// restore from file
	health = 5;
	speed = 5;
	cout << "    Person constructed." << endl;
}

// Person()
//-----------------------------------------	
// initialize with display_code, id_num, and location

Person::Person(char in_code, int in_id, Cart_Point in_loc)
	:Game_Object(in_code, in_id, in_loc)
{
	health = 5;
	speed = 5;
	cout << "    Person constructed." << endl;
}

// ~Person()
//-----------------------------------------	
// destructor

Person::~Person()
{
	cout << "    Person destructed." << endl;
}

/*****************************************************************/
/* PUBLIC MEMBER FUNCTIONS:                                      */
/*****************************************************************/

// Person.start_moving()
//-----------------------------------------	
// setup destination and begin moving Person

void Person::start_moving(Cart_Point dest)
{
	// check for life
	if (is_alive())
	{
		// setup destination
		setup_destination(dest);
			
		// set state to "moving"
		state = 'm';
		cout << "Moving " << get_id() << " to " << destination << endl;
		cout << display_code << get_id() << ": On my way." << endl;
	}
	else
	{
		cout << display_code << get_id() << ": I am dead. The dead cannot move!" << endl;
	}
}

// Person.stop()
//-----------------------------------------	
// stop moving Person

void Person::stop()
{
	// check for life
	if (is_alive())
	{
		// stop person
		state = 's';
		cout << "Stopping." << endl;
		delta = Cart_Vector(0,0);
		cout << display_code << get_id() << ": All right." << endl;
	}
	else
	{
		state = 's';
		delta = Cart_Vector(0,0);
		cout << display_code << get_id() << ": I am dead. The dead cannot be stopped!" << endl;
	}
}

// Person.show_status()
//-----------------------------------------	
// print current status of Person

void Person::show_status()
{
	Game_Object::show_status();

	if (state == 'm' || state == 'o' || state == 'r' || state == 'i')
	{
		cout << "moving at speed of " << speed << " to " << destination
			 << " at each step of " << delta;
	}

	if (state != 'x')	 
		cout << endl << "    Health " << health << "." << endl;
	else
		cout << " is dead." << endl;
}

// Person.is_alive()
//-----------------------------------------	
// return true if Person not dead (health > 0)

bool Person::is_alive()
{
	if (state == 'x')
		return false;
	else
		return true;
}

// Person.take_hit()
//-----------------------------------------	
// decrement health of Person until death

void Person::take_hit(int attack_strength, Person *attacker_ptr)
{
	health -= attack_strength;

	if (health < 3)
	{
		display_code = tolower(display_code);
	}

	if (health <= 0)
	{
		state = 'x';
		cout << display_code << get_id() << ": Ahhhh, I am dying!" << endl;
	}
	else
	{
		cout << display_code << get_id() << ": Ouch!" << endl;
	}
}

// Person.save()
//-----------------------------------------	
// save the state of all member variables

int Person::get_health()
{
	return health;
}

// Person.save()
//-----------------------------------------	
// save the state of all member variables

void Person::save(ofstream &file)
{
	Game_Object::save(file);

	// write health, speed
	file << health << endl << speed << endl;

	// write destination (x,y) and delta <x,y> components
	file << destination.x << endl << destination.y << endl;
	file << delta.x << endl << delta.y << endl;
}

// .restore()
//-----------------------------------------	
// restore the state of all member variables

void Person::restore(ifstream &file, Model &model)
{
	Game_Object::restore(file, model);

	// restore member variables

	// health and speed
	file >> health;
	file >> speed;

	// destination and delta
	file >> destination.x;
	file >> destination.y;
	file >> delta.x;
	file >> delta.y;
}

// Person_start_mining()
//-----------------------------------------	
// print message, Person cannot work a mine

void Person::start_mining(Gold_Mine *g, Town_Hall *t)
{
	cout << "Sorry, I can't work a mine." << endl;
}

// Person.start_attack()
//-----------------------------------------	
// print message, Person cannot attack

void Person::start_attack(Person *target)
{
	cout << "Sorry, I can't attack." << endl;
}

// Person.start_inspecting()
//-----------------------------------------	
// print message, Person cannot inspect

void Person::start_inspecting(Model &model)
{
	cout << "Sorry, I can't inspect." << endl;
}

/*****************************************************************/
/* PROTECTED MEMBER FUNCTIONS:                                   */
/*****************************************************************/

// Person.update_location()
//-----------------------------------------	
// update current location while moving
// after each unit of time passes

bool Person::update_location()
{
	// if within one step of destination
	if ((fabs(destination.x - location.x) <= fabs(delta.x)
		&& fabs(destination.y - location.y) <= fabs(delta.y))
		|| location == destination)
	{
		cout << display_code << get_id() << ": I'm there!" << endl;
		location = destination; // update location
		delta = Cart_Vector(0,0);
		return true;
	}
	
	// has not reached destination
	else
	{
		cout << display_code << get_id() << ": step..." << endl;
		location = location + delta; // update location
		return false;
	}
}

// Person.setup_destination()
//-----------------------------------------	
// store specified destination when commanded
// to start moving

void Person::setup_destination(Cart_Point dest)
{
	// store destination
	destination = dest;
	
	// calculate delta
	double dist = speed / cart_distance(dest, location);
	Cart_Vector separation;
	separation = dest - location;
	delta = separation * dist;
}