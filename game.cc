#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "game.h"

using namespace std;

Game::Game(void) {
	gameBoard = new Board();
	testingMode = false;
}

void Game::testingON(void) {
	testingMode = true;
}
// Remove the array of players, and just get everything you need from the board. 
void Game::initPlayers(void) {
	char symbol;
	string name;
	cout << "How many players will be playing?" << endl;
	cin >> _numPlayers;
	numPlayers = _numPlayers;

	cout << "Here is the list of possible symbols. " << endl;
	cout << "G B D P S $ L T" << endl;
	cout << "Please type in the player name and " << endl;
	cout << "then the symbol to represent them." << endl;
	for(int i = 0; i < numPlayers; i++) {
		cin >> name >> symbol;
		players[i] = new Player(name, symbol);
		players[i]->setIndex(i);
		gameBoard->addPlayer(players[i]);

	}
	cout << "All the players have been added!" << endl;
	cout << "Now... LETS GET RICH!!" << endl;
	// NOTE, need to have error checking to make sure that
	// Someone isn't adding the same player twice, 
	// and if the symbol entered is valid. 

	// DELETE THIS PART AFTER
//	for(int i = 0; i < numPlayers; i++) 
//		players[i]->printAssets();
	
}

void Game::newGame(void){}; // We should delete this... right? 

void Game::runGame(void) {
	cout << players[0]->getName() << " will start play." << endl;
	string fullCommand;
	getline(cin, fullCommand);
	while(getline(cin, fullCommand)) {
		getCommand(fullCommand);
	}
}


void Game::loadFile(string file) {
	// We need to have something that checks if the file
	// is actually there or not. 
	fstream loadfile(file.c_str());
	string readfile;
	while(loadfile >> readfile) {
		cout << readfile << " ";
	}
	cout << endl;
}

void Game::getCommand(string fullCommand) {
	srand(time(NULL)); // can this go somewhere else? 
	int roll1;
	int roll2;
	string command;
	stringstream getCommand(fullCommand);
	getCommand >> command;
	if(command == "roll") {
		if(testingMode) {
			if(getCommand >> roll1 >> roll2) {
				cout << roll1 << " ";
				cout << roll2 << " ";
				cout << "testing cheat" << endl;
				gameBoard->getCurrentRoll(roll1, roll2);	
			} else {
				roll1 = rand() % 6 + 1;
				roll2 = rand() % 6 + 1;
				cout << roll1 << " ";
				cout << roll2 << " ";
				cout << "testing no cheat" << endl;
				gameBoard->getCurrentRoll(roll1, roll2);
			}
		} else {
			roll1 = rand() % 6 + 1;
			roll2 = rand() % 6 + 1;
			cout << roll1 << " " << roll2 << endl;
			gameBoard->getCurrentRoll(roll1, roll2);
			cout << "Write 'next' to switch to the next player." << endl;
		}
	} else if(command == "next") {
		if(playerTurn == numPlayers){
			playerTurn = 0;
		} else {
			playerTurn++;
		}
		
		cout << "It is now " << players[playerTurn]->getName() << "'s turn!" << endl;
		gameBoard->changeTurn();
	} else if(command == "trade") {
		cout << "trying to trade" << endl;
	} else if(command == "improve") {
		cout << "trying to improve" << endl;
	} else if(command == "mortgage") {
		cout << "trying to mortgage" << endl;
	} else if(command == "unmortgage") {
		cout << "trying to unmortgage" << endl;
	} else if(command == "bankrupt") {
		cout << "trying to declare bankruptcy" << endl;
	} else if(command == "assets") {
		players[playerTurn]->printAssets();
	} else if(command == "save") {
		string savefile;
		getCommand >> savefile;
		ifstream checkFile(savefile.c_str());
		if(checkFile.is_open()) {
			cout << "Overwrite " << savefile << "? (yes/no)";
			cout << endl;
			string answer;
			getline(cin, answer);
			if(answer == "yes") {
				checkFile.close();
				ofstream saveToMe(savefile.c_str());
				saveToMe << "overwritten";
				cout << savefile << " has been overwrtten.";
				cout << endl;
			} else {
				cout << "try saving differently." << endl;
			}
		} else {
			checkFile.close();
			ofstream saveToMe(savefile.c_str());
			saveToMe << "File saved" << endl;
			cout << "saved into: " << savefile << endl;
		}
	} else if (command == "") {
		// Do nothing, this is a really hacky solution. 
	} else { 
		cout << "Unrecognized command!" << endl;
	}
}



