//Import Header
#include "HTMLChange.h"

using namespace std;

//Change Navigation Bar Function
//Objectives: The html file will be opened if not already, and will check each element of the navigation
//			  bar and change it to the required item in the priority list.
//Prereqs: The priority list is different than the current list in the html file. Priority list has a
//         reference to only one of each item entity in navOptions.
//Postreq: The html file navigation code has been adjusted to reflect the updated priority list
//Notes: itemSpots refers to the same spots in navOptions. For example both [0] indecies are refering to
//       "Class: Safe" location. priorityList will keep track of the list of items in the order that they
//       should come out. For example if the list looks like {5, 4, 3, 2, 1, 0} then the order will be
//		 "Series: III", "Series II", "Series: I", etc.
bool changeNavBar(fstream* HTMLFile, int priorityList[], string newFileLocation, string fileName)
{
	//Initialize Variables
	int maxCodeLines = 500, navSpot = -1, numLines = 0, count, maxNavOptions, * itemSpots;
	string* ReplacementCode = new string[maxCodeLines], * navOptions, * navLinks;

	//Check if stream is open
	try {
		if (!HTMLFile->is_open())
		{
			//return fail
			throw runtime_error("Error: file failed to open.");
		}
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		delete[] ReplacementCode;
		return false;
	}

	//Copy entire stream into buffer line by line
	while (HTMLFile->peek() != EOF)
	{
		//Store line into buffer
		getline(*HTMLFile, ReplacementCode[numLines]);

		//Increase number of lines by 1
		numLines += 1;
	}

	//Find where <nav> is located at
	try
	{
		navSpot = findNavLine(ReplacementCode, numLines);
		//Check if failed to find
		if (navSpot == -1)
		{
			//Throw error
			throw runtime_error("Error: Failed to find <nav>");
		}
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		delete[] ReplacementCode;
		return false;
	}


	//Find number of links in file
	maxNavOptions = findMaxNavOptions(ReplacementCode, navSpot, numLines);

	//Create variables based on how many navigation options there are
	navOptions = new string[maxNavOptions];
	navLinks = new string[maxNavOptions];
	itemSpots = new int[maxNavOptions];

	//Find each line a navigation option is in
	try
	{
		if (setItemSpotsForNavOptions(ReplacementCode, itemSpots, navSpot, numLines, maxNavOptions) < maxNavOptions)
		{
			//Throw error
			throw runtime_error("Error: Failed to find all navigation options");

		}

		//Fill in navOptions with names of the links
		fillNavOptions(ReplacementCode, itemSpots, navOptions, maxNavOptions);

		//Fill in navLinks with links of each navigation option
		fillNavLinks(ReplacementCode, itemSpots, navLinks, maxNavOptions);

		//Fill in itemSpots will all item line locations and check for all items filled
		if (setItemSpotsForNames(ReplacementCode, &itemSpots[0], navOptions, navSpot, numLines, maxNavOptions) < maxNavOptions)
		{
			//Throw error
			throw runtime_error("Error: Failed to find all Navigation items");
		}

		//Change names of items based on the priorityList
		changeLinkNames(ReplacementCode, itemSpots, priorityList, navOptions, maxNavOptions);

		//Fill in itemSpots with all link line locations and check for all items filled
		if (setItemSpotsForLinks(ReplacementCode, &itemSpots[0], navLinks, navSpot, numLines, maxNavOptions) < maxNavOptions)
		{
			//Print error statement and return error
			throw runtime_error("Error: Failed to find all Link items");
		}
	
		//Change links of items based on the priorityList
		changeLinks(ReplacementCode, itemSpots, priorityList, navOptions, maxNavOptions);
	
		//Apply changes to new HTML Document
		if (!copyToNewHTML(ReplacementCode, newFileLocation, fileName, numLines))
		{
			//Print error statement
			throw runtime_error("Error: Failed to create " + fileName + " in " + newFileLocation);
		}
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		delete[] ReplacementCode;
		delete[] navOptions;
		delete[] navLinks;
		delete[] itemSpots;
		return false;
	}
	

	//Clear data
	delete[] ReplacementCode;
	delete[] navOptions;
	delete[] navLinks;
	delete[] itemSpots;
	
	return true;
}

int findNavLine(string code[], int maxLines)
{
	//Initliaze Variables
	int linePosition = 0;
	bool notFound = true;

	//Find what line <nav> is on
	while (linePosition < maxLines && notFound)
	{
		//Check if <nav> is in the current line
		if (code[linePosition].find("<nav>") != string::npos)
		{
			notFound = false;
		}
		//Increase by 1 and loop
		else
		{
			linePosition += 1;
		}
	}

	//Check if found
	if (notFound)
	{
		//return -1 if not found
		return -1;
	}

	return linePosition;
}

int findMaxNavOptions(string code[], int start, int end)
{
	//Initialize Variables
	int currentLine = start + 1;
	int count = 0;

	//Find how many <a... there are until </nav> is reached
	while (code[currentLine].find("</nav>") == string::npos)
	{
		//Check if <a is located on this line
		if (code[currentLine].find("<a") != string::npos)
		{
			//Increase count
			count += 1;
		}

		//Increase currentLine
		currentLine += 1;
	}

return count;
}

int setItemSpotsForNavOptions(string code[], int* itemSpots, int start, int end, int maxOptions)
{
	//Initialize Variables
	int itemLocation = start, count = 0;

	//Find item spots and fill in array
	while (count < maxOptions && itemLocation < end)
	{
		//Find each item spot
		if (code[itemLocation].find("<a") != string::npos)
		{
			itemSpots[count] = itemLocation;

			//Increase count
			count += 1;
		}

		//Increase itemLocation and loop
		itemLocation += 1;
	}

	return count;
}

