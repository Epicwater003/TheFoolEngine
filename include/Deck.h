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
	
	iterator begin() {
		return cards.begin();
	}

	iterator end() {
		return cards.end();
	}
private:
	const Card& chooseTrumpCard() const;
	void shuffle();
	mutable std::unique_ptr<Card> trumpCard;
	mutable CardSet cards;
	std::mt19937& re;
};

}