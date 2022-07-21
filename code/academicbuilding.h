#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H
#include "building.h"

class Player;

class AcademicBuilding : public Building {
  MonopolyBlock mb;
  Player* owner;
  int improvement;
  bool mortgage;
 public:
  AcademicBuilding(BuildingName bn);
  bool AddImprovement(); // return false if already 5 improvements
  virtual int tuition() const override;
  Player *getOwner();
  virtual BuildingInfo getInfo() const override;
  ~AcademicBuidling(); 
  bool getMortgage();
  int mortgage();
  int unmortgage();
};

#endif
