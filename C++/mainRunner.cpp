//Import Libraries
#include "Controller.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

//Main Function
//Objectives: Will manage when the program will run
//Prereqs: None
//Postreq: HTML files are changed and uploaded
//Notes: Can be adjusted to run as freaquently as the user wants
int main()
{
	//When program is initalized run the task once then loop
	if (run())
	{
		cout << "\nSuccessfully Changed HTML Files!\n";
	}
	else
	{
		cout << "\nFailed to Change HTML Files.\n";
	}

	/*
	while (true)
	{
		auto currentTime = chrono::system_clock::now();
		auto nextSunday = chrono::time_point_cast<chrono::hours>(currentTime + chrono::hours(24 * (7 - currentTime.time_since_epoch().count() % 7)));

		//Sleep until next sunday
		this_thread::sleep_until(nextSunday);

		//Run code
		if (run())
		{
			cout << "\nSuccessfully Changed HTML Files!\n";
		}
		else
		{
			cout << "\nFailed to Change HTML Files.\n";
		}
	}
	*/
	return 0;
}