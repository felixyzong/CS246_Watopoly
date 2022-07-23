#ifndef BUILDING_H
#define BUILDING_H
#include "subject.h"
#include "info.h"
#include <vector>

class Building : public Subject<BuildingInfo> {
  BuildingType bt;
  BuildingName bn;
 public:
  virtual Building(BuildingType bt, BuildingName bn);
  virtual BuildingName GetBuildingName() const { return bn; }
  virtual int getCost() const = 0;
  virtual int getWorth() const = 0;
  virtual int tuition() const = 0;
  virtual bool getMortgage() const = 0;
  virtual bool getImprovement() const = 0;
  virtual int mortgage() const = 0;
  virtual int unMortgage() const = 0;
  virtual BuildingType getBuildingType() const { return bt; }
  virtual ~Building() = default;
  virtual InfoType getInfo() const = 0;
};

#endif
