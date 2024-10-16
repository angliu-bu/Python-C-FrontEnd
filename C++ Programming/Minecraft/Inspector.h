// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Inspector.h

#ifndef INSPECTOR_H
#define INSPECTOR_H

#include "Model.h"
#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Game_Object.h"
#include "Person.h"
#include <fstream>
#include <list>

// forward declaration of Model
class Model;

class Inspector:public Person
{
	public:

	// constructors:
	Inspector();
	Inspector(int);
	Inspector(int, Cart_Point);
	~Inspector();

	// public member functions:
	bool update();
	void show_status();
	void start_inspecting(Model &);
	void take_hit(int, Person *);
	void save(ofstream &);
	void restore(ifstream &, Model &);

	private:

	// private member functions:
	Gold_Mine * get_closest_mine(list<Gold_Mine*>);

	// private member variables:
	Gold_Mine *current_mine;
	bool outbound;
	bool inspection_complete;
	Cart_Point starting_location;

	// inspection lists:
	list<Gold_Mine*> mines_to_inspect;
	list<Gold_Mine*> mines_inspected; // LIFO
	list<double> outbound_amounts;

};

#endif