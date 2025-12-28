#pragma once

#include <iostream>
#include "Status.h"

class Player
{
public:
	Player();

	//Operator Overload
	//post decreament
	Player operator--(int u);

	//Pre decreament
	Player operator--();

	//Getters
	int getLives() const { return lives; }
	int getGuesses() const { return guesses; }
	int getWords() const { return words; }
	int getLetters() const { return letters; }
	int getWins() const { return wins; }
	int getLoses() const { return loses; }


	Status getStatus() const {return status;}
	PlayerType getPlayerType() const { return type; }
	virtual int getDifficulty() const { return diff; }


	//Setters
	void setLives(int l) { lives = l; }
	void setGuesses(int g) { guesses = g; }
	void setWords(int w) { words = w; }
	void setLetters(int l) { letters = l; }
	void setWins(int w) { wins = w; }
	void setLoses(int l) { loses = l; }

	void setStatus(Status s) { status = s; }
	virtual void setDifficulty(int d);
	void setType(PlayerType t) { type = t; }


	//Other Functions
	void increaseLoses() { loses++; }
	void increaseWins() { wins++; }


	virtual std::string getName() const;
	virtual int getRecord() const;
	virtual int getStreak() const;

	virtual void setName(std::string);
	virtual void setRecord(int);
	virtual void setStreak(int);


private:
	int lives;

	//comeplete word guesses
	int words;

	//letter guesses
	int letters;

	//total guesses
	int guesses;

	int wins;
	int loses;
	int diff;
	Status status;
	PlayerType type;
};

