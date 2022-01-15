#ifndef ASKFORANYANDFILESTREAM_H
#define ASKFORANYANDFILESTREAM_H

#include<fstream>
#include<string>
#include<iostream>
#include<vector>

using namespace std;

void readFile(string fileName);
void writeFile(string fileName, string result);

string askForName(string question);
int askForNumber(string question, int low, int high);
int askForNumber(string question);
char askForLetter(string question);

vector<int> askForLockDice(string question); //Ask the user the location of the dice you want to lock.

#endif // !ASKFORANYANDFILESTREAM_H
