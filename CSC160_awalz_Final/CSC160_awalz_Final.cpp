/*
* File: CSC160_awalz_Final.cpp
* Author: Austin Walz
* Date: 11/25/21
* Description: The final project of Hangman
*/


#include <iostream>
#include <fstream>
#include <string>
#include "Competitive.h"
#include "Casual.h"
using namespace std;

struct userWordInformation {

	//Information for this round
	int wordsGuessed = 0;
	int lettersGuessed = 0;
	int totalGuesses = 0;

	//Each spot fills up after each wrong guess and will be default at " "
	char wrongChars[7] = " ";

	//Helps keep wrong chars on track
	int wrongProgress = 0;

	//Refered back to for Correct Letters guessed
	char* wordProgress;


	//Words, letters, and total will be added to object at end of round for a running count as program runs
};

void start(Player* user, userWordInformation& wordInfo, string& realWord);
void board(Player *user, userWordInformation words, string realWord);
void letterCalculation(char choice, Player& user, userWordInformation& info, string realWord);
void wordCalculation(string choice, Player& user, userWordInformation& info, string realWord);
bool isGoing(Player* user, userWordInformation& info, string realWord);
void lose(Player* user, userWordInformation& info, string realWord);
void win(Player& user, userWordInformation& info);
void playAgain(Player* user, userWordInformation& info, string& realWord);

void difficultyChange(Player* user);


int main()
{
	//Variables
	Player* user;
	userWordInformation wordInfo;
	char letterGuess, wordLetter;
	string word, name, wordGuess;
	char style;
	Competitive test;

	//Intro to the game
	cout << "Welcome to hangman! In this game a random word is generated and it is up to you to guess the word!\n" <<
		"When you choose a Competitive style you will get less known words higher the difficulty.\n"<<
		"It will also keep track of your highest streak record along with current streak!\n"<<

		"\nWhile a Casual style will generate more and more complex words the higher the difficulty\n"<<
		"A Casual style will let you input a name to feel more friendly.\n" << 

		"\nWhen it says current difficulty 1,1 the first number is your word difficulty,\n"<<
		"And the second number means your lives difficulty.\n"<<
		"\nHave fun and good luck\n";
	system("pause");
	cout << endl;



	//Prevents incorrect input
	do {
		cout << "Would you like a more 1. competitive style or 2. casual style? (1 or 2): ";
		cin >> style;
	} while (!(style == '1' || style == '2'));

	//Chooses which word type is chosen and which features to use 
	if (style == '1') user = new Competitive();
	if (style == '2') user = new Casual();
	else user = new Competitive;
	cin.get();

	//Asks user name if Casual is chosen
	if ((*user).getPlayerType() == PlayerType::Casual) {
		cout << "What is your name? ";
		getline(cin, name);
		(*user).setName(name);
		cout << endl << "Welcome " << (*user).getName();
	}


	start(user, wordInfo, word);

	//Game loop
	while (true){
		while (user->getStatus() == Status::Going) {

			board(user, wordInfo, word);

			if (isGoing(user, wordInfo, word)) {

				//Asks user if guess word or letter then uses a switch to determine what to output for further input
				do {
					cout << "Would you like to guess 1. a letter or 2. a word (1 or 2): ";
					cin >> wordLetter;
				} while (!(wordLetter == '1' || wordLetter == '2'));
				
				switch (wordLetter)
				{
					//Letter Guess
				case('1'):
					//Input Loop to make sure guess is a letter
					do {
						try
						{
							cout << "Enter a character: ";
							cin >> letterGuess;
							if (!(isalpha(letterGuess))) throw letterGuess;
							letterCalculation(tolower(letterGuess), *user, wordInfo, word);
						}
						catch (char a)
						{
							cout << "Invalid input. Try again \n";
							system("pause");
						}
					} while (!(isalpha(letterGuess)));
					break;

					//Word guess
				case('2'):
					cin.get();
					cout << "Enter a word: ";
					getline(cin, wordGuess);
					//Makes word guess all lowercase
					for (int i = 0; i < wordGuess.length(); i++) wordGuess[i] = tolower(wordGuess[i]);
					wordCalculation(wordGuess, *user, wordInfo, word);
					break;
				default:
					break;
				}
				
			}
		}
		cout << endl;

		//End of game statments
		if (user->getStatus() == Status::Lose) lose(user, wordInfo,word);
		if (user->getStatus() == Status::Win) win(*user, wordInfo);
		cin.get();
		playAgain(user, wordInfo, word);
	};

	

}

