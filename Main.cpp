#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

void PrintGameHead()
{
	//Game Start
	cout << "           ________________________\n";
	cout << "          |                        |\n";
	cout << "          | HANG MAN: MOVIES/SHOWS |\n";
	cout << "          |________________________|\n";

}

void PrintHangMan(int life)
{
	if (life == 6)
	{
		cout << "     ______\n";
		cout << "    |      |\n";
		cout << "    |\n";
		cout << "    |\n";
		cout << "    |\n";
		cout << "    |\n";
		cout << "    |\n";
		cout << "____|____\n";
	}
	else if (life == 5)
	{
		cout << "     ______\n";
		cout << "    |      |\n";
		cout << "    |      O\n";
		cout << "    |\n";
		cout << "    |\n";
		cout << "    |\n";
		cout << "    |\n";
		cout << "____|____\n";
	}
	else if (life == 4)
	{
		cout << "     ______\n";
		cout << "    |      |\n";
		cout << "    |      O\n";
		cout << "    |      |\n";
		cout << "    |      |\n";
		cout << "    |\n";
		cout << "    |\n";
		cout << "____|____\n";
	}
	else if (life == 3)
	{
		cout << "     ______\n";
		cout << "    |      |\n";
		cout << "    |      O\n";
		cout << "    |      |-->\n";
		cout << "    |      |\n";
		cout << "    |\n";
		cout << "    |\n";
		cout << "____|____\n";
	}
	else if (life == 2)
	{
		cout << "     ______\n";
		cout << "    |      |\n";
		cout << "    |      O\n";
		cout << "    |   <--|-->\n";
		cout << "    |      |\n";
		cout << "    |\n";
		cout << "    |\n";
		cout << "____|____\n";
	}
	else if (life == 1)
	{
		cout << "     ______\n";
		cout << "    |      |\n";
		cout << "    |      O\n";
		cout << "    |   <--|-->\n";
		cout << "    |      |\n";
		cout << "    |       \\\n";
		cout << "    |        \\\n";
		cout << "____|____\n";
	}
	else if (life == 0)
	{
		cout << "     ______\n";
		cout << "    |      |\n";
		cout << "    |      O\n";
		cout << "    |   <--|-->\n";
		cout << "    |      |\n";
		cout << "    |     / \\\n";
		cout << "    |    /   \\\n";
		cout << "____|____\n";
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
	string word, wordGuessed, wordIn;
	char chr, playAgain, letter;
	bool run, finish, found, wordNotGuessed;
	int randNum, count;

	
	run = true;


	//Getting the word from file and into array

	while (getline(words, word))
	{
		if (!word.empty())
			wordsArray.push_back(word);
	}

	/*while (!words.eof())
	{
		words.get(chr);
		while (chr != '\n')
		{
			word += chr;
			words.get(chr);

		}
		wordsArray.push_back(word);
		word = "";
	}
	*/
	//cout << wordsArray.at(1);
	
	//cout << wordsArray.size();

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
		randNum = rand() % (wordsArray.size() - 1);
		word = wordsArray.at(randNum);

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


			cout << "Enter charachter/word: ";
			cin >> wordIn;

			if (wordIn.length() > 1)
			{
				if (wordIn == word)
				{
					cout << "\nCongrats.. You guessed the word:\n";
					cout << word << "\n";
					finish = true;
				}
				else
				{
					life -= 1;
					PrintHangMan(life);
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
				for (int i = 0; i < word.length(); i++)
				{
					if (word[i] == letter)
					{
						found = true;
						wordGuessed[i] = letter;
					}
				}



				if (not found)
				{
					life -= 1;
					PrintHangMan(life);
					//cout << "\n";
					if (life == 0)
					{
						finish = true;
						cout << "\nOOPS.. You failed\n";
						cout << word << "\n";
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
					cout << "\nCongrats.. You guessed the word:\n";
					cout << wordGuessed << "\n";
					finish = true;
				}
				else if (life != 0)
					cout << "\n" << wordGuessed << "\n";

				found = false;

			}
		}

		cout << "\nPlay again? (y/n): ";
		cin >> playAgain;
		if (playAgain == 'y')
			run = true;
		else if (playAgain == 'n')
			run = false;
		else
			cout << "Invalid input.. Try again";
	}

	return 0;
}
