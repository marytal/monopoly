#include "ownable.h"

using namespace std;

Ownable::Ownable(string name, bool owned, Player *owner, int purchasePrice, bool isMortgaged, int totalPrice) : 
owned(owned), owner(NULL), purchasePrice(purchasePrice), isMortgaged(isMortgaged), totalPrice(totalPrice), BoardTile(name, true) {};

Ownable::Ownable(string name) : BoardTile(name, true) {};

Player *Ownable::getOwner(void) {
	return owner;
}

void Ownable::setOwner(Player *newOwner) {
	owner = newOwner;
}

void Ownable::mortgage(void) {
	isMortgaged = true;
}

void Ownable::unmortgage(void) {
	isMortgaged = false;
}

int Ownable::getPurchasePrice(void) {
	return purchasePrice;
}




	
