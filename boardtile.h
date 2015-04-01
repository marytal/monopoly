#ifndef __BOARDTILE_H__
#define __BOARDTILE_H__
#include <string> 
#include "textdisplay.h"

class BoardTile {
	public:
		TextDisplay *td;
		std::string name;
		bool ownable;
    BoardTile(std::string name, bool ownable);

    virtual int getPurchasePrice(); // queestiooon
};

#endif
