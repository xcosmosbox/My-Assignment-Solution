#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<iostream>
#include"MyEnum.h"
using namespace std;

class Player
{
private:
	static int playerID;//Static variable, used to set the player's ID
	string playerName;
	int playerScore = 0;//Total score obtained by the player at this time
	int farkleCount = 0;//Number of Farkle encounters
	int ID = -1;//The default ID of the player will be changed in the constructor, and the changed value is the unique identification, because after each change, the static variable will change its own value.
	PlayerAttributeEnumType playerAttribute;//Used to distinguish between human and AI
	AIEnumType AI_Character;//AI's character

	void setID(int ID);//It is only used for syntax identification.
	void setPlayerName(string name);//It is only used for syntax identification.
	void setPlayerScore(int score);//It is only used for syntax identification.
	void setFarkleCount(int number);//It is only used for syntax identification.
	void setPlayerAttribute(PlayerAttributeEnumType playerAttribute);//It is only used for syntax identification.
	void setAIEnumType(AIEnumType AI_Character);//It is only used for syntax identification.

public:
	Player(string name, PlayerAttributeEnumType playerAttribute);//Constructor for human use
	Player(string name, PlayerAttributeEnumType playerAttribute, AIEnumType AI_Character);////Constructor for AI use
	~Player();

	string getPlayerName() const;//Get player's name

	int getPlayerScore() const;//Get player's total score
	void updatePlayerScore(int score);//Update player's total score
	void subtPlayerScore(int score);//When the player encounters three farkles, subtract part of the player's score
	void resetPlayerScore();//Get player's total score

	int getFarkleCount() const;//Get count of Farkle
	void updateFarkleCount();//Update count of Farkle
	void refreshFarkleCount();//refresh count of Farkle when player meet punishment

	int getID() const;//Get unique ID

	PlayerAttributeEnumType getPlayerAttribute() const;//Get player attribute
	AIEnumType getAIEnumType() const;//Get the AI's character

};


#endif // !PLAYER_H


