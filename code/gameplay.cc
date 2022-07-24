#include "gameplay.h"
#include "info.h"

using namespace std;

Gameplay::Gameplay(bool test) {
  std::vector<char> availablePlayers = {'G','B','D','P','S','$','L','T'};
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
    while (find(availablePlayers.begin(), availablePlayers.end(), playerChar) == availablePlayers.end())
    {
      cout << "Invalid avatar char, please choose from available!" << endl;
      cout << "Current available avatars: ";
      for (char name : availablePlayers) {
        cout  << " " << name;
      }
      cout << "Player #" << i << ", please enter your avator char:";
      cin >> playerChar;
    }

    availablePlayers.erase(find(availablePlayers.begin(), availablePlayers.end(), playerChar));
    players.push_back(new Player(defaultMoney, playerChar));
  }

  // buildings initialize
  b = new Board();
  curBuilding = b->getBuilding(0);
  curPlayer = players[0];
  isTest = test;
}


Gameplay::~Gameplay() {
  delete b;
  for (Player *p : players) delete p;
}


// search player by name
Player *Gameplay::findPlayer(char c) {
  for (Player *p : players) {
    if (p->getName() == c) return p;
  }
  return nullptr;
}


// search building by name
// only applicable to property buildings
Building *Gameplay::findBuilding(string name) {
  return b->findBuilding(name);
}


// switch to next player
void Gameplay::switchPlayer() {
  auto it = find(players.begin(), players.end(), curPlayer);
  int index = it - players.begin();
  if (index != players.size()+1) {
    index++;
  } else index = 0;
  curPlayer = players[index];
  curBuilding = b->getBuilding(curPlayer->getPos());
  curTuition = 0;
  isRolled = false;
}


// Player dropout;
void Gameplay::dropOut() {
  if (curPlayer->getTimCups() > 0) {
    totalRimCup -= curPlayer->getTimCups();
  }
  Player *p = curPlayer;
  switchPlayer();
  players.erase(find(players.begin(), players.end(), p));
}


// check if a player can declare bankruptcy
bool Gameplay::checkBankRuptcy() {
  if (curPlayer->getMoney() < curTuition) return true;
  else return false;
}


// random roll
void Gameplay::roll() {
  // row two dices
  int die1 = randomGen(1,6,seed);
  int die2 = randomGen(1,6,seed);
  cout << "You rolled out " << die1 << " " << die2 << endl;
  roll(die1,die2);
}

