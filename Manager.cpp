#include "Manager.h"
#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"

Manager::Manager()
{
	gameProcessing = true;
}

Manager::~Manager()
{
	delete b;
	delete playerWhite;
	delete playerBlack;
}

bool Manager::init(string nameWhite, string nameBlack, bool humanWhite, bool humanBlack)
{
	b = new Board();
	
    if (!humanWhite)
        playerWhite = new Computer(nameWhite, Chip::white);
	else
        playerWhite = new Human(nameWhite, Chip::white);

    if (!humanBlack)
        playerBlack = new Computer(nameBlack, Chip::black);
	else
        playerBlack = new Human(nameBlack, Chip::black);

	playerWhite->setBoard(b);
	playerBlack->setBoard(b);
	currentPlayer = playerBlack;
	
	canMove = true;

	return true;
}

//void Manager::showBoard()
//{
//	for (int i = 0; i <= b->getSize(); i++) {
//		for (int j = 0; j < b->getSize(); j++) {
//			if (i == 0) {
//				if (j == 0)
//					cout << "   ";
//				cout << " " << j << " ";
//			}
//			else {
//				if (j == 0)
//					cout << " " << i - 1 << " ";
//				Chip chip = b->getChip(i - 1, j);
//				switch (chip) {
//				case Chip::white:
//					cout << " O ";
//					break;
//				case Chip::black:
//					cout << " X ";
//					break;
//				case Chip::empty:
//					cout << " - ";
//					break;
//				}
//			}
//		}
//		cout << endl;
//	}
//}

int Manager::makeMove(int ilast, int jlast)
{
    //showBoard();

	if (currentPlayer->analisis()) {
		int row = 0, col = 0;

		if (currentPlayer->isHuman()) {
            row = ilast;
            col = jlast;
		}
		if (!currentPlayer->makeMove(row, col)) {
            //cout << "Недопустимый ход. Попробуйте еще раз." << endl;
            return 1;
			//showBoard();
		}
		else {
			currentPlayer = (currentPlayer == playerWhite) ? playerBlack : playerWhite;
			b->reduce();
		}
	}
	else {
        //cout << "Игрок " << currentPlayer->getName() << ", у Вас нет доступных ходов." << endl;
		currentPlayer = (currentPlayer == playerWhite) ? playerBlack : playerWhite;
		if (!currentPlayer->analisis()) {
            //cout << "Игрок " << currentPlayer->getName() << ", у Вас нет доступных ходов." << endl;
			canMove = false;
            return 5;
		}
        return 2;
	}
    return 0;
}

bool Manager::isOver()
{
	if (!canMove)
		return true;
	return b->isOver();
}

int Manager::gameOver(Chip& win)
{
    win = b->victory();

	if (win == Chip::black)
        return 3;
        //cout << "Победил игрок " << playerBlack->getName() << "!" << endl;
	else if (win == Chip::white)
        return 3;
        //cout << "Победил игрок " << playerWhite->getName() << "!" << endl;
	else
        return 4;
        //cout << "Ничья!" << endl;
}

bool Manager::restartGame(string nameWhite, string nameBlack, bool humanWhite, bool humanBlack)
{
//	cout << "Начать игру заново? Введите 1, если да, и 0, если нет -->\t";
//	bool again;
//	cin >> again;
//	if (again) {
    b->start();

    currentPlayer = nullptr;

    delete playerWhite;
    delete playerBlack;



    if (!humanWhite)
        playerWhite = new Computer(nameWhite, Chip::white);
    else
        playerWhite = new Human(nameWhite, Chip::white);

    if (!humanBlack)
        playerBlack = new Computer(nameBlack, Chip::black);
    else
        playerBlack = new Human(nameBlack, Chip::black);

    playerBlack->setBoard(b);
    playerWhite->setBoard(b);

    currentPlayer = playerBlack;
    canMove = true;
    return true;
}

Chip **Manager::getChips()
{
    return b->getChips();
}

Chip Manager::getChip(int i, int j)
{
    return b->getChip(i, j);
}

bool Manager::isCurrentPlayerBlack()
{
    if (currentPlayer == playerBlack)
        return true;
    return false;
}

bool Manager::isCurrentPlayerHuman()
{
    return currentPlayer->isHuman();
}

int Manager::getLast_i()
{
    return currentPlayer->getLast_i();
}

int Manager::getLast_j()
{
    return currentPlayer->getLast_j();
}
