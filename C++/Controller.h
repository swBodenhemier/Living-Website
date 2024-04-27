#pragma once
#ifndef CONTROLLER_H
#include "HTMLChange.h"
#include "databaseConnection.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Forward declare functions
bool HTMLChangeExecute(int* priorityList, string locationOfFolders);
bool databaseExecute(int** priorityList, string locationOfFolders);
void setup();
void pushToGit();
bool run();
bool runTests(string locationOfFolders);

#endif // !CONTROLLER_H
