#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

#include "game.h"
#include "board.h"
#include "boardtile.h"
#include "ownable.h"
#include "unownable.h"
#include "player.h"
#include "textdisplay.h"
#include "gym.h"
#include "residence.h"
#include "academicbuilding.h"

using namespace std;

int main(int argc, char* argv[]) {
	
	Game g;

	string readfile;
	string myfile;
	if(argc > 1) {
		string firstArg = argv[1];
		if(firstArg == "-load") {
			cout << "loading file... " << endl;
			g.loadFile(argv[2]);
		} else if (firstArg == "-testing") {
			cout << "Testing mode enabled" << endl;
			g.testingON();
		} else {
			cout << "Unrecognized command. Exiting." << endl;
			exit(EXIT_FAILURE);
		}
	} else {
		cout << "No arguments read - starting game" << endl;
	}
	g.initPlayers();	
	g.runGame();
/*
	string fullCommand;
	while(getline(cin, fullCommand)) {
		g.getCommand(fullCommand);
	}
*/
	cout << "Program finished without errors." << endl;
	return 0;
}

// THE DEPARTED CODE

//	srand(time(NULL));
/*
	string command; 
	string fullCommand;

	while(getline(cin, fullCommand)) {
		stringstream getCommand(fullCommand); // make this "faster" 
		getCommand >> command;
		if(command == "roll") {
			if(testingMode) {
				if(getCommand >> roll1 >> roll2) {
					cout << roll1 << " " << roll2 << " testing \"cheat\"" << endl;
				} else {
					roll1 = rand() % 6 + 1;
					roll2 = rand() % 6 + 1;
					cout << roll1 << " " << roll2 << " non-testing" << endl;
				}
			} else {
				roll1 = rand() % 6 + 1;
				roll2 = rand() % 6 + 1;
				cout << roll1 << " " << roll2 << endl;
			}
		} else if(command == "next") {
			cout << "it is the next players turn now." << endl;
		} else if(command == "trade") {
			// read in some values to make a trade
		} else if(command == "improve") {
			// read in some values to improve property
		} else if(command == "mortagage") {
			// read in some values to mortgage stuff
		} else if(command == "unmortgage") {
			// attempt to unmortgage thigns
		} else if(command == "bankrupt") {
			cout << "You are attempting to declare bankruptcy." << endl;
		} else if(command == "assets") {
			cout << "You have no assets. (yet)" << endl;
		} else if(command == "save") {

			string savefile;
			getCommand >> savefile;
			ifstream checkFile(savefile.c_str());
			if(checkFile.is_open()) {
				cout << "Are you sure you want to overwrite \"" << savefile << "\"? (yes/no)" << endl;
				string answer;
				getline(cin, answer);
				if(answer == "yes") {
					checkFile.close();
					ofstream saveToMe(savefile.c_str());
					saveToMe << "overwritten";
					cout << "\"" << savefile << "\" has been overwritten." << endl;
				} else {
					cout << "Please try the save command again with a different filename." << endl;
				}
			} else {
				checkFile.close();
				ofstream saveToMe(savefile.c_str());
				saveToMe << "File saved" << endl;
				cout << "The file has been saved into \"" << savefile << "\"" << endl;
			}
		} else {
			cout << "Unrecognized command!" << endl;
		}
	}
*/