//Start of game Function
void start(Player* user, userWordInformation& info, string& realWord) {	
	ifstream file;
	int random = rand() % 20;

	difficultyChange(user);

	//Sets possible chosen word to a Competitive File
	if (user->getPlayerType() == PlayerType::Competitive) {
		switch (user->getDifficulty())
		{
		case(1):
			file.open("Level1Comp.txt");
			break;
		case(2):
			file.open("Level2Comp.txt");
			break;
		case(3):
			file.open("Level3Comp.txt");
			break;
		default:
			file.open("GeneralWords.txt");
			break;
		}
	}

	//Sets possible chosen word to a Casual File
	if (user->getPlayerType() == PlayerType::Casual) {
		switch (user->getDifficulty())
		{
		case(1):
			file.open("Level1Casual.txt");
			break;
		case(2):
			file.open("Level2Casual.txt");
			break;
		case(3):
			file.open("Level3Casual.txt");
			break;
		default:
			file.open("GeneralWords.txt");
			break;
		}
	}
	
	for (int i = 0; i < random; i++) {
		file.ignore(100, '\n');
	}
	getline(file, realWord);

	file.close();

	//Inital start of the game
	for (int i = 0; i < 7; i++) {
		info.wrongChars[i] = ' ';
	}

	info.wordProgress = new char[realWord.length()];
	for (int i = 0; i < realWord.length(); i++) {
		info.wordProgress[i] = '_';
	}
}

//Displays board to paly in
void board(Player *user, userWordInformation words, string realWord) {

	//Clear the screen for a updated screen
	for (int i = 0; i < 20; i++) cout << endl;

	cout <<
		"Current Difficulty is : " <<	user->getDifficulty() << ", " << user->Player::getDifficulty();
	if (user->getPlayerType() == PlayerType::Competitive) {
		cout << endl << "Current Streak: " << user->getStreak();
	}

	//Draws the hangman based on remaining lives
	switch (user->getLives())
	{
	case(6):
		cout <<
			"\n   +---+\n"
			"   |   |\n"
			"       |\n"
			"       |\n"
			"       |\n"
			"   =====\n";
		break;
	case(5):
		cout <<
			"\n   +---+\n"
			"   |   |\n"
			"   O   |\n"
			"       |\n"
			"       |\n"
			"   =====\n";
		break;
	case(4):
		cout <<
			"\n   +---+\n"
			"   |   |\n"
			"   O   |\n"
			"   |   |\n"
			"       |\n"
			"   =====\n";
		break;
	case(3):
		cout <<
			"\n   +---+\n"
			"   |   |\n"
			"   O   |\n"
			"   |   |\n"
			"    \\  |\n"
			"   =====\n";
		break;
	case(2):
		cout <<
			"\n   +---+\n"
			"   |   |\n"
			"   O   |\n"
			"   |   |\n"
			"  / \\  |\n"
			"   =====\n";
		break;
	case(1):
		cout <<
			"\n   +---+\n"
			"   |   |\n"
			"   O/  |\n"
			"   |   |\n"
			"  / \\  |\n"
			"   =====\n";
		break;
	case(0):
		cout <<
			"\n  +---+\n"
			"  |   |\n"
			" \\O/  |\n"
			"  |   |\n"
			" / \\  |\n"
			"  =====\n";
		break;
	default:
		cout <<
			"\n  +---+\n"
			"  |   |\n"
			" \\O/  |\n"
			"  |   |\n"
			" / \\  |\n"
			"  =====\n";
		break;
	}
	
	for (int i = 0; i < realWord.length(); i++) {
		cout << words.wordProgress[i] << ' ';
	}


	cout << endl << "Incorrect Letters: \n";
	for (int i = 0; i < 7; i++) {
		cout << words.wrongChars[i] << ' ';
	}

	cout << endl;
}

