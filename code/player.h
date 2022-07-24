#ifndef WATOPOLY_PLAYER_H
#define WATOPOLY_PLAYER_H


#include <vector>
#include "subject.h"
#include "Property.h"
#include "academicbuilding.h"
#include "residencebuilding.h"
#include "gymsbuilding.h"
#include "nonpropertybuilding.h"

class Player : Subject<PlayerInfo> {
  int money;
  std::vector<Property *> property;

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

  void addProperty(Property *b);
  void removeProperty(Property *b);
  void buyImprovement(Property *b);
  void sellImprovement(Property *b);

  void buyProperty(Property *b);
  void mortgage(Property *b);
  void unmortgage(Property *b);
  int getTimCups() const;

  void move(int num);    // To move on the board for a certain number
  void setPos(int pos); // differentiates "sent" to a place and "move" to a place
  void printAsset();

  PlayerInfo getInfo() const override;
};


#endif
