#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>


class TextDisplay {
	char **theDisplay;
	int positions[8];
	int *tileRow; // These fields will be implemented later, on "tune up"
 	int *tileCol; 
	int houses[40];
	public:
		TextDisplay(void);	// Standard constructor (uses heap for now)
		
		// Notify to move a player on the board. 
		// You just need to give the tile the player should now be at, 
		// the textdisplay handles the rest. 
		void notify(int newTile, char playerSymbol);

		// Improves a property. 
		// The TextDisplay keeps track of the number of improvements that have been
		// made, but nothing yet has been implemented to warn if trying to build
		// a sixth improvement on the same property.
		// Also, it is currently possible to build an improvement in places that 
		// Should not have improvements like GO square or Railroads, etc. 
		// Be careful not to improve or unimprove those spots! 
		//		The capstone (5th) improvement is a "@" instead of a "&"
		void improve(int tile);

		// Unimproves a property.
		// The textdisplay keeps track of the number of improvements that have been 
		// made, but nothing yet has been implemented if trying to unimprove a 
		// property that isn't there. This will likely be implemented to prevent
		// Damage to the actual textdisplay. 
		void unimprove(int tile);	 
			

		~TextDisplay(); // Standard destructor.

		// Standard gamboard print
		friend std::ostream &operator <<(std::ostream &out, const TextDisplay &td);


		// Note:
		// Maybe at the end of all this it would be fun to implement a 
		// "flip table" function that just turns the board into garbage, 
		// and is the equivalent of someone rage quitting while screwing 
		// up the game for everybody else~
};

#endif
