#ifndef GYMSBUILDING_H
#define GYMSBUILDING_H
#include "building.h"
#include "player.h"
#include "info.h"
#include <iostream>
#include <vector>
#include <map>

class GymsBuilding : public Building, public Observer<BuildingInfo>{
  Player* owner;
  int totalOwns;
  std::map<BuildingName,Player*> monopoly;
  int lastRoll;
  bool mtg;

 public:
  GymsBuilding(BuildingName bn);
  ~GymsBuilding();

  Player *getOwner();
  int getCost();
  bool getMortgage();

  int getWorth();

  // call enterLastRoll before call tuition() of a gym building
  void enterLastRoll(int lastRoll);

  virtual int tuition() const;           // inherit from building
  virtual int movement() const;          // inherit from building
  virtual BuildingInfo getInfo() const override;  // inherit from subject
  virtual void notify(Subject<BuildingInfo> &whoFrom) override; // inherit from observer
  virtual void setOwner(Player *p);

  bool mortgage();
  bool unmortgage();

  void updateTotalOwns();
  void init();
};

#endif
