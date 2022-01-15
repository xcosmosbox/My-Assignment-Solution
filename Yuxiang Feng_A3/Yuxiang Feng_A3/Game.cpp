

#include "Game.h"

 //Constructors and Destructors
Game::Game(vector<Player>* players, Dice* dice)
{
	this->setPlayers(players);
	this->setDice(dice);
	this->setEndFlag(false);
	this->setNowPlayer(this->randomStartPlayer());
	this->setProcess(ProcessOperatorEnumType::ROLL);

}
Game::~Game()
{
}



//Start game
void Game::start()
{
	char userInput = ' ';
	int added = 0;//AI players with a personality need to use this variable to determine whether to save

	//This loop runs until you exit or the game is over
	while (!endFlag)
	{
		bool needRoll = true;

		//Perform different operations through the process code
		switch (this->getProcess())
		{
		case ProcessOperatorEnumType::ROLL:
			needRoll = true;

			//Display
			system("cls");
			readFile(ASCII_ART_FARKLE_GAME_NAME_FILE_ADDR);
			displayInfo();

			//Determine whether the player at this time is a human or an AI player
			if ((*(this->players))[this->nowPlayer].getPlayerAttribute() == PlayerAttributeEnumType::AI)
			{
				//Check whether it can be saved
				if (this->dice->checkMinScoreInRound())
				{
					//Choose different operations according to AI's character
					switch ((*(this->players))[this->nowPlayer].getAIEnumType())
					{
						//The coward will save it immediately
					case AIEnumType::COWARD:
						userInput = 'B';
						cout << "\t\t\t\t\t\tDo you want to [H]elp, [Q]uit, [R]oll or [B]ank?";
						Sleep(2000);
						cout << " B";
						Sleep(1000);
						cout << "\n\n\t\t\t\t\t\tAI successfully saved scores!";
						Sleep(2000);
						break;

						//The fearless will choose whether to save or not according to the number of dice saved
					case AIEnumType::DREADNAUGHT:
						//If the all dice have been shelved once, choose to save the score
						if (added == 1)
						{
							added = 0;
							userInput = 'B';
							cout << "\t\t\t\t\t\tDo you want to [H]elp, [Q]uit, [R]oll or [B]ank?";
							Sleep(1500);
							cout << " B";
							Sleep(1500);
							cout << "\n\n\t\t\t\t\t\tAI successfully saved scores!";
							Sleep(2000);
						}
						else
						{
							userInput = 'R';
							cout << "\t\t\t\t\t\tDo you want to [H]elp, [Q]uit, [R]oll or [B]ank?";
							Sleep(1500);
							cout << " R\n";
							Sleep(1500);
						}
						break;

						//Gamblers will decide according to the number of dice. If the number of dice is less than or equal to 2, the score is saved.
					case AIEnumType::GAMBLER:
						if (this->dice->getUnlockedNumber() <= 2)
						{
							userInput = 'B';
							cout << "\t\t\t\t\t\tDo you want to [H]elp, [Q]uit, [R]oll or [B]ank?";
							Sleep(1500);
							cout << " B";
							Sleep(1500);
							cout << "\n\n\t\t\t\t\t\tAI successfully saved scores!";
							Sleep(2000);
						}
						else
						{
							userInput = 'R';
							cout << "\t\t\t\t\t\tDo you want to [H]elp, [Q]uit, [R]oll or [B]ank?";
							Sleep(1500);
							cout << " R\n";
							Sleep(1000);
						}
						break;

					}
				}
				else
				{
					userInput = 'R';
					cout << "\t\t\t\t\t\tDo you want to [H]elp, [Q]uit, [R]oll or [B]ank?";
					Sleep(1500);
					cout << " R\n";
					Sleep(1000);
				}
			}
			else
			{
				//Not AI, so ask human players what to do.
				userInput = inputCheck("\t\t\t\t\t\tDo you want to [H]elp, [Q]uit, [R]oll or [B]ank?");
			}

			//If you choose to save scores or leave the game, subsequent actions are not displayed
			if (userInput == 'Q' || userInput == 'B' || userInput == 'H')
			{
				needRoll = false;
			}

			//If 'needroll' is true, subsequent operations need to be displayed
			if (needRoll)
			{
				//If no dice can be locked, add a new array of dice
				if (this->dice->getUnlockedNumber() == 0)
				{
					this->dice->addNewDice();
					added++;
				}

				//Execute the program and output the results using ASCII art
				this->dice->rollDice();
				this->displayDice();

				//Check whether it is Farkle at this time
				if (this->dice->checkFarkle())
				{
					cout << "\t\t\t\t\t\tOops! You are FARKLE! You lost your temp score!\n";

					//Farkle appears, so the player's Farkle counter should be incremented by one
					((*players)[this->nowPlayer]).updateFarkleCount();

					//If the player's Farkle counter reaches three times, he will be punished.
					if (((*players)[this->nowPlayer]).getFarkleCount() == 3)
					{
						((*players)[this->nowPlayer]).subtPlayerScore(1000);//punishment
						((*players)[this->nowPlayer]).refreshFarkleCount();//Number of times the counter was refreshed

						//If the player's score is less than 0, he will be eliminated directly.
						if ((*(this->players))[this->nowPlayer].getPlayerScore() < 0)
						{
							cout << "\t\t\t\t\t\tToo bad! Player " + (*(this->players))[this->nowPlayer].getPlayerName() + "'s score became negative\n\t\t\t\t\t\tSo he lost his qualification to continue the game! \n\n\t\t\t\t\t\tReduce the number of players by one!!\n\n";

							system("pause");

							//Only when there are multiple players, the operation at this time makes sense. And it can effectively prevent the subscript from crossing the boundary.
							if ((*(this->players)).size() >= 2)
							{
								//Remove this player directly from the game.
								(*(this->players)).erase(this->players->begin() + this->nowPlayer);
							}
						}
					}

					//The results of AI players need to wait for users to view
					if ((*(this->players))[this->nowPlayer].getPlayerAttribute() == PlayerAttributeEnumType::AI)
					{
						Sleep(3000);
					}
					else
					{
						system("pause");
					}

					//Due to Farkle, switch players, reset temp score and change the process symbol.
					this->changePlayer();
					this->dice->resetTempScore();
					added = 0;
					userInput = 'S';
				}

				//If the process symbol is not changed, Farkle is not encountered.
				if (userInput == 'R')
				{
					//Enter the function that locks the dice
					locking();
				}
			}
			break;
		case ProcessOperatorEnumType::BANK:
			((*players)[this->nowPlayer]).updatePlayerScore(this->dice->getTempScore());//Store the cached score into the player's score.
			this->checkGameOver();//Check game over
			this->changePlayer();//change player
			this->dice->resetTempScore();//Reset temp score
			added = 0;
			userInput = 'S';
			break;
		case ProcessOperatorEnumType::QUIT:
			if (!this->quit("\t\t\t\t\t\tAre you sure you want to quit the game?(Y/n)"))
			{
				userInput = 'R';
			}
			break;
		case ProcessOperatorEnumType::HELP:
			cout << "\n\n";
			readFile(GAME_RULE_FILE_ADDR);//game rule
			system("pause");
			system("cls");
			userInput = 'R';
			break;
		}

		//Change the process according to user input
		switch (userInput)
		{
		case 'S':
			this->setProcess(ProcessOperatorEnumType::ROLL);
			break;
		case 'Q':
			this->setProcess(ProcessOperatorEnumType::QUIT);
			break;
		case 'R':
			this->setProcess(ProcessOperatorEnumType::ROLL);
			break;
		case 'B':
			this->setProcess(ProcessOperatorEnumType::BANK);
			break;
		case 'H':
			this->setProcess(ProcessOperatorEnumType::HELP);
			break;
		}

	}

	this->gameOver();

}

