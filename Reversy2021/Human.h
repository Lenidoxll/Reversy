#pragma once
#include "Player.h"
#include "Board.h"

class Human :
    public Player
{
public:
    Human(string _name, Chip _type);
    virtual ~Human();
    virtual bool makeMove(int i, int j);
};

