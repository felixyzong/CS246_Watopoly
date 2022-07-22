#ifndef OBSERVER_H
#define OBSERVER_H

template <typename InfoType> class Subject;

template <typename InfoType>
class Observer {
  public:
  virtual void notify(Subject<InfoType> &whoFrom) = 0;
  virtual ~Observer() = default;
};

#endif
