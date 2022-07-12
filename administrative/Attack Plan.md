# Attack Plan

CS 246 Assignement 5 Project Watopoly Attack Plan

Group: f2zong, q473wang, t345chen

## Class Breakdown

Board is an observer to all players and all buildings.

### Player Class

```c++
class Player : public Subject {
  long money;
  std::vector<Building> property;
  // ...
 public:
  // ...
};
```

### Building Class

```c++
class Building : public Subject {
   // abstract building class
 public:
  virtual Abuilding() = 0;
  // ...
  virtual ~Abuilding() = 0;
};

class AcademicBuilding : public Building {
  // ...
}

```

### Board Class

```c++
class Board : public Observer {
  // ...
 public:
  init(Player p);
  // ...
};
```

### Observer Class

```c++
class Observer {
  
}
```

### Subject Class

```c++
class Subject {
  
}
```

