#ifndef __BOARD_H__
#define __BOARD_H__
#include "boardtile.h"
#include "player.h"
#include "textdisplay.h"

class AcademicBuilding;

class Board {
	 // can we put the const 40 here instead?
//	Ownable *ownables[28];
	int roll1;
	int roll2;
	TextDisplay *td;
	int numPlayers;
	int currentPlayerIndex;
	Player *currentPlayer;
	Player *players[8];
	public: 
		BoardTile *tiles[40];
		Board(void);
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

		void improveSell(string property); // sell an improvement
		void improveBuy(string property); // buy an improvement
		void mortagage(string property);
		void unmortgage(string property);
		void changeTurn(void);
		void getTileAction();
};

#endif


















