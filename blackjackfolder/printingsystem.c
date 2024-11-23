#include <stdio.h>
#include <stdlib.h>
#include "printingsystem.h"
#include "cardsystem.h"
#include "savingsystem.h"

const char *colors[] = {
    CARDGRAY,
    CARDRED,
    CARDGREEN,
    CARDYELLOW,
    RESET
};

int startupscreen(){
    char c;
    FILE *fp;

    printf("\n %s/$$$$$$$  /$$                     /$$                                     %s/$$%s      \n",BBLU, RED, RESET);
    printf("%s| $$__  $$| $$                    | $$                                    %s| $$%s      \n",BBLU, RED, RESET);
    printf("%s| $$  \\ $$| $$  /$$$$$$   /$$$$$$$| $$   /$$       %s/$$  /$$$$$$   /$$$$$$$| $$   /$$%s\n",BBLU, RED, RESET);
    printf("%s| $$$$$$$ | $$ |____  $$ /$$_____/| $$  /$$/      %s|__/ |____  $$ /$$_____/| $$  /$$/%s\n",BBLU, RED, RESET);
    printf("%s| $$__  $$| $$  /$$$$$$$| $$      | $$$$$$/        %s/$$  /$$$$$$$| $$      | $$$$$$/%s \n",BBLU, RED, RESET);
    printf("%s| $$  \\ $$| $$ /$$__  $$| $$      | $$_  $$       %s| $$ /$$__  $$| $$      | $$_  $$%s \n",BBLU, RED, RESET);
    printf("%s| $$$$$$$/| $$|  $$$$$$$|  $$$$$$$| $$ \\  $$      %s| $$|  $$$$$$$|  $$$$$$$| $$ \\  $$%s\n",BBLU, RED, RESET);
    printf("%s|_______/ |__/ \\_______/ \\_______/|__/  \\__/      %s| $$ \\_______/ \\_______/|__/  \\__/%s\n",BBLU, RED, RESET);
    printf("                                             %s/$$  | $$                              \n", RED);
    printf("                                            |  $$$$$$/                              \n");
    printf("                                             \\______/%s                               \n", RESET);


    fp = fopen("savegame.txt", "r");
    if(fp==NULL){
        printf("File not found, exiting...\n"); //Checks if file is deleted
        exit(EXIT_FAILURE);
    }
    int flag = fscanf(fp, "%c", &c); //Checks if the file is empty; if empty it will print continue as red
    fclose(fp);

    printf(BORE "Choose:\n");
    printf(GREEN "1. New Game\n");
    flag != -1 ? printf("2. Continue\n") : printf(RED "2. Continue\n"); //Draws depending on if a save exists
    printf(GREEN "3. Leaderboard\n4. Stats\n5. Achievements\n6. Reset stats\n7. Quit\n" PLAYER);

    if(flag!=-1){
        do{
            c = getchar();
        } while(c<'1' || c>'7'); //Everything is available
    }
    else{
        do{
            c = getchar();
        } while(c!='1' && c!='3' && c!='4' && c!='5' && c!='6' && c!='7'); //Everything except continue
    }

    return(c - '0');
}

void leaderboard(){
    FILE *fp;
    long long board[10];
    char names[10][50];

    fp = fopen("leaderboard.txt", "r");
    if(fp==NULL){
        printf("File not found, exiting...\n"); //Checks if file is deleted
        exit(EXIT_FAILURE);
    }


    printf(BLUEISH "------------------------------------\nLEADERBOARD\n" RESET);
    for(int i = 0; i<10; i++){
        fscanf(fp, "%s %lld", names[i], &board[i]); //Loads with the values
        printf("%s%2d. %s %s%lld\n", BLUEISH, i+1, names[i], YELLOW, board[i]); //Prints out the values
    }
    printf(BLUEISH"------------------------------------\n" RESET);
    fclose(fp);
}

void stats(long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost, float *biggestmult) {
    printf("%s------------------------------------------------\n", PINK);
    printf("|                 Stats Page                   |\n");
    printf("------------------------------------------------\n");
    printf("| Overall games played:  %s%21lld%s |\n", BORE, *overallplayed, PINK);
    printf("| Total wins:            %s%21lld%s |\n", GREEN, *totalwins, PINK);
    printf("| Total losses:          %s%21lld%s |\n", RED, *totallost, PINK);
    printf("| Total ties:            %s%21lld%s |\n", BORE, *totalties, PINK);
    printf("| Money gained:          %s%21lld%s |\n", YELLOW, *moneygained, PINK);
    printf("| Money lost:            %s%21lld%s |\n", RED, *moneylost, PINK);
    printf("| Biggest multiplier:    %s%21.1f%s |\n", RED, *biggestmult, PINK);
    printf("------------------------------------------------%s\n", RESET);
}

