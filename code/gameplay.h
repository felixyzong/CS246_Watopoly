#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include "info.h"
#include "building.h"
#include "residencebuilding.h"
#include "academicbuilding.h"
#include "gymsbuilding.h"
#include "nonpropertybuilding.h"
#include "board.h"

/*
This class will be responsible for interpreting input as instructions. 
It will keep track of the status of each player, players assigned, etc. 
*/
class Gameplay {
  Board* b;
	std::vector<Building *> buildings;
	std::vector<Player *> players;
	std::vector<char> availablePlayers;
	Player *curPlayer;
  Building *curBuilding;
  unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  bool isTest;
  int curTuition;
  int totalRimCup = 0;
  friend class Player;

  Player *findPlayer(char c);
 	void dropOut(Player *p);
	bool checkBankRuptcy(Player *p);

	void auction(Building *b); // begin an auction on building b, input for a single player will be like [num]/W. "W" means withdraw

  bool parseAction(); // return true for normal moves, return false for bankrupt
  void trade(Player* p, int money);
  void roll();
  void roll(int die1, int die2); // only availale in test mode
  void switchPlayer();
  void improve(AcademicBuilding *ab, char instruction);
  void mortage(Building *b);
  void unmortage(Building *b);
  void assets();
  void all();
 public:
  void setseed(unsigned seed);
  Gameplay(bool test);
  void play();
  void saveGame();
  void loadGame(std::string file);
  ~Gameplay();
}


#endif
