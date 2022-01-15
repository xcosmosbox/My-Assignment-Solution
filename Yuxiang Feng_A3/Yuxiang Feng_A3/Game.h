
#ifndef GAME_H
#define GAME_H

#include<string>
#include<sstream>
#include"Dice.h"
#include"Player.h"
#include"MyEnum.h"
#include"AskForAny_FileStream.h"

class Game
{
private:
	vector<Player>* players;//pointer of players
	Dice* dice;//pointer of dice
	bool endFlag;//Change this variable to determine when the program ends the loop
	int nowPlayer;//Store the subscript of the player at this time
	ProcessOperatorEnumType process;//The operation process enumeration class can switch the programs in the loop differently by changing the value of this variable
	const string ASCII_ART_FARKLE_GAME_NAME_FILE_ADDR = "FARKLE.txt";//Game name for ASCII art
	const string GAME_RULE_FILE_ADDR = "Rule.txt";//Game rule


	void setPlayers(vector<Player>* pPlayer);//It is only used for syntax identification.
	void setDice(Dice* pDice);//It is only used for syntax identification.
	void setEndFlag(bool flag);//It is only used for syntax identification.
	void setNowPlayer(int index);//It is only used for syntax identification.
	void setProcess(ProcessOperatorEnumType process);//It is only used for syntax identification.
	string operator<<(array<string, 8>& myDiceImage);//Operator overloading. Only as a demonstration of advanced functions.


public:
	Game(vector<Player>* players, Dice* dice);//Constructor
	~Game();//Deconstruction


	vector<Player>* getPlayers(); //Get the pointer that stores all players
	Dice* getDice();//Get the pointer that stores dice object
	bool getEndFlag();//Get end identifier
	int getNowPlayer();//Get the subscript of the current player

	void start();//The game begins here
	void locking();//Function for locking dice
	int randomStartPlayer();//It is used to randomly select a player as the first player at the beginning of the game
	bool quit(string str);//The user's input determines whether to really quit the game
	void checkGameOver();//Detect whether there is a winner in the game
	void gameOver();//End the game

	void changePlayer();//When the previous player saves scores or encounters falkle, the playing power will be transferred to the next player
	void displayDice();//The dice constructed by ASCII art are displayed.
	void displayInfo();//Format and output some game information
	ProcessOperatorEnumType getProcess() const;//Get the process information at this time

	char inputCheck(string question);//Contains the input program for the detection rule

};


#endif // !GAME_H



