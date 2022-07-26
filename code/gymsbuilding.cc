#include "gymsbuilding.h"
using namespace std;

GymsBuilding::GymsBuilding(BuildingName bn):
  Property{BuildingType::Gyms, bn}, owner{nullptr}, totalOwns{0}, mtg{false} {}

GymsBuilding::~GymsBuilding() {}

Player *GymsBuilding::getOwner() { return owner; }

int GymsBuilding::getCost() { return 150; }

bool GymsBuilding::getMortgage() { return mtg; }

int GymsBuilding::getWorth() {
  return 150;
}

void GymsBuilding::enterLastRoll(int lastRoll) {
  this->lastRoll = lastRoll;
}

int GymsBuilding::tuition() const {
  if (totalOwns == 1) return 4*lastRoll;
  else if (totalOwns == 2) return 10*lastRoll;
  else return 0;
}

int GymsBuilding::movement() const {
  return 0;
}

BuildingInfo GymsBuilding::getInfo() const {
  BuildingInfo bi;
  bi.bn = getBuildingName();
  bi.improvement = -1;
  bi.owner = this->owner;
  return bi;
}

void GymsBuilding::notify(Subject<BuildingInfo> &whoFrom) {
  BuildingInfo bi = whoFrom.getInfo();
  auto it = monopoly.find(bi.bn);
  if (it == monopoly.end()) {
    monopoly.insert(std::pair<BuildingName,Player*>(bi.bn,bi.owner));
    return;
  }
  it->second = bi.owner;
  if (owner != nullptr) updateTotalOwns();
}


void GymsBuilding::setOwner(Player *p) {
  owner = p;
  updateTotalOwns();
  notifyObservers();
}

bool GymsBuilding::mortgage() {
  if (mtg) {
    cout << "This building is already mortgaged!" << endl;
    return false;
  }
  mtg = true;
  owner->addFund(getCost()/2);
  return true;
}

bool GymsBuilding::unmortgage() {
  if (!mtg) {
    cout << "This building is not mortgaged!" << endl;
    return false;
  }
  mtg = false;
  owner->addFund(-getCost()*10/6);
  return true;
}


void GymsBuilding::updateTotalOwns() {
  totalOwns = 1;
  for (auto it = monopoly.begin(); it!= monopoly.end(); ++it) {
    if (it->second == owner) totalOwns++;
  }
}

void GymsBuilding::init() {
  owner = nullptr;
  totalOwns = 0;
  mtg = false;
  notifyObservers();
}

