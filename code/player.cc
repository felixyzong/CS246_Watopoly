//
// Created by a1234 on 2022/7/21.
//

#include "player.h"
#include <random>
#include <iostream>
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
  default_random_engine rng{seed};
  uniform_int_distribution<> distrib(1, 100);
  return distrib(rng);
}

void Player::move(int num) {
  pos += num;
  pos %= 39;
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
  if (b->getImprovement() != 0) {
    cout << "You must sold improvements to mortgage this building!" << endl;
    return;
  }
  b->setMortgage();
  addFund(b->getCost() / 2);
  cout << "You successfully mortagaged this building! Now you have $" << money << endl;
}

void Player::unMortgage(Building *b) {
  int price = b->getCost() * 0.6;
  if (money < price) {
    cout << "You don't have enough money to unmortgage this buidling! The price is " << price << " and you currently have " << money << endl;
    return;
  }
  b->setUnmortgage();
}















