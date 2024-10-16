// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Town_Hall.h

#ifndef TOWN_HALL_H
#define TOWN_HALL_H

#include "Cart_Point.h"
#include "Game_Object.h"
#include <fstream>

// forward declaration of Model
class Model;

using namespace std;

class Town_Hall:public Game_Object
{
	public:
	
	// constructors:
	Town_Hall();
	Town_Hall(char, int);
	Town_Hall(int, Cart_Point);
	~Town_Hall();
	
	// public member functions:
	void deposit_gold(double);
	bool update();
	void show_status();
	void save(ofstream &);
	void restore(ifstream &, Model &);
	
	private:
	
	// private member variables:
	double amount;
};

#endif