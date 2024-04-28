//Import header
#include "databaseConnection.h"

using namespace std;

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
		if (!databaseFile.is_open())
		{
			//Print error statement and return false
			throw runtime_error("Error: file failed to open at location \"" + fileLocation + "\"");
		}
		else if (!HTMLFile.is_open())
		{
			//Print error statement and return false
			throw runtime_error("Error: file failed to open at location \"" + HTMLFileLocation + "\"");
		}

		//Check for empty file
		if (databaseFile.get() == EOF)
		{
			throw runtime_error("Error: Empty file at location \"" + fileLocation + "\"");
		}
		else if (HTMLFile.get() == EOF)
		{
			throw runtime_error("Error: Empty file at location \"" + HTMLFileLocation + "\"");
		}

		maxItems = findMaxItems(&databaseFile, &databaseInfo);
		if (maxItems == -1)
		{
			throw runtime_error("Error: Failed to get total items.");
		}
	
		updateList = new int[maxItems];

		//Loop until each item in priorityList is filled
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
	int repeat = 0, beginning = 0, end, repeatCount = 0;
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
	while (repeatCount != 2)
	{
		beginning = line.find(">", beginning + 1);
		repeatCount++;
	}

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
	weight = databaseInfo.find(',', weight);
	end = databaseInfo.find('\n', weight);
	temp = databaseInfo.substr(weight + 1, end - weight - 1);
	buffer << temp;
	buffer >> weight;

	return weight;
}

void sortList(int* list, int end)
{
	//Initialize Variables
	int count, compare, weight = 0, loop;
	int* newList = new int[end] {0};
	bool* weightAssigned = new bool[end] { false };

	//Loop through the list from beginning to end
	for (count = 0; count < end; count++)
	{

		//Inner loop to compare the value to the rest of the items
		for (compare = 0; compare < end; compare++)
		{
			//Check if compare and count not the same and if value at count is smaller than compare
			 if (list[count] < list[compare] || (list[count] == list[compare] && count > compare))
			 {
				 weight++;
			 }
		}

		while (weightAssigned[weight])
		{
			weight++;
		}

		newList[weight] = count;
		weightAssigned[weight] = true;

		//Reset weight based on where the loop is
		weight = 0;
	}
	
	//Deep copy list
	for (count = 0; count < end; count++)
	{
		list[count] = newList[count];
	}

	delete[] newList;
	delete[]weightAssigned;
}