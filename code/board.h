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
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <string>

class Board : public Observer<BuildingInfo>, public Observer<PlayerInfo> {
  std::vector<std::string> text;
  std::vector<Building *> buildings;
  std::map<char,int> playerPos;
 protected:
 
  BuildingName getBuildingName(int pos);
  int getBuildingPos(BuildingName bn);
  std::pair<int,int> getBoardEntry(int pos);
  void clearPlayer(char name); // remove this player from display text
 public:
  void init(std::vector<Player*> players);
  Board(); // initialize the board, can be extended to multiple themes by parameter
  Building *getBuilding(int pos);
  Building *findBuilding(std::string name);
  virtual void notify(Subject<BuildingInfo> &whoFrom) override;
  virtual void notify(Subject<PlayerInfo> &whoFrom) override;
  friend std::ostream &operator<<(std::ostream &out, Board* b);
  ~Board();
};


#endif
