#include <cstdlib>
#include <ctime>
#include "board.h"
#include "unownable.h"
#include "ownable.h"
#include "academicbuilding.h"
#include "gym.h"
#include "residence.h"
#include "player.h"
#include "game.h"

#include <sstream>

using namespace std;

const string trolluser = "Stop trying to break the game. -_-";

void Board::cantPay(int amount, Player *creditor) {
	cout << "You need to pay $" << amount << "." << endl;
	cout << "You do not have sufficient funds to pay this." << endl;
	cout << "You can mortgage properties that you own, sell" << endl;		// giving options to the player
	cout << "improvements or trade properties to get the cash." << endl;	// when they can't pay.
	cout << "Alternatively, if you feel that there isn't much" << endl;
	cout << "chance of recovering, You can declare bankruptcy." << endl;
	while (currentPlayer->cash < amount) {
		string command;
		string commandLine;
		getline(cin, commandLine);
		stringstream getCommand(commandLine);
		getCommand >> command;
		if("bankrupt" == command) {						// Small interpreter loop to give player minimal choices
			bankrupt(creditor);							// For ease, a save option isn't given, 
			return;										// So the player must save before quitting.
		} else if ("mortgage" == command) {
			string property;
			getCommand >> property;
			mortgage(property);
		} else if ("improve" == command) {
			string property;
			string action;
			getCommand >> property >> action;
			if("buy" == action) {
				cout << "Thats a pretty bad idea." << endl;
				cout << "You must first pay of your creditor before making other purchases." << endl;
			} else if("sell" == action) {
				improveSell(property);
			}
		} else if("trade" == command) {
			string player;
			string val1;
			string val2;
			int cash;
			getCommand >> player >> val1 >> val2;
			stringstream readVal1(val1);
			stringstream readVal2(val2);
			if(readVal1 >> cash) {
				trade(player, val1, cash);
			} else if(readVal2 >> cash) {
				trade(player, val1, cash);
			} else {
				trade(player, val1, val2);
			}
		}
	}
	currentPlayer->pay(amount);		// The one of two ways the function exits, 
	if(creditor) {					// You either pay off what you need to, or declare bankrupt.
		creditor->getPaid(amount);
	}
	cout << "You managed to scrape together the funds to pay the bill." << endl;
}

void Board::bankrupt(Player *creditor) {
	Ownable *tempHold[28];
	int k = 0;
	if (creditor == NULL) {
		for(int i = 0; i < 40; i++) {
			Ownable *myOwn = dynamic_cast<Ownable *>(tiles[i]);		// If bankrupt to the board... 
			if(myOwn && (myOwn->owner == currentPlayer)) {
				myOwn->owner = NULL;
				tempHold[k] = myOwn;
				k++;
			}
		}
		removePlayer(currentPlayer);
		for(int i = 0; i <= k; i++) {
			auction(tempHold[i]);
		}
	} else {
		currentPlayer->pay(currentPlayer->cash);
		creditor->getPaid(currentPlayer->cash);
		for(int i = 0; i < 40; i++) {
			Ownable *myOwn = dynamic_cast<Ownable *>(tiles[i]);		// If bankrupt to a player...
			if(myOwn && (myOwn->owner == currentPlayer)) {
				myOwn->owner = creditor;
				cout << creditor->name << " now owns " << myOwn->name << endl;
			}
		}
		removePlayer(currentPlayer);
	}

}

void Board::removePlayer(Player *delMe) {
	int spot = 0;
	while(players[spot] != delMe) {
		spot++;
	}
	if(spot < numPlayers - 1) {
		for(int i = spot; i < numPlayers - 1; i++) {	// Deleting a player, and then...
			players[i] = players[i + 1];
		}
		players[numPlayers] = NULL;
		currentPlayer = players[spot];
	} else {
		delete players[spot];
		players[spot] = NULL;
		currentPlayer = players[0];
	}
	numPlayers--;
	for(int j = 0; j < numPlayers; j++) {
		cout << players[j]->name << endl;
	}

	theGame->removePlayer(spot);			// redundancy problem, getting rid of the player here too.
}

int rollstore1 = 0;		// Hacky solution to an odd problem here. 
int rollstore2 = 0;

