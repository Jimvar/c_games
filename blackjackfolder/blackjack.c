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
    int choice, packs, limitcards, played_cards, deck[5][4][14], buffed_mult, all_in; //Choice is for the main menu, deck houses the cards
    long long overallplayed, totalwins, totallost, totalties, moneygained, moneylost; //Stats
    float multiplier, mult_increase = 0.2, mult_double = 0.3, all_in_mult = 0.8, biggestmult; //Combo mechanic
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
        int win, loss, tie;
        while(again==1){

            win = loss = tie = 0;

            game(name, deck, &played_cards, packs, limitcards, &win, &loss, &tie, &money, &multiplier, &overallplayed, &totalwins, &totallost, &totalties, &moneygained, &moneylost, &biggestmult, &mult_increase, &mult_double, &all_in_mult); //Game is played

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
