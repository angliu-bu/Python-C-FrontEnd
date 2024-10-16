// EC 327: Introduction to Software Engineering
// Programming Assignment 2, Question 2
//
// Carlton Duffett
// October 9, 2013
//
// myfunctions.h
// function prototypes

/*********************************************/
/* Q2recursion1 functions:                   */
/*********************************************/

int printTriangle(int, int);
int printTriangleLine(int, int, int);

/*********************************************/
/* Q2recursion2 functions:                   */
/*********************************************/

int printRhombus(int);

int printRhombusTop(int *, int, int);
int printRhombusTopLine(int *, int, int, int);

int printRhombusBottom(int *, int, int);
int printRhombusBottomLine(int *, int, int, int);

int findNumPrimes(int, int);
int genPrimes(int *,int, int, int);
bool testPrime(int, int);

/*********************************************/
/* Q2 shared functions: 		              */
/*********************************************/

void printLeadingSpaces(int);