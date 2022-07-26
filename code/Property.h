//
// Created by a1234 on 2022/7/24.
//

#ifndef ACADEMICBUILDING_H_PROPERTY_H
#define ACADEMICBUILDING_H_PROPERTY_H
#include "building.h"


class Player;
class Property: public Building{
  Player *owner;
public:
  Property(BuildingType ty, BuildingName bn): Building{ty, bn} {};
  virtual Player *getOwner() = 0;
  virtual void setOwner(Player *p) = 0;
  virtual int getCost() = 0;
  virtual bool getMortgage() = 0;
  virtual int getWorth() = 0;
  virtual bool mortgage() = 0;
  virtual bool unmortgage() = 0;
  virtual void setMortgage() = 0;
  virtual BuildingInfo getInfo() const = 0; // inherit from Subject<Info>
  virtual void init() = 0;
  virtual ~Property() = 0;
};


#endif //ACADEMICBUILDING_H_PROPERTY_H
