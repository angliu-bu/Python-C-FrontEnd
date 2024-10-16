// EC 327: Introduction to Software Engineering
// Programming Assignment 2, Question 1
//
// Carlton Duffett
// September 30, 2013
//
// myLib.h
// function prototypes

// global constants:
extern const int ENTRIES;
extern const char *OUTPUT_FILE_NAME;
extern const char *INPUT_FILE_NAME;

// required functions:
void initialize(void);
bool checkCode(char);
void writeDataToFile(const char *);
void readDataFromFile(const char *);
double findNyanCatValue(double);

// my functions:
char getCode(void);
void getParams(double &, double &, double &);
bool checkParams(double, double, double);
void printResult(char, double, double, double);