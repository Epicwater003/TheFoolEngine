#include <iostream>
#include <iterator>
#include <algorithm>
#include <random>
#include <list>
#include "include/Card.h"
#include "include/Deck.h"
#include "include/Table.h"
#include "include/Player.h"

using namespace std;
using namespace thefoolengine;

int main() {

	auto seed = random_device()();
	std::mt19937 re(seed);

	Table table;
	auto egc1 = std::make_shared<GreedyComputer>(re);

	auto gc1 = std::make_shared<GreedyComputer>(re);

	auto rc1 = std::make_shared<RandomComputer>(re);

	int64_t a = 0;
	int64_t af = 0;
	int64_t b = 0;
	int64_t bf = 0;
	int64_t c = 0;
	int64_t cf = 0;
	table.tableNewGame = [&](auto player) {
		if (player == egc1)
			++af;
		if (player == gc1)
			++bf;
		if (player == rc1)
			++cf;
		};
	table.tableLeave = [&](auto player) {
		if (player == egc1) {
			++a;
		}
		if (player == gc1) {
			++b;
		}
		if (player == rc1) {
			++c;
		}
		};
	table.tableGameEnd = [&](auto player) {
		if (!player) {
			--a;
			--b;
			--c;
		}
		};
	//TODO:: figure out why player position in list affects on win rate...
	for (int i = 0; i < 3333; ++i) {
		seed = random_device()();
		for (int o = 0; o < 4; ++o) {
			//table.addPlayer(rc1);
			table.addPlayer(egc1);
			table.addPlayer(gc1);
			table.newGame(seed);
			while (!table.gameEnd())
			{
				table.doTurn();
			}
		}
	}

	cout << "egc = " << a << ", f = " << af << endl;
	cout << "gc  = " << b << ", f = " << bf << endl;
	cout << "rc  = " << c << ", f = " << cf << endl;



}



