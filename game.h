#ifndef __GAME_H__
#define __GAME_H__
#include "board.h"
#include "player.h"

class Game {
	Board *gameBoard;
	bool testingMode;
	int numPlayers;
	int playerTurn;
	Player **players;
	void getCommand(std::string fullCommand);
	public:
		Game(void);
		void initPlayers(void);
		void testingON(void);
		void runGame(void);
		void newGame(void);
		void loadFile(std::string file);
		void getTileAction();
//		void getCommand(std::string fullCommand);
};
#endif
