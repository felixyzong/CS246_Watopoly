#ifndef NONPROPERTYBUILDING_H
#define NONPROPERTYBUILDING_H

class NonPropertyBuilding : public Building {
 public:
  NonPropertyBuilding(BuildingName bn);
  int MoveTo(); // return an index that player should be moved to based on the rule of that non-property buidling
  virtual int tuition() const override;
  virtual BuildingInfo getInfo() const override;
  ~NonPropertyBuilding();
};

#endif
