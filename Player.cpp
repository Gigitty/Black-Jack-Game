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

void Player::setPlayerName(std::string name){
    playerName = name;
}

void Player::setPlayerBet(int bet){
    currentBet = bet;
}

void Player::setPlayerScore(int score){
    playerScore = score;
}

std::string Player::getPlayerName() {
    return playerName;
}

int Player::getPlayerBet() {
    return currentBet;
}

int Player::getPlayerScore() {
    return playerScore;
}