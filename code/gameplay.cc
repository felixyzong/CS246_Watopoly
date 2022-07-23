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
  b = new Board();
  curBuilding = b->getBuilding(0);
  curPlayer = players[0];
  isTest = test;

}


Gameplay::~Gameplay() {
  delete b;
  for (auto it = players.begin(); it != players.end(); ++it) delete it;
}


// search player by name
Player *Gameplay::findPlayer(char c) {
  for (auto it = players.begin(); it != players.end(); ++it) {
    if (*it->getName() == c) return it;
  }
  return nullptr;
}


// search building by name
// only applicable to property buildings
Building *Gameplay::findBuilding(string name) {
  BuildingName bn = strtobn(name);
  for (auto it = buildings.begin(); it != buildings.end(); ++it) {
    if (*it->getBuildingName() == bn) return it;
  }
  return nullptr;
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
  curPlayer->rolled = false;
}


// Player dropout;
void Gameplay::dropOut() {
  if (curPlayer->cup > 0) totalRimCup -= curPlayer->cup;
  Player *p = curPlayer;
  switchPlayer();
  players.erase(p);
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
  roll(die1,die2);
}

// main roll function, with two dice results as argument
void Gameplay::roll(int die1, int die2) {
  
  // check is player is stuck in timsline
  if (curPlayer->isInTim()) {
    if (die1 == die2) {
      curPlayer->isInTimLine = false;
      roll(die1,die2);
    } else {
      curPlayer->incTimTurn();
      return
    }
  }

  // move and get curBuilding
  if (curPlayer->getPos() + die1 + die2 >= 40) {
    // player passed Collect OSAP
    curPlayer->addFund(200);
  }
  curPlayer->Move(die1+die2);
  Building * curBuilding = buildings[curPlayer->getPos()];


  if (curBuilding->getBuildingType() != BuildingType::Nonproperty) {
    // if its not a Nonproperty building
    Player *owner = curBuilding.getOwner();

    if ( owner == nullptr ) {
      // if the building has no owner, curPlayer buys it or auction starts
      cout << bntostr(curBuilding->GetBuildingName()) << " has no owner, do you want to buy it at a price of $" << curBuilding->getCost() << "?" << endl;
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
        cout << "You bought " << bntostr(curBuilding->GetBuildingName()) << " successfully!" << endl;
        curPlayer->buyProperty(curBuilding);
      
      } else if (yn == "no") {
        auction(curBuilding);
      }

    } else if ( owner == curPlayer && curBuilding->getBuidlingType() == BuildingType::Academic 
    && curBuilding->getMonopoly == curPlayer && curBuilding->improvement < 5) {
      // if curPlayer own the academic building and monopoly available
      cout << "Improvement available at" << bntostr(curBuilding->GetBuildingName()) << cout;

    } else if (owner != curPlayer) {
      // if building is not owned by curPlayer, curPlayer need to pay tuition
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
    // if curBuidling is a Nonproperty building, curPlayer react based on specific rules
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
        cout << "You need to pay $300 or 10%($" << curPlayer->getTotalWorth()/10 << ") of your total wealth:" << endl;
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
          int result = randomGen(1,100,seed);
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
          int result = randomGen(1,100,seed);
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
  curTuition = 0;
  curPlayer->rolled = true;
}

// set game seed
void setseed(seed) {
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
    if (curPlayer->isRolled()) {
      cout << "You have rolled!" << endl;
    } else if (isTest) {
      int dice1, dice2;
      ss >> dice1 >> dice2;
      roll(dice1, dice2);
    } else {
      roll();
    }

  } else if (action == "next") {
    if (!curPlayer->isRolled()) {
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
      cout << "You cannot declare bankruptcy!"
    }
    
  } else if (action == "help") {
    cout << "Available commend list:" << endl;

    if (!curPlayer->isRolled()) {
      cout << "roll";
      if (isTest) cout << " (die1) (die2)";
      cout << endl;
    }

    if (curPlayer->isRolled() && curTuition == 0) {
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
    if (give < curPlayer->money) {
      cout << "You don't have enough money to give!" << endl;
      return;
    }

    Building *receiveBuidling = b->findBuilding(receive);
    if (receiveBuidling == nullptr) {
      cout << receive << " is not a valid building name!" << endl;
      return;
    }
    if (receiveBuidling->getOwner() != tradePlayer) {
      cout << bntostr(receiveBuidling->GetBuildingName()) << " is not owned by " << tradePlayer->getName() << "!" << endl;
      return;
    }
    
    cout << "Player " << tradePlayer->getName() << ", please accept or reject the trade: ";
    string command;
    while (cin >> command) {
      if (command == "accept") {
        cout << "Trade accepted!" << endl;
        curPlayer->addProperty(receiveBuidling);
        curPlayer->addFund(-giveMoney);
        tradePlayer->property.erase(receiveBuidling);
        tradePlayer->addFund(giveMoney);
        receiveBuidling->owner = curPlayer;
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
      cout << bntostr(giveBuilding->GetBuildingName()) << " is not owned by " << curPlayer->getName() << "!" << endl;
      return;
    }

    if (isNumeric(receive)) {
      int receiveMoney = stoi(receive);
      if (receive < tradePlayer->money) {
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
          giveBuidling->owner = tradePlayer;
          break;
        } else if (command == "reject") {
          cout << "Trade rejected!" << endl;
          break;
        } else {
          cout << "Invalid command. Please enter accept or reject: ";
        }
      }
    } else {
      Building *receiveBuidling = b->findBuilding(receive);
      if (receiveBuidling == nullptr) {
        cout << receive << " is not a valid building name!" << endl;
        return;
      }
      if (receiveBuidling->getOwner() != tradePlayer) {
        cout << bntostr(receiveBuidling->GetBuildingName()) << " is not owned by " << tradePlayer->getName() << "!" << endl;
        return;
      }
      cout << "Player " << tradePlayer->getName() << ", please accept or reject the trade: ";
      string command;
      while (cin >> command) {
        if (command == "accept") {
          cout << "Trade accepted!" << endl;
          curPlayer->addProperty(receiveBuidling);
          curPlayer->removeProperty(giveBuilding);
          tradePlayer->removeProperty(receiveBuidling);
          tradePlayer->addProperty(giveBuilding);
          receiveBuidling->setOwner(curPlayer);
          giveBuidling->setOwner(tradePlayer);
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
  cout << "Auction of building " << bntostr(bs->getBuidlingName()) << " starts!" << endl;
  int curBid = bs->getCost()-1; // base bid
  int playersCount = players.size();
  std::vector<bool> auctionStatus(playersCount);
  for (int i = 0; i < playersCount; i++) {
    auctionStatus[i] = true;
  }
  Player *p = curPlayer;
  int index = players.find(players.begin(), players.end(), p);
  
  for (int i = index; ; i++) {
    if (i = players.size()) i = 0;
    if (!auctionStatus[i]) continue;

    if (playersCount = 1 && curBid != bs->getCost()-1) {
      cout << "Congradulations! Player " << p->getName() << " buys building " << bntostr(b->GetBuildingName()) << " at price of $" << curBid << endl;
      p->addProperty(b);
      p->addFund(-curBid);
      bs->getOwner() = p;
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
          if (bid > players[i]->money) {
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
  } else if (bs->getOwner() != curPlayer) {
    cout << bn << " is not owned by you!" << endl;
  } else if (bs->getBuidlingType() != BuildingType::Academic) {
    cout << bn << " is not an academic building!" << endl;
  } else if (bs->getMonopoly() != curPlayer) {
    cout << "You don't own all buildings in that monopoly block, you can't add/sell improvement!" << endl;
  } else if (instruction == "buy") {
    if(!bs->addImprovement()) cout << "Unsucessful buy!" << endl;
  } else if (instruction == "sell") {
    if(!bs->removeImprovement()) cout << "Unsuccessful sell!" << endl;
  } else {
    cout << "Invalid command, please enter buy/sell for instruction!" << endl;
  }
}


// mortgage building
void Gameplay::mortgage(string bn) {
  Building *bs = b->findBuilding(bn);
  if (bs == nullptr) {
    cout << bn << " is not a name of a property building!" << endl;

  } else if (bs->getOwner() != curPlayer) {
    cout << bn << " is not owned by you!" << endl;

  } else if (bs->getBuidlingType() != BuildingType::Academic) {
    cout << bn << " is not an academic building!" << endl;

  } else {
    curPlayer->mortgage(b);
  }
}



// unmortgage building
void Gameplay::unmortgage(string bn) {
  Building *bs = b->findBuilding(bn);
  if (bs == nullptr) {
    cout << bn << " is not a name of a property building!" << endl;

  } else if (bs->getOwner() != curPlayer) {
    cout << bn << " is not owned by you!" << endl;

  } else if (bs->getBuidlingType() != BuildingType::Academic) {
    cout << bn << " is not an academic building!" << endl;

  } else {
    curPlayer->unortgage(b);
  }
}


// show assets of curPlayer
void Gameplay::assets() {
  cout << "Player " << curPlayer->getName() << ":" << endl;
  cout << "Money: $" << curPlayer->money << endl;
  cout << "Total Worth: $" << curPlayer->getTotalWorth() << endl;
  cout << "Properties: ";
  for (int i = 0; i < curPlayer->property.size(); i++) {
    cout << bntostr(curPlayer->property[i]->GetBuildingName()) << ", ";
  }
  cout << endl;
}


// show assets of all Players
void Gameplay::all() {
  for (int j = 0; j < players.size(); j++) {
    cout << "Player " << players[i]->getName() << ":" << endl;
    cout << "Money: $" << players[i]->money << endl;
    cout << "Total Worth: $" << players[i]->getTotalWorth() << endl;
    cout << "Properties: ";
    for (int i = 0; i < players[i]->property.size(); i++) {
      cout << bntostr(players[i]->property[i]->GetBuildingName()) << ", ";
    }
    cout << endl;
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
    if (bs->getBuidlingType() == BuildingType::Nonproperty) continue;
    saving << bntostr(bs->getBuildingName()) << " ";
    if (bs->getOwner() == nullptr) saving << "BANK ";
    else saving << bs->getOwner()->getName() << " ";
    if (bs->getBuidlingType() == BuildingType::Gyms || bs->getBuidlingType() == BuildingType::Residence ) {
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


