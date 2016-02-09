#ifndef __GAME_H__
#define __GAME_H__
#include "board.h"
#include "player.h"

class Game {
	bool quit;
	Board *gameBoard;
	bool rolled;
	int numDoubles;
	bool testingMode;
	int numPlayers;
	int playerTurn;
	Player *players[8];
	void getCommand(std::string fullCommand);
	public:
		Game(void);
		~Game(void);
		void initPlayers(void);
		void testingON(void);
		void runGame(void);
		void newGame(void);
		void loadFile(std::string file);
		void getTileAction();
//		void getCommand(std::string fullCommand);
		void saveFile(std::string filename);
		void removePlayer(int spot);
};
#endif
