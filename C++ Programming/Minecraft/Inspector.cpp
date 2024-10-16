// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Inspector.cpp

#include "Model.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Person.h"
#include "Inspector.h"
#include <iostream>
#include <fstream>
#include <list>

/*****************************************************************/
/* CONSTRUCTORS:                                                 */
/*****************************************************************/

// Inspector()
//-----------------------------------------	
// default constructor

Inspector::Inspector()
	:Person('I',0) // display code 'I'
{
	outbound = false;
	inspection_complete = true;
	starting_location = Cart_Point(0,0); // default location
	current_mine = NULL;

	cout << "    Inspector default constructed." << endl;
}

// Inspector()
//-----------------------------------------	
// restore constructor

Inspector::Inspector(int in_id)
	:Person('I',in_id)
{
	// restore from file
	outbound = false;
	inspection_complete = true;
	starting_location = Cart_Point(0,0); // default location
	current_mine = NULL;

	cout << "    Inspector constructed." << endl;
}

// Inspector()
//-----------------------------------------	
// initialize with id_num and location

Inspector::Inspector(int in_id, Cart_Point in_loc)
	:Person('I', in_id, in_loc)
{
	outbound = false;
	inspection_complete = true;
	starting_location = in_loc;
	current_mine = 0;

	cout << "    Inspector constructed." << endl;
}

// ~Inspector()
//-----------------------------------------	
// destructor

Inspector::~Inspector()
{
	cout << "    Inspector destructed." << endl;
}

/*****************************************************************/
/* PUBLIC MEMBER FUNCTIONS:                                      */
/*****************************************************************/

// Inspector.update()
//-----------------------------------------	
// update member variables depending on state

bool Inspector::update()
{
	switch (state)
	{
		case 's':	// stopped, do nothing
			break;

		case 'm':	// moving to destination

			// Inspector has arrived at location
			if (update_location())
			{
				state = 's'; // stop
				return true;
			}
			// Inspector has not yet arrived
			break;

		case 'o':	// outbound inspecting

			// Inspector has arrived at next mine
			if (update_location())
			{
				state = 'l'; // continue inspection
				return true;
			}
			// Inspector has not yet arrived
			break;

		case 'r':	// return inspecting

			// Inspector has arrived at next mine
			if (update_location())
			{
				if (inspection_complete)
				{
					state = 's';
					cout << "Inspection trip completed." << endl;
				}
				else
					state = 'l'; // continue inspection
				return true;
			}
			// Inspector has not yet arrived
			break;

		case 'l':	// inspecting ("looking at") a Gold_Mine
		{
			// outbound inspecting:
			if (outbound)
			{
				// get current amount of gold from mine
				double inspected_amount = current_mine->get_gold_amount();
				cout << "This mine contains " << inspected_amount << " of gold." << endl;

				// remove current mine from list of mines to inspect
				mines_to_inspect.remove(current_mine);

				if (!mines_to_inspect.empty())
				{
					// add current mine and its amount to list of inspected mines
					mines_inspected.push_front(current_mine);
					outbound_amounts.push_front(inspected_amount);

					// find next mine
					current_mine = get_closest_mine(mines_to_inspect);

					// set up destination to next mine
					state = 'o';
					setup_destination(current_mine->get_location());
				}
				else
				{
					// begin return inspection
					cout << display_code << get_id() << ": Starting back." << endl;
					outbound = false;
					state = 'r';
					current_mine = mines_inspected.front();
					setup_destination(current_mine->get_location());
				}
			}

			// return inspecting (!outbound):
			else
			{
				// get amount of gold in current mine
				double new_inspected_amount = current_mine->get_gold_amount();

				// compare the new amount to the original inspected amount
				double amount_removed = outbound_amounts.front() - new_inspected_amount;
				cout << "Amount of gold removed from this mine is " << amount_removed << "." << endl;

				// remove current mine and amount from list of mines to inspect on return trip
				mines_inspected.pop_front();
				outbound_amounts.pop_front();

				if (mines_inspected.empty()) // all mines inspected
				{
					// return to starting location
					state = 'r';
					inspection_complete = true;
					setup_destination(starting_location);
				}
				else
				{	
					// get next mine
					current_mine = mines_inspected.front();

					// continue return inspection
					state = 'r';
					setup_destination(current_mine->get_location());
				}
			}
			break;
		}
	}
	return false;
}

// Inspector.show_status()
//-----------------------------------------	
// print the current status of the Inspector

void Inspector::show_status()
{
	cout << "Inspector status: ";
	Person::show_status();

	switch (state)
	{
		case 's': 	// stopped
			cout << "    Stopped." << endl;
			break;

		case 'm':	// moving
			cout << "    Moving to destination." << endl;
			break;

		case 'o':	// outbound inspecting
			cout << "    Outbound inspection." << endl;
			break;

		case 'r':	// return inspecting
			cout << "    Returning inspection." << endl;
			break;

		case 'l': 	// looking at a Gold_Mine
			cout << "    Inspecting a mine." << endl;
			break;
	}
}

// Inspector.start_inspecting()
//-----------------------------------------	
// setup destination nearest Gold_Mine
// and begin inspecting

