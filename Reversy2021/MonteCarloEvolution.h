#pragma once
#include "pch.h"
#include "Board.h"
#include "Player.h"

class MonteCarloEvolution
{
public:
	MonteCarloEvolution(Board* b, int _attempts, Chip _type, int i, int j);
	~MonteCarloEvolution();
	void test();
	bool evolution();
	double probebilityVictory();

private:
	Board* board;
	Chip type;
	int victories, losses, draws;
	int attempts;
};

