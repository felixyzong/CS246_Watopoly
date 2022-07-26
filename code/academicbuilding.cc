#include "academicbuilding.h"
#include "player.h"
#include <vector>
#include "building.h"
using namespace std;

AcademicBuilding::AcademicBuilding(BuildingName bn, MonopolyBlock mb, std::vector<int> info):
  Property{BuildingType::Academic, bn}, owner{nullptr}, mb{mb}, improvement{0}, mtg{false}, info{info} {}

AcademicBuilding::~AcademicBuilding() {}

Player *AcademicBuilding::getOwner() { return owner; }

int AcademicBuilding::getCost() { return info[0]; }

int AcademicBuilding::getImprovementCost() { return info[1]; }

bool AcademicBuilding::getMortgage() { return mtg; }

int AcademicBuilding::getWorth() {
  return info[0] + improvement * info[1];
}


bool AcademicBuilding::addImprovement() {
  if (monopolist != owner) {
    cout << "You don't own all buildings from this monopoly block!" << endl;
    return false;
  }
  if (improvement == 5) {
    cout << "There are already 5 improvements, you can't add more!" << endl;
    return false;
  }
  if (info[1] > owner->getMoney()) {
    cout << "You don't have enough money!" << endl;
    return false;
  }
  cout << "You successfully build an improvement at " << bntostr(getBuildingName()) << endl;
  improvement++;
  owner->addFund(-info[1]);
  notifyObservers();
  return true;
}

bool AcademicBuilding::sellImprovement() {
  if (monopolist != owner) {
    cout << "You don't own all buildings from this monopoly block!" << endl;
    return false;
  }
  if (this->improvement == 0) {
    cout << "There is no improvement at this building, you can't sell!" << endl;
    return false;
  }
  improvement--;
  owner->addFund(info[1] / 2);
  notifyObservers();
  return true;
}

int AcademicBuilding::tuition() const {
  if (monopolist == owner && owner != nullptr) return info[improvement+2] * 2;
  else return info[improvement+2];
}

int AcademicBuilding::movement() const {
  return 0;
}

BuildingInfo AcademicBuilding::getInfo() const {
  BuildingInfo bi;
  bi.bn = getBuildingName();
  bi.improvement = this->improvement;
  bi.owner = this->owner;
  return bi;
}

int AcademicBuilding::find(BuildingName bn) {
  for (int i = 0; i < monopoly.size(); i++) {
    if (monopoly[i].bn == bn) return i;
  }
  return -1;
}

int AcademicBuilding::getMonopolyImprovement() {
  if (monopolist) {
    int imp = improvement;
    for (BuildingInfo bi : monopoly) {
      imp += bi.improvement;
    }
    return imp;
  }
  return 0;
}

void AcademicBuilding::notify(Subject<BuildingInfo> &whoFrom) {
  BuildingInfo bi = whoFrom.getInfo();
  int index = find(bi.bn);
  if (index == -1) {
    monopoly.emplace_back(bi);
    return;
  }
  monopoly[index].improvement = bi.improvement;
  monopoly[index].owner = bi.owner;
  if (owner != nullptr) updateMonopolist();
}


void AcademicBuilding::setOwner(Player *p) {
  owner = p;
  updateMonopolist();
  notifyObservers();
}

bool AcademicBuilding::mortgage() {
  if (mtg) {
    cout << "This building is already mortgaged!" << endl;
    return false;
  }
  if (improvement != 0) {
    cout << "You need sell all improvement first!" << endl;
    return false;
  }
  mtg = true;
  owner->addFund(getCost()/2);
  return true;
}

bool AcademicBuilding::unmortgage() {
  if (!mtg) {
    cout << "This building is not mortgaged!" << endl;
    return false;
  }
  if (getCost()*10/6 > owner->getMoney()) {
    cout << "You don't have enough money!" << endl;
    return false;
  }
  mtg = false;
  owner->addFund(-getCost()*10/6);
  return true;
}

void AcademicBuilding::updateMonopolist() {
  bool monopolyStatus = true;
  for (auto it = monopoly.begin(); it!= monopoly.end(); ++it) {
    if (it->owner != owner) {
      monopolyStatus = false;
      monopolist = nullptr;
      break;
    }
  }
  if (monopolyStatus) monopolist = owner;
}

void AcademicBuilding::init() {
  owner = nullptr;
  monopolist = nullptr;
  improvement = 0;
  mtg = false;
  notifyObservers();
}


Player * AcademicBuilding::getMonopolist() const {
  return monopolist;
}

int AcademicBuilding::getImprovement() const{
  return improvement;
}
