#include "gameplay.h"
#include "info.h"

using namespace std;

Gameplay::Gameplay(bool test) {
  std::vector<char> availablePlayers = {'G','B','D','P','S','$','L','T'};
  const int defaultMoney = 1500;
  int playerCount;
  char playerChar;
  cout << "Please enter the number of players(at lease 2, at most 8): ";
  cin >> playerCount;
  while (playerCount < 2 || playerCount > 8) {
    cout << "Invalid number of players." << endl;
    cout << "Please enter the number of players(at lease 2, at most 8): ";
    cin >> playerCount;
  }

  // display a list of avatas for choosing
  cout << "Please choose your avatar from the following:" << endl;
  cout << "| Goose | GRT bus | Tim Hortons Doughnut | Professor | Student | Money | Laptop | Pink tie |" << endl;
  cout << "|   G   |    B    |           D          |     P     |    S    |   $   |   L    |    T     |" << endl;

  // every player enter their avatar
  for (int i = 0; i < playerCount; ++i) {
    cout << "Current available avatars:";
    for (char name : availablePlayers) {
      cout  << " " << name;
    }
    cout << endl;
    cout << "Player #" << i+1 << ", please enter your avatar char: ";
    cin >> playerChar;
    while (find(availablePlayers.begin(), availablePlayers.end(), playerChar) == availablePlayers.end())
    {
      cout << "Invalid avatar char, please choose from available!" << endl;
      cout << "Current available avatars:";
      for (char name : availablePlayers) {
        cout  << " " << name;
      }
      cout << endl;
      cout << "Player #" << i << ", please enter your avatar char: ";
      cin >> playerChar;
    }

    availablePlayers.erase(find(availablePlayers.begin(), availablePlayers.end(), playerChar));
    players.push_back(new Player(defaultMoney, playerChar));
  }

  // buildings initialize
  b = new Board("square.in");
  b->init(players);
  curBuilding = b->getBuilding(0);
  curPlayer = players[0];
  isTest = test;
  cout << b;
}

Gameplay::Gameplay(bool test, bool isLoad ,string load) {
  if (isLoad) {
    loadGame(load);
    cout << "Finish loading" <<endl;
    b = new Board("square.in");
    b->init(players);
    curBuilding = b->getBuilding(curPlayer->getPos());
    isTest = test;
    cout << b;
  } else {
    std::vector<char> availablePlayers = {'G','B','D','P','S','$','L','T'};
    const int defaultMoney = 1500;
    int playerCount;
    char playerChar;
    cout << "Please enter the number of players(at lease 2, at most 8): ";
    cin >> playerCount;
    while (playerCount < 2 || playerCount > 8) {
      cout << "Invalid number of players." << endl;
      cout << "Please enter the number of players(at lease 2, at most 8): ";
      cin >> playerCount;
    }

    // display a list of avatars for choosing
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
      cout << "Player #" << i+1 << ", please enter your avatar char: ";
      cin >> playerChar;
      while (find(availablePlayers.begin(), availablePlayers.end(), playerChar) == availablePlayers.end())
      {
        cout << "Invalid avatar char, please choose from available!" << endl;
        cout << "Current available avatars:";
        for (char name : availablePlayers) {
          cout  << " " << name;
        }
        cout << endl;
        cout << "Player #" << i << ", please enter your avatar char: ";
        cin >> playerChar;
      }

      availablePlayers.erase(find(availablePlayers.begin(), availablePlayers.end(), playerChar));
      players.push_back(new Player(defaultMoney, playerChar));
    }

    // buildings initialize
    b = new Board(load);
    b->init(players);
    curBuilding = b->getBuilding(0);
    curPlayer = players[0];
    isTest = test;
    cout << b;
  }
}

Gameplay::Gameplay(bool test, string load, string theme) {
  loadGame(load);
  
  b = new Board(theme);
  b->init(players);
  curBuilding = b->getBuilding(curPlayer->getPos());
  isTest = test;
  cout << b;
}


