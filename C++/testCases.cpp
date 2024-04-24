//Import Libraries
#include "Controller.h"

using namespace std;

void printRunCase(int number, bool returnCase)
{
	cout << "Test Case #" << number << " executed with result: ";

	//Check what to print
	if (returnCase)
	{
		cout << "True" << endl;
	}
	else
	{
		cout << "False" << endl << endl;
	}
}


// Main class to run all test cases
int main()
{
	int testNumber;

	//Run all test cases
	for (testNumber = 1; testNumber < 6; testNumber++)
	{
		printRunCase(testNumber, runTests("TestInputFiles/Test" + to_string(testNumber) + "/"));
	}

	//Return successful run
	return 0;
}