void Board::getCurrentRoll(int roll1, int roll2) {
  roll1 = roll1;
  roll2 = roll2;
  cout << "The current player is: " << currentPlayer->name << endl;
  rollstore1 = roll1;
  rollstore2 = roll2;
  bool passedGo = false;
  int newPos = currentPlayer->getPos() + roll1 + roll2;
  if(newPos > 39){ // greater or equals? // this is fine~
    newPos = newPos % 40;
	currentPlayer->getPaid(200);					// Determining if after a roll, 
	passedGo = true;								// A player passes go or not.
  }
  currentPlayer->setPos(newPos);
  td->notify(newPos, currentPlayer->getSymbol());
  cout << *td << endl;
	if(passedGo) {
		if(newPos > 0) {
			cout << "You passed GO!" << endl;
			cout << "200 dollars have been added to your Watcard." << endl;
		}
	}
  	getTileAction();	// Now that player is moved, find out what happens to them. 
}

void Board::auction(BoardTile *tile){
  // what if no one bids??? Undefined behaviour? No one gets the property?

  int _currentPlayerIndex = currentPlayerIndex + 1;
  int highest_bid = 1;
  int player_bid = 0;
  int playersInRunning = numPlayers;	
  string bidders [8];
  string player_input;
  cout << "Let's start the bidding." << endl;

  for(int i = 0; i < numPlayers; i++){
    if(players[i] == NULL){
      bidders[i] = "";
    } else {
      bidders[i] = players[i]->getName();
    }
  }

  while(true){

    if(_currentPlayerIndex == 8){
      _currentPlayerIndex = 0;
    }

    if(playersInRunning == 1){
      _currentPlayerIndex--;
      break;
    }

    if(bidders[_currentPlayerIndex] != ""){

      cout << bidders[_currentPlayerIndex] << ", the current bid is at $" << highest_bid << 
      ". Input an integer higher than the current bid or enter 'w' to withddraw." << endl;
      cin >> player_input;
      stringstream ss(player_input);
      if(ss >> player_bid){
        if(player_bid <= highest_bid){
          cout << "That is not a valid bid. You are withdrawn for being silly." << endl;
          bidders[_currentPlayerIndex] = "";
          playersInRunning--;
        } else {
          highest_bid = player_bid;
          cout << "Thank you for your interest and good luck." << endl;
        }
      } else {
        cout << "Very well, your loss." << endl;
        bidders[_currentPlayerIndex] = "";
        playersInRunning--;
      }

    }

    _currentPlayerIndex++;

  }

  Player *winner = players[_currentPlayerIndex];

  cout << "Congratulations, " << winner->getName() << "! You are now the proud owner of " <<
  tile->name << "!" << endl;
  cout << "You have paid $" << highest_bid << " to the bank." << endl; 

  Ownable *ownable = dynamic_cast<Ownable *>(tile);
  ownable->owner = winner;
  winner->pay(highest_bid);
}

