#include "Manager.h"
#include "Board.h"
#include "Player.h"

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

bool Manager::init()
{
	string name;
	b = new Board();
	
	cout << " ������� ��� ������ �� ����� -> ";
	getline(cin, name);
	playerWhite = new Player(name, Chip::white);

	cout << " ������� ��� ������ �� ������ -> ";
	getline(cin, name);
	playerBlack = new Player(name, Chip::black);

	playerWhite->setBoard(b);
	playerBlack->setBoard(b);
	currentPlayer = playerBlack;
	
	canMove = true;

	return true;
}

void Manager::showBoard()
{
	for (int i = 0; i <= b->getSize(); i++) {
		for (int j = 0; j < b->getSize(); j++) {
			if (i == 0) {
				if (j == 0)
					cout << "   ";
				cout << " " << j << " ";
			}
			else {
				if (j == 0)
					cout << " " << i - 1 << " ";
				Chip chip = b->getChip(i - 1, j);
				switch (chip) {
				case Chip::white:
					cout << " O ";
					break;
				case Chip::black:
					cout << " X ";
					break;
				case Chip::empty:
					cout << " - ";
					break;
				}
			}
		}
		cout << endl;
	}
}

void Manager::makeMove()
{
	showBoard();

	if (currentPlayer->analisis()) {
		int row, col;
		cout << "����� " << currentPlayer->getName() << ", ��� ���..." << endl;
		cout << "������� ������ -> ";
		cin >> row;
		cout << "������� ������� -> ";
		cin >> col;
		if (!currentPlayer->makeMove(row, col)) {
			cout << "������������ ���. ���������� ��� ���." << endl;
			//showBoard();
		}
		else {
			currentPlayer = (currentPlayer == playerWhite) ? playerBlack : playerWhite;
			b->reduce();
		}
	}
	else {
		cout << "����� " << currentPlayer->getName() << ", � ��� ��� ��������� �����." << endl;
		currentPlayer = (currentPlayer == playerWhite) ? playerBlack : playerWhite;
		if (!currentPlayer->analisis()) {
			cout << "����� " << currentPlayer->getName() << ", � ��� ��� ��������� �����." << endl;
			canMove = false;
		}
	}
	
}

bool Manager::isOver()
{
	if (!canMove)
		return true;
	return b->isOver();
}

void Manager::gameOver()
{
	Chip win = b->victory();

	if (win == Chip::black)
		cout << "������� ����� " << playerBlack->getName() << "!" << endl;
	else if (win == Chip::white)
		cout << "������� ����� " << playerWhite->getName() << "!" << endl;
	else
		cout << "�����!" << endl;
}

bool Manager::restartGame()
{
	cout << "������ ���� ������? ������� 1, ���� ��, � 0, ���� ��� -->\t";
	bool again;
	cin >> again;
	if (again) {
		b->start();
		currentPlayer = playerBlack;
		canMove = true;
		return true;
	}
	cout << "����� ����." << endl;
	return false;
}
