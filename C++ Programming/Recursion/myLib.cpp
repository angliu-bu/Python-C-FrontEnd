// EC 327: Introduction to Software Engineering
// Programming Assignment 2, Question 1
//
// Carlton Duffett
// September 30, 2013
//
// myLib.cpp
// function definitions

#include <iostream>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "myLib.h"

using namespace std;

/******************************************************************************/
/* initialize()								                                   */
/******************************************************************************/

// initialize() prints the program output header
void initialize(void){
	
	cout << "EC327: Introduction to Software Engineering" << endl
		 << "Fall 2013" << endl
		 << "Programming Assignment 2" << endl
		 << "Maximum computation is: " << ENTRIES << endl << endl;
		
	return;
}

/******************************************************************************/
/* checkCode()								                                   */
/******************************************************************************/

// checkCode() error checks the user code input
bool checkCode(char userCode){
	
	// valid user codes:
	// s,c,r,e,l,n,i,o,q
	
	// check if code is letter
	if (!isalpha(userCode))
		return false;
	else{
		// make all codes lowercase for comparison
		userCode = tolower(userCode);
		
		// check if code is valid
		if (userCode == 's')
			return true;
		else if (userCode == 'c')
			return true;
		else if (userCode == 'r')
			return true;
		else if (userCode == 'e')
			return true;
		else if (userCode == 'l')
			return true;
		else if (userCode == 'n')
			return true;
		else if (userCode == 'i')
			return true;
		else if (userCode == 'o')
			return true;
		else if (userCode == 'q')
			return true;
		else
			return false;
	}
}

/******************************************************************************/
/* writeDataToFile()						                                   */
/******************************************************************************/

// writeDataToFile() writes the program output to specified file name
void writeDataToFile(const char *outputFileName){

	// create file output stream
	ofstream myOutput;
	
	// create file
	myOutput.open(outputFileName);
	
	// initialize random number generator
	srand(time(0));
	
	// randomize "first" parameter (0 - 10)
	int ranFirst = rand()%11;

	// randomize "last" parameter (20 - 30)
	int ranLast = rand()%11 + 20;
	
	// randomize "delta" parameter (5 - 10)
	int ranDelta = rand()%6 + 5;
	
	
	// write to file
	double currentValueToWrite = ranFirst;
	int numEntriesWritten = 0;
	
	while(currentValueToWrite <= ranLast && numEntriesWritten < ENTRIES){
		
		myOutput << "nyanCat(" << fixed << setprecision(2) << currentValueToWrite
			   << ") = " << fixed << setprecision(5)
			   << findNyanCatValue(currentValueToWrite) << endl;
			
		currentValueToWrite += ranDelta;
		numEntriesWritten++;
	}
	
	// close file
	myOutput.close();
	
	cout << "File has been written." << endl << endl;
	
	return;
}

/******************************************************************************/
/* readDataFromFile()						                                   */
/******************************************************************************/

// readDataFromFile() reads the program input from specified file name
void readDataFromFile(const char *inputFileName){
	
	// create file input stream
	ifstream myInput;
	
	// open file
	myInput.open(inputFileName);
	
	// file variables
	double firstLoad;
	double lastLoad;
	double deltaLoad;
	
	// read file
	if (myInput.is_open()){
		
		myInput >> firstLoad >> lastLoad >> deltaLoad;
		myInput.close();	// close file
		
	}else{
		
		cout << "Unable to open file." << endl << endl;
		return;
	}
	
	// error check parameters
	if (checkParams(firstLoad, lastLoad, deltaLoad))
		printResult('n', firstLoad, lastLoad, deltaLoad);
	
	return;	
}

/******************************************************************************/
/* findNyanCatValue()						                                   */
/******************************************************************************/

// findNyanCatValue() calculated the NyanCat value for a double input
double findNyanCatValue(double number){
	
	// computation:
	double base = 2*number;
	return pow(base,number);	
}

/******************************************************************************/
/* getCode()								                                   */
/******************************************************************************/

// getCode() prompts the user for a command
char getCode(void){
	
	char userCode;
	cout << "Please enter command code: ";
	cin >> userCode;
	return userCode;
}

/******************************************************************************/
/* getParams()								                                   */
/******************************************************************************/

// getParams() prompts the user for parameters
void getParams(double &firstLoc, double &lastLoc, double &deltaLoc){
	
	cout << "Please enter command parameters: ";
	cin >> firstLoc >> lastLoc >> deltaLoc;
	return;
}

/******************************************************************************/
/* checkParams()							                                   */
/******************************************************************************/

// checkParams() error checks the user-entered parameters
bool checkParams(double firstParam, double lastParam, double deltaParam){
	
	// compare first to last
	if (firstParam >= lastParam){
		cout << "Invalid parameters." << endl << endl;
		return false;
		
	// check domain of delta
	}else if (deltaParam <= 0){
		cout << "No computation needed." << endl << endl;
		return false;
		
	// no error
	}else
		return true;
}

/******************************************************************************/
/* printResult()							                                   */
/******************************************************************************/

// printResult() prints the result(s) given parameters and the command code
void printResult(char userCodeIn, double firstIn, double lastIn, double deltaIn){
	
	// set starting value
	double currentValue = firstIn;
	double currentResult;
	string functionStr;
	int numEntries = 0;
	
	// print result(s)	
	while(currentValue <= lastIn && numEntries < ENTRIES){
		
		switch (userCodeIn){
			
			case 's':
			
				currentResult = sin(currentValue);
				functionStr = "sin(";
				break;
			
			case 'c':
			
				currentResult = cos(currentValue);
				functionStr = "cos(";
				break;
			
			case 'r':
			
				currentResult = sqrt(currentValue);
				functionStr = "sqrt(";
				break;
			
			case 'e':
			
				currentResult = exp(currentValue);
				functionStr = "exp(";
				break;
			
			case 'l':
			
				currentResult = log(currentValue);
				functionStr = "log(";
				break;
			
			case 'n':
			
				currentResult = findNyanCatValue(currentValue);
				functionStr = "nyanCat(";
				break;
		}
		
		cout << functionStr << fixed << setprecision(2) << currentValue
			 << ") = " << fixed << setprecision(5) << currentResult << endl;
		
		currentValue += deltaIn;
		numEntries++;
	}
	cout << endl;		
	return;
}