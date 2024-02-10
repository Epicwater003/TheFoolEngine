#include "Deck.h"

Deck::Deck(std::mt19937& re): re(re) {
	cards.reserve(54);
	for (auto& suit : {Suit::Heart, Suit::Diamod, Suit::Clover, Suit::Pike}) {
		for (int rank = 6; rank <= 14; ++rank) {
			cards.push_back(Card(rank, suit));
		}
	}
	shuffle();
	chooseTrumpCard();
}

Card& Deck::chooseTrumpCard(){
	if (trumpCard) {
		return *trumpCard;
	}
	for (auto card = cards.begin(); card != cards.end(); ++card) {
		if (card->rank != 14) {
			trumpCard = std::make_unique<Card>(*card);
			trumpCard->isTrump = true;
			cards.erase(card);
			break;
		}
	}
	std::cout << "deck trump change to trump" << std::endl;
	for (auto& card : cards) {
		if (card.suit == trumpCard->suit) {
			card.isTrump = true;
		}
	}
	return *trumpCard;
}

Card Deck::getCard() {
	if (!trumpCard) {
		std::cout << "Cards in deck out!" << std::endl;
		throw "Cards out!";
	}
	if (!cards.size()) {
		Card c = *trumpCard;
		trumpCard = nullptr;
		return c;
	}
	Card card = cards.back();
	cards.pop_back();
	return card;
}

void Deck::shuffle() {
	std::shuffle(cards.begin(), cards.end(), re);
}

void Deck::viewDeck() const {
	std::cout << "Deck has " << cards.size() << " cards. Trump is " << *trumpCard << std::endl;
	std::cout << "Cards: ";
	for (auto card = cards.rbegin(); card != cards.rend(); ++card) {
		std::cout << *card << ", ";
	}
	std::cout << std::endl;
}
int Deck::cardsCount() const {
	return cards.size() + (trumpCard?1:0);
}