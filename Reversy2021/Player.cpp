#include "Player.h"
#include "Board.h"

bool** createMatrix(int size) {
	bool** matrix = new bool* [size];
	for (int i = 0; i < size; i++)
		matrix[i] = new bool[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			matrix[i][j] = false;

	return matrix;
}

template <typename T>
void destroyMatrix(T** matrix, int size) {
	for (int i = 0; i < size; i++)
		delete[] matrix[i];
	delete[] matrix;
}

template <typename T>
void showMatrix(T** matrix, int size)
{
	cout << "Матрица ->" << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << matrix[i][j] << ", ";
		}
		cout << endl;
	}
}

Player::Player()
{
	name = "Zero";
	type = Chip::empty;
}

Player::~Player()
{
}

string Player::getName()
{
	return name;
}

void Player::setBoard(Board* b)
{
	board = b;
}

bool Player::makeMove(int i, int j)
{
	return false;
}

Chip Player::getType()
{
	return type;
}

bool Player::analisis()
{
	/*bool** horizontalMatrix = enemyViceHorizontal();
	bool** verticalMatrix = enemyViceVertical();

	int** enemyMatrix = enemyVice(verticalMatrix, horizontalMatrix);

	destroyMatrix(horizontalMatrix, board->getSize());
	destroyMatrix(verticalMatrix, board->getSize());
	destroyMatrix(enemyMatrix, board->getSize());*/

	int i = 0, j = 0;
	bool enough = false;
	bool ok = false;

	do {
		if (j == board->getSize()) {
			j = 0;
			i++;
		}

		if (i == board->getSize()) {
			enough = true;
		}

		if (board->getChip(i, j) == Chip::empty) 
			if ((columnDown(i, j, false)) || (columnUp(i, j, false)) || (rowLeft(i, j, false)) || (rowRight(i, j, false)) || (diagDownLeft(i, j, false))
				|| (diagUpLeft(i, j, false)) || (diagUpRight(i, j, false)) || (diagDownRight(i, j, false))) {
				enough = true;
				ok = true;
			}

		j++;
	} while (!enough);

	if (ok)
		return true;

	return false;
}

bool Player::isHuman()
{
	return false;
}

bool Player::control(int i, int j)
{
	if (board->control(i, j)) {
		bool cd = columnDown(i, j), cu = columnUp(i, j), rl = rowLeft(i, j), rr = rowRight(i, j), ddl = diagDownLeft(i, j),
			dul = diagUpLeft(i, j), dur = diagUpRight(i, j), ddr = diagDownRight(i, j);

		if (cd || cu || rl || rr || ddl || dul || dur || ddr) {
			return true;
		}
	}
	return false;
}

bool Player::columnDown(int i, int j, bool change)
{
	bool enemy = false;
	bool vice = false;
	bool begin = false;
	int ivice = i;

	do {
		ivice++;
		//cout << ivice << endl;
		if (ivice < board->getSize()) {
			if (!begin) {
				if ((board->getChip(ivice, j) != type) && (board->getChip(ivice, j) != Chip::empty)) {
					begin = true;
					enemy = true;
				}
			}
			else {
				if ((board->getChip(ivice, j) == type) && (begin == true) && (enemy == true)) {
					enemy = false;
					vice = true;
					begin = false;
				}
				else if ((board->getChip(ivice, j) == Chip::empty) && (begin == true) && (enemy == true)) {
					enemy = false;
					begin = false;
				}
			}
		}
	} while (begin && ivice < board->getSize());

	if (vice) {
		if (change)
			while (ivice != i) {
				board->setChip(ivice, j, type);
				ivice--;
			}
		return true;
	}

	return false;
}

bool Player::columnUp(int i, int j, bool change)
{
	bool enemy = false;
	bool vice = false;
	bool begin = false;
	int ivice = i;

	do {
		ivice--;
		//cout << ivice << endl;
		if (ivice >= 0) {
			if (!begin) {
				if ((board->getChip(ivice, j) != type) && (board->getChip(ivice, j) != Chip::empty)) {
					begin = true;
					enemy = true;
				}
			}
			else {
				if ((board->getChip(ivice, j) == type) && (begin == true) && (enemy == true)) {
					enemy = false;
					vice = true;
					begin = false;
				}
				else if ((board->getChip(ivice, j) == Chip::empty) && (begin == true) && (enemy == true)) {
					enemy = false;
					begin = false;
				}
			}
		}
	} while (begin && ivice >= 0);

	if (vice) {
		if (change)
			while (ivice != i) {
				board->setChip(ivice, j, type);
				ivice++;
			}
		return true;
	}

	return false;
}