//Finds out if letter is valid in correct word or not
void letterCalculation(char choice, Player& user, userWordInformation &info, string realWord) {
	
	//Prevents double guessing a letter
	for (int i = 0; i < realWord.length(); i++)
	{
		if (choice == info.wordProgress[i] || choice == info.wrongChars[i]) throw choice;
	}
	
	//Adds letter to correct spot
	bool temp = false;
	for (int i = 0; i < realWord.length(); i++) {
		if (choice == realWord[i]) {
			info.wordProgress[i] = choice;
			temp = true;
		}
	}

	//Adds letter to incorrect letters and subtracts lives
	if (!temp) {
		user--;
		info.wrongChars[info.wrongProgress++] = choice;
	}

	info.totalGuesses++;
	info.lettersGuessed++;
}

//Finds out if word matches real word
void wordCalculation(string choice, Player& user, userWordInformation& info, string realWord) {

	//Ends game if correct
	if (choice == realWord) {
		for (int i = 0; i < realWord.length(); i++) {
			info.wordProgress[i] = choice[i];
		}
	}

	//Subtracts Lives according to how wrong
	if (choice != realWord) {
		int tempLetter = info.lettersGuessed, tempTotal = info.totalGuesses;

		//Sets a tempProgress to reset the Shown Word Progress after calcuations
		char* tempProgress;
		tempProgress = new char[realWord.length()];
		for (int i = 0; i < realWord.length(); i++) {
			tempProgress[i] = info.wordProgress[i];
		}

		//Calculates how many letters in the guessed word aren't in the real word and subtracts lives accordingly
		for (int i = 0; i < choice.length(); i++) {
			try {
				letterCalculation(choice[i], user, info, realWord);
			}
			catch (char a)
			{
				
			}
		}
		

		//Undos the letterCalculation running totals
		for (int i = 0; i < realWord.length(); i++) {
			info.wordProgress[i] = tempProgress[i];
		}
		info.lettersGuessed = tempLetter;
		info.totalGuesses = tempTotal;
	}
	//Loop each letter through letter Calculation
	//Saves letter and total guess to reset them

	info.totalGuesses++;
	info.wordsGuessed++;
}

//Determines if game will continue
bool isGoing(Player *user, userWordInformation& info, string realWord) {
	int temp = 0;

	//Determines if lost
	if (user->getLives() <= 0) {
		user->setStatus(Status::Lose);
		return false;
	}

	//Determines if win
	for (int i = 0; i < realWord.length(); i++) {
		if (info.wordProgress[i] == realWord[i]) temp++; 
	}
	if (temp == realWord.length()) {
		user->setStatus(Status::Win);
		return false;
	}

	//Continues if both fail
	return true;
}

//Function to deal with a lost
void lose(Player* user, userWordInformation& info, string realWord) {
	user->increaseLoses();

	//Resets streak if user is Competitive
	user->setStreak(0);

	cout << "Bummer... " << user->getName()<< "You lost on level " << user->getDifficulty() << ", " << user->Player::getDifficulty() << " Difficulty\n";

	if (info.lettersGuessed > 0) cout << "You had " << info.lettersGuessed << " letters guessed! " << endl;
	if (info.wordsGuessed > 0) cout << "You had " << info.wordsGuessed << " words guessed!" << endl;
	cout << "The word was " << realWord << endl;

}

//Function to deal with a win
void win(Player& user, userWordInformation& info) {
	user.increaseWins();

	//Updates streak and record
	user.setStreak(user.getStreak() + 1);
	if (user.getStreak() >= user.getRecord()) user.setRecord(user.getStreak());

	cout << "Congrats " << user.getName() <<"you won on level " << user.getDifficulty() << ", " << user.Player::getDifficulty() << " Difficulty!\n";
	cout << "You guessed the word this round in " << info.totalGuesses << " guesses!" << endl;

	if(info.lettersGuessed > 0) cout << "You had " << info.lettersGuessed << " letters guessed! " << endl;
	if (info.wordsGuessed > 0) cout << "You had " << info.wordsGuessed << " words guessed!" << endl;

}

