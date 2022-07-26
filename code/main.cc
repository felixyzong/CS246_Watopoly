#include "gameplay.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
 //if (argc == 2 && argv[1] == string("-testing")) {
 //  std::cout << "test mode starts" << std::endl;
 //  Gameplay *gp = new Gameplay(true);
 //  gp->play();
 //  delete gp;
 //} else {
 //  Gameplay *gp = new Gameplay(false);
 //  gp->play();
 //  delete gp;
 //}
  bool isTest = false, isLoad = false, isTheme = false;
  string theme, load;
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      if (argv[i] == string("-testing")) isTest = true;
      if (argv[i] == string("-load")) {
        cout << "detected load" << endl;
        if (i == argc - 1) {
          cout << "Missing loading file!" << endl;
          return - 1;
        }
        isLoad = true;
        load = argv[i+1];
        i++;
      }
      if (argv[i] == string("-theme")) {
        cout << "detected theme" << endl;
        if (i == argc - 1) {
          cout << "Missing theme file!" << endl;
          return - 1;
        }
        isTheme = true;
        theme = argv[i+1];
        i++;
      }
    }
  }

  Gameplay *gp;

  if (isLoad && isTheme) {
    cout << "Loading file " << load << " and theme" << theme << endl;
    gp =  new Gameplay(isTest, load, theme);
  } else if (!isLoad && !isTheme) {
    gp =  new Gameplay(isTest);
  } else if (isLoad) {

    cout << "Loading file " << load << endl;
    gp = new Gameplay(isTest, isLoad, load);
  } else {
    cout << "Loading theme " << theme << endl;
    gp = new Gameplay(isTest, isLoad, theme);
  }
  gp->play();
  delete gp;
}
