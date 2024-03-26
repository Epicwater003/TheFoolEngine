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
	return false;
}
bool GreedyComputer::giveUp() {
	return false;
}


}