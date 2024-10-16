// EC 327: Introduction to Software Engineering
// Programming Assignment 5
//
// Carlton Duffett
// December 11, 2013
//
// Input_Handling.h

#ifndef INPUT_HANDLING_H
#define INPUT_HANDLING_H

class Invalid_Input
{
	public:
	Invalid_Input(char * in_ptr):msg_ptr(in_ptr){} 
	const char * const msg_ptr;

	private:
	Invalid_Input(); // no default construction allowed
};


#endif