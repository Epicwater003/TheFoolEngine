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
	auto gc2 = std::make_shared<Human>("EpicWater");
	//auto gc3 = std::make_shared<GreedyComputer>(re);
	//auto egc1 = std::make_shared<EGreedyComputer>(re);
	//auto rc1 = std::make_shared<RandomComputer>(re);
	table.tableNewGame = [](auto player, auto trump) {
		cout << "Trump is " << trump << endl;
		cout << "First goes " << player->name << endl;
	};
	table.turnBefore = [](auto t, auto& deck, auto a, auto d) {
		cout << "Turn: " << t << " Cards: " << deck.getCardsCount() << endl;
	};
	table.turnAttack = [](auto p, auto act, auto card) {
		switch (act){
		case Player::Action::Attack:
			cout << p->name << " attack: " << *card << endl;
			break;
		case Player::Action::Pass:
			cout << p->name << " pass ===" << endl;
		}
	};
	table.turnDefend = [](auto p, auto act, auto card) {
		switch (act) {
		case Player::Action::Defend:
			cout << p->name << " defend: " << *card << endl;
			break;
		case Player::Action::GiveUp:
			cout << p->name << " give up ===" << endl;
		}
	};
	table.turnAfter = [&](auto t, auto& deck, auto withdraw) {
		cout << "Withdraw: " << withdraw.size() << endl;
	};
	table.tableGameEnd = [&](auto player) {
		if (player) {
			cout << (*player)->name << " fool! Cards on hand: " << (*player)->getCardCount() << endl;
		}
		else
		{
			cout << "Game ended in a draw!" << endl;
		}
	};
	/*table.tableLeave = [&](auto player) {
		
	};
	table.tableGameEnd = [&](auto player) {
		if (!player) {
			--gc1_n;
			--gc2_n;
			--gc3_n;
			--egc1_n;
			--rc1_n;
		}
		else if (*player == gc1)
			gc1_n += 1;
		else if (*player == gc2)
			gc2_n += 1;
		else if (*player == gc3)
			gc3_n += 1;
		else if (*player == egc1)
			egc1_n += 1;
		else if (*player == rc1)
			rc1_n += 1;

	};*/
	
	seed = random_device()();
	table.addPlayer(gc1);
	//table.addPlayer(egc1);
	table.addPlayer(gc2);
	//table.addPlayer(rc1);
	//table.addPlayer(gc3);
	table.newGame(seed);
	while (!table.gameEnd())
	{
		table.doTurn();
	}

}



