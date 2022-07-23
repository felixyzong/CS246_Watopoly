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
int Player::getCup() { return cup;}
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
    cout << "It's your " << TimeLineTurn << "th turn at tim line." << endl;
    return true;
  }
}


void Player::addProperty(Building *b) {
  property.emplace_back(b);
}

void Player::removeProperty(Buidling *b) {
  property.erase(b);
}


void Player::buyImprovement(Building *b) {
  if (find(property.begin(), property.end(), b) == property.end()) {
    cout << "You don't own the building you are mortgaging!" << endl;
    return;
  }
  b->addImprovement();
}

void Player::sellImprovement(Building *b) {
  if (find(property.begin(), property.end(), b) == property.end()) {
    cout << "You don't own the building you are mortgaging!" << endl;
    return;
  }
  b->sellImprovement();
}

void Player::buyProperty(Building *b) {
  if (player->money < b->getCost()) {
    cout << "You don't have enough money!" << endl;
    return;
  }
  addProperty(b);
  p->addFund(-b->getCost());
}

void Player::mortgage(Building *b) {
  if (find(property.begin(), property.end(), b) == property.end()) {
    cout << "You don't own the building you are mortgaging!" << endl;
    return;
  }
  b->mortgage();
}

void Player::unmortgage(Building *b) {
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