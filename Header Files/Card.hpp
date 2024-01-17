//Card.hpp
#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <vector>

//Structure for cards
struct Card {
  std::string suit;
  std::string face;
  int cardValue;
  int cardPlayStatus;
  bool isAce;

};

void deckOfCards();
void displayCard(Card &card);
Card dealCard();

#endif