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

  // element initialize
  b = new Board();
  td = new TextDisplay(b, players);
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





