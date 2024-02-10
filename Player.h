#pragma once

#include "CardSet.h"
#include "Deck.h"



class Player {
public:
	static std::string getRandomName(std::mt19937& re);
	CardSet hand;
	std::string name;
	Player(std::string name = ""): name(name){
		iCanBeat.reserve(27);
		iCanToss.reserve(27);
	}
	
	mutable std::vector<int> iCanBeat;
	mutable std::vector<int> iCanToss;
	const bool canIBeat(const Card&) const;
	const bool canIToss(const CardSet&) const;
	
	void takeCard(Deck&);
	void takeCards(Deck&);
	void takeAll(CardSet&);

	int getSmallestTrump() const;

	void viewHand() const;
	void viewPossibleBeat() const;
	void viewPossibleToss() const;
	
	virtual Card attack() = 0;
	virtual Card defend() = 0;
	virtual bool pass()   = 0;
	virtual bool giveUp() = 0;
};

class Human : public Player {
public:
	Human(std::string name): Player(name) {};
	Card attack() override;
	Card defend() override;
	bool pass()   override;
	bool giveUp() override;
};



class Computer : public Player {
public:
	Computer(std::mt19937& re): Player(Player::getRandomName(re)), re(re){}
	
	Card attack() override;
	Card defend() override;
	bool pass()   override;
	bool giveUp() override;
	// TODO: minCard(CardSet);
	std::mt19937& re;
	int minPossibleCard(const std::vector<int>) const;
};