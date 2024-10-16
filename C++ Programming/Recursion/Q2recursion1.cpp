// EC 327: Introduction to Software Engineering
// Programming Assignment 2, Question 2
//
// Carlton Duffett
// October 4, 2013
//
// Q2recursion1.cpp

#include <iostream>
#include "myFunctions.h"

using namespace std;
int main(){
	
	// prompt user for limiting value
	cout << "Enter: ";
	int level;
	cin >> level;
	
	// call recursive function
	int k = printTriangle(level, level);
	
	return 0;
}