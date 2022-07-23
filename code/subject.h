#ifndef SUBJECT_H
#define SUBJECT_H

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
  for (auto &ob : this->obs) ob->notify(*this);
}

#endif
