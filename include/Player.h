#pragma once

#include "CardSet.h"
#include "Deck.h"

namespace thefoolengine {
class Player {
public:
	Player(std::string name = ""): name(name){
		iCanBeat.reserve(27);
		iCanToss.reserve(27);
	}
	const bool canIBeat(const Card&) const;
	const bool canIToss(const CardSet&) const;
	
	void takeCard(Deck&);
	void takeCards(Deck&);
	void takeAll(CardSet&);

	const std::string& getName() const;
	int getSmallestTrump() const;
	int getCardCount() const;

	void viewHand() const;
	void viewPossibleBeat() const;
	void viewPossibleToss() const;
	
	virtual Card attack() = 0;
	virtual Card defend() = 0;
	virtual bool pass()   = 0;
	virtual bool giveUp() = 0;

protected:
	static std::string getRandomName(std::mt19937& re);
	mutable std::vector<int> iCanBeat;
	mutable std::vector<int> iCanToss;
	CardSet hand;

private:
	std::string name;
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

private:
	std::mt19937& re;
	int minPossibleCard(const std::vector<int>) const;
};

}