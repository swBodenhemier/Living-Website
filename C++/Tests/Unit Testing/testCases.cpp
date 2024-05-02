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
		cout << "True" << endl;
	}
	else
	{
		cout << "False" << endl;
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

//Comapre Test Results Function
//Objectives: Will compare the output of the code to the expected output
//Prereqs: Both arrays are filled in with valid inputs, end represents end of array
//Postreq: returns true if arrays are the same or false if not
//Notes: None
bool compareTestCase(int* inputArray, int testArray[], int end)
{
	//Initialize Variables
	int loop;

	for (loop = 0; loop < end; loop++)
	{
		if (inputArray[loop] != testArray[loop])
		{
			return false;
		}
	}

	return true;
}

//DatabaseConnect Unit Tests Function
//Objectives: Will run all the tests to be made for unit testing databaseConnect.cpp
//Prereqs: None
//Postreq: None
//Notes: None
void databaseConnectionUnitTests()
{
	int testNumber = 1;
	int* testPriorityList = NULL;
	int actualPriorityList[6];
	
	//TEST sortList
	cout << "TESTING SORTLIST FUNCTION:\n";
	//TEST 1
	testPriorityList = new int[5] {120,35,15,5,0};
	actualPriorityList[0] = 0;
	actualPriorityList[1] = 1;
	actualPriorityList[2] = 2;
	actualPriorityList[3] = 3;
	actualPriorityList[4] = 4;
	sortList(testPriorityList, 5);
	printRunCase(testNumber, compareTestCase(testPriorityList, actualPriorityList, 5));
	delete[] testPriorityList;
	testNumber++;

	//TEST 2
	testPriorityList = new int[5] {-120,-99,-35,-45,-10};
	actualPriorityList[0] = 4;
	actualPriorityList[1] = 2;
	actualPriorityList[2] = 3;
	actualPriorityList[3] = 1;
	actualPriorityList[4] = 0;
	sortList(testPriorityList, 5);
	printRunCase(testNumber, compareTestCase(testPriorityList, actualPriorityList, 5));
	delete[] testPriorityList;
	testNumber++;

	//TEST 3
	testPriorityList = new int[5] {0,0,0,0,0};
	actualPriorityList[0] = 0;
	actualPriorityList[1] = 1;
	actualPriorityList[2] = 2;
	actualPriorityList[3] = 3;
	actualPriorityList[4] = 4;
	sortList(testPriorityList, 5);
	printRunCase(testNumber, compareTestCase(testPriorityList, actualPriorityList, 5));
	delete[] testPriorityList;
	testNumber++;

	//TEST 4
	testPriorityList = new int[5] {25, 130, 25, 130, 25};
	actualPriorityList[0] = 1;
	actualPriorityList[1] = 3;
	actualPriorityList[2] = 0;
	actualPriorityList[3] = 2;
	actualPriorityList[4] = 4;
	sortList(testPriorityList, 5);
	printRunCase(testNumber, compareTestCase(testPriorityList, actualPriorityList, 5));
	delete[] testPriorityList;
	testNumber++;

	//TEST 5
	testPriorityList = new int[5] {11542,32445,78994,10002,96874};
	actualPriorityList[0] = 4;
	actualPriorityList[1] = 2;
	actualPriorityList[2] = 1;
	actualPriorityList[3] = 0;
	actualPriorityList[4] = 3;
	sortList(testPriorityList, 5);
	printRunCase(testNumber, compareTestCase(testPriorityList, actualPriorityList, 5));
	delete[] testPriorityList;
	testNumber++;

	//TEST organizeItems
	testNumber = 1;
	cout << endl << "TESING ORGANIZEITEMS FUNCTION\n";

	//TEST 1
	organizeItems("TestInputFiles/Test1/Database Files/output.csv", "TestInputFiles/Test1/HTMLFiles/scp_main_page.html", &testPriorityList);
	actualPriorityList[0] = 0;
	actualPriorityList[1] = 1;
	actualPriorityList[2] = 2;
	actualPriorityList[3] = 3;
	actualPriorityList[4] = 4;
	actualPriorityList[5] = 5;
	printRunCase(testNumber, compareTestCase(testPriorityList, actualPriorityList, 6));
	delete[] testPriorityList;
	testNumber++;

	//TEST 2
	organizeItems("TestInputFiles/Test2/Database Files/output.csv", "TestInputFiles/Test2/HTMLFiles/scp_main_page.html", &testPriorityList);
	actualPriorityList[0] = 0;
	actualPriorityList[1] = 1;
	actualPriorityList[2] = 2;
	actualPriorityList[3] = 3;
	actualPriorityList[4] = 4;
	actualPriorityList[5] = 5;
	printRunCase(testNumber, compareTestCase(testPriorityList, actualPriorityList, 6));
	delete[] testPriorityList;
	testNumber++;

	//TEST 3
	organizeItems("TestInputFiles/Test3/Database Files/output.csv", "TestInputFiles/Test3/HTMLFiles/scp_main_page.html", &testPriorityList);
	actualPriorityList[0] = 0;
	actualPriorityList[1] = 1;
	actualPriorityList[2] = 2;
	actualPriorityList[3] = 3;
	actualPriorityList[4] = 4;
	actualPriorityList[5] = 5;
	printRunCase(testNumber, compareTestCase(testPriorityList, actualPriorityList, 6));
	testNumber++;

	//TEST 4
	organizeItems("TestInputFiles/Test4/Database Files/output.csv", "TestInputFiles/Test4/HTMLFiles/scp_main_page.html", &testPriorityList);
	actualPriorityList[0] = 0;
	actualPriorityList[1] = 1;
	actualPriorityList[2] = 2;
	actualPriorityList[3] = 3;
	actualPriorityList[4] = 4;
	actualPriorityList[5] = 5;
	printRunCase(testNumber, compareTestCase(testPriorityList, actualPriorityList, 6));
	testNumber++;

	//TEST 5
	organizeItems("TestInputFiles/Test5/Database Files/output.csv", "TestInputFiles/Test5/HTMLFiles/scp_main_page.html", &testPriorityList);
	actualPriorityList[0] = 0;
	actualPriorityList[1] = 1;
	actualPriorityList[2] = 2;
	actualPriorityList[3] = 3;
	actualPriorityList[4] = 4;
	actualPriorityList[5] = 5;
	printRunCase(testNumber, compareTestCase(testPriorityList, actualPriorityList, 6));
	delete[] testPriorityList;
	testNumber++;
}

//TEST Main Function
//Objectives: Will manage when the program will run
//Prereqs: None
//Postreq: HTML files are changed and compared to the expected output
//Notes: ONLY USED FOR TEST CASES!!!!
int main()
{
	//Run all test cases
	databaseConnectionUnitTests();

	//Return successful run
	return 0;
}
