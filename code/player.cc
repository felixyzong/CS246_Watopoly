//
// Created by a1234 on 2022/7/21.
//

#include "player.h"
#include "info.h"
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;
Player::Player(int money, char name): money{money}, name{name}, pos{0} {}

Player::~Player() {
  pos = -1;
  notifyObservers();
  for (Property* p : property) {
    p->init();
  }
}

char Player::getName() { return name; }
int Player::getMoney() {return money; }
int Player::getPos() { return pos; }
int Player::getTimTurn() { return TimLineTurn; }
int Player::getTimCups() const { return cup; }
bool Player::isInTim() { return isInTimLine; }

int Player::getTotalWorth() {
  int totalWorth = 0;
  for (auto it : property) {
    totalWorth += it->getWorth();
  }
  return totalWorth + money;
}

void Player::addFund(int num) {
  money += num;
}

void Player::gainCup() {
  cup += 1;
}

// return true if player cannot leave, return false if can leave
bool Player::incTimTurn() {
  if (TimLineTurn == 0) {
    TimLineTurn += 1;
    isInTimLine = true;
    cout << "It's your " << TimLineTurn << "th turn at tims line." << endl;
    return true;
  }
  cout << "It's your " << TimLineTurn << "th turn at tims line." << endl;
  if (cup > 0) {
    cup -= 1;
    OutfromTimsLine();
    cout << "You leave tim line because you have a Roll up the Rim Cup!" << endl;
    return false;
  } else if (TimLineTurn == 3) {
    OutfromTimsLine();
    cout << "You leave tim line because you have been here for 3 turns!" << endl;
    return false;
  } else {
    cout << "Do you want to pay $50 to leave tim line? Please enter yes or no: ";
    string command;
    while (cin >> command) {
      if (command == "yes") {
        if (money < 50) {
          cout << "You don't have enough money!" << endl;
          break;
        }
        cout << "You leave tim line because you paid $50!" << endl;
        money -= 50;
        OutfromTimsLine();
        return false;
      } else if (command == "no") break;
      else {
        cout << "Invalid command! Please enter yes or no: ";
      }
    }
  }
  TimLineTurn += 1;
  isInTimLine = true;
  return true;
}

void Player::MovetoTimsLine() {
  TimLineTurn = 0;
  isInTimLine = true;
}
void Player::OutfromTimsLine() {
  TimLineTurn = 0;
  isInTimLine = false;
}


void Player::addProperty(Property *b) {
  property.emplace_back(b);
  b->setOwner(this);
}

void Player::removeProperty(Property *b) {
  property.erase(find(property.begin(), property.end(), b));
}


void Player::buyImprovement(Property *b) {
  if (find(property.begin(), property.end(), b) == property.end()) {
    cout << "You don't own the building!" << endl;
    return;
  }
  if (b->getBuildingType() != BuildingType::Academic) {
    cout << "It's not academic building!" << endl;
    return;
  }
  static_cast<AcademicBuilding *>(b)->addImprovement();
}

void Player::sellImprovement(Property *b) {
  if (find(property.begin(), property.end(), b) == property.end()) {
    cout << "You don't own the building!" << endl;
    return;
  }
  if (b->getBuildingType() != BuildingType::Academic) {
    cout << "It's not academic building!" << endl;
    return;
  }
  static_cast<AcademicBuilding *>(b)->sellImprovement();
}



void Player::buyProperty(Property *b) {
  if (money < b->getCost()) {
    cout << "You don't have enough money!" << endl;
    return;
  }
  addProperty(b);
  addFund(-b->getCost());
  b->setOwner(this);
}

void Player::mortgage(Property *b) {
  if (find(property.begin(), property.end(), b) == property.end()) {
    cout << "You don't own the building!" << endl;
    return;
  }
  b->mortgage();
}

void Player::unmortgage(Property *b) {
  if (find(property.begin(), property.end(), b) == property.end()) {
    cout << "You don't own the building!" << endl;
    return;
  }
  b->unmortgage();
}

// To move on the board for a certain number
void Player::move(int num){
  pos += num;
  pos %= 40;
  if (pos < 0) { pos += 40; }
  notifyObservers();
}

// differentiates "sent" to a place and "move" to a place
void Player::setPos(int pos) {
  this->pos = pos;
  notifyObservers();
}

void Player::printAsset() {
  cout << "Player " << name << ":" << endl;
  cout << "Money: $" << money << endl;
  cout << "Total Worth: $" << getTotalWorth() << endl;
  cout << "Properties: ";
  for (int i = 0; i < property.size(); i++) {
    cout << bntostr(property[i]->getBuildingName());
    if (property[i]->getBuildingType() == BuildingType::Academic) {
      cout << "(" << static_cast<AcademicBuilding *>(property[i])->getImprovement() << ")";
    }
    if (property[i]->getMortgage()) {
      cout << "(M)";
    }
    cout << ", ";
  }
  cout << endl;
}

PlayerInfo Player::getInfo() const {
  PlayerInfo pi;
  pi.name = this->name;
  pi.pos = this->pos;
  return pi;
}


void Player::setCup(int n) {
  cup = n;
}

void Player::setTimTurn(int n) {
  isInTimLine = true;
  TimLineTurn = n;
}