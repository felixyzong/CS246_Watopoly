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
#include "player.h"
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>

class Board : public Observer<BuildingInfo>, public Observer<PlayerInfo> {
  std::vector<std::string> text;
  std::vector<Building *> buildings;
  std::map<char,int> playerPos;
  std::map<std::pair<int, int>, int> buildingLayout;
  int width = 0, height = 0;
  void compileAca(Building *b, int x, int y);
  void compileOther(Building *b, int x, int y);
  void compilePlayers();
  void clearBoard();
protected:
  void compileText();
  BuildingName getBuildingName(int pos);

public:
  void init(std::vector<Player*> players);
  Board(std::string theme_file); // initialize the board, can be extended to multiple themes by parameter
  Building *getBuilding(int pos);
  Building *findBuilding(std::string name);
  virtual void notify(Subject<BuildingInfo> &whoFrom) override;
  virtual void notify(Subject<PlayerInfo> &whoFrom) override;
  friend std::ostream &operator<<(std::ostream &out, Board* b);
  ~Board();
};


#endif
