// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Game_Object.h

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Cart_Point.h"
#include <fstream>

// forward declaration of Model
class Model;

using namespace std;

class Game_Object
{
	public:

	//constructors:
	Game_Object();
	Game_Object(char, int);
	Game_Object(char, int, Cart_Point);
	virtual ~Game_Object();

	// public member functions:
	Cart_Point get_location();
	int get_id();
	char get_display_code();
	void drawself(char *);
	virtual bool is_alive();
	virtual void show_status();
	virtual bool update() = 0; // pure virtual function
	virtual void save(ofstream &);
	virtual void restore(ifstream &, Model &);

	protected:

	// protected member variables:
	Cart_Point location;
	char display_code;
	char state;

	private:

	// private member variables:
	int id_num;
};

#endif