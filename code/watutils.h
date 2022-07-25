
#ifndef _WATUTILS_H
#define _WATUTILS_H

#include <random>
#include <chrono>
// test
#include <iostream>
//


inline int randomGen(int low, int high) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 rng{seed};
  std::uniform_int_distribution<> distrib(low, high);
  int r = distrib(rng);
  // test
  // std::cout << r << " is generated within " << low << " and " << high << std::endl;
  //
  return r;
}


inline bool isNumeric(std::string const &str)
{
  auto it = str.begin();
  while (it != str.end() && std::isdigit(*it)) {
    it++;
  }
  return !str.empty() && it == str.end();
}

/* TODO : fix checkMonopoly
bool checkMonopoly(Building *p, Board *b) {
  for (int i = 0; i < 40; ++i) {
    Building * bs = b->getBuilding(i);
    if (bs->getBuildingType() == BuildingType::Academic && bs->getBlock() == p->getBlock()) {
      if (bs->getOwner() != p->getOwner()) {
        return false;
      }
    }
  }
  return true;
}
*/

#endif //_WATUTILS_H