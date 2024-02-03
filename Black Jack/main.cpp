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
#include <Windows.h>

#include "Card.hpp"
#include "Player.hpp"

//#include<unistd.h>
using namespace std;

//Functions

void welcomeScreen();
char hOSOption(int player, char hitOrStand);

int main()
{
    srand(time(NULL));//Random Number Generator Seeded
    string name;//String for Name Input

    int playCount = 0;//Counter for initiating player(s)
    int handBet = 0;//How much the player would want to bet

    char hitOrStand = '\0';//Hit or Stand Option
    char playerChoice = '\0';//To End the Game Loop

    bool roundOver = false;//Round Over Flag
    bool userQuit = false; //To end the game loop  


    deckOfCards();//Initializes the deck


    printf("\033c");//Clears Screen
    welcomeScreen();//Displays Welcome Screen
    cin >> playCount;//Gets the number of players
    int ogPlayCnt = playCount; //Maintains original playcount
    Player dealer;//Creates a dealer
    dealer.resetPlayer();
    vector <Player> players(playCount);//Creates a vector of players
    

    //Loop to get the name of each player
    for (int i = 0; i < playCount; i++) { 
        Player* plyr = &players[i];
        
        cout << "Please Enter Player " << (i + 1) << "'s Name:" << endl;
        cin >> name;
        plyr->setPlayerName(name);
    }

    while (!userQuit) {

        //Loop to get the bet of each player
        for (int i = 0; i < playCount; i++) { 
            Player* plyr = &players[i];
            cout << "How much would " << plyr->getPlayerName() << " like to bet? " << flush << endl;
            bool isValidIn = false;

            while (!isValidIn) {

                cout << "$"; cin >> handBet;
                cin.clear(); cin.ignore(1000, '\n');

                if ((handBet > plyr->getPlayerScore()) || (handBet == 0)) {
                    cout << "You cannot bet that amount..." << endl;
                }
                else {
                    isValidIn = true;
                }
            }
            plyr->setPlayerBet(handBet);
            plyr->setPlayerScore(plyr->getPlayerScore() - plyr->getPlayerBet());
            cout << "You have $" << plyr->getPlayerScore() << " left" << endl;
        }

        Sleep(1000);

        printf("\033c");

        //Deals the cards to each player
        for (int i = playCount; i > 0; i--) { 
            Player* plyr = &players[playCount - i];
            
            plyr->currentHand[0] = dealCard();
            plyr->currentHand[1] = dealCard();

            plyr->setHandValue(plyr->currentHand[0].cardValue + plyr->currentHand[1].cardValue);

            cout << plyr->getPlayerName() << "'s Cards" << endl;
            displayCard(plyr->currentHand[0]); cout << " & ";  displayCard(plyr->currentHand[1]); cout << endl << endl << endl;

            if (plyr->currentHand[0].cardValue == plyr->currentHand[1].cardValue) {
                cout << "Would you like to split?" << endl;
                
                bool isValidIn = false;
                while (!isValidIn) {
                    cin >> playerChoice;
                    if (playerChoice == 'y')
                    {
                        playCount += 1;
                        players.insert(players.end() - i , *plyr);
                        players[playCount - i].setSplit();

                        players[playCount - i].currentHand[1] = dealCard();

                        plyr->setPlayerScore(plyr->getPlayerScore() - plyr->getPlayerBet());
                        displayCard(players[playCount - i].currentHand[0]); cout << " & ";  displayCard(players[playCount - i].currentHand[1]);
                        isValidIn = true;
                    }
                    else if (playerChoice == 'n')
                    {
                        isValidIn = true;
                    }
                }
            }
        }

        dealer.currentHand[0] = dealCard();
        dealer.currentHand[1] = dealCard();

        cout << "House Cards" << endl;
        displayCard(dealer.currentHand[0]); cout << " & X"; cout << endl << endl << endl;

        //Loop to get the hit or stand option of each player
        for (int i = 0; i < playCount; i++) { 
            Player* plyr = &players[i];
            
            int x = 2;
            cout << plyr->getPlayerName() << "'s Turn" << endl;

            for (int j = 0; j < x; j++) { //For every card in player hand
                if ((plyr->currentHand[j].isAce) && (plyr->getHandValue() > 21)) { //Check for Ace to decide whether Ace is 1 or 11
                    plyr->setHandValue(-10);//By default Ace is assumed 11 and changed to 1
                }
                else {
                    continue;
                }
            }

            do {
                hitOrStand = hOSOption(plyr->getHandValue(), hitOrStand);

                bool isValidIn = false;
                while (!isValidIn) {
                    switch (hitOrStand) {
                    case 'h':
                    case 'H':
                        plyr->currentHand[x] = dealCard();
                        displayCard(plyr->currentHand[x]); cout << endl;
                        plyr->setHandValue(plyr->currentHand[x].cardValue);
                        isValidIn = true;
                        x++;
                        break;
                    
                    case 'b':
                        plyr->setBust();
                        isValidIn = true;
                        break;
                    
                    case 's':
                    case 'S':
                        isValidIn = true;
                        break;

                    default:
                        cout << "Invalid Input. Please Enter H or S." << endl;
                    }
                }                
            } while (hitOrStand == 'h' || hitOrStand == 'H');
        }//End of Player Selection Loop

        //Second Dealer Card is Flipped and more cards are played if necessary
        cout << "House Cards." << endl << endl << endl;

        displayCard(dealer.currentHand[0]); cout << endl;
        Sleep(1000);
        displayCard(dealer.currentHand[1]); cout << endl;
        dealer.setHandValue(dealer.currentHand[0].cardValue + dealer.currentHand[1].cardValue);
        Sleep(1000);
        
        for (int i = 0; i < playCount; i++) { 
            Player* plyr = &players[i];
            
            if (!plyr->getBust()) {
                roundOver = false;
                break;
            }
            else if (i < playCount - 1) {
                continue;
            }
            roundOver = true;
        }
                                
        while (!roundOver) {// Loop to play the dealer's cards and determine the winners
            int x = 2;
            if (dealer.getHandValue() > 21) { //If the dealer busts
                cout << "Congratualtions! The following players have won the round." << endl;

                for (int i = 0; i < playCount; i++) { 
                    Player* plyr = &players[i];
                    
                    if (!plyr->getBust() && !plyr->getSplit()) {
                        cout << plyr->getPlayerName() << endl;
                        plyr->setPlayerScore(plyr->getPlayerScore() + (plyr->getPlayerBet() * 2));
                    }
                    else if (!plyr->getBust() && plyr->getSplit()) {
                        cout << plyr->getPlayerName() << endl;
                        players[i - 1].setPlayerScore(players[i - 1].getPlayerScore() + (plyr->getPlayerBet() * 2));
                    }
                    roundOver = true;
                }
            }

            else if (dealer.getHandValue() <= 21) { //If the dealer doesn't bust     
                for (int i = 0; i < playCount; i++) { 
                    Player* plyr = &players[i];
                    
                    if (!plyr->getBust()) {

                        if (plyr->getHandValue() < dealer.getHandValue()) {
                            cout << plyr->getPlayerName() << ": Lost." << endl;
                            plyr->setBust();
                            Sleep(1000);
                        }

                        else if ((dealer.getHandValue() == plyr->getHandValue()) && (dealer.getHandValue() > 16)) {
                            cout << plyr->getPlayerName() << ": Push." << endl;
                            if (!plyr->getBust() && !plyr->getSplit()) {
                                plyr->setPlayerScore(plyr->getPlayerScore() + plyr->getPlayerBet());
                                plyr->setBust();
                            }
                            else if (!plyr->getBust() && plyr->getSplit()) {
                                players[i - 1].setPlayerScore(players[i - 1].getPlayerScore() + plyr->getPlayerBet());
                                plyr->setBust();
                            }
                            Sleep(1000);
                        }

                        else if ((dealer.getHandValue() < 21) && (dealer.getHandValue() < plyr->getHandValue())) {
                            dealer.currentHand[x] = dealCard();
                            displayCard(dealer.currentHand[x]); cout << endl;
                            dealer.setHandValue(dealer.currentHand[x].cardValue);
                            x++;
                            Sleep(1000);
                        }
                    }
                }
            }

            for (int i = 0; i < playCount; i++) { 
                Player* plyr = &players[i];

                if (!plyr->getBust()) {
                    break;
                }
                else if(i < playCount -1){
                    continue;
                }
                roundOver = true;
            }
        }
        //Loop Starts Again if player inputs yes
        cout << "Want to play again? (y/n)" << endl;
        

        bool isValidIn = false;

        while (!isValidIn) {
            cin >> playerChoice;
            if (playerChoice == 'y')
            {
                for (int i = 0; i < playCount; i++) { 
                    Player* plyr = &players[i];
                    plyr->resetPlayer();
                }
                dealer.resetPlayer();
                playCount = ogPlayCnt;
                printf("\033c");//Clears output
                isValidIn = true;
            }
            else if (playerChoice == 'n')
            {
                userQuit = true;//Loop stops if player inputs no
                isValidIn = true;
            }
        }
    }
    return 0;
}

