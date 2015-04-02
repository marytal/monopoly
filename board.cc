#include "board.h"
#include "unownable.h"
#include "ownable.h"
#include "academicbuilding.h"
#include "gym.h"
#include "residence.h"
#include "player.h"

#include <sstream>

const string trolluser = "Stop trying to break the game. -_-";


void Board::getCurrentRoll(int roll1, int roll2) {
  roll1 = roll1;
  roll2 = roll2;
  int newPos = currentPlayer->getPos() + roll1 + roll2;
  if(newPos > 39){ // greater or equals?
    newPos = newPos % 40;
  }
  currentPlayer->setPos(newPos);
  td->notify(newPos, currentPlayer->getSymbol());
  cout << *td << endl;

  getTileAction();
}

void Board::auction(BoardTile *tile){
  // what if no one bids??? Undefined behaviour? No one gets the property?

  int _currentPlayerIndex = currentPlayerIndex + 1;
   // how to copy the array of players to the heap...
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

void Board::getTileAction(){
  BoardTile *currentTile = tiles[currentPlayer->getPos()];
  cout << endl << "You've landed on " << currentTile->name << "!" << endl;
  if(currentTile->ownable) {
    Ownable *ownable = dynamic_cast<Ownable *>(currentTile);
    if(ownable->owner == currentPlayer){
      cout << "You already own this property." << endl;
    } else if(ownable->owner != NULL){
      Player *tileOwner = ownable->owner;
      int rent = ownable->rent();
      if(currentPlayer->canPay(rent)){
        cout << "You've paid $" << rent  << " to " << tileOwner->getName() << " for landing on his/her property." << endl;  
        currentPlayer->pay(rent);
        tileOwner->getPaid(rent);
        cout << "You now have $" << currentPlayer->getBalance() << " in your account." << endl;
        
      } else {
        // do you want to mortgage something? / bankrupt!
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
        auction(currentTile);

      } else {
        //check if can pay?
        currentPlayer->pay(price);
        ownable->owner = currentPlayer;
        cout << "Congratulations! You are the brand new owner of " << currentTile->name << "!" << endl; // name not working

        Gym *gym = dynamic_cast<Gym *>(ownable);
        AcademicBuilding *ab = dynamic_cast<AcademicBuilding *>(ownable);
        if(ab && ab->isMonopoly()){
          cout << "Even better, you now own a monopoly. Feel free to start making improvements!" << endl;
        }
      }
    }
  } else {
    cout << "We don't know what happens yet." << endl;
  }
}

void Board::changeTurn(void) {
  if(currentPlayerIndex == numPlayers - 1){
    currentPlayerIndex = 0;
  } else {
    currentPlayerIndex++;
  }
	
  currentPlayer = players[currentPlayerIndex];

}

bool Board::isOwnable(BoardTile *tile){
  return tile->ownable;
}

int Board::getTilePrice(Ownable *tile){
  return tile->getPurchasePrice();
}

void Board::addPlayer(Player * newPlayer) {
	players[numPlayers] = newPlayer;
  numPlayers++;
  if(currentPlayer == NULL){
    currentPlayer = newPlayer;
  }
}

void makeFaculty(BoardTile *first, BoardTile *second, BoardTile *third){
  AcademicBuilding *_first = dynamic_cast<AcademicBuilding *>(first);
  AcademicBuilding *_second = dynamic_cast<AcademicBuilding *>(second);
  AcademicBuilding *_third = dynamic_cast<AcademicBuilding *>(third);


  _first->addFaculty(_second, _third);
  _second->addFaculty(_first, _third);
  if(_third){
    _third->addFaculty(_first, _second);
  }

}


Board::Board(void) {
  tiles[0] = new Unownable("COLLECT OSAP");
  tiles[1] = new AcademicBuilding("AL", 40, 50, "Arts1", 2, 10, 30, 90, 160, 250);
  tiles[2] = new Unownable("SLC");
  tiles[3] = new AcademicBuilding("ML", 60, 50, "Arts1", 4, 20, 60, 180, 320, 450);
  makeFaculty(tiles[1], tiles[3], NULL);
  tiles[4] = new Unownable("TUITION");
  tiles[5] = new Residence("MKV");
  tiles[6] = new AcademicBuilding("ECH", 100, 50, "Arts2", 6, 30, 90, 270, 400, 550);
  tiles[7] = new Unownable("NEEDLES HALL");
  tiles[8] = new AcademicBuilding("PAS", 100, 50, "Arts2", 6, 30, 90, 270, 400, 550);
  tiles[9] = new AcademicBuilding("HH", 120, 50, "Arts2", 8, 40, 100, 300, 450, 600);
  makeFaculty(tiles[6], tiles[8], tiles[9]);
  tiles[10] = new Unownable("DC Tims Line");
  tiles[11] = new AcademicBuilding("RCH", 140, 100, "Eng", 10, 50, 150, 450, 625, 750);
  tiles[12] = new Gym("PAC");
  tiles[13] = new AcademicBuilding("DWE", 140, 100, "Eng", 10, 50, 150, 450, 625, 750);
  tiles[14] = new AcademicBuilding("CPH", 160, 100, "Eng", 12, 60, 180, 500, 700, 900);
  makeFaculty(tiles[11], tiles[13], tiles[14]);
  tiles[15] = new Residence("UWP");
  tiles[16] = new AcademicBuilding("LHI", 180, 100, "Health", 14, 70, 200, 550, 750, 950);
  tiles[17] = new Unownable("SLC");
  tiles[18] = new AcademicBuilding("BMH", 180, 100, "Health", 14, 70, 200, 550, 750, 950);
  tiles[19] = new AcademicBuilding("OPT", 200, 100, "Health", 16, 80, 220, 600, 800, 1000);
  makeFaculty(tiles[16], tiles[18], tiles[19]);
  tiles[20] = new Unownable("Goose Nesting");
  tiles[21] = new AcademicBuilding("EV1", 220, 150, "Env", 18, 90, 250, 700, 875, 1015);
  tiles[22] = new Unownable("NEEDLES HALL");
  tiles[23] = new AcademicBuilding("EV2", 220, 150, "Env", 18, 90, 250, 700, 875, 1015);
  tiles[24] = new AcademicBuilding("EV3", 240, 150, "Env", 20, 100, 300, 750, 925, 1100);
  makeFaculty(tiles[21], tiles[23], tiles[24]);
  tiles[25] = new Residence("V1");
  tiles[26] = new AcademicBuilding("PHYS", 260, 150, "Sci1", 22, 110, 330, 800, 975, 1150);
  tiles[27] = new AcademicBuilding("B1", 260, 150, "Sci1", 22, 110, 330, 800, 975, 1150);
  tiles[28] = new Gym("CIF");
  tiles[29] = new AcademicBuilding("B2", 280, 150, "Sci1", 24, 120, 360, 850, 1025, 1200);
  makeFaculty(tiles[26], tiles[27], tiles[29]);
  tiles[30] = new Unownable("GO TO TIMES");
  tiles[31] = new AcademicBuilding("EIT", 300, 200, "Sci2", 26, 130, 390, 900, 1100, 1275);
  tiles[32] = new AcademicBuilding("ESC", 300, 200, "Sci2", 26, 130, 390, 900, 1100, 1275);
  tiles[33] = new Unownable("SLC");
  tiles[34] = new AcademicBuilding("C2", 320, 200, "Sci2", 28, 150, 450, 1000, 1200, 1400);
  makeFaculty(tiles[31], tiles[32], tiles[34]);
  tiles[35] = new Residence("REV");
  tiles[36] = new Unownable("NEEDLES HALL");
  tiles[37] = new AcademicBuilding("MC", 350, 200, "Math", 35, 175, 500, 1100, 1300, 1500);
  tiles[38] = new Unownable("COOP FEE");
  tiles[39] = new AcademicBuilding("DC", 400, 200, "Math", 50, 200, 600, 1400, 1700, 2000);
  makeFaculty(tiles[37], tiles[39], NULL);
  td = new TextDisplay();
  currentPlayerIndex = 0;
  currentPlayer = NULL;
  numPlayers = 0; 
}

// initialize facultyMembers for all deez bitchez

BoardTile *Board::findTileByName(string property){
  for(int i = 0; i < 40; i++){ // 28 magic number
    if(tiles[i]->name == property){
      return tiles[i];
    }
  }
}

//Ownable *Board::findOwnableByName(string property) {}
//AcademicBuilding *Board::findAcademicByName(string property) {}

Player *Board::findPlayerByName(string name){
  for(int i = 0; i < numPlayers; i++){
    if(players[i]->getName() == name){
      return players[i];
    }
  }
}

void Board::trade(string name, int amount, string property){
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
  	currentPlayer->pay(tmp->getImprovementPrice());
	tmp->unimprove();
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
		currentPlayer->pay(tmp->getImprovementPrice() / 2);
		tmp->improve();
//  tmp->improvements += 1;
//  tmp->totalPrice += tmp->improvementPrice;
	} else {
		cout << trolluser << endl;
	}
}


void Board::mortagage(string property){
  // check if any improvements still left
  BoardTile *findTile = findTileByName(property);
  Ownable *tmp = dynamic_cast<Ownable *>(findTile); //findOwnableByName(property);
  if(tmp) {
  	currentPlayer->getPaid(tmp->getPurchasePrice() / 2);
  	tmp->mortgage(); // if tile is owned, check if mortgaged before paying (don't have to for mortgaged places)
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
