#ifndef WATOPOLY_PLAYER_H
#define WATOPOLY_PLAYER_H


#include <vector>
#include "building.h"
#include "academicbuilding.h"
#include "residencebuilding.h"
#include "gymsbuilding.h"
#include "nonpropertybuilding.h"

class Player {
  int money;
  std::vector<Building *> property;

  int cup = 0; // The numebr of Roll Up the Rim Cup
  int TimLineTurn = 0;
  bool isInTimLine = false;
  int pos = 0;
  char name;
  bool rolled;
 public:
  Player(int money, char name);

  char getName();
  int getMoney();
  int getPos();
  int getTimTurn();      // Get the number of turn the player is stuck at time line
  int getCup();
  bool isInTim();
  int getTotalWorth();   // get the total wealth

  void addFund(int num); // To increase the money for a certain number
  
  void gainCup();        // Increase the cup by 1
  bool incTimTurn();      // Increase the tim line turn

  void addProperty(Building *b);
  void removeProperty(Building *b);
  void buyImprovement(Building *b);
  void sellImprovement(Building *b);

  void buyProperty(Building *b);
  void mortgage(Building *b);
  void unmortgage(Building *b);
  int getTimCups() const;

  void move(int num);    // To move on the board for a certain number
  void setPos(int pos); // differentiates "sent" to a place and "move" to a place
  void printAsset();
};


#endif
