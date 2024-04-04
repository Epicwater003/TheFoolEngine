#include "../include/Player.h"

namespace thefoolengine {

Card HeuristicsComputer::attack() {
	int ans = minCard(iCanToss);
	float avgWorth = static_cast<float>(CardSetWorth(hand))/static_cast<float>(hand.size());
	
	for (const auto& cardIndex : iCanToss) {
		CardSet cards = hand;
		cards.erase(cards.begin() + cardIndex);
		int newAvgWorth = static_cast<float>(CardSetWorth(cards)) / static_cast<float>(cards.size());
		if ((newAvgWorth - 100) >= avgWorth) {
			ans = cardIndex;
			avgWorth = newAvgWorth;
		}
	}

	Card c = hand[ans];
	hand.erase(hand.begin() + ans);
	return c;
}
Card HeuristicsComputer::defend() {
	int ans = minCard(iCanBeat);
	float avgWorth = static_cast<float>(CardSetWorth(hand)) / static_cast<float>(hand.size());

	for (const auto& cardIndex : iCanBeat) {
		CardSet cards = hand;
		cards.erase(cards.begin() + cardIndex);
		int newAvgWorth = static_cast<float>(CardSetWorth(cards)) / static_cast<float>(cards.size());
		if ((newAvgWorth - 100) >= avgWorth) {
			ans = cardIndex;
			avgWorth = newAvgWorth;
		}
	}

	Card c = hand[ans];
	hand.erase(hand.begin() + ans);
	return c;
}
bool HeuristicsComputer::pass() {
	bool ans = true;
	float avgWorth = static_cast<float>(CardSetWorth(hand)) / static_cast<float>(hand.size());

	for (const auto& cardIndex : iCanToss) {
		CardSet cards = hand;
		cards.erase(cards.begin() + cardIndex);
		int newAvgWorth = static_cast<float>(CardSetWorth(cards)) / static_cast<float>(cards.size());
		if (newAvgWorth >= avgWorth) {
			ans = true;
			break;
		}
	}

	return false;
}
bool HeuristicsComputer::giveUp() {
	return false;
}

int HeuristicsComputer::CardSetWorth(CardSet cards) {
	int values[9] = { 0 }; // 6 7 8 9 10 J Q K A
	int worth = 0;
	for (const auto& card : cards) {
		values[card.getRank() - 6] += 1;
	}
	for (const auto& card : cards) {
		int rank = card.getRank();
		worth += values[rank - 6] * (float)rank;
		if (card.isTrump()) {
			worth += 100;
		}
	}
	return worth;
}


}