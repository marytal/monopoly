#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "game.h"
#include "board.h"
#include "academicbuilding.h"
#include "residence.h"
#include "gym.h"

using namespace std;

Game::Game(void) {
	gameBoard = new Board();
	gameBoard->theGame = this;
	testingMode = false;
	playerTurn = 0;
	rolled = false;
	numDoubles = 0;
	quit = false;
}

void Game::removePlayer(int spot) {
	if(spot < numPlayers - 1) {
		for(int i = spot; i < numPlayers - 1; i++) {
			players[i] = players[i + 1];
		}
		players[numPlayers] = NULL;
	} else {
		players[spot] = NULL;
		playerTurn = 0;
		spot = 0;
	}
	numPlayers--;
	cout << "Removed the player." << endl;
	rolled = false;
	numDoubles = false;
	if(numPlayers == 1) {
		cout << "Congartulations " << players[spot]->name << "!" << endl;
		cout << "You is the winner! (Cue victory music)" << endl;
		cout << "GAME OVER." << endl;
		quit = true;
	} else {
		cout << "It is now: " << players[spot]->name << "\'s turn!" << endl;
	}
}

Game::~Game(void) {
	delete gameBoard;
//	for(int i = 0; i < gameBoard->numPlayers; i++) {
//		delete players[i];
//	}
}

void Game::testingON(void) {
	testingMode = true;
}
// Remove the array of players, and just get everything you need from the board. 
void Game::initPlayers(void) {
	char symbol;
	string name;
	cout << "How many players will be playing?" << endl;

	cin >> numPlayers;

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
	cout << *(gameBoard->td) << endl;
	cout << players[0]->getName() << " will start play." << endl;
	string fullCommand;
	getline(cin, fullCommand);
	while(getline(cin, fullCommand) && !quit) {
		getCommand(fullCommand);
	}
}


void Game::loadFile(string file) {
	// We need to have something that checks if the file
	// is actually there or not. 
	fstream loadfile(file.c_str());
	string readfile;
	int numOfPlayers;
	string playerName;
	char playerSymbol;
	int playerCash;
	int playerPos;
	int playerCups;

	loadfile >> numOfPlayers;
	numPlayers = numOfPlayers;
//	gameBoard->numPlayers = numOfPlayers;
//	cout << "Got here" << endl;
	getline(loadfile, readfile);
	for(int i = 0; i < numOfPlayers; i++) {
		getline(loadfile, readfile);
		stringstream ss(readfile);
		ss >> playerName >> playerSymbol;
		ss >> playerCash >> playerCups >> playerPos; // READ IN MORE FOR TIMS STUFF
//		cout << playerName << " " << playerSymbol << " " << playerCash << " " << playerCups << " " << playerPos << endl;
		players[i] = new Player(playerName, playerSymbol, playerCash, playerCups, playerPos);
		players[i]->setIndex(i);
		gameBoard->addPlayer(players[i]);
		gameBoard->td->notify(players[i]->getPos(), players[i]->getSymbol());
	}
	string name;
	string owner;
	int improvements;
	for(int i = 0; i < 28; i++) {
		loadfile >> name >> owner >> improvements;
//		cout << name << " " << owner << " " << improvements << endl;
		BoardTile *mytile = gameBoard->findTileByName(name);
		Ownable *myOwn = dynamic_cast<Ownable *>(mytile);
		if(myOwn) {
			AcademicBuilding *myAc = dynamic_cast<AcademicBuilding *>(myOwn);
			Residence *myRez = dynamic_cast<Residence *>(myOwn);
			Gym *myGym = dynamic_cast<Gym *>(myOwn);
			if(myGym) {
				if(owner == "BANK") {
					myGym->owner = NULL;
				} else {
					myGym->owner = gameBoard->findPlayerByName(owner);
					if(improvements == -1) {
						myGym->isMortgaged = true;
					}
				}
			} else if(myRez) {
				if(owner == "BANK") {
					myRez->owner = NULL;
				} else {
					myRez->owner = gameBoard->findPlayerByName(owner);
					if(improvements == -1) {
						myRez->isMortgaged = true;
					}
				}
			} else if(myAc) {
				if(owner == "BANK") {
					myAc->owner = NULL;
				} else {
					myAc->owner = gameBoard->findPlayerByName(owner);
					if(improvements == -1) {
						myAc->isMortgaged = true;
					} else {
						myAc->improvements = improvements;
						for(int i = 0; i < myAc->improvements; i++) {
							gameBoard->td->improve(myAc->tileNum);
						}
					}
				}
			}
		} else {
			cout << "Some odd error occurred..." << endl;
		}
	}
	// What to do here...
	// Do a for loop. 
	// Make the appropriate pointer, and set the 
	// values accordingly. 
	// Search for owner, find the player, and then 
	// manually set the owner address for each.  
	// Should probably make psuedocode
}

