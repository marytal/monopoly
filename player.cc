#include "player.h"

Player::Player(string name, char symbol) :	name(name),
											symbol(symbol), 
											cash(1500), 
											position(0), 
											cups(0), 
											jailtime(0), 
											currentRoll(0), 
											numOwned(0) {}


Player::Player(string name, char symbol, int cash, int cups, int position): name(name), symbol(symbol), cash(cash), position(position) {};

// An interesting constructor, which raises some nice questions.

void Player::changeBalance(int value){
  cash += value;
}

void Player::setPos(int newPos) {
	position = newPos;
}

int Player::getPos(void) {
	return position;
}

string Player::getName(void) {
	return name;
}

char Player::getSymbol(void) {
	return symbol;
}

int Player::getRoll(void) {
	return currentRoll;
}

bool Player::canPay(int value){
  if(value > cash){
    return false;
  } else {
    return true;
  }
}

int Player::getIndex(void) {
	return index;
}

void Player::setIndex(int newIndex) {
	index = newIndex;
}
// TO DO brankrupt();

void Player::pay(int price){
  this->changeBalance(-price); // check if works
}

void Player::getPaid(int amount){
  this->changeBalance(amount);
}

int Player::netWorth(){
  int networth = 0;
  networth += cash;
  for(int i = 0; i < numOwned; i++){
  //  networth += ownedProperties[i]->totalPrice(); IMPLEMENT
  }

  return networth / 10;
}

void Player::printProperties(void){
  for(int i = 0; i < 28; i++){
    if(ownedProperties[i] != NULL){
      cout << "Properties: " << ownedProperties[i]->getName() << endl;
    }
  }
}

void Player::printAssets(void) {
	cout << endl;
	cout << "Player Name:  " << name << endl;
	cout << "Player token: " << symbol << endl;
	cout << "Cash:         " << cash << endl;
//  printProperties();

//    for(int i = 0; i < numOwned; i++) {
//		cout << "    " << ownedProperties[i]->getName() << endl; 
//	}	
}

int Player::getBalance(void) {
  return cash;
}
