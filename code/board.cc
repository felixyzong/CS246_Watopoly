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

  
  
  // text display initialization
  text.push_back(string("_________________________________________________________________________________________")); // 0
  text.push_back(string("|Goose  |       |NEEDLES|       |       |V1     |       |       |CIF    |       |GO TO  |"));
  text.push_back(string("|Nesting|-------|HALL   |-------|-------|       |-------|-------|       |-------|TIMS   |"));
  text.push_back(string("|       |EV1    |       |EV2    |EV3    |       |PHYS   |B1     |       |B2     |       |"));
  text.push_back(string("|       |       |       |       |       |       |       |       |       |       |       |"));
  text.push_back(string("|       |       |       |       |       |       |       |       |       |       |       |"));
  text.push_back(string("|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|"));
  text.push_back(string("|       |                                                                       |       |"));
  text.push_back(string("|-------|                                                                       |-------|"));
  text.push_back(string("|OPT    |                                                                       |EIT    |"));
  text.push_back(string("|       |                                                                       |       |")); // 10
  text.push_back(string("|       |              Sample:                                                  |       |"));
  text.push_back(string("|_______|                _______                                                |_______|"));
  text.push_back(string("|       |               | BBBBC |   B: Bathroom improvement                     |       |"));
  text.push_back(string("|-------|               |-------|   C: Cafeteria improvement                    |-------|"));
  text.push_back(string("|BMH    |               |BDN  O |   BDN: Name of the building                   |ESC    |"));
  text.push_back(string("|       |               | ABCDE |   O: Owner of the building                    |       |"));
  text.push_back(string("|       |               | FGH   |   ABCDEFGH: Players at this building          |       |"));
  text.push_back(string("|_______|               |_______|                                               |_______|"));
  text.push_back(string("|SLC    |                                                                       |SLC    |")); 
  text.push_back(string("|       |                                                                       |       |")); // 20
  text.push_back(string("|       |                                                                       |       |"));
  text.push_back(string("|       |                                                                       |       |")); 
  text.push_back(string("|       |                                                                       |       |"));
  text.push_back(string("|_______|                                                                       |_______|"));
  text.push_back(string("|       |                                                                       |       |"));
  text.push_back(string("|-------|                                                                       |-------|"));
  text.push_back(string("|LHI    |                                                                       |C2     |"));
  text.push_back(string("|       |                                                                       |       |"));
  text.push_back(string("|       |            _______________________________________________            |       |")); 
  text.push_back(string("|_______|           |                                               |           |_______|")); // 30
  text.push_back(string("|UWP    |           | #   #  ###  #####  ###  ####   ###  #   #   # |           |REV    |"));
  text.push_back(string("|       |           | #   # #   #   #   #   # #   # #   # #   #   # |           |       |"));
  text.push_back(string("|       |           | # # # #####   #   #   # ####  #   # #    # #  |           |       |"));
  text.push_back(string("|       |           | # # # #   #   #   #   # #     #   # #     #   |           |       |"));
  text.push_back(string("|       |           |  ###  #   #   #    ###  #      ###  ####  #   |           |       |"));
  text.push_back(string("|_______|           |_______________________________________________|           |_______|"));
  text.push_back(string("|       |                                                                       |NEEDLES|"));
  text.push_back(string("|-------|                                                                       |HALL   |"));
  text.push_back(string("|CPH    |                                                                       |       |")); 
  text.push_back(string("|       |                                                                       |       |")); // 40
  text.push_back(string("|       |                                                                       |       |"));
  text.push_back(string("|_______|           Monopoly Block:                                             |_______|"));
  text.push_back(string("|       |           Arts1: AL, ML                                               |       |"));
  text.push_back(string("|-------|           Arts2: ECH, PAS, HH                                         |-------|"));
  text.push_back(string("|DWE    |           Eng: RCH, DWE, CPH                                          |MC     |"));
  text.push_back(string("|       |           Health: LHI, BMH, OPT                                       |       |"));
  text.push_back(string("|       |           Env: EV1, EV2, EV3                                          |       |"));
  text.push_back(string("|_______|           Sci1: PHYS, B1, B2                                          |_______|"));
  text.push_back(string("|PAC    |           Sci2: EIT, ESC, C2                                          |COOP   |")); 
  text.push_back(string("|       |           Math: MC, DC                                                |FEE    |")); // 50
  text.push_back(string("|       |                                                                       |       |"));
  text.push_back(string("|       |                                                                       |       |"));
  text.push_back(string("|       |                                                                       |       |"));
  text.push_back(string("|_______|                                                                       |_______|"));
  text.push_back(string("|       |                                                                       |       |"));
  text.push_back(string("|-------|                                                                       |-------|"));
  text.push_back(string("|RCH    |                                                                       |DC     |"));
  text.push_back(string("|       |                                                                       |       |"));
  text.push_back(string("|       |                                                                       |       |")); 
  text.push_back(string("|_______|_______________________________________________________________________|_______|")); // 60
  text.push_back(string("|DC Tims|       |       |NEEDLES|       |MKV    |TUITION|       |SLC    |       |COLLECT|"));
  text.push_back(string("|Line   |-------|-------|HALL   |-------|       |       |-------|       |-------|OSAP   |"));
  text.push_back(string("|       |HH     |PAS    |       |ECH    |       |       |ML     |       |AL     |       |"));
  text.push_back(string("|       |       |       |       |       |       |       |       |       |       |       |"));
  text.push_back(string("|       |       |       |       |       |       |       |       |       |       |       |"));
  text.push_back(string("|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|"));
                              //01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678
                              //0         1         2         3         4         5         6         7         8 


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

