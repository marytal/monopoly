#ifndef __BOARD_H__
#define __BOARD_H__
#include "boardtile.h"
#include "player.h"
#include "textdisplay.h"

//class AcademicBuilding;   /// Whyyy
class Game;
// heeeeeey

class Board {
	 // can we put the const 40 here instead?
//	Ownable *ownables[28];
	int roll1;
	int roll2;
	int currentPlayerIndex;
	
	public:
		Player *currentPlayer; // change later
		Game *theGame;		
		int numPlayers;
		Player *players[8];
		TextDisplay *td;
		BoardTile *tiles[40];
		Board(void);
		~Board(void);
		//Board(string filename);
		void addPlayer(Player *);
		bool isOwnable(BoardTile *tile);
		int getTilePrice(Ownable *tile);
		void getCurrentRoll(int roll1, int roll2);

		BoardTile *findTileByName(string property);
//		Ownable *findOwnableByName(string property);
//		AcademicBuilding *findAcademicByName(string property);
		Player *findPlayerByName(string name);
		//void save(); // Uhmm.... do we need this here or in the Game class? 
		void trade(string name, int amount, string property); // buy property from name
		void trade(string name, string property1, string property2);
		void trade(string name, string property, int amount); 
		void unownableAction(BoardTile *);
		void improveSell(string property); // sell an improvement
		void improveBuy(string property); // buy an improvement
		void mortgage(string property);
		void unmortgage(string property);
		void changeTurn(void);
		void getTileAction();
		void auction(BoardTile *tile);
		void printAssets(void);
		int playerNetworth(void);
		int slcHelper(void);
		void jailHelper(void);
		void bankrupt(Player *creditor);
		void cantPay(int amount, Player *creditor);
		void removePlayer(Player *delMe);
};

void makeFaculty(BoardTile *first, BoardTile *second, BoardTile *third);

int needlesHelper(void);
int slcHelper(void);

#endif


















