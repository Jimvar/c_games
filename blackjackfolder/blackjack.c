#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "savingsystem.h"
#include "printingsystem.h"
#include "cardsystem.h"

int main(){
    first_time_set();
    char name[50];
    int money, seed, choice;
    FILE *fp;
    int deck[4][14];

    while(1){
        choice = startupscreen();
        if(choice==3){
            leaderboard();
            continue;
        }
        else if(choice==1){
            new_game(name, &money, &seed, deck);
        }
        else if(choice==2){
            load_game(name, &money, &seed, deck);
        }
        srand(seed);
        int played_cards = 0;
        int bet, won;
        
        int again = 1;
        while(again==1){
            
            do{
                printf("Choose bet(You have %d money): ", money);
                scanf("%d", &bet);
            } while(bet>money || bet<=0);
            money -=bet;
            
            won = game(deck, &played_cards);
            
            if(won==0){
                printf( RED "You lost %d money!\n" RESET, bet);
            }
            else if(won==1){
                printf(GREEN "You won %d money!\n" RESET, bet);
                money += 2*bet;
            }
            else if(won==2){
                printf("You tied!\n");
                money += bet;
            }
            savegame(name, &money, &seed, deck);

            if(money==0){
                printf(RED "You lost completely!\n" RESET);
                leaderboard_save_delete(money);
                break;
            }

            do{
                printf(GREEN "Choose what to do next:\n1. Play again?\n2.Quit\n3.End game and put your money in the leaderboard\n" RESET);
                scanf("%d", &again);
            } while(again<1 || again>3);

            if(again==2){
                return 0;
            }
            else if(again == 3){
                leaderboard_save_delete(money);
            }
        }
    }
}
