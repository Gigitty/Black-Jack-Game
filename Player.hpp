#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <vector>

#include "Card.hpp"

class Player{
    std::string playerName;
    int playerScore;
    int currentBet;
    Card currentHand [5];

    public:    

    //Player(std::string new_name, int new_currentBet);    
    void setPlayerName(std::string name);
    std::string getPlayerName();
    void setPlayerBet(int bet);
    int getPlayerBet();
    void setPlayerScore(int score);
    int getPlayerScore();

    
};

#endif