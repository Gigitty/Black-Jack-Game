//Player.cpp
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>

#include "Player.hpp"

void Player::setPlayerName(const std::string& playerName) {
    name = playerName;
    score = 1000;
    isBust = false;
    isSplit = false;
}

void Player::setPlayerBet(int currentBet) {
    bet = 0;
    bet = currentBet;
}

void Player::setPlayerScore(int playerScore) {
    score = playerScore;
}

void Player::setHandValue(int value) {
    handValue += value;
}

void Player::setBust() {
    isBust = true;
}

void Player::setSplit() {
    isSplit = true;
}

std::string Player::getPlayerName() const {
    return name;
}

int Player::getPlayerBet() const {
    return bet;
}

int Player::getPlayerScore() const {
    return score;
}

int Player::getHandValue() const {
    return handValue;
}

bool Player::getBust() const {
    return isBust;
}

bool Player::getSplit() const {
    return isSplit;
}

void Player::resetPlayer() {
    isBust = false;
    handValue = 0;
}