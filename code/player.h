#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "subject.h"
#include "info.h"
#include "building.h"
#include "academicbuilding.h"
#include "residencebuilding.h"
#include "gymsbuilding.h"
#include "nonpropertybuilding.h"

class Player : Subject<PlayerInfo> {
  long money;
  std::vector<Building *> property;
  // ...
  int cup; // The numebr of Roll Up the Rim Cup
  int TimLineTurn; 
  bool isInTimLine;
  int pos;
  char name;
  bool rolled;
 public:
  // ...
  Player(long money, char name);
  void addFund(int num); // To increase the money for a certain number
  int getTotalWorth();   // get the total wealth
  int rollDice();        // get a random number
  void move(int num);    // To move on the board for a certain number
  void gainCup();        // Increase the cup by 1
  int getTimTurn();      // Get the number of turn the player is stuck at time line
  int incTimTurn();      // Increase the tim line turn
  bool isInTim();
  void buyProperty(Building *b);
  int getPos();
  void setPos(int pos); // differentiates "sent" to a place and "move" to a place
  char getName();
  bool isRolled();
  void addProperty(Building *b);
  void mortgage();
  void unMortgage();
};


#endif
