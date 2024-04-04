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
	auto h1 = std::make_shared<Human>("EpicWater");
	auto hec1 = std::make_shared<HeuristicsComputer>(re);
	auto hec2 = std::make_shared<HeuristicsComputer>(re);
	auto hec3 = std::make_shared<HeuristicsComputer>(re);
	auto gc1 = std::make_shared<GreedyComputer>(re);
	auto gc2 = std::make_shared<GreedyComputer>(re);
	auto gc3 = std::make_shared<GreedyComputer>(re);
	auto egc1 = std::make_shared<EGreedyComputer>(re);
	auto egc2 = std::make_shared<EGreedyComputer>(re);
	auto egc3 = std::make_shared<EGreedyComputer>(re);
	auto rc1 = std::make_shared<RandomComputer>(re);
	auto rc2 = std::make_shared<RandomComputer>(re);
	auto rc3 = std::make_shared<RandomComputer>(re);
	
	
	/*table.tableNewGame = [](auto player, auto trump) {
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
	};*/
	table.tableLeave = [&](auto player) {
		
	};
	int rc1_n = 0, rc2_n = 0, rc3_n = 0;
	int gc1_n = 0, gc2_n = 0, gc3_n = 0;
	int egc1_n = 0, egc2_n = 0, egc3_n = 0;
	int hec1_n = 0, hec2_n = 0, hec3_n = 0;
	table.tableGameEnd = [&](auto player) {
		if (!player) {
			--gc1_n;
			--hec1_n;
		}
		else if (*player == gc1)
			gc1_n += 1;
		
		else if (*player == hec1)
			hec1_n += 1;
		

	};
	float tries = 1000;
	float win = 0;
	float cumulative_win = 0;
	float count = 0;
	while (true) {
		for (int i = 0; i < tries; ++i) {
			seed = random_device()();
			for (int o = 0; o < 3; ++o) {
				if ((int)count % 2) {
					table.addPlayer(gc1);
					table.addPlayer(hec1);
				}
				else {
					table.addPlayer(hec1);
					table.addPlayer(gc1);
				}
				
				table.newGame(seed);
				while (!table.gameEnd())
				{
					table.doTurn();
				}
			}

		}
		++count;
		
		win = (tries * 3.0 - hec1_n - (tries * 3.0 - (gc1_n + hec1_n))) / (tries * 3.0);
		cumulative_win += win;
		cout << "win rate:" << win << endl;
		cout << "avg win: " << cumulative_win / count << endl;
		
		gc1_n = 0;
		hec1_n = 0;
	}
	

	
}