void achievements(int achievements_track[]){
    printf("%s------------------------------------------------\n", PINK);
    printf("|              Achievements Page               |\n");
    printf("------------------------------------------------\n");
    printf("| %sGet 10k money%s                                |\n", achievements_track[0] ? GREEN : RED, PINK);
    printf("| %sGet 1m money%s                                 |\n", achievements_track[1] ? GREEN : RED, PINK);
    printf("| %sGet a multiplier of x4.0 or better%s           |\n", achievements_track[2] ? GREEN : RED, PINK);
    printf("| %sPlay 1000 hands%s                              |\n", achievements_track[3] ? GREEN : RED, PINK);
    printf("| %sWin 1000 hands%s                               |\n", achievements_track[4] ? GREEN : RED, PINK);
    printf("| %sBreak the bank (and the game)%s                |\n", achievements_track[5] ? GREEN : RED, PINK);
    printf("------------------------------------------------%s\n", RESET);
}

void achieve_check(int achievements_track[], long long *money, float *multiplier, long long *overallplayed, long long *totalwins){
    if(achievements_track[0]==0 && *money >= 10000){
        printf(YELLOW "Congrats on getting over 10k money!\n");
        printf("New functionality for custom games unlocked! You can now choose a specific amount of money for the start, up to 10k!\n" PLAYER);
        achievements_track[0]++;
    }
    if(achievements_track[1]==0 && *money >= 100000){
        printf(YELLOW "Congrats on getting over 1m money!\n");
        printf("New functionality for custom games unlocked! You can now choose a specific amount of money for the start, up to 1m!\n" PLAYER);
        achievements_track[1]++;
    }
    if(achievements_track[2]==0 && *multiplier >= 4.0){
        printf(YELLOW "Congrats on getting over x4.0 multiplier!\n");
        printf("New functionality for custom games unlocked! You can now choose a more buffed version of multipliers!\n" PLAYER);
        achievements_track[2]++;
    }
    if(achievements_track[3]==0 && *overallplayed >= 1000){
        printf(YELLOW "Congrats on playing 1000 hands!\n");
        printf("New functionality for custom games unlocked! You can now choose a specific seed to play on!\n" PLAYER);
        achievements_track[3]++;
    }
    if(achievements_track[4]==0 && *totalwins >= 1000){
        printf(YELLOW "Congrats on winning 1000 hands!\n");
        printf("New functionality for custom games unlocked! You can now choose to play with more decks simultaneously, upping the difficulty!\n" PLAYER);
        achievements_track[4]++;
    }
    if(achievements_track[5]==0 && *money < 0){
        printf(YELLOW "Congrats on.... breaking the game?\n");
        printf("Either you messed with the savefile or you actually did that. Respect either way!\n" PLAYER);
        achievements_track[5]++;
        *money = 0;
    }

}

void reset_prompt(){
    printf("Do you want to reset:\n1. Leaderboard\n2. Stats\n3. Achievements\n4. Everything\n");
    int choice, verify;
    do{
        scanf("%d", &choice);
    } while(choice<1 || choice>4);
    printf("Are you sure? Press 1 for yes, 0 for no: ");
    do{
        scanf("%d", &verify);
    } while(verify != 1 && verify != 0);
    if(verify){
        resetchoice(choice);
    }
}

void print_deck(int deck[][4][14], int packs){
    putchar('\n');
    for(int l = 0; l < packs; l++){
        printf("Deck %d:\n", l+1);
        for(int k = 0; k<4; k++){ //Print every suit
            for(int i = 0; i<14; i++){ //Top part, print every card of the suit, using the correct color
                printf("%s ---  ", colors[k]);
            }
            putchar('\n');
            for(int i = 0; i<3; i++){ //Middle part
                for(int j = 0; j<14; j++){ //The central part of the card
                    printf("| ");
                    if(i==1){
                        deck[l][k][j] ? putchar('-') : printf("%c", symbolmatcher(j)); //When the middle is found, print - if already played; else print the number/symbol
                    }
                    else{
                        putchar(' ');
                    }
                    printf(" | ");
                }
                putchar('\n');
            }
            for(int i = 0; i<14; i++){
                printf(" ---  "); //Bottom part
            }
            putchar('\n');
        }
    }
    putchar('\n');
    printf(RESET);
}

void draw_cards(int how_many, int hand[][20]){

    for(int i = 0; i<how_many; i++){ //Top part
        printf("%s ---  ", colors[hand[0][i]]);
    }

    putchar('\n');
    for(int i = 0; i<3; i++){ //Middle part
        for(int j = 0; j<how_many; j++){ //All the cards
            printf("%s| ", colors[hand[0][j]]);
            if(i==1){
                printf("%c", symbolmatcher(hand[1][j])); //Print the correct symbol when the time comes
            }
            else{
                putchar(' ');
            }
            printf(" | ");
        }
        putchar('\n');
    }

    for(int i = 0; i<how_many; i++){
        printf("%s ---  ", colors[hand[0][i]]); //Bottom part
    }
    printf(RESET "\n");

}