void Board::getTileAction(){	// Pretty readable code right here (particularly proud of my partner)
  BoardTile *currentTile = tiles[currentPlayer->getPos()];
  cout << "You rolled: " << rollstore1 << " " << rollstore2 << endl;
  cout << endl << "You've landed on " << currentTile->name << "!" << endl;
  if(currentTile->ownable) {
    Ownable *ownable = dynamic_cast<Ownable *>(currentTile);
    if(ownable->owner == currentPlayer){
      cout << "You already own this property." << endl;
    } else if(ownable->owner != NULL){
		if(ownable->isMortgaged) {
			cout << "You do not have to pay rent, this property is currently mortgaged." << endl;
		} else {
      		Player *tileOwner = ownable->owner;
      		int rent = ownable->rent();
      		if(currentPlayer->canPay(rent)){
        		cout << "You've paid $" << rent  << " to " << tileOwner->getName() << " for landing on his/her property." << endl;  
        		currentPlayer->pay(rent);
        		tileOwner->getPaid(rent);
        		cout << "You now have $" << currentPlayer->getBalance() << " in your account." << endl;
        
      		} else {
				cantPay(rent, tileOwner);
      		}
		}
    } else if(ownable->owner == NULL){
      int price = ownable->getPurchasePrice();
      // if(!currentPlayer->canPay(price)){
      //   cout << "You cannot afford this property at this time." << endl;
      //   return;
      // }
      
      cout << "Would you like to buy this property? It costs $" << price << "." << endl;
      cout << "You currently have $" << currentPlayer->getBalance() << " in your account." << endl;  
      cout << "(y/n)" << endl;
      char response;
      cin >> response;
      if(response == 'n'){
        auction(currentTile);	// This is a problem, where even though it costs more than player cash,
								// the game allows you to buy the property. 
      } else {
        //check if can pay?
        currentPlayer->pay(price);
        ownable->owner = currentPlayer;
		currentPlayer->ownedProperties[currentPlayer->numOwned] = ownable;
		currentPlayer->numOwned++;
        cout << "Congratulations! You are the brand new owner of " << currentTile->name << "!" << endl; // name not working

        Gym *gym = dynamic_cast<Gym *>(ownable);
        AcademicBuilding *ab = dynamic_cast<AcademicBuilding *>(ownable);
        if(ab && ab->isMonopoly()){
          cout << "Even better, you now own a monopoly. Feel free to start making improvements!" << endl;
        }
      }
    }
  } else {
	unownableAction(currentTile); // These probably could have been implemented as a class.
  }
}


void Board::jailHelper(){	// Called when getting someone to jail.
	
  cout << "You're still stuck in the Tim's line." << endl;

  string command;
  while(true){
    cout << "Pick a command: roll (r), use cup (c), pay (p)" << endl;
    cin >> command;
    if(command == "r"){
      srand(time(NULL));
      int dice1 = rand() % 6 + 1;
      int dice2 = rand() % 6 + 1;
      cout << "You've rolled: " << dice1 << " " << dice2 << endl;
      if(dice1 == dice2){
        cout << "Congratulations! You're a free bird! Enjoy the finer things in life." << endl;
        currentPlayer->jailtime = 0;
        break;
      } else {
        currentPlayer->jailtime += 1;
        if(currentPlayer->jailtime == 4){
          cout << "This was your third try." << endl;
          if(currentPlayer->canPay(50)){
            cout << "You have paid $50 to the bank and are free to go." << endl;
            currentPlayer->pay(50);
            currentPlayer->jailtime = 0;
          } else {
            cout << "You cannot afford to leave jail. Either get more money or declare bankruptcy." << endl;
            cantPay(50, NULL);	
          }
        }
        break;
      }

    } else if(command == "c"){
      if (currentPlayer->cups > 0){
        cout << "Congratulations! You're a free bird! Enjoy the finer things in life." << endl;
        currentPlayer->jailtime = 0;
        break;
        currentPlayer->cups--;	// Get rid of that cup. 
      }

    } else if(command == "p"){
        if(currentPlayer->canPay(50)){
          cout << "You have paid $50 to the bank and are free to go." << endl;
          currentPlayer->pay(50);
          currentPlayer->jailtime = 0;
          break;
        } else {
          cout << "You cannot afford the $50 fine. Either get more money, declare bankruptcy, or wait to roll again." << endl;
          cantPay(50, NULL);
          break;
        }

    } else {
      cout << "invalid command, try again." << endl;	// Helping the player make the right choice. :-)
    }
  }

}

