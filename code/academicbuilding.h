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
  int getCost() const override;
  int getWorth() const override;
  MonopolyBlock getMonopoly();
  int tuition() const override;
  Player *getOwner();
  bool AddImprovement(); // return false if already 5 improvements
  bool sellImprovement();
  int getImprovement();
  bool getMortgage();
  int mortgage();
  int unMortgage();
  BuildingInfo getInfo() const override;
  ~AcademicBuilding();
};

#endif
