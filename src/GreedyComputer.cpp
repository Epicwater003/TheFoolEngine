#include "../include/Player.h"

namespace thefoolengine{

Card GreedyComputer::defend() {
	int ans = minCard(iCanBeat);
	Card c = hand[ans];
	hand.erase(hand.begin() + ans);
	return c;
}
Card GreedyComputer::attack() {
	int ans = minCard(iCanToss);
	Card c = hand[ans];
	hand.erase(hand.begin() + ans);
	return c;
}
bool GreedyComputer::pass() {
	if (iCanToss.empty()) {
		return false;
	}
	if (hand[minCard(iCanToss)].isTrump()) {
		//std::uniform_int_distribution<> dist(0, 1);
		return std::uniform_int_distribution<>(0,1)(re);
	}
	return false;
}
bool GreedyComputer::giveUp() {
	if (iCanBeat.empty()) {
		return false;
	}
	Card c = hand[minCard(iCanBeat)];
	if (c.isTrump()) {
		std::uniform_int_distribution<> dist(6, c.getRank());
		return dist(re) > 11 ? true : false;
	}
	return false;
}


}