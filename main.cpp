//Aly Abousen

//Libraries that are needed for the code
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <ctime>
//#include<unistd.h>
using namespace std;


//Constants 
const int DEFAULT_SCORE = 1000;

//Structure for cards
struct Card 
{
  string suit;
  string face;
  int cardValue;
  int cardPlayStatus;
  

}Deck[53];//Array for cards

//Functions

void welcomeScreen ();
void deckOfCards();
void displayCard(Card &card);
Card dealCard();

//Booleans

bool userQuit = false;




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

  int currentScore = DEFAULT_SCORE;//Initialize Score
  int handBet = 0;//How much the player would want to bet
  char hitOrStand;//Hit or Stand Option
  char playerChoice;//To End the Game Loop
  bool isBust = false;//Indicate if player loss resulted from a Bust    


  deckOfCards();//Initializes the deck



  welcomeScreen ();//Displays Welcome Screen
  cin >> name;
 
  while (!userQuit)
  {

  cout << "How much would " << name << " like to bet? " << flush << endl;
  cout << "$"; cin >> handBet; 
  currentScore -= handBet;
  printf("\033c");//Clears Screen
  cout << "You have $" << currentScore << " left"<< endl;

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

//Nested if statemenst so the player can keep hitting if desired or stand
  playerTotal = playerCard1.cardValue + playerCard2.cardValue;

  if (playerTotal > 21) {

    cout << "Over 21. Bust." << endl;
    isBust = true;
    hitOrStand = 's';   
  }
  else if (playerTotal == 21) {

    cout << "Black Jack!" << endl;
    hitOrStand = 's';
  }
  else if (playerTotal < 21) {

    cout << "Would You like to Hit or Stand? (H/S)" << endl;
    cin >> hitOrStand;
  }

  if(hitOrStand == 'h') {

    playerCard3 = dealCard();
    displayCard(playerCard3); cout << endl;
    playerTotal += playerCard3.cardValue;

    if(playerTotal > 21) {

      cout << "Over 21. Bust." << endl;
      isBust = true;
      hitOrStand = 's';
    }
    else if(playerTotal == 21) {

      cout << "21. Black Jack!." << endl;
      hitOrStand = 's';
    }
    else if(playerTotal < 21) {

      cout << "Would You like to Hit or Stand? (H/S)" << endl;
      cin >> hitOrStand;
    } 
  }   

  if(hitOrStand == 'h') {

    playerCard4 = dealCard();
    displayCard(playerCard4); cout << endl;
    playerTotal += playerCard4.cardValue;

    if(playerTotal > 21) {
      cout << "Over 21. Bust." << endl;
      isBust = true;
      hitOrStand = 's';
    }
    else if(playerTotal == 21) {
      cout << "21. Black Jack!" << endl;
      hitOrStand = 's';
    }
    else if(playerTotal < 21) {
      cout << "Would You like to Hit or Stand? (H/S)" << endl;
      cin >> hitOrStand;
    }
  }

  if(hitOrStand == 'h') { 

    playerCard5 = dealCard();
    displayCard(playerCard5); cout << endl;
    playerTotal += playerCard5.cardValue;

    if(playerTotal > 21) {
      cout << "Over 21. Bust." << endl;
      isBust = true;
      hitOrStand = 's';
    }
    else if(playerTotal == 21) {
      cout << "21. Black Jack!" << endl;
    }
    else if(playerTotal < 21) {
          
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
  cout << "Please Enter Your Name:" << endl;
  
}//end of welcomeScreen

//Function initializes deck by looping and placing the arrays into Deck[i]

void deckOfCards()
{
  string face [13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
  string suit [4] = {"Spades", "Clubs", "Hearts", "Diamnonds"};
  int cardValue [13] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
  int cardPlayStatus[3] = {0, 1, 2}; 

  int suitIndex = 0;

  for(int i = 0; i < 52; i++)
  {
		Deck[i].face = face[i % 13];
		Deck[i].suit = suit[suitIndex];
		Deck[i].cardValue = cardValue[i % 13];
		Deck[i].cardPlayStatus = 0;
		if ((i + 1) % 13 == 0)
			suitIndex++;
  }

  for (int x = 0; x < 600; x++)
	{
		int a = rand() % 52;
		int b = rand() % 52;
		
		Deck[52].face = Deck[a].face;
		Deck[52].suit = Deck[a].suit;
		Deck[52].cardValue = Deck[a].cardValue;
		Deck[52].cardPlayStatus = Deck[a].cardPlayStatus;

	  Deck[a].face = Deck[b].face;
		Deck[a].suit = Deck[b].suit;
		Deck[a].cardValue = Deck[b].cardValue;
		Deck[a].cardPlayStatus = Deck[b].cardPlayStatus;

		Deck[b].face = Deck[52].face;
		Deck[b].suit = Deck[52].suit;
		Deck[b].cardValue = Deck[52].cardValue;
		Deck[b].cardPlayStatus = Deck[52].cardPlayStatus;
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


void displayCard(Card &card)
{
  if (card.cardValue == 11)
  {
    card.cardValue = 1;
  }

  cout << card.face << " of " << card.suit;
  card.cardPlayStatus = 1;

}//end of displayCard