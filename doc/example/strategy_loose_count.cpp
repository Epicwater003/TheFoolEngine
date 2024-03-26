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

	vector<double> counter(6, 0.);

	auto seed = random_device()();
	std::mt19937 re(seed);

	Table table(seed);


	auto gc1 = std::make_shared<GreedyComputer>(re);
	auto gc2 = std::make_shared<GreedyComputer>(re);
	auto gc3 = std::make_shared<GreedyComputer>(re);
	auto gc4 = std::make_shared<GreedyComputer>(re);
	auto gc5 = std::make_shared<GreedyComputer>(re);
	auto rc1 = std::make_shared<RandomComputer>(re);

	table.foolHandler = [&](std::string name) {
		if (name == gc1->getName()) ++counter[0];
		if (name == gc2->getName()) ++counter[1];
		if (name == gc3->getName()) ++counter[2];
		if (name == gc4->getName()) ++counter[3];
		if (name == gc5->getName()) ++counter[4];
		if (name == rc1->getName()) ++counter[5];

		};
	for (int i = 0; i < 5; ++i) {

		cout << "Test " << i << endl;
		for (int i = 0; i < 1000; ++i) {
			auto seed = random_device()();
			for (int i = 0; i < 10; ++i) {
				table.addPlayer(gc1);
				table.addPlayer(gc2);
				table.addPlayer(gc3);
				table.addPlayer(gc4);
				table.addPlayer(gc5);
				table.addPlayer(rc1);
				table.newGame(seed);
				while (!table.gameEnd())
				{
					table.doTurn();
				}
			}
		}

		std::cout << "Greedy computers loses: " << counter[0] + counter[1] + counter[2] + counter[3] + counter[4] << endl;
		std::cout << "Random computer loses: " << counter[5] << endl;
	}
}



