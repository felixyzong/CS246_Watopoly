#ifndef RESIDENCEBUILDING_H
#define RESIDENCEBUILDING_H
#include "building.h"

class Player;

class ResidenceBuilding : public Building {
  Player* owner;
  bool mortgage;
 public:
  ResidenceBuilding(BuildingName bn);
  virtual int tuition() const override;
  Player *getOwner();
  virtual BuildingInfo getInfo() const override;
  ~ResidenceBuidling();
  bool getMortgage();
  int mortgage();
  int unmortgage();
};


#endif