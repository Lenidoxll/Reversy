#include "Computer.h"

Computer::Computer(string _name, Chip _type)
{
	name = _name;
	type = _type;
}

Computer::~Computer()
{
}

bool Computer::makeMove(int row, int column)
{
	return false;
}
