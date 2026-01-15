
//Libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>

using namespace std;


//Constants
const string SPACE = "                         ";
const string TITLESPACE = "                   ";


string lowerString(string stringToLower)
{
	for (char& c : stringToLower)
	{
		c = tolower(static_cast<unsigned char>(c));
	}
	return stringToLower;
}


//Removes element from vector once used
void removeElement(vector<string>& v, int index)
{
	v.erase(v.begin() + index);
}


void PrintGameHead()
{
	//Game Start
	cout << TITLESPACE << " ________________________\n";
	cout << TITLESPACE << "|                        |\n";
	cout << TITLESPACE << "| HANG MAN: MOVIES/SHOWS |\n";
	cout << TITLESPACE << "|________________________|\n";

}



void PrintHangMan(int life)
{
	if (life == 6)
	{
		cout << SPACE << "     ______\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "____|____\n";
	}
	else if (life == 5)
	{
		cout << SPACE << "     ______\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |      O\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "____|____\n";
	}
	else if (life == 4)
	{
		cout << SPACE << "     ______\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |      O\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "____|____\n";
	}
	else if (life == 3)
	{
		cout << SPACE << "     ______\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |      O\n";
		cout << SPACE << "    |      |-->\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "____|____\n";
	}
	else if (life == 2)
	{
		cout << SPACE << "     ______\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |      O\n";
		cout << SPACE << "    |   <--|-->\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "    |\n";
		cout << SPACE << "____|____\n";
	}
	else if (life == 1)
	{
		cout << SPACE << "     ______\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |      O\n";
		cout << SPACE << "    |   <--|-->\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |       \\\n";
		cout << SPACE << "    |        \\_\n";
		cout << SPACE << "____|____\n";
	}
	else if (life == 0)
	{
		cout << SPACE << "     ______\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |      O\n";
		cout << SPACE << "    |   <--|-->\n";
		cout << SPACE << "    |      |\n";
		cout << SPACE << "    |     / \\\n";
		cout << SPACE << "    |   _/   \\_\n";
		cout << SPACE << "____|____\n";
	}
}


//Store words in vector from file
vector<string> loadWordsFromFile(ifstream& file)
{
	string wordRead;
	vector<string> wordVector;

	while (std::getline(file, wordRead))
	{
		if (!wordRead.empty())
			wordVector.push_back(wordRead);
	}

	return wordVector;

}


//Printing game is completed when no more words are left to guess in the vector 
bool printGameComplete(vector<string> wordVector)
{
	bool complete = false;

	if (wordVector.size() == 0)
	{
		cout << "\n--------------------------------------------\n";
		cout << "    Congrats!! You completed the game!!\n";
		cout << "--------------------------------------------\n\n\n";

		complete = true;
	}
	return complete;
}


//Asking users if they want to play another round
bool askPlayAgain()
{
	char playAgain = 'x';
	bool returnVal = false;

	playAgain = tolower(playAgain);
	while ((playAgain != 'y') and (playAgain != 'n'))
	{
		cout << "\nPlay again? (y/n): ";
		std::cin >> playAgain;
		playAgain = tolower(playAgain);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (playAgain == 'y')
			returnVal = true;
		else if (playAgain == 'n')
			returnVal = false;
		else
			cout << "Invalid input.. Try again";
	}
	return returnVal;
}

bool searchVector(std::vector<char> v, char letterToSearch)
{
	char currentLetter = 'z';
	bool letterFound = false;
	int size, index;
	size = v.size();
	index = 0;

	while (letterFound == false and index < size)
	{
		currentLetter = v[index];
		if (currentLetter == letterToSearch)
			letterFound = true;
		else
			index++;
	}

	return letterFound;
}

//vector<char> v is the vector that stores letters that were already guessed by the user
// char letterToAdd adds the guessed charchter to the vector if the letter was not guessed before
//adds the letter inputted to a vector to keep track of the letters already guessed by the user
void addGuessedLettersToVector(std::vector<char>& v, char letterToAdd)
{
	if (searchVector(v, letterToAdd) == false)
		v.push_back(letterToAdd);
}

