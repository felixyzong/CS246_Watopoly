#ifndef GAMEPLAY_H
#define GAMEPLAY_H
#include <vector>
#include <iostream>
#include <fstream>
#include "textdisplay.h"
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
  bool isTest;

  Player *findPlayer(char c);
	void switchPlayer();
 	void dropOut(Player *);
	bool checkBankRuptcy(Player *);
	void auction(Building *b); // begin an auction on building b, input for a single player will be like [num]/W. "W" means withdraw
 public:
  Gameplay(bool test);
	void parseAction(std::string action);
  void saveGame();
	void loadGame(std::string file);
  ~Gameplay();
}


#endif
