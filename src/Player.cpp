#include "../include/Player.h"

namespace thefoolengine {

std::string Player::getRandomName(std::mt19937& re) {
	std::string ab = "ABCDEF123456789";
	std::uniform_int_distribution<> dist(0, ab.size() - 1);
	std::string name = std::string(3, ab[0]);
	std::generate_n(name.begin(), 3,
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
			std::cout << "Player " << name << " can't take card. Deck out!" << std::endl;
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

const std::string& Player::getName() const {
	return name;
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


Card Human::attack() {
	std::cout << "You can attack with: " << std::endl;
	viewPossibleToss();
	std::cout << "Input number of card to toss: " << std::endl;
	int ans;
	while (true) {
		std::cin >> ans;
		if (std::find(iCanToss.begin(), iCanToss.end(), ans) != iCanToss.end()) {
			break;
		}
		std::cout << "Can't attack with that card" << std::endl;
	}
	Card c = hand[ans];
	
	hand.erase(hand.begin() + ans);
	return c;
}
Card Human::defend() {
	std::cout << "You can defend with: " << std::endl;
	viewPossibleBeat();

	std::cout << "Input number of card to beat: " << std::endl;
	int ans;
	while (true) {
		std::cin >> ans;
		if (std::find(iCanBeat.begin(), iCanBeat.end(), ans) != iCanBeat.end()) {
			break;
		}
		std::cout << "Can't beat with that card" << std::endl;
	}
	Card c = hand[ans];
	hand.erase(hand.begin() + ans);
	return c;
}
bool Human::pass() {
	std::cout << "Pass? y/n: " << std::endl;
	char ans;
	bool a;
	do { // TODO: refactor to check function
		std::cin >> ans;
		if (ans == 'y') {
			a = true;
			break;
		}
		else if (ans == 'n') {
			a = false;
			break;
		}
		else {
			std::cout << "Wrong input!" << std::endl;
		}
	} while (true);
	return a;
}
bool Human::giveUp() {
	std::cout << "Give up? y/n: " << std::endl;
	char ans;
	bool a;
	do { // TODO: refactor to check function
		std::cin >> ans;
		if (ans == 'y') {
			a = true;
			break;
		}
		else if (ans == 'n') {
			a = false;
			break;
		}
		else {
			std::cout << "Wrong input!" << std::endl;
		}
	} while (true);
	return a;
}

Card Computer::defend() {
	int ans = minPossibleCard(iCanBeat);
	Card c = hand[ans];
	hand.erase(hand.begin() + ans);
	return c;
}
Card Computer::attack() {
	int ans = minPossibleCard(iCanToss);
	Card c = hand[ans];
	hand.erase(hand.begin() + ans);
	return c;
}
bool Computer::pass() {
	if (iCanToss.empty()) {
		return false;
	}
	if (hand[minPossibleCard(iCanToss)].isTrump()) {
		std::uniform_int_distribution<> dist(0, 1);
		return dist(re);
	}
	return false;
}
bool Computer::giveUp() {
	if (iCanBeat.empty()) {
		return false;
	}
	Card c = hand[minPossibleCard(iCanBeat)];
	if (c.isTrump()) {
		std::uniform_int_distribution<> dist(6, c.getRank());
		return dist(re) > 11 ? true : false;
	}
	return false;
}

int Computer::minPossibleCard(const std::vector<int> ixs) const {
	Card card = hand[ixs[0]];
	int index = ixs[0];
	for (auto i : ixs) {
		if ((hand[i].isTrump() && card.isTrump()) || (!hand[i].isTrump() && !card.isTrump())) {
			if (hand[i].getRank() < card.getRank()) {
				card = hand[i];
				index = i;
			}
		}
		if (!hand[i].isTrump() && card.isTrump()) {
			card = hand[i];
			index = i;
		}
		
	}
	return index;
}

}