#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "savingsystem.h" //Includes everything file-related
#include "printingsystem.h" //Includes printing
#include "cardsystem.h" //Includes the logic for the cards

int main(){
    first_time_set(); //Makes sure every file is available; if not it makes them
    char name[50]; //Stores the name of the player
    long long money, seed; //They are made long long to increase range
    int choice, packs, limitcards, played_cards, deck[5][4][14], buffed_mult; //Choice is for the main menu, deck houses the cards
    long long overallplayed, totalwins, totallost, totalties, moneygained, moneylost; //Stats
    float multiplier, mult_increase = 0.2, mult_double = 0.3, biggestmult; //Combo mechanic
    int achievements_track[6];

    while(1){
        load_stats(&overallplayed, &totalwins, &totallost, &totalties, &moneygained, &moneylost, &biggestmult); //Loading before entering the menu
        load_achievements(achievements_track);
        choice = startupscreen(); //Displays the main menu with the 5 choices and waits for response
        if(choice==1){
            new_game(name, &money, &seed, &multiplier, &buffed_mult, deck, &packs, &limitcards, &played_cards, achievements_track); //Makes a new save file(overwriting anything before), and fills it up, as well with the variables
        }
        else if(choice==2){
            load_game(name, &money, &seed, &multiplier, &buffed_mult, deck, &packs, &limitcards, &played_cards); //Gets the existing savefile and loads the variables with the info
        }
        else if(choice==3){
            leaderboard(); //Prints out the leaderboard file
            continue; //Hops back to the main menu
        }
        else if(choice==4){
            stats(&overallplayed, &totalwins, &totallost, &totalties, &moneygained, &moneylost, &biggestmult); //Displays the stats from all the playthroughs
            continue; //Hops back to the main menu
        }
        else if(choice==5){
            achievements(achievements_track, &overallplayed, &totalwins);
            continue; //Hops back to the main menu
        }
        else if(choice==6){
            reset_prompt();
            continue; //Hops back to the main menu
        }
        else if(choice==7){
            return 0; //Ends the game
        }

        srand(seed); //Setting up the RNG with the seed
        int won, again = 1; //won houses what happened in the game, again continues until the player wants to exit or end the playthrough

        if(buffed_mult==2){
            mult_increase = 0.5;
            mult_double = 0.8;
        }
        else if(buffed_mult==1){
            mult_increase = 0.2;
            mult_double = 0.3;
        }

        long long bet; //houses the bet, made long long since money is also long long
        int double_down, flagdoubling = 0; //Flag for if the can double down or not, and flag for if they did double down or not

        while(again==1){
            
            do{
                printf("%sChoose bet(You have %s%lld%s money, and multiplier %sx%.1f%s):%s ", PLAYER, YELLOW , money, PLAYER, RED, multiplier, PLAYER, YELLOW);
                scanf("%lld", &bet);
            } while(bet>money || bet<=0); //Waits for input of player, and makes sure he doesn't give a false bet
            money -=bet; //The bet gets withdrawn from the balance
            
            if(money>=bet){
                double_down = 1; //They can double_down
            }
            else{
                double_down = 0; //They can't double_down
            }

            won = game(name, deck, &played_cards, double_down, &flagdoubling, packs, limitcards); //Game is played
            overallplayed++; //Stat counter
            if(flagdoubling){ //They doubled
                money -=bet; //The extra bet gets withdrawn from the balance
                bet *= 2; //Doubles reward
            }

            if(won==0){
                printf("%sYou lost %s%lld%s money and your x%.1f multiplier!%s\n", RED , YELLOW, bet, RED, multiplier, RESET); 
                multiplier = 1.0; //Resets multiplier
                totallost++; //Stat counter
                moneylost += bet; //Stat counter
            }
            else if(won==1){
                printf("%sYou won %s%lld%s money and a boost to your multiplier!%s\n", GREEN , YELLOW, (long long)(bet*multiplier), GREEN, RESET);
                money += 2*bet*multiplier; //Awards player with the amount withdrawn, the bet, plus what the multiplier gives
                flagdoubling ? (multiplier += mult_double) : (multiplier += mult_increase); //If they doubled down, they get extra multiplier; else standard
                totalwins++; //Stat counter
                moneygained += bet; //Stat counter
            }
            else if(won==2){
                printf(GREEN "You tied!\n" RESET);
                money += bet; //Gives back the money withdrawn
                totalties++; //Stat counter
            }

            if(multiplier > biggestmult){
                biggestmult = multiplier;
            }

            savegame(name, &money, &seed, &multiplier, &buffed_mult, deck, &packs, &limitcards, &played_cards); //Saves the current state of the game
            save_stats(&overallplayed, &totalwins, &totallost, &totalties, &moneygained, &moneylost, &biggestmult); //Saves the stats
            achieve_check(achievements_track, &money, &multiplier, &overallplayed, &totalwins);
            save_achievements(achievements_track);

            if(money==0){
                printf(RED "You lost completely!\n" RESET);
                leaderboard_save_delete(money); //Ends the game, and goes back to main menu
                break;
            }

            do{
                printf(PLAYER "%s, choose what to do next:\n1. Play again?\n2. Quit\n3. End game and put your money in the leaderboard\n", name);
                scanf("%d", &again);
            } while(again<1 || again>3); //Asks what the player wants to do

            if(again==2){
                return 0; //Exits the game
            }
            else if(again == 3){
                leaderboard_save_delete(money); //Ends the game, saves the money to leaderboard, and goes back to main menu
            }
        }
    }
}
