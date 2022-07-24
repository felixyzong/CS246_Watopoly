#include "gameplay.h"
#include <string>

int main(int argc, char **argv) {
  if (argc == 1 && argv[0] == "test") {
    Gameplay *gp = new Gameplay(true);
    gp->play();
    delete gp;
  } else {
    Gameplay *gp = new Gameplay(false);
    gp->play();
    delete gp;
  }
}
