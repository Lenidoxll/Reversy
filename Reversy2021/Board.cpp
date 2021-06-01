#include "Board.h"

Board::Board()
{
	size = 8;
	chips = new Chip * [size];
	for (int i = 0; i < size; i++)
		chips[i] = new Chip[size];

	start();
}

Board::~Board()
{
	for (int i = 0; i < size; i++)
		delete[] chips[i];
	delete[] chips;
}

void Board::start()
{
	freeChips = size * size;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (((i == size / 2) && (j == size / 2)) || ((i == (size / 2 - 1)) && (j == (size / 2 - 1))))
				chips[i][j] = Chip::white;
			else if (((i == size / 2) && (j == (size / 2 - 1))) || ((i == (size / 2 - 1)) && (j == size / 2)))
				chips[i][j] = Chip::black;
			else
				chips[i][j] = Chip::empty;
		}
}

//void Board::show()
//{
//	for (int i = 0; i <= size; i++) {
//		for (int j = 0; j < size; j++) {
//			if (i == 0) {
//				if (j == 0)
//					cout << "   ";
//				cout << " " << j << " ";
//			}
//			else {
//				if (j == 0)
//					cout << " " << i - 1 << " ";
//				switch (chips[i - 1][j]) {
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

void Board::setChip(int i, int j, Chip chip)
{
	chips[i][j] = chip;
}

bool Board::control(int i, int j)
{
	if ((i < 0) || (i > size - 1) || (j < 0) || (j > size - 1))
		return false;
	return (chips[i][j] == Chip::empty);
}

Chip Board::getChip(int i, int j)
{
	if ((i < 0) || (i > size - 1) || (j < 0) || (j > size - 1))
		return Chip::empty;
	return chips[i][j];
}

int Board::getSize()
{
	return size;
}

bool Board::isOver()
{
	if (freeChips <= 0)
		return true;
	return false;
}

Chip Board::victory()
{
	int white = 0, black = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++) {
			if (chips[i][j] == Chip::black)
				black++;
			else
				white++;
		}

	if (black > white)
		return Chip::black;
	else if (white > black)
		return Chip::white;
	else
		return Chip::empty;
}

bool Board::reduce()
{
	if (freeChips >= 0) {
		freeChips--;
		return true;
	}
	return false;
}


