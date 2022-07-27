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
  bool isTest;
  int totalRimCup = 0;
  bool running = true;
  std::string theme = "square.in";


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
  Gameplay(bool test);
  Gameplay(bool test, bool isLoad, std::string load);
  Gameplay(bool test, std::string load, std::string theme);
  void play();
  ~Gameplay();
};


#endif
