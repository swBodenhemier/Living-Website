#pragma once
#ifndef DATABASECONNECTION_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//Forward declare functions
bool organizeItems(string fileLocation, string HTMLFileLocation, int** priorityList);
int findMaxItems(ifstream* databaseFile, string* databaseInfo);
bool findNav(istream* HTMLFile);
string getItemName(istream* HTMLFile);
int getWeightOfName(string databaseInfo, string itemName);
void sortList(int* list, int end);

#endif // !DATABASECONNECTION_H
