#include "academicbuilding.h"
#include "player.h"
#include <vector>
#include "building.h"
using namespace std;

AcademicBuilding::AcademicBuilding(BuildingName bn, MonopolyBlock mb, std::vector<int> info):
  Building{BuildingType::Academic, bn}, owner{nullptr}, mb{mb}, improvement{0}, mtg{false}, info{info} {}

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

void AcademicBuilding::notify(Subject<BuildingInfo> &whoFrom) {
  BuildingInfo bi = whoFrom.getInfo();
  auto it = monopoly.find(bi.bn);
  if (it == monopoly.end()) {
    monopoly.insert(std::pair<BuildingName,Player*>(bi.bn,bi.owner));
    return;
  }
  it->second = bi.owner;
  if (owner != nullptr) updateMonopolist();
}


void AcademicBuilding::setOwner(Player *p) {
  owner = p;
  updateMonopolist();
  notifyObservers();
}

bool AcademicBuilding::mortgage() {
  if (mtg == true) {
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
  if (mtg == false) {
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
    if (it->second != owner) {
      monopolyStatus = false;
      monopolist = nullptr;
      break;
    }
  }
  if (monopolyStatus == true) monopolist = owner;
}

void AcademicBuilding::init() {
  owner = nullptr;
  monopolist = nullptr;
  improvement = 0;
  mtg = false;
}


Player * AcademicBuilding::getMonoplist() const {
  return monopolist;
}
