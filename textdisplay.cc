#include <iostream>
#include <string> 
#include "textdisplay.h"

using namespace std;
// look into namespace to make these "priveate" annonymous namespace
// Use getline to make this a bit more streamlined so that I can store
// the board in a different place or use different themes. LOL
int tileRowMap[40] = {54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 49, 44, 39, 34, 29, 24, 19, 14, 9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,  9,  14, 19, 24, 29, 34, 39, 44, 49}; 
int tileColMap[40] = {81, 73, 65, 57, 49, 41, 33, 25, 17,  9,  1,  1,   1, 1,  1,  1,  1,  1,  1, 1, 1, 9, 17,25,33,41,49,57,65,73,81, 81, 81, 81, 81, 81, 81, 81, 81, 81};


int rows = 56;
int cols = 89;

string normalTheme = "_________________________________________________________________________________________|Goose  |       |NEEDLES|       |       |V1     |       |       |CIF    |       |GO TO  ||Nesting|-------|HALL   |-------|-------|       |-------|-------|       |-------|TIMS   ||       |EV1    |       |EV2    |EV3    |       |PHYS   |B1     |       |B2     |       ||       |       |       |       |       |       |       |       |       |       |       ||_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______||       |                                                                       |       ||-------|                                                                       |-------||OPT    |                                                                       |EIT    ||       |                                                                       |       ||_______|                                                                       |_______||       |                                                                       |       ||-------|                                                                       |-------||BMH    |                                                                       |ESC    ||       |                                                                       |       ||_______|                                                                       |_______||SLC    |                                                                       |SLC    ||       |                                                                       |       ||       |                                                                       |       ||       |                                                                       |       ||_______|                                                                       |_______||       |                                                                       |       ||-------|                                                                       |-------||LHI    |                                                                       |C2     ||       |               _________________________________________               |       ||_______|               |                                       |               |_______||UWP    |               |  ###   ###   #####  ###   ###   ###   |               |REV    ||       |               |  #  #  #  #     #  #   # #   # #   #  |               |       ||       |               |  ####  ####    #   #   # #   # #   #  |               |       ||       |               |  #   # #   #  #    #   # #   # #   #  |               |       ||_______|               |  ####  ####  #      ###   ###   ###   |               |_______||       |               |_______________________________________|               |NEEDLES||-------|                                                                       |HALL   ||CPH    |                                                                       |       ||       |                                                                       |       ||_______|                                                                       |_______||       |                                                                       |       ||-------|                                                                       |-------||DWE    |                                                                       |MC     ||       |                                                                       |       ||_______|                                                                       |_______||PAC    |                                                                       |COOP   ||       |                                                                       |FEE    ||       |                                                                       |       ||       |                                                                       |       ||_______|                                                                       |_______||       |                                                                       |       ||-------|                                                                       |-------||RCH    |                                                                       |DC     ||       |                                                                       |       ||_______|_______________________________________________________________________|_______||DC Tims|       |       |NEEDLES|       |MKV    |TUITION|       |SLC    |       |COLLECT||Line   |-------|-------|HALL   |-------|       |       |-------|       |-------|OSAP   ||       |HH     |PAS    |       |ECH    |       |       |ML     |       |AL     |       ||       |       |       |       |       |       |       |       |       |       |       ||_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|";

TextDisplay::TextDisplay(void) {
	theDisplay = new char* [rows];
	for(int i = 0; i < rows; i++) {
		theDisplay[i] = new char [cols];
	}
	int k = 0;
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			theDisplay[i][j] = normalTheme[k];
			k++;
		}
	}
	tileRow = tileRowMap; 
	tileCol = tileColMap;
	for(int i = 0; i < 40; i++) {
		houses[i] = 0;
	}
	for(int i = 0; i < 8; i++) {
		positions[i] = 0;
	}
}

void TextDisplay::notify(int newTile, char playerSymbol) {
	int adjustX = 0;
	int adjustY = 0;
	int playerIndex = 0;
	if(playerSymbol == 'G') {
		adjustX = 0;
		adjustY = 0;
		playerIndex = 0;
	} else if(playerSymbol == 'B') {
		adjustX = 1;
		adjustY = 0;
		playerIndex = 1;
	} else if(playerSymbol == 'D') {
		adjustX = 2;
		adjustY = 0;
		playerIndex = 2;
	} else if(playerSymbol == 'P') {
		adjustX = 3;
		adjustY = 0;
		playerIndex = 3;
	} else if(playerSymbol == 'S') {
		adjustX = 0;
		adjustY = 1;
		playerIndex = 4;
	} else if(playerSymbol == '$') {
		adjustX = 1;
		adjustY = 1;
		playerIndex = 5;
	} else if(playerSymbol == 'L') {
		adjustX = 2;
		adjustY = 1;
		playerIndex = 6;
	} else if(playerSymbol == 'T') {
		adjustX = 3;
		adjustY = 1;
		playerIndex = 7;
	}

	int y = tileRowMap[positions[playerIndex]] + adjustY;
	int x = tileColMap[positions[playerIndex]] + adjustX;
	if(playerSymbol == 'S' || playerSymbol == '$' || playerSymbol == 'L' || playerSymbol == 'T') {
		theDisplay[y][x] = '_';
	} else {
		theDisplay[y][x] = ' ';
	}
	y = tileRowMap[newTile] + adjustY;
	x = tileColMap[newTile] + adjustX;
	theDisplay[y][x] = playerSymbol;
	positions[playerIndex] = newTile;
}

void TextDisplay::improve(int tile) {
	int y = tileRowMap[tile] - 3;
	int x = tileColMap[tile] + houses[tile];
	if(houses[tile] == 4) {
		theDisplay[y][x] = 'I';
	} else {
		theDisplay[y][x] = 'I';
	}
	houses[tile]++;
}
void TextDisplay::unimprove(int tile) {
	int y = tileRowMap[tile] - 3;
	int x = tileColMap[tile] + houses[tile] - 1;
	theDisplay[y][x] = ' ';
	houses[tile]--;
}

ostream &operator<<(std::ostream &out, const TextDisplay &td) {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			cout << td.theDisplay[i][j];
		}
		cout << endl;
	}
	return out;
}

TextDisplay::~TextDisplay(void) {
	for(int i = 0; i < rows; i++) {
		delete [] theDisplay[i];
	}
	delete [] theDisplay;
}

