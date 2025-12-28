#include "Casual.h"

Casual::Casual()
{
	name = "John Doe";
	difficulty = 1;
	Player::setType(PlayerType::Casual);
}

void Casual::setDifficulty(int d2)
{
	
	difficulty = d2;
}

int Casual::getDifficulty() const
{
	return difficulty;
}
