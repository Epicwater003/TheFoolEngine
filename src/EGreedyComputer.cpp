#include "../include/Player.h"

namespace thefoolengine{

Card EGreedyComputer::defend() {
	int ans = 0;
	if (std::uniform_int_distribution<>(0, 3)(re)) {
		ans = minCard(iCanBeat);
	}
	else {
		ans = anyCard(iCanBeat);
	}
	Card c = hand[ans];
	hand.erase(hand.begin() + ans);
	return c;
}
Card EGreedyComputer::attack() {
	int ans = 0;
	if (std::uniform_int_distribution<>(0, 3)(re)) {
		ans = minCard(iCanBeat);
	}
	else {
		ans = anyCard(iCanBeat);
	}

	Card c = hand[ans];
	hand.erase(hand.begin() + ans);
	return c;
}
bool EGreedyComputer::pass() {
	if (hand[minCard(iCanToss)].isTrump()) {
		return std::uniform_int_distribution<>(0, 1)(re);
	}
	return false;
}
bool EGreedyComputer::giveUp() {
	Card c = hand[minCard(iCanBeat)];
	if (c.isTrump()) {
		std::uniform_int_distribution<> dist(6, c.getRank());
		return dist(re) > 11 ? true : false;
	}
	return false;
}


}