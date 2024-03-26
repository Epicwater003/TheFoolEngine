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
	
	auto gc1 = std::make_shared<GreedyComputer>(re);
	auto gc2 = std::make_shared<GreedyComputer>(re);
	
	table.tableNewGame = [](auto player) {
		cout << player->name << endl;
	};
	table.tableGameEnd = [](auto player) {
		if (player) {
			cout << (*player)->name << endl;
		}
		else {
			cout << "Game ended in a draw" << endl;
		}
			
	};
	table.turnBefore = [](auto t, auto& deck, auto attacker, auto defender) {
		cout << t << endl;
		cout << deck.getCardsCount() << endl;
	};
	
	table.addPlayer(gc1);
	table.addPlayer(gc2);

	table.newGame(seed);

	while (!table.gameEnd())
	{
		table.doTurn();
	}
	

}



