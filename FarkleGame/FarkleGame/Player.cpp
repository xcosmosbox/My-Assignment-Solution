#include "Player.h"

int Player::playerID = 0; // Initialize static variables

//Constructors and Destructors
Player::Player(string name, PlayerAttributeEnumType playerAttribute)//Create constructor for human players
{
	this->setID(++playerID);
	this->setPlayerName(name);
	this->setPlayerScore(0);
	this->setFarkleCount(0);
	this->setPlayerAttribute(playerAttribute);
}
Player::Player(string name, PlayerAttributeEnumType playerAttribute, AIEnumType AI_Character)//Create constructor for AI players
{
	this->setID(++playerID);
	this->setPlayerName(name);
	this->setPlayerScore(0);
	this->setFarkleCount(0);
	this->setPlayerAttribute(playerAttribute);
	this->setAIEnumType(AI_Character);
}
Player::~Player()
{

}


//Getter and setter of player name
string Player::getPlayerName() const
{
	return this->playerName;
}
void Player::setPlayerName(string name)
{
	this->playerName = name;
}

//Getter and setter of player score
int Player::getPlayerScore() const
{
	return this->playerScore;
}
void Player::setPlayerScore(int score)
{
	this->playerScore = score;
}
//There are many different operations for player scores
void Player::updatePlayerScore(int score)//addition score
{
	this->playerScore += score;
}
void Player::subtPlayerScore(int score)//score will be deducted after encountering Farkle three times
{
	this->playerScore -= score;
}
void Player::resetPlayerScore()//initialization
{
	this->setPlayerScore(0);
}


//Getter and setter of counter of Farkle
int Player::getFarkleCount() const
{
	return this->farkleCount;
}
void Player::setFarkleCount(int number)
{
	this->farkleCount = number;
}
void Player::updateFarkleCount()
{
	this->farkleCount++;
}
void Player::refreshFarkleCount()
{
	this->setFarkleCount(0);
};


//Getter and setter of player ID
int Player::getID() const
{
	return this->ID;
}
void Player::setID(int ID)
{
	this->ID = ID;
}


//Getter and setter of player attribute
void Player::setPlayerAttribute(PlayerAttributeEnumType playerAttribute)
{
	this->playerAttribute = playerAttribute;
}
PlayerAttributeEnumType Player::getPlayerAttribute() const
{
	return this->playerAttribute;
}

//Getter and setter of AI character
void Player::setAIEnumType(AIEnumType AI_Character)
{
	this->AI_Character = AI_Character;
}
AIEnumType Player::getAIEnumType() const
{
	return this->AI_Character;
}




