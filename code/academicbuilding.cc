#include "academicbuilding.h"
using namespace std;

bool AcademicBuilding::AddImprovement() {
  if (this->improvement == 5) {
    cout << "There are already 5 improvements, you can't add more!" << endl;
    return false;
  }
  if (info[improvement + 2] > owner->getMoney()) {
    cout << "You don't have enough money!" << endl;
    return false;
  }
  improvement++;
  owner->addFund(-info[improvement + 2]);
  return true;
}

bool AcademicBuilding::sellImprovement() {
  if (this->improvement == 0) {
    cout << "There is no improvement at this building, you can't sell!" << endl;
    return false;
  }
  improvement--;
  owner->addFund(info[improvement + 2] / 2);
  return true;
}