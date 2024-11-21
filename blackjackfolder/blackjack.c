#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "savingsystem.h"
#include "printingsystem.h"
#include "cardsystem.h"

int main(){
    first_time_set();
    char name[50];
    int money, seed, choice, deck[4][14];
    int overallplayed, totalwins, totallost, totalties, moneygained, moneylost;

    while(1){
        load_stats(&overallplayed, &totalwins, &totallost, &totalties, &moneygained, &moneylost);
        choice = startupscreen();
        if(choice==1){
            new_game(name, &money, &seed, deck);
        }
        else if(choice==2){
            load_game(name, &money, &seed, deck);
        }
        else if(choice==3){
            leaderboard();
            continue;
        }
        else if(choice==4){
            stats(&overallplayed, &totalwins, &totallost, &totalties, &moneygained, &moneylost);
            continue;
        }
        else if(choice==5){
            return 0;
        }

        srand(seed);
        int bet, won, played_cards = 0, again = 1;

        while(again==1){
            
            do{
                printf("Choose bet(You have %d money): ", money);
                scanf("%d", &bet);
            } while(bet>money || bet<=0);
            money -=bet;
            
            won = game(deck, &played_cards);
            overallplayed++;
            if(won==0){
                printf( RED "You lost %d money!\n" RESET, bet);
                totallost++;
                moneylost += bet;
            }
            else if(won==1){
                printf(GREEN "You won %d money!\n" RESET, bet);
                money += 2*bet;
                totalwins++;
                moneygained += bet;
            }
            else if(won==2){
                printf("You tied!\n");
                money += bet;
                totalties++;
            }
            savegame(name, &money, &seed, deck);
            savestats(&overallplayed, &totalwins, &totallost, &totalties, &moneygained, &moneylost);

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
