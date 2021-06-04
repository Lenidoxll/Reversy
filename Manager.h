#pragma once
#include "pch.h"

class Board;
class Player;

class Manager
{
public:
	Manager();
	~Manager();
    bool init(string nameWhite, string nameBlack, bool humanWhite, bool humanBlack);
    //void showBoard();
    int makeMove(int ilast, int jlast);
	bool isOver();
    int gameOver(Chip& win);
    bool restartGame(string nameWhite, string nameBlack, bool humanWhite, bool humanBlack);
    Chip** getChips();
    Chip getChip (int i, int j);
    bool isCurrentPlayerBlack();
    bool isCurrentPlayerHuman();
    int getLast_i();
    int getLast_j();

private:
	Board* b;
	Player* playerWhite;
	Player* playerBlack;
	Player* currentPlayer;
	bool gameProcessing;
	bool canMove;

};

