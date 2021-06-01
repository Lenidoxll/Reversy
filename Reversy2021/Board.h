#pragma once
#include "pch.h"

class Board
{
public:
	Board();
	~Board();

	void start();
	//void show();
	void setChip(int i, int j, Chip chip);
	bool control(int i, int j);
	Chip getChip(int i, int j);
	int getSize();
	bool isOver();
	Chip victory();
	bool reduce();

private:
	Chip** chips;
	int size;
	int freeChips;
};

