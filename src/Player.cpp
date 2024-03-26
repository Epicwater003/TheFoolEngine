#include "../include/Player.h"

namespace thefoolengine {

std::string Player::getRandomName(std::mt19937& re, int length) {
	std::string ab = "ABCDEF123456789";
	std::uniform_int_distribution<> dist(0, ab.size() - 1);
	std::string name = std::string(length, ab[0]);
	std::generate_n(name.begin(), length,
		[&ab, &re, &dist]() { return ab[dist(re)]; }
	);
	return name;
}

const bool Player::canIBeat(const Card& card) const {
	iCanBeat.clear();
	for (size_t i = 0, s = hand.size(); i < s; ++i) {
		if (hand[i].beat(card)) {
			iCanBeat.push_back(i);
		}
	}
	return iCanBeat.size();
}

const bool Player::canIToss(const CardSet& cards) const {
	
	iCanToss.clear();
	if (cards.empty()) {
		for (size_t i = 0, s = hand.size(); i < s; ++i) {
			iCanToss.push_back(i);
		}
		return iCanToss.size();
	}
	for (size_t i = 0, s = hand.size(); i < s; ++i) {
		for (auto& card : cards) {
			if (card.getRank() == hand[i].getRank()) {
				iCanToss.push_back(i);
				break;
			}
		}
	}
	return iCanToss.size();
}

void Player::takeCard(Deck& deck) {
	if (hand.size() < 6) {
		hand.push_back(deck.getCard());
	}
	
}
void Player::takeCards(Deck& deck) {
	while (hand.size() < 6) {
		if (!deck.getCardsCount()) {
			//std::cout << "Player " << name << " can't take card. Deck out!" << std::endl;
			return;
		}
		takeCard(deck);
	}
}

void Player::takeAll(CardSet& cards) {
	for (auto card : cards) {
		hand.push_back(card);
	}
}

void Player::dropCards() {
	hand.clear();
}

int Player::getSmallestTrump() const {
	// TODO: refactor this piece
	int rank = 100;
	for (auto& card : hand) {
		if (card.isTrump() && (card.getRank() < rank)) {
			rank = card.getRank();
		}
	}
	return rank;
}

int Player::getCardCount() const {
	return hand.size();
}


void Player::viewHand() const {
	std::cout << name << " cards: ";
	for (auto& card : hand) {
		std::cout << card << ", ";
	}
	std::cout << std::endl;
}
void Player::viewPossibleBeat() const {
	for (auto& i : iCanBeat) {
		std::cout << i << ":" << hand[i] << ", ";
	}
	std::cout << std::endl;
}
void Player::viewPossibleToss() const {
	for (auto& i : iCanToss) {
		std::cout << i << ":" << hand[i] << ", ";
	}
	std::cout << std::endl;
}
}