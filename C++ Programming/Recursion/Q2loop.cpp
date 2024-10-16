// EC 327: Introduction to Software Engineering
// Programming Assignment 2, Question 2
//
// Carlton Duffett
// September 30, 2013
//
// Q2loop.cpp

#include <iostream>
#include "myFunctions.h"

using namespace std;

int main(){
	
	// prompt user for limiting value
	cout << "Enter: ";
	int limit;
	cin >> limit;
	
	// "limit" is total number of lines
	
	// error check
	if (limit > 0){
		
		// loop for total number of lines
		for (int i = 1; i <= limit; i++){
			
			// print leading spaces
			printLeadingSpaces(limit - i);
			
			// print the line
			for (int j = 1; j < i*2 ; j++){
				
				// increasing numbers
				if (j <= i)
					cout << j << " ";
				
				// decreasing numbers
				else
					cout << i*2 - j << " ";
			}
			cout << endl;
		}
	}
	return 0;
}