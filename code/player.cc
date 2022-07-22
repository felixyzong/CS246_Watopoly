//
// Created by a1234 on 2022/7/21.
//

#include "player.h"
#include "info.h"
#include <random>
#include <iostream>
#include <algorithm>

using namespace std;
Player::Player(long money, char name): money{money}, name{name} {}

void Player::addFund(int num) {
  money += num;
}

int Player::getTotalWorth() {
  int worth = 0;
  for (Building * b : property) {
    worth += b->getWorth();
  }
  return worth;
}

int Player::rollDice(unsigned seed) {
  return randomGen(1, 6, seed);
}

void Player::move(int num) {
  pos += num;
  pos %= 40;
}

void Player::gainCup() {
  cup++;
}

int Player::getTimTurn() {
  return TimLineTurn;
}

int Player::incTimTurn() {
  TimLineTurn++;
}

bool Player::isInTim() {
  return isInTimLine;
}

void Player::buyProperty(Building *b) {
  int price = b->getCost();
  if (price > money) {
    cout << "You don't have enough money! Please try to raise fund.";
    return;
  }
  money -= price;
  addProperty(b);
}

int Player::getPos() {
  return pos;
}

void Player::setPos(int pos) {
  // TODO: add other functionality like move to Tims Line
  this->pos = pos;
}

char Player::getName() {
  return name;
}

bool Player::isRolled() {
  return rolled;
}

void Player::addProperty(Building *b) {
  property.emplace_back(b);
}

void Player::mortgage(Building *b) {
  if (find(property.begin(), property.end(), b) == property.end()) {
    cout << "You don't own the building you are mortgaging!" << endl;
    return;
  }
  if (b->getMortgage()) {
    cout << "This building is under mortgage! Try another building!" << endl;
    return;
  }
  if (b->getImprovement() != 0) {
    cout << "You must sold improvements to mortgage this building!" << endl;
    return;
  }
  b->mortgage();
  addFund(b->getCost() / 2);
  cout << "You successfully mortagaged this building! Now you have $" << money << endl;
}

void Player::unMortgage(Building *b) {
  int price = b->getCost() * 0.6;
  if (money < price) {
    cout << "You don't have enough money to unmortgage this buidling! The price is " << price << " and you currently have " << money << endl;
    return;
  }
  b->unMortgage();
}















