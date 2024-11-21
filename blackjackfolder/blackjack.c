#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "savingsystem.h"
#include "printingsystem.h"
#include "cardsystem.h"

int main(){
    first_time_set();
    char name[50];
    long long money, seed;
    int choice, deck[4][14];
    long long overallplayed, totalwins, totallost, totalties, moneygained, moneylost;
    float multiplier;

    while(1){
        load_stats(&overallplayed, &totalwins, &totallost, &totalties, &moneygained, &moneylost);
        choice = startupscreen();
        if(choice==1){
            new_game(name, &money, &seed, &multiplier, deck);
        }
        else if(choice==2){
            load_game(name, &money, &seed, &multiplier, deck);
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
        int won, played_cards = 0, again = 1;
        long long bet;

        while(again==1){
            
            do{
                printf("%sChoose bet(You have %s%lld%s money, and multiplier %sx%.1f%s): ", PLAYER, YELLOW , money, PLAYER, RED, multiplier, PLAYER);
                scanf("%lld", &bet);
            } while(bet>money || bet<=0);
            money -=bet;
            
            won = game(deck, &played_cards);
            overallplayed++;
            if(won==0){
                printf("%sYou lost %s%lld%s money and your x%.1f multiplier!%s\n", RED , YELLOW, bet, RED, multiplier, RESET);
                multiplier = 1.0;
                totallost++;
                moneylost += bet;
            }
            else if(won==1){
                multiplier += 0.2;
                printf("%sYou won %s%lld%s money and a boost to your multiplier!%s\n", GREEN , YELLOW, (long long)(bet*multiplier), GREEN, RESET);
                money += 2*bet*multiplier;
                totalwins++;
                moneygained += bet;
            }
            else if(won==2){
                printf(GREEN "You tied!\n" RESET);
                money += bet;
                totalties++;
            }
            savegame(name, &money, &seed, &multiplier ,deck);
            save_stats(&overallplayed, &totalwins, &totallost, &totalties, &moneygained, &moneylost);

            if(money==0){
                printf(RED "You lost completely!\n" RESET);
                leaderboard_save_delete(money);
                break;
            }

            do{
                printf(PLAYER "Choose what to do next:\n1. Play again?\n2. Quit\n3. End game and put your money in the leaderboard\n");
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