//Lock dice
void Game::locking()
{
	cout << "\n\n\t\t\t\t\t\tPlease select the dice you want using the number.\n";
	vector<int> needPosition;

	//Determine whether it is AI or human
	if ((*(this->players))[this->nowPlayer].getPlayerAttribute() == PlayerAttributeEnumType::AI)
	{
		//AI will lock all unlocked dice
		needPosition = this->dice->getUnlockedPosition();
		cout << "\t\t\t\t\t\tThe dice you want are: ";
		Sleep(700);

		//Input numbers one by one, and there is a certain time interval between each number.
		for (int i = 0; i < needPosition.size(); i++)
		{
			cout << to_string(needPosition[i] + 1);
			Sleep(700);
		}
		cout << "\n\n";
	}
	else
	{
		//Ask human players what dice they want to save
		needPosition = askForLockDice("\t\t\t\t\t\tThe dice you want are:");
	}

	//Check whether it was saved successfully
	bool successSave = this->dice->lockDice(needPosition);
	if (successSave)
	{
		cout << "\t\t\t\t\t\tYou successfully put the dice on desk!\n\n\n";
		if ((*(this->players))[this->nowPlayer].getPlayerAttribute() == PlayerAttributeEnumType::AI)
		{
			Sleep(2500);
		}
		else
		{
			system("pause");
		}

	}
	else
	{
		cout << "\t\t\t\t\t\tThe combination you gave can't get points. Please select the dice again.\n\n";
		system("pause");
		locking();
	}

}

