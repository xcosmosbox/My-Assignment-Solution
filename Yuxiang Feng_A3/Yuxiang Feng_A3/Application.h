
#ifndef APPLICATION_H
#define APPLICATION_H

#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<ctime>
#include"Dice.h"
#include"Game.h"
#include"Player.h"
#include"MyEnum.h"
#include"AskForAny_FileStream.h"

 //Variable
const string ASCII_ART_FARKLE_GAME_NAME_FILE_ADDR = "FARKLE.txt"; //Game name for ASCII art
const string GAME_ABOUT_INFO_FILE_ADDR = "Info.txt"; //Game information
const string GAME_MENU_FILE_ADDR = "Menu.txt"; //Game menu 
const string GAME_EXAMPLE_FILE_ADDR = "Example.txt"; //Game example
const string GAME_RULE_FILE_ADDR = "Rule.txt";//Game rule
const string GAME_SETTING_FILE_ADDR = "Setting.txt";//Setting the default AI character
const string SET_SKILL_LEVEL_FILE_ADDR = "SetSkillLevel.txt";//Setting skill level
const string SAY_BYE_FILE_ADDR = "SayBye.txt";//Say bye
AIEnumType defaultAI = AIEnumType::COWARD;//Default AI character

//Function
vector<Player> addPlayers(); //The user selects the number of players to create.
Dice addDice(); //Create the dice object

void playGame();

void runMenu(); //Print the all menu
void displayInfo(); //Display the information
void displayMenu(); //Display the menu
void help(int number); //Display the "help" information
void displayExample(); //Display the game example
void displayRule(); //Display the game rule
void settingDefaultAI(); //Setting the AI character

#endif // !APPLICATION_H






