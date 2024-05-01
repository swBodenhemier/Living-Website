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

		//Check if file is empty
		if (HTMLFile->get() == EOF)
		{
			throw runtime_error("Error: file is empty.");
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

//Find Navigation Line Function
//Objectives: The code will search through the HTML code and find what line the <nav> is located on.
//Prereqs: All code has been sorted into an array divided by lines, and max lines is the max amount of
//		   lines inside code array.
//Postreq: Returns an int that shows the line location of <nav>
//Notes: None
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

//Find maxOptions Function
//Objectives: The code will search through the HTML code and find all the total amount of navigation
//			   bar options.
//Prereqs: All code has been sorted into an array divided by lines, and start represents the location of
//		   <nav> and end is the max lines in code array.
//Postreq: Returns an int of the total amount of navigaiton bar options
//Notes: None
int findMaxNavOptions(string code[], int start, int end)
{
	//Initialize Variables
	int currentLine = start + 1;
	int count = 0;

	//Find how many <a... there are until </nav> is reached
	while (code[currentLine].find("</nav>") == string::npos && currentLine < end)
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

//Set Item Spots Nav Options Function
//Objectives: The code will search through the HTML code and will set itemSpots array with tthe line
//			  location of each navigation option inside it.
//Prereqs: All code has been sorted into an array divided by lines, and start represents the location of
//		   <nav> and end is the max lines in code array, itemSpots array is initalized and maxOptions is
//		   set to the max amount of naviagation options
//Postreq: Returns an int of the number of options it successfully set and itemSpots is set to each line
//		   location of each option
//Notes: None
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

//Set Item Spots Nav Options Function
//Objectives: The code will search through the HTML code and will set itemSpots array with the line
//			  location of each navigation option inside it.
//Prereqs: All code has been sorted into an array divided by lines, and start represents the location of
//		   <nav> and end is the max lines in code array, itemSpots array is initalized and maxOptions is
//		   set to the max amount of naviagation options, navoptions array has been filled in
//Postreq: Returns an int of the number of options it successfully set and itemSpots is set to each line
//		   location of each option
//Notes: None
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

//Fill navOptions Function
//Objectives: The code will search through the HTML code and will fill in navOptions with the name of
//			  each navigation option available.
//Prereqs: All code has been sorted into an array divided by lines, itemSpots array is filled in, navOptions
//		   is initialized and maxOptions is set to the max amount of naviagation options.
//Postreq: Fills in the navOptions array
//Notes: None
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

//Fill navLinks Function
//Objectives: The code will search through the HTML code and will fill in navLinks with the link of
//			  each navigation option available.
//Prereqs: All code has been sorted into an array divided by lines, itemSpots array is filled in, navlinks
//		   is initialized and maxOptions is set to the max amount of naviagation options.
//Postreq: Fills in the navLinks array
//Notes: None
void fillNavLinks(string code[], int itemSpots[], string* navLinks, int maxOptions)
{
	//Initialize Variables
	int currentItem = 0, charStart = 0, charEnd = 0, repeatCount = 0;

	//Fill in the links of each nav option into navLinks
	while (currentItem < maxOptions)
	{
		//Find location of 2nd =
		while (repeatCount != 2)
		{
			charStart = code[itemSpots[currentItem]].find("=", charStart + 1);
			repeatCount++;
		}

		repeatCount = 0;

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

//Change Link Names Function
//Objectives: The code will search through the HTML code and will change the code array to reflect the priority
//			  list.
//Prereqs: All code has been sorted into an array divided by lines, itemSpots array is filled in, priorityList
//		   navOptions is filled in is filled in with link names and maxOptions is set to the max amount of
//		   naviagation options.
//Postreq: Adjust the code array to reflect the priorityList array's order
//Notes: None
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

//Change links Function
//Objectives: The code will search through the HTML code and will change the code array to reflect the priority
//			  list.
//Prereqs: All code has been sorted into an array divided by lines, itemSpots array is filled in, priorityList
//		   navLinks is filled in is filled in with links and maxOptions is set to the max amount of
//		   naviagation options.
//Postreq: Adjust the code array to reflect the priorityList array's order
//Notes: None
void changeLinks(string* code, int itemSpots[], int priorityList[], string navLinks[], int maxOptions)
{
	//Initiliaze Variables
	int currentItem = 0, charSpot = 0, repeatCount = 0;

	//Change the links
	while (currentItem < maxOptions)
	{
		//Find start 2nd =
		while (repeatCount != 2)
		{
			charSpot = code[itemSpots[currentItem]].find('=', charSpot + 1);
			repeatCount++;
		}

		repeatCount = 0;

		//Check if failed to find '='
		if (charSpot == -1)
		{
			//Find locaiton of "link"
			charSpot = code[itemSpots[currentItem]].find("link");
			code[itemSpots[currentItem]].replace(charSpot, 4, "link=");
			charSpot += 4;
		}

		//Replace link in string
		code[itemSpots[currentItem]].replace(charSpot + 1, navLinks[currentItem].length(), navLinks[priorityList[currentItem]]);

		//Reset Start
		charSpot = 0;

		//Increase currentItem
		currentItem += 1;
	}
}

//Copy to New HTML File Function
//Objectives: The code will copy each line in code array to a new string in a different file location
//Prereqs: All code has been adjusted into an array divided by lines, fileLocation has the location of
//		   the new file, fileName is the new file name, end represent the max lines in the code array.
//Postreq: Copies all of code array into new file and returns true or false if fails.
//Notes: None
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