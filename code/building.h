#ifndef BUILDING_H
#define BUILDING_H
#include "subject.h"
#include "info.h"
#include <vector>
class Player;
class Building : public Subject<BuildingInfo> {
  BuildingType bt;
  BuildingName bn;

 public:
  Building(BuildingType bt, BuildingName bn): bt{bt}, bn{bn} {}
  virtual ~Building() = 0;

  virtual BuildingName getBuildingName() const { return bn; }
  virtual BuildingType getBuildingType() const { return bt; }

  virtual BuildingInfo getInfo() const = 0; // inherit from Subject<Info>

  virtual int tuition(unsigned seed) const = 0; // get tuition that need to be paid if player land on this building
  virtual int movement(unsigned seed) const = 0; // get steps that player need to move if player land on this building
};

inline Building::~Building() {}
#endif
