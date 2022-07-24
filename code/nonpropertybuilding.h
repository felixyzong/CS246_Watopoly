#ifndef NONPROPERTYBUILDING_H
#define NONPROPERTYBUILDING_H
#include "building.h"
#include "watutils.h"
class NonPropertyBuilding : public Building {
 public:
  NonPropertyBuilding(BuildingName bn);
  virtual int tuition(unsigned seed) const override;           // inherit from building
  virtual int movement(unsigned seed) const override;          // inherit from building
  virtual BuildingInfo getInfo() const override;  // inherit from subject
  ~NonPropertyBuilding();
};

#endif
