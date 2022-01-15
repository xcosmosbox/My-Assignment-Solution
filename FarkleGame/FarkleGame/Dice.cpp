#include "Dice.h"



 //---------Constructors and Destructors-----------// done.12.16
Dice::Dice(SkillLevelEnumType skillLevel)
{
	this->setSkillLevel(skillLevel);
	this->setTargetScore(getSkillLevel());
	this->setMinScoreInRound(getSkillLevel());
	this->setTempScore(0);
	this->setCountUnfarkle(0);
	this->lockPosition.fill(0); // init all elements of array
}
Dice::~Dice()
{
}


//---------Rolling dice and related functions-----------// done.12.16
void Dice::rollDice()
{
	//Get different values for six dice at random
	for (int i = 0; i < this->dice.size(); i++)
	{
		switch (rand() % 6 + 1)// [1,7)
		{
		case 1:
			setDiceValue(i, DiceEnumType::ONE);
			break;
		case 2:
			setDiceValue(i, DiceEnumType::TWO);
			break;
		case 3:
			setDiceValue(i, DiceEnumType::THREE);
			break;
		case 4:
			setDiceValue(i, DiceEnumType::FOUR);
			break;
		case 5:
			setDiceValue(i, DiceEnumType::FIVE);
			break;
		case 6:
			setDiceValue(i, DiceEnumType::SIX);
			break;
		}
	}
}
DiceEnumType Dice::getDiceValue(int index) const
{
	//Obtain the value of the dice according to the subscript
	return dice[index];
}


