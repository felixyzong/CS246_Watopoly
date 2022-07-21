#ifndef RESIDENCEBUILDING_H
#define RESIDENCEBUILDING_H
#include "building.h"

class Player;

class GymsBuilding : public Building {
  Player* owner;
  bool mortgage;
 public:
  GymsBuilding(BuildingName bn);
  virtual int tuition() const override;
  Player* getOwner();
  virtual BuildingInfo getInfo() const override;
  ~GymsBuilding();
  bool getMortgage();
  int mortgage();
  int unmortgage();
};


#endif