//Randomly select a player as the first player to start the game
int Game::randomStartPlayer()
{
	return rand() % this->players->size();
}
//Quit the game
bool Game::quit(string str)
{
	if (askForLetter(str) == 'Y')
	{
		this->setEndFlag(true);
		return true;
	}
	return false;
}
//Check game over
void Game::checkGameOver()
{
	//If the player's score is greater than or equal to the target score, the game ends and the player wins.
	if (((*players)[this->nowPlayer]).getPlayerScore() >= this->dice->getTargetScore())
	{
		this->setEndFlag(true);//Change the flag to end the loop
		cout << "\n\n\t\t\t\t\t\tCongratulations! Player " + ((*players)[this->nowPlayer]).getPlayerName() + " won!\n\n";
	}
}
//Game over
void Game::gameOver()
{
	cout << "\t\t\t\t\t\tThe game is over!\n\t\t\t\t\t\tPress any key to return to the menu.\n\n";
	system("pause");
}


//Change player
void Game::changePlayer()
{
	//If this player is the last, the next player switches back to the first player
	if (this->nowPlayer < this->players->size() - 1)
	{
		this->nowPlayer++;
		this->dice->resetTempScore();
		this->dice->resetLockedPosition();
	}
	else
	{
		this->nowPlayer = 0;
		this->dice->resetTempScore();
		this->dice->resetLockedPosition();
	}
}




//Display
void Game::displayDice()
{
	//ASCII art for dice
	array<string, 8> myDiceImage = this->dice->get_ASCII_Dice(this->dice->getLockedPosition());
	array<string, 8>& rMyDiceImage = myDiceImage;

	//Overload operators to display images. (just as a demonstration of my advanced skills, no special meaning)
	cout << operator<<(rMyDiceImage);
}
//Displays the player's name, score, cache score, and remaining dice
void Game::displayInfo()
{
	stringstream sTitleBox;

	string name = ((*players)[this->nowPlayer]).getPlayerName();
	int totalScore = ((*players)[this->nowPlayer]).getPlayerScore();
	int tempScore = this->dice->getTempScore();
	int leftDice = this->dice->getUnlockedNumber();


	string line0 = "\n";
	string line2 = " " + name + "   " + "Total:" + to_string(totalScore) + "  " + "Temp:" + to_string(tempScore) + "   " + "Dice Left:" + to_string(leftDice) + " " + "\n";
	string line1 = "\t\t\t\t\t\t";
	for (int i = 0; i < line2.size(); i++)
	{
		line1 += "*";
	}
	line1 += "\n";
	string line3 = line1;
	line2 = "\t\t\t\t\t\t" + line2;
	string line4 = "\t\t\t\t\t\tIt is your turn, " + ((*players)[this->nowPlayer]).getPlayerName() + "\n\n";

	sTitleBox << line0 << line1 << line2 << line3 << line4;
	cout << sTitleBox.str();
}







//Getter
vector<Player>* Game::getPlayers()
{
	return this->players;
}
Dice* Game::getDice()
{
	return this->dice;
}
bool Game::getEndFlag()
{
	return this->endFlag;
}
int Game::getNowPlayer()
{
	return this->nowPlayer;
}



//Setter
void Game::setPlayers(vector<Player>* pPlayer)
{
	this->players = pPlayer;
}
void Game::setDice(Dice* pDice)
{
	this->dice = pDice;
}
void Game::setEndFlag(bool flag)
{
	this->endFlag = flag;
}
void Game::setNowPlayer(int index)
{
	this->nowPlayer = index;
}
void Game::setProcess(ProcessOperatorEnumType process)
{
	this->process = process;
}
ProcessOperatorEnumType Game::getProcess() const
{
	return this->process;
}


//operators overloading to display the dic image of ASCII art
string Game::operator<<(array<string, 8>& myDiceImage)
{
	string myImage = "";
	for (int i = 0; i < 8; i++)
	{
		myImage += "\t\t\t\t" + myDiceImage[i];
	}

	return myImage;

}

//Function with input detection
char Game::inputCheck(string question)
{
	char userInput = ' ';

	userInput = askForLetter(question);

	//Only one of three can be selected
	if ((userInput != 'Q') && (userInput != 'R') && (userInput != 'B') && (userInput != 'H'))
	{
		cout << "\t\t\t\t\t\tThe command you entered does not exist! Please re-enter.\n";
		userInput = inputCheck(question);
	}

	//If the minimum saved score is not reached, re-enter it
	if (userInput == 'B' && this->dice->checkMinScoreInRound() == false)
	{
		cout << "\t\t\t\t\t\tYou haven't reached the minimum score yet. You can't save the score yet.\n" << "\t\t\t\t\t\tYou need to get at least " << this->dice->getMinScoreInRound() << " scores!\n";
		userInput = inputCheck(question);//recursion
	}

	return toupper(userInput);

}