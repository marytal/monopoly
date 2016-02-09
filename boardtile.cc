#include "boardtile.h"

using namespace std;

BoardTile::BoardTile(string name, bool ownable) : name(name), ownable(ownable) {};

string BoardTile::getName(void) {		// A purely abstract class
	return name;
}

int BoardTile::getPurchasePrice(){		// Not entirely sure why this is here...
  return 10;
};
