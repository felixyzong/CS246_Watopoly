#ifndef WATOPOLY_PLAYER_H
#define WATOPOLY_PLAYER_H


#include <vector>
#include "building.h"
#include "academicbuilding.h"
#include "residencebuilding.h"
#include "gymsbuilding.h"
#include "nonpropertybuilding.h"

class Player {
  long money;
  std::vector<Building *> property;
  // ...
  int cup; // The numebr of Roll Up the Rim Cup
  int TimLineTurn = 0;
  bool isInTimLine = false;
  int pos = 0;
  char name;
  bool rolled = false;
 public:
  Player(long money, char name);
  void addFund(int num); // To increase the money for a certain number
  int getTotalWorth();   // get the total wealth
  int rollDice(unsigned seed);        // get a random number
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
  void buyImprovement(Building *b);
  void mortgage(Building *b);
  void unMortgage(Building *b);
};


#endif
