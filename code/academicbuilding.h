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
  std::map<BuildingName,Player*> monopoly;
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

  bool addImprovement() ;
  bool sellImprovement();
  int getImprovement() const;

  virtual int tuition(unsigned seed) const override;           // inherit from building
  virtual int movement(unsigned seed) const override;          // inherit from building
  virtual BuildingInfo getInfo() const override;  // inherit from subject
  virtual void notify(Subject<BuildingInfo> &whoFrom) override; // inherit from observer
  virtual void setOwner(Player *p) override;

  virtual bool mortgage() override;
  virtual bool unmortgage() override;

  void updateMonopolist();
  void init();
};

#endif
