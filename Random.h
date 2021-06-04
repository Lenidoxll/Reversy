#pragma once
#include "Player.h"
#include "Board.h"

class Random :
    public Player
{
public:
    Random(Chip _type);
    virtual ~Random();
    virtual bool makeMove(int row = 0, int column = 0);
    virtual bool isHuman();

protected:
    virtual bool control(int i, int j);

private:
    bool variants(vector<int>& i, vector<int>& j);
};

