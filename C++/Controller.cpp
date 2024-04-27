//Import Libraries
#include "Controller.h"

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

bool databaseExecute(int** priorityList, string locationOfFolders)
{
	//Initalize Variables
	return organizeItems(locationOfFolders + "Database Files/mysql_ac_nau_edu_3306.csv", locationOfFolders + "HTMLFiles/scp_main_page.html", priorityList);
}

void setup()
{
	//Startup/setup
	system("setup.bat> NUL");
}

void pushToGit()
{
	system("updateWebsite.bat > NUL");
}

bool run()
{
	//Initialize Variables
	int* priorityList = NULL;

	//Run setup
	setup();

	if (!databaseExecute(&priorityList, ""))
	{
		return false;
	}

	if (!HTMLChangeExecute(priorityList, ""))
	{
		return false;
	}

	//pushToGit();

	delete[] priorityList;

	return true;
}

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
