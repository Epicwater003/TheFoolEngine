#pragma once

#include "Deck.h"
#include "Player.h"
#include <list>
#include <random>
#include <functional>

namespace thefoolengine {

enum class PlayerType {
	Computer,
	Player,
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
	void addPlayer(std::shared_ptr<Player> player);
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

class Table {
public:
	using Seed = std::random_device::result_type;

	Deck deck;
	std::mt19937 re;
	std::vector<Players::c_iterator> playersOut;
	CardSet field;
	Card attackCard;
	Card defendCard;
	Players players;
	Seed seed;
	uint32_t turn;
	std::function<void(std::string)> leaveHandler;
	std::function<void(std::string)> foolHandler;

	Table(Seed seed): 
		seed(seed),
		re(seed),
		deck(re),
		turn(0),
		attackCard(0, Suit::Clover), // TODO: refactor 
		defendCard(0, Suit::Clover)
	{}
	Table(std::mt19937& re) :
		seed(0),
		re(re),
		deck(re),
		turn(0),
		attackCard(0, Suit::Clover),
		defendCard(0, Suit::Clover)
	{}

	
	void newGame();
	void newGame(Seed seed);
	
	void doTurn();

	//void addPlayer(PlayerType type);
	void addPlayer(Player* player);
	void addPlayer(std::shared_ptr<Player> player);

	bool gameEnd();

	
};

}