void Board::unownableAction(BoardTile *tile) {
	// A somewhat inflexible implementation, 
	// especially since the visitor would have worked so well, 
	// since then the entire function wouldn't need to change, 
	// just the function for that one tile. 
	Unownable *mytile = dynamic_cast<Unownable *>(tile);
	if(mytile) {
		string name = mytile->getName();
		if(name == "COLLECT OSAP") {
			cout << "200 dollars hve been aded to your Watcard" << endl;
			// (Board takes care of this anyways, so just do the thing if you get 400, else pass. 
		} else if(name == "GO TO TIMS") {
			currentPlayer->setPos(10);
			td->notify(10, currentPlayer->getSymbol());
			cout << *td << endl;
			cout << "You are now in the DC Tims Lane." << endl;
			cout << "You have 3 turns in which you can attempt to roll doubles and exit." << endl;
			cout << "You can pay $50 on any of these turns and exit the Lane." << endl;
			cout << "If at the end of your three turns you have not managed" << endl;
			cout << "To roll doubles, you must pay the $50 fine and exit." << endl;
			cout << "Alternatively, if you have a \"Roll Up the Rims\" cup," << endl;
			cout << "you may use it to exit the lane on your next turn. Please enter 'next'." << endl;

      currentPlayer->jailtime = 1;
			// run some sort of thing to make this work. 
		} else if(name == "GOOSE NESTING") {
			cout << "You have been attacked by a flock of geese!" << endl;
			cout << "Luckily, you come away unscathed, and without loss of assets." << endl;
		} else if(name == "COOP FEE") {
			if(currentPlayer->canPay(150)) {
				currentPlayer->pay(150); // Put this as a constant somehwere. 
				cout << "You paid the $150 co-op fee." << endl;
			} else {
				cout << "Please find ways to aquire the funds to pay the co-op fee." << endl;
				cantPay(150, NULL);
			}
		} else if(name == "DC Tims Line") {
			// Do nothing
			cout << "Landed on DC Times lane" << endl;
		} else if(name == "TUITION") {
			int worth = playerNetworth();
			cout << "You must pay either the flat amount of $300 or 10\% of your current net worth." << endl;
			cout << "Your current net worth is: $" << worth;
			cout << " Which will it be? (flat/percent)" << endl;
			string answer;
			cin >> answer;
			if(answer == "flat") {
				currentPlayer->pay(300);
			} else {
				currentPlayer->pay(playerNetworth() / 10);
			}
		} else if(name == "SLC") {
			slcHelper();
		} else if(name == "NEEDLES HALL") {
			int change = needlesHelper();
			if(change == 0) {
				cout << "You've found a Roll up the Rims cup!" << endl;
				cout << "You can use it later to get out of the Tims Line!" << endl;
			} if(change > 0) {
				cout << "A stroke of good-fortune: You recieved $" << change << "!" << endl;
				currentPlayer->getPaid(change);
			} else {
				cout << "Sadly, you need to pay $" << -1 * change <<  endl;
				if (currentPlayer->canPay(-1 * change)) {
					currentPlayer->pay(-1 * change);
				} else {
					cantPay(-1 * change, NULL);
				}
			}
		}
	} 
}

int needlesHelper(void) {		// The thing that takes care of the random process for determining money
	srand(time(NULL));			// and sending out tims cups
	int mynum = rand() % 100 + 1;
	if(mynum == 100) {
		return 0;	// Signifies roll up the rim in code)
	}
	else {
		mynum = rand() % 18 + 1;
		if(mynum == 1) {
			return -200;
		} else if(mynum == 18) {
			return 200;
		} else if((mynum == 2) || (mynum == 3)) {
			return -100;
		} else if((mynum == 16) || (mynum == 17)) {
			return 100;
		} else if((4 <= mynum) && (mynum <= 6)) {
			return -50;
		} else if((13 <= mynum) && (mynum <=15)) {
			return 50;
		} else {
			return 25;
		}
	}
}

