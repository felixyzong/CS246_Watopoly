#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include <iostream>
#include "info.h"
#include "player.h"
#include "building.h"
#include "board.h"
#include "observer.h"
#include "subject.h"



class TextDisplay : public Observer<BuildingInfo>, public Observer<PlayerInfo> {
  std::vector<std::vector<char>> text;
 public:
  TextDisplay(Board *b, std::vector<player*> players);
  virtual void notify(Subject<BuildingInfo> &whoFrom) override;
  virtual void notify(Subject<PlayerInfo> &whoFrom) override;
  friend std::ostream &operator<<(std::ostream &out, constTextDisplay* td);
  ~TextDisplay();
};

#endif
