#include <stdio.h>
#include <stdlib.h>
#include "printingsystem.h"
#include "cardsystem.h"

int card_check(int played_cards, int deck[][4][14], int limitcards){
    if(played_cards==limitcards){
        for(int k = 0; k < limitcards / 56; k++){
            for(int i = 0 ; i<4; i++){
                for(int j = 0; j<14; j++){
                    deck[k][i][j] = 0; //Resuffles cards
                }
            }
        }
        printf("Resuffled cards!\n\n");
        return 0;
    }
    return played_cards; //If there are still cards to be played, it returns back
}

char symbolmatcher(int symbol){
    if(symbol == 0) return '1'; //Matches the number(index) generated to the appropriate symbol
    else if(symbol == 1) return '2';
    else if(symbol == 2) return '3';
    else if(symbol == 3) return '4';
    else if(symbol == 4) return '5';
    else if(symbol == 5) return '6';
    else if(symbol == 6) return '7';
    else if(symbol == 7) return '8';
    else if(symbol == 8) return '9';
    else if(symbol == 9) return 'T';
    else if(symbol == 10) return 'J';
    else if(symbol == 11) return 'Q';
    else if(symbol == 12) return 'K';
    else if(symbol == 13) return 'A';
}

int sumcheck(int symbol, int sum, int *flag){
    int now = 0;

    if(symbol==13 && *flag==1){
        return sum + 1; //If it stumbles upon another ace, then it counts it as 1
    }
    else if(symbol==13){
        *flag = 1; //Notifies that we have a potential soft mode
        now = 1; //Notifies that the current card is an ace
    }

    if(symbol == 0) symbol = 1; //Makes the number(index) into the appropriate value it holds in the game
    else if(symbol == 1) symbol = 2;
    else if(symbol == 2) symbol = 3;
    else if(symbol == 3) symbol = 4;
    else if(symbol == 4) symbol = 5;
    else if(symbol == 5) symbol = 6;
    else if(symbol == 6) symbol = 7;
    else if(symbol == 7) symbol = 8;
    else if(symbol == 8) symbol = 9;
    else if(symbol == 9) symbol = 10;
    else if(symbol == 10) symbol = 10;
    else if(symbol == 11) symbol = 10;
    else if(symbol == 12) symbol = 10;;

    if(*flag==1){
        if(now==1){
            if(sum + 11 > 21){
                *flag = 0; 
                return sum + 1; //If the current card is an ace, but it can't initiate a soft mode, it gets counted as 1
            }
            else{
                return sum + 11; //The current card is an ace, and it initiates soft mode
            }
        }
        else{
            if(sum + symbol > 21){
                *flag = 0;
                return sum - 10 + symbol; //A previous card was an ace, but the soft mode is broken, so we remove the +10 it gave, and also add the new number
            }
        }
    }
    else{
        return sum + symbol; //We don't need to check if soft mode is broken since we don't have it, so we just add the new number
    }
}

void carddraw(int deck[][4][14], int hand[][20], int *limit, int *sum, int *played_cards, int *softflag, int limitcards, int packs){
    int suit, rank, whichdeck;
    whichdeck = rand()%packs;
    suit = rand()%4; //Generates number 0-3
    rank = rand()%14; //Generates number 0-13
    if(deck[whichdeck][suit][rank]==0){ //Works as a map. If we play a card, then we cross it off by saying its a one
        deck[whichdeck][suit][rank]++; //Cross off
        hand[0][*limit] = suit; 
        hand[1][*limit] = rank; //Storing the card drawn to the corresponding hand
        (*limit)++; //How many cards we need to draw on the scren
        (*sum) = sumcheck(rank, *sum, softflag); //Get the value of cards
        (*played_cards)++; 
        (*played_cards) = card_check(*played_cards, deck, limitcards); //See if we need to resuffle the cards; if we do, it resuffles them
    }
}

