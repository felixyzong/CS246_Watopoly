//
// Created by a1234 on 2022/7/24.
//

#ifndef _WATUTILS_H
#define _WATUTILS_H

#include <random>

inline int randomGen(int low, int high, unsigned seed) {
  std::default_random_engine rng{seed};
  std::uniform_int_distribution<> distrib(low, high);
  return distrib(rng);
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