//vector<char> v is the vector of letters that were already guessed
//prints out the letters that were already guessed by the user so they can keep track
void printGuessedLetters(std::vector<char> v)
{
	if (v.size() > 0)
	{
		std::cout << "\n\n\nLetters guessed:\n";
		for (char currentChar : v)
		{
			std::cout << currentChar << " | ";
		}
		std::cout << "\n";
	}
}



int main()
{
	//Generating different random numbers each time
	srand(time(0));


	//Opening file to read titles
	ifstream words;
	words.open("words.txt");


	//Checking if file opnened
	if (!words.is_open())
	{
		cout << "Error: words.txt not found!\n";
		return 1;
	}


	//Declarations
	vector<string> wordsArray;
	vector<char> lettersGuessed;
	int life, index;
	string word, wordGuessed, wordIn, wordLower;
	char playAgain, letter;
	bool run, finish, found, wordNotGuessed, complete;
	int randNum;

	run = true;

	wordsArray = loadWordsFromFile(words);

	PrintGameHead();

	//Loop of different rounds
	while (run)
	{
		lettersGuessed.clear();
		life = 6;
		found = false;
		finish = false;
		run = false;
		word = "";

		wordGuessed = "";

		// Selecting random word
		if (wordsArray.size() > 1)
			randNum = rand() % (wordsArray.size() - 1);
		else
			randNum = 0;

		word = wordsArray.at(randNum);
		wordLower = lowerString(word);

		PrintHangMan(life);

		cout << "\nGuess the word:\n\n";


		//Printing the dash
		for (int i = 0; i < word.length(); i++)
		{
			if (word[i] != ' ')
				wordGuessed += "-";
			else
				wordGuessed += " ";

		}
		cout << wordGuessed;
		cout << "\n";


		//Loop of guessing charchters until word is guesed
		while (finish == false)
		{

			wordNotGuessed = false;
			index = 0;
			wordIn = "";


			cout << "Enter charachter/word: ";
			std::getline(std::cin, wordIn);

			wordIn = lowerString(wordIn);


			//Checking if whole word is guessed or just a charachter
			if (wordIn.length() > 1)
			{
				if (wordIn == wordLower)
				{
					cout << "\nCongrats.. You guessed the word: " << word << "\n";
					finish = true;
				}
				else
				{

					life -= 1;
					PrintHangMan(life);
					printGuessedLetters(lettersGuessed);
					cout << "\n" << wordGuessed << "\n";
					//cout << "\n";
					if (life == 0)
					{
						finish = true;
						cout << "\nOOPS.. You failed\n";
						cout << word << "\n";
					}
				}

			}
			else
			{
				//If charchter guessed then storing it in a variable
				letter = wordIn[0];
				if (searchVector(lettersGuessed, letter) == false)
				{
					addGuessedLettersToVector(lettersGuessed, letter);
					//Checking if charchter is found in the word to be guessed
					for (int i = 0; i < wordLower.length(); i++)
					{
						if (wordLower[i] == letter)
						{
							found = true;
							wordGuessed[i] = word[i];
						}
					}


					//If wrong charchter guessed then print hangman and reduce life
					if (not found)
					{
						life -= 1;
						PrintHangMan(life);

						if (life == 0)
						{
							finish = true;
							cout << "\nOOPS.. You failed\n";
							cout << "The word was: " << word << "\n";
						}
					}


					//Checks if the whole word is guessed
					while (index < wordGuessed.length())
					{
						if (wordGuessed[index] == '-')
							wordNotGuessed = true;
						index++;

					}


					//If the whole word is guessed then exits loop to ask to start another round
					if (wordNotGuessed == false)
					{
						cout << "\nCongrats.. You guessed the word: " << wordGuessed << "\n";
						finish = true;
					}
					else if (life != 0)
					{
						printGuessedLetters(lettersGuessed);
						cout << "\n" << wordGuessed << "\n";

					}
				}
				else
					std::cout << "\nLetter guessed before!! Try Again..\n\n";

				found = false;

			}
		}

		//removing movie/series from vector to prevent repeat
		removeElement(wordsArray, randNum);


		//Exit program when vector becommes empty
		complete = printGameComplete(wordsArray);
		if (complete)
		{
			return 1;
		}


		run = askPlayAgain();
	}

	words.close();

	return 0;
}
