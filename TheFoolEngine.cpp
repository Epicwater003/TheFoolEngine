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

	/*addplayers;
	newgame;
	while (!gameEnd) {
		doTurn();
		checkWin();
	}*/


	// Create random engine
	auto seed = random_device()();
	std::mt19937 re(seed);

	cout << "@@@@@@@@@@@@@@@ Game start! @@@@@@@@@@@@@@@" << endl;
	Deck deck(re);
	CardSet field;
	Card attackCard(0, Suit::Clover); // TODO: Refactor code
	Card defendCard(0, Suit::Clover); // TODO: Refactor code

	int turn = 0;
	cout << "Trump is: " << deck.getTrump() << ", " << deck.getCardsCount() << " cards in deck" << endl;
	Players players;
	vector<Players::c_iterator> playersOut;
	int players_number = 0;
	char human_player = ' ';
	bool is_human_player = false;
	string human_name = "";
	cout << "Will human play: y/n " << endl;
	do {
		cin >> human_player;
		if (human_player == 'y') {
			is_human_player = true;
			break;
		}
		else if (human_player == 'n') {
			is_human_player = false;
			break;
		}
		else{
			cout << "Wrong input!" << endl;
		}
	} while (true);
	if (is_human_player) {
		cout << "Enter name: " << endl;
		cin >> human_name;
	}
	cout << "Input players cout: 0<n<=6 " << endl;
	do {
		cin >> players_number;
		if (players_number < 0 or !players_number) {
			cout << "Wrong input!" << endl;
			players_number = 0;
		}
	} while (!players_number);
	if (!is_human_player) {
		for (int i = 0; i < players_number; ++i) {
			players.addPlayer(new Computer(re));
		}
	}
	else {
		for (int i = 0; i < players_number - 1; ++i) {
			players.addPlayer(new Computer(re));
		}
		players.addPlayer(new Human(human_name));
	}
	for (auto player : players) {
		player->takeCards(deck);
	}
	players.chooseFistPlayer();

	while (true) {

		// Next player move
		if (turn) {
			players.nextPlayerTurn();
		}
		// Set roles
		Players::player_p attacker = players.getCurrentPlayer();
		Players::c_iterator attacker_it = players.curr();
		Players::player_p defender = players.getNextPlayer();
		Players::c_iterator defender_it = players.next();

			
		// Take cards
		if (deck.getCardsCount()) {
			for (auto player : players) {
				player->takeCards(deck);
			}
		}
		// View turn status
		cout << " == Turn " << turn << " == Cards " << deck.getCardsCount() << "== Players " << players.players.size() << endl;
		// View players status
		for (auto player : players) {
			if (player == attacker) { cout << "--"; }
			else if (player == defender) { cout << "->"; }
			else { cout << "  "; }
			player->viewHand();
		}
		// Do turn
		
		while (true) {
			// 
			if (!defender->getCardCount() || (!turn && (defender->getCardCount() == 1))) {
				break;
			}
			
			// Attacker move
			if (attacker->canIToss(field)) {
				if (!field.empty() && attacker->pass()) {
					std::cout << attacker->getName() << " pass" << std::endl;
					break;
				}
				else {
					attackCard = attacker->attack();
					cout << attacker->getName() << " use " << attackCard << " to attack!" << endl;
					field.push_back(attackCard);
				}
			}
			else {

				std::cout << attacker->getName() << " can't attack" << std::endl;
				break; // there a condition for pitchers
			}
			// Pitchers move
			// TODO: If attacking player cannot make a move, then pitchers go
			// Defender move
			if (defender->canIBeat(attackCard)) {
				if (defender->giveUp()) {
					std::cout << defender->getName() << " give up" << std::endl;
					defender->takeAll(field);
					players.skipPlayerTurn(); // Player skips turn if give up
					break;
				}
				else {
					defendCard = defender->defend();
					cout << defender->getName() << " use " << defendCard << " to defend!" << endl;
					field.push_back(defendCard);
				}
			}
			else {

				std::cout << defender->getName() << " can't defend" << std::endl;
				defender->takeAll(field);
				players.skipPlayerTurn(); // Player skips turn if can't defend
				break;
			}
		}
		cout << " == Turn end == " << endl;
		if (!deck.getCardsCount()) {
			if (!attacker->getCardCount()) {
				cout << "#### Player " << attacker->getName() << " win! ####" << endl;
				playersOut.push_back(attacker_it);
			}
			if (!defender->getCardCount()) {
				cout << "#### Player " << defender->getName() << " win! ####" << endl;
				playersOut.push_back(defender_it);
			}
			// Let players out
			for (const auto& player : playersOut) {
				players.erasePlayer(player);
			}
			playersOut.clear();
			// Check players
			if (players.players.size() == 1) {
				cout << "#### Player " << players.players.front()->getName() << " fool! ####" << endl;
				break;
			}
			if (players.players.size() == 0) {
				cout << "#### The game ended in a draw ####" << endl;
				break;
			}
		}
		// Clear field. Maybe move to retreat
		field.clear();
		// Count turns
		++turn;
	};
		
	players.players.clear();
	cout << "@@@@@@@@@@@@@@@ Game end! @@@@@@@@@@@@@@@" << endl;
	int ack;
	std::cin >> ack;
}



