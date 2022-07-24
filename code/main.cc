#include "gameplay.h"
#include <string>

int main(int argc, char **argv) {
  Gameplay *gp = new Gameplay(true);
  gp->play();
  delete gp;
}
