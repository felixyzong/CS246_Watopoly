#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H
#include "building.h"
#include <iostream>
#include <vector>
class Player;

class AcademicBuilding : public Building {
  MonopolyBlock mb;
  Player* owner;
  int improvement;
  bool mortgage;
  std::vector<int> info;
 public:
  AcademicBuilding(BuildingName bn, std::vector<int> info);
  bool AddImprovement(); // return false if already 5 improvements
  bool sellImprovement();
  virtual int tuition() const override;
  Player *getOwner();
  void setOwner(Player *p);
  virtual BuildingInfo getInfo() const override;
  ~AcademicBuidling();
  bool getMortgage();
  void mortgage();
  void unMortgage();
};

#endif
