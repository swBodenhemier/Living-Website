//Import header
#include "databaseConnection.h"

using namespace std;

//Organize Items Function
//Objectives: The code will search through the database csv file and return the priorityList all filled in
//Prereqs: Database files are in the correct locaiton and contain data, priorityList is initialized to NULL
//		   and HTML files are in the folder and contain code.
//Postreq: Fills in the priorityList in order of wight based on the database file and returns true or false
//		   if fails.
//Notes: None
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

//Find Max Items Function
//Objectives: The code will search through the database file and find how many lines there are to see how
//			  many items will be contained in the file.
//Postreq: returns number of items inside the csv file.
//Notes: None
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

//Find Navigation Function
//Objectives: Finds the locaiton of the <nav> in the HTML file
//Prereqs: Html file is filled in and accessable.
//Postreq: Return true or false if fails to find <nav>
//Notes: None
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

//Get Item names Function
//Objectives: Locates the next item name in order of the HTML code and returns it
//Prereqs: Html file is filled in and accessable.
//Postreq: Return the name of the next name of the navigation links
//Notes: This will loop through in the order that the code is written and will store
//		 all the strings into the respective spots, for example: if SCP-999 is first
//		 then it will be stored in position 0 in the array
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

//Get Weight of Each Name Function
//Objectives: Finds the weight of each item in the order it is recieved
//Prereqs: Database file is accessable and itemName is the same name as an item in
//		   both the database and the HTML file.
//Postreq: return the number retrieved from the database
//Notes: None
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

//Sort List Function
//Objectives: Will take an array of weights and then sort the weight of each associated
//			  item in the database to a numbered order.
//Prereqs: List is filled with the weights of each database item in the order it reads in the HTML
//		   file and the end represents the size of the list array.
//Postreq: List is filled in with the new order of the HTML names/links
//Notes: This will take an array of wieghts like {102, 3, 54} and organize it into a numbered list where
//		 the new location will be for each object associated with it. In this example the output would be
//		 {0, 2, 1}.
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