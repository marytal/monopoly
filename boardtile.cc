#include "boardtile.h"

using namespace std;

BoardTile::BoardTile(string name, bool ownable) : name(name), ownable(ownable) {};

int BoardTile::getPurchasePrice(){
  return 10;
};
