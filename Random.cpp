#include "Random.h"

Random::Random(Chip _type)
{
	name = "Random";
	type = _type;
}

Random::~Random()
{
}

bool Random::makeMove(int row, int column)
{
	unsigned int i, j;

	vector<int> iv, jv;

	if (!variants(iv, jv))
		return false;

	int numbers = iv.size();

	int para = (unsigned int)(rand() % numbers);
	i = iv[para];
	j = jv[para];

	bool cd = columnDown(i, j), cu = columnUp(i, j), rl = rowLeft(i, j), rr = rowRight(i, j), ddl = diagDownLeft(i, j),
		dul = diagUpLeft(i, j), dur = diagUpRight(i, j), ddr = diagDownRight(i, j);
	board->setChip(i, j, type);
	return true;
}

bool Random::control(int i, int j)
{
	if (board->control(i, j)) {
		//cout << "here 3.1!!!" << endl;

		if ((columnDown(i, j, false)) || (columnUp(i, j, false)) || (rowLeft(i, j, false)) || (rowRight(i, j, false)) || (diagDownLeft(i, j, false))
			|| (diagUpLeft(i, j, false)) || (diagUpRight(i, j, false)) || (diagDownRight(i, j, false))) {
			return true;
		}
	}
	//cout << "here 3.2" << endl;

	return false;
}

bool Random::variants(vector<int>& iv, vector<int>& jv)
{
	for (int i = 0; i < board->getSize(); i++) {
		for (int j = 0; j < board->getSize(); j++) {
			if (control(i, j)) {
				iv.push_back(i);
				jv.push_back(j);
			}
		}
	}

	if (iv.size() > 0)
		return true;

	return false;
}

bool Random::isHuman()
{
	return false;
}