Gameplay::~Gameplay() {
  delete b;
  players.clear();
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
  // test
  // cout << index << " is index of curPlayer out of " << players.size() << " players"<< endl;
  //
  index++;
  if (index == players.size()) index = 0;
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
  delete p;
}


// check if a player can declare bankruptcy
bool Gameplay::checkBankRuptcy() {
  if (curPlayer->getMoney() < curTuition) return true;
  else return false;
}


// random roll
void Gameplay::roll() {
  // row two dices
  int die1 = randomGen(1,6);
  int die2 = randomGen(1,6);
  cout << "You rolled out " << die1 << " " << die2 << endl;
  roll(die1,die2);
}

// main roll function, with two dice results as argument
void Gameplay::roll(int die1, int die2) {
  // check is player is stuck in timsline
  if (curPlayer->isInTim()) {
    cout << "You are stucked in tims line!" << endl;
    if (die1 == die2) {
      cout << "You leave DC tims line because you rolled out two same number!" << endl;
      curPlayer->OutfromTimsLine();
      roll(die1, die2);
    } else if (!curPlayer->incTimTurn()) {
      curPlayer->OutfromTimsLine();
      roll(die1, die2);
    }
    isRolled = true;
    return;
  }

  // move and get curBuilding
  if (curPlayer->getPos() + die1 + die2 >= 40 && !curPlayer->isInTim()) {
    cout << "You passed Collect OSAP, you gain $200!" << endl;
    curPlayer->addFund(200);
  }

  stringstream ss;
  ss << "You moved from " << bntostr(b->getBuilding(curPlayer->getPos())->getBuildingName()) << " to ";
  curPlayer->move(die1+die2);
  ss << bntostr(b->getBuilding(curPlayer->getPos())->getBuildingName()) << endl;
  cout << b;
  string s = ss.str();
  cout << s;
  curBuilding = b->getBuilding(curPlayer->getPos());


  if (curBuilding->getBuildingType() != BuildingType::Nonproperty) {
    // if curBuilding is a property building
    Property *curProperty = static_cast<Property *>(curBuilding);

    Player *owner = curProperty->getOwner();

    if ( !owner ) {
      // if the building has no owner, curPlayer buys it or auction starts
      cout << bntostr(curProperty->getBuildingName()) << " has no owner, do you want to buy it at a price of $" << curProperty->getCost() << "?" << endl;
      cout << "Please enter yes or no: ";
      string yn;
      while (cin >> yn) {
        if (yn == "yes") {
          while(curPlayer->getMoney() < curProperty->getCost()) {
            cout << "You don't have enough money! You only have $" << curPlayer->getMoney() << endl;
            cout << "Would you like to trade/sell property/improvements? Please enter yes or no: ";
            string command;
            while (cin >> command) {
              if (command == "yes") {
                parseAction();
                break;
              } else if (command == "no") {
                auction(curProperty);
                isRolled = true;
                return;
              } else {
                cout << "Invalid command! Would you like to trade/sell property/improvements? Please enter yes or no: ";
              }
            }
          }
          cout << "You bought " << bntostr(curProperty->getBuildingName()) << " successfully!" << endl;
          curPlayer->buyProperty(static_cast<Property *>(curBuilding));
          cout << b;
          break;
        } else if (yn == "no") {
          auction(curProperty);
          break;
        } else {
          cout << "Invalid command! Please enter yes or no: " ;
        }
      }

    } else if ( curBuilding->getBuildingType() == BuildingType::Academic && static_cast<AcademicBuilding*>(curBuilding)->getMonopolist() == curPlayer && static_cast<AcademicBuilding*>(curBuilding)->getImprovement() < 5) {
      // if curPlayer own the academic building and monopoly available
      cout << "Improvement available at" << bntostr(static_cast<AcademicBuilding*>(curBuilding)->getBuildingName()) << endl;

    } else if (owner != curPlayer) {
      // if building is not owned by curPlayer, curPlayer need to pay tuition

      if (curBuilding->getBuildingType() == BuildingType::Gyms) {
        static_cast<GymsBuilding*>(curBuilding)->enterLastRoll(die1+die2);
      } 
      curTuition = static_cast<Property *>(curBuilding)->tuition();
      cout << "You need to pay $" << curTuition << " tuition to " << owner->getName() << endl;
      while(curPlayer->getMoney() < curTuition) {
        cout << "You don't have enough money! You only have $" << curPlayer->getMoney() << endl;
        cout << "You need to raise money!";
        if (!parseAction()) return;
      }
      cout << "You paid tuition successfully." << endl;
      curPlayer->addFund(-curTuition);
      owner->addFund(curTuition);
    }

  } else if ( curBuilding->getBuildingType() == BuildingType::Nonproperty) {
    // if curBuilding is a Nonproperty building, curPlayer react based on specific rules
    int moveNum = static_cast<NonPropertyBuilding *>(curBuilding)->movement();
    curTuition = static_cast<NonPropertyBuilding *>(curBuilding)->tuition();
    switch(curBuilding->getBuildingName()) {
      case BuildingName::Tuition: {
        cout << "You need to pay $300 or 10%($" << curPlayer->getTotalWorth() / 10 << ") of your total wealth:" << endl;
        cout << "Please choose your way to pay (enter $300 or 10%): " << endl;
        string payMethod;
        while (cin >> payMethod) {
          if (payMethod == "$300" || payMethod == "300") {
            curTuition = 300;
            break;
          } else if (payMethod == "10%" || payMethod == "10") {
            curTuition = curPlayer->getTotalWorth() / 10;
            break;
          }
          cout << "Invalid pay method! Please choose your way to pay (enter $300 or 10%): " << endl;
        }
        cout << "You need to pay $" << curTuition << " to University of Waterloo." << endl;
        while(curPlayer->getMoney() < curTuition) {
          cout << "You don't have enough money! You only have $" << curPlayer->getMoney() << endl;
          cout << "You need to raise money!";
          if (!parseAction()) return;
        }
        cout << "You paid tuition successfully." << endl;
        curPlayer->addFund(-curTuition);
        break;
      }
      case BuildingName::SLC: {
        if (totalRimCup < 4) {
          int result = randomGen(1, 100);
          if (result == 100) {
            curPlayer->gainCup();
            totalRimCup += 1;
            cout << "You get a Rim Cup!" << endl;
          } else cout << "You didn't win a Rim Cup" << endl;
        }
        if (moveNum == -4) {
          // move to DC Tims Line
          moveNum = 50 - curPlayer->getPos();
          moveNum %= 40;
          curPlayer->MovetoTimsLine();
          cout << b;
        } else if (moveNum == 4) {
          // move to Collect OSAP
          moveNum = 40 - curPlayer->getPos();
        }
        if (moveNum != 0) roll(0, moveNum);
        break;
      }
      case BuildingName::NeedlesHall:
        if (totalRimCup < 4) {
          int result = randomGen(1,100);
          if (result == 100) {
            curPlayer->gainCup();
            totalRimCup += 1;
            cout << "You get a Rim Cup!" << endl;
          }
        }
        if (curTuition < 0) {
          curPlayer->addFund(-curTuition);
        } else if (curTuition > 0) {
          if (curPlayer->getMoney() < curTuition) {
            curPlayer->addFund(-curPlayer->getMoney());
          }
          curPlayer->addFund(-curTuition);
        }
        break;
      default:
        if (curTuition > 0) {
          cout << "You need to pay $" << curTuition << " to University of Waterloo." << endl;
          while(curPlayer->getMoney() < curTuition) {
            cout << "You don't have enough money! You only have $" << curPlayer->getMoney() << endl;
            cout << "You need to raise money!";
            if (!parseAction()) return;
          }
          cout << "You paid tuition successfully." << endl;
          curPlayer->addFund(-curTuition);
        }
        if (curTuition < 0) {
          curPlayer->addFund(-curTuition);
        }

        if (moveNum != 0) {
          if (moveNum == -4) {
            // move to DC Tims Line
            moveNum = 50 - curPlayer->getPos();
            moveNum %= 40;
            curPlayer->MovetoTimsLine();
            cout << b;
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


// reads in action from std::cin
bool Gameplay::parseAction() {
  cout << endl;
  cout << "Player "<< curPlayer->getName() << ", please enter command:" << endl;
  string action;
  cin >> action;
  if (action == "roll") {
    string s;
    getline(cin, s);
    stringstream ss{s};
    if (isRolled) {
      cout << "You have rolled!" << endl;
    } else if (isTest) {
      int die1, die2;
      if (ss.eof()) roll();
      else {
        ss >> die1;
        if (ss.eof()) roll();
        else {
          ss >> die2;
          roll(die1, die2);
        }
      }
    } else {
      roll();
    }

  } else if (action == "next") {
    if (!isRolled) {
      cout << "You haven't rolled!" << endl;
    } else if (curTuition > 0) {
      cout << "Please pay tuition first!" << endl;
    } else switchPlayer();

  } else if (action == "trade") {
    char pn;
    string give, receive;
    cin >> pn >> give >> receive;
    trade(pn, give, receive);
  
  } else if (action == "improve") {
    string bn, instruction;
    cin >> bn >> instruction;
    improve(bn, instruction);
  
  } else if (action == "mortgage") {
    string bn;
    cin >> bn;
    mortgage(bn);
  
  } else if (action == "unmortgage") {
    string bn;
    cin >> bn;
    unmortgage(bn);
  
  } else if (action == "all") {
    all();

  } else if (action == "assets") {
    assets();

  } else if (action == "bankrupt") {
    if (checkBankRuptcy()) {
      cout << "Player " << curPlayer->getName() << " declare bankruptcy!" << endl;
      dropOut();
      return false;
    } else {
      cout << "You cannot declare bankruptcy!" << endl;
    }
    
  } else if (action == "save") {
    string save_name;
    cin >> save_name;
    saveGame(save_name);
      
  } else if (action == "quit") {
    running = false;

  } else if (action == "help") {
    cout << "Available command list:" << endl;

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

    cout << "all" << endl;
    cout << "assets" << endl;

    
    cout << "save <filename>" <<endl;
    
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
    if (giveMoney > curPlayer->getMoney()) {
      cout << "You don't have enough money to give!" << endl;
      return;
    }

    Building *receiveBuilding = b->findBuilding(receive);
    if (receiveBuilding == nullptr) {
      cout << receive << " is not a valid building name!" << endl;
      return;
    }
    if (receiveBuilding->getBuildingType() == BuildingType::Nonproperty) {
      cout << "It isn't a property!" << endl;
      return;
    }
    Property *receiveProp = static_cast<Property *>(receiveBuilding);

    if (receiveProp->getOwner() != tradePlayer) {
      cout << bntostr(receiveProp->getBuildingName()) << " is not owned by " << tradePlayer->getName() << "!" << endl;
      return;
    }
    
    if (receiveProp->getBuildingType() == BuildingType::Academic) {
      AcademicBuilding *receiveAB = static_cast<AcademicBuilding*>(receiveProp);
      if (receiveAB->getMonopolyImprovement() > 0) {
        cout << bntostr(receiveAB->getBuildingName()) << "can't be traded! " << endl;
        cout << tradePlayer->getName() << " need to sell all improvement in that monopoly block first!" << endl;
        return;
      }
    }

    cout << "Player " << tradePlayer->getName() << ", please accept or reject the trade: ";
    string command;
    while (cin >> command) {
      if (command == "accept") {
        cout << "Trade accepted!" << endl;
        curPlayer->addProperty(receiveProp);
        curPlayer->addFund(-giveMoney);
        tradePlayer->removeProperty(receiveProp);
        tradePlayer->addFund(giveMoney);
        receiveProp->setOwner(curPlayer);
        cout << b;
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
    if (giveBuilding->getBuildingType() == BuildingType::Nonproperty) {
      cout << "It's not a property!" << endl;
      return;
    }
    Property *giveProp = static_cast<Property *>(giveBuilding);
    if (giveProp->getOwner() != curPlayer) {
      cout << bntostr(giveProp->getBuildingName()) << " is not owned by " << curPlayer->getName() << "!" << endl;
      return;
    }

    if (giveProp->getBuildingType() == BuildingType::Academic) {
      AcademicBuilding *giveAB = static_cast<AcademicBuilding*>(giveProp);
      if (giveAB->getMonopolyImprovement() > 0) {
        cout << bntostr(giveAB->getBuildingName()) << "can't be traded! " << endl;
        cout << "You need to sell all improvement in that monopoly block first!" << endl;
        return;
      }
    }

    if (isNumeric(receive)) {
      int receiveMoney = stoi(receive);
      if (receiveMoney > tradePlayer->getMoney()) {
        cout << tradePlayer->getName() << " don't have enough money!" << endl;
        return;
      }
      cout << "Player " << tradePlayer->getName() << ", please accept or reject the trade: ";
      string command;
      while (cin >> command) {
        if (command == "accept") {
          cout << "Trade accepted!" << endl;
          curPlayer->removeProperty(giveProp);
          curPlayer->addFund(receiveMoney);
          tradePlayer->addProperty(giveProp);
          tradePlayer->addFund(-receiveMoney);
          giveProp->setOwner(tradePlayer);
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
      if (receiveBuilding->getBuildingType() == BuildingType::Nonproperty) {
        cout << "It isn't a property!" << endl;
        return;
      }
      Property *receiveProp = static_cast<Property *>(receiveBuilding);
      if (receiveProp->getOwner() != tradePlayer) {
        cout << bntostr(receiveProp->getBuildingName()) << " is not owned by " << tradePlayer->getName() << "!" << endl;
        return;
      }
      if (receiveProp->getBuildingType() == BuildingType::Academic) {
        AcademicBuilding *receiveAB = static_cast<AcademicBuilding*>(receiveProp);
        if (receiveAB->getMonopolyImprovement() > 0) {
          cout << bntostr(receiveAB->getBuildingName()) << "can't be traded! " << endl;
          cout << tradePlayer->getName() << " need to sell all improvement in that monopoly block first!" << endl;
          return;
        }
    }
      cout << "Player " << tradePlayer->getName() << ", please accept or reject the trade: ";
      string command;
      while (cin >> command) {
        if (command == "accept") {
          cout << "Trade accepted!" << endl;
          curPlayer->addProperty(receiveProp);
          curPlayer->removeProperty(giveProp);
          tradePlayer->removeProperty(receiveProp);
          tradePlayer->addProperty(giveProp);
          receiveProp->setOwner(curPlayer);
          giveProp->setOwner(tradePlayer);
          cout << b;
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
  Property *prop = static_cast<Property *>(bs);
  cout << "Auction of building " << bntostr(bs->getBuildingName()) << " starts!" << endl;
  int curBid = prop->getCost()-1; // base bid
  int playersCount = players.size();
  vector<bool> auctionStatus(playersCount);
  for (int i = 0; i < playersCount; i++) {
    auctionStatus[i] = true;
  }
  Player *p = curPlayer;
  int index = find(players.begin(), players.end(), p) - players.begin();
  
  for (int i = index; ; i++) {
    if (i == players.size()) i = 0;

    if (playersCount == 0 && curBid == prop->getCost()-1) {
      cout << "No player offers a bid, auction aborts." << endl;
      return;
    }

    if (!auctionStatus[i]) continue;

    if (playersCount == 1 && curBid != prop->getCost()-1) {
      cout << "Congradulations! Player " << p->getName() << " buys building " << bntostr(bs->getBuildingName()) << " at price of $" << curBid << endl;
      p->addProperty(prop);
      p->addFund(-curBid);
      prop->setOwner(p);
      cout << b;
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
          } else if (curBid >= bid) {
            cout << "Your bid is less than or equal to current highest bid!" << endl;
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
    curPlayer->buyImprovement(static_cast<Property *>(bs));
    cout << b;
  } else if (instruction == "sell") {
    curPlayer->sellImprovement(static_cast<Property *>(bs));
    cout << b;
  } else {
    cout << "Invalid command, please enter buy/sell for instruction!" << endl;
  }
}


// mortgage building
void Gameplay::mortgage(string bn) {
  Building *bs = b->findBuilding(bn);
  if (bs == nullptr) {
    cout << bn << " is not a name of a property building!" << endl;

  } else if (bs->getBuildingType() == BuildingType::Nonproperty) {
    cout << bn << " is not an property building!" << endl;
  } else {
    curPlayer->mortgage(static_cast<Property *>(bs));
  }
}



// unmortgage building
void Gameplay::unmortgage(string bn) {
  Building *bs = b->findBuilding(bn);
  if (bs == nullptr) {
    cout << bn << " is not a name of a property building!" << endl;

  } else if (bs->getBuildingType() == BuildingType::Nonproperty) {
    cout << bn << " is not an property building!" << endl;

  } else {
    curPlayer->unmortgage(static_cast<Property *>(bs));
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
    if (players.size() == 1) {
      cout << curPlayer->getName() << " is the winner of the game!" << endl;
      break;
    }
    else if (running == false) break;
    else parseAction();
  }
  
}



void Gameplay::saveGame(string save_name){
  ofstream saving;
  saving.open(save_name + ".txt");
  saving << players.size() << endl;
  for (Player * p : players) {
    saving << "Player " << p->getName() << " " << p->getTimCups() << " " << p->getMoney() << " " << p->getPos();
    if (p->getPos() == 10 && p->isInTim()) {
      saving << " "  << 1 << " " << p->getTimTurn() << endl;
    } else if (p->getPos() == 10) {
      saving << " 0" << endl;
    } else {
      saving << endl;
    }
  }
  saving << curPlayer->getName() << " ";
  if (isRolled) {
  saving << "yes";
  } else saving << "no";
  saving << endl;
  for (int i = 0; i < 40; i++) {
    Building *bs = b->getBuilding(i);
    if (bs->getBuildingType() == BuildingType::Nonproperty) continue;
    Property *prop = static_cast<Property *>(bs);
    saving << bntostr(prop->getBuildingName()) << " ";
    if (prop->getOwner() == nullptr) saving << "BANK ";
    else saving << prop->getOwner()->getName() << " ";
    if (prop->getMortgage()) {
      saving << -1 << endl;
    }
    else if (prop->getBuildingType() == BuildingType::Gyms || prop->getBuildingType() == BuildingType::Residence ) {
      saving << 0 << endl;
    }
    else {
        saving << static_cast<AcademicBuilding *>(bs)->getImprovement() << endl;
    }
  }
}

void Gameplay::loadGame(string file) {
  ifstream myfile(file);
  int cnt;
  if (myfile.is_open()) {
    myfile >> cnt;
    // initialize player
    for (int i = 0; i < cnt; ++i) {
      string pl;
      char c;
      int cups, money, position, dc, round;
      myfile >> pl >> c >> cups >> money >> position;
      Player *p = new Player(money, c);
      p->setPos(position);
      p->setCup(cups);
      this->totalRimCup += cups;
      if (position == 10) {
        myfile >> dc;
        if (dc == 1) {
          myfile >> round;
          p->setTimTurn(round);
        }
      }
      players.emplace_back(p);
    }
    char curPlayerName;
    string isRolledSave;
    myfile >> curPlayerName >> isRolledSave;
    
    curPlayer = findPlayer(curPlayerName);
    if (isRolledSave == string("yes")) {
      isRolled = true;
    } else if (isRolledSave == string("no")) {
      isRolled = false;
    }
    string bn;
    char own;
    int imp;
    Property *build;
    while (myfile >> bn >> own >> imp) {
       build = static_cast<Property *>(b->findBuilding(bn));
      for (Player *p : players) {
        if (p->getName() == own) build->setOwner(p);
      }
    }
    if (imp  > 0) {
      static_cast<AcademicBuilding *>(build)->setImprovement(imp);
    } else if (imp == -1) {
      build->setMortgage();
    }
  }
  
  myfile.close();
}


