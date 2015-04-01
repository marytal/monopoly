#ifndef __UNOWNABLE_H_
#define __UNOWNABLE_H_

#include "boardtile.h"
#include <string>

class Unownable : public BoardTile {
public:
  Unownable(std::string name);
};

#endif
