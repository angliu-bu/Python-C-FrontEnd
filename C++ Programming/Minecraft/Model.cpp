// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Model.cpp

#include "Model.h"
#include "View.h"
#include "Game_Object.h"
#include "Person.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include "Miner.h"
#include "Soldier.h"
#include "Inspector.h"
#include "Cart_Point.h"
#include "Game_Command.h"
#include "Input_Handling.h"
#include <list>

using namespace std;

/*****************************************************************/
/* CONSTRUCTORS:                                                 */
/*****************************************************************/

// Model()
//-----------------------------------------	
// default constructor

Model::Model()
{
	// initialize game time
	current_time = 0;

	// initialize startup objects
	person_ptrs.push_back(new Miner(1,Cart_Point(5,1)));
	person_ptrs.push_back(new Miner(2,Cart_Point(10,1)));
	person_ptrs.push_back(new Soldier(3,Cart_Point(5,15)));
	person_ptrs.push_back(new Soldier(4,Cart_Point(10,15)));
	person_ptrs.push_back(new Inspector(5,Cart_Point(5,5)));
	mine_ptrs.push_back(new Gold_Mine(1,Cart_Point(1,20)));
	mine_ptrs.push_back(new Gold_Mine(2,Cart_Point(10,20)));
	hall_ptrs.push_back(new Town_Hall(1,Cart_Point(0,0)));

	// add Persons to object_ptrs
	for (person_it = person_ptrs.begin(); person_it != person_ptrs.end(); person_it++)
	{
		object_ptrs.push_back(dynamic_cast<Game_Object*>(*person_it));
	}

	// add Gold_Mines to object_ptrs
	for (mine_it = mine_ptrs.begin(); mine_it != mine_ptrs.end(); mine_it++)
	{
		object_ptrs.push_back(dynamic_cast<Game_Object*>(*mine_it));
	}

	// add Town_Halls to object_ptrs
	object_ptrs.push_back(dynamic_cast<Game_Object*>(hall_ptrs.front()));

	// copy object_ptrs to active_ptrs
	active_ptrs = object_ptrs;

	cout << "    Model default constructed." << endl;
}

// ~Model()
//-----------------------------------------	
// destructor

Model::~Model()
{
	// delete all objects
	for (object_it = object_ptrs.begin(); object_it != object_ptrs.end(); object_it++)
	{
		delete *object_it;
	}
	cout << "    Model destructed." << endl;
}

// Model(&)
//-----------------------------------------	
// copy constructor (NO COPYING PERMITTED)

Model::Model(Model &model){}

/*****************************************************************/
/* PUBLIC MEMBER FUNCTIONS:                                      */
/*****************************************************************/

// Model.update()
//-----------------------------------------	
// update all objects in the Model

bool Model::update()
{
	// increment game time
	current_time++;

	// update each object
	int events = 0;

	for (active_it = active_ptrs.begin(); active_it != active_ptrs.end(); active_it++)
	{
		bool query_event; 
		query_event = (*active_it)->update(); // check for event

		if (query_event) // at least one event has occured
			events++;
	}

	// delete all "dead" objects
	for (active_it = active_ptrs.begin(); active_it != active_ptrs.end(); active_it++)
	{
		if (!(*active_it)->is_alive()) // object is dead
		{
			active_ptrs.erase(active_it); // delete object
		}
	}

	// at least one event occured
	if (events > 0)
		return true;
	else
		return false;
}

// Model.display()
//-----------------------------------------	
// populate the View with all objects
// and print View

void Model::display(View &view)
{
	// output the current game time:
	printCurrentTime(current_time);

	// clear grid
	view.clear();

	// plot active objects to grid
	for (active_it = active_ptrs.begin(); active_it != active_ptrs.end(); active_it++)
	{
		view.plot(*active_it);
	}

	// print grid
	view.draw(); 
}

// Model.show_status()
//-----------------------------------------	
// print the status of all objects

void Model::show_status()
{
	// display all objects status
	for (object_it = object_ptrs.begin(); object_it != object_ptrs.end(); object_it++)
	{
		(*object_it)->show_status();
	}

}

// Model.handle_new_command()
//-----------------------------------------	
// create a new game object of TYPE and ID
// at location (x,y)

void Model::handle_new_command(char type, int id, double x_coord, double y_coord)
{
	if (id < 0)
		throw Invalid_Input("ID must be an integer greater than zero.");

	switch (type)
	{
		case 'g':
		{
			// search for id in Gold_Mine list
			Gold_Mine *ptr = get_Gold_Mine_ptr(id);

			if (ptr != 0) // id found, object already exists
				throw Invalid_Input("Gold_Mine with specified ID already exists.");

			// exception not thrown, create new object
			mine_ptrs.push_back(new Gold_Mine(id,Cart_Point(x_coord, y_coord)));
			object_ptrs.push_back(dynamic_cast<Game_Object*>(mine_ptrs.back()));
			active_ptrs.push_back(dynamic_cast<Game_Object*>(mine_ptrs.back()));
			break;
		}
		case 't':
		{
			Town_Hall *ptr = get_Town_Hall_ptr(id);
			if (ptr != 0)
				throw Invalid_Input("Town_Hall with specified ID already exists.");

			hall_ptrs.push_back(new Town_Hall(id,Cart_Point(x_coord, y_coord)));
			object_ptrs.push_back(dynamic_cast<Game_Object*>(hall_ptrs.back()));
			active_ptrs.push_back(dynamic_cast<Game_Object*>(hall_ptrs.back()));
			break;
		}
		case 'm':
		{
			Person *ptr = get_Person_ptr(id);
			if (ptr != 0)
				throw Invalid_Input("Person with specified ID already exists.");			
			
			person_ptrs.push_back(new Miner(id,Cart_Point(x_coord, y_coord)));
			object_ptrs.push_back(dynamic_cast<Game_Object*>(person_ptrs.back()));
			active_ptrs.push_back(dynamic_cast<Game_Object*>(person_ptrs.back()));
			break;
		}
		case 's':
		{
			Person *ptr = get_Person_ptr(id);
			if (ptr != 0)
				throw Invalid_Input("Person with specified ID already exists.");

			person_ptrs.push_back(new Soldier(id,Cart_Point(x_coord, y_coord)));
			object_ptrs.push_back(dynamic_cast<Game_Object*>(person_ptrs.back()));
			active_ptrs.push_back(dynamic_cast<Game_Object*>(person_ptrs.back()));
			break;
		}
		case 'i':
		{
			Person *ptr = get_Person_ptr(id);
			if (ptr != 0)
				throw Invalid_Input("Person with specified ID already exists.");

			person_ptrs.push_back(new Inspector(id,Cart_Point(x_coord, y_coord)));
			object_ptrs.push_back(dynamic_cast<Game_Object*>(person_ptrs.back()));
			active_ptrs.push_back(dynamic_cast<Game_Object*>(person_ptrs.back()));
			break;
		}
		default:
			throw Invalid_Input("Invalid object type specified.");
	}
}

