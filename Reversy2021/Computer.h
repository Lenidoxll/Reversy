#pragma once
#include "Player.h"
#include "Board.h"

class Computer :
    public Player
{
public:
    Computer(string _name, Chip _type);
    ~Computer();
    bool makeMove(int row = 0, int column = 0);
};