//Play again functionality
void playAgain(Player* user, userWordInformation& info, string& realWord) {
	string choice;
	
	//Adds round stats to total stats
	user->setGuesses(user->getGuesses() + info.totalGuesses);
	user->setLetters(user->getLetters() + info.lettersGuessed);
	user->setWords(user->getWords() + info.wordsGuessed);

	//Varification to ensure they choose yes or no
	do {
		cout << "Would you like to play again? (yes or no): ";
		getline(cin, choice);
		for (int i = 0; i < choice.length(); i++) {
			choice[i] = tolower(choice[i]);
		}

	} while (!(choice == "yes" || choice == "no"));

	//Resets the game
	if (choice == "yes") {
		info.totalGuesses = 0;
		info.lettersGuessed = 0;
		info.wordsGuessed = 0;
		info.wrongProgress = 0;
		delete[] info.wordProgress;
		info.wordProgress = nullptr;
		user->setStatus(Status::Going);
		start(user, info, realWord);
	}

	//Ends game and displays game run time record
	if (choice == "no") {
		cout << "You had a total of: " << user->getWins() << " Wins,\n" <<
			user->getLoses() << " Losses,\n" <<
			user->getGuesses() << " Total Guesses,\n" <<
			user->getLetters() << " of which were Letters,\n" <<
			user->getWords() << " of which were Words.";

		//Adds extra line if user type is competitive
		if (user->getPlayerType() == PlayerType::Competitive) {
			cout << "\nYour Longest streak was: " << user->getRecord();
		}	
		cout << endl;
		exit(0);
	}

}

//Changes Difficulty of game
void difficultyChange(Player* user){
	do
	{
		string choice;
		cout << endl << "Current Difficulty is: "<< user->getDifficulty() << ", " << user->Player::getDifficulty();
		do {
			cout << " Would you like to change difficulty (1 is the lowest difficulty) (yes or no) ";
			getline(cin, choice);
			for (int i = 0; i < choice.length(); i++) {
				choice[i] = tolower(choice[i]);
			}

		} while (!(choice == "yes" || choice == "no"));

		//Which difficulty they change
		if (choice == "yes") {
			string choice2;
			do {
				cout << "\nWould you like to change word or lives difficulty? (word or lives): ";
				getline(cin, choice2);
				for (int i = 0; i < choice2.length(); i++) {
					choice2[i] = tolower(choice2[i]);
				}
			} while (!(choice2 == "lives" || choice2 == "word"));

			//Changes and resets lives
			if (choice2 == "lives") {
				int choice3;
				do {
					cout << "\nHow many lives would you like? (6, 4, or 3) ";
					cin >> choice3;
				} while (!(choice3 == 6 || choice3 == 4 || choice3 == 3));
				switch (choice3)
				{
				case(6):
					user->Player::setDifficulty(1);
					break;
				case(4):
					user->Player::setDifficulty(2);
					break;
				case(3):
					user->Player::setDifficulty(3);
					break;
				default:
					break;
				}
			}

			//Changes Word difficulty while reseting lives
			if (choice2 == "word") {
				int choice3;
				do {
					cout << "\nWhat difficulty would you like 1-3 (1 is easiest 3 is toughest) ";
					cin >> choice3;
				} while (!(choice3 >= 1 || choice3 <= 3));
				switch (choice3)
				{
				case(1):
					user->setDifficulty(1);
					break;
				case(2):
					user->setDifficulty(2);
					break;
				case(3):
					user->setDifficulty(3);
					break;
				default:
					break;
				}

			}
		}
		if (choice == "no") {
			user->Player::setDifficulty(user->Player::getDifficulty());
			break;
		}
	} while (true);
}