//main.cpp

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

//Functions

void welcomeScreen ();
char hOSOption(int playerTotal, char hitOrStand);

int main() 
{
  srand(time(NULL));//Random Number Generator Seeded
  string name;//String for Name Input
  
  int playCount = 0;//Counter for initizating player(s)
  int handBet = 0;//How much the player would want to bet
 
  char hitOrStand;//Hit or Stand Option
  char playerChoice;//To End the Game Loop

  bool isValidIn = false;//Limit possible user input
  bool roundOver = false;//Round Over Flag
  bool userQuit = false; //To end the game loop  
  

  deckOfCards();//Initializes the deck


  printf("\033c");//Clears Screen
  welcomeScreen ();//Displays Welcome Screen
  cin >> playCount;//Gets the number of players

  vector <Player> players (playCount);//Creates a vector of players
  Player dealer;//Creates a dealer

  //Loop to get the name of each player
  for(int i = 0; i < playCount; i++) {
    cout << "Please Enter Player " << (i + 1) << "'s Name:" << endl;
    cin >> name;      
    players[i].setPlayerName(name);
  }

  while (!userQuit) {
    
    //Loop to get the bet of each player
    for(int i = 0; i < playCount; i++) {      
      cout << "How much would " << players[i].getPlayerName() << " like to bet? " << flush << endl;
      isValidIn = false;
      
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
    
    //Deals the cards to each player
    for(int i = 0; i < playCount; i++) { 
      players[i].currentHand[0] = dealCard(); 
      players[i].currentHand[1] = dealCard();

      players[i].setHandValue(players[i].currentHand[0].cardValue + players[i].currentHand[1].cardValue);
 
      cout << players[i].getPlayerName() << "'s Cards" << endl;
      displayCard(players[i].currentHand[0]); cout << " & ";  displayCard(players[i].currentHand[1]); cout << endl << endl << endl;
    
    } 
    
    dealer.currentHand[0] = dealCard(); 
    dealer.currentHand[1] = dealCard();

    cout << "House Cards" << endl;
    displayCard(dealer.currentHand[0]); cout << " & X"; cout << endl << endl << endl;  

    //Loop to get the hit or stand option of each player
    for(int i = 0; i < playCount; i++) {
      int x = 2;
      cout << players[i].getPlayerName() << "'s Turn" << endl;
    
      do { 
        hitOrStand = hOSOption(players[i].getHandValue(), hitOrStand);      
        
        isValidIn = false;      
        while(!isValidIn) {
        
          if(hitOrStand == 'h') {                  
            players[i].currentHand[x] = dealCard();
            displayCard(players[i].currentHand[x]); cout << endl;
            players[i].setHandValue(players[i].currentHand[x].cardValue);
            isValidIn = true;
          }
          else if(hitOrStand == 'b') {
            players[i].setBust();
            isValidIn = true;
          }          
          else if(hitOrStand != 's') {
            cout << "Invalid Input. Please Enter H or S." << endl;
          }
          else{
            isValidIn = true;          
          }
        }
        x++;
      } while(hitOrStand == 'h');
    }
    
    //Second Dealer Card is Flipped and more cards are played if necessary
    cout << "House Cards." << endl << endl << endl;

    displayCard(dealer.currentHand[0]); cout << endl;
    displayCard(dealer.currentHand[1]); cout << endl;
    dealer.setHandValue(dealer.currentHand[0].cardValue + dealer.currentHand[1].cardValue);

    //Loop to play the dealer's cards and determine the winners
    while(!roundOver) {
      int x = 2;
      if(dealer.getHandValue() > 21) { //If the dealer busts
        cout << "Congratualtions! The following players have won the round." << endl; 
        
        for(int i = 0; i < playCount; i++) {          
          if(players[i].getBust() == false) {
            cout << players[i].getPlayerName() << endl; 
            players[i].setPlayerScore(players[i].getPlayerScore() + (players[i].getHandValue() * 2));
          }        
          roundOver = true;      
        }
      }
        
      else if(dealer.getHandValue() <= 21) { //If the dealer doesn't bust     
        for(int i = 0; i < playCount; i++) {          
          while(!players[i].getBust()) {  
            
            if(players[i].getHandValue() < dealer.getHandValue()) { 
              cout << players[i].getPlayerName() << ": Lost." << endl;    
              players[i].setBust();
            } 
              
            else if((dealer.getHandValue() == players[i].getHandValue()) && (dealer.getHandValue() > 16)){
              cout << players[i].getPlayerName() << ": Push." << endl;
              players[i].setPlayerScore(players[i].getPlayerScore() + players[i].getHandValue());
              players[i].setBust();
            }   
              
            else if((dealer.getHandValue() < 21) && (dealer.getHandValue() < players[i].getHandValue())){
              dealer.currentHand[x] = dealCard();
              displayCard(dealer.currentHand[x]); cout << endl;
              dealer.setHandValue(dealer.currentHand[x].cardValue);
              x++;
            }
          }
        }
      }
      roundOver = true;
    }
  //Loop Starts Again if player inputs yes
  cout << "Want to play again? (y/n)" << endl;
  cin >> playerChoice;

  if(playerChoice == 'y')
  {
    for(int i = 0; i < playCount; i++) {
      players[i].resetPlayer();
    }
    dealer.resetPlayer();      
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





