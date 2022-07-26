#include "board.h"

using namespace std;
Board::Board(string theme_file) {
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

  ifstream myfile(theme_file);
  string line;
  if (myfile.is_open()) {
    myfile >> width >> height;
    for (int i = 0; i < 40; ++i) {
      int x, y;
      myfile >> x >> y;
      buildingLayout[make_pair(x,y)] = i;
    }
  }
  myfile.close();
  for (int i = 0; i < 5 * height + 6; ++i) {
    text.emplace_back(string(9 * width + 10, ' '));
  }


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

void Board::init(vector<Player*> players) {
  // set building observer
  for (Building * bd : buildings) {
    bd->attach(this);
  }
  for (auto p : players) p->attach(this);
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



/*-------------compile text for building----------------------*/

void Board::compileAca(Building *b, int x, int y) {
  int pos = buildingLayout[make_pair(x,y)];
  BuildingName bn = getBuildingName(pos);
  string name;
  for (auto it = table.begin(); it != table.end(); it++) {
    if (it->second == bn) name = it->first;
  }
  for (int i = 1 + 5 * y; i < 6 + 5 * y; ++i) {
    text[i][9 + 9 * x] = '|';
  }
  for (int i = 1 + 9 * x; i < 9 + 9 * x; ++i) {
    text[5 + 5 * y][i] = '_';
  }

  // upper part for improvement
  for (int i = 1 + 9 * x; i < 9 + 9 * x; ++i) {
    text[5 * y + 2][i] = '-';
  }
  for (int i = 0; i < name.size(); ++i) {
    text[5 * y + 3][i + 1 + 9 * x] = name[i];
  }
  // improvement
  for (int i = 0; i < static_cast<AcademicBuilding *>(b)->getImprovement(); ++i) {
    text[5 * y + 1][i + 1 + 9 * x] = 'I';
  }
  // complete boundary
  if (buildingLayout.find(make_pair(x, y - 1)) == buildingLayout.end()) {
    for (int i = 1 + 9 * x; i < 9 + 9 * x; ++i) {
      text[5 * y][i] = '_';
    }
  }
  if (buildingLayout.find(make_pair(x - 1, y)) == buildingLayout.end()) {
    for (int i = 1 + 5 * y; i < 6 + 5 * y; ++i) {
      text[i][9 * x] = '|';
    }
  }

  // owner
  if (static_cast<AcademicBuilding *>(b)->getOwner() != nullptr) {
    text[5 * y + 3][6 + 1 + 9 * x] = static_cast<AcademicBuilding *>(b)->getOwner()->getName();
  }

}

void Board::compileOther(Building *b, int x, int y) {
  int pos = buildingLayout[make_pair(x,y)];
  BuildingName bn = getBuildingName(pos);
  string name;
  for (auto it = table.begin(); it != table.end(); it++) {
    if (it->second == bn) name = it->first;
  }
  int line = 1 + y * 5;
  for (int i = 0; i < 8; ++i) {
    if (i == name.size()) break;
    text[line][1 + i + 9 * x] = name[i];
  }
  if (name.size() > 8) {
    for (int i = 8; i < name.size(); ++i) {
      text[line+1][1 + x * 9 + i-8] = name[i];
    }
  }
  for (int i = 1 + 5 * y; i < 6 + 5 * y; ++i) {
    text[i][9 + 9 * x] = '|';
  }
  for (int i = 1 + 9 * x; i < 9 + 9 * x; ++i) {
    text[5 + 5 * y][i] = '_';
  }
  // complete boundary
  if (buildingLayout.find(make_pair(x, y - 1)) == buildingLayout.end()) {
    for (int i = 1 + 9 * x; i < 9 + 9 * x; ++i) {
      text[5 * y][i] = '_';
    }
  }
  if (buildingLayout.find(make_pair(x - 1, y)) == buildingLayout.end()) {
    for (int i = 1 + 5 * y; i < 6 + 5 * y; ++i) {
      text[i][9 * x] = '|';
    }
  }

  if (b->getBuildingType() != BuildingType::Nonproperty) {
    if (static_cast<Property *>(b)->getOwner() != nullptr) {
      text[5 * y + 2][7 + 1 + 9 * x] = static_cast<Property *>(b)->getOwner()->getName();
    }
  }
}

void Board::compilePlayers() {
  for (auto it = playerPos.begin(); it != playerPos.end(); it++) {
    int pos = it->second;
    int x, y;
    for (auto bit = buildingLayout.begin(); bit != buildingLayout.end(); bit++) {
      if (bit->second == pos) {
        x = bit->first.first;
        y = bit->first.second;
        break;
      }
    }
    int index = 0;
    while (text[4 + 5 * y][index + 9 * x] != ' ') {
      index++;
    }
    text[4 + 5 * y][index + 9 * x] = it->first;
  }
}

void Board::notify(Subject<PlayerInfo> &whoFrom) {
  PlayerInfo pi = whoFrom.getInfo();
  if (pi.pos == -1) {
    playerPos.erase(pi.name);
    return;
  }
  playerPos[pi.name] = pi.pos;
}


void Board::notify(Subject<BuildingInfo> &whoFrom) {}

Board::~Board() noexcept {
  for (Building * b : buildings) {
    delete b;
  }
}

BuildingName Board::getBuildingName(int pos) {
  return buildings[pos]->getBuildingName();
}

void Board::compileText() {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (buildingLayout.find(make_pair(j, i)) != buildingLayout.end()) {
        int pos = buildingLayout[make_pair(j, i)];
        Building *b = getBuilding(pos);
        if (b->getBuildingType() != BuildingType::Academic) {
          compileOther(b, j, i);
        } else {
          compileAca(b, j, i);
        }
      }
    }
  }
  compilePlayers();
}

void Board::clearBoard() {
  for (int i = 0; i < 5 * height + 6; ++i) {
    text[i] = (string(9 * width + 10, ' '));
  }
}
std::ostream &operator<<(std::ostream &out, Board* b) {
  b->compileText();
  for (string s : b->text) {
    out << s << endl;
  }
  b->clearBoard();
  return out;
}
