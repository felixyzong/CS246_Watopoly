#ifndef BUILDING_H
#define BUILDING_H
#include "subject.h"
#include "info.h"
#include <vector>

class Building : public Subject<BuildingInfo> {
  BuildingType bt;
  BuildingName bn;
 public:
  virtual Building(BuildingType bt, BuidlingName bn);
  virtual BuildingName GetBuildingName() const { return bn; }
  virtual int tuition() const = 0;
  virtual BuildingType getBuidlingType() const { return bt; }
  virtual ~building() = default;
  virtual InfoType getInfo() const = 0;
};

#endif