int Board::slcHelper(void) {		// Random process for moving people.
  int mynum = rand() % 100 + 1;
  if(mynum == 100) {
	  cout << "You've found a roll up the Rims cup!" << endl;
      cout << "You may use it later to get out of the DC Tims Lane!" << endl;
  } else {
	cout << "This square will move you automatically to a random tile." << endl;
	cout << "Type in \"go\" to proceed." << endl;
	string answer;
	cin >> answer;
	int move = 0;
	bool directMove = false;
	int directTile = 0;
	srand(time(NULL));
	int mynum = rand() % 24 + 1;
	if ((1 <= mynum) && (mynum <= 3)) {
		move = -3;
	} else if ((4 <= mynum) && (mynum <= 7)) {
		  move = -2;
	} else if ((8 <= mynum) && (mynum <= 11)) {
		  move = -1;
	} else if ((12 <= mynum) && (mynum <= 14)) {
		  move = 3;
	} else if ((15 <= mynum) && (mynum <= 18)) {
		  move = 2;
	} else if ((19 <= mynum) && (mynum <= 22)) {
		  move = 1;
	} else if (mynum == 23) {
		directMove = true;
		directTile = 0;
	} else if (mynum == 24) {
		directMove = true;
		directTile = 10;
	}

	if(directMove && directTile == 0) {
		currentPlayer->getPaid(200);
		currentPlayer->setPos(0);
		td->notify(0, currentPlayer->getSymbol());
		cout << *td << endl;
		cout << "You've advanced to collect OSAP!" << endl;
		cout << "200 dollars have been added to your Watcard." << endl;
	} else if(directMove && directTile == 10) {
		currentPlayer->setPos(10);
		td->notify(10, currentPlayer->getSymbol());
		cout << *td << endl;
		cout << "Go to DC Tims." << endl;
	 } else {
			bool passedGo = false;
			int newPos = currentPlayer->getPos() + move;
			if(newPos > 39){ // greater or equals? // this is fine~
				newPos = newPos % 40;
				currentPlayer->getPaid(200);
				passedGo = true;
			}
			currentPlayer->setPos(newPos);
			td->notify(newPos, currentPlayer->getSymbol());
			cout << *td << endl;
			if(passedGo) {
				if(newPos > 0) {
					cout << "You passed GO!" << endl;
					cout << "200 dollars have been added to your Watcard." << endl;
				}
			}
			getTileAction();
		}
  }
}


void Board::changeTurn(void) {			// Gets called at the end of every turn. 
  if(currentPlayerIndex == numPlayers - 1){
    currentPlayerIndex = 0;
  } else {
    currentPlayerIndex++;
  }
  currentPlayer = players[currentPlayerIndex];
}

bool Board::isOwnable(BoardTile *tile){
  return tile->ownable;	// Just a check to see if someone can own the tile. 
						// Somewhat bad because now boardtiles seem to have knowledge of subclasses. 
}

int Board::getTilePrice(Ownable *tile){
  return tile->getPurchasePrice();		
}

void Board::addPlayer(Player * newPlayer) {
	players[numPlayers] = newPlayer;
  numPlayers++;
  if(currentPlayer == NULL){
    currentPlayer = newPlayer;		// Called in the initialization of players, whether from file or newgame. 
  }
  td->notify(0, newPlayer->symbol);
}



void Board::printAssets(void) {
	Ownable *temp;
	cout << "Properties" << endl;
	for(int i = 0; i < 40; i++) {
		temp = dynamic_cast<Ownable *>(tiles[i]);
		if(temp) {
			if(temp->owner == currentPlayer) {		// Somewhat modest in that we should print out 
				cout << "    " << temp->getName();	// improvements as well... 
				if (temp->isMortgaged) {
					cout << " mortgaged" << endl;
				} else {
					cout << endl;
				}
			}
		}
	}
}

int Board::playerNetworth(void) {	// calculates net worth in those times that we actually need to.
	int totalworth = currentPlayer->cash;
	Ownable *temp;
	for(int i = 0; i < 40; i++) {
		temp = dynamic_cast<Ownable *>(tiles[i]);
		if(temp) {
			if(temp->owner == currentPlayer) {
				Gym *myGym = dynamic_cast<Gym *>(temp);
				AcademicBuilding *myAc = dynamic_cast<AcademicBuilding *>(temp);
				Residence *myRez = dynamic_cast<Residence *>(temp);
				if(myGym) {
					totalworth = totalworth + 150;
				} else if(myRez) {
					totalworth = totalworth + 200;
				} else {
					totalworth = totalworth + myAc->purchasePrice + myAc->improvements * myAc->improvementPrice;
				}
			}
		}
	}
	return totalworth;
}

				

void makeFaculty(BoardTile *first, BoardTile *second, BoardTile *third){
  AcademicBuilding *_first = dynamic_cast<AcademicBuilding *>(first);		// grouping faculties
  AcademicBuilding *_second = dynamic_cast<AcademicBuilding *>(second);
  AcademicBuilding *_third = dynamic_cast<AcademicBuilding *>(third);


  _first->addFaculty(_second, _third);
  _second->addFaculty(_first, _third);
  if(_third){
    _third->addFaculty(_first, _second);
  }
}

