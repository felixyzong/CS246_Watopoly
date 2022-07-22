#ifndef INFO_H
#define INFO_H
class Player;

#include <vector>

struct PlayerInfo {
  char name;
  int pos;
};

enum class BuildingType { Academic, Residence, Gyms, Nonproperty };
enum class BuildingName { AL, ML, ECH, PAS, HH, RCH, DWE, CPH, LHI, BMH, OPT, EV1, EV2, EV3, PHYS, B1, B2, EIT, ESC, C2, MC, DC, MKV, UWP, V1, REV, PAC, CIF, CollectOSAP, DCTimsLine, GoToTims, GooseNesting, Tuition, CoopFee, SLC, NeedlesHall}; 
enum class MonopolyBlock { Arts1, Arts2, Eng, Health, Env, Sci1, Sci2, Math };

// BuildingInfo are received by textdisplay for display
struct BuildingInfo {
  BuildingName bn;
  Player * owner;
  int improvement;
};

const std::vector<int> AL{40, 50, 2, 10, 30, 90, 160, 250};
const std::vector<int> ML{60, 50, 4, 20, 60, 180, 320, 450};
const std::vector<int> ECH{100, 50, 6, 30, 90, 270, 400, 550};
const std::vector<int> PAS{100, 50, 6, 30, 90, 270, 400, 550};
const std::vector<int> HH{120, 50, 8, 40, 100, 300, 450, 600};
const std::vector<int> RCH{140, 100, 10, 50, 150, 450, 625, 750};
const std::vector<int> DWE{140, 100, 10, 50, 150, 450, 625, 750};
const std::vector<int> CPH{160, 100, 12, 60, 180, 500, 700, 900};
const std::vector<int> LHI{180, 100, 14, 70, 200, 550, 750, 950};
const std::vector<int> BMH{180, 100, 14, 70, 200, 550, 750, 950};
const std::vector<int> OPT{200, 100, 16, 80, 220, 600, 800, 1000};
const std::vector<int> EV1{220, 150, 18, 90, 250, 700, 875, 1050};
const std::vector<int> EV2{220, 150, 18, 90, 250, 700, 875, 1050};
const std::vector<int> EV3{240, 150, 20, 100, 300, 750, 925, 1100};
const std::vector<int> PHYS{260, 150, 22, 110, 330, 800, 975, 1150};
const std::vector<int> B1{260, 150, 22, 110, 330, 800, 975, 1150};
const std::vector<int> B2{280, 150, 24, 120, 360, 850, 1025, 1200};
const std::vector<int> EIT{300, 200, 26, 130, 390, 900, 1100, 1275};
const std::vector<int> ESC{300, 200, 26, 130, 390, 900, 1100, 1275};
const std::vector<int> C2{320, 200, 28, 150, 450, 1000, 1200, 1400};
const std::vector<int> MC{350, 200, 35, 175, 500, 1100, 1300, 1500};
const std::vector<int> DC{400, 200, 50, 200, 600, 1400, 1700, 2000};

int randomGen(int low, int high, unsigned seed) {
  default_random_engine rng{seed};
  uniform_int_distribution<> distrib(low, high);
  return distrib(rng);
}


#endif
