#pragma once
#ifndef HTMLCHANGE_H
#define HTMLCHANGE_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//Forward Declare Functions
bool changeNavBar(fstream *HTMLFile, int priorityList[], string newFileLocation, string fileName);
int findNavLine(string code[], int maxLines);
int findMaxNavOptions(string code[], int start, int end);
int setItemSpotsForNavOptions(string code[], int* itemSpots, int start, int end, int maxOptions);
int setItemSpotsForNames(string code[], int* itemSpots, string navOptions[], int start, int end, int maxOptions);
void fillNavOptions(string code[], int itemSpots[], string* navOptions, int maxOptions);
void fillNavLinks(string code[], int itemSpots[], string* navLinks, int maxOptions);
void changeLinkNames(string* code, int itemSpots[], int priorityList[], string navOptions[], int maxOptions);
void changeLinks(string* code, int itemSpots[], int priorityList[], string navLinks[], int maxOptions);
bool copyToNewHTML(string code[], string fileLocation, string fileName, int end);

#endif