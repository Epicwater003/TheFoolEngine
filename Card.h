#pragma once

#include <iostream>
#include <iomanip>

enum class Suit: uint8_t {
	Heart = 3,
	Diamod = 4,
	Clover = 5, 
	Pike = 6,
};

class Card {
public:
	Card(int rank, Suit suit): rank(rank), suit(suit) {}
	int rank;
	Suit suit;
	bool isTrump = false;
	bool operator<(const Card&) const;
	bool beat(const Card&) const;
};

std::ostream& operator<<(std::ostream&, const Card&);
