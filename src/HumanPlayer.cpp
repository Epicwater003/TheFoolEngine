#include "../include/Player.h"

namespace thefoolengine {

Card Human::attack() {
	std::cout << "Your cards: " << std::endl;
	viewHand();
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
	std::cout << "Your cards: " << std::endl;
	viewHand();

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
	
	std::cout << "You can attack with: " << std::endl;
	viewPossibleToss();
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
	
	std::cout << "You can defend with: " << std::endl;
	viewPossibleBeat();

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

}