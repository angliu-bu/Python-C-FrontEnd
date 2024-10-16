// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Soldier.h

#ifndef SOLDIER_H
#define SOLDIER_H

#include "Cart_Point.h"
#include "Person.h"
#include <fstream>

// forward declaration of Model
class Model;

using namespace std;

class Soldier:public Person
{
	public:

	// constructors:
	Soldier();
	Soldier(int);
	Soldier(int, Cart_Point);
	~Soldier();

	// public member functions:
	void start_attack(Person *);
	bool update();
	void show_status();
	void take_hit(int, Person *);
	void save(ofstream &);
	void restore(ifstream &, Model &);

	private:

	// private member variables:
	int attack_strength;
	double range;
	Person *target;
};

#endif