int game(char name[], int deck[][4][14], int *played_cards, int double_down, int *flagdoubling, int packs, int limitcards){
    int dealerhand[2][20] = {0}; //Stores cards drawn by dealer
    int playerhand[2][20] = {0}; //Stores cards drawn by player
    int dealerlimit = 0, playerlimit = 0; //How many cards we need to draw
    int dealersum = 0, playersum = 0, softflagdealer = 0, softflagplayer = 0; //Value of cards for each entity, and a flag for if they have soft mode
    *flagdoubling = 0; //Haven't yet doubled
    
    do{ //Dealer
        carddraw(deck, dealerhand, &dealerlimit, &dealersum, played_cards, &softflagdealer, limitcards, packs);
    } while(dealerlimit<=1); //Draws two cards
    
    do{ //Player
        carddraw(deck, playerhand, &playerlimit, &playersum, played_cards, &softflagplayer, limitcards, packs);
    } while(playerlimit<=1); //Draws two cards
    

    int player_turn = 0; //Initialize flag for when we quit from the player mode
    int choice, cap = playerlimit; //Choice is for the menu later on, cap is initialized to the current cards the player has, to stop a loop later on

    while(player_turn==0){ //Check the flag
        printf(BORE "-------------------------------------\n");
        printf(DEALER "Dealer\n"); 
        draw_cards(dealerlimit, dealerhand); //Prints the two cards the dealer has
        printf(DEALER "Sum: %d\n", dealersum);
        printf(BORE "-------------------------------------\n");
        printf(PLAYER "%s\n", name); 
        draw_cards(playerlimit, playerhand); //Prints the two cards the player has
        printf(PLAYER "Sum: %d\n", playersum);
        printf(BORE "-------------------------------------\n");

        if(playersum>=21 || *flagdoubling==1){ //If the player gets burned or draws a blackjack or has doubled down, break and go to the dealer
            break;
        }
        
        if(double_down){
            do{
                printf(PLAYER "Choose action: 1. Draw 2. Stand 3. View Deck %s4. Double Down:%s ", GREEN, PLAYER);
                scanf("%d", &choice);
            } while(choice<=0 || choice>=5); //Include doubling
            if(choice==4){
                choice = 1; //To draw card
                *flagdoubling = 1; //Notify main() of doubling
            }
        }
        else{
            do{
                printf(PLAYER "Choose action: 1. Draw 2. Stand 3. View Deck %s4. Double Down:%s ", RED, PLAYER);
                scanf("%d", &choice); 
            } while(choice<=0 || choice>=4); //Exclude doubling
        }
        
        if(choice==1){
            do{ //Player
                carddraw(deck, playerhand, &playerlimit, &playersum, played_cards, &softflagplayer, limitcards, packs);
            } while(playerlimit<=cap); //Stops the loop when a card is drawn
            cap++; //Raise the cap if the player wants to search again
        }
        else if(choice==2){
            player_turn++; //Stand and go to dealer
        }
        else{
            print_deck(deck, packs); //Prints deck
        }
    }

    if(playersum>21){
        return 0; //If they burned, automatic win for dealer
    }
    else{
        if(dealersum>=17){
            if(playersum>dealersum){
                return 1; //Lost since he can't draw above than 17
            }
            else if(playersum==dealersum){
                return 2; //Tie
            }
            else{
                return 0; //Dealer has won
            }
        }
        else{
            do{ //Dealer
                carddraw(deck, dealerhand, &dealerlimit, &dealersum, played_cards, &softflagdealer, limitcards, packs);
            } while(dealersum<17); //Draw until limit

            printf(BORE "-------------------------------------\n");
            printf(DEALER "Dealer\n"); 
            draw_cards(dealerlimit, dealerhand); //Draws the dealer's cards
            printf(DEALER "Sum: %d\n", dealersum);
            printf(BORE "-------------------------------------\n");
            printf(PLAYER "%s\n", name);
            draw_cards(playerlimit, playerhand); //Draws the player's cards
            printf(PLAYER "Sum: %d\n", playersum);
            printf(BORE "-------------------------------------\n");

            if(dealersum>21){
                return 1; //Dealer burned, player wins
            }
            else if(playersum>dealersum){
                return 1; //Player won
            }
            else if(playersum==dealersum){
                return 2; //Tie
            }
            else{
                return 0; //Player lost
            }

        }
    }
    
}