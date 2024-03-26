#pragma once

#include "Deck.h"
#include "Player.h"
#include <list>
#include <random>
#include <functional>
#include <optional>

namespace thefoolengine {

enum class PlayerType {
	Computer,
	Player,
};

class Players {
public:
    // TODO:: Refactor class
	using player_p = std::shared_ptr<Player>;
	using iterator = std::list<player_p>::iterator;
	using c_iterator = std::list<player_p>::const_iterator;
	std::list<player_p> players;
	mutable c_iterator order;
	Players();
	iterator begin();
	iterator end();
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
	Seed seed = 0;
	uint32_t turn = 0;
	
	// Called: on player added. 
	// Passes: _1 player added
	std::function<void(Players::player_p)> tablePlayerAdded;

	// Called: on player leave table (win). 
	// Passes: _1 player
	std::function<void(Players::player_p)> tableLeave;

	// Called: on new game or replay. 
	// Passes: _1 player, who goes first
	std::function<void(Players::player_p)> tableNewGame;

	// Called: on end of game. 
	// Passes: _1 optional player, if player exists - it's fool, also game ended in draw
	std::function<void(std::optional<Players::player_p>)> tableGameEnd;

	// Called: before every turn. 
	// Passes: _1 turn, _2 Deck, _3 attacker, _4 defender
	std::function<void(uint32_t, const Deck&, Players::player_p, Players::player_p)> turnBefore;
	
	// Called: after every turn. 
	// Passes: _1 turn, _2 Deck, _3 attacker, _4 defender
	std::function<void(uint32_t, const Deck&, Players::player_p, Players::player_p)> turnAfter;

	// Called: on player attack. 
	// Passes: _1 player, _2 Action, _3 optional card
	std::function<void(Players::player_p, Player::Action, std::optional<Card>)> turnAttack;

	// Called: on player defend. 
	// Passes: _1 player, _2 Action, _3 optional card
	std::function<void(Players::player_p, Player::Action, std::optional<Card>)> turnDefend;

	

	Table():
		deck(re),
		attackCard(0, Suit::Clover), // TODO: refactor 
		defendCard(0, Suit::Clover)
	{}
	Table(std::mt19937& re) :
		seed(0),
		re(re),
		deck(re),
		attackCard(0, Suit::Clover),
		defendCard(0, Suit::Clover)
	{}

	
	void replay();
	void newGame(Seed seed);
	
	void doTurn();

	//void addPlayer(PlayerType type);
	void addPlayer(std::shared_ptr<Player> player);

	bool gameEnd();

	
};

}