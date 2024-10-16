// EC 327 PROGRAM 1, QUESTION 1
// "Shortest Distance From a Point to a Line"
//
// Carlton Duffett
// September 15, 2013

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
int main(){
	
	// declare variables:
	
	// user input variables
 	double x1,x2,x3;
	double y1,y2,y3;
	
	// calculation variables
	double slope;
	double x0, y0; 	// (x0 y0) defines closest point on line
	double b;		// b fulfils the equation of the line y = mx + b
	double dist;
	
	
	// get user input
	cout << "Enter three x,y coordinates:"<< endl;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	
	// error check input
	if (cin.fail()){
		cout << "Error: Wrong input format." << endl;
		return 0;
	}else{
	
		// calculate slope of line
		slope = (y2 - y1)/(x2 - x1);

		// calculate 'b'
		b = y1 - slope*x1;

		// calculate nearest point on line (x0 y0)
		x0 = (slope*y3 + x3 - slope*b)/(pow(slope,2) + 1);
		y0 = (pow(slope,2)*y3 + slope*x3 + b)/(pow(slope,2) + 1);

		
		// calculate distance between point (x3 y3) and point (x0 y0)
		dist = sqrt(pow((x3 - x0),2) + pow((y3 - y0),2));
		
		// output calculated distance
		if (dist == 0){
			cout << "The point is on the line." << endl;
		}else{
			cout << "The shortest distance for " << x3 << "," << y3
					<< " to the line composed of " << x1 << "," << y1
					<< " and " << x2 << "," << y2 << " is? "
					<< fixed << setprecision(2) << dist << "." << endl;
		}
	}
		
	return 0;
}