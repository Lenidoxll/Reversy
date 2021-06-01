#pragma once
#include "pch.h"

class Board;

class Player
{
public:
	Player(string _name, Chip _type);
	~Player();
	string getName();
	void setBoard(Board* b);
	bool makeMove(int i, int j);
	Chip getType();
	bool analisis();
	//void showMatrix(bool** matrix);

private:
	bool columnDown(int i, int j, bool change = true);
	bool columnUp(int i, int j, bool change = true);
	bool rowLeft(int i, int j, bool change = true);
	bool rowRight(int i, int j, bool change = true);
	bool diagDownLeft(int i, int j, bool change = true);
	bool diagUpLeft(int i, int j, bool change = true);
	bool diagUpRight(int i, int j, bool change = true);
	bool diagDownRight(int i, int j, bool change = true);
	/*bool** enemyViceHorizontal();
	bool** enemyViceVertical();
	int** enemyVice(bool** verticalMatrix, bool** horizontalMatrix);*/

	string name;
	Chip type;
	Board* board;
};

