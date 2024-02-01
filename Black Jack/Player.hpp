//Player.hpp
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <map>

#include "Card.hpp"

class Player {
    std::string name;
    int score;
    int bet;
    int handValue;
    bool isBust;
    bool isSplit;

public:
    std::map<int, Card> currentHand;
    std::map<int, Card> splitHand;

    void setPlayerName(const std::string& playerName);
    std::string getPlayerName() const;
    void setPlayerBet(int currentBet);
    int getPlayerBet() const;
    void setPlayerScore(int playerScore);
    int getPlayerScore() const;
    void setHandValue(int value);
    int getHandValue() const;
    void setBust();
    bool getBust() const;
    void setSplit();
    bool getSplit() const;
    void resetPlayer();

};

#endif