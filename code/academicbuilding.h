#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H
#include "building.h"
#include <iostream>
#include <vector>
class Player;

class AcademicBuilding : public Building {
  MonopolyBlock mb;
  Player* owner = nullptr;

  Player* monopolist = nullptr;
  std::map<BuildingName, Player*> monopoly;

  int improvement = 0;
  bool mortgage = 0;
  std::vector<int> info;
 public:

  AcademicBuilding(BuildingName bn, MonopolyBlock mb, std::vector<int> info);
  ~AcademicBuilding();

  Player *getOwner();
  void setOwner(Player *p);
  MonopolyBlock getMonopoly();

  int getCost();
  int getImprovementCost();
  int getWorth();

  int tuition() const override;
  int movement() const override;

  bool addImprovement(); // return false if already 5 improvements
  bool sellImprovement();
  int getImprovement();

  bool getMortgage();
  void mortgage();
  void unMortgage();

  BuildingInfo getInfo() const override;
  void notify(Subject<BuildingInfo> &whoFrom) override; //inherite from observer

  void updateMonopolist();
  void init();
};

#endif
