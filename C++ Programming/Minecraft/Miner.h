// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Miner.h

#ifndef MINER_H
#define MINER_H

#include "Cart_Point.h"
#include "Cart_Vector.h"
#include "Person.h"
#include "Gold_Mine.h"
#include "Town_Hall.h"
#include <fstream>

// forward declaration of Model
class Model;

using namespace std;

class Miner:public Person
{
	public:

	// constructors:
	Miner();
	Miner(int);
	Miner(int, Cart_Point);
	~Miner();

	// public member functions:
	bool update();
	void start_mining(Gold_Mine *, Town_Hall *);
	void show_status();
	void save(ofstream &);
	void restore(ifstream &, Model &);
	void take_hit(int, Person *);

	private:

	// private member variables:
	double amount;
	Gold_Mine *mine;
	Town_Hall *home;
};

#endif