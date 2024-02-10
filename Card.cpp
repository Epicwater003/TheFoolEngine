#include "Card.h"

bool Card::operator<(const Card& r_card) const {
	if (this->suit != r_card.suit && !r_card.isTrump) return false;
	return (this->rank < r_card.rank) || (r_card.isTrump && !this->isTrump);

}

bool Card::beat(const Card& card) const {
	return card < *this;
}

std::ostream& operator << (std::ostream& os, const Suit& suit)
{
	os << static_cast<uint8_t>(suit);
	return os;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
	os << card.rank << card.suit;
	return os;
}