void Board::notify(Subject<PlayerInfo> &whoFrom) {
  PlayerInfo pi = whoFrom.getInfo();

  auto it = playerPos.find(pi.name);
  
  if (it == playerPos.end()) {
    playerPos.insert(make_pair(pi.name,pi.pos));
  } 
  clearPlayer(pi.name);

  if (pi.pos == -1) {
    playerPos.erase(pi.name);
    return;
  }
  auto entry = getBoardEntry(pi.pos);
  bool write = false;
  for (int i = entry.first+3; i != entry.first+5; i++){
    for (int j = entry.second+1; j != entry.second+6; j++) {
      if (text[i][j] == ' ') {
        text[i][j] = pi.name;
        it->second == pi.pos;
        write = true;
        break;
      }
    }
    if (write) break;
  }

}

void Board::notify(Subject<BuildingInfo> &whoFrom) {
  BuildingInfo bi = whoFrom.getInfo();
  int pos = getBuildingPos(bi.bn);
  auto entry = getBoardEntry(pos);
  if (bi.improvement != -1) {
    for (int i = 1; i < 5; i++){
      if (bi.improvement >= i) {
        text[entry.first][entry.second+i] = 'B';
      } else {
        text[entry.first][entry.second+i] = ' ';
      }
    }
    if (bi.improvement == 5) {
      text[entry.first][entry.second+5] = 'C';
    } else {
      text[entry.first][entry.second+5] = ' ';
    }
  }

  if (bi.owner) {
    text[entry.first+2][entry.second+5] = bi.owner->getName();
  } else {
    text[entry.first+2][entry.second+5] = ' ';
  }
}

Board::~Board() noexcept {
  for (Building * b : buildings) {
    delete b;
  }
}

BuildingName Board::getBuildingName(int pos) {
  return buildings[pos]->getBuildingName();
}

int Board::getBuildingPos(BuildingName bn) {
  for (int i = 0; i != buildings.size(); ++i) {
    if (getBuildingName(i) == bn) return i;
  }
  return -1; // should not happen
}

// return the coordinate of left up cornor of the building square
pair<int,int> Board::getBoardEntry(int pos) {
  if ( pos < 10) {
    return make_pair(61,81-8*pos);
  } else if ( pos < 20 ) {
    return make_pair(121-pos*6,1);
  } if ( pos < 30 ) {
    return make_pair(1,pos*8-159);
  } else if (pos < 40 ) {
    return make_pair(pos*6-179,81);
  }
  return make_pair(0,0); // should not happen
}

void Board::clearPlayer(char name) {
  auto it = playerPos.find(name);
  auto entry = getBoardEntry(it->second);
  for (int i = entry.first+3; i != entry.first+5; i++) {
    for (int j = entry.second+1; j != entry.second+6; j++) {
      if (text[i][j] == name) {
        text[i][j] = ' ';
      }
    }    
  }
}

std::ostream &operator<<(std::ostream &out, Board* b) {
  for (string s : b->text) {
    out << s << endl;
  }
  return out;
}