// main roll function, with two dice results as argument
void Gameplay::roll(int die1, int die2) {
  // check is player is stuck in timsline
  if (curPlayer->isInTim()) {
    if (!curPlayer->incTimTurn()) {
      roll(die1, die2);
    }
    isRolled = true;
    return;
  }

  // move and get curBuilding
  if (curPlayer->getPos() + die1 + die2 >= 40) {
    // player passed Collect OSAP
    curPlayer->addFund(200);
  }

  curPlayer->move(die1+die2);
  curBuilding = b->getBuilding(curPlayer->getPos());


  if (curBuilding->getBuildingType() != BuildingType::Nonproperty) {
    // if curBuilding is a property building
    if (curBuilding->getBuildingType() == BuildingType::Gyms) {curBuilding = static_cast<GymsBuilding *>(curBuilding);}
    else if (curBuilding->getBuildingType() == BuildingType::Academic) {curBuilding = static_cast<AcademicBuilding *>(curBuilding);}
    else {curBuilding = static_cast<ResidenceBuilding *>(curBuilding);}

    Player *owner = curBuilding->getOwner();

    if ( !owner ) {
      // if the building has no owner, curPlayer buys it or auction starts
      cout << bntostr(curBuilding->getBuildingName()) << " has no owner, do you want to buy it at a price of $" << curBuilding->getCost() << "?" << endl;
      cout << "Please enter yes or no: ";
      string yn;
      while (cin >> yn) {
        if (yn == "yes") {
          while(curPlayer->getMoney() < curBuilding->getCost()) {
            cout << "You don't have enough money! You only have " << curPlayer->getMoney() << endl;
            cout << "Would you like to trade/sell property/improvements? Please enter yes or no: ";
            string command;
            while (cin >> command) {
              if (yn == "yes") {
                parseAction();
                break;
              } else if (yn == "no") {
                auction(curBuilding);
                isRolled = true;
                return;
              }
            }
          }
          cout << "You bought " << bntostr(curBuilding->getBuildingName()) << " successfully!" << endl;
          curPlayer->buyProperty(curBuilding);
        
        } else if (yn == "no") {
          auction(curBuilding);
        } else {
          cout << "Invalid command! Please enter yes or no: " ;
        }
      }

    } else if ( curBuilding->getBuildingType() == BuildingType::Academic && curBuilding->getMonopolist() == curPlayer && curBuilding->getImprovement() < 5) {
      // if curPlayer own the academic building and monopoly available
      cout << "Improvement available at" << bntostr(curBuilding->getBuildingName()) << endl;

    } else if (owner != curPlayer) {
      // if building is not owned by curPlayer, curPlayer need to pay tuition

      if (curBuilding->getBuildingType() == BuildingType::Gyms) {
        static_cast<GymsBuilding*>(curBuilding)->enterLastRoll(die1+die2);
      } 
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

  } else if ( curBuilding->getBuildingType() == BuildingType::Nonproperty) {
    // if curBuilding is a Nonproperty building, curPlayer react based on specific rules
    int moveNum = curBuilding->movement();
    curTuition = curBuilding->tuition();
    switch(curBuilding->getBuildingName()) {
      case BuildingName::Tuition: {
        cout << "You need to pay $300 or 10%($" << curPlayer->getTotalWorth() / 10 << ") of your total wealth:" << endl;
        cout << "Please choose your way to pay (enter $300 or 10%): " << endl;
        string payMethod;
        while (cin >> payMethod) {
          if (payMethod == "$300" || payMethod == "300") {
            if (curPlayer->getMoney() < 300) {
              cout << "You don't have enough money!";
            } else {
              curPlayer->addFund(-300);
              break;
            }
          } else if (payMethod == "10%" || payMethod == "10") {
            curPlayer->addFund(-curPlayer->getTotalWorth() / 10);
            break;
          }
          cout << "Invalid pay method! Please choose your way to pay (enter $300 or 10%): " << endl;
        }
        break;
      }
      case BuildingName::SLC: {
        if (totalRimCup < 4) {
          int result = randomGen(1, 100, seed);
          if (result == 100) {
            curPlayer->gainCup();
            totalRimCup += 1;
            cout << "You get a Rim Cup!" << endl;
          }
        }
        moveNum = static_cast<NonPropertyBuilding *>(curBuilding)->movement(seed);
        if (moveNum == -4) {
          // move to DC Tims Line
          moveNum = 50 - curPlayer->getPos();
          moveNum %= 40;
        } else if (moveNum == 4) {
          // move to Collect OSAP
          moveNum = 40 - curPlayer->getPos();
        }
        if (moveNum != 0) roll(0, moveNum);
        break;
      }
      case BuildingName::NeedlesHall:
        if (totalRimCup < 4) {
          int result = randomGen(1,100,seed);
          if (result == 100) {
            curPlayer->gainCup();
            totalRimCup += 1;
            cout << "You get a Rim Cup!" << endl;
          }
        }
        curTuition = static_cast<NonPropertyBuilding *>(curBuilding)->tuition(seed);
        if (curTuition > 0) {
          cout << "You gain $" << curTuition << "." << endl;
          curPlayer->addFund(curTuition);
        } else {
          cout << "You lose $" << curTuition << "." << endl;\
          if (curPlayer->getMoney() + curTuition < 0) {
            curPlayer->addFund(-curPlayer->getMoney());
          }
          curPlayer->addFund(curTuition);
        }
        break;
      default:
        if (curTuition > 0) {
          cout << "You need to pay $" << curTuition << " to University of Waterloo." << endl;
          while(curPlayer->getMoney() < curTuition) {
            cout << "You don't have enough money! You only have " << curPlayer->getMoney() << endl;
            cout << "You need to raise money!";
            if (!parseAction()) return;
          }
          cout << "You paid tuition successfully." << endl;
          curPlayer->addFund(-curTuition);
        }
        if (curTuition < 0) {
          cout << "Congrats! You get $" << curTuition << "!" << endl;
          curPlayer->addFund(-curTuition);
        }

        if (moveNum != 0) {
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
        }
    }
  }
  curTuition = 0;
  isRolled = true;
}

// set game seed
void Gameplay::setseed(unsigned seed) {
  this->seed = seed;
}


// reads in action from std::cin
bool Gameplay::parseAction() {
  cout << "Player "<< curPlayer->getName() << ", please enter command:" << endl;
  string s;
  string action;
  getline(cin, s);
  stringstream ss{s};
  ss >> action;
  if (action == "roll") {
    if (isRolled) {
      cout << "You have rolled!" << endl;
    } else if (isTest) {
      int dice1, dice2;
      ss >> dice1 >> dice2;
      roll(dice1, dice2);
    } else {
      roll();
    }

  } else if (action == "next") {
    if (!isRolled) {
      cout << "You haven't rolled!" << endl;
    } if (curTuition > 0) {
      cout << "Please pay tuition first!" << endl;
    } else switchPlayer();

  } else if (action == "trade") {
    char pn;
    string give, receive;
    ss >> pn >> give >> receive;
    trade(pn, give, receive);
  
  } else if (action == "improve") {
    string bn, instruction;
    ss >> bn >> instruction;
    improve(bn, instruction);
  
  } else if (action == "mortgage") {
    string bn;
    ss >> bn;
    mortgage(bn);
  
  } else if (action == "unmortgage") {
    string bn;
    ss >> bn;
    unmortgage(bn);
  
  } else if (action == "all") {
    if (curTuition != 0) {
      cout << "You cannot use this command at this point, please pay tuition first!";
    } all();

  } else if (action == "assets") {
    if (curTuition != 0) {
      cout << "You cannot use this command at this point, please pay tuition first!";
    } else assets();

  } else if (action == "bankrupt") {
    if (checkBankRuptcy()) {
      cout << "Player " << curPlayer->getName() << " declare bankruptcy!" << endl;
      dropOut();
      return false;
    } else {
      cout << "You cannot declare bankruptcy!";
    }
    
  } else if (action == "help") {
    cout << "Available commend list:" << endl;

    if (!isRolled) {
      cout << "roll";
      if (isTest) cout << " (die1) (die2)";
      cout << endl;
    }

    if (isRolled && curTuition == 0) {
      cout << "next" << endl;
    }

    cout << "trade <name> <give> <receive>" << endl;
    cout << "improve <property> buy/sell" << endl;
    cout << "mortgage <property>" << endl;
    cout << "mortgage <property>" << endl;

    if (checkBankRuptcy()) {
      cout << "bankrupt" << endl;
    }

    if (curTuition == 0) {
      cout << "all" << endl;
      cout << "assets" << endl;
    }
    
  } else {
    cout << "Invalid command! Enter \"help\" to check valid commands." << endl;
  }
  return true;
}



// trade <name> <give> <recieve>
void Gameplay::trade(char pn, string give, string receive) {
  Player *tradePlayer = findPlayer(pn);
  if (tradePlayer == nullptr) {
    cout << pn << " is not a valid player name!" << endl;
    return;
  } else if (tradePlayer == curPlayer) {
    cout << "You cannot trade with yourself!" << endl;
    return;
  }

  if (isNumeric(give)) {
    if (isNumeric(receive)) {
      cout << "Both <give> and <receive> are money, you can't trade money for money!" << endl;
      return;
    }
    int giveMoney = stoi(give);
    if (giveMoney < curPlayer->getMoney()) {
      cout << "You don't have enough money to give!" << endl;
      return;
    }

    Building *receiveBuilding = b->findBuilding(receive);
    if (receiveBuilding == nullptr) {
      cout << receive << " is not a valid building name!" << endl;
      return;
    }
    if (receiveBuilding->getOwner() != tradePlayer) {
      cout << bntostr(receiveBuilding->getBuildingName()) << " is not owned by " << tradePlayer->getName() << "!" << endl;
      return;
    }
    
    cout << "Player " << tradePlayer->getName() << ", please accept or reject the trade: ";
    string command;
    while (cin >> command) {
      if (command == "accept") {
        cout << "Trade accepted!" << endl;
        curPlayer->addProperty(receiveBuilding);
        curPlayer->addFund(-giveMoney);
        tradePlayer->removeProperty(receiveBuilding);
        tradePlayer->addFund(giveMoney);
        receiveBuilding->setOwner(curPlayer);
        break;
      } else if (command == "reject") {
        cout << "Trade rejected!" << endl;
        break;
      } else {
        cout << "Invalid command. Please enter accept or reject: ";
      }
    }
  } else {
    Building *giveBuilding = b->findBuilding(give);
    if (giveBuilding == nullptr) {
      cout << give << " is not a valid building name!" << endl;
      return;
    }
    if (giveBuilding->getOwner() != curPlayer) {
      cout << bntostr(giveBuilding->getBuildingName()) << " is not owned by " << curPlayer->getName() << "!" << endl;
      return;
    }

    if (isNumeric(receive)) {
      int receiveMoney = stoi(receive);
      if (receiveMoney < tradePlayer->getMoney()) {
        cout << tradePlayer->getName() << " don't have enough money!" << endl;
        return;
      }
      cout << "Player " << tradePlayer->getName() << ", please accept or reject the trade: ";
      string command;
      while (cin >> command) {
        if (command == "accept") {
          cout << "Trade accepted!" << endl;
          curPlayer->removeProperty(giveBuilding);
          curPlayer->addFund(receiveMoney);
          tradePlayer->addProperty(giveBuilding);
          tradePlayer->addFund(receiveMoney);
          giveBuilding->setOwner(tradePlayer);
          break;
        } else if (command == "reject") {
          cout << "Trade rejected!" << endl;
          break;
        } else {
          cout << "Invalid command. Please enter accept or reject: ";
        }
      }
    } else {
      Building *receiveBuilding = b->findBuilding(receive);
      if (receiveBuilding == nullptr) {
        cout << receive << " is not a valid building name!" << endl;
        return;
      }
      if (receiveBuilding->getOwner() != tradePlayer) {
        cout << bntostr(receiveBuilding->getBuildingName()) << " is not owned by " << tradePlayer->getName() << "!" << endl;
        return;
      }
      cout << "Player " << tradePlayer->getName() << ", please accept or reject the trade: ";
      string command;
      while (cin >> command) {
        if (command == "accept") {
          cout << "Trade accepted!" << endl;
          curPlayer->addProperty(receiveBuilding);
          curPlayer->removeProperty(giveBuilding);
          tradePlayer->removeProperty(receiveBuilding);
          tradePlayer->addProperty(giveBuilding);
          receiveBuilding->setOwner(curPlayer);
          giveBuilding->setOwner(tradePlayer);
          break;
        } else if (command == "reject") {
          cout << "Trade rejected!" << endl;
          break;
        } else {
          cout << "Invalid command. Please enter accept or reject: ";
        }
      }
    }
  }
}



// Auction program
void Gameplay::auction(Building* bs) {
  cout << "Auction of building " << bntostr(bs->getBuildingName()) << " starts!" << endl;
  int curBid = bs->getCost()-1; // base bid
  int playersCount = players.size();
  std::vector<bool> auctionStatus(playersCount);
  for (int i = 0; i < playersCount; i++) {
    auctionStatus[i] = true;
  }
  Player *p = curPlayer;
  int index = find(players.begin(), players.end(), p) - players.begin();
  
  for (int i = index; ; i++) {
    if (i = players.size()) i = 0;
    if (!auctionStatus[i]) continue;

    if (playersCount = 1 && curBid != bs->getCost()-1) {
      cout << "Congradulations! Player " << p->getName() << " buys building " << bntostr(bs->getBuildingName()) << " at price of $" << curBid << endl;
      p->addProperty(bs);
      p->addFund(-curBid);
      bs->setOwner(p);
      return;
    } else if (playersCount = 0 && curBid == bs->getCost()-1) {
      cout << "No player offers a bid, auction aborts." << endl;
      return;
    } else {
      cout << "Player " << players[i]->getName() << ", please withdraw(W) or enter your bid(at least $" << curBid+1 << ") :" ;
      string command;
      while (cin >> command) {
        if (command == "W" || command == "withdrawn") {
          auctionStatus[i] = false;
          playersCount -= 1;
          break;
        } else if (isNumeric(command)) {
          int bid = stoi(command);
          if (bid > players[i]->getMoney()) {
            cout << "You don't have enough money!" << endl;
          } else if (curBid > bid) {
            cout << "Your bid is less than current highiest bid!" << endl;
          } else {
            curBid = bid;
            p = players[i];
            cout << "Player " << players[i]->getName() << " raised bid to $" << curBid << endl;
            break;
          }
        }
        cout << "Player " << players[i]->getName() << ", please withdraw(W) or enter your bid(at least $" << curBid+1 << "): ";
      }
    }
  }
}



// improve <property> buy/sell
void Gameplay::improve(string bn, string instruction) {
  Building *bs = b->findBuilding(bn);
  if (bs == nullptr) {
    cout << bn << " is not a name of a property building!" << endl;
  } else if (bs->getBuildingType() != BuildingType::Academic) {
    cout << bn << " is not an academic building!" << endl;
  } else if (instruction == "buy") {
    curPlayer->buyImprovement(bs);
  } else if (instruction == "sell") {
    curPlayer->sellImprovement(bs);
  } else {
    cout << "Invalid command, please enter buy/sell for instruction!" << endl;
  }
}


// mortgage building
void Gameplay::mortgage(string bn) {
  Building *bs = b->findBuilding(bn);
  if (bs == nullptr) {
    cout << bn << " is not a name of a property building!" << endl;

  } else if (bs->getBuildingType() != BuildingType::Academic) {
    cout << bn << " is not an academic building!" << endl;

  } else {
    curPlayer->mortgage(bs);
  }
}



// unmortgage building
void Gameplay::unmortgage(string bn) {
  Building *bs = b->findBuilding(bn);
  if (bs == nullptr) {
    cout << bn << " is not a name of a property building!" << endl;

  } else if (bs->getBuildingType() != BuildingType::Academic) {
    cout << bn << " is not an academic building!" << endl;

  } else {
    curPlayer->unmortgage(bs);
  }
}


// show assets of curPlayer
void Gameplay::assets() {
  curPlayer->printAsset();
}


// show assets of all Players
void Gameplay::all() {
  for (int i = 0; i < players.size(); i++) {
    players[i]->printAsset();
  }

}



void Gameplay::play() {
  while (true) {
    if (!parseAction() && players.size() == 1) break;
  }
}



void Gameplay::saveGame(string save_name){
  ofstream saving;
  saving.open(save_name + ".txt");
  saving << players.size() << endl;
  for (Player * p : players) {
    saving << "Player " << p->getName() << " " << p->getTimCups() << " " << p->getTotalWorth() << " " << p->getPos();
    if (p->getPos() == 10 && p->isInTim()) {
      cout << " "  << 1 << " " << p->getTimTurn() << endl;
    } else if (p->getPos() == 10) {
      cout << " 0" << endl;
    } else {
      cout << endl;
    }
  }
  for (int i = 0; i < 40; i++) {
    Building *bs = b->getBuilding(i);
    if (bs->getBuildingType() == BuildingType::Nonproperty) continue;
    saving << bntostr(bs->getBuildingName()) << " ";
    if (bs->getOwner() == nullptr) saving << "BANK ";
    else saving << bs->getOwner()->getName() << " ";
    if (bs->getBuildingType() == BuildingType::Gyms || bs->getBuildingType() == BuildingType::Residence ) {
      saving << 0 << endl;
    }
    else {
      if (bs->getMortgage()) {
        saving << -1 << endl;
      } else {
        saving << bs->getImprovement() << endl;
      }
    }
  }

}



void Gameplay::loadGame(string file) {

}



ostream &operator<<(ostream& out, Gameplay* gp) {
  out << gp;
  return out;
}


