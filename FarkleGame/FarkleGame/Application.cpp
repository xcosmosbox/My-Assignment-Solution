 //    ______                 _      _         
 //   |  ____|               | |    | |        
 //   | |__     __ _   _ __  | | __ | |   ___  
 //   |  __|   / _` | | '__| | |/ / | |  / _ \ 
 //   | |     | (_| | | |    |   <  | | |  __/ 
 //   |_|      \__,_| |_|    |_|\_\ |_|  \___| 
 //                                             
 

#include "Application.h"
using namespace std;

int main()
{
	//seed random
	srand(unsigned(time(NULL)));

	//run
	runMenu();

	return 0;
}



/*******************************
 * Setup Game And Display Menu *
 *******************************/
void runMenu()
{
	//Flag to exit the program
	bool quitFlag = false;

	//Setup game
	displayInfo();

	while (!quitFlag)
	{
		// Display the menu information
		displayMenu();

		switch (askForNumber("\t\t\t\t\t\t Which option would you like (1-6):", 1, 6))
		{
		case 1:
			playGame();//start
			break;
		case 2:
			settingDefaultAI();//setting
			break;
		case 3:
			displayInfo();//game information
			break;
		case 4:
			help(1);//game rule
			break;
		case 5:
			help(2);//game example
			break;
		case 6:
			system("cls");
			readFile(SAY_BYE_FILE_ADDR);//say bye
			quitFlag = true; //Adjust the flag to end the loop
			break;
			/*    ____                   _
			//   |  _ \                 | |
			//   | |_) |  _   _    ___  | |
			//   |  _ <  | | | |  / _ \ | |
			//   | |_) | | |_| | |  __/ |_|
			//   |____/   \__, |  \___| (_)
			//             __/ |
			//            |___/
			*/
		}

	}
	system("pause");
}
void displayInfo()
{
	system("cls");
	readFile(ASCII_ART_FARKLE_GAME_NAME_FILE_ADDR);
	readFile(GAME_ABOUT_INFO_FILE_ADDR);//game information
	system("pause");
	system("cls");
}
void displayMenu()
{
	readFile(ASCII_ART_FARKLE_GAME_NAME_FILE_ADDR);
	readFile(GAME_MENU_FILE_ADDR);//game menu
}
void help(int number)
{
	switch (number)
	{
	case 1:
		system("cls");
		displayRule();//game rule
		break;
	case 2:
		system("cls");
		displayExample();//game example
		break;
	}
	system("cls");
}
void displayRule()
{
	readFile(ASCII_ART_FARKLE_GAME_NAME_FILE_ADDR);
	readFile(GAME_RULE_FILE_ADDR);//game rule
	system("pause");
	system("cls");
}
void displayExample()
{
	readFile(ASCII_ART_FARKLE_GAME_NAME_FILE_ADDR);
	readFile(GAME_EXAMPLE_FILE_ADDR);//game example
	system("pause");
	system("cls");
}



/************************************
 * Setting computer player in game  *
 ************************************/
void settingDefaultAI()
{
	system("cls");
	readFile(ASCII_ART_FARKLE_GAME_NAME_FILE_ADDR);
	readFile(GAME_SETTING_FILE_ADDR);//AI

	//Set the character of AI players
	switch (askForNumber("\t\t\t\t\t\t Which option would you like (1-4):", 1, 4))
	{
	case 1:
		defaultAI = AIEnumType::COWARD;
		cout << "\n\t\t\t\t\t\t Modified successfully!\n\n";
		system("pause");
		break;
	case 2:
		defaultAI = AIEnumType::DREADNAUGHT;
		cout << "\n\t\t\t\t\t\t Modified successfully!\n\n";
		system("pause");
		break;
	case 3:
		defaultAI = AIEnumType::GAMBLER;
		cout << "\n\t\t\t\t\t\t Modified successfully!\n\n";
		system("pause");
		break;
	case 4:
		//notiong
		//return menu
		break;
	}
	system("cls");
}



/***************
 * Start Game! *
 ***************/
void playGame()
{
	system("cls");
	vector<Player> createPlayerVector = addPlayers();//add player into the game
	Dice createDice = addDice();//add dice
	Game game(&createPlayerVector, &createDice);//create Game object
	game.start();//Start game!
	system("cls");
}
vector<Player> addPlayers()
{
	readFile(ASCII_ART_FARKLE_GAME_NAME_FILE_ADDR);
	vector<Player> playerVector;//Allows you to create an unlimited number of players
	int playerNumber = askForNumber("\t\t\t\t\t\t Please enter the number of players you want to create:");
	cout << endl;

	//Allows you to create an unlimited number of players
	for (int i = 0; i < playerNumber; i++)
	{
		//Create a human player, pass the human attribute and name to the player object and add it to the vector
		playerVector.push_back(Player(askForName("\t\t\t\t\t\t Please enter the name of player " + to_string((i + 1)) + ":"), PlayerAttributeEnumType::HUMAN));
		cout << endl;
	}
	cout << endl;

	//Ask if you want to create an AI player
	if (askForLetter("\t\t\t\t\t\t Do you wa nt to create a computer AI player?(y/n)") == 'Y')
	{
		//Ask AI's character
		switch (defaultAI)
		{
		case AIEnumType::COWARD:
			playerVector.push_back(Player("AI:Coward", PlayerAttributeEnumType::AI, defaultAI));
			break;
		case AIEnumType::DREADNAUGHT:
			playerVector.push_back(Player("AI:Dreadnaught", PlayerAttributeEnumType::AI, defaultAI));
			break;
		case AIEnumType::GAMBLER:
			playerVector.push_back(Player("AI:Gambler", PlayerAttributeEnumType::AI, defaultAI));
			break;
		}
	}

	cout << "\n\n\t\t\t\t\t\t Player created successfully! It's only the last step to start the game!\n\n";
	system("pause");
	system("cls");
	return playerVector;
}
Dice addDice()
{
	readFile(ASCII_ART_FARKLE_GAME_NAME_FILE_ADDR);
	readFile(SET_SKILL_LEVEL_FILE_ADDR);
	int skillSelect = askForNumber("\t\t\t\t\t\t Please enter the number of skill level of the dice:", 1, 3);

	//Difficulty in selecting dice
	if (skillSelect == 1)
	{
		Dice createDice(SkillLevelEnumType::ROOKIE);
		cout << "\n\t\t\t\t\t\t The game is created successfully. Press enter to start the game!\n";
		system("pause");
		return createDice;
	}
	else if (skillSelect == 2)
	{
		Dice createDice(SkillLevelEnumType::ROLLER);
		cout << "\n\t\t\t\t\t\t The game is created successfully. Press enter to start the game!\n";
		system("pause");
		return createDice;
	}
	else
	{
		Dice createDice(SkillLevelEnumType::HIGH_ROLLER);
		cout << "\n\t\t\t\t\t\t The game is created successfully. Press enter to start the game!\n";
		system("pause");
		return createDice;
	}

}

