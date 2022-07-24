#ifndef BUILDING_H
#define BUILDING_H
#include "subject.h"
#include "info.h"
#include <vector>

class Building : public Subject<BuildingInfo> {
  BuildingType bt;
  BuildingName bn;

 public:
  virtual Building(BuildingType bt, BuildingName bn): bt{bt}, bn{bn} {}
  virtual ~Building() = default;

  virtual BuildingName getBuildingName() const { return bn; }
  virtual BuildingType getBuildingType() const { return bt; }
  
  virtual InfoType getInfo() const = 0; // inherit from Subject<Info>

  virtual int tuition() const = 0; // get tuition that need to be paid if player land on this building
  virtual int movement() const = 0; // get steps that player need to move if player land on this building
};

#endif
