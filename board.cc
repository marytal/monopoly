#include "board.h"
#include "unownable.h"
#include "ownable.h"
#include "academicbuilding.h"
#include "gym.h"
#include "residence.h"
#include "player.h"

const string trolluser = "Stop trying to break the game. -_-";

// At the start of every turn just put the next player in the current player instead of calling the players array all the time

void Board::getCurrentRoll(int roll1, int roll2) {
  roll1 = roll1;
  roll2 = roll2;
  int newPos = currentPlayer->getPos() + roll1 + roll2;
  currentPlayer->setPos(newPos);
  td->notify(newPos, currentPlayer->getSymbol());
  cout << *td << endl;

  getTileAction();
}

void Board::getTileAction(){
  BoardTile *currentTile = tiles[currentPlayer->getPos()];
  cout << endl << "You've landed on " << currentTile->name << "!" << endl;
  if(currentTile->ownable){
    Ownable *ownable = dynamic_cast<Ownable *>(currentTile);
    if(ownable->owner == currentPlayer){
      cout << "You already own this property." << endl;
    } else if(ownable->owner != NULL){
      Player *tileOwner = ownable->owner;
      int rent = ownable->rent();
      if(currentPlayer->canPay(rent)){
        cout << "Please pay $" << rent  << " to " << tileOwner->getName() << "." << endl;
        currentPlayer->pay(rent);
        tileOwner->getPaid(rent);
        
      } else {
        // do you want to mortgage something? / bankrupt!
      }
    } else if(ownable->owner == NULL){
      int price = ownable->getPurchasePrice();
      cout << "Would you like to buy this property? It costs $" << price << endl;
      cout << "(y/n)" << endl;
      char response;
      cin >> response;
      if(response == 'n'){
        // start auction.
      } else {
        //check if can pay?
        currentPlayer->pay(price);
        ownable->owner = currentPlayer;
        cout << "Congratulations! You are the brand new owner of " << ownable->name << endl;

        Gym *gym = dynamic_cast<Gym *>(ownable);
        AcademicBuilding *ab = dynamic_cast<AcademicBuilding *>(ownable);
        if(gym){
        } else if(ab->isMonopoly()){
          cout << "Even better, you now own a monopoly. Feel free to start making improvements!" << endl;
        }
      }
    }
  }
}

void Board::changeTurn(void) {
	currentPlayerIndex++;
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
  if(currentPlayer == NULL){
    currentPlayer = newPlayer;
  }
}

Board::Board(void) {
  tiles[0] = new Unownable("COLLECT OSAP");
  tiles[1] = new AcademicBuilding("AL", 40, 50, "Arts1", 2, 10, 30, 90, 160, 250);
  tiles[2] = new Unownable("SLC");
  tiles[3] = new AcademicBuilding("ML", 60, 50, "Arts1", 4, 20, 60, 180, 320, 450);
  tiles[4] = new Unownable("TUITION");
  tiles[5] = new Residence("MKV");
  tiles[6] = new AcademicBuilding("ECH", 100, 50, "Arts2", 6, 30, 90, 270, 400, 550);
  tiles[7] = new Unownable("NEEDLES HALL");
  tiles[8] = new AcademicBuilding("PAS", 100, 50, "Arts2", 6, 30, 90, 270, 400, 550);
  tiles[9] = new AcademicBuilding("HH", 120, 50, "Arts2", 8, 40, 100, 300, 450, 600);
  tiles[10] = new Unownable("DC Tims Line");
  tiles[11] = new AcademicBuilding("RCH", 140, 100, "Eng", 10, 50, 150, 450, 625, 750);
  tiles[12] = new Gym("PAC");
  tiles[13] = new AcademicBuilding("DWE", 140, 100, "Eng", 10, 50, 150, 450, 625, 750);
  tiles[14] = new AcademicBuilding("CPH", 160, 100, "Eng", 12, 60, 180, 500, 700, 900);
  tiles[15] = new Residence("UWP");
  tiles[16] = new AcademicBuilding("LHI", 180, 100, "Health", 14, 70, 200, 550, 750, 950);
  tiles[17] = new Unownable("SLC");
  tiles[18] = new AcademicBuilding("BMH", 180, 100, "Health", 14, 70, 200, 550, 750, 950);
  tiles[19] = new AcademicBuilding("OPT", 200, 100, "Health", 16, 80, 220, 600, 800, 1000);
  tiles[20] = new Unownable("Goose Nesting");
  tiles[21] = new AcademicBuilding("EV1", 220, 150, "Env", 18, 90, 250, 700, 875, 1015);
  tiles[22] = new Unownable("NEEDLES HALL");
  tiles[23] = new AcademicBuilding("EV2", 220, 150, "Env", 18, 90, 250, 700, 875, 1015);
  tiles[24] = new AcademicBuilding("EV3", 240, 150, "Env", 20, 100, 300, 750, 925, 1100);
  tiles[25] = new Residence("V1");
  tiles[26] = new AcademicBuilding("PHYS", 260, 150, "Sci1", 22, 110, 330, 800, 975, 1150);
  tiles[27] = new AcademicBuilding("B1", 260, 150, "Sci1", 22, 110, 330, 800, 975, 1150);
  tiles[28] = new Gym("CIF");
  tiles[29] = new AcademicBuilding("B2", 280, 150, "Sci1", 24, 120, 360, 850, 1025, 1200);
  tiles[30] = new Unownable("GO TO TIMES");
  tiles[31] = new AcademicBuilding("EIT", 300, 200, "Sci2", 26, 130, 390, 900, 1100, 1275);
  tiles[32] = new AcademicBuilding("ESC", 300, 200, "Sci2", 26, 130, 390, 900, 1100, 1275);
  tiles[33] = new Unownable("SLC");
  tiles[34] = new AcademicBuilding("C2", 320, 200, "Sci2", 28, 150, 450, 1000, 1200, 1400);
  tiles[35] = new Residence("REV");
  tiles[36] = new Unownable("NEEDLES HALL");
  tiles[37] = new AcademicBuilding("MC", 350, 200, "Math", 35, 175, 500, 1100, 1300, 1500);
  tiles[38] = new Unownable("COOP FEE");
  tiles[39] = new AcademicBuilding("DC", 400, 200, "Math", 50, 200, 600, 1400, 1700, 2000);
  td = new TextDisplay();
  currentPlayerIndex = 0;
  currentPlayer = NULL;
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
