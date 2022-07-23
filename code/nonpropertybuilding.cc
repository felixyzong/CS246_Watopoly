#include "nonpropertybuilding.h"

NonPropertyBuilding::NonPropertyBuilding(BuildingName bn): Building{BuildingType::Nonproperty, bn} {}

NonPropertyBuilding::~NonPropertyBuilding() {}

int NonPropertyBuilding::tuition() const {
  switch(bn) {
    case BuildingName::CollectOSAP:
      return -200;
    case BuildingName::CoopFee:
      return 150;
    case BuildingName::NeedlesHall:
      int n = randomGen(1,18, std::chrono::system_clock::now().time_since_epoch().count());
      switch (n) {
        case 1:
          return 200;
        case 2: case 3:
          return 100;
        case 4: case 5: case 6:
          return 50;
        case 7: case 8: case 9: case 10: case 11: case 12:
          return -25;
        case 13: case 14: case 15:
          return -50;
        case 16: case 17:
          return -100;
        case 18:
          return -150;
      }
    case default:
      return 0;
  } 
}


int NonPropertyBuilding::movement() const {
  switch(bn) {
    case BuildingName::GoToTims:
      // -4 means gototims
      return -4;
    case BuildingName::SLC:
      int n = randomGen(1,24, std::chrono::system_clock::now().time_since_epoch().count());
      switch(n) {
        case 1: case 2: case 3:
          return -3;
        case 4: case 5: case 6: case 7:
          return -2;
        case 8: case 9: case 10: case 11:
          return -1;
        case 12: case 13: case 14:
          return 1;
        case 15: case 16: case 17: case 18:
          return 2;
        case 19: case 20: case 21: case 22:
          return 3;
        case 23:
          return -4;
        case 24:
          return 4;
      }
    case default:
      return 0;
  }
}

BuildingInfo NonPropertyBuilding::getInfo() const {
  BuildingInfo bi;
  bi.bn = this->bn;
  bi.improvement = -1;
  bi.owner = nullptr;
  return bi;
}

