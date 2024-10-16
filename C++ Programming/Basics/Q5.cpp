// EC 327 PROGRAM 1, QUESTION 5
// "Grade Calculator"
//
// Carlton Duffett
// September 18, 2013

#include <iostream>
#include <iomanip>

using namespace std;
int main(){
	
	// prompt user for all grade values
	
	cout << "Enter quiz average: ";
	double qzavg;
	cin >> qzavg;
	
	cout << "Enter lab average: ";
	double labavg;
	cin >> labavg;
	
	cout << "Enter hw average: ";
	double hwavg;
	cin >> hwavg;
	
	cout << "Enter program average: ";
	double progavg;
	cin >> progavg;
	
	cout << "Enter project average: ";
	double projavg;
	cin >> projavg;
	
	cout << "Enter midterm average: ";
	double midavg;
	cin >> midavg;

	cout << "Enter final average: ";
	double finavg;
	cin >> finavg;
	
	// adjust grades by weight, add to total
	double overall = 0;
	
		// quiz average (5%)
		overall = overall + (qzavg/100)*0.05;
		
		// lab average (10%)
		overall = overall + (labavg/100)*0.1;
		
		// hw average (15%)
		overall = overall + (hwavg/100)*0.15;
		
		// program average (25%)
		overall = overall + (progavg/100)*0.25;
			
		// project average (15%)
		overall = overall + (projavg/100)*0.15;
			
		// midterm average (15%)
		overall = overall + (midavg/100)*0.15;
		
		// final average (15%)
		overall = overall + (finavg/100)*0.15;
		
	// output overall average
	cout << "Your overall average is: " << fixed << setprecision(2)
		<< overall*100 << "." << endl;
		
	return 0;
}