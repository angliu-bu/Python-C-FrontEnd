// EC 327 PROGRAM 1, QUESTION 3
// "Hamming Distance"
//
// Carlton Duffett
// September 18, 2013

#include <iostream>
#include <sstream>

#define minval 0
#define maxval 999999

using namespace std;
int main(){
	
	// prompt user for two values
	cout << "Enter two integers between " << minval
		<< " and " << maxval << ": ";
	
	// recieve values
	int val1;
	int val2;
	cin >> val1 >> val2;
	
	// error check user input
	while (val1 < minval || val1 > maxval || val2 < minval || val2 > maxval){
		
		cout << "ERROR: please enter two values in the specified range (0 - 999999)." << endl;
		
		// prompt user for two new values
		cout << "Enter two integers between " << minval
				<< " and " << maxval << ": ";
		
		// recieve values
		cin >> val1 >> val2;
	}

	// convert input to strings
	string str1;
	string str2;
	
	stringstream s1;
	s1 << val1;
	str1 = s1.str();
	
	stringstream s2;
	s2 << val2;
	str2 = s2.str();
	
	// find the length of each string
	int str1len;
	int str2len;
	str1len = str1.length();
	str2len = str2.length();
	
	// add leading zeros, if needed, to strings
	string zeros1;
	string zeros2;
	int numzeros;
	
	// string 1:
	if (str1len < 6){
		numzeros = 6 - str1len;
		zeros1.append(numzeros, '0');
		zeros1.append(str1);
		str1 = zeros1;
	}
	
	// string 2:
	if (str2len < 6){
		numzeros = 6 - str2len;
		zeros2.append(numzeros, '0');
		zeros2.append(str2);
		str2 = zeros2;
	}
	
	// compare strings
	string substr1;
	string substr2;
	bool same;
	int hamdist = 0;
	
	for (int i = 1; i <= 6; i++){
		
		// compare i-th character of strings
		substr1 = str1.substr((i - 1),1);
		substr2 = str2.substr((i - 1),1);
		same = substr1.compare(substr2);
		
		// increment counter if characters inequal
		if (same != false){
			hamdist++;
		}
	}
	
	// output Hamming distance
	cout << "Hamming distance between " << val1 << " and " << val2
		<< " is " << hamdist << "." << endl;
	
	return 0;
}