// Model.get_Gold_Mine_list()
//-----------------------------------------	
// return the list of Gold_Mines

std::list<Gold_Mine*> Model::get_Gold_Mine_list()
{
	return mine_ptrs;
}

// Model.save()
//-----------------------------------------	
// save the current state of all Game_Objects

void Model::save(ofstream &file)
{
	// save current simulation time
	file << current_time << endl;

	// save number of active objects
	file << active_ptrs.size() << endl;

	// save catalog of active objects
	active_it = active_ptrs.begin();
	for (int i = 0; i < active_ptrs.size(); i++)
	{
		// write display_code and id_num of each object
		file << (*active_it)->get_display_code() << (*active_it)->get_id() << endl;
		active_it++;
	}

	// save all active Game_Objects
	active_it = active_ptrs.begin();
	for (int i = 0; i < active_ptrs.size(); i++)
	{
		(*active_it)->save(file);
		active_it++;
	}
}

void Model::restore(ifstream &file)
{
	// delete current game objects
	cout << "Restoring game..." << endl;

	for (object_it = object_ptrs.begin(); object_it != object_ptrs.end(); object_it++)
	{
		delete *object_it;
	}

	// clear all lists
	object_ptrs.clear();
	active_ptrs.clear();
	person_ptrs.clear();
	mine_ptrs.clear();
	hall_ptrs.clear();

	// load current simulation time
	file >> current_time;

	// load number of active objects
	int num_restore_objects;
	file >> num_restore_objects;

	// restore all active objects:
	for (int i = 0; i < num_restore_objects; i++)
	{
		// read object display_code and id_num
		char in_code;
		int in_id;

		file >> in_code >> in_id;

		// default construct new objects:

		if (in_code == 'm' || in_code == 'M') // Miner
		{
			person_ptrs.push_back(new Miner(in_id));
			object_ptrs.push_back(dynamic_cast<Game_Object*>(person_ptrs.back()));
		}
		else if(in_code == 's' || in_code == 'S') // Soldier
		{
			person_ptrs.push_back(new Soldier(in_id));
			object_ptrs.push_back(dynamic_cast<Game_Object*>(person_ptrs.back()));
		}        
		else if(in_code == 'i' || in_code == 'I') // Inspector
		{
			person_ptrs.push_back(new Inspector(in_id));
			object_ptrs.push_back(dynamic_cast<Game_Object*>(person_ptrs.back()));
		}
		else if(in_code == 'g' || in_code == 'G') // Gold_Mine
		{
			mine_ptrs.push_back(new Gold_Mine(in_code, in_id));
			object_ptrs.push_back(dynamic_cast<Game_Object*>(mine_ptrs.back()));
		}
		else if(in_code == 't' || in_code == 'T') // Town_Hall
		{
			hall_ptrs.push_back(new Town_Hall(in_code, in_id));
			object_ptrs.push_back(dynamic_cast<Game_Object*>(hall_ptrs.back()));
		}
	}

	// copy object_ptrs to active_ptrs
	active_ptrs = object_ptrs;

	// restore the variables of all active objects
	active_it = active_ptrs.begin();
	for (int i = 0; i < active_ptrs.size(); i++)
	{
		(*active_it)->restore(file, *this); // *this is model
		active_it++;
	}
	
	cout << "Game restored!" << endl;
}

// Model.get_Person_ptr()
//-----------------------------------------	
// return the Person pointer matching ID

Person * Model::get_Person_ptr(int id)
{
	person_it = person_ptrs.begin();
	for (int i = 0; i < person_ptrs.size(); i++)
	{
		if(id == (*person_it)->get_id())
			return *person_it;
		person_it++;
	}
	return 0;
}

// Model.get_Gold_Mine_ptr()
//-----------------------------------------	
// return the Gold_Mine pointer matching ID

Gold_Mine * Model::get_Gold_Mine_ptr(int id)
{
	mine_it = mine_ptrs.begin();
	for (int i = 0; i < mine_ptrs.size(); i++)
	{
		if(id == (*mine_it)->get_id())
			return *mine_it;
		mine_it++;
	}
	return 0;
}

// Model.get_Town_Hall_ptr()
//-----------------------------------------	
// return the Town_Hall pointer matching ID

Town_Hall * Model::get_Town_Hall_ptr(int id)
{
	hall_it = hall_ptrs.begin();
	for (int i = 0; i < hall_ptrs.size(); i++)
	{
		if(id == (*hall_it)->get_id())
			return *hall_it;
		hall_it++;
	}
	return 0;
}