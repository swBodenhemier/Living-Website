//Import Libraries
#include "Controller.h"

using namespace std;

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

// Main class to run all test cases
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
