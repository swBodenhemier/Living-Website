//Import header
#include "databaseConnection.h"

using namespace std;


bool downloadItems(string fileLoaction)
{
	return false;
}

bool organizeItems(string fileLocation, string HTMLFileLocation, int** priorityList)
{
	//Initialize Variables
	int currentItem = 0, maxItems = -1, *updateList;
	string nameOfItem, databaseInfo;
	ifstream databaseFile, HTMLFile;

	try
	{
		//Open HTML file
		HTMLFile.open(HTMLFileLocation);

		//Open databaseFile
		databaseFile.open(fileLocation);

		//Check if each file is open
		if (!HTMLFile.is_open() || !databaseFile.is_open())
		{
			//Print error statement and return false
			throw runtime_error("Error: file failed to open at location " + fileLocation + HTMLFileLocation + ".");
		}
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return false;
	}

	maxItems = findMaxItems(&databaseFile, &databaseInfo);
	updateList = new int[maxItems];

	//Loop until each item in priorityList is filled
	try
	{
		if (!findNav(&HTMLFile))
		{
			//Print error statement and return false
			throw runtime_error("Error: Failed to find <nav>.");
		}
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return false;
	}

	while (currentItem < maxItems)
	{
		//Grab the navigation name of next navigation item
		nameOfItem = getItemName(&HTMLFile);
		updateList[currentItem] = getWeightOfName(databaseInfo, nameOfItem);

		currentItem += 1;
	}

	//Sort the list based on its weight
	sortList(updateList, maxItems);

	*priorityList = updateList;

	return true;
}

int findMaxItems(ifstream* databaseFile, string* databaseInfo)
{
	//Initialize Variables
	int count = -1; //-1 to skip the first line of the CSV file
	string temp;

	while (databaseFile->peek() != EOF)
	{
		//Get next line and increase count
		getline(*databaseFile, temp);
		count += 1;

		//Set data from temp into databaseInfo
		*databaseInfo += "\n" + temp;
	}

	return count;
}

bool findNav(istream* HTMLFile)
{
	//Initialize Variables
	int repeat = 0;
	string line;

	//Find <nav>
	getline(*HTMLFile, line);
	while (line.find("<nav>") == string::npos && HTMLFile->peek() != EOF)
	{
		//Copy current HTML line to line
		getline(*HTMLFile, line);
	}

	//Check for error
	if (line == "</html>" || line == "")
	{
		return false;
	}

	return true;
}

string getItemName(istream* HTMLFile)
{
	//Initialize Variables
	int repeat = 0, beginning, end;
	string line;

	//Find first instance of <a
	getline(*HTMLFile, line);
	while (line.find("<a") == string::npos && HTMLFile->peek() != EOF)
	{
		//Copy current HTML line to line
		getline(*HTMLFile, line);
	}

	//Find and copy name of link
	//Find beginning
	beginning = line.find("<a");
	beginning = line.find('>', beginning);

	//Find end
	end = line.find('<', beginning);

	//Copy subsrting into line
	line = line.substr(beginning + 1, end - beginning - 1);

	return line;
}

int getWeightOfName(string databaseInfo, string itemName)
{
	//Initialize Variables
	int weight, end;
	string temp;
	stringstream buffer;
	
	weight = databaseInfo.find(itemName);
	weight = databaseInfo.find('"', weight + itemName.length() + 1);
	end = databaseInfo.find('"', weight + 1);
	temp = databaseInfo.substr(weight + 1, end - weight - 1);
	buffer << temp;
	buffer >> weight;

	return weight;
}

void sortList(int* list, int end)
{
	//Initialize Variables
	int count, compare, weight = end - 1;
	int* newList = new int[end];

	//Loop through the list from beginning to end
	for (count = 0; count < end; count++)
	{
		//Inner loop to compare the value to the rest of the items
		for (compare = 0; compare < end; compare++)
		{
			//Check if compare and count not the same and if value at count is smaller than compare
			 if (count != compare && list[count] > list[compare])
			 {
				 weight -= 1;
			 }
		}

		//Set counts value to the weight
		newList[count] = weight;

		//Reset weight based on where the loop is
		weight = end - 1;
	}
	
	//Deep copy list
	for (count = 0; count < end; count++)
	{
		list[count] = newList[count];
	}

	delete[] newList;
}