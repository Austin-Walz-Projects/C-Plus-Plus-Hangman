#include "Competitive.h"

Competitive::Competitive()
{
	record = 0;
	streak = 0;
	difficulty = 1;
	Player::setType(PlayerType::Competitive);
}

int Competitive::getDifficulty() const
{
	return difficulty;
}

void Competitive::setDifficulty(int d2)
{
	
	difficulty = d2;
}
