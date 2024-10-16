// EC 327: Introduction to Software Engineering
// Programming Assignment 2, Question 2
//
// Carlton Duffett
// October 9, 2013
//
// myFunctions.cpp

#include <iostream>
#include "myFunctions.h"

using namespace std;

/*************************************************************************/
/* QUESTION 2, RECURSION 1 FUNCTIONS:                                    */
/*************************************************************************/

// printTriangle()
// --------------------------------------------
// recursively prints each line of the triangle

int printTriangle(int level, int i){
	
	// base case
	if (i == 0)
		return 1;
		
	// recursion
	else{
		int k  = printTriangle(level, i - 1);
		
		// print line of the triangle
		k = printTriangleLine(level, i, i*2 - 1); // j < i*2
		cout << endl;
		return k;
	}
}

// printTriangleLine()
// --------------------------------------------
// recursively prints a given line of the triangle

int printTriangleLine(int level, int i, int j){
	
	// base case
	if (j == 0){
		
		// print leading spaces
		printLeadingSpaces(level - i);
		return 1;
	}
		
	// recursion
	else{
		int k = printTriangleLine(level, i, j - 1);
		
		// increasing values on the line
		if (j <= i)
			cout << j << " ";
			
		// decreasing values on the line
		else
			cout << i*2 - j << " ";
			
		return k;
	}
}

/*************************************************************************/
/* QUESTION 2, RECURSION 2 FUNCTIONS:                                    */
/*************************************************************************/

// printRhombus()
// --------------------------------------------
// recursively prints a rhombus of prime numbers
// less than n

int printRhombus(int n){
	
	if (n > 2){
		
		// find number of primes < n
		int numPrimes = findNumPrimes(n, n - 1);
		
		// create array to store primes < n
		int *primes = new int [numPrimes];
		
		// generate array of primes < n
		int j = 0; // starting index of array
		genPrimes(primes, numPrimes - 1, n - 1, j);
		
		// print top half of rhombus
		printRhombusTop(primes, numPrimes, numPrimes);
		
		// print bottom half of rhombus
		printRhombusBottom(primes, numPrimes, numPrimes - 1);
		
		// delete array of primes
		delete [] primes;
	}
	return 0;
}

// printRhombusTop()
// --------------------------------------------
// prints the top half of the rhombus

int printRhombusTop(int *primes, int level, int i){
	
	// base case
	if (i == 0)
		return 1;
	
	// recursion
	else{
		int k = printRhombusTop(primes, level, i - 1);
		
		// print line of the rhombus
		k = printRhombusTopLine(primes, level, i, i*2 - 1);
		cout << endl;
		return k;
	}
}

// printRhombusBottom()
// --------------------------------------------
// prints the bottom half of the rhombus

int printRhombusBottom(int *primes, int level, int i){
	
	// base case
	if (i == 0){
		return 1;
		
	// recursion
	}else{
		int k = printRhombusBottom(primes, level, i - 1);
		
		// print line of the rhombus
		k = printRhombusBottomLine(primes, level, i, (level - i)*2 - 1);
		cout << endl;
		return k;
	}
}

// printRhombusTopLine()
// --------------------------------------------
// prints the primes on a given line
// of the top of the rhombus

int printRhombusTopLine(int *primes, int level, int i, int j){
	
	// base case
	if (j == 0){
		printLeadingSpaces(level - i);
		return 1;
	
	// recursion
	}else{
		int k = printRhombusTopLine(primes, level, i, j - 1);
		
		// print increasing values
		if (j <= i)
			cout << primes[j - 1] << " ";
			
		// print decreasing values
		else
			cout << primes[i*2 - j - 1] << " ";
			
		return k;
	}	
}

// printRhombusBottomLine()
// --------------------------------------------
// prints the primes on a given line
// of the bottom of the rhombus

int printRhombusBottomLine(int *primes, int level, int i, int j){
	
	// base case
	if (j == 0){
		printLeadingSpaces(i);
		return 1;
		
	// recursion
	}else{
		int k = printRhombusBottomLine(primes, level, i, j - 1);
		
		// print increasing values
		if (j <= (level - i))
			cout << primes[j - 1] << " ";
			
		// print decreasing values
		else
			cout << primes[(level - i)*2 - j - 1] << " ";
			
		return k;
	}
}

// genPrimes()
// --------------------------------------------
// populates an array with n primes

int genPrimes(int *primes, int n, int i, int j){

	// base case
	if (i < 2){
		return 0;
		
	//recursion
	}else{
		
		if (testPrime(i, i/2)){ // i is prime
		
			// add i to the array
			primes[n - j] = i;
			j++;
			
			// generate next prime
			return genPrimes(primes, n, i - 1, j);
			
		}else
		
			// generate next prime
			return genPrimes(primes, n, i - 1, j);
	}
}

// findNumPrimes()
// --------------------------------------------
// finds the total number of primes less than n

int findNumPrimes(int n, int i){

	// base case
	if (i < 2){
		return 0;
		
	//recursion
	}else{
		if (testPrime(i, i/2)){ // i is prime
			return findNumPrimes(n, i - 1) + 1; // add 1 to count
		}else
			return findNumPrimes(n, i - 1);
	}
}

// testPrime()
// --------------------------------------------
// tests a number i for primality using all
// possible divisors j

bool testPrime(int i, int j){

	// base case
	if (j < 2){
		return true;
		
	// recursion
	}else{
		
		if (i%j == 0) // i is not prime
			return false;
			
		else // i MAY be prime
			return testPrime(i, j - 1); // test next j
	}
}


/*************************************************************************/
/* QUESTION 2, SHARED FUNCTIONS:	                                      */
/*************************************************************************/

// printLeadingSpaces()
// --------------------------------------------
// prints the specified number of spaces

void printLeadingSpaces(int numSpaces){
	string spaces;
	spaces.append(2*numSpaces, ' '); // 2 spaces per unit
	cout << spaces;
	return;
}
