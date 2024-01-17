//Player.cpp
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <vector>

#include "Player.hpp"

/*Player::Player(std::string new_name, int new_currentBet){
    playerName = new_name;
    playerScore = 1000;
    currentBet = new_currentBet;
}*/

void Player::setPlayerName(const std::string& name){
    playerName = name;
}

void Player::setPlayerBet(int bet){
    currentBet = bet;
}

void Player::setPlayerScore(int score){
    playerScore = score;
}

std::string Player::getPlayerName() const {
    return playerName;
}

int Player::getPlayerBet() const {
    return currentBet;
}

int Player::getPlayerScore() const {
    return playerScore;
}