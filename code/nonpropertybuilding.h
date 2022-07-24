#ifndef NONPROPERTYBUILDING_H
#define NONPROPERTYBUILDING_H
#include "building.h"

class NonPropertyBuilding : public Building {
 public:
  NonPropertyBuilding(BuildingName bn);
  virtual int tuition() const override;           // inherit from building
  virtual int movement() const override;          // inherit from building
  virtual BuildingInfo getInfo() const override;  // inherit from subject
  ~NonPropertyBuilding();
};

#endif
