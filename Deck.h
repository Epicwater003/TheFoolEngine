#pragma once

#include "Card.h"
#include "CardSet.h"
#include <vector>
#include <algorithm>
#include <random>


class Deck {
public:
	Deck(std::mt19937& re);
	Card& chooseTrumpCard();
	Card getCard();
	void shuffle();
	friend int main();
	void viewDeck() const;
	int cardsCount() const;
	typedef CardSet::iterator iterator;

	iterator begin() {
		return cards.begin();
	}

	iterator end() {
		return cards.end();
	}
private:
	mutable std::unique_ptr<Card> trumpCard;
	CardSet cards;
	
	std::mt19937& re;
};