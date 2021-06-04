#include "MonteCarloEvolution.h"
#include "Random.h"
#include "Human.h"

MonteCarloEvolution::MonteCarloEvolution(Board* b, int _attempts, Chip _type, int i, int j)
{
	board = new Board(b);
	//cout << "here 1.1" << endl;

	attempts = _attempts;
	type = _type;
	victories = 0;
	losses = 0;

	Player* player = new Human("Human", type);
	player->setBoard(board);
	player->makeMove(i, j);
	delete player;
	//cout << "here 1.2" << endl;

}

MonteCarloEvolution::~MonteCarloEvolution()
{
	delete board;
}

void MonteCarloEvolution::test()
{
	bool stop;
	int i = 0;
	do {
		//cout << "here 1.3" << endl;

		stop = evolution();
		i++;
	} while ((i < attempts) && (!stop));
	//cout << "here 1.4" << endl;

}

bool MonteCarloEvolution::evolution()
{
	//cout << "here 1.5" << endl;

	Player* playerWhite = new Random(Chip::white);
	Player* playerBlack = new Random(Chip::black);
	Board* b = new Board(board);

	playerBlack->setBoard(board);
	playerWhite->setBoard(board);

	Player* currentPlayer;

	if (type == Chip::white)
		currentPlayer = playerBlack;
	else
		currentPlayer = playerWhite;

	bool gameOver = b->isOver();

	if (gameOver) {
		if (type == b->victory()) {
			victories = attempts;
		}
		else if (Chip::empty == b->victory()) {
			draws = attempts;
		}
		else {
			losses = attempts;
		}

		delete playerWhite;
		delete playerBlack;
		delete b;
		return true;
	}

	while (!gameOver) {
		//cout << "here 1.7" << endl;

		if (currentPlayer->analisis()) {
			//cout << "here 2.1" << endl;

			currentPlayer->makeMove(0, 0);
			//cout << "here 2.2" << endl;

			currentPlayer = (currentPlayer == playerWhite) ? playerBlack : playerWhite;
			//cout << "here 2.3" << endl;

			b->reduce();
			//cout << "here 2.4" << endl;

			gameOver = b->isOver();
			//cout << "here 2.5" << endl;

		}
		else {
			currentPlayer = (currentPlayer == playerWhite) ? playerBlack : playerWhite;
			if (!currentPlayer->analisis()) {
				gameOver = true;
				//cout << "here 1.9" << endl;

			}
		}

		//cout << "here 1.8" << endl;
	}

	if (type == b->victory()) {
		//cout << "here 1.10" << endl;

		victories++;
	}
	else if (Chip::empty == b->victory()) {
		//cout << "here 1.11" << endl;

		draws++;
	}
	else {
		//cout << "here 1.12" << endl;

		losses++;
	}
	//cout << "here 1.6" << endl;


	delete playerWhite;
	delete playerBlack;
	delete b;
	return true;
}

double MonteCarloEvolution::probebilityVictory()
{
	double numero = victories;
	return numero / attempts;
}
