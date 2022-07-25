#include "gameplay.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc == 2 && argv[1] == string("test")) {
    std::cout << "test mode starts" << std::endl;
    Gameplay *gp = new Gameplay(true);
    gp->play();
    delete gp;
  } else {
    Gameplay *gp = new Gameplay(false);
    gp->play();
    delete gp;
  }
}
