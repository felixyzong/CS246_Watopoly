#ifndef BOARD_H
#define BOARD_H
#include "building.h"
#include "residencebuilding.h"
#include "academicbuilding.h"
#include "gymsbuilding.h"
#include "nonpropertybuilding.h"
#include <vector>

class Board {
  std::vector<Building *> buildings;
 public:
  Building * getBuilding(int pos);
  void init();
  int searchBuilding(Building *);
};


#endif
