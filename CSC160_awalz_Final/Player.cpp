#include "Player.h"

Player::Player()
{
    lives = 6;
    words = 0;
    letters = 0;
    guesses = 0;
    wins = 0;
    loses = 0;
    diff = 1;
    status = Status::Going;
}

Player Player::operator--(int u)
{
    Player temp = *this;

    lives--;
    return temp;
}

Player Player::operator--()
{
    --lives;
    return *this;
}


void Player::setDifficulty(int d)
{
    diff = d;
    switch (diff)
    {
    case(1):
        lives = 6;
        break;
    case(2):
        lives = 4;
        break;
    case(3):
        lives = 3;
        break;
    default:
        break;
    }
}

std::string Player::getName() const
{
    return "";
}

int Player::getRecord() const
{
    return 0;
}

int Player::getStreak() const
{
    return 0;
}

void Player::setName(std::string)
{
}

void Player::setRecord(int)
{
}

void Player::setStreak(int)
{
}