void setRez(BoardTile *rez1, BoardTile *rez2, BoardTile *rez3, BoardTile *rez4) {
	Residence *first = dynamic_cast<Residence *>(rez1);
	Residence *secnd = dynamic_cast<Residence *>(rez2);
	Residence *third = dynamic_cast<Residence *>(rez3);		// grouping residences
	Residence *forth = dynamic_cast<Residence *>(rez4);		// by giving appropriate pointers
	first->setResidencies(secnd, third, forth);
	secnd->setResidencies(first, third, forth);
	third->setResidencies(first, secnd, forth);
	forth->setResidencies(first, secnd, third);
}

void setGym(BoardTile *gym1, BoardTile *gym2) {		// grouping Gyms
	Gym *first = dynamic_cast<Gym *>(gym1);			// by giving appropriate poynters
	Gym *secnd = dynamic_cast<Gym *>(gym2);
	first->setOtherGym(secnd);
	secnd->setOtherGym(first);
}

Board::Board(void) {	// Massive harcoded initalization. 
  tiles[0] = new Unownable("COLLECT OSAP");
  tiles[1] = new AcademicBuilding("AL",1, 40, 50, "Arts1", 2, 10, 30, 90, 160, 250);
  tiles[2] = new Unownable("SLC");
  tiles[3] = new AcademicBuilding("ML",3, 60, 50, "Arts1", 4, 20, 60, 180, 320, 450);
  makeFaculty(tiles[1], tiles[3], NULL);
  tiles[4] = new Unownable("TUITION");
  tiles[5] = new Residence("MKV");
  tiles[6] = new AcademicBuilding("ECH",6, 100, 50, "Arts2", 6, 30, 90, 270, 400, 550);
  tiles[7] = new Unownable("NEEDLES HALL");
  tiles[8] = new AcademicBuilding("PAS",8, 100, 50, "Arts2", 6, 30, 90, 270, 400, 550);
  tiles[9] = new AcademicBuilding("HH",9, 120, 50, "Arts2", 8, 40, 100, 300, 450, 600);
  makeFaculty(tiles[6], tiles[8], tiles[9]);
  tiles[10] = new Unownable("DC Tims Line");
  tiles[11] = new AcademicBuilding("RCH", 11, 140, 100, "Eng", 10, 50, 150, 450, 625, 750);
  tiles[12] = new Gym("PAC");
  tiles[13] = new AcademicBuilding("DWE", 13, 140, 100, "Eng", 10, 50, 150, 450, 625, 750);
  tiles[14] = new AcademicBuilding("CPH", 14, 160, 100, "Eng", 12, 60, 180, 500, 700, 900);
  makeFaculty(tiles[11], tiles[13], tiles[14]);
  tiles[15] = new Residence("UWP");
  tiles[16] = new AcademicBuilding("LHI", 16, 180, 100, "Health", 14, 70, 200, 550, 750, 950);
  tiles[17] = new Unownable("SLC");
  tiles[18] = new AcademicBuilding("BMH", 18, 180, 100, "Health", 14, 70, 200, 550, 750, 950);
  tiles[19] = new AcademicBuilding("OPT", 19, 200, 100, "Health", 16, 80, 220, 600, 800, 1000);
  makeFaculty(tiles[16], tiles[18], tiles[19]);
  tiles[20] = new Unownable("Goose Nesting");
  tiles[21] = new AcademicBuilding("EV1", 21, 220, 150, "Env", 18, 90, 250, 700, 875, 1015);
  tiles[22] = new Unownable("NEEDLES HALL");
  tiles[23] = new AcademicBuilding("EV2", 23, 220, 150, "Env", 18, 90, 250, 700, 875, 1015);
  tiles[24] = new AcademicBuilding("EV3", 24, 240, 150, "Env", 20, 100, 300, 750, 925, 1100);
  makeFaculty(tiles[21], tiles[23], tiles[24]);
  tiles[25] = new Residence("V1");
  tiles[26] = new AcademicBuilding("PHYS", 26, 260, 150, "Sci1", 22, 110, 330, 800, 975, 1150);
  tiles[27] = new AcademicBuilding("B1", 27, 260, 150, "Sci1", 22, 110, 330, 800, 975, 1150);
  tiles[28] = new Gym("CIF");
  tiles[29] = new AcademicBuilding("B2", 29, 280, 150, "Sci1", 24, 120, 360, 850, 1025, 1200);
  makeFaculty(tiles[26], tiles[27], tiles[29]);
  tiles[30] = new Unownable("GO TO TIMS");
  tiles[31] = new AcademicBuilding("EIT", 31, 300, 200, "Sci2", 26, 130, 390, 900, 1100, 1275);
  tiles[32] = new AcademicBuilding("ESC", 32, 300, 200, "Sci2", 26, 130, 390, 900, 1100, 1275);
  tiles[33] = new Unownable("SLC");
  tiles[34] = new AcademicBuilding("C2", 34, 320, 200, "Sci2", 28, 150, 450, 1000, 1200, 1400);
  makeFaculty(tiles[31], tiles[32], tiles[34]);
  tiles[35] = new Residence("REV");
  tiles[36] = new Unownable("NEEDLES HALL");
  tiles[37] = new AcademicBuilding("MC", 37, 350, 200, "Math", 35, 175, 500, 1100, 1300, 1500);
  tiles[38] = new Unownable("COOP FEE");
  tiles[39] = new AcademicBuilding("DC", 39, 400, 200, "Math", 50, 200, 600, 1400, 1700, 2000);
  makeFaculty(tiles[37], tiles[39], NULL);
  setRez(tiles[5], tiles[15], tiles[25], tiles[35]); // Hopefully this works~
  setGym(tiles[12], tiles[28]);
  td = new TextDisplay();
  currentPlayerIndex = 0;
  currentPlayer = NULL;
  numPlayers = 0; 
}

