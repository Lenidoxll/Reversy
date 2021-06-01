#include "Human.h"

Human::Human(string _name, Chip _type)
{
	name = _name;
	type = _type;
}

Human::~Human()
{
}

bool Human::makeMove(int i, int j)
{
	if (board->control(i, j)) {
		bool cd = columnDown(i, j), cu = columnUp(i, j), rl = rowLeft(i, j), rr = rowRight(i, j), ddl = diagDownLeft(i, j),
			dul = diagUpLeft(i, j), dur = diagUpRight(i, j), ddr = diagDownRight(i, j);

		if (cd || cu || rl || rr || ddl || dul || dur || ddr) {
			board->setChip(i, j, type);
			return true;
		}
	}
	return false;
}
