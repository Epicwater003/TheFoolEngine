#pragma once

#include "Card.h"
#include "CardSet.h"
#include <vector>
#include <algorithm>
#include <random>

namespace thefoolengine {

class Deck {
	typedef CardSet::iterator iterator;
public:
	Deck(std::mt19937& re);
	Card getCard();
	void viewDeck() const;

	int getCardsCount() const;
	const Card& getTrump() const;
	void refill(); // too good method
	void fill();
	void shuffle();
	const Card& chooseTrumpCard() const;
private:
	iterator begin() {
		return cards.begin();
	}

	iterator end() {
		return cards.end();
	}
	
	
	mutable std::unique_ptr<Card> trumpCard;
	mutable CardSet cards;
	std::mt19937& re;
};

}