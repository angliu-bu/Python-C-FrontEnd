// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Model.h

#ifndef MODEL_H
#define MODEL_H

#include "View.h"
#include "Game_Object.h"
#include "Person.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include <list>
#include <fstream>

using namespace std;

class Model
{
	public:

	// constructors:
	Model();
	~Model();

	// public member functions:
	bool update();
	void display(View &);
	void show_status();
	void handle_new_command(char, int, double, double);
	std::list<Gold_Mine*> get_Gold_Mine_list();
	void save(ofstream &);
	void restore(ifstream &);
	
	// pointer functions:
	Person * get_Person_ptr(int);
	Gold_Mine * get_Gold_Mine_ptr(int);
	Town_Hall * get_Town_Hall_ptr(int);

	private:

	// copy constructor: (no copying permitted)
	Model(Model &);

	int current_time;

	// game object linked lists:
	list<Game_Object*> object_ptrs;
	list<Game_Object*> active_ptrs;
	list<Person*> person_ptrs;
	list<Gold_Mine*> mine_ptrs;
	list<Town_Hall*> hall_ptrs;

	// list iterators:
	list<Game_Object*>::iterator object_it;
	list<Game_Object*>::iterator active_it;
	list<Person*>::iterator person_it;
	list<Gold_Mine*>::iterator mine_it;
	list<Town_Hall*>::iterator hall_it;
};

#endif