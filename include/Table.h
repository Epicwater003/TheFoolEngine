#pragma once

#include "Deck.h"
#include "Player.h"
#include <list>
#include <random>
#include <functional>
#include <map>

namespace thefoolengine {

enum class PlayerType { // TODO: move in player namespace
	Computer,
	Player,
};
enum class MoveType {
	Pass,  // attackers choice 
	Attack,// attackers choice 
	GiveUp,// defenders choice 
	Defend,// defenders choice 
	NoMove,// attacker or defender can't do any move - skip
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

const static std::map<MoveType, std::function<void(const std::string,const Card*)>> SimpleMoveHandler{
	{ MoveType::Pass,   [](const std::string name, const Card* c) { std::cout << name << " pass"                      << std::endl; } },
	{ MoveType::Attack, [](const std::string name, const Card* c) { std::cout << name << " use " << *c << " to attack" << std::endl; } },
	{ MoveType::GiveUp, [](const std::string name, const Card* c) { std::cout << name << " give up"                   << std::endl; } },
	{ MoveType::Defend, [](const std::string name, const Card* c) { std::cout << name << " use " << *c << " to defend" << std::endl; } },
	{ MoveType::NoMove, [](const std::string name, const Card* c) { std::cout << name << " can't move"                << std::endl; } },
};

class Table {
public:
	using Seed = std::random_device::result_type;

	using TurnStatusF = std::function<void(const Players::player_p, const Players::player_p, const Players&)>;
	using MoveStatusF = std::function<void(const Players::player_p, MoveType, const Card*)>;

	Deck deck;
	std::mt19937 re;
	std::vector<Players::c_iterator> playersOut;
	CardSet field;
	Card attackCard;
	Card defendCard;
	Players players;
	Seed seed;
	uint32_t turn;

	Table(Seed seed): 
		seed(seed),
		re(seed),
		deck(re),
		turn(0),
		attackCard(0, Suit::Clover),
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
	
	void doTurn(const TurnStatusF& turnStart, const MoveStatusF& attackerMove, const MoveStatusF& defenderMove);

	//void addPlayer(PlayerType type);
	void addPlayer(Player* player);

	bool gameEnd();

	
};

}