void Inspector::start_inspecting(Model &model)
{
	// store current location
	starting_location = this->get_location();

	// get list of current Gold_Mines
	mines_to_inspect = model.get_Gold_Mine_list();

	// find the closest Gold_Mine
	current_mine = get_closest_mine(mines_to_inspect);

	// setup destination to closest Gold_Mine
	setup_destination(current_mine->get_location());
	state = 'o';
	outbound = true;
	inspection_complete = false;
	cout << display_code << get_id() << ": Starting inspection trip." << endl;
}

// Inspector.take_hit()
//-----------------------------------------	
// run away from attacker

void Inspector::take_hit(int attack_strength, Person *attacker_ptr)
{
	Person::take_hit(attack_strength, attacker_ptr);

	if (get_health() > 0)
	{
		// calculate distance between person and attacker
		Cart_Point attacker_location = attacker_ptr->get_location();
		Cart_Vector attacker_direction = location - attacker_location;

		// scale by 1.5 (in opposite direction)
		double scale = 1.5;
		attacker_direction = attacker_direction * scale;

		// calculate location to flee to
		Cart_Point flee_location = location + attacker_direction;

		cout << display_code << get_id() << ": I dont want to fight!" << endl;

		// move away from attacker
		start_moving(flee_location);
	}
}

// Inspector.save()
//-----------------------------------------	
// save the state of all member variables

void Inspector::save(ofstream &file)
{
	Person::save(file);

	// write boolean variables
	file << outbound << endl << inspection_complete << endl;

	// write starting_location (x,y)
	file << starting_location.x << endl << starting_location.y << endl;

	// write current_mine pointer
	if (current_mine == 0)
		file << -1 << endl;
	else
		file << current_mine->get_id() << endl;

	// write list contents:

	// mines_to_inspect
	file << mines_to_inspect.size() << endl; // write size of list

	list<Gold_Mine*>::iterator it = mines_to_inspect.begin();
	for (int i = 0; i < mines_to_inspect.size(); i++)
	{
		if((*it) == 0)
			file << -1 << endl;
		else
			file << (*it)->get_id() << endl;
		it++;
	}

	// mines_inspected
	file << mines_inspected.size() << endl;

	it = mines_inspected.begin();
	for (int i = 0; i < mines_inspected.size(); i++)
	{
		if((*it) == 0)
			file << -1 << endl;
		else
			file << (*it)->get_id() << endl;
		it++;
	}

	// outbound_amounts
	file << outbound_amounts.size() << endl;

	list<double>::iterator amount_it = outbound_amounts.begin();
	for (int i = 0; i < outbound_amounts.size(); i++)
	{
		file << (*amount_it) << endl;
		amount_it++;
	}
}

// .restore()
//-----------------------------------------	
// restore the state of all member variables

void Inspector::restore(ifstream &file, Model &model)
{
	Person::restore(file, model);

	// read boolean variables
	file >> outbound;
	file >> inspection_complete;

	// read starting location
	file >> starting_location.x;
	file >> starting_location.y;

	// read current mine pointer
	int current_mine_id;
	file >> current_mine_id;

	if (current_mine_id == -1)
		current_mine = 0;
	else
		current_mine = model.get_Gold_Mine_ptr(current_mine_id);

	// restore lists:

	// clear lists
	mines_to_inspect.clear();
	mines_inspected.clear();
	outbound_amounts.clear();

	// mines_to_inspect
	int list_size;
	file >> list_size; // read list size

	for (int i = 0; i < list_size; i++)
	{
		// read id from file
		int inspect_id;
		file >> inspect_id;

		// push pointer to object with specified id to list
		if (inspect_id == -1)
			mines_to_inspect.push_back(0);
		else
			mines_to_inspect.push_back(model.get_Gold_Mine_ptr(inspect_id));
	}

	// mines_inspected
	file >> list_size;

	for (int i = 0; i < list_size; i++)
	{
		int inspect_id;
		file >> inspect_id;

		if (inspect_id == -1)
			mines_inspected.push_back(0);
		else
			mines_inspected.push_back(model.get_Gold_Mine_ptr(inspect_id));
	}

	// outbound_amounts
	file >> list_size;

	for (int i = 0; i < list_size; i++)
	{
		double in_amount;
		file >> in_amount;

		outbound_amounts.push_back(in_amount);
	}
}

/*****************************************************************/
/* PRIVATE MEMBER FUNCTIONS:                                     */
/*****************************************************************/

// get_closest_mine()
//-----------------------------------------	
// finds the closest Gold_Mine to the
// Inspector's location

Gold_Mine * Inspector::get_closest_mine(list<Gold_Mine*> mines_to_check)
{
	// initialize iterator
	list<Gold_Mine*>::iterator mine_it;
	mine_it = mines_to_check.begin();

	// assume first mine is the closest
	Gold_Mine *closest_mine = *mine_it;
	mine_it++;

	// calculate distance to first mine from Inspector's location
	double dist_to_closest_mine = cart_distance(location, closest_mine->get_location());

	for (int i = 1; i < mines_to_check.size(); i++)
	{
		Gold_Mine *this_mine = *mine_it;
		double distance_to_check = cart_distance(location, this_mine->get_location());


		// if mine in list is closer than first mine
		if (distance_to_check < dist_to_closest_mine)
		{
			// update closest mine
			dist_to_closest_mine = distance_to_check;
			closest_mine = this_mine;
		}
		mine_it++;
	}

	return closest_mine;
}