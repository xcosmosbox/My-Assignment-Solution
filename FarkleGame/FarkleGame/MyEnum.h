
#ifndef MYENUM_H
#define MYENUM_H

using namespace std;

//All possible scores on a dice
enum class DiceEnumType
{
	ONE = 1,
	TWO = 2,
	THREE = 3,
	FOUR = 4,
	FIVE = 5,
	SIX = 6
};

//All scoring rules
enum class ScoreRuleType
{
	THREE_KIND_OF_ONE = 300, // 1,1,1
	THREE_KIND_OF_TWO = 200, // 2,2,2
	THREE_KIND_OF_THREE = 300, // 3,3,3
	THREE_KIND_OF_FOUR = 400, // 4,4,4
	THREE_KIND_OF_FIVE = 500, // 5,5,5
	THREE_KIND_OF_SIX = 600, // 6,6,6
	FOUR_OF_A_KIND = 1000, // Four of the same
	FIVE_OF_A_KIND = 2000, // FIVE of the same
	SIX_OF_A_KIND = 3000, // Six of the same
	ONE_TO_SIX_STRAIGHT = 1500, // 1,2,3,4,5,6
	THREE_PAIRS = 1500, // {[T1,T1]+[T2,T2]+[T3,T3]}
	FOUR_OF_A_KIND_PLUS_PAIR = 1500, // Four of the same + [T,T]
	TWO_TRIPLETS = 2500, // {[T1,T1,T1] + [T2,T2,T2]}
};

//All the difficulty of the game
enum class SkillLevelEnumType
{
	ROOKIE, //low:5000
	ROLLER, //mid:10000
	HIGH_ROLLER, //high:20000
};

//All process codes
enum class ProcessOperatorEnumType
{
	START,
	ROLL,
	BANK,
	QUIT,
	HELP
};

//When the program detects possible scores, it determines whether to store scores according to the status code
enum class StatusCodeForRollAndSaveEnumType
{
	CHECKFARKLE, //The score will not be saved at this time, because it is only to detect whether Farkle occurs
	CHECKSAVE, //Save score
};

//Possible character of AI players
enum class AIEnumType
{
	COWARD, //Very timid. It will be saved whenever the minimum saving score is reached
	DREADNAUGHT, //Very bold, only after obtaining at least one complete set of dice will you choose to save
	GAMBLER, //Choose carefully. You usually choose to save the score when there are only two dice left
};

//Player attributes
enum class PlayerAttributeEnumType
{
	AI,
	HUMAN
};

#endif // !MYENUM_H
