//Import Libraries
#include "Controller.h"

//HTML Change Execute Function
//Objectives: Will create a new HTML file in the associated folders
//			  and change the new files according to the priorityList
//Prereqs: PriorityList properly filled in and locationOfFolders is
//		   accessable.
//Postreq: New HTML files will be created in the git repo and ready
//		   to be pushed to the git repo.
//Notes: None
bool HTMLChangeExecute(int* priorityList, string locationOfFolders)
{
	//Initalize Variables
	fstream HTMLFile = fstream();
	int count;
	string filesToOpen[7] = {"HTMLFiles/scp_main_page.html", "HTMLFiles/scp_081_page.html", "HTMLFiles/scp_999_page.html",
							"HTMLFiles/scp_1990_page.html", "HTMLFiles/scp_2006_page.html",  "HTMLFiles/scp_2161_page.html",
							"HTMLFiles/scp_8012_page.html"};

	//Loop until no more files
	for (count = 0; count < 7; count++)
	{
		try
		{
			HTMLFile.open(locationOfFolders + filesToOpen[count]);

			if (!HTMLFile.is_open())
			{
				throw runtime_error("Error: file failed to open at location \"" + locationOfFolders + filesToOpen[count] + "\"");
			}

			if (!changeNavBar(&HTMLFile, priorityList, locationOfFolders + "deployed_website", filesToOpen[count].substr(9, string::npos)))
			{
				HTMLFile.close();
				throw runtime_error("Run " + to_string(count) + " failed: " + locationOfFolders + filesToOpen[count]);
			}

			HTMLFile.close();
		}
		catch (runtime_error e)
		{
			cout << e.what() << endl;
		}
	}

	return true;
}

//Database Execute Function
//Objectives: Will create the priorityList based on the database
//Prereqs: The file location of the database file and HTML file is accessable
//Postreq: PriorityList is orgranized based on the locaiton of each item in the
//		   HTML file and the sorted by the wieghts of each item.
//Notes: Example of a possible input/output:
//	     Input from HTML file: {"SCP-999", "SCP-081", "SCP-2006"}
//		 Input from CSV file: {199, 32, 540}
//		 Output aka priorityList: {1, 2, 0}
bool databaseExecute(int** priorityList, string locationOfFolders)
{
	//Initalize Variables
	return organizeItems(locationOfFolders + "Database Files/output.csv", locationOfFolders + "HTMLFiles/scp_main_page.html", priorityList);
}

//Setup Function
//Objectives: Will run setup.bat and set up all required directories as well as
//			  download the git repo and all HTML files to change and download 
//			  the database csv
//Prereqs: None
//Postreq: All files are in the proper locations and directories are setup
//Notes: None
void setup()
{
	//Startup/setup
	system("setup.bat > NUL");
}

//Download Database Function
//Objectives: Will run downloadDatabase.bat and download the csv file
//Prereqs: The file location of the database file is accessable
//Postreq: Database files are downloaded to the correlated folder
//Notes: None
void downloadDB()
{
	system("downloadDatabase.bat > NUL");
}

//Push to Git Function
//Objectives: Will execute the updateWebsite.bat file
//Prereqs: The git repo exists HTML files have successfully been changed.
//Postreq: Git repo has created a new pull request with updates to the website.
//Notes: None
void pushToGit()
{
	system("updateWebsite.bat > NUL");
}

//Controller Runner Function
//Objectives: Will control how the program will be operated.
//Prereqs: None
//Postreq: Return true or false if fails to run
//Notes: None
bool run()
{
	//Initialize Variables
	int* priorityList = NULL;

	//Run setup
	setup();

	//Run database download


	if (!databaseExecute(&priorityList, ""))
	{
		return false;
	}

	if (!HTMLChangeExecute(priorityList, ""))
	{
		return false;
	}

	pushToGit();

	delete[] priorityList;

	return true;
}

//Test Controller Function
//Objectives: Will controll how the test will be operated
//Prereqs: The locationOfFolders points to where the test files are located.
//Postreq: Return true or false if fails to run or compare tests.
//Notes: None
bool runTests(string locationOfFolders)
{
	//Initialize Variables
	int* priorityList= NULL;

	if (!databaseExecute(&priorityList, locationOfFolders))
	{
		return false;
	}

	if (!HTMLChangeExecute(priorityList, locationOfFolders))
	{
		return false;
	}

	delete[] priorityList;

	return true;
}
