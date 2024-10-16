// EC 327 PROGRAM 1, QUESTION 4
// "Simple Ciphering with ASCII"
//
// Carlton Duffett
// September 18, 2013

#include <iostream>
#include <cctype>

using namespace std;

int main(){
	
	// create upper/lowercase alphabets for reference
	string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string lower = "abcdefghijklmnopqrstuvwxyz";
	
	// prompt user for character, operation
	cout << "Enter char, operation: ";
	
	// get user input
	char character;
	int operation;
	 
	cin >> character >> operation;
	
	// error check input
	
	// multiple characters:
	if (cin.fail()){
		cout << "Result: More than one character inputted" << endl;
		return 0;
		
	// illegal character
	}else if (!isalpha(character)){
		cout << "Result: Illegal char" << endl;
		return 0;
		
	// illegal operation
	}else if (operation < 1 || operation > 3){
		cout << "Result: Illegal operation" << endl;
		return 0;
		
	// no errors, continue
	}else{
		
		string output;
		int origindex;
		int newindex;
		
		switch (operation){
			
			 // OPTION 1: CONVERT CASE
			case 1:
			
				if (isupper(character)){
					output = tolower(character);
				}else{
					output = toupper(character);
				}
				
				break;
			
			// OPTION 2: REVERSE ALPHABET/CASE
			case 2:
				
				// UPPERCASE		
				if (isupper(character)){	
					
					// find index of character in uppercase alphabet
					origindex = upper.find(character) + 1;
					newindex = 26 - origindex;
					
					// find "reverse" character, change case
					output = lower.substr(newindex,1);
				
				// LOWERCASE				
				}else{						
					
					// find index of character in lowercase alphabet
					origindex = lower.find(character) + 1;
					newindex = 26 - origindex;
					
					// find "reverse" character, change case
					output = upper.substr(newindex,1);
				}
				
				break;
			
			// OPTION 3: ENCRYPT
			case 3:
			
				// UPPERCASE
				if (isupper(character)){
					
					// find index of character in uppercase alphabet
					origindex = upper.find(character) + 1;
					
					// if necessary, "wrap around" to beginning of alphabet
					if (origindex > 20){
						newindex = 6 - (27 - origindex);
					}else{
						newindex = origindex + 5;
					}
					
					// generate corresponding character
					output = upper.substr(newindex,1);
					
				// LOWERCASE	
				}else{						
				
					// find index of character in uppercase alphabet
					origindex = lower.find(character) + 1;
					
					// if necessary, "wrap around" to beginning of alphabet
					if (origindex > 20){
						newindex = 6 - (27 - origindex);
					}else{
						newindex = origindex + 5;
					}
										
					// generate corresponding character
					output = lower.substr(newindex,1);
				}
				
				break;
		}
		
		// output result
		cout << "Result: " << output << endl;
		
		return 0;
	}
}