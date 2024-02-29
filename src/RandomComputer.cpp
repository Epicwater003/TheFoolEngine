#include "../include/Player.h"

namespace thefoolengine {

Card RandomComputer::defend() {
	int ans = anyCard(iCanBeat);
	Card c = hand[ans];
	hand.erase(hand.begin() + ans);
	return c;
}
Card RandomComputer::attack() {
	int ans = anyCard(iCanToss);
	Card c = hand[ans];
	hand.erase(hand.begin() + ans);
	return c;
}
bool RandomComputer::pass() {
	if (iCanToss.empty()) {
		return false;
	}
	
	std::uniform_int_distribution<> dist(0, 1);
	return dist(re);
	

}
bool RandomComputer::giveUp() {
	if (iCanBeat.empty()) {
		return false;
	}
	std::uniform_int_distribution<> dist(0, 4);
	return dist(re) > 3 ? true : false;

}

}