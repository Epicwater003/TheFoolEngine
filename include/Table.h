#pragma once

#include "Deck.h"
#include "Player.h"
#include <list>
#include <random>

namespace thefoolengine {

enum class PlayerType {
	Computer,
	Player,
};

class Table {
public:
	using deck_p = std::unique_ptr<Deck>;
	using Seed = std::random_device::result_type;

	deck_p deck;
	Players players;
	Seed seed;
	uint32_t turn;

	Table(Seed seed): seed(seed), turn(0) {
		deck = std::make_unique<Deck>(seed);
	}
	
	void newGame();
	void newGame(Seed seed);
	
	void doTurn();
	void doSubTurn();
	void checkGameEnd();

	void addPlayer(PlayerType type);
	void addPlayer(Player& player);

	bool gameEnd();

	
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