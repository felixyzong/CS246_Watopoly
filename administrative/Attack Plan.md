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
struct BuildingInfo {
  
};
```



```c++
class Building : public Subject<BuildingInfo> {
   // abstract building class
 public:
  virtual building() = 0;
  // ...
  virtual ~building() = 0;
};

class AcademicBuilding : public Building {
  // ...
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
// A copy of observer class provided for a4q3

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
// A copy of subject class provided for a4q3

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



