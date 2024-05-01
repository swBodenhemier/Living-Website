//Import Libraries
#include "Controller.h"

using namespace std;

//Print Run Case Function
//Objectives: Will print to console weather the test cases have succeeded or not
//Prereqs: Files have been compared and will tell if true or false.
//Postreq: Console statement has been printed with the end result.
//Notes: None
void printRunCase(int number, bool returnCase)
{
	cout << "Test Case #" << number << " executed with result: ";

	//Check what to print
	if (returnCase)
	{
		cout << "True" << endl << endl;
	}
	else
	{
		cout << "False" << endl << endl;
	}
}

//Compare Files Function
//Objectives: Will compare character by character to make sure each file is the same
//			  as the expected output.
//Prereqs: Files are accessable and new HTML files have been created
//Postreq: returns true if files are the same or false if not
//Notes: None
bool compareFiles(ifstream* file1, ifstream* file2)
{
	//Check if each file is open
	if (!file1->is_open() && file2->is_open())
	{
		cout << "Error: files not open to compare." << endl;
	}

	//Compare each character of files until EOF
	while (!file1->eof() && !file2->eof())
	{
		if (file1->get() != file2->get())
		{
			return false;
		}
	}

	return true;
}

//Comapre Test Results Function
//Objectives: Will compare the output of the code to the expected output
//Prereqs: Files are accessable and new HTML files have been created
//Postreq: returns true if files are the same or false if not
//Notes: None
bool compareTestCase(string locationOfFiles, string locationOfValidateFiles)
{
	//Initialize Vairables
	ifstream newFile, validFile;
	string filesToOpen[7] = { "scp_main_page.html", "scp_081_page.html", "scp_999_page.html",
							"scp_1990_page.html", "scp_2006_page.html",  "scp_2161_page.html",
							"scp_8012_page.html" };
	int count;

	//Check each file if they are the same
	for (count = 0; count < 7; count++)
	{
		//Open files
		try
		{
			newFile.open(locationOfFiles + filesToOpen[count]);
			validFile.open(locationOfValidateFiles + filesToOpen[count]);

			if (!newFile.is_open())
			{
				throw runtime_error("Error: failed to find file at location \"" + locationOfFiles + filesToOpen[count] + "\"");
			}
			else if (!validFile.is_open())
			{
				throw runtime_error("Error: failed to find file at location \"" + locationOfValidateFiles + filesToOpen[count] + "\"");
			}
		}
		catch (runtime_error e)
		{
			cout << e.what() << endl;
			return false;
		}

		//Compare contents of each file
		if (!compareFiles(&newFile, &validFile))
		{
			return false;
		}
	}

	return true;
}

//TEST Main Function
//Objectives: Will manage when the program will run
//Prereqs: None
//Postreq: HTML files are changed and compared to the expected output
//Notes: ONLY USED FOR TEST CASES!!!!
/*
int main()
{
	int testNumber;

	//Run all test cases
	for (testNumber = 1; testNumber < 16; testNumber++)
	{
		if (runTests("TestInputFiles/Test" + to_string(testNumber) + "/"))
		{
			printRunCase(testNumber, compareTestCase("TestInputFiles/Test" + to_string(testNumber) + "/deployed_website/", "TestExpectedOutputs/Test" + to_string(testNumber) + "/"));
		}
		else
		{
			printRunCase(testNumber, false);
		}
		
	}

	//Return successful run
	return 0;
}
*/