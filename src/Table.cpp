#pragma once

#include "../include/Table.h"

namespace thefoolengine {

void Table::replay() {
	newGame(seed);
}
void Table::newGame(Seed s) {
	turn = 0;

	for (auto player : players) {
		player->dropCards();
	}

	re.seed(s);
	deck.refill(re);
	deck.shuffle();
	deck.chooseTrumpCard();

	for (auto player : players) {
		player->takeCards(deck);
	}

	players.chooseFistPlayer();
	if (tableNewGame) {
		tableNewGame(*players.order);
	}
}
void Table::doTurn() {
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


	if (turnBefore) {
		turnBefore(turn, deck, attacker, defender);
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
				if (turnAttack) {
					turnAttack(attacker, Player::Action::Pass, {});
				}
				break;
			}
			else {
				attackCard = attacker->attack();
				if (turnAttack) {
					turnAttack(attacker, Player::Action::Attack, attackCard);
				}
				field.push_back(attackCard);
			}
		}
		else {

			//std::cout << attacker->getName() << " can't attack" << std::endl;
			break; // there a condition for pitchers
		}
		// Pitchers move
		// TODO: If attacking player cannot make a move, then pitchers go
		// Defender move
		if (defender->canIBeat(attackCard)) {
			if (defender->giveUp()) {
				if (turnDefend) {
					turnDefend(defender, Player::Action::GiveUp, {});
				}
				defender->takeAll(field);
				players.skipPlayerTurn(); // Player skips turn if give up
				break;
			}
			else {
				defendCard = defender->defend();
				if (turnDefend) {
					turnDefend(defender, Player::Action::Defend, defendCard);
				}
				field.push_back(defendCard);
			}
		}
		else {

			if (turnDefend) {
				turnDefend(defender, Player::Action::GiveUp, {});
			}
			defender->takeAll(field);
			players.skipPlayerTurn(); // Player skips turn if can't defend
			break;
		}
	}
	//std::cout << " == Turn end == " << std::endl; // TODO: mb don't erase players, just hide em?

	if (turnAfter) {
		turnAfter(turn, deck, attacker, defender);
	}

	if (!deck.getCardsCount()) {
		if (!attacker->getCardCount()) {
			if (tableLeave) {
				tableLeave(attacker);
			}
			
			playersOut.push_back(attacker_it);
		}
		if (!defender->getCardCount()) {
			if (tableLeave) {
				tableLeave(defender);
			}
			
			playersOut.push_back(defender_it);
		}
		// Let players out
		for (const auto& player : playersOut) {
			
			players.erasePlayer(player);
		}
		playersOut.clear();
		
	}
	// Clear field. Maybe move to retreat
	field.clear();
	// Count turns
	++turn;
}

//void Table::addPlayer(PlayerType type) {
//
//}

void Table::addPlayer(std::shared_ptr<Player> player) {
	players.addPlayer(player);
}

bool Table::gameEnd() {
	// Check players
	if (players.players.size() == 1) {
		//std::cout << "#### Player " << players.players.front()->getName() << " fool! ####" << std::endl;
		if (tableGameEnd) {
			tableGameEnd(players.players.front());
		}
		players.players.clear();
		return true;
	}
	if (players.players.size() == 0) {
		if (tableGameEnd) {
			tableGameEnd({});
		}
		players.players.clear();
		return true;
	}
	return false;
}
}



namespace thefoolengine {
namespace {
	using player_p = std::shared_ptr<Player>;
	using iterator = std::list<player_p>::iterator;
	using c_iterator = std::list<player_p>::const_iterator;
}
Players::Players() {
	order = players.begin();
}
Players::iterator Players::begin() {
	return players.begin();
}
Players::iterator Players::end() {
	return players.end();
}

void Players::addPlayer(std::shared_ptr<Player> player) {
	players.emplace_back(player);
	order = players.begin();
}
void Players::chooseFistPlayer() {
	c_iterator pit = players.begin();
	for (c_iterator player = players.begin(); player != players.end(); ++player) {
		if ((*player)->getSmallestTrump() < (*pit)->getSmallestTrump()) {
			pit = player;
		}
	}
	order = pit;
}
Players::c_iterator Players::curr() {
	return order;
}
Players::c_iterator Players::next() const {
	if (std::next(order) == players.end()) {
		return players.begin();
	}
	return std::next(order);
}
Players::c_iterator Players::prev() const {
	if (order == players.begin()) {
		return std::next(players.end(), -1);
	}
	return std::next(order, -1);
}
const Players::player_p Players::getCurrentPlayer() const {
	return *order;
}
const Players::player_p Players::getNextPlayer() const {
	return *next();
}
const Players::player_p Players::getPrevPlayer() const {
	return *prev();
}
void Players::nextPlayerTurn() {
	order = next();
}
void Players::skipPlayerTurn() {
	order = next();
}
void Players::erasePlayer(c_iterator ord) {
	if (ord == order) {
		order = prev();
		players.erase(ord);
		return;
	}
	players.erase(ord);
}

}