Board::~Board(void) {		// Destructor 
	delete td;		
	for(int i = 0; i < 40; i++) {
		delete tiles[i];
	}
	for(int i = 0; i < numPlayers; i++) {
		delete players[i];
	}
}

// initialize facultyMembers for all deez bitchez

BoardTile *Board::findTileByName(string property){	// Very useful function. 
  for(int i = 0; i < 40; i++){ // 28 magic number	// could probably be replaced with a map. 
    if(tiles[i]->name == property){
      return tiles[i];
    }
  }
}

//Ownable *Board::findOwnableByName(string property) {}
//AcademicBuilding *Board::findAcademicByName(string property) {}

Player *Board::findPlayerByName(string name){	// very useful function, 
  for(int i = 0; i < numPlayers; i++){			// could be replaced with a map. 
    if(players[i]->getName() == name){
      return players[i];
    }
  }
}

void Board::trade(string name, int amount, string property){ 
  // Waaay too many ways to get invalid input here. 
  // TO DO: check if name owns property, if not return "Invalid request"
  // TO DO: check if current player can afford trade
  char response;
  cout << "Would " << name << " like to trade " << property << " for " << amount << "?" << endl;
  cout << "(y/n)" << endl; // accept or reject response necessary?
  cin >> response;
  if(response == 'n'){
    return; 
  }

  Player *tmpPlayer = findPlayerByName(name);
  BoardTile *findTile = findTileByName(property);
  Ownable *tmpTile = dynamic_cast<Ownable *>(findTile); //findOwnableByName(property);
  if(tmpTile) {
  // players pay and receive money
  	tmpPlayer->getPaid(amount);
  	currentPlayer->pay(amount);
  // change owner of board
  	tmpTile->setOwner(currentPlayer); 

  	cout << "Trade completed!" << endl;
   } else {
	 cout << trolluser << endl;
  }
}

void Board::trade(string name, string property1, string property2){
  // TO DO: check if current player owns property1.
  // TO DO: check if name owns property2, if not return "Invalid request"
  char response;
  cout << "Would " << name << " like to trade " << property2 << " for " << property1 << "?" << endl;
  cout << "(y/n)" << endl; // accept or reject response necessary?
  cin >> response;
  if(response == 'n'){
    return; 
  }

  Player *tmpPlayer = findPlayerByName(name);
//  BoardTile *prop1 = findTileByName(property1);
//  BoardTile *prop2 = findTileByName(property2);

	BoardTile *findTile1 = findTileByName(property1);
	BoardTile *findTile2 = findTileByName(property2);
	Ownable *prop1 = dynamic_cast<Ownable *>(findTile1); //findOwnableByName(property1);
	Ownable *prop2 = dynamic_cast<Ownable *>(findTile2); //findOwnableByName(property2);
	if(prop1 && prop2) {
		
  // change owner of board
  		prop1->setOwner(tmpPlayer); // TO DO field
  		prop2->setOwner(currentPlayer);

  		cout << "Trade completed!" << endl;
	} else {
		cout << trolluser << endl;
	}
}

