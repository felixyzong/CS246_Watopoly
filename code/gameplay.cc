#include "gameplay.h"
#include "info.h"
using namespace std;

Gameplay::Gameplay(bool test): availablePlayers{'G','B','D','P','S','$','L','T'} {
  const int defaultMoney = 1500;
  int playerCount;
  char playerChar;
  cout << "Please enter the number of players(at lease 6, at most 8):";
  cin >> playerCount;
  while (playerCount < 6 || playerCount > 8) {
    cout << "Invalid number of players." << endl;
    cout << "Please enter the number of players(at lease 6, at most 8):";
    cin >> playerCount;
  }

  // display a list of avatas for choosing
  cout << "Please choose your avatar from the following:" << endl;
  cout << "| Goose | GRT bus | Tim Hortons Doughnut | Professor | Student | Money | Laptop | Pink tie |" << endl;
  cout << "|   G   |    B    |           D          |     P     |    S    |   $   |   L    |    T     |" << endl;

  // every player enter their avatar
  for (int i = 0; i < playerCount; ++i) {
    cout << "Current available avatars: ";
    for (char name : availablePlayers) {
      cout  << " " << name;
    }
    cout << endl;
    cout << "Player #" << i << ", please enter your avator char:";
    cin >> playerChar;
    while (find(defaultPlayerName.begin(), defaultPlayerName.end(), x) == defaultPlayerName.end())
    {
      cout << "Invalid avatar char, please choose from available!" << cout;
      cout << "Current available avatars: ";
      for (char name : availablePlayers) {
        cout  << " " << name;
      }
      cout << "Player #" << i << ", please enter your avator char:";
      cin >> playerChar;
    }
    availablePlayers.erase(playerChar);
    players.push_back(new Player(defaultMoney, playerChar));
  }

  // buildings initialize
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
  vector<int> d = { 1, 2, 3, 4, 5, 6 };
  int die1 = shuffle( d.begin(), d.end(), default_random_engine(seed) );
  int die2 = shuffle( d.begin(), d.end(), default_random_engine(seed) );
  roll(die1,die2);
}

void Gameplay::roll(int die1, int die2) {
  if (curPlayer->isInTim()) {
    if (die1 == die2) {
      curPlayer->isInTimLine = false;
      roll(die1,die2);
      return;
    } else {
      curPlayer->incTimTurn();
    }
  }

  curPlayer->Move(die1+die2);
  Building * curBuilding = buildings[curPlayer->getPos()];

  if (curBuilding->getBuildingType() != BuildingType::Nonproperty) {
    Player *owner = curBuilding.getOwner();
    if ( owner == nullptr ) {
      cout << curBuilding->GetBuildingName() << " has no owner, do you want to buy it at a price of $" << curBuilding->getCost() << "?" << endl;
      cout << "Please enter yes or no: ";
      string yn;
      cin >> yn;
      if (yn == "yes") {
        while(curPlayer->getMoney() < curBuilding->getCost()) {
          cout << "You don't have enough money! You only have " << curPlayer->getMoney() << endl;
          cout << "Would you like to trade/sell property/improvements? Please enter yes or no: ";
          if (yn == "yes") {
            parseAction();
          } else if (yn == "no") {
            auction(curBuilding);
            curPlayer->rolled = true;
            return;
          }
        }
        cout << "You bought " << curBuilding->GetBuildingName() << " successfully!" << endl;
        curPlayer->buyProperty(curBuilding);
      
      } else if (yn == "no") {
        auction(curBuilding);
      }
    } else if ( owner == curPlayer && curBuilding->getBuidlingType() == BuildingType::Academic 
    && curBuilding->getMonopoly == curPlayer && curBuilding->getImprovement < 5) {
      cout << "Improvement available at" << curBuilding->GetBuildingName() << cout;
    } else if (owner != curPlayer) {
      curTuition = curBuilding->getTuition();
      cout << "You need to pay " << curTuition << " tuition to " << owner->getName() << endl;
      while(curPlayer->getMoney() < curTuition) {
        cout << "You don't have enough money! You only have " << curPlayer->getMoney() << endl;
        cout << "You need to raise money!";
        if (!parseAction()) return;
      }
      cout << "You paid tuition successfully." << endl;
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
        cout << "You need to pay $300 or 10\%($" << curPlayer->getTotalWorth()/10 << ") of your total wealth:" << endl;
        cout << "Please choose your way to pay (enter $300 or 10%): " << endl;
        string payMethod;
        cin >> payMethod;
        if (payMethod = "$300") curPlayer->addFund(-300);
        else if (payMethod = "10%") curPlayer->addFund(-curPlayer->getTotalWorth()/10);
        break;
      case BuildingName::CoopFee:
        curTuition = curBuilding->getTuition();
        cout << "You need to pay " << curTuition << " COOP fee to University of Waterloo." << endl;
        while(curPlayer->getMoney() < curTuition) {
          cout << "You don't have enough money! You only have " << curPlayer->getMoney() << endl;
          cout << "You need to raise money!";
          if (!parseAction()) return;
        }
        cout << "You paid COOP fee successfully." << endl;
        curPlayer->addFund(-curTuition);
      case BuildingName::SLC:
        if (totalRimCup < 4) {
          int result = curPlayer->rollDice(seed);
          if (result == 100) {
            curPlayer->gainCup();
            totalRimCup += 1;
            cout << "You get a Rim Cup!" << endl;
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
          int result = curPlayer->rollDice(seed);
          if (result == 100) {
            curPlayer->gainCup();
            totalRimCup += 1;
            cout << "You get a Rim Cup!" << endl;
          }
        }
        curTuition = curBuilding->tuition();
        if (curTuition > 0) {
          cout << "You gain $" << curTuition << "." << endl;
          curPlayer->addFund(curTuition);
        } else {
          cout << "You lose $" << curTuition << "." << endl;\
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

void setseed(seed) {
  this->seed = seed;
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


