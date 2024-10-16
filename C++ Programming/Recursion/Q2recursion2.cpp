// EC 327: Introduction to Software Engineering
// Programming Assignment 2, Question 2
//
// Carlton Duffett
// October 4, 2013
//
// Q2recursion2.cpp

#include <iostream>
#include "myFunctions.h"

using namespace std;
int main(){
	
	// prompt user for limiting value
 	int a;
    cout << "Enter: ";
    cin >> a;
	
	// call recursive function
    printRhombus(a);

    return 0;
}