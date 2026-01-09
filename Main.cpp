#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>

using namespace std;

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

void removeElement(vector<string> &v, int index)
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
		cout << SPACE << "    |        \\\n";
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
		cout << SPACE << "    |    /   \\\n";
		cout << SPACE << "____|____\n";
	}
}


int main()
{

	//Generating different random numbers each time
	srand(time(0));

	ifstream words;
	words.open("words.txt");

	if (!words.is_open())
	{
		cout << "Error: words.txt not found!\n";
		return 1;
	}

	vector<string> wordsArray;
	int life, index;
	string word, wordGuessed, wordIn, wordLower;
	char playAgain, letter;
	bool run, finish, found, wordNotGuessed;
	int randNum;

	run = true;


	//Getting the word from file and into array

	while (std::getline(words, word))
	{
		if (!word.empty())
			wordsArray.push_back(word);
	}


	//Printing the game title
	PrintGameHead();


	//Loop of different rounds

	while (run)
	{
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


		//Loop of guessing charchters

		while (finish == false)
		{

			wordNotGuessed = false;
			index = 0;
			wordIn = "";


			cout << "Enter charachter/word: ";
			std::getline(std::cin, wordIn);
			
			wordIn = lowerString(wordIn);

			

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
				letter = wordIn[0];
				//cout << letter << "\n";
				for (int i = 0; i < wordLower.length(); i++)
				{
					if (wordLower[i] == letter)
					{
						found = true;
						wordGuessed[i] = word[i];
					}
				}



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


				while (index < wordGuessed.length())
				{
					if (wordGuessed[index] == '-')
						wordNotGuessed = true;
					index++;

				}



				if (wordNotGuessed == false)
				{
					cout << "\nCongrats.. You guessed the word: " << wordGuessed << "\n";
					finish = true;
				}
				else if (life != 0)
					cout << "\n" << wordGuessed << "\n";

				found = false;

			}
		}

		//removing movie/series from vector to prevent repeat
		
		removeElement(wordsArray, randNum);
		
		
		//When vector is empty

		if (wordsArray.size() == 0)
		{
			cout << "\n--------------------------------------------\n";
			cout << "    Congrats!! You completed the game!!\n";
			cout << "--------------------------------------------\n\n\n";
			break;
		}


		//Playing Again or exiting

		cout << "\nPlay again? (y/n): ";
		std::cin >> playAgain;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (playAgain == 'y')
			run = true;
		else if (playAgain == 'n')
			run = false;
		else
			cout << "Invalid input.. Try again";
	}

	words.close();

	return 0;
}
