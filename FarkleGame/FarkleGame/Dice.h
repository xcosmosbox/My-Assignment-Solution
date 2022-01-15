
#ifndef DICE_H
#define DICE_H

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<array>
#include<algorithm>
#include<Windows.h>
#include"MyEnum.h"

using namespace std;

class Dice
{
private:
    array<DiceEnumType, 6> dice;//An array that stores the values of six dice
    array<int, 6> lockPosition;//Record the position of the locked dice
    int countUnfarkle;//Once there is a combination of scores available, add one to this variable
    int tempScore;//Cache score. Before the player's Bank score, the cache score will not be written into the player's total score
    int targetScore;//Set the target score according to skill level
    int minScoreInRound;//Set the minimum score to be saved for each game according to the skill level
    SkillLevelEnumType skillLevel;//The variables of enumeration class are used to set the difficulty of the game

    void setLockPosition(int index);//It is only used for syntax identification. When the user calls the lockDice() function, only the dice that true the rules can be locked
    void setTempScore(int tempScore); //It is only used for syntax identification. Users cannot set scores directly. They need to call the exposed public function updateTempScore() function to call implicitly
    void setTargetScore(SkillLevelEnumType skillLevel); //It is only used for syntax identification. The user cannot directly set the target score. This function needs to be called by the constructor during initialization.
    void setSkillLevel(SkillLevelEnumType skillLevel); //It is only used for syntax identification. Set the difficulty of the game with the constructor
    void setDiceValue(int index, DiceEnumType value); //It is only used for syntax identification. In fact, the user does not have permission to manually set the value of the dice. User can only roll the dice by calling the rollDice() function
    void setMinScoreInRound(SkillLevelEnumType skillLevel);//It is only used for syntax identification. The user cannot directly set the minimum saving score. This function needs to be called by the constructor during initialization.
    void setCountUnfarkle(int number);//It is only used for syntax identification.


public:
    Dice(SkillLevelEnumType skillLevel);
    ~Dice();


    void rollDice();
    DiceEnumType getDiceValue(int index) const;//Get a subscript and find the number of dice in the corresponding position according to the subscript


    bool lockDice(vector<int> position); //Lock the dice and pass the "check save" status code
    bool checkLockRule(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode);//According to the obtained vector variable storing location information, select the scoring rule of corresponding length, and pass the obtained status code.
    bool checkLockRuleForSix(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode);//Check the score of the combination with length of six
    bool checkLockRuleForFive(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode);//Check the score of the combination with length of five
    bool checkLockRuleForFour(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode);//Check the score of the combination with length of four
    bool checkLockRuleForThree(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode);//Check the score of the combination with length of three
    bool checkLockRuleForTwo(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode);//Check the score of the combination with length of two
    bool checkLockRuleForOne(vector<int> position, StatusCodeForRollAndSaveEnumType statusCode);//Check the score of the combination with length of one
    bool checkFarkle();//Check whether it is in the "Farkle" state after each roll of dice

    /*
    The algorithm for calculating permutation and combination written by myself. This function takes seven arguments.
    The first parameter: vector < int > position -- this parameter stores all the position information to be arranged and combined.
    The second parameter: array < int, 6 > result -- the parameter that stores the results of permutation and combination. At the beginning, it is only initialized and does not store any meaningful data.
    The third parameter: int totalSize -- stores the number of cycles of the outermost cycle
    The fourth parameter: int targetSize -- the length of the combination to be arranged
    The fifth parameter: int startIndex -- where to start each recursion
    The sixth parameter: const int range -- a constant parameter that needs to be equal to targetSize. It is used to store the results in the array into the vector through a loop after obtaining the results
    The seventh parameter: statuscodeforrollandsaveenumtype statusCode -- status code. This permutation and combination function will pass the obtained results into the 'check' function, which will respond differently according to different status codes.*/
    void combination(vector<int> position, array<int, 6> result, int totalSize, int targetSize, int startIndex, const int range, StatusCodeForRollAndSaveEnumType statusCode);

    bool checkBothUnlocked(vector<int> position);//Before the program needs to detect how many scores the obtained combination can get, it needs to detect whether all positions in the combination are not locked.
    bool checkMinScoreInRound();//Check the minimum saved score in a round
    int getMinScoreInRound() const;//Obtain the minimum score that needs to be saved most in a game according to skill level
    array<int, 6> getLockedPosition() const;//Get locked posiiton
    vector<int> getUnlockedPosition() const;//Get unlocked position
    void resetLockedPosition();//When adding a new set of dice or exchanging players, the locked position information will be reset.
    int getUnlockedNumber() const;//Number of unlocked positions
    void updateCountUnfarkle();//Update the number of possible scoring situations
    int getCountUnfarkle() const;//The number of possible scoring situations is recorded

    array<string, 8> get_ASCII_Dice(array<int, 6> position);//Obtain the dice pattern at this time, using ASCII art technology


    int getTempScore() const;//Get cache score
    void updateTempScore(int score);//Update cache score
    void resetTempScore();//Reset cache score

    int getTargetScore() const;//Get target score

    SkillLevelEnumType getSkillLevel() const;//Get skill level

    void addNewDice();//When all dice are locked, you need to add a new array of dice

    void initial();//initial
};

#endif // !DICE_H