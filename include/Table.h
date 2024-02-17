#pragma once

#include "Deck.h"
#include "Player.h"
#include <list>

namespace thefoolengine {

enum class PlayerType {
	Computer,
	Player,
};

class Table {
public:
	Deck deck;
	void newGame();
	void doTurn();

	void addPlayer(PlayerType type);
	void addPlayer(Player& player);
	
};

class Players {
public:
	using player_p = std::shared_ptr<Player>;
	using iterator = std::list<player_p>::iterator;
	using c_iterator = std::list<player_p>::const_iterator;
	std::list<player_p> players;
	mutable c_iterator order;
	Players();
	iterator begin();
	iterator end();
	void addPlayer(Player* player);
	void chooseFistPlayer();
	c_iterator curr();
	c_iterator next() const;
	c_iterator prev() const;
	const player_p getCurrentPlayer() const;
	const player_p getNextPlayer() const;
	const player_p getPrevPlayer() const;
	void nextPlayerTurn();
	void skipPlayerTurn();
	void erasePlayer(c_iterator ord);
};
}