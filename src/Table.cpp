#pragma once

#include "../include/Table.h"

namespace thefoolengine {

void Table::newGame() { // TODO: mb need another function name like replay?
	turn = 0;
	for (auto player : players) {
		player->dropCards();
	}
	deck = std::make_unique<Deck>(seed);
}
void Table::newGame(Seed seed) {
	turn = 0;
	for (auto player : players) {
		player->dropCards();
	}
	deck = std::make_unique<Deck>(seed);
}
void Table::doTurn() {

}

void Table::addPlayer(PlayerType type) {

}
void Table::addPlayer(Player& player) {

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
void Players::addPlayer(Player* player) {
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