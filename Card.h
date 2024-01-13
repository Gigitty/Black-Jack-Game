#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>

//Structure for cards
struct Card 
{
  std::string suit;
  std::string face;
  int cardValue;
  int cardPlayStatus;
  bool isAce = false;

}Deck[53];//Array for cards

void deckOfCards();
void displayCard(Card &card);
Card dealCard();

//Function returns a card with members to variable 
Card dealCard()
{
  bool uniqueCard = false;
  int i = 0;

  while(uniqueCard == false){

    i = rand() % 52;
    if (Deck[i].cardPlayStatus == 0) {
      uniqueCard = true;
    }    
    else{
      uniqueCard = false;
    }
  }
  
  Deck[i].cardPlayStatus = 1;
  return Deck[i];
}//end of dealCard


void displayCard(Card &card) {
  std::cout << card.face << " of " << card.suit;
}//end of displayCard

char hOSOption(int playerTotal, char hitOrStand) {

  if (playerTotal > 21) {

    std::cout << "Over 21. Bust." << std::endl;    
    hitOrStand = 'b';   
  }
  else if (playerTotal == 21) {

    std::cout << "Black Jack!" << std::endl;
    hitOrStand = 's';
  }
  else if (playerTotal < 21) {

    std::cout << "Would You like to Hit or Stand? (H/S)" << std::endl;
    std::cin >> hitOrStand;
  }

  return hitOrStand;
}

#endif