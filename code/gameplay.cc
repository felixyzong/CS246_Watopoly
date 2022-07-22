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
  curBuilding = buildings[0];
  curPlayer = players[0];
  isTest = test;

}


Gameplay::~Gameplay() {
  delete b;
  delete buildings;
  for (auto it = players.begin(); it != players.end(); ++it) delete it;
}


Player *Gameplay::findPlayer(char c) {
  for (auto it = players.begin(); it != players.end(); ++it) {
    if (it->getName() == c) return it;
  }
  return nullptr;
}


void Gameplay::switchPlayer() {
  auto it = find(players.begin(), players.end(), curPlayer);
  int index = it - players.begin();
  if (index != players.size()+1) {
    index++;
  } else index = 0;
  curPlayer = players[index];
  curBuilding = buildings[curPlayer->getPos];
  curTuition = 0;
}


void Gameplay::dropOut() {
  if (curPlayer->cup > 0) totalRimCup -= curPlayer->cup;
  Player *p = curPlayer;
  switchPlayer();
  players.erase(p);
}


bool Gameplay::checkBankRuptcy() {
  if (curPlayer->getMoney() < curTuition) return true;
  else return false;
}


void Gameplay::roll() {
  std::vector<int> d = { 1, 2, 3, 4, 5, 6 };
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  int die1 = std::shuffle( d.begin(), d.end(), std::default_random_engine(seed) );
  int die2 = std::shuffle( d.begin(), d.end(), std::default_random_engine(seed) );
  roll(die1,die2);
}

void Gameplay::roll(int die1, int die2) {
  if (curPlayer->isInTim()) {
    if (die1 == die2) {
      curPlayer->isInTimLine = false;
      roll(die1,die2);
    } else {
      curPlayer->incTimTurn();
    }
  }

  curPlayer->Move(die1+die2);
  Building * curBuilding = buildings[curPlayer->getPos()];

  if (curBuilding->getBuildingType() != BuildingType::Nonproperty) {
    Player *owner = curBuilding.getOwner();
    if ( owner == nullptr ) {
      std::cout << curBuilding->GetBuildingName() << " has no owner, do you want to buy it at a price of $" << curBuilding->getCost() << "?" << std::endl;
      std::cout << "Please enter yes or no: ";
      std::string yn;
      std::cin >> yn;
      if (yn == "yes") {
        while(curPlayer->getMoney() < curBuilding->getCost()) {
          std::cout << "You don't have enough money! You only have " << curPlayer->getMoney() << std::endl;
          std::cout << "Would you like to trade/sell property/improvements? Please enter yes or no: ";
          if (yn == "yes") {
            parseAction();
          } else if (yn == "no") {
            auction(curBuilding);
            curPlayer->rolled = true;
            return;
          }
        }
        std::cout << "You bought " << curBuilding->GetBuildingName() << " successfully!" << std::endl;
        curPlayer->buyProperty(curBuilding);
      
      } else if (yn == "no") {
        auction(curBuilding);
      }
    } else if ( owner == curPlayer && curBuilding->getBuidlingType() == BuildingType::Academic 
    && curBuilding->getMonopoly == curPlayer && curBuilding->getImprovement < 5) {
      std::cout << "Improvement available at" << curBuilding->GetBuildingName() << std::cout;
    } else if (owner != curPlayer) {
      curTuition = curBuilding->getTuition();
      std::cout << "You need to pay " << curTuition << " tuition to " << owner->getName() << std::endl;
      while(curPlayer->getMoney() < curTuition) {
        std::cout << "You don't have enough money! You only have " << curPlayer->getMoney() << std::endl;
        std::cout << "You need to raise money!";
        if (!parseAction()) return;
      }
      std::cout << "You paid tuition successfully." << std::endl;
      curPlayer->addFund(-curTuition);
      owner->addFund(curTuition);
    }
  } else if ( curBuilding->getBuidlingType() == BuildingType::Nonproperty) {
    int moveNum;
    switch(curBuilding->GetBuildingName()) {
      case BuildingName::CollectOSAP:
        curPlayer->addFund(200);
        break;
      case BuildingName::DCTimsLine:
        break;
      case BuildingName::GoToTims:
        moveNum = 50 - curPlayer->getPos();
        moveNum %= 40;
        curPlayer->move(moveNum);
        if (curPlayer->cup > 0) {
          curPlayer->cup -= 1;
          roll(die1,die2);
        } else {
          curPlayer->isInTimLine = true;
          curPlayer->move(moveNum);
        }
        break;
      case BuildingName::GooseNesting:
        break;
      case BuildingName::Tuition:
        std::cout << "You need to pay $300 or 10\%($" << curPlayer->getTotalWorth()/10 << ") of your total wealth:" << std::endl;
        std::cout << "Please choose your way to pay (enter $300 or 10%): " << std::endl;
        std::string payMethod;
        std::cin >> payMethod;
        if (payMethod = "$300") curPlayer->addFund(-300);
        else if (payMethod = "10%") curPlayer->addFund(-curPlayer->getTotalWorth()/10);
        break;
      case BuildingName::CoopFee:
        curTuition = curBuilding->getTuition();
        std::cout << "You need to pay " << curTuition << " COOP fee to University of Waterloo." << std::endl;
        while(curPlayer->getMoney() < curTuition) {
          std::cout << "You don't have enough money! You only have " << curPlayer->getMoney() << std::endl;
          std::cout << "You need to raise money!";
          if (!parseAction()) return;
        }
        std::cout << "You paid COOP fee successfully." << std::endl;
        curPlayer->addFund(-curTuition);
      case BuildingName::SLC:
        if (totalRimCup < 4) {
          unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
          int result = curPlayer->rollDice(seed);
          if (result == 100) {
            curPlayer->gainCup();
            totalRimCup += 1;
            std::cout << "You get a Rim Cup!" << std::endl;
          }
        }
        moveNum = curBuidling->MoveTo();
        if (moveNum == -4) {
          // move to DC Tims Line
          moveNum = 50 - curPlayer->getPos();
          moveNum %= 40;
        } else if (moveNum == 4) {
          // move to Collect OSAP
          moveNum = 40 - curPlayer->getPos();
        }
        if (moveNum != 0) roll(0,moveNum);
        break;
      case BuildingName::NeedlesHall:
        if (totalRimCup < 4) {
          unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
          int result = curPlayer->rollDice(seed);
          if (result == 100) {
            curPlayer->gainCup();
            totalRimCup += 1;
            std::cout << "You get a Rim Cup!" << std::endl;
          }
        }
        curTuition = curBuilding->tuition();
        if (curTuition > 0) {
          std::cout << "You gain $" << curTuition << "." << std::endl;
          curPlayer->addFund(curTuition);
        } else {
          std::cout << "You lose $" << curTuition << "." << std::endl;\
          if (curPlayer->money + curTuition < 0) {
            curPlayer->addFund(-curPlayer->money);
          }
          curPlayer->addFund(curTuition);
        }
        break;
    }
  }
  curPlayer->rolled = true;
}


bool Gameplay::parseAction() {

}

void Gameplay::trade(Building* b, Player* p, int money) {

}

void Gameplay::auction(Building* b) {

}

void Gameplay::improve(AcademicBuilding *ab, char instruction) {

}

void Gameplay::mortage(Building *b) {

}

void Gameplay::unmortage(Building *b) {

}

void Gameplay::assets() {

}

void Gameplay::all() {

}


void Gameplay::play() {

}

void Gameplay::saveGame(){

}

void Gameplay::loadGame(std::string file) {

}

std::ostream &operator<<(std::ostream& out, Gameplay* gp) {

}


