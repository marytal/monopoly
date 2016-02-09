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
    int totalPrice;
    Ownable(std::string name, bool owned, Player *owner, int purchasePrice, bool isMortgaged, int totalPrice);
    Ownable(std::string name, int purchasePrice);
	public:
//		std::string name;
		bool isMortgaged;
		Player *owner; 
		Player *getOwner(void);
		void setOwner(Player *newOwner);
		void mortgage();
		void unmortgage();
		int getPurchasePrice();
//		std::string getName();
		virtual int rent() = 0;
		virtual ~Ownable(void) = 0;
};
#endif

