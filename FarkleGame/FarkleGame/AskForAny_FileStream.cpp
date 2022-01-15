#include"AskForAny_FileStream.h"

using namespace std;

/***************
 * File Stream *
 ***************/
void readFile(string fileName)
{
	// open file for reading
	ifstream fileToRead(fileName);
	if (fileToRead.is_open())
	{
		string line = "";
		while (!fileToRead.eof())
		{
			getline(fileToRead, line); // read from data
			cout << line << "\n";
		}
	}
	else
	{
		cout << "\n File not found!\n";
	}
	// remember to close the file
	fileToRead.close();
}
void writeFile(string fileName, string result)
{
	ofstream fileToWrite; //Create file output stream object

	//Open the fileand write data as an append at the end of the file
	fileToWrite.open(fileName, ios::out | ios::ate | ios::app);

	//Check file status
	if (fileToWrite.is_open())
	{
		//write the data
		fileToWrite << result << "\n";
		fileToWrite << "\n";
	}
	else
	{
		//display error message
		cout << "File is not open";
	}

	fileToWrite.close(); // close the file
}




/***************
 * Ask for any *
 ***************/
string askForName(string question)
{
	string userInput = "";
	while (userInput == "")
	{
		cout << question << " ";
		cin >> userInput;
	}
	return userInput;
}
int askForNumber(string question, int low, int high)
{
	int userInput;
	cout << question << " ";
	cin >> userInput;

	//Verify that the number is within range
	if (userInput < low || userInput > high)
	{
		cout << "The number you entered is illegal. Please re-enter." << "\n\n";
		userInput = askForNumber(question, low, high); //Call the function itself repeatedly
	}

	return userInput;
}
int askForNumber(string question)
{
	int userInput = -1; //-1 cannot appear in this program, so it represents an error
	cout << question << " ";
	cin >> userInput;

	//Verify that the number is within range
	if (userInput <= 0)
	{
		cout << "The number you entered is illegal. Please re-enter." << "\n\n";
		userInput = askForNumber(question); //Call the function itself repeatedly
	}

	return userInput;
}
char askForLetter(string question)
{
	string userInput = " ";
	while (userInput == " ")
	{
		cout << question << " ";
		cin >> userInput;
	}

	return toupper(userInput.at(0));
}

vector<int> askForLockDice(string question)
{
	cout << question << " ";
	string line = "";
	cin >> line;
	vector<int> lockPosition;
	for (int i = 0; i < line.size(); i++)
	{
		//The corresponding number can be obtained by subtracting the character '0' from the character entered by the user. Subtract 1 because the subscript of the array starts from zero.
		int number = line.at(i) - '0' - 1;

		lockPosition.push_back(number);
	}

	return lockPosition;
}

