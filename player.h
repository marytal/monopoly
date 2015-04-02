#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include "ownable.h"

using namespace std;

class Player {
	private:
		string name;
		int cash;
		int index;
		int position;
		int cups; // Tims rool up the rim cups
		int jailtime; // An integer from 0 to 3 ....... idk (turns left in jail)
		int currentRoll;
		Ownable *ownedProperties[28];
		int numOwned;
		char symbol;
	public:
		void changeBalance(int value); // is this useuful? 
		bool canPay(int value);
		//void bankrupt();
		void pay(int price);
		void getPaid(int amount); // recieve money from another player or bank
		int netWorth(); // calculates net worth for the special case of tuition tile
		string getName(void);
		void printAssets(void);
		Player(string name, char symbol);
		int getRoll(void);
		int getIndex(void);
		void setIndex(int newIndex);
		void setPos(int newPos);
		int getPos(void);
		char getSymbol(void);
		int getBalance(void);
};

#endif




