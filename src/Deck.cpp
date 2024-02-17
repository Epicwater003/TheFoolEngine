#include "../include/Deck.h"

namespace thefoolengine {


Deck::Deck(std::mt19937& re): re(re) {
	cards.reserve(54);
	for (auto& suit : { Suit::Heart, Suit::Diamod, Suit::Clover, Suit::Pike}) {
		for (int rank = 6; rank <= 14; ++rank) {
			cards.push_back(Card::Card(rank, suit));
		}
	}
	shuffle();
	chooseTrumpCard();
}

const Card& Deck::chooseTrumpCard() const{
	if (trumpCard) {
		return *trumpCard;
	}
	for (size_t i = 0, s = cards.size(); i < s; ++i) {
		if (cards[i].getRank() != 14) {
			trumpCard = std::make_unique<Card>(cards[i]);
			trumpCard->setTrump(true);
			cards.erase(cards.begin() + i);
			break;
		}
	}
	for (auto& card : cards) {
		if (card.getSuit() == trumpCard->getSuit()) {
			card.setTrump(true);
		}
	}
	return *trumpCard;
}

Card Deck::getCard(){ // TODO: rewrite copy to move 
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
int Deck::getCardsCount() const {
	return cards.size() + (trumpCard?1:0);
}
const Card& Deck::getTrump() const {
	return *trumpCard;
}


}