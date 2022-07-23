#include "academicbuilding.h"
using namespace std;

bool AcademicBuilding::AddImprovement() {
  if (this->improvement == 5) {
    cout << "There are already 5 improvements, you can't add more!" << endl;
    return false;
  }
  if (info[1] > owner->getMoney()) {
    cout << "You don't have enough money!" << endl;
    return false;
  }
  improvement++;
  owner->addFund(-info[1]);
  return true;
}

bool AcademicBuilding::sellImprovement() {
  if (this->improvement == 0) {
    cout << "There is no improvement at this building, you can't sell!" << endl;
    return false;
  }
  improvement--;
  owner->addFund(info[1] / 2);
  return true;
}

int AcademicBuilding::tuition() const {
  return info[improvement + 2];
}

Player * AcademicBuilding::getOwner() {
  return owner;
}

bool AcademicBuilding::getMortgage() {
  return mortgage;
}

void AcademicBuilding::mortgage() {
  mortgage = true;
}

void AcademicBuilding::unMortgage() {
  mortgage = false;
}

void AcademicBuilding::setOwner(Player *p) {
  owner = p;
}