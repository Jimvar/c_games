#include <stdio.h>
#include <stdlib.h>
#include "printingsystem.h"
#include "cardsystem.h"

long long read_number() {
    long long number = 0;

    char c = getchar();

    while (!(c >= '0' && c <= '9')) {
        c = getchar();
    }

    while (c >= '0' && c <= '9') {
        int digit = c - '0';
        number = number * 10 + digit;
        c = getchar();
    }

    if(c=='k' || c=='K') number *= 1000;
    else if(c=='m' || c=='M') number *= 1000000;
    else if(c=='b' || c=='B') number *= 1000000000;

    return number;
}

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
    else if(symbol == 12) symbol = 10;

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

int game(char name[], int deck[][4][14], int *played_cards, int packs, int limitcards, int *win, int *loss, int *tie, long long *money, float *multiplier, long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost, float *biggestmult, float *mult_increase, float *mult_double, float *all_in_mult){

    int dealerhand[2][20] = {0}; //Stores cards drawn by dealer
    int playerhand[2][20] = {0}; //Stores cards drawn by player
    int dealersnapshot[3][10] = {0};
    int playersnapshot[3][10] = {0};
    int can_split = 0, snapshotplacedealer = -1, snapshotplaceplayer = -1;

    int dealerlimit = 0, playerlimit = 0; //How many cards we need to draw
    int dealersum = 0, playersum = 0, softflagdealer = 0, softflagplayer = 0; //Value of cards for each entity, and a flag for if they have soft mode
    
    int player_turn = 0; //Initialize flag for when we quit from the player mode
    int choice = 0, cap; //Choice is for the menu later on, cap is initialized to the current cards the player has, to stop a loop later on
    long long bet;
    int all_in, double_down, flagdoubling = 0, split;


    do{
        printf("%sChoose bet(You have %s%lld%s money, and multiplier %sx%.1f%s):%s ", PLAYER, YELLOW , *money, PLAYER, RED, *multiplier, PLAYER, YELLOW);
        bet = read_number();
    } while(bet>*money || bet<=0); //Waits for input of player, and makes sure he doesn't give a false bet
    *money -= bet; //The bet gets withdrawn from the balance
    
    if(*money == 0){
        all_in = 1;
        printf("Brave for you to go all in, good luck!\n");
    }
    else{
        all_in = 0;
    }

    if(*money>=bet){
        double_down = 1; //They can double_down
        split = 1;
    }
    else{
        double_down = 0; //They can't double_down
        split = 0;
    }

    while(player_turn==0){ //Check the flag

        choice = 0;

        while(dealerlimit<=1){ //Dealer
            carddraw(deck, dealerhand, &dealerlimit, &dealersum, played_cards, &softflagdealer, limitcards, packs);
        }//Draws two cards
        
        while(playerlimit<=1){ //Player
            carddraw(deck, playerhand, &playerlimit, &playersum, played_cards, &softflagplayer, limitcards, packs);
        }
        
        cap = playerlimit;

        printf(BORE "-------------------------------------\n");
        printf(DEALER "Dealer\n"); 
        draw_cards(dealerlimit, dealerhand); //Prints the two cards the dealer has
        printf(DEALER "Sum: %d\n", dealersum);
        printf(BORE "-------------------------------------\n");
        printf(PLAYER "%s\n", name); 
        draw_cards(playerlimit, playerhand); //Prints the two cards the player has
        printf(PLAYER "Sum: %d\n", playersum);
        printf(BORE "-------------------------------------\n");

        if(playersum>=21 || flagdoubling==1){ //If the player gets burned or draws a blackjack or has doubled down, break and go to the dealer
            player_turn++;
        }

        if(playerhand[1][0] == playerhand[1][1] && playerlimit == 2 && split) can_split = 1;
        else can_split = 0;
        
        while(player_turn == 0 && choice <= 0 || choice >= 6 || (choice == 4 && double_down == 0) || (choice == 5 && can_split == 0)){
            printf(PLAYER "Choose action: 1. Draw 2. Stand 3. View Deck %s4. Double Down %s5. Split:%s ", double_down ? GREEN : RED, can_split ? GREEN : RED, PLAYER);
            scanf("%d", &choice);
        } //Include doubling

        if(choice==4){
            choice = 1; //To draw card
            flagdoubling = 1; //Notify main() of doubling
        }

        if(choice == 5){
            snapshotplacedealer = 0;
            dealersnapshot[0][snapshotplacedealer] = dealerhand[0][0];
            dealersnapshot[1][snapshotplacedealer] = dealerhand[1][0];
            snapshotplacedealer++;
            dealersnapshot[0][snapshotplacedealer] = dealerhand[0][1];
            dealersnapshot[1][snapshotplacedealer] = dealerhand[1][1];
            dealersnapshot[2][snapshotplacedealer] = dealersum;
            snapshotplacedealer++;
            dealerlimit = 0;
            dealersum = 0;

            snapshotplaceplayer = 0;
            playersnapshot[0][snapshotplaceplayer] = playerhand[0][1];
            playersnapshot[1][snapshotplaceplayer] = playerhand[1][1];
            playersnapshot[2][snapshotplaceplayer] = playersum;
            snapshotplaceplayer++;
            playerlimit = 1;
            playersum = playersum / 2;

            *money -= bet;
            if(*money>=bet){
                double_down = 1; //They can double_down
                split = 1;
            }
            else{
                double_down = 0; //They can't double_down
                split = 0;
            }

            continue;
        }

        if(choice==1){
            do{ //Player
                carddraw(deck, playerhand, &playerlimit, &playersum, played_cards, &softflagplayer, limitcards, packs);
            } while(playerlimit<=cap); //Stops the loop when a card is drawn//Raise the cap if the player wants to search again
        }
        else if(choice==2){
            player_turn++; //Stand and go to dealer
        }
        else if(choice==3){
            print_deck(deck, packs); //Prints deck
        }

        if(player_turn){
            if(playersum>21){
                (*loss)++;//If they burned, automatic win for dealer
            }
            else{
                if(dealersum>=17){
                    if(playersum>dealersum){
                        (*win)++; //Lost since he can't draw above than 17
                    }
                    else if(playersum==dealersum){
                        (*tie)++;//Tie
                    }
                    else{
                        (*loss)++;//Dealer has won
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
                        (*win)++;//Dealer burned, player wins
                    }
                    else if(playersum>dealersum){
                        (*win)++;//Player won
                    }
                    else if(playersum==dealersum){
                        (*tie)++;//Tie
                    }
                    else{
                        (*loss)++; //Player lost
                    }
                }
            }

            overallplayed++; //Stat counter
            if(flagdoubling){ //They doubled
                money -=bet; //The extra bet gets withdrawn from the balance
                bet *= 2; //Doubles reward
            }

            if(*loss){
                printf("%sYou lost %s%lld%s money and your x%.1f multiplier!%s\n", RED , YELLOW, bet, RED, *multiplier, RESET); 
                *multiplier = 1.0; //Resets multiplier
                *totallost++; //Stat counter
                *moneylost += bet; //Stat counter
                *loss = 0;
            }
            else if(*win){
                printf("%sYou won %s%lld%s money and a boost to your multiplier!%s\n", GREEN , YELLOW, (long long)(bet*(*multiplier)), GREEN, RESET);
                *money += 2*bet*(*multiplier); //Awards player with the amount withdrawn, the bet, plus what the multiplier gives
                flagdoubling ? (*multiplier += *mult_double) : (*multiplier += *mult_increase); //If they doubled down, they get extra multiplier; else standard
                if(all_in){
                    printf(YELLOW "Since you went all in, you get an extra boost to your multiplier as a treat!\n" RESET);
                    *multiplier += *all_in_mult;
                }
                *totalwins++; //Stat counter
                *moneygained += bet; //Stat counter
                *win = 0;
            }
            else if(*tie){
                printf(GREEN "You tied!\n" RESET);
                *money += bet; //Gives back the money withdrawn
                *totalties++; //Stat counter
                *tie = 0;
            }

            if(*multiplier > *biggestmult){
                *biggestmult = *multiplier;
            }

            if(snapshotplaceplayer>0){
                player_turn = 0;
                snapshotplacedealer--;
                dealersum = dealersnapshot[2][snapshotplacedealer];
                dealerhand[1][1] = dealersnapshot[1][snapshotplacedealer];
                dealerhand[0][1] = dealersnapshot[0][snapshotplacedealer];
                snapshotplacedealer--;
                dealerhand[1][0] = dealersnapshot[1][snapshotplacedealer];
                dealerhand[0][0] = dealersnapshot[0][snapshotplacedealer];
                snapshotplacedealer--;
                dealerlimit = 2;

                snapshotplaceplayer--;
                playersum = playersnapshot[2][snapshotplaceplayer] / 2;
                playerhand[0][0] = playersnapshot[0][snapshotplaceplayer];
                playerhand[1][0] = playersnapshot[1][snapshotplaceplayer];
                playerlimit = 1;
            }
        }
    }
}