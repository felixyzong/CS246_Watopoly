# Attack Plan

CS 246 Assignement 5 Project Watopoly Attack Plan

Group: f2zong, q473wang, t345chen

## Class Breakdown

Board is an observer to all players and all buildings.

### Player Class

```c++
struct PlayerInfo {
  
};
```

```c++
class Player : public Subject<PlayerInfo> {
  long money;
  std::vector<Building> property;
  // ...
 public:
  // ...
};



```

### Building Class

```c++
enum class BuildingType { Academic, Residence, Gyms, CollectOSAP, DCTimsLine, GoToTims, GooseNesting, Tuition, CoopFee, SLC, NeedlesHall}; 
enum class AcademicType { AL, ML, ECH, PAS, HH, RCH, DWE, CPH, LHI, BMH, OPT, EV1, EV2, EV3, PHYS, B1, B2, EIT, ESC, C2, MC, DC };
enum class ResidenceType { MKV，UWP, V1, REV };
enum class GymsType { PAC, CIF };

// BuildingInfo are received by board for display
struct BuildingInfo {
  BuildingType bt;
  AcademicType at;
  ResidenceType rt;
  GymsType gt;
  Player * owner;
  int improvement;
};
```

```c++
class Building : public Subject<BuildingInfo> {
  BuildingType bt;
 public:
  virtual Buidling(BuidlingType bt);
  virtual int tuition() const = 0;
  virtual BuildingType getBuidlingType() const { return bt; }
  virtual ~building() = default;
  virtual InfoType getInfo() const = 0;
};

class AcademicBuilding : public Building {
  AcademicType at;
  Player* owner;
  int improvement;
 public:
  AcademicBuilding(AcademicType at);
  bool AddImprovement(); // return false if already 5 improvements
  virtual int tuition() const override;
  Player *getOwner();
  virtual BuildingInfo getInfo() const override;
  ~AcademicBuidling(); 
};

class ResidenceBuilding : public Building {
  ResidenceType rt;
  Player* owner;
 public:
  ResidenceBuilding(ResidenceType at);
  virtual int tuition() const override;
  Player *getOwner();
  virtual BuildingInfo getInfo() const override;
  ~ResidenceBuidling(); 
};

class GymsBuilding : public Building {
  GymsType gt;
  Player* owner;
 public:
  GymsBuilding(GymsType gt);
  virtual int tuition() const override;
  Player* getOwner();
  virtual BuildingInfo getInfo() const override;
  ~GymsBuilding();
};

class NonPropertyBuilding : public Building {
  friend class player;
  friend class Board;
 public:
  NonPropertyBuilding(BuidlingType bt);
  int MoveTo(); // return an index that player should be moved to based on the rule of that non-property buidling
  virtual int tuition() const override;
  virtual BuildingInfo getInfo() const override;
  ~NonPropertyBuilding();
};
```

### Board Class

```c++
class Board : public Observer<BuildingInfo>, public Observer<PlayerInfo> {
  // ...
 public:
  init(Player p);
  // ...
};
```

### Observer Class

```c++
// A revised version based on observer class provided for a4q3

template <typename InfoType> class Subject;

template <typename InfoType>
class Observer {
  public:
  virtual void notify(Subject<InfoType> &whoFrom) = 0;
  virtual ~Observer() = default;
};
```

### Subject Class

```c++
// A revised version based on subject class provided for a4q3

template <typename InfoType> class Observer;

template <typename InfoType>
class Subject {
  std::vector<Observer<InfoType>*> obs;
 public:
  void attach(Observer<InfoType> *ob);
  void notifyObservers();
  virtual InfoType getInfo() const = 0;
};

template <typename InfoType>
void Subject<InfoType>::attach(Observer<InfoType> *o) {
  observers.emplace_back(o);
}

template <typename InfoType>
void Subject<InfoType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

```



