#pragma once

#include "Player.h"
class Casual :
    public Player
{
public:
    Casual();

    //Setters
    virtual void setName(std::string s) { name = s + " "; }
    virtual void setDifficulty(int d2);
    //Getters
    virtual std::string getName() const { return name; }
    virtual int getDifficulty() const;

private:
    std::string name;
    int difficulty;
};