int setItemSpotsForNames(string code[], int* itemSpots, string navOptions[], int start, int end, int maxOptions)
{
	//Initialize Variables
	int itemLocation = start, currentItem = 0;

	//Find item spots and fill in array
	while (currentItem < maxOptions && itemLocation < end)
	{
		//Find each item spot
		if (code[itemLocation].find(navOptions[currentItem]) != string::npos)
		{
			//Set itemSpots
			itemSpots[currentItem] = itemLocation;

			//reset itemLocation
			itemLocation = start;

			//Increase currentItem
			currentItem += 1;
		}
		//Increase by 1 and loop
		else
		{
			itemLocation += 1;
		}
	}

	return currentItem;
}

int setItemSpotsForLinks(string code[], int* itemSpots, string navLinks[], int start, int end, int maxOpions)
{
	//Initliaize Variables
	int currentItem = 0, itemLocaiton = start;

	//Change the links
	//Loop through buffer finding each spot for the links
	while (currentItem < maxOpions && itemLocaiton < end)
	{
		//Check for link in line
		if (code[itemLocaiton].find(navLinks[currentItem]) != string::npos)
		{
			//Set itemSpots to current location
			itemSpots[currentItem] = itemLocaiton;

			//Reset itemLocation
			itemLocaiton = start;

			//Increase currentItem
			currentItem += 1;
		}
		//Increase by 1 and loop
		else
		{
			itemLocaiton += 1;
		}
	}

	return currentItem;
}

void fillNavOptions(string code[], int itemSpots[], string* navOptions, int maxOptions)
{
	//Initialize Variables
	int currentItem = 0, repeatCount = 0, charStart = 0, charEnd = 0;

	//Fill in the names of each nav option into navOptions
	while (currentItem < maxOptions)
	{
		//Find the beginning of the name
		//Find 2nd instance of >
		while(repeatCount != 2)
		{
			charStart = code[itemSpots[currentItem]].find('>', charStart + 1);
			repeatCount += 1;
		}

		//Reset repeatCount
		repeatCount = 0;

		//Find charEnd
		charEnd = code[itemSpots[currentItem]].find('<', charStart + 1);

		//Set name into navOptions
		navOptions[currentItem] = code[itemSpots[currentItem]].substr(charStart + 1, charEnd - charStart - 1);

		//Reset variables
		charStart = 0;
		charEnd = 0;

		//Increase currentItem
		currentItem += 1;
	}
}

void fillNavLinks(string code[], int itemSpots[], string* navLinks, int maxOptions)
{
	//Initialize Variables
	int currentItem = 0, charStart = 0, charEnd = 0;

	//Fill in the links of each nav option into navLinks
	while (currentItem < maxOptions)
	{
		//Find location of href
		charStart = code[itemSpots[currentItem]].find("href");

		//Find location of first "
		charStart = code[itemSpots[currentItem]].find("\"", charStart);

		//Find end of link
		charEnd = code[itemSpots[currentItem]].find("\"", charStart + 1);

		//Set link into navLinks
		navLinks[currentItem] = code[itemSpots[currentItem]].substr(charStart + 1, charEnd - charStart - 1);

		//Reset variables
		charStart = 0;
		charEnd = 0;

		//Increase currentItem
		currentItem += 1;
	}
}

void changeLinkNames(string* code, int itemSpots[], int priorityList[], string navOptions[], int maxOptions)
{
	//Initialize Variables
	int currentItem = 0, repeatCount = 0, charSpot = 0;

	//Change the names of each link
	while (currentItem < maxOptions)
	{
		//Find start
		//Find the 2nd instance of >
		while (repeatCount != 2)
		{
			charSpot = code[itemSpots[currentItem]].find('>', charSpot + 1);
			repeatCount += 1;
		}

		//Reset count
		repeatCount = 0;

		//Replace name in string
		code[itemSpots[currentItem]].replace(charSpot + 1, navOptions[currentItem].length(), navOptions[priorityList[currentItem]]); //ERROR IN THIS LINE

		//Reset Start
		charSpot = 0;

		//Increase currentItem
		currentItem += 1;
	}
}

void changeLinks(string* code, int itemSpots[], int priorityList[], string navLinks[], int maxOptions)
{
	//Initiliaze Variables
	int currentItem = 0, charSpot = 0;

	//Change the links
	while (currentItem < maxOptions)
	{
		//Find start
		charSpot = code[itemSpots[currentItem]].find("href=", charSpot + 1) + 6;

		//Replace link in string
		code[itemSpots[currentItem]].replace(charSpot, navLinks[currentItem].length(), navLinks[priorityList[currentItem]]);

		//Reset Start
		charSpot = 0;

		//Increase currentItem
		currentItem += 1;
	}
}

bool copyToNewHTML(string code[], string fileLocation, string fileName, int end)
{
	//Initialize Variables
	ofstream newHTML = ofstream();
	int lineCount;

	//Create new HTML document
	newHTML.open(fileLocation + fileName);

	//Check if new document has been opened
	if (newHTML.is_open())
	{
		//Write each line to document
		for (lineCount = 0; lineCount < end; lineCount++)
		{
			newHTML << code[lineCount] << endl;
		}

		//Close file
		newHTML.close();

		return true;
	}
	
	return false;
}