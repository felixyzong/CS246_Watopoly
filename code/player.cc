//
// Created by a1234 on 2022/7/21.
//

#include "player.h"
#include "info.h"
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;
Player::Player(int money, char name): money{money}, name{name} {}

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
  return totalWorth;
}

void Player::addFund(int num) {
  money += num;
}

void Player::gainCup() {
  cup += 1;
}

// return true if player cannot leave, return false if can leave
bool Player::incTimTurn() {
  if (cup > 0) {
    cup -= 1;
    isInTimLine = false;
    cout << "You leave tim line because you have a Roll up the Rim Cup!" << endl;
    return false;
  } else if (TimLineTurn == 3) {
    TimLineTurn = 0;
    isInTimLine = false;
    cout << "You leave tim line because you have been here for 3 turn!" << endl;
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
        TimLineTurn = 0;
        isInTimLine = false;
        return false;
      } else if (command == "no") break;
      else {
        cout << "Invalid command! Please enter yes or no: ";
      }
    }
    TimLineTurn += 1;
    isInTimLine = true;
    cout << "It's your " << TimLineTurn << "th turn at tim line." << endl;
    return true;
  }
}


void Player::addProperty(Property *b) {
  property.emplace_back(b);
}

void Player::removeProperty(Property *b) {
  property.erase(find(property.begin(), property.end(), b));
}


void Player::buyImprovement(Property *b) {
  if (find(property.begin(), property.end(), b) == property.end()) {
    cout << "You don't own the building you are mortgaging!" << endl;
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
    cout << "You don't own the building you are mortgaging!" << endl;
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
}

void Player::mortgage(Property *b) {
  if (find(property.begin(), property.end(), b) == property.end()) {
    cout << "You don't own the building you are mortgaging!" << endl;
    return;
  }
  b->mortgage();
}

void Player::unmortgage(Property *b) {
  if (find(property.begin(), property.end(), b) == property.end()) {
    cout << "You don't own the building you are unmortgaging!" << endl;
    return;
  }
  b->unmortgage();
}

// To move on the board for a certain number
void Player::move(int num){
  pos += num;
  pos %= 40;
}

// differentiates "sent" to a place and "move" to a place
void Player::setPos(int pos) {
  this->pos = pos;
}

void Player::printAsset() {
  cout << "Player " << name << ":" << endl;
  cout << "Money: $" << money << endl;
  cout << "Total Worth: $" << getTotalWorth() << endl;
  cout << "Properties: ";
  for (int i = 0; i < property.size(); i++) {
    cout << bntostr(property[i]->getBuildingName()) << ", ";
  }
  cout << endl;
}
