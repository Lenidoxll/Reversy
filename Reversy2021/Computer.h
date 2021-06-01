#pragma once
#include "Player.h"
#include "Board.h"

class Computer :
    public Player
{
public:
    Computer(string _name, Chip _type);
    virtual ~Computer();
    virtual bool makeMove(int row = 0, int column = 0);
    virtual bool isHuman();

protected:
    bool control(int i, int j);
};

