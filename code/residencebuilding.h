#ifndef RESIDENCEBUILDING_H
#define RESIDENCEBUILDING_H
#include "building.h"
#include "player.h"
#include "observer.h"
#include "info.h"
#include <iostream>
#include <vector>
#include <map>

class ResidenceBuilding : public Building, public Observer<BuildingInfo>{
  Player* owner;
  int totalOwns;
  std::map<BuildingName,Player*> monopoly;
  bool mtg;

 public:
  ResidenceBuilding(BuildingName bn);
  ~ResidenceBuilding();

  Player *getOwner();
  int getCost();
  bool getMortgage();

  int getWorth();
 
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
