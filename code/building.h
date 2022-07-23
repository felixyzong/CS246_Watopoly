#ifndef BUILDING_H
#define BUILDING_H
#include "subject.h"
#include "info.h"
#include <vector>

class Building : public Subject<BuildingInfo> {
  BuildingType bt;
  BuildingName bn;
  
 public:
  Building(BuildingType bt, BuildingName bn);
  BuildingName GetBuildingName() const { return bn; }
  virtual int getCost() const = 0;
  virtual int getWorth() const = 0;
  virtual int tuition() const = 0;
  BuildingType getBuildingType() const { return bt; }
  virtual BuildingInfo getInfo() const = 0;
  virtual ~Building() = default;
};

#endif
