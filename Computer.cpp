#include "Computer.h"
#include "MonteCarloEvolution.h"

Computer::Computer(string _name, Chip _type)
{
	name = _name;
	type = _type;
}

Computer::~Computer()
{
}

bool Computer::makeMove(int, int)
{

	int maini = 0, mainj = 0;
	double mainvictory = -1;
	for (int i = 0; i < board->getSize(); i++) {
		for (int j = 0; j < board->getSize(); j++) {
            //cout << "i = " << i << ", j = " << j << endl;
			if (control(i, j)) {
				//cout << "here 1" << endl;
				MonteCarloEvolution mtc(board, 100, type, i, j);
				mtc.test();
				if (mainvictory <= mtc.probebilityVictory()) {
					//cout << "here 2" << endl;
					maini = i;
					mainj = j;
					mainvictory = mtc.probebilityVictory();
				}
			}
		}
	}

	//cout << "here 3" << endl;

	int i = maini, j = mainj;

	if (board->control(i, j)) {
		//cout << "here 4" << endl;

		bool cd = columnDown(i, j), cu = columnUp(i, j), rl = rowLeft(i, j), rr = rowRight(i, j), ddl = diagDownLeft(i, j),
			dul = diagUpLeft(i, j), dur = diagUpRight(i, j), ddr = diagDownRight(i, j);

		if (cd || cu || rl || rr || ddl || dul || dur || ddr) {
			board->setChip(i, j, type);
            ilast = i;
            jlast = j;
			return true;
		}
	}

    ilast = -1;
    jlast = -1;
    //cout << "Error!" << endl;
	return false;
}

bool Computer::isHuman()
{
    return false;
}

int Computer::getLast_i()
{
    return ilast;
}

int Computer::getLast_j()
{
    return jlast;
}

bool Computer::control(int i, int j)
{
	if (board->control(i, j)) {
		//cout << "here 5" << endl;

		if ((columnDown(i, j, false)) || (columnUp(i, j, false)) || (rowLeft(i, j, false)) || (rowRight(i, j, false)) || (diagDownLeft(i, j, false))
			|| (diagUpLeft(i, j, false)) || (diagUpRight(i, j, false)) || (diagDownRight(i, j, false))) {
				return true;
		}
	}
	//cout << "here 6" << endl;

	return false;
}
