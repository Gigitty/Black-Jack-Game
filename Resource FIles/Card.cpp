//Card.cpp
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <vector>

#include "Card.hpp"

//Function initializes deck by looping and placing the arrays into Deck[i]

Card Deck[53];

void deckOfCards()
{
  std::string face [13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
  std::string suit [4] = {"Spades", "Clubs", "Hearts", "Diamnonds"};
  int cardValue [13] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
 // int cardPlayStatus[3] = {0, 1, 2}; 

  int suitIndex = 0;

  for(int i = 0; i < 52; i++) {

		Deck[i].face = face[i % 13];
		Deck[i].suit = suit[suitIndex];
		Deck[i].cardValue = cardValue[i % 13];
		Deck[i].cardPlayStatus = 0;
    Deck[i].isAce = false;

		if ((i + 1) % 13 == 0){
      Deck[i].isAce = true;
			suitIndex++;
    }
  }

  for (int x = 0; x < 600; x++)
	{
		int a = rand() % 52;
		int b = rand() % 52;
		
		Deck[52].face = Deck[a].face;
		Deck[52].suit = Deck[a].suit;
		Deck[52].cardValue = Deck[a].cardValue;
		Deck[52].cardPlayStatus = Deck[a].cardPlayStatus;
    Deck[52].isAce = Deck[a].isAce;

	  Deck[a].face = Deck[b].face;
		Deck[a].suit = Deck[b].suit;
		Deck[a].cardValue = Deck[b].cardValue;
		Deck[a].cardPlayStatus = Deck[b].cardPlayStatus;
    Deck[a].isAce = Deck[b].isAce;

		Deck[b].face = Deck[52].face;
		Deck[b].suit = Deck[52].suit;
		Deck[b].cardValue = Deck[52].cardValue;
		Deck[b].cardPlayStatus = Deck[52].cardPlayStatus;
    Deck[b].isAce = Deck[52].isAce;
  }
}//end of deckOfCards


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