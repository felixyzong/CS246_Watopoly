#ifndef INFO_H
#define INFO_H
class Player;

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


#endif