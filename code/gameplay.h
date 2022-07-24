#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
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
#include "watutils.h"
#include "Property.h"
/*
This class will be responsible for interpreting input as instructions. 
It will keep track of the status of each player, players assigned, etc. 
*/
class Gameplay {
  Board* b;
	std::vector<Player *> players;
	Player *curPlayer;
  Building *curBuilding;
  int curTuition = 0;
  bool isRolled = false;
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  bool isTest;
  int totalRimCup = 0;


  friend class Player;
  friend class Building;

  Player *findPlayer(char c);
  Building *findBuilding(std::string name);
 	void dropOut();
	bool checkBankRuptcy();

	void auction(Building *b); // begin an auction on building b, input for a single player will be like [num]/W. "W" means withdraw

  bool parseAction(); // return true for normal moves, return false for bankrupt
  void trade(char pn, std::string give, std::string receive);
  void roll();
  void roll(int die1, int die2); // only availale in test mode
  void switchPlayer();
  void improve(std::string bn, std::string instruction);
  void mortgage(std::string bn);
  void unmortgage(std::string bn);
  void assets();
  void all();
  void saveGame(std::string file);
  void loadGame(std::string file);
 public:
  void setseed(unsigned seed);
  Gameplay(bool test);
  void play();
  ~Gameplay();
  friend std::ostream &operator<<(std::ostream& out, Gameplay* gp);
};


#endif
