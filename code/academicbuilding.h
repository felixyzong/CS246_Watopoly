#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H
#include "building.h"
#include "player.h"
#include "info.h"
#include "observer.h"
#include <iostream>
#include <vector>
#include <map>
#include "Property.h"

class AcademicBuilding : public Property, public Observer<BuildingInfo>{
  Player* owner;
  MonopolyBlock mb;
  Player* monopolist;
  std::vector<BuildingInfo> monopoly;
  int improvement;
  bool mtg;
  std::vector<int> info;

 public:
  AcademicBuilding(BuildingName bn,  MonopolyBlock mb, std::vector<int> info);
  ~AcademicBuilding();

  virtual Player *getOwner() override;
  virtual int getCost() override;
  int getImprovementCost();
  virtual bool getMortgage() override;
  Player *getMonopolist() const;
  virtual int getWorth() override;
  virtual void setMortgage() override;

  int find(BuildingName bn);
  int getMonopolyImprovement();

  bool addImprovement() ;
  bool sellImprovement();
  void setImprovement(int i);
  int getImprovement() const;

  virtual int tuition() const override;           // inherit from building
  virtual int movement() const override;          // inherit from building
  virtual BuildingInfo getInfo() const override;                // inherit from subject
  virtual void notify(Subject<BuildingInfo> &whoFrom) override; // inherit from observer
  virtual void setOwner(Player *p) override;

  virtual bool mortgage() override;
  virtual bool unmortgage() override;

  void updateMonopolist();
  virtual void init() override;
};

#endif
