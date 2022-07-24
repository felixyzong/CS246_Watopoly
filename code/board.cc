#include "board.h"

using namespace std;
Board::Board() {
  // buildings initialize
  // index 0 - 9
  buildings.push_back(new NonPropertyBuilding(BuildingName::CollectOSAP));
  buildings.push_back(new AcademicBuilding(BuildingName::AL, MonopolyBlock::Arts1, AL));
  buildings.push_back(new NonPropertyBuilding(BuildingName::SLC));
  buildings.push_back(new AcademicBuilding(BuildingName::ML, MonopolyBlock::Arts1, ML));
  buildings.push_back(new NonPropertyBuilding(BuildingName::Tuition));
  buildings.push_back(new ResidenceBuilding(BuildingName::MKV));
  buildings.push_back(new AcademicBuilding(BuildingName::ECH, MonopolyBlock::Arts2, ECH));
  buildings.push_back(new NonPropertyBuilding(BuildingName::NeedlesHall));
  buildings.push_back(new AcademicBuilding(BuildingName::PAS, MonopolyBlock::Arts2, PAS));
  buildings.push_back(new AcademicBuilding(BuildingName::HH, MonopolyBlock::Arts2, HH));
  // index 10 - 19
  buildings.push_back(new NonPropertyBuilding(BuildingName::DCTimsLine));
  buildings.push_back(new AcademicBuilding(BuildingName::RCH, MonopolyBlock::Eng, RCH));
  buildings.push_back(new GymsBuilding(BuildingName::PAC));
  buildings.push_back(new AcademicBuilding(BuildingName::DWE, MonopolyBlock::Eng, DWE));
  buildings.push_back(new AcademicBuilding(BuildingName::CPH, MonopolyBlock::Eng, CPH));
  buildings.push_back(new ResidenceBuilding(BuildingName::UWP));
  buildings.push_back(new AcademicBuilding(BuildingName::LHI, MonopolyBlock::Health, LHI));
  buildings.push_back(new NonPropertyBuilding(BuildingName::SLC));
  buildings.push_back(new AcademicBuilding(BuildingName::BMH, MonopolyBlock::Health, BMH));
  buildings.push_back(new AcademicBuilding(BuildingName::OPT, MonopolyBlock::Health, OPT));
  // index 20 - 29
  buildings.push_back(new NonPropertyBuilding(BuildingName::GooseNesting));
  buildings.push_back(new AcademicBuilding(BuildingName::EV1, MonopolyBlock::Env, EV1));
  buildings.push_back(new NonPropertyBuilding(BuildingName::NeedlesHall));
  buildings.push_back(new AcademicBuilding(BuildingName::EV2, MonopolyBlock::Env, EV2));
  buildings.push_back(new AcademicBuilding(BuildingName::EV3, MonopolyBlock::Env, EV3));
  buildings.push_back(new ResidenceBuilding(BuildingName::V1));
  buildings.push_back(new AcademicBuilding(BuildingName::PHYS, MonopolyBlock::Sci1, PHYS));
  buildings.push_back(new AcademicBuilding(BuildingName::B1, MonopolyBlock::Sci1, B1));
  buildings.push_back(new GymsBuilding(BuildingName::CIF));
  buildings.push_back(new AcademicBuilding(BuildingName::B2, MonopolyBlock::Sci1, B2));
  // index 30 - 39
  buildings.push_back(new NonPropertyBuilding(BuildingName::GoToTims));
  buildings.push_back(new AcademicBuilding(BuildingName::EIT, MonopolyBlock::Sci2, EIT));
  buildings.push_back(new AcademicBuilding(BuildingName::ESC, MonopolyBlock::Sci2, ESC));
  buildings.push_back(new NonPropertyBuilding(BuildingName::SLC));
  buildings.push_back(new AcademicBuilding(BuildingName::C2, MonopolyBlock::Sci2, C2));
  buildings.push_back(new ResidenceBuilding(BuildingName::REV));
  buildings.push_back(new NonPropertyBuilding(BuildingName::NeedlesHall));
  buildings.push_back(new AcademicBuilding(BuildingName::MC, MonopolyBlock::Math, MC));
  buildings.push_back(new NonPropertyBuilding(BuildingName::CoopFee));
  buildings.push_back(new AcademicBuilding(BuildingName::DC, MonopolyBlock::Math, DC));
}

Building * Board::getBuilding(int pos) {
  return buildings[pos];
}

Building * Board::findBuilding(string name) {
  BuildingName bn = strtobn(name);
  for (Building *b : buildings) {
    if (b->getBuildingName() == bn) return b;
  }
  return nullptr;
}

void Board::notify(Subject<PlayerInfo> &whoFrom) {

}

void Board::notify(Subject<BuildingInfo> &whoFrom) {

}

Board::~Board() noexcept {
  for (Building * b : buildings) {
    delete b;
  }
}