void Board::trade(string name, string property, int amount){
  // TO DO: check if name owns property2, if not return "Invalid request"
  // TO DO: check if current player owns property1.
  char response;
  cout << "Would " << name << " like to trade " << property << " for " << amount << "?" << endl;
  cout << "(y/n)" << endl; // accept or reject response necessary?
  cin >> response;
  if(response == 'n'){
    return; 
  }

  Player *tmpPlayer = findPlayerByName(name);
  BoardTile *findTile = findTileByName(property);
  Ownable *tmpTile = dynamic_cast<Ownable *>(findTile); //findOwnableByName(property);
  if(tmpTile) {
  // players pay and receive money
  	tmpPlayer->pay(amount);
  	currentPlayer->getPaid(amount);
  // change owner of board
  	tmpTile->setOwner(tmpPlayer); // TO DO field
 	cout << "Trade completed!" << endl;
  } else {
	  cout << trolluser << endl;
  }
}

void Board::improveSell(string property){
  // TO DO: check if monopoly, if owned by current player, if enough money, if any improvements left to buy
  BoardTile *findTile = findTileByName(property);
  AcademicBuilding *tmp = dynamic_cast<AcademicBuilding *>(findTile); //= findAcademicByName(property);
  if(tmp) {
  	currentPlayer->getPaid(tmp->getImprovementPrice() / 2);
	tmp->unimprove();
	td->unimprove(tmp->tileNum);
	cout << *td << endl;
  //  tmp->improvements -= 1;
//  tmp->totalPrice -= tmp->improvementPrice; 
  } else {
	  cout << trolluser << endl;
  }
}

void Board::improveBuy(string property){
  BoardTile *findTile = findTileByName(property);  
  AcademicBuilding *tmp = dynamic_cast<AcademicBuilding *>(findTile);// = findAcademicByName(property);
	if(tmp) {
		if(tmp->isMonopoly()) {
			currentPlayer->pay(tmp->getImprovementPrice());
			tmp->improve();
			cout << tmp->tileNum << endl;
			td->improve(tmp->tileNum);
			cout << *td << endl;
			cout << property << " has been successfully improved." << endl;
		} else {
			cout << "You do not own all buildings in the faculty, and so cannot make improvements." << endl;
		}
//  tmp->improvements += 1;
//  tmp->totalPrice += tmp->improvementPrice;
	} else {
		cout << trolluser << endl;
	}
}


void Board::mortgage(string property){
	// check if any improvements still left
  	BoardTile *findTile = findTileByName(property);
  	Ownable *tmp = dynamic_cast<Ownable *>(findTile); //findOwnableByName(property);
  	if(tmp) {
		AcademicBuilding *mytemp = dynamic_cast<AcademicBuilding *>(tmp);
		if(mytemp) {
			if(mytemp->improvements > 0) {
				cout << "You must sell all improvements on the property before being able to mortgage it." << endl;
				return;
			} else {
				currentPlayer->getPaid(tmp->getPurchasePrice() / 2);
				tmp->mortgage();
			}
		} else {
  			currentPlayer->getPaid(tmp->getPurchasePrice() / 2);
  			tmp->mortgage();
		}	
  	} else {
	  	cout << trolluser << endl;
  	}
}

void Board::unmortgage(string property){
  BoardTile *findTile = findTileByName(property);
  Ownable *tmp = dynamic_cast<Ownable *>(findTile);//findOwnableByName(property); 
  if(tmp) {
  	currentPlayer->pay(tmp->getPurchasePrice() / 2);
  	currentPlayer->pay(tmp->getPurchasePrice() / 10); // 10% of purchse price or of payment (pp/2) ?? 
  tmp->unmortgage();
  } else {
	  cout << trolluser << endl;
  }
}
