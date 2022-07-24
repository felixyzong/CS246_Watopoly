#ifndef RESIDENCEBUILDING_H
#define RESIDENCEBUILDING_H
#include "building.h"
#include "player.h"
#include "observer.h"
#include "info.h"
#include <iostream>
#include <vector>
#include <map>
#include "Property.h"

class ResidenceBuilding : public Property, public Observer<BuildingInfo>{
  Player* owner;
  int totalOwns;
  std::map<BuildingName,Player*> monopoly;
  bool mtg;

 public:
  ResidenceBuilding(BuildingName bn);
  ~ResidenceBuilding();

  virtual Player *getOwner() override;
  virtual int getCost() override;
  virtual bool getMortgage() override;
  virtual int getWorth() override;
  virtual bool mortgage() override;
  virtual bool unmortgage() override;
 
  virtual int tuition(unsigned seed) const override;           // inherit from building
  virtual int movement(unsigned seed) const override;          // inherit from building
  virtual BuildingInfo getInfo() const override;  // inherit from subject
  virtual void notify(Subject<BuildingInfo> &whoFrom) override; // inherit from observer
  virtual void setOwner(Player *p) override;


  void updateTotalOwns();
  void init();
};

#endif
