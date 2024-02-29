#include "../include/Player.h"

namespace thefoolengine {

int Computer::minCard(const std::vector<int> ixs) const {
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
int Computer::anyCard(const std::vector<int> ixs) const {
	return ixs[std::uniform_int_distribution<>(0, ixs.size()-1)(re)];
}

}