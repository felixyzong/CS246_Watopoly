#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H
#include "building.h"
#include "player.h"
#include "info.h"
#include <iostream>
#include <vector>
#include <map>

class AcademicBuilding : public Building, public Observer<BuildingInfo>{
  Player* owner;
  MonopolyBlock mb;
  Player* monopolist;
  std::map<BuildingName,Player*> monopoly;
  int improvement;
  bool mtg;
  std::vector<int> info;

 public:
  AcademicBuilding(BuildingName bn,  MonopolyBlock mb, std::vector<int> info);
  ~AcademicBuidling();

  Player *getOwner();
  int getCost();
  int getImprovementCost();
  bool getMortgage();

  int getWorth();

  bool addImprovement();
  bool sellImprovement();
 
  virtual int tuition() const override;           // inherit from building
  virtual int movement() const override;          // inherit from building
  virtual BuildingInfo getInfo() const override;  // inherit from subject
  virtual void notify(Subject<BuildingInfo> &whoFrom) override; // inherit from observer

  void setOwner(Player *p);

  bool mortgage();
  bool unmortgage();

  void updateMonopolist();
  void init();
};

#endif
