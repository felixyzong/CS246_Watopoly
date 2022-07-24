#ifndef GYMSBUILDING_H
#define GYMSBUILDING_H
#include "building.h"
#include "player.h"
#include "info.h"
#include <iostream>
#include <vector>
#include <map>
#include "Property.h"
class GymsBuilding : public Property, public Observer<BuildingInfo>{
  Player* owner;
  int totalOwns;
  std::map<BuildingName,Player*> monopoly;
  int lastRoll;
  bool mtg;

 public:
  GymsBuilding(BuildingName bn);
  ~GymsBuilding();

  virtual Player *getOwner() override;
  virtual int getCost() override;
  virtual bool getMortgage() override;
  virtual int getWorth() override;
  virtual bool mortgage() override;
  virtual bool unmortgage() override;

  // call enterLastRoll before call tuition() of a gym building
  void enterLastRoll(int lastRoll);

  virtual int tuition() const override;           // inherit from building
  virtual int movement() const override;          // inherit from building
  virtual BuildingInfo getInfo() const override;  // inherit from subject
  virtual void notify(Subject<BuildingInfo> &whoFrom) override; // inherit from observer
  virtual void setOwner(Player *p) override;


  void updateTotalOwns();
  virtual void init() override;
};

#endif
