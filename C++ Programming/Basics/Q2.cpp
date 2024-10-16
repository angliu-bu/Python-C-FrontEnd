// EC 327 PROGRAM 1, QUESTION 2
// "Converting Units"
//
// Carlton Duffett
// September 16, 2013

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
int main(){
	
	// declare variables
	int selection;
	double inval;
	double convval;
	
	// display selection list to user
	cout << "Meters to Feet (enter 0)" << endl
		<< "Meters to Leagues (enter 1)" << endl
		<< "Feet to Meters (enter 2)" << endl
		<< "Feet to Leagues (enter 3)" << endl
		<< "Leagues to Meters (enter 4)" << endl
		<< "Leagues to Feet (enter 5)" << endl
		<< "Conversion Type: ";
	
	// get user selection
	cin >> selection;
	
	// error check selection
	while (selection > 5 || selection < 0){
		
		// display error message
		cout << "Error: please make a valid selection (0 - 5)." << endl;
		
		// repeat valid options
		cout << "Meters to Feet (enter 0)" << endl
			<< "Meters to Leagues (enter 1)" << endl
			<< "Feet to Meters (enter 2)" << endl
			<< "Feet to Leagues (enter 3)" << endl
			<< "Leagues to Meters (enter 4)" << endl
			<< "Leagues to Feet (enter 5)" << endl
			<< "Conversion Type: ";
		
		// get user selection
		cin >> selection;
	}
	
	switch (selection){
		
		case 0:	// Meters to Feet
		
			// prompt user for value
			cout << "Enter the amount in Meters";
			cin >> inval;
			
			// convert value
			convval = inval*3.280833;
			
			// output value
			cout << inval << " Meters is ";
			cout << fixed << setprecision(6) << convval << " Feet." << endl;
		
			break;
		
		case 1: // Meters to Leagues
		
			// prompt user for value
			cout << "Enter the amount in Meters: ";
			cin >> inval;
			
			// convert value
			convval = inval/5556;
				
			// output value
			cout << inval << " Meters is ";
			cout << fixed << setprecision(6) << convval << " Leagues." << endl;
		
			break;
		
		case 2: // Feet to Meters
	
			// prompt user for value
			cout << "Enter the amount in Feet: ";
			cin >> inval;
			
			// convert value
			convval = inval/3.280833;
						
			// output value
			cout << endl << inval << " Feet is ";
			cout << fixed << setprecision(6) << convval << " Meters." << endl;
		
			break;
		
		case 3: // Feet To Leagues
		
			// prompt user for value
			cout << "Enter the amount in Feet: ";
			cin >> inval;
				
			// convert value
			convval = inval/18228.3465;
							
			// output value
			cout << inval << " Feet is ";
			cout << fixed << setprecision(6) << convval << " Leagues." << endl;
		
			break;
		
		case 4: // Leagues to Meters
		
			// prompt user for value
			cout << "Enter the amount in Leagues: ";
			cin >> inval;
							
			// convert value
			convval = inval*5556;
									
			// output value
			cout << inval << " Leagues is ";
			cout << fixed << setprecision(6) << convval << " Meters." << endl;

		
			break;
		
		case 5: // Leagues to Feet
		
			// prompt user for value
			cout << "Enter the amount in Leagues: ";
			cin >> inval;
										
			// convert value
			convval = inval*18228.3465;
												
			// output value
			cout << inval << " Leagues is ";
			cout << fixed << setprecision(6) << convval << " Feet." << endl;
		
			break;
	}
	
	return 0;
}