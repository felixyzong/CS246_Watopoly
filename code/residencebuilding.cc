#include "residencebuilding.h"
using namespace std;

ResidenceBuilding::ResidenceBuilding(BuildingName bn):
  Building{BuildingType::Residence, bn}, owner{nullptr}, totalOwns{0}, mtg{false} {}

ResidenceBuilding::~ResidenceBuidling() {}

Player *ResidenceBuilding::getOwner() { return owner; }

int ResidenceBuilding::getCost() { return 200; }

bool ResidenceBuilding::getMortgage() { return mtg; }

int ResidenceBuilding::getWorth() {
  return 200;
}

int ResidenceBuilding::tuition() const {
  return totalOwns * 50;
}

int ResidenceBuilding::movement() const {
  return 0;
}

BuildingInfo ResidenceBuilding::getInfo() const {
  BuildingInfo bi;
  bi.bn = this->bn;
  bi.improvement = -1;
  bi.owner = this->owner;
  return bi;
}

void ResidenceBuilding::notify(Subject<BuildInfo> &whoFrom) {
  BuildingInfo bi = whoFrom.getInfo();
  auto it = monopoly.find(bi.bn);
  if (it == monopoly.end()) {
    monopoly.insert(std::pair<BuildingName,Player*>(bi.bn,bi.owner));
    return;
  }
  it->second = bi.owner;
  if (owner != nullptr) updateTotalOwns();
}


void ResidenceBuilding::setOwner(Player *p) {
  owner = p;
  updateTotalOwns();
  notifyObservers();
}

bool ResidenceBuilding::mortgage() {
  if (mtg == true) {
    cout << "This building is already mortgaged!" << endl;
    return false;
  }
  mortgage = true;
  owner->addFund(getCost()/2);
  return true;
}

bool ResidenceBuilding::unmortgage() {
  if (mtg == false) {
    cout << "This building is not mortgaged!" << endl;
    return false;
  }
  mortgage = false;
  owner->addFund(-getCost()*10/6);
  return true;
}


void ResidenceBuilding::updateTotalOwns() {
  totalOwns = 1;
  for (it = monopoly.begin(); it!= monopoly.end(); ++it) {
    if (it.second == owner) totalOwns++;
  }
}

void ResidenceBuilding::init() {
  owner = nullptr;
  totalOwns = 0;
  mtg = false;
}


