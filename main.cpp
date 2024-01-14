//Aly Abousen

//Libraries that are needed for the code
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <ctime>
#include <vector>

#include "Card.hpp"
#include "Player.hpp"

//#include<unistd.h>
using namespace std;


//Constants 
const int DEFAULT_SCORE = 1000;

//Functions

void welcomeScreen ();
char hOSOption(int playerTotal, char hitOrStand);

int currentScore = DEFAULT_SCORE;//Initialize Score
int handBet = 0;//How much the player would want to bet


int main() 
{
  srand(time(NULL));//Random Number Generator Seeded
  string name;//String for Name Input

  //Players Cards (Only Up to Five Cards in Black Jack)
  Card playerCard1;
  Card playerCard2; 
  Card playerCard3;
  Card playerCard4;
  Card playerCard5;

  //Dealers Cards
  Card dealerCard1;
  Card dealerCard2;
  Card dealerCard3;
  Card dealerCard4;
  Card dealerCard5;

  //Card Value Totals
  int playerTotal = 0;
  int dealerTotal = 0;

  int playCount = 0;//Counter for initizating player(s)
 
  char hitOrStand;//Hit or Stand Option
  char playerChoice;//To End the Game Loop

  bool isBust = false;//Indicate if player loss resulted from a Bust 
  bool isValidIn = false;//Limit possible user input
  bool userQuit = false;   


  deckOfCards();//Initializes the deck


  printf("\033c");//Clears Screen
  welcomeScreen ();//Displays Welcome Screen
  cin >> playCount;

  vector <Player> players (playCount);



  for(int i = 0; i < playCount; i++) {
    cout << "Please Enter Player" << (i + 1) << "'s Name:" << endl;
    cin >> name;      
    players[i].setPlayerName(name);
  }

  while (!userQuit) {
    for(int i = 0; i < playCount; i++){

      cout << "How much would " << players[i].getPlayerName() << " like to bet? " << flush << endl;
      while(!isValidIn){

        cout << "$"; cin >> handBet; 
        cin.clear(); cin.ignore(1000, '\n');

      if((handBet > players[i].getPlayerScore()) || (handBet == 0)) {
        cout << "You cannot bet that amount..." << endl;
      }
      else {        
        isValidIn = true;
      }
    }    
    players[i].setPlayerBet(handBet);
    players[i].setPlayerScore(players[i].getPlayerScore() - players[i].getPlayerBet());
    cout << "You have $" << players[i].getPlayerScore() << " left"<< endl;
  }

  printf("\033c");
  
  

  playerTotal = 0;
  dealerTotal = 0;
  isBust = false;

  //Makes the members of specific Deck[x] belong to  variable

  playerCard1 = dealCard(); 
  playerCard2 = dealCard();
  dealerCard1 = dealCard();
  dealerCard2 = dealCard();
    
  //Displays Cards
  
  cout <<"Your Cards" << endl;
  displayCard(playerCard1); cout << " & ";  displayCard(playerCard2); cout << endl << endl << endl;

  cout << "House Cards" << endl;
  displayCard(dealerCard1); cout << " & X"; cout << endl << endl << endl; 

  playerTotal = playerCard1.cardValue + playerCard2.cardValue;

  hitOrStand = hOSOption(playerTotal, hitOrStand);

  isValidIn = false;
  while(!isValidIn) {

    if(hitOrStand == 'h') {

      playerCard3 = dealCard();
      displayCard(playerCard3); cout << endl;
      playerTotal += playerCard3.cardValue;
      hitOrStand = hOSOption(playerTotal, hitOrStand); 
      isValidIn = true;
    }
    else if(hitOrStand != 's') {
      cout << "Invalid Input. Please Enter H or S." << endl;
    }
  }

  isValidIn = false;
  while(!isValidIn) {

    if(hitOrStand == 'h') {

      playerCard4 = dealCard();
      displayCard(playerCard4); cout << endl;
      playerTotal += playerCard4.cardValue;
      hitOrStand = hOSOption(playerTotal, hitOrStand);
      isValidIn = true;
    }
    else if(hitOrStand == 'b') {
      isBust = true;
      isValidIn = true;
    }
    else if(hitOrStand != 's') {
      cout << "Invalid Input. Please Enter H or S." << endl;
    }
  }

  isValidIn = false;
  while(!isValidIn){

    if(hitOrStand == 'h') { 

      playerCard5 = dealCard();
      displayCard(playerCard5); cout << endl;
      playerTotal += playerCard5.cardValue;
      hitOrStand = hOSOption(playerTotal, hitOrStand);
      isValidIn = true;
    }
    else if(hitOrStand == 'b') {
      isBust = true;
      isValidIn = true;
    }
    else if(hitOrStand != 's') {
      cout << "Invalid Input. Please Enter H or S." << endl;
    }
  }
  
  if(isBust == true){
    cout << "House Wins...";
  }
  else{

  // Second Dealer Card is Flipped and more cards are played if necessary
    cout << "House Cards." << endl << endl << endl;

    displayCard(dealerCard1); cout << endl;
    displayCard(dealerCard2); cout << endl;
    dealerTotal = dealerCard1.cardValue + dealerCard2.cardValue;


    if(dealerTotal > 21) {
      cout << "Player Wins!" << endl;
      currentScore += 2 * handBet;
    }
    else if((dealerTotal > playerTotal) && (dealerTotal <= 21)) {
      cout << "House Wins..." << endl;     
    }
    else if ((dealerTotal == playerTotal) && (dealerTotal > 16)){
      cout << "Push" << endl;
      currentScore += handBet;
    }
    else if((dealerTotal < 21) && (dealerTotal < playerTotal)) {

      dealerCard3 = dealCard();
      displayCard(dealerCard3); cout << endl;
      dealerTotal += dealerCard3.cardValue;

      if(dealerTotal > 21) {
        cout << "Player Wins!" << endl;
        currentScore += 2 * handBet;
  
      }
      else if((dealerTotal > playerTotal) && (dealerTotal <= 21)) {
        cout << "House Wins..." << endl;
        
      }
      else if ((dealerTotal == playerTotal) && (dealerTotal > 16)){
        cout << "Push" << endl;
        currentScore += handBet;

      }
      else if((dealerTotal < 21) && (dealerTotal < playerTotal)) {
        dealerCard4 = dealCard();
        displayCard(dealerCard4); cout << endl;
        dealerTotal += dealerCard4.cardValue;

        if(dealerTotal > 21) {
          cout << "Player Wins!" << endl;
          currentScore += 2 * handBet;
    
        }
        else if((dealerTotal > playerTotal) && (dealerTotal <= 21)) {
          cout << "House Wins..." << endl;
    
        }
        else if ((dealerTotal == playerTotal) && (dealerTotal > 16)){
          cout << "Push" << endl;
          currentScore += handBet;
    
        }
        else if((dealerTotal < 21) && (dealerTotal < playerTotal)) {
          dealerCard5 = dealCard();
          displayCard(dealerCard5); cout << endl;
          dealerTotal += dealerCard5.cardValue;

          if(dealerTotal > 21) {
            cout << "Player Wins!" << endl;
            currentScore += 2 * handBet;
      
          }
          else if((dealerTotal > playerTotal) && (dealerTotal <= 21)) {
            cout << "House Wins..." << endl;
      
          }
          else if ((dealerTotal == playerTotal) && (dealerTotal > 16)){
            cout << "Push" << endl;
            currentScore += handBet;
      
          }
          else if((dealerTotal < 21) && (dealerTotal < playerTotal)) {
            cout << "Player Wins!" << endl;
            currentScore += 2 * handBet;
          }
        }
      }
    }
  }
//Loop Starts Again if player inputs yes
  cout << "Does " << name << " want to play again? (y/n)" << endl;
  cin >> playerChoice;

  if(playerChoice == 'y')
  {
    printf("\033c");//Clears output
    continue;
  }
  else if (playerChoice == 'n')
  {
    userQuit = true;//Loop stops if player inputs no
  }
}
return 0;
}

void welcomeScreen ()
{
  cout << "$$$$$   $$     $$$$$$   $$$$$$$   $$   $$      $$$$$$$  $$$$$$   $$$$$$   $$   $$" << endl;
  cout << "$$  $$  $$     $$  $$   $$        $$  $$          $$    $$  $$   $$       $$  $$ " << endl;
  cout << "$$$$$   $$     $$$$$$   $$        $$$$            $$    $$$$$$   $$       $$$$" << endl;
  cout << "$$  $$  $$     $$  $$   $$        $$  $$       $$ $$    $$  $$   $$       $$  $$" << endl;
  cout << "$$$$$   $$$$$  $$  $$   $$$$$$$   $$   $$      $$$$$    $$  $$   $$$$$$   $$   $$"<< endl << endl << endl;

  cout << "---------------------------------------------------------------------------------------" << endl << endl;
  cout <<"Welcome to The Royal House Casino \n---------------------------------\nBlackJack Table" << endl << endl << endl;
  cout <<"How many players?" << endl;
  
}//end of welcomeScreen





