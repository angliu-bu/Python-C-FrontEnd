// EC 327: Introduction to Software Engineering
// Programming Assignment 2, Question 1
//
// Carlton Duffett
// September 30, 2013
//
// main function

#include <iostream>
#include <cctype>
#include "myLib.h"

extern const int ENTRIES = 10;
extern const char *OUTPUT_FILE_NAME = "myOutput.txt";
extern const char *INPUT_FILE_NAME = "myInput.txt";

using namespace std;

int main(){
	
	// declare runtime variables
	bool progRunning = true;
	char userCode;
	
	// parameters
	double first;
	double last;
	double delta;
	
	// print program header
	initialize();
	
	// main program loop
	while (progRunning){
		
		// get command code
		userCode = getCode();
		
		// error check command code
		while (!checkCode(userCode)){
			
			cout << "Not a legal command code!" << endl << endl;
			userCode = getCode();
		}
		
		// evaluate valid command code
		userCode = tolower(userCode);

		switch (userCode){
			
			case 'i':
			
				// read from file
				readDataFromFile(INPUT_FILE_NAME);
				break;
			
			case 'o':
			
				// write to file
				writeDataToFile(OUTPUT_FILE_NAME);
				break;
			
			case 'q':
				
				// exit program (exit main loop)
				cout << "Ciao!" << endl;
				progRunning = false;
				break;
				
			default: // s,c,r,e,l,n options
			
				// get parameters
				getParams(first, last, delta);
				
				// check parameters, then print result
				if(checkParams(first, last, delta))
						printResult(userCode, first, last, delta);
				break;
		}
	}	
	return 0;
}