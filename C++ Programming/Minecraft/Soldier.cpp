// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Soldier.cpp

#include "Cart_Point.h"
#include "Person.h"
#include "Soldier.h"
#include "Model.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

/*****************************************************************/
/* CONSTRUCTORS:                                                 */
/*****************************************************************/	

// Soldier()
//-----------------------------------------	
// default constructor, initialize only with display_code

Soldier::Soldier()
	:Person('S', 0)
{
	attack_strength = 2;
	range = 2.0;
	target = NULL;
	cout << "   Soldier default constructed." << endl;
}

// Soldier()
//-----------------------------------------	
// restore constructor

Soldier::Soldier(int in_id)
	:Person('S', in_id)
{
	// restore from file
	attack_strength = 2;
	range = 2.0;
	target = NULL;
	cout << "    Soldier constructed." << endl;
}

// Soldier()
//-----------------------------------------	
// initialize with display_code, id_num, and location

Soldier::Soldier(int in_id, Cart_Point in_loc)
	:Person('S', in_id, in_loc)
{
	attack_strength = 2;
	range = 2.0;
	target = 0;
	cout << "    Soldier constructed." << endl;
}

// ~Soldier()
//-----------------------------------------	
// destructor

Soldier::~Soldier()
{
	cout << "    Soldier destructed." << endl;
}

/*****************************************************************/
/* PUBLIC MEMBER FUNCTIONS:                                      */
/*****************************************************************/	

// Soldier.start_attack()
//-----------------------------------------	
// begin attacking specified target if
// within range (2 units)

void Soldier::start_attack(Person *in_target)
{
	// check for life
	if (is_alive())
	{	
		if (in_target->get_id() == this->get_id()) // soldier cannot attack itself
		{
			cout << display_code << get_id() << ": I cannot attack myself!" << endl;
			state = 's'; // stopped
		}
		else
		{
			// calculate distance to target
			double dist = cart_distance(in_target->get_location(), location);

			if (dist <= range)
			{
				target = in_target;
				cout << display_code << get_id() << ": Attacking." << endl;
				state = 'a'; // attack
			}
			else
				cout << display_code << get_id() << ": Target is out of range." << endl;
		}
	}
	else
	{
		cout << display_code << get_id() << ": I am dead. The dead cannot attack." << endl;
	}
}

// Soldier.update()
//-----------------------------------------	
// update member variables after each
// passing unit of time

bool Soldier::update()
{
	switch (state)
	{
		case 's': // stopped
			break;

		case 'm': // moving 

			// Soldier has arrived at assigned location
			if (update_location())
			{
				state = 's'; // stop
				return true;
			}
			break; // soldier has not yet arrived

		case 'a': // attacking
		{
			// check distance to target
			Cart_Point target_location = target->get_location();
			double dist_to_target = cart_distance(location, target_location);

			if (dist_to_target <= range) // target is still in range
			{
				if (target->is_alive())
				{
					cout << display_code << get_id() << ": Take that!" << endl;
					target->take_hit(attack_strength, this); // "this" soldier
 					return false;
				}
				else
				{
					cout << display_code << get_id() << ": I win!" << endl;
					state = 's';
					return true;
				}
			}
			else // target is no longer in range
			{
				cout << display_code << get_id() << ": Target is out of range." << endl;
				state = 's';
				return true;
			}
			break;
		}
		case 'x': // dead
			break;
	}
	return false;
}

// Soldier.show_status()
//-----------------------------------------	
// print current status of Soldier object

void Soldier::show_status()
{
	cout << "Soldier status: ";
	Person::show_status();
	
	switch (state)
	{
		case 's': // stopped
			cout << "    Stopped." << endl;
			break;
				
		case 'm': // moving to a destination
			cout << "    Moving at speed." << endl;
			break;
				
		case 'a':
			cout << "    Attacking." << endl;
			break;
	}
}

// Soldier.take_hit()
//-----------------------------------------	
// attack the Person that is attacking

void Soldier::take_hit(int attack_strength, Person *attacker_ptr)
{
	Person::take_hit(attack_strength, attacker_ptr);

	// begin attacking attacker
	start_attack(attacker_ptr);
}

// Soldier.save()
//-----------------------------------------	
// save the state of all member variables

void Soldier::save(ofstream &file)
{
	Person::save(file);

	// write attack_strength, range
	file << attack_strength << endl << range << endl;

	// write target pointer
	if (target == 0)
		file << -1 << endl;
	else
		file << target->get_id() << endl;
}

// .restore()
//-----------------------------------------	
// restore the state of all member variables

void Soldier::restore(ifstream &file, Model &model)
{
	Person::restore(file, model);

	// restore member variables
	file >> attack_strength;
	file >> range;

	// restore target pointer
	int target_id;
	file >> target_id;

	if (target_id == -1)
		target = 0;
	else
		target = model.get_Person_ptr(target_id);
}