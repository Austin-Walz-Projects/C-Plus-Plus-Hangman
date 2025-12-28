#pragma once

#include "Player.h"
class Competitive :
    public Player
{
public:
    Competitive();

    //Getters
    virtual int getRecord() const { return record; }
    virtual int getStreak() const { return streak; }
    virtual int getDifficulty() const;

    //Setters
    virtual void setRecord(int r) { record = r; }
    virtual void setStreak(int s) { streak = s; }
    virtual void setDifficulty(int d2);

    //Other
    void increaseStreak() { streak++; }

private:
    int record;
    int streak;
    int difficulty;
};

