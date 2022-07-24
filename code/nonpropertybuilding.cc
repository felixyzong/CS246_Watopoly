#include "nonpropertybuilding.h"
using namespace std;

NonPropertyBuilding::NonPropertyBuilding(BuildingName bn): Building{BuildingType::Nonproperty, bn} {}

NonPropertyBuilding::~NonPropertyBuilding() {}

int NonPropertyBuilding::tuition() const {
  switch(getBuildingName()) {
    case BuildingName::CollectOSAP:
      cout << "You get $200 at Collect OSAP!" << endl;
      return -200;
    case BuildingName::CoopFee:
      return 150;
    case BuildingName::NeedlesHall: {
      cout << "You landed at NeedlesHall! ";
      int n = randomGen(1, 18);
      switch (n) {
        case 1:
          cout << "You lost $200!" << endl;
          return 200;
        case 2:
        case 3:
          cout << "You lost $100!" << endl;
          return 100;
        case 4:
        case 5:
        case 6:
          cout << "You lost $50!" << endl;
          return 50;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
          cout << "You gain $25!" << endl;
          return -25;
        case 13:
        case 14:
        case 15:
          cout << "You gain $50!" << endl;
          return -50;
        case 16:
        case 17:
          cout << "You gain $100!" << endl;
          return -100;
        case 18:
          cout << "You gain $150!" << endl;
          return -150;
        default:
          return 0;
      }
    }
      default:
        return 0;
  } 
}


int NonPropertyBuilding::movement() const {
  switch(getBuildingName()) {
    case BuildingName::GoToTims:
      cout << "You landed at Go To Tims! You will move to Tims Line!" << endl;
      return -4;
    case BuildingName::SLC: {
      cout << "You landed at SLC! ";
      int n = randomGen(1, 24);
      switch (n) {
        case 1:
        case 2:
        case 3:
          cout << "You will move back 3 steps!" << endl;
          return -3;
        case 4:
        case 5:
        case 6:
        case 7:
          cout << "You will move back 2 steps!" << endl;
          return -2;
        case 8:
        case 9:
        case 10:
        case 11:
          cout << "You will move back 1 steps!" << endl;
          return -1;
        case 12:
        case 13:
        case 14:
          cout << "You will move forward 1 steps!" << endl;
          return 1;
        case 15:
        case 16:
        case 17:
        case 18:
          cout << "You will move forward 2 steps!" << endl;
          return 2;
        case 19:
        case 20:
        case 21:
        case 22:
          cout << "You will move forward 3 steps!" << endl;
          return 3;
        case 23:
          cout << "You will move to Tims Line!" << endl;
          return -4;
        case 24:
          cout << "You will move to Collect OSAP!" << endl;
          return 4;
        default:
          return 0;
      }
    }
      default: {
        return 0;
      }
  }
}

BuildingInfo NonPropertyBuilding::getInfo() const {
  BuildingInfo bi;
  bi.bn = getBuildingName();
  bi.improvement = -1;
  bi.owner = nullptr;
  return bi;
}

