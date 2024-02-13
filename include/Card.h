#pragma once

#include <iostream>
#include <iomanip>

namespace card {

enum class Suit: uint8_t {
	Heart = 3,
	Diamod = 4,
	Clover = 5, 
	Pike = 6,
};

class Card {
public:
	Card(int rank, Suit suit): rank(rank), suit(suit) {}

	bool operator<(const Card&) const;
	bool beat(const Card&) const;

	int getRank() const;
	Suit getSuit() const;
	bool isTrump() const;

	void setTrump(bool value);

	friend std::ostream& operator<<(std::ostream&, const Card&);
private:
	int rank;
	Suit suit;
	bool trump = false; // TODO: mb create derived class "Trump" or move istrump logic to deck?
};

} // Card namespace end
