# Attack Plan

CS 246 Assignement 5 Project Watopoly Attack Plan

Group: f2zong, q473wang, t345chen

## Class Breakdown

### TextDisplay Class

```c++
class TextDisplay : public Observer<BuildingInfo>, public Observer<PlayerInfo> {
  std::vector<std::vector<char>> text;
 public:
  TextDisplay(Board *b, std::vector<player*> players);
  virtual void notify(Subject<BuildingInfo> &whoFrom) override;
  virtual void notify(Subject<PlayerInfo> &whoFrom) override;
  friend std::ostream &operator<<(std::ostream &out, constTextDisplay* td);
  ~TextDisplay();
};
```
### Monopoly Block
```c++
// The header file to provide collection of monopoly blocks
std::vector<Building *> Arts1;
std::vector<Building *> Arts2;
std::vector<Building *> Eng;
std::vector<Building *> Health;
std::vector<Building *> Env;
std::vector<Building *> Sci1;
std::vector<Building *> Sci2;
std::vector<Building *> Math;
```


### Controller Class

```c++

/*
This class will be responsible for interpreting input as instructions. 
It will keep track of the status of each player, players assigned, etc. 
*/
class Controller {
  TextDisplay *td;
	Board *b;
	std::vector<Player *> players;
	std::vector<char> availablePlayers;
	Player *findPlayer(char c);
	Player *curPlayer;
	void switchPlayer();
 	void dropOut(Player *);
	bool checkBankRuptcy(Player *);
	bool isTest;
	void auction(Building *b); // begin an auction on building b, input for a single player will be like [num]/W. "W" means withdraw
 public:
	void parseAction(std::string action);
	void loadGame(std::string file);
}
```

### Player Class

```c++
struct PlayerInfo {
  char name;
  int pos;
};
```

```c++
class Player {
  long money;
  std::vector<Building *> property;
  // ...
  int cup; // The numebr of Roll Up the Rim Cup
  int TimLineTurn; 
  bool isInTimLine;
  int pos;
  char name;
  bool rolled;
 public:
  // ...
  Player(long money, char name);
  void addFund(int num); // To increase the money for a certain number
  int getTotalWorth();   // get the total wealth
  int rollDice();        // get a random number
  void move(int num);    // To move on the board for a certain number
  void gainCup();        // Increase the cup by 1
  int getTimTurn();      // Get the number of turn the player is stuck at time line
  int incTimTurn();      // Increase the tim line turn
  bool isInTim();
  void buyProperty(Building *b);
  int getPos();
  void setPos(int pos); // differentiates "sent" to a place and "move" to a place
  char getName();
  bool isRolled();
  void addProperty(Building *b);
  void mortgage();
  void unMortgage();
};



```

### Building Class

```c++
enum class BuildingType { Academic, Residence, Gyms, CollectOSAP, DCTimsLine, GoToTims, GooseNesting, Tuition, CoopFee, SLC, NeedlesHall}; 
enum class MonopolyBlock { Arts1, Arts2, Eng, Health, Env, Sci1, Sci2, Math };
enum class AcademicType { AL, ML, ECH, PAS, HH, RCH, DWE, CPH, LHI, BMH, OPT, EV1, EV2, EV3, PHYS, B1, B2, EIT, ESC, C2, MC, DC };
enum class ResidenceType { MKV，UWP, V1, REV };
enum class GymsType { PAC, CIF };

// BuildingInfo are received by board for display
struct BuildingInfo {
  BuildingType bt;
  AcademicType at;
  MonopolyBlock mb;
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
  MonopolyBlock mb;
  Player* owner;
  int improvement;
  bool mortgage;
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
class Board {
  std::vector<Building *> buildings;
 public:
  Building * getBuilding(int pos);
  void init();
  int searchBuilding(Building *);
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

### Answer to questions

**Question:** After reading this subsection, would the Observer Pattern be a good pattern to use when implementing a game board? Why or why not?

**Answer:** Yes, similar to assignment 4 question 3, an observer pattern can notify the board class only when there are changes inside building or player classes that will result changes in text displayed.

**Question:** Suppose that we wanted to model SLC and Needles Hall more closely to Chance and Community Chest cards. Is there a suitable design pattern you could use? How would you use it?

**Answer:** I don't find a proper design pattern that are suitable for model SLC and Needles Hall. In my opinion, these two buildings can be implemented by placing a random number generator inside, by which the number generated each time will determine the behaviour of players on that building.

**Question:** Is the Decorator Pattern a good pattern to use when implementing Improvements? Why or why not?

**Answer:** Decorator Pattern might not be a good pattern to use for improvement. Since each improvement level will return different addition on tuition which is also differ from building to building, and there is a limit of 5 improvement maximum, if we implement it as a decorator, we need to implement too many decorators or too complicated logic inside decorators. Instead, an integer that saves the number of improvements of a building will be good enough to represent and easy to implement the tuition function.
