#ifndef __OWNABLE_H__
#define __OWNABLE_H__
#include "textdisplay.h"
#include "boardtile.h"

#include <string>

class Player;

class  Ownable : public BoardTile {
	protected:
		TextDisplay *td;
		bool owned;
		// Is there a better way to do this/ Ask Nomar and Kirsten and Tonghui

		int purchasePrice;
		bool isMortgaged;
    int totalPrice;
    Ownable(std::string name, bool owned, Player *owner, int purchasePrice, bool isMortgaged, int totalPrice);
    Ownable(std::string name);
	public:
		std::string name;
		Player *owner; 
		Player *getOwner(void);
		void setOwner(Player *newOwner);
		void mortgage();
		void unmortgage();
		int getPurchasePrice();
		virtual int rent() = 0;
};
#endif

