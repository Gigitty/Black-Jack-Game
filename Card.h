#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>

//Structure for cards
struct Card 
{
  std::string suit;
  std::string face;
  int cardValue;
  int cardPlayStatus;
  bool isAce = false;

}Deck[53];//Array for cards


#endif