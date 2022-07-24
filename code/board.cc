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


  // Monopoly block initiation
  // Arts1
  buildings[1]->attach(static_cast<AcademicBuilding *>(buildings[3]));
  buildings[3]->attach(static_cast<AcademicBuilding *>(buildings[1]));

  // Arts2
  buildings[6]->attach(static_cast<AcademicBuilding *>(buildings[8]));
  buildings[6]->attach(static_cast<AcademicBuilding *>(buildings[9]));
  buildings[8]->attach(static_cast<AcademicBuilding *>(buildings[6]));
  buildings[8]->attach(static_cast<AcademicBuilding *>(buildings[9]));
  buildings[9]->attach(static_cast<AcademicBuilding *>(buildings[6]));
  buildings[9]->attach(static_cast<AcademicBuilding *>(buildings[8]));

  // Eng
  buildings[11]->attach(static_cast<AcademicBuilding *>(buildings[13]));
  buildings[11]->attach(static_cast<AcademicBuilding *>(buildings[14]));
  buildings[13]->attach(static_cast<AcademicBuilding *>(buildings[11]));
  buildings[13]->attach(static_cast<AcademicBuilding *>(buildings[14]));
  buildings[14]->attach(static_cast<AcademicBuilding *>(buildings[11]));
  buildings[14]->attach(static_cast<AcademicBuilding *>(buildings[13]));

  // Health
  buildings[16]->attach(static_cast<AcademicBuilding *>(buildings[18]));
  buildings[16]->attach(static_cast<AcademicBuilding *>(buildings[19]));
  buildings[18]->attach(static_cast<AcademicBuilding *>(buildings[16]));
  buildings[18]->attach(static_cast<AcademicBuilding *>(buildings[19]));
  buildings[19]->attach(static_cast<AcademicBuilding *>(buildings[16]));
  buildings[19]->attach(static_cast<AcademicBuilding *>(buildings[18]));

  // Env
  buildings[21]->attach(static_cast<AcademicBuilding *>(buildings[23]));
  buildings[21]->attach(static_cast<AcademicBuilding *>(buildings[24]));
  buildings[23]->attach(static_cast<AcademicBuilding *>(buildings[21]));
  buildings[23]->attach(static_cast<AcademicBuilding *>(buildings[24]));
  buildings[24]->attach(static_cast<AcademicBuilding *>(buildings[21]));
  buildings[24]->attach(static_cast<AcademicBuilding *>(buildings[23]));

  // Sci1
  buildings[26]->attach(static_cast<AcademicBuilding *>(buildings[27]));
  buildings[26]->attach(static_cast<AcademicBuilding *>(buildings[29]));
  buildings[27]->attach(static_cast<AcademicBuilding *>(buildings[26]));
  buildings[27]->attach(static_cast<AcademicBuilding *>(buildings[29]));
  buildings[29]->attach(static_cast<AcademicBuilding *>(buildings[26]));
  buildings[29]->attach(static_cast<AcademicBuilding *>(buildings[27]));

  // Sci2
  buildings[31]->attach(static_cast<AcademicBuilding *>(buildings[32]));
  buildings[31]->attach(static_cast<AcademicBuilding *>(buildings[34]));
  buildings[32]->attach(static_cast<AcademicBuilding *>(buildings[31]));
  buildings[32]->attach(static_cast<AcademicBuilding *>(buildings[34]));
  buildings[34]->attach(static_cast<AcademicBuilding *>(buildings[31]));
  buildings[34]->attach(static_cast<AcademicBuilding *>(buildings[32]));

  // Math
  buildings[37]->attach(static_cast<AcademicBuilding *>(buildings[39]));
  buildings[39]->attach(static_cast<AcademicBuilding *>(buildings[37]));

  // Residence
  buildings[5]->attach(static_cast<ResidenceBuilding *>(buildings[15]));
  buildings[5]->attach(static_cast<ResidenceBuilding *>(buildings[25]));
  buildings[5]->attach(static_cast<ResidenceBuilding *>(buildings[35]));
  buildings[15]->attach(static_cast<ResidenceBuilding *>(buildings[5]));
  buildings[15]->attach(static_cast<ResidenceBuilding *>(buildings[25]));
  buildings[15]->attach(static_cast<ResidenceBuilding *>(buildings[35]));
  buildings[25]->attach(static_cast<ResidenceBuilding *>(buildings[5]));
  buildings[25]->attach(static_cast<ResidenceBuilding *>(buildings[15]));
  buildings[25]->attach(static_cast<ResidenceBuilding *>(buildings[35]));
  buildings[35]->attach(static_cast<ResidenceBuilding *>(buildings[5]));
  buildings[35]->attach(static_cast<ResidenceBuilding *>(buildings[15]));
  buildings[35]->attach(static_cast<ResidenceBuilding *>(buildings[25]));

  // Gyms
  buildings[12]->attach(static_cast<GymsBuilding *>(buildings[28]));
  buildings[28]->attach(static_cast<GymsBuilding *>(buildings[12]));

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