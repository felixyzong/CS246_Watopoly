#ifndef BUILDING_H
#define BUILDING_H
#include "subject.h"
#include "info.h"
#include <vector>

class Building : public Subject<BuildingInfo> {
  BuildingType bt;
  BuildingName bn;
<<<<<<< HEAD

 public:
  virtual Building(BuildingType bt, BuildingName bn): bt{bt}, bn{bn} {}
  virtual ~Building() = default;

  virtual BuildingName getBuildingName() const { return bn; }
  virtual BuildingType getBuildingType() const { return bt; }

  virtual InfoType getInfo() const = 0; //inherit from Subject<Info>

  virtual int tuition() const = 0;
  virtual int movement() const = 0;
=======
  
 public:
  Building(BuildingType bt, BuildingName bn);
  BuildingName GetBuildingName() const { return bn; }
  virtual int getCost() const = 0;
  virtual int getWorth() const = 0;
  virtual int tuition() const = 0;
  BuildingType getBuildingType() const { return bt; }
  virtual BuildingInfo getInfo() const = 0;
  virtual ~Building() = default;
>>>>>>> 444017ad208972637c1afd14f9a1fcdbed30595c
};

#endif
