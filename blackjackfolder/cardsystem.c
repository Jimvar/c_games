#include <stdio.h>
#include <stdlib.h>
#include "printingsystem.h"
#include "cardsystem.h"

int card_check(int played_cards, int deck[][14]){
    if(played_cards==56){
        for(int i = 0 ; i<4; i++){
            for(int j = 0; j<14; j++){
                deck[i][j] = 0;
            }
        }
        printf("Resuffled cards!\n\n");
        return 0;
    }
    return played_cards;
}

char symbolmatcher(int symbol){
    if(symbol == 0) return '1';
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
        return sum + 1;
    }
    else if(symbol==13){
        *flag = 1;
        now = 1;
    }

    if(symbol == 0) symbol = 1;
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
                return sum + 1;
            }
            else{
                return sum + 11;
            }
        }
        else{
            if(sum + symbol > 21){
                *flag = 0;
                return sum - 10 + symbol;
            }
        }
    }
    else{
        return sum + symbol;
    }
}

int game(int deck[][14], int *played_cards){
    int setup = 0;
    int dealerhand[2][20] = {0};
    int playerhand[2][20] = {0};
    int dealerlimit = 0, playerlimit = 0; 
    int dealersum = 0, playersum = 0, softflagdealer = 0, softflagplayer = 0;
    
    
    do{ //Dealer
        carddraw(deck, dealerhand, &dealerlimit, &dealersum, played_cards, &softflagdealer);
    } while(dealerlimit<=1);
    
    do{ //Player
        carddraw(deck, playerhand, &playerlimit, &playersum, played_cards, &softflagplayer);
    } while(playerlimit<=1);
    
    int start = playersum;
    int player_turn = 0;
    int choice;
    while(player_turn==0){
        printf("Dealer\n"); 
        draw_cards(dealerlimit, dealerhand);
        printf("Sum: %d\n", dealersum);
        printf("Player\n");
        draw_cards(playerlimit, playerhand);
        printf("Sum: %d\n", playersum);
        if(playersum>=21 || dealersum>=21){
            break;
        }
        
        do{
            printf("Choose action: 1. Draw 2. Stand 3. View Deck: ");
            scanf("%d", &choice);
        } while(choice<=0 || choice>=4);
        
        if(choice==1){
            do{ //Player
                carddraw(deck, playerhand, &playerlimit, &playersum, played_cards, &softflagplayer);
            } while(start==playersum);
            start = playersum;
        }
        else if(choice==2){
            player_turn++;
        }
        else{
            print_deck(deck);
        }
    }

    if(playersum>21){
        return 0;
    }
    else{
        if(dealersum>=17){
            if(playersum>dealersum){
                return 1;
            }
            else if(playersum==dealersum){
                return 2;
            }
            else{
                return 0;
            }
        }
        else{
            do{ //Dealer
                carddraw(deck, dealerhand, &dealerlimit, &dealersum, played_cards, &softflagdealer);
            } while(dealersum<17);

            printf("Dealer\n"); 
            draw_cards(dealerlimit, dealerhand);
            printf("Sum: %d\n", dealersum);
            printf("Player\n");
            draw_cards(playerlimit, playerhand);
            printf("Sum: %d\n", playersum);

            if(dealersum>21){
                return 1;
            }
            else if(playersum>dealersum){
                return 1;
            }
            else if(playersum==dealersum){
                return 2;
            }
            else{
                return 0;
            }

        }
    }
    
}