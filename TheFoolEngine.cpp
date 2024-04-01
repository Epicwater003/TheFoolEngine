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
	int a = 0;
	int b = 0;
	Table table;
	auto gc1 = std::make_shared<GreedyComputer>(re);
	auto gc2 = std::make_shared<GreedyComputer>(re);
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
		cout << "Total: " << withdraw.size() << " Cards: ";
		for (Card& card : withdraw) {
			cout << card << " ";
		}
		cout << endl;
		a = withdraw.size();
	};
	table.tableGameEnd = [&](auto player) {
		if (player) {
			cout << (*player)->name << " fool! Total: " << (*player)->getCardCount() << " Cards: ";
			(*player)->viewHand();
			cout << endl;
			b = (*player)->getCardCount();
		}
		else
		{
			b = 0;
			cout << "Game ended in a draw!" << endl;
		}
	};
	for (int i = 0; i < 10000; ++i) {
		auto seed = random_device()();
		table.addPlayer(gc1);
		table.addPlayer(gc2);
		table.newGame(seed);
		while (!table.gameEnd())
		{
			table.doTurn();
		}
		if (a + b != 36) {
			cout << "Ahtung!!";
		}
	}
	

}