bool Player::rowLeft(int i, int j, bool change)
{
	bool enemy = false;
	bool vice = false;
	bool begin = false;
	int jvice = j;

	do {
		jvice--;
		//cout << jvice << endl;
		if (jvice >= 0) {
			if (!begin) {
				if ((board->getChip(i, jvice) != type) && (board->getChip(i, jvice) != Chip::empty)) {
					begin = true;
					enemy = true;
				}
			}
			else {
				if ((board->getChip(i, jvice) == type) && (begin == true) && (enemy == true)) {
					enemy = false;
					vice = true;
					begin = false;
				}
				else if ((board->getChip(i, jvice) == Chip::empty) && (begin == true) && (enemy == true)) {
					enemy = false;
					begin = false;
				}
			}
		}
	} while (begin && jvice >= 0);

	if (vice) {
		if (change)
			while (jvice != j) {
				board->setChip(i, jvice, type);
				jvice++;
			}
		return true;
	}

	return false;
}

bool Player::rowRight(int i, int j, bool change)
{
	bool enemy = false;
	bool vice = false;
	bool begin = false;
	int jvice = j;

	do {
		jvice++;
		//cout << jvice << endl;
		if (jvice < board->getSize()) {
			if (!begin) {
				if ((board->getChip(i, jvice) != type) && (board->getChip(i, jvice) != Chip::empty)) {
					begin = true;
					enemy = true;
				}
			}
			else {
				if ((board->getChip(i, jvice) == type) && (begin == true) && (enemy == true)) {
					enemy = false;
					vice = true;
					begin = false;
				}
				else if ((board->getChip(i, jvice) == Chip::empty) && (begin == true) && (enemy == true)) {
					enemy = false;
					begin = false;
				}
			}
		}
	} while (begin && jvice < board->getSize());

	if (vice) {
		if (change)
			while (jvice != j) {
				board->setChip(i, jvice, type);
				jvice--;
			}
		return true;
	}

	return false;
}

bool Player::diagDownLeft(int i, int j, bool change)
{
	bool enemy = false;
	bool vice = false;
	bool begin = false;
	int ivice = i;
	int jvice = j;

	do {
		ivice++;
		jvice--;
		//cout << ivice << " " << jvice << endl;
		if ((ivice < board->getSize()) && (jvice >= 0)) {
			if (!begin) {
				if ((board->getChip(ivice, jvice) != type) && (board->getChip(ivice, jvice) != Chip::empty)) {
					begin = true;
					enemy = true;
				}
			}
			else {
				if ((board->getChip(ivice, jvice) == type) && (begin == true) && (enemy == true)) {
					enemy = false;
					vice = true;
					begin = false;
				}
				else if ((board->getChip(ivice, jvice) == Chip::empty) && (begin == true) && (enemy == true)) {
					enemy = false;
					begin = false;
				}
			}
		}
	} while (begin && ivice < board->getSize() && jvice >= 0);

	if (vice) {
		if (change)
			while (ivice != i && jvice != j) {
				board->setChip(ivice, jvice, type);
				ivice--;
				jvice++;
			}
		return true;
	}

	return false;
}

bool Player::diagUpLeft(int i, int j, bool change)
{
	bool enemy = false;
	bool vice = false;
	bool begin = false;
	int ivice = i;
	int jvice = j;

	do {
		ivice--;
		jvice--;
		//cout << ivice << " " << jvice << endl;
		if ((ivice >= 0) && (jvice >= 0)) {
			if (!begin) {
				if ((board->getChip(ivice, jvice) != type) && (board->getChip(ivice, jvice) != Chip::empty)) {
					begin = true;
					enemy = true;
				}
			}
			else {
				if ((board->getChip(ivice, jvice) == type) && (begin == true) && (enemy == true)) {
					enemy = false;
					vice = true;
					begin = false;
				}
				else if ((board->getChip(ivice, jvice) == Chip::empty) && (begin == true) && (enemy == true)) {
					enemy = false;
					begin = false;
				}
			}
		}
	} while (begin && ivice >= 0 && jvice >= 0);

	if (vice) {
		if (change)
			while (ivice != i && jvice != j) {
				board->setChip(ivice, jvice, type);
				ivice++;
				jvice++;
			}
		return true;
	}

	return false;
}

bool Player::diagUpRight(int i, int j, bool change)
{
	bool enemy = false;
	bool vice = false;
	bool begin = false;
	int ivice = i;
	int jvice = j;

	do {
		ivice--;
		jvice++;
		//cout << ivice << " " << jvice << endl;
		if ((ivice >= 0) && (jvice < board->getSize())) {
			if (!begin) {
				if ((board->getChip(ivice, jvice) != type) && (board->getChip(ivice, jvice) != Chip::empty)) {
					begin = true;
					enemy = true;
				}
			}
			else {
				if ((board->getChip(ivice, jvice) == type) && (begin == true) && (enemy == true)) {
					enemy = false;
					vice = true;
					begin = false;
				}
				else if ((board->getChip(ivice, jvice) == Chip::empty) && (begin == true) && (enemy == true)) {
					enemy = false;
					begin = false;
				}
			}
		}
	} while (begin && ivice >= 0 && jvice < board->getSize());

	if (vice) {
		if (change)
			while (ivice != i && jvice != j) {
				board->setChip(ivice, jvice, type);
				ivice++;
				jvice--;
			}
		return true;
	}

	return false;
}