void welcomeScreen()
{
    cout << "$$$$$   $$     $$$$$$   $$$$$$$   $$   $$      $$$$$$$  $$$$$$   $$$$$$   $$   $$" << endl;
    cout << "$$  $$  $$     $$  $$   $$        $$  $$          $$    $$  $$   $$       $$  $$ " << endl;
    cout << "$$$$$   $$     $$$$$$   $$        $$$$            $$    $$$$$$   $$       $$$$" << endl;
    cout << "$$  $$  $$     $$  $$   $$        $$  $$       $$ $$    $$  $$   $$       $$  $$" << endl;
    cout << "$$$$$   $$$$$  $$  $$   $$$$$$$   $$   $$      $$$$$    $$  $$   $$$$$$   $$   $$" << endl << endl << endl;

    cout << "---------------------------------------------------------------------------------------" << endl << endl;
    cout << "Welcome to The Royal House Casino \n---------------------------------\nBlackJack Table" << endl << endl << endl;
    cout << "How many players?" << endl;

}//end of welcomeScreen

char hOSOption(int player, char hitOrStand) {

	if (player > 21) {

		cout << "Over 21. Bust." << endl;
		hitOrStand = 'b';
	}
	else if (player == 21) {

		cout << "Black Jack!" << endl;
		hitOrStand = 's';
	}
	else if (player < 21) {

		cout << "Would You like to Hit or Stand? (H/S)" << endl;
		cin >> hitOrStand;
	}

	return hitOrStand;
}//end of hOSOption



