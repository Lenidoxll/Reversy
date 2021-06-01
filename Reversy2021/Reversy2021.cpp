#include "pch.h"
#include "Manager.h"

int main()
{
	setlocale(LC_ALL, "ru");
	Manager m;
	bool game = true;
	if (!m.init()) {
		cout << "Неверные данные..." << endl;
		return 0;
	}

	while (game) {
		while (!m.isOver())
			m.makeMove();
		m.gameOver();
		game = m.restartGame();
	}
	return 0;
}