bool Player::diagDownRight(int i, int j, bool change)
{
	bool enemy = false;
	bool vice = false;
	bool begin = false;
	int ivice = i;
	int jvice = j;

	do {
		ivice++;
		jvice++;
		//cout << ivice << " " << jvice << endl;
		if ((ivice < board->getSize()) && (jvice < board->getSize())) {
			if (!begin) {
				if ((board->getChip(ivice, jvice) != type) && (board->getChip(ivice, jvice) != Chip::empty)) {
					begin = true;
					enemy = true;
				}
			}
			else {
				if ((board->getChip(ivice, jvice) == type) && (begin == true) && (enemy == true)) {
					enemy = false;
					vice = true;
					begin = false;
				}
				else if ((board->getChip(ivice, jvice) == Chip::empty) && (begin == true) && (enemy == true)) {
					enemy = false;
					begin = false;
				}
			}
		}
	} while (begin && ivice < board->getSize() && jvice < board->getSize());

	if (vice) {
		if (change)
			while (ivice != i && jvice != j) {
				board->setChip(ivice, jvice, type);
				ivice--;
				jvice--;
			}
		return true;
	}

	return false;
}

//bool** Player::enemyViceHorizontal()
//{
//	bool** matrix = createMatrix(board->getSize());
//
//	for (int i = 0; i < board->getSize(); i++) {
//		//cout << "\tHorizontal -> " << i << endl;
//		bool begin = false;
//		bool me = false;
//		vector <int> first, second;
//		for (int j = 0; j < board->getSize(); j++) {
//			if (!begin) {
//				if (board->getChip(i, j) == type) {
//					me = true;
//					//cout << "here 1" << endl;
//				}
//				else if (board->getChip(i, j) == Chip::empty) {
//					me = false;
//					//cout << "here 2" << endl;
//
//				}
//				else if ((board->getChip(i, j) != type) && (board->getChip(i, j) != Chip::empty) && (me == true)) {
//					begin = true;
//					first.push_back(j);
//					//cout << "here 3" << endl;
//				}
//				//cout << "here 4" << endl;
//			}
//			else {
//				if (board->getChip(i, j) == Chip::empty) {
//					me = false;
//					begin = false;
//					first.clear();
//					//cout << "here 5" << endl;
//				}
//				else if (board->getChip(i, j) == type) {
//					begin = false;
//					second.push_back(j);
//					//cout << "here 6" << endl;
//				}
//				//cout << "here 7" << endl;
//			}
//
//			if (!second.empty()) {
//				for (int k = first[0]; k < second[0]; k++)
//					matrix[i][k] = true;
//				first.clear();
//				second.clear();
//			}
//		}
//	}
//
//	//showMatrix(matrix);
//
//	return matrix;
//}
//
//bool** Player::enemyViceVertical()
//{
//	bool** matrix = createMatrix(board->getSize());
//
//	for (int j = 0; j < board->getSize(); j++) {
//		//cout << "\tVertical -> " << j << endl;
//		bool begin = false;
//		bool me = false;
//		vector <int> first, second;
//		for (int i = 0; i < board->getSize(); i++) {
//			if (!begin) {
//				if (board->getChip(i, j) == type) {
//					me = true;
//					//cout << "here 1" << endl;
//				}
//				else if (board->getChip(i, j) == Chip::empty) {
//					me = false;
//					//cout << "here 2" << endl;
//
//				}
//				else if ((board->getChip(i, j) != type) && (board->getChip(i, j) != Chip::empty) && (me == true)) {
//					begin = true;
//					first.push_back(i);
//					//cout << "here 3" << endl;
//				}
//				//cout << "here 4" << endl;
//			}
//			else {
//				if (board->getChip(i, j) == Chip::empty) {
//					me = false;
//					begin = false;
//					first.clear();
//					//cout << "here 5" << endl;
//				}
//				else if (board->getChip(i, j) == type) {
//					begin = false;
//					second.push_back(i);
//					//cout << "here 6" << endl;
//				}
//				//cout << "here 7" << endl;
//			}
//
//			if (!second.empty()) {
//				for (int k = first[0]; k < second[0]; k++)
//					matrix[k][j] = true;
//				first.clear();
//				second.clear();
//			}
//		}
//	}
//
//	//showMatrix(matrix);
//
//	return matrix;
//}
//
//int** Player::enemyVice(bool** verticalMatrix, bool** horizontalMatrix)
//{
//	int** matrix = new int* [board->getSize()];
//	for (int i = 0; i < board->getSize(); i++)
//		matrix[i] = new int[board->getSize()];
//
//	for (int i = 0; i < board->getSize(); i++)
//		for (int j = 0; j < board->getSize(); j++) {
//			if ((verticalMatrix[i][j]) && (horizontalMatrix[i][j])) {
//				matrix[i][j] = 2;
//			}
//			else if ((!verticalMatrix[i][j]) && (!horizontalMatrix[i][j])) {
//				matrix[i][j] = 0;
//			}
//			else {
//				matrix[i][j] = 1;
//			}
//		}
//
//	showMatrix(matrix, board->getSize());
//
//	return matrix;
//}