void Game::getCommand(string fullCommand) {
	srand(time(NULL)); // can this go somewhere else? 
	int roll1;
	int roll2;
	string command;
	stringstream getCommand(fullCommand);
	getCommand >> command;



	if(command == "roll") {
		if(rolled == true) {
			cout << "You've already rolled!" << endl;
		} else {
			if(testingMode) {
				if(getCommand >> roll1 >> roll2) {
					cout << roll1 << " ";
					cout << roll2 << " ";
					cout << "testing cheat" << endl;
				} else {
					roll1 = rand() % 6 + 1;
					roll2 = rand() % 6 + 1;
					cout << roll1 << " ";
					cout << roll2 << " ";
					cout << "testing no cheat" << endl;
				}
				if(roll1 == roll2) {
					if(numDoubles == 2) {
						cout << "You've rolled doubles 3 times in a row. Go to DC Tims." << endl;
						gameBoard->currentPlayer->setPos(10);
						gameBoard->currentPlayer->jailtime = 1;
						cout << "Please input 'next' and await your next turn to take action." << endl;
						rolled = true;
						return;


					} else {
						rolled = false;
						numDoubles++;
						gameBoard->getCurrentRoll(roll1, roll2);
						cout << "You rolled doubles! You may roll again." << endl;
					}
				} else {
					rolled = true;
					numDoubles = 0;
					gameBoard->getCurrentRoll(roll1, roll2);
				}
			} else {
				roll1 = rand() % 6 + 1;
				roll2 = rand() % 6 + 1;
				cout << roll1 << " " << roll2 << endl;

				if(roll1 == roll2) {
					if(numDoubles == 2) {
						cout << "You've rolled doubles 3 times in a row. Go to DC Tims." << endl;
						gameBoard->currentPlayer->setPos(10);
						gameBoard->currentPlayer->jailtime = 1;
						cout << "Please input 'next' and await your next turn to take action." << endl;
						rolled = true;
						gameBoard->changeTurn();
						return;

					} else {
						rolled = false;
						numDoubles++;
						gameBoard->getCurrentRoll(roll1, roll2);
						cout << "You've rolled doubles! You may roll again." << endl;
					}
				} else {
					rolled = true;
					numDoubles = 0;
					gameBoard->getCurrentRoll(roll1, roll2);
				}
			}
		}
	} else if(command == "next") {
		if (rolled) { // might run into problems here with the rolling history and jailtime method of getting a roll.
			if(playerTurn == numPlayers - 1){
				playerTurn = 0;
			} else {
				playerTurn++;
			}
		
			cout << "It is now " << players[playerTurn]->getName() << "'s turn!" << endl;
			gameBoard->changeTurn();
			numDoubles = 0;
			rolled = false;

			if(gameBoard->currentPlayer->jailtime > 0){
				rolled = true;
				gameBoard->jailHelper();
 // should it return?
			}

		} else {

			cout << "You haven't rolled yet!" << endl;
		}
	} else if(command == "trade") {
		string player;
		string val1;
		string val2;
		int cash;
		getCommand >> player >> val1 >> val2;
		stringstream readVal1(val1);
		stringstream readVal2(val2);
		if (readVal1 >> cash) {
			gameBoard->trade(player, cash, val2);
		} else if (readVal2 >> cash) {
			gameBoard->trade(player, val1, cash);
		} else {
			gameBoard->trade(player, val1, val2);
		}
	} else if(command == "improve") {
		string property;
		string action;
		getCommand >> property >> action;
		if(action == "buy") {
			gameBoard->improveBuy(property);
		} else if(action == "sell") {
			gameBoard->improveSell(property);
		} else {
			cout << "Invalid Command!" << endl;
		}
	} else if(command == "mortgage") {
		string property;
		getCommand >> property;
		gameBoard->mortgage(property);
	} else if(command == "unmortgage") {
		string property;
		getCommand >> property;
		gameBoard->unmortgage(property);
	} else if(command == "bankrupt") {
		cout << "trying to declare bankruptcy" << endl;
	} else if(command == "assets") {
		players[playerTurn]->printAssets();
		gameBoard->printAssets();
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
			//	saveToMe << "overwritten";
				saveFile(savefile);
				cout << savefile << " has been overwrtten.";
				cout << endl;
			} else {
				cout << "try saving differently." << endl;
			}
		} else {
			checkFile.close();
			//ofstream saveToMe(savefile.c_str());
			saveFile(savefile);
			cout << "File saved" << endl;
			cout << "saved into: " << savefile << endl;
		}
	} else if (command == "") {
		// Do nothing, this is a really hacky solution. 
	} else if(command == "q" || command == "quit") {
		cout << "Are you sure you want to quit the game?" << endl;
		cout << "All unsaved changes will be lost." << endl;
		string answer;
		cin >> answer;
		if(answer == "y" || answer == "yes") {
			quit = true;
		}
	} else { 
		cout << "Unrecognized command!" << endl;
	}
}

void Game::saveFile(string filename) {
	ofstream saveToMe(filename.c_str());
	saveToMe << gameBoard->numPlayers << endl;
	for(int i = 0; i < gameBoard->numPlayers; i++) {
		saveToMe << gameBoard->players[i]->name << " ";
		saveToMe << gameBoard->players[i]->symbol << " ";
		saveToMe << gameBoard->players[i]->cash << " ";
		saveToMe << gameBoard->players[i]->cups << " ";
		saveToMe << gameBoard->players[i]->position << " ";
		saveToMe << endl;
	}
	
	Gym *tempGym;
	AcademicBuilding *tempAc;
	Residence *tempRez;
	for(int i = 1; i < 40; i++) {
		//cout << "Debugging 1" << endl;
		tempGym = dynamic_cast<Gym *>(gameBoard->tiles[i]);
		tempAc  = dynamic_cast<AcademicBuilding *>(gameBoard->tiles[i]);
		tempRez = dynamic_cast<Residence *>(gameBoard->tiles[i]);
		//cout << "Debugging 2" << endl;
		if(tempGym) {
		//	cout << "Debugging 3" << endl;
			cout << tempGym->name << endl;
			saveToMe << tempGym->name;
			if(tempGym->owner == NULL) {
				saveToMe << " BANK";
			} else {
				saveToMe << " " << tempGym->owner->name;
			}
			if(tempGym->isMortgaged) {
				saveToMe << " -1" << endl;
			} else {
				saveToMe << " 0" << endl;
			}
		} else if(tempAc) {
			saveToMe << tempAc->name;
			if(tempAc->owner == NULL) {
				saveToMe << " BANK";
			} else {
				saveToMe << " " << tempAc->owner->name;
			}
			if(tempAc->isMortgaged) {
				saveToMe << " -1" << endl;
			} else {
				saveToMe << " " << tempAc->improvements << endl;
			}
		} else if(tempRez) {
			saveToMe << tempRez->name;
			if(tempRez->owner == NULL) {
				saveToMe << " BANK";
			} else {
				saveToMe << " " << tempRez->owner->name;
			}
			if(tempRez->isMortgaged) {
				saveToMe << " -1" << endl;
			} else {
				saveToMe << " 0" << endl;
			}
		}
		//cout << "Debugging 6" << endl;
	}
}
