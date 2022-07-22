#include "gameplay.h"

Gameplay::Gameplay(bool test): availablePlayers{'G','B','D','P','S','$','L','T'} {
  const int defaultMoney = 1500;
  int playerCount;
  char playerChar;
  std::cout << "Please enter the number of players(at lease 6, at most 8):";
  std::cin >> playerCount;
  while (playerCount < 6 || playerCount > 8) {
    std::cout << "Invalid number of players." << std::endl;
    std::cout << "Please enter the number of players(at lease 6, at most 8):";
    std::cin >> playerCount;
  }

  // display a list of avatas for choosing
  std::cout << "Please choose your avatar from the following:" << std::endl;
  std::cout << "| Goose | GRT bus | Tim Hortons Doughnut | Professor | Student | Money | Laptop | Pink tie |" << std::endl;
  std::cout << "|   G   |    B    |           D          |     P     |    S    |   $   |   L    |    T     |" << std::endl;

  // every player enter their avatar
  for (int i = 0; i < playerCount; ++i) {
    std::cout << "Current available avatars: ";
    for (auto it = availablePlayers.begin(); it != availablePlayers.end(); ++it) {
      std::cout  << " " << *it;
    }
    std::cout << std::endl;
    std::cout << "Player #" << i << ", please enter your avator char:";
    std::cin >> playerChar;
    while (std::find(defaultPlayerName.begin(), defaultPlayerName.end(), x) == defaultPlayerName.end())
    {
      std::cout << "Invalid avatar char, please choose from available!" << std::cout;
      std::cout << "Current available avatars: ";
      for (auto it = availablePlayers.begin(); it != availablePlayers.end(); ++it) {
        std::cout  << " " << *it;
      }
      std::cout << "Player #" << i << ", please enter your avator char:";
      std::cin >> playerChar;
    }
    availablePlayers.erase(playerChar);
    players.push_back(new Player(defaultMoney, playerChar));
  }

  // buildings initialize
  // index 0 - 9
  buildings.push_back(new NonPropertyBuilding(BuildingName::CollectOSAP));
  buildings.push_back(new AcademicBuilding(BuildingName::AL));
  buildings.push_back(new NonPropertyBuilding(BuildingName::SLC));
  buildings.push_back(new AcademicBuilding(BuildingName::ML));
  buildings.push_back(new NonPropertyBuilding(BuildingName::Tuition));
  buildings.push_back(new ResidenceBuilding(BuildingName::MKV));
  buildings.push_back(new AcademicBuilding(BuildingName::ECH));
  buildings.push_back(new NonPropertyBuilding(BuildingName::NeedlesHall));
  buildings.push_back(new AcademicBuilding(BuildingName::PAS));
  buildings.push_back(new AcademicBuilding(BuildingName::HH));
  // index 10 - 19
  buildings.push_back(new NonPropertyBuilding(BuildingName::DCTimsLine));
  buildings.push_back(new AcademicBuilding(BuildingName::RCH));
  buildings.push_back(new GymsBuilding(BuildingName::PAC));
  buildings.push_back(new AcademicBuilding(BuildingName::DWE));
  buildings.push_back(new AcademicBuilding(BuildingName::CPH));
  buildings.push_back(new ResidenceBuilding(BuildingName::UWP));
  buildings.push_back(new AcademicBuilding(BuildingName::LHI));
  buildings.push_back(new NonPropertyBuilding(BuildingName::SLC));
  buildings.push_back(new AcademicBuilding(BuildingName::BMH));
  buildings.push_back(new AcademicBuilding(BuildingName::OPT));
  // index 20 - 29
  buildings.push_back(new NonPropertyBuilding(BuildingName::GooseNesting));
  buildings.push_back(new AcademicBuilding(BuildingName::EV1));
  buildings.push_back(new AcademicBuilding(BuildingName::NeedlesHall));
  buildings.push_back(new AcademicBuilding(BuildingName::EV2));
  buildings.push_back(new AcademicBuilding(BuildingName::EV3));
  buildings.push_back(new ResidenceBuilding(BuildingName::V1));
  buildings.push_back(new AcademicBuilding(BuildingName::PHYS));
  buildings.push_back(new AcademicBuilding(BuildingName::B1));
  buildings.push_back(new GymsBuilding(BuildingName::CIF));
  buildings.push_back(new AcademicBuilding(BuildingName::B2));
  // index 30 - 39
  buildings.push_back(new NonPropertyBuilding(BuildingName::GoToTims));
  buildings.push_back(new AcademicBuilding(BuildingName::EIT));
  buildings.push_back(new AcademicBuilding(BuildingName::ESC));
  buildings.push_back(new NonPropertyBuilding(BuildingName::SLC));
  buildings.push_back(new AcademicBuilding(BuildingName::C2));
  buildings.push_back(new ResidenceBuilding(BuildingName::REV));
  buildings.push_back(new NonPropertyBuilding(BuildingName::NeedlesHall));
  buildings.push_back(new AcademicBuilding(BuildingName::MC));
  buildings.push_back(new NonPropertyBuilding(BuildingName::CoopFee));
  buildings.push_back(new AcademicBuilding(BuildingName::DC));

  b = new Board(buildings, players);
  curPlayer = players[0];
  isTest = test;

}


Gameplay::~Gameplay() {
  delete b;
  delete td;
  for (auto it = players.begin(); it != players.end(); ++it) delete it;
}


Player *Gameplay::findPlayer(char c) {
  for (auto it = players.begin(); it != players.end(); ++it) {
    if (it->getName() == c) return it;
  }
  return NULL;
}


void Gameplay::switchPlayer() {
  auto it = find(players.begin(), players.end(), curPlayer);
  int index = it - players.begin();
  if (index != players.size()+1) {
    index++;
  } else index = 0;
  curPlayer = players[index];
}


void Gameplay::dropOut(Player * p) {
  if (curPlayer == p) switchPlayer();
  playes.erase(p);
}


bool Gameplay::checkBankRuptcy(Player * p) {
  if (p->getTotalWorth() < 0) dropOut(p);
}

void auction(Building *b) {
  
}





