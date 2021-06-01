#pragma once
#include "pch.h"

class Board;
class Player;

class Manager
{
public:
	Manager();
	~Manager();
	bool init();
	void showBoard();
	void makeMove();
	bool isOver();
	void gameOver();
	bool restartGame();
	
private:
	Board* b;
	Player* playerWhite;
	Player* playerBlack;
	Player* currentPlayer;
	bool gameProcessing;
	bool canMove;

};

