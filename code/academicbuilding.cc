#include "academicbuilding.h"
#include "player.h"
#include <vector>
#include "building.h"
using namespace std;


class AcademicBuilding : public Building {
  MonopolyBlock mb;
  Player* owner = nullptr;
  Player* monopolist = nullptr;
  std::map<BuildingName, Player*> monopoly;
  int improvement = 0;
  bool mortgage = 0;
  std::vector<int> info;


AcademicBuilding::AcademicBuilding(BuildingName bn, vector<int> info) : bn{bn}, info{info} {}

AcademicBuilding::~AcademicBuilding() {
  owner.clear;
  monopolist.clear;
  monopoly.clear;
  info.clear;
}

Player * AcademicBuilding::getowner() {
  return owner;
}

void AcademicBuilding::setOwner(Player *p) {
  owner = p;
}

MonopolyBlock AcademicBuilding::getMonopoly() {
  if (bn ==  BuildingName::AL || bn == BuildingName::ML) {
    mb = MonopolyBlock::Arts1;
  } else if (bn == BuildingName::ECH || bn == BuildingName::PAS || bn == BuildingName::HH) {
    mb = MonopolyBlock::Arts2;
  } else if (bn == BuildingName::RCH || bn == BuildingName::DWE || bn == BuildingName::CPH) {
    mb = MonopolyBlock::Eng;
  } else if (bn == BuildingName::LHI || bn == BuildingName::BMH || bn == BuildingName::OPT) {
    mb = MonopolyBlock::Health;
  } else if (bn == BuildingName::EV1 || bn == BuildingName::EV2 || bn == BuildingName::EV3) {
    mb = MonopolyBlock::Env;
  } else if (bn == BuildingName::PHYS || bn == BuildingName::B1 || bn == BuildingName::B2) {
    mb = MonopolyBlock::Sci1;
  } else if (bn == BuildingName::EIT || bn == BuildingName::ESC || bn == BuildingName::C2) {
    mb = MonopolyBlock::Sci2;
  } else if (bn == BuildingName::MC || bn == BuildingName::DC) {
    mb = MonopolyBlock::Math;
  } 
  return mb;
}

int AcademicBuilding::getCost() {
  return info[0];
}

int AcademicBuilding::getImprovementCost() {
  return info[1];
}

int AcademicBuilding::getWorth() {
  return 0.5 * (info[0] + (info[1] * improvement));
}


int AcademicBuilding::tuition() {
  if (monopolist != nullptr && improvement == 0) {
    return 2* info[2];
  } else {
    return info[improvement+2];
  }
}

int AcademicBuilding::movement() {
  return 0;
}

bool AcademicBuilding::AddImprovement() {
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
  return true;
}

bool AcademicBuilding::sellImprovement() {
  if (improvement == 0) {
    cout << "There is no improvement at this building, you can't sell!" << endl;
    return false;
  }
  improvement--;
  owner->addFund(info[1] / 2);
  return true;
}

<<<<<<< HEAD
int AcademicBuilding::getImprovement() {
  return improvement;
=======
int AcademicBuilding::tuition() const {
  return info[improvement + 2];
}

Player * AcademicBuilding::getOwner() {
  return owner;
>>>>>>> 444017ad208972637c1afd14f9a1fcdbed30595c
}

bool AcademicBuilding::getMortgage() {
  return mortgage;
}

void AcademicBuilding::mortgage() {
<<<<<<< HEAD
  owner->addFund(0.5 * (info[0] + (info[1] * improvement)));
  improvement = 0;
  mortgage = 1;
}
void AcademicBuilding::unMortgage() {
  owner->addFund(-0.6 * info[0]);
  mortgage = 0;
} 


BuildingInfo AcademicBuilding::getInfo() {
  BuildingInfo bi;
  bi.bn = bn;
  bi.owner = owner;
  bi.improvement = improvement;
  return bi;
}

void AcademicBuilding::notify(Subject<BuildingInfo> &whoFrom) {
}

void AcademicBuilding::updateMonopolist() {
  if (monopoly->Player)
}
void AcademicBuilding::init() {
}
  
=======
  mortgage = true;
}

void AcademicBuilding::unMortgage() {
  mortgage = false;
}

void AcademicBuilding::setOwner(Player *p) {
  owner = p;
}
>>>>>>> 444017ad208972637c1afd14f9a1fcdbed30595c
