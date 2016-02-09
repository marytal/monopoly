#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include "ownable.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;

class Player {
	private:
		int index; // Tims rool up the rim cups
// An integer from 0 to 3 ....... idk (turns left in jail)
		int currentRoll;
	public:
		int jailtime; // change later
		string name;
		int cash;
		char symbol;
		int position;
		int cups;
		Ownable *ownedProperties[28];
		int numOwned;
		void changeBalance(int value); // is this useuful? 
		bool canPay(int value);
		//void bankrupt();
		void pay(int price);
		void getPaid(int amount); // recieve money from another player or bank
		int netWorth(); // calculates net worth for the special case of tuition tile
		string getName(void);
		void printAssets(void);
		Player(string name, char symbol);
		Player(string name, char symbol, int cash, int cups, int position);
		int getRoll(void);
		int getIndex(void);
		void setIndex(int newIndex);
		void setPos(int newPos);
		int getPos(void);
		char getSymbol(void);
		int getBalance(void);
		void printProperties(void);
		
};

#endif




