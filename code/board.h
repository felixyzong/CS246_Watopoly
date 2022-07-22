#ifndef BOARD_H
#define BOARD_H
#include "info.h"
#include "building.h"
#include "residencebuilding.h"
#include "academicbuilding.h"
#include "gymsbuilding.h"
#include "nonpropertybuilding.h"
#include "player.h"
#include "observer.h"
#include "subject.h"
#include <vector>
#include <iostream>

class Board : public Observer<BuildingInfo>, public Observer<PlayerInfo> {
  std::vector<std::vector<char>> text;
 public:
  Board(std::vector<Building*> buildings, std::vector<Player*> players);
  virtual void notify(Subject<BuildingInfo> &whoFrom) override;
  virtual void notify(Subject<PlayerInfo> &whoFrom) override;
  friend std::ostream &operator<<(std::ostream &out, Board* b);
  ~Board();
};


#endif