//---------Lock dice and check FARKLE---------//done.12.20
bool Dice::lockDice(vector<int> position)
{
	array<int, 6> result = { 0 };//An empty array for storing results

	/*Please note: I didn't write 'break;' Because I need to traverse each case, I need to combine all cases less than or equal to the length of the unlocked position.*/
	switch (position.size())
	{
	case 6:
		combination(position, result, position.size(), 6, 0, 6, StatusCodeForRollAndSaveEnumType::CHECKSAVE);//Find a combination with a target length of six
	case 5:
		combination(position, result, position.size(), 5, 0, 5, StatusCodeForRollAndSaveEnumType::CHECKSAVE);//Find a combination with a target length of five
	case 4:
		combination(position, result, position.size(), 4, 0, 4, StatusCodeForRollAndSaveEnumType::CHECKSAVE);//Find a combination with a target length of four
	case 3:
		combination(position, result, position.size(), 3, 0, 3, StatusCodeForRollAndSaveEnumType::CHECKSAVE);//Find a combination with a target length of three
	case 2:
		combination(position, result, position.size(), 2, 0, 2, StatusCodeForRollAndSaveEnumType::CHECKSAVE);//Find a combination with a target length of two
	case 1:
		combination(position, result, position.size(), 1, 0, 1, StatusCodeForRollAndSaveEnumType::CHECKSAVE);//Find a combination with a target length of one
	}

	//As long as the possible score is not zero, it means that the locking of dice is successful
	if (this->getCountUnfarkle() != 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}
/*This function is called by the combination() function.This function will pass the obtained combination to the rule to obtain the score according to the length of the combination.*/
bool Dice::checkLockRule(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode)
{
	switch (position.size())
	{
	case 1:
		return checkLockRuleForOne(position, statusCode);
		break;
	case 2:
		return checkLockRuleForTwo(position, statusCode);
		break;
	case 3:
		return checkLockRuleForThree(position, statusCode);
		break;
	case 4:
		return checkLockRuleForFour(position, statusCode);
		break;
	case 5:
		return checkLockRuleForFive(position, statusCode);
		break;
	case 6:
		return checkLockRuleForSix(position, statusCode);
		break;
	}
	return false;
}
bool Dice::checkLockRuleForSix(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode)
{
	vector<DiceEnumType> tempDice;
	for (int i = 0; i < 6; i++)
	{
		tempDice.push_back(this->getDiceValue(position[i]));
	}

	//In ascending order
	sort(tempDice.begin(), tempDice.end());//Because the length of six is the maximum length, sorting will not affect the locking of dice results
	DiceEnumType value = tempDice[0];

	//First, make sure that no position is locked
	if (this->checkBothUnlocked(position))
	{
		// SIX_OF_A_KIND = 3000, // Six of the same
		if (tempDice[1] == value && tempDice[2] == value && tempDice[3] == value && tempDice[4] == value && tempDice[5] == value)
		{
			//Only the status code indicates that the result needs to be locked and the cache score needs to be updated. Otherwise, the following operations will not be performed
			if (statusCode == StatusCodeForRollAndSaveEnumType::CHECKSAVE)
			{
				this->updateTempScore(3000);
				for (int i = 0; i < 6; i++)
				{
					this->setLockPosition(i);
				}
			}

			//Inform the system of possible scores
			this->updateCountUnfarkle();
			return true;
		}

		// TWO_TRIPLETS = 2500, // {[T1,T1,T1] + [T2,T2,T2]}
		if ((tempDice[0] == tempDice[1] && tempDice[1] == tempDice[2]) && (tempDice[3] == tempDice[4] && tempDice[4] == tempDice[5]))
		{
			//Only the status code indicates that the result needs to be locked and the cache score needs to be updated. Otherwise, the following operations will not be performed
			if (statusCode == StatusCodeForRollAndSaveEnumType::CHECKSAVE)
			{
				this->updateTempScore(2500);
				for (int i = 0; i < 6; i++)
				{
					this->setLockPosition(i);
				}
			}

			//Inform the system of possible scores
			this->updateCountUnfarkle();
			return true;
		}

		// FOUR_OF_A_KIND_PLUS_PAIR = 1500, // Four of the same + [T,T]
		if ((tempDice[0] == tempDice[1] && tempDice[1] == tempDice[2] && tempDice[2] == tempDice[3]) && (tempDice[4] == tempDice[5]))
		{
			//Only the status code indicates that the result needs to be locked and the cache score needs to be updated. Otherwise, the following operations will not be performed
			if (statusCode == StatusCodeForRollAndSaveEnumType::CHECKSAVE)
			{
				this->updateTempScore(1500);
				for (int i = 0; i < 6; i++)
				{
					this->setLockPosition(i);
				}
			}

			//Inform the system of possible scores
			this->updateCountUnfarkle();
			return true;
		}

		// THREE_PAIRS = 1500, // {[T1,T1]+[T2,T2]+[T3,T3]}
		if ((tempDice[0] == tempDice[1]) && (tempDice[2] == tempDice[3]) && (tempDice[4] == tempDice[5]))
		{
			//Only the status code indicates that the result needs to be locked and the cache score needs to be updated. Otherwise, the following operations will not be performed
			if (statusCode == StatusCodeForRollAndSaveEnumType::CHECKSAVE)
			{
				this->updateTempScore(1500);
				for (int i = 0; i < 6; i++)
				{
					this->setLockPosition(i);
				}
			}

			//Inform the system of possible scores
			this->updateCountUnfarkle();
			return true;
		}

		// ONE_TO_SIX_STRAIGHT = 1500, // 1,2,3,4,5,6
		if (tempDice[0] == DiceEnumType::ONE && tempDice[1] == DiceEnumType::TWO && tempDice[2] == DiceEnumType::THREE && tempDice[3] == DiceEnumType::FOUR && tempDice[4] == DiceEnumType::FIVE && tempDice[5] == DiceEnumType::SIX)
		{
			//Only the status code indicates that the result needs to be locked and the cache score needs to be updated. Otherwise, the following operations will not be performed
			if (statusCode == StatusCodeForRollAndSaveEnumType::CHECKSAVE)
			{
				this->updateTempScore(1500);
				for (int i = 0; i < 6; i++)
				{
					this->setLockPosition(i);
				}
			}
			//Inform the system of possible scores
			this->updateCountUnfarkle();
			return true;
		}

		return false;
	}
	else
	{
		return false;
	}

}
bool Dice::checkLockRuleForFive(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode)
{
	DiceEnumType value = this->getDiceValue(position[0]);

	//First, make sure that no position is locked
	if (this->checkBothUnlocked(position))
	{
		// FIVE_OF_A_KIND = 2000, // FIVE of the same}
		for (int i = 0; i < 5; i++)
		{
			if (this->getDiceValue(position[i]) != value)
			{
				return false;
			}
		}
		//Only the status code indicates that the result needs to be locked and the cache score needs to be updated. Otherwise, the following operations will not be performed
		if (statusCode == StatusCodeForRollAndSaveEnumType::CHECKSAVE)
		{
			this->updateTempScore(2000);
			for (int i = 0; i < 5; i++)
			{
				this->setLockPosition(position[i]);
			}
		}
		//Inform the system of possible scores
		this->updateCountUnfarkle();
		return true;
	}
	else
	{
		return false;
	}

}
bool Dice::checkLockRuleForFour(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode)
{
	DiceEnumType value = this->getDiceValue(position[0]);

	//First, make sure that no position is locked
	if (this->checkBothUnlocked(position))
	{
		// FOUR_OF_A_KIND = 1000, // Four of the same
		for (int i = 0; i < 4; i++)
		{
			if (this->getDiceValue(position[i]) != value)
			{
				return false;
			}
		}
		//Only the status code indicates that the result needs to be locked and the cache score needs to be updated. Otherwise, the following operations will not be performed
		if (statusCode == StatusCodeForRollAndSaveEnumType::CHECKSAVE)
		{
			this->updateTempScore(1000);
			for (int i = 0; i < 4; i++)
			{
				this->setLockPosition(position[i]);
			}
		}
		//Inform the system of possible scores
		this->updateCountUnfarkle();
		return true;
	}
	else
	{
		return false;
	}


}
bool Dice::checkLockRuleForThree(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode)
{
	int willTempScore = 0;
	DiceEnumType value = this->getDiceValue(position[0]);

	//First, make sure that no position is locked
	if (this->checkBothUnlocked(position))
	{
		// Three of a kind
		if (this->getDiceValue(position[0]) == value && this->getDiceValue(position[1]) == value && this->getDiceValue(position[2]) == value)
		{
			switch (value)
			{
			case DiceEnumType::ONE:
				willTempScore = 300;// 1,1,1
				break;
			case DiceEnumType::TWO:
				willTempScore = 200;// 2,2,2
				break;
			case DiceEnumType::THREE:
				willTempScore = 300;// 3,3,3
				break;
			case DiceEnumType::FOUR:
				willTempScore = 400;// 4,4,4
				break;
			case DiceEnumType::FIVE:
				willTempScore = 500;// 5,5,5
				break;
			case DiceEnumType::SIX:
				willTempScore = 600;// 6,6,6
				break;
			}
			//Only the status code indicates that the result needs to be locked and the cache score needs to be updated. Otherwise, the following operations will not be performed
			if (statusCode == StatusCodeForRollAndSaveEnumType::CHECKSAVE)
			{
				this->updateTempScore(willTempScore);
				for (int i = 0; i < 3; i++)
				{
					this->setLockPosition(position[i]);
				}
			}
			//Inform the system of possible scores
			this->updateCountUnfarkle();
			return true;
		}
		else
		{
			return false;//No combination can score
		}
	}
	else
	{
		return false;//There are locked dice
	}


}
bool Dice::checkLockRuleForTwo(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode)
{
	//First, make sure that no position is locked
	if (this->checkBothUnlocked(position))
	{
		//Is there a single 1 or a single 5
		if (this->getDiceValue(position[0]) == DiceEnumType::ONE || this->getDiceValue(position[0]) == DiceEnumType::FIVE || this->getDiceValue(position[1]) == DiceEnumType::ONE || this->getDiceValue(position[1]) == DiceEnumType::FIVE)
		{
			if (statusCode == StatusCodeForRollAndSaveEnumType::CHECKSAVE)
			{
				if (this->getDiceValue(position[0]) == DiceEnumType::ONE)
				{
					this->updateTempScore(100);//mean signle 1
					this->setLockPosition(position[0]);
				}
				if (this->getDiceValue(position[1]) == DiceEnumType::ONE)
				{
					this->updateTempScore(100);//mean signle 1
					this->setLockPosition(position[1]);
				}
				if (this->getDiceValue(position[0]) == DiceEnumType::FIVE)
				{
					this->updateTempScore(50);//mean signle 5
					this->setLockPosition(position[0]);
				}
				if (this->getDiceValue(position[1]) == DiceEnumType::FIVE)
				{
					this->updateTempScore(50);//mean signle 5
					this->setLockPosition(position[1]);
				}
			}

			this->updateCountUnfarkle();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
bool Dice::checkLockRuleForOne(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode)
{
	//First, make sure that no position is locked
	if (this->checkBothUnlocked(position))
	{
		//Is there a single 1 or a single 5
		if (this->getDiceValue(position[0]) == DiceEnumType::ONE || this->getDiceValue(position[0]) == DiceEnumType::FIVE)
		{
			if (statusCode == StatusCodeForRollAndSaveEnumType::CHECKSAVE)
			{
				if (this->getDiceValue(position[0]) == DiceEnumType::ONE)
				{
					this->updateTempScore(100);
					this->setLockPosition(position[0]);
				}
				if (this->getDiceValue(position[0]) == DiceEnumType::FIVE)
				{
					this->updateTempScore(50);
					this->setLockPosition(position[0]);
				}
			}

			this->updateCountUnfarkle();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//Traverse all dice that are not latched and pass their subscripts to the combination () function.
bool Dice::checkFarkle()
{
	//Reset counter
	this->setCountUnfarkle(0);

	//Get the lock information of all positions
	array<int, 6> nowLockedPosition = this->getLockedPosition();
	vector<int> nowPosition;
	array<int, 6> result = { 0 };

	//Extract every position that is not lockeded
	for (int i = 0; i < nowLockedPosition.size(); i++)
	{
		if (nowLockedPosition[i] == 0)
		{
			nowPosition.push_back(i); //store unlock index for dice
		}
	}

	/*Please note: I didn't write 'break;' Because I need to traverse each case, I need to combine all cases less than or equal to the length of the unlocked position.*/
	switch (nowPosition.size())
	{
	case 6:
		combination(nowPosition, result, nowPosition.size(), 6, 0, 6, StatusCodeForRollAndSaveEnumType::CHECKFARKLE);
	case 5:
		combination(nowPosition, result, nowPosition.size(), 5, 0, 5, StatusCodeForRollAndSaveEnumType::CHECKFARKLE);
	case 4:
		combination(nowPosition, result, nowPosition.size(), 4, 0, 4, StatusCodeForRollAndSaveEnumType::CHECKFARKLE);
	case 3:
		combination(nowPosition, result, nowPosition.size(), 3, 0, 3, StatusCodeForRollAndSaveEnumType::CHECKFARKLE);
	case 2:
		combination(nowPosition, result, nowPosition.size(), 2, 0, 2, StatusCodeForRollAndSaveEnumType::CHECKFARKLE);
	case 1:
		combination(nowPosition, result, nowPosition.size(), 1, 0, 1, StatusCodeForRollAndSaveEnumType::CHECKFARKLE);
	}

	//If the end result of the counter is 0, it means that there is no possibility of getting a score, which means Farkle
	if (this->getCountUnfarkle() == 0)
	{
		return true; // means FARKLE
	}
	this->setCountUnfarkle(0);
	return false;
}
void Dice::combination(vector<int> position, array<int, 6> result, int totalSize, int targetSize, int startIndex, const int range, StatusCodeForRollAndSaveEnumType statusCode)
{
	//As long as the target length is not equal to 0, it means that you need to continue to extract numbers
	if (targetSize != 0)
	{
		targetSize -= 1; //Extracted a number, so subtract one

		//Take the StartIndex at this time as the starting point and extract a number
		for (int i = startIndex; i < totalSize; i++)
		{
			//Store the numbers extracted in this recursion into the result
			result[range - (targetSize + 1)] = position[i];

			//Open a new recursion
			combination(position, result, totalSize, targetSize, i + 1, range, statusCode);//The new recursion moves StartIndex back one bit
		}
	}
	else
	{
		//If the target length is zero, it means that the extraction is completed and the result needs to be output
		vector<int> resultPosition;
		for (int i = 0; i < range; i++)
		{
			resultPosition.push_back(result[i]);
		}

		//Pass the final combination result to another function to check the score
		this->checkLockRule(resultPosition, statusCode);
	}
}
bool Dice::checkBothUnlocked(vector<int> position)
{
	for (int i = 0; i < position.size(); i++)
	{

		if (this->lockPosition[position[i]] == 1)
		{
			return false;
		}
	}
	return true;
}

//---------Get the scores---------//
bool Dice::checkMinScoreInRound()
{
	//Check whether it can be saved
	if ((this->getTempScore() - this->getMinScoreInRound()) >= 0)
	{
		return true;
	}

	return false;
}
int Dice::getMinScoreInRound() const
{
	return this->minScoreInRound;
}


//---------Get the position---------//
array<int, 6> Dice::getLockedPosition() const
{
	//Get the locked position
	return this->lockPosition;
}
vector<int> Dice::getUnlockedPosition() const
{
	//Get the position information of all dice that are not latched
	array<int, 6> position = this->getLockedPosition();
	vector<int> unlockedPosition;
	for (int i = 0; i < position.size(); i++)
	{
		if (position[i] == 0)
		{
			unlockedPosition.push_back(i);
		}
	}
	return unlockedPosition;
}
void Dice::resetLockedPosition()
{
	//reset locked position
	this->lockPosition.fill(0);
}
//See how many dice are not locked now
int Dice::getUnlockedNumber() const
{
	int count = 6;
	for (int i = 0; i < 6; i++)
	{
		if ((this->getLockedPosition())[i] == 1)
		{
			count--;
		}
	}

	return count;
}
void Dice::updateCountUnfarkle()
{
	//If there is a possible scoring situation, the counter is incremented by one
	this->countUnfarkle++;
}
int Dice::getCountUnfarkle() const
{
	return this->countUnfarkle;
}



//---------Operate the temp scores---------//done.12.17
int Dice::getTempScore() const
{
	return this->tempScore;
}
void Dice::updateTempScore(int score)
{
	this->tempScore += score;
}
void Dice::resetTempScore() //reset temp scores before changging player
{
	this->setTempScore(0);
}


//---------Getting the target score---------//done.12.17
int Dice::getTargetScore() const
{
	return this->targetScore;
}

//---------Getting the skill level---------//done.12.17
SkillLevelEnumType Dice::getSkillLevel() const
{
	return this->skillLevel;
}



//---------Adding new dice if all dice are set aside---------//done.12.17
void Dice::addNewDice()
{
	lockPosition.fill(0); // initialize all elements of array
}

//---------Initialize the dice if changging the player---------//done.12.17
void Dice::initial()
{
	addNewDice();
	resetTempScore();
}





/*
* The following functions are only used for syntax identification and can only
* be called by functions within the class, and cannot be called directly be users
*/
void Dice::setLockPosition(int index)
{
	this->lockPosition[index] = 1; // 1 means locked
}
void Dice::setTempScore(int tempScore)
{
	this->tempScore = tempScore;
}
void Dice::setTargetScore(SkillLevelEnumType skillLevel)
{
	//Select different target scores according to different skill levels
	switch (skillLevel)
	{
	case SkillLevelEnumType::ROOKIE:
		this->targetScore = 5000;
		break;
	case SkillLevelEnumType::ROLLER:
		this->targetScore = 10000;
		break;
	case SkillLevelEnumType::HIGH_ROLLER:
		this->targetScore = 20000;
		break;
	}

}
void Dice::setSkillLevel(SkillLevelEnumType skillLevel)
{
	this->skillLevel = skillLevel;
}
void Dice::setDiceValue(int index, DiceEnumType value)
{
	this->dice[index] = value;
}
void Dice::setMinScoreInRound(SkillLevelEnumType skillLevel)
{
	//Select different minimum save scores according to different skill levels
	switch (skillLevel)
	{
	case SkillLevelEnumType::ROOKIE:
		this->minScoreInRound = 250;
		break;
	case SkillLevelEnumType::ROLLER:
		this->minScoreInRound = 500;
		break;
	case SkillLevelEnumType::HIGH_ROLLER:
		this->minScoreInRound = 750;
		break;
	}

}
void Dice::setCountUnfarkle(int number)
{
	this->countUnfarkle = number;
}

//---------Use ASCII art to output the image of dice---------//done.12.19
array<string, 8> Dice::get_ASCII_Dice(array<int, 6> position)
{
	string lockedString = "     [x]     ";
	string unlockedString_1 = "     [1]     ";
	string unlockedString_2 = "     [2]     ";
	string unlockedString_3 = "     [3]     ";
	string unlockedString_4 = "     [4]     ";
	string unlockedString_5 = "     [5]     ";
	string unlockedString_6 = "     [6]     ";
	array<string, 6> unlockedString = { unlockedString_1 ,unlockedString_2 ,unlockedString_3,unlockedString_4,unlockedString_5,unlockedString_6 };

	string px_0 = "             ";

	string p1_0 = " +---------+ ";
	string p1_1 = " |         | ";
	string p1_2 = " |         | ";
	string p1_3 = " |    O    | ";
	string p1_4 = " |         | ";
	string p1_5 = " |         | ";
	string p1_6 = " +---------+ ";
	array<string, 8> point_1 = { p1_0, p1_1 , p1_2 , p1_3 , p1_4 , p1_5 , p1_6 , "" };

	string p2_0 = " +---------+ ";
	string p2_1 = " |         | ";
	string p2_2 = " |         | ";
	string p2_3 = " |  O   O  | ";
	string p2_4 = " |         | ";
	string p2_5 = " |         | ";
	string p2_6 = " +---------+ ";
	array<string, 8> point_2 = { p2_0, p2_1 , p2_2 , p2_3 , p2_4 , p2_5 , p2_6 , "" };

	string p3_0 = " +---------+ ";
	string p3_1 = " |         | ";
	string p3_2 = " |  O      | ";
	string p3_3 = " |    O    | ";
	string p3_4 = " |      O  | ";
	string p3_5 = " |         | ";
	string p3_6 = " +---------+ ";
	array<string, 8> point_3 = { p3_0, p3_1 , p3_2 , p3_3 , p3_4 , p3_5 , p3_6 , "" };

	string p4_0 = " +---------+ ";
	string p4_1 = " |         | ";
	string p4_2 = " |  O   O  | ";
	string p4_3 = " |         | ";
	string p4_4 = " |  O   O  | ";
	string p4_5 = " |         | ";
	string p4_6 = " +---------+ ";
	array<string, 8> point_4 = { p4_0, p4_1 , p4_2 , p4_3 , p4_4 , p4_5 , p4_6 , "" };

	string p5_0 = " +---------+ ";
	string p5_1 = " |         | ";
	string p5_2 = " |  O   O  | ";
	string p5_3 = " |    O    | ";
	string p5_4 = " |  O   O  | ";
	string p5_5 = " |         | ";
	string p5_6 = " +---------+ ";
	array<string, 8> point_5 = { p5_0, p5_1 , p5_2 , p5_3 , p5_4 , p5_5 , p5_6 , "" };

	string p6_0 = " +---------+ ";
	string p6_1 = " |         | ";
	string p6_2 = " |  O   O  | ";
	string p6_3 = " |  O   O  | ";
	string p6_4 = " |  O   O  | ";
	string p6_5 = " |         | ";
	string p6_6 = " +---------+ ";
	array<string, 8> point_6 = { p6_0, p6_1 , p6_2 , p6_3 , p6_4 , p6_5 , p6_6 , "" };


	string line0 = "";
	string line1 = "";
	string line2 = "";
	string line3 = "";
	string line4 = "";
	string line5 = "";
	string line6 = "";
	string line7 = "";
	array<string, 8> line = { "","","","","","","","" };

	//Since the printout on the terminal can only be performed line by line, I need to format the dice.
	for (int i = 0; i < line.size(); i++)
	{
		//The previous line is the content of dice, and will only wrap after the sixth dice is printed.
		if (i == 7)
		{
			//According to the value of dice, select the string corresponding to the number of rows of different dice for splicing.
			for (int j = 0; j < position.size(); j++)
			{
				if (position[j] == 0)
				{
					line[i] += unlockedString[j];
				}
				else
				{
					line[i] += lockedString;
				}
			}
			line[i] += "\n";
		}
		else
		{
			//The eighth line is the number of lines that identify whether the dice are locked, so we need to specify the locked position information.
			for (int j = 0; j < position.size(); j++)
			{
				if (position[j] == 0)
				{
					switch (this->getDiceValue(j))
					{
					case DiceEnumType::ONE:
						line[i] += point_1[i];
						break;
					case DiceEnumType::TWO:
						line[i] += point_2[i];
						break;
					case DiceEnumType::THREE:
						line[i] += point_3[i];
						break;
					case DiceEnumType::FOUR:
						line[i] += point_4[i];
						break;
					case DiceEnumType::FIVE:
						line[i] += point_5[i];
						break;
					case DiceEnumType::SIX:
						line[i] += point_6[i];
						break;
					}
				}
				else
				{
					line[i] += px_0;
				}

			}
			line[i] += "\n";
		}

	}

	return line;
}
