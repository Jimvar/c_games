#include <stdio.h>
#include <stdlib.h>
#include "printingsystem.h"
#include "cardsystem.h"

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
    printf(GREEN "3. Leaderboard\n4. Stats\n5. Quit\n" PLAYER);

    if(flag!=-1){
        do{
            c = getchar();
        } while(c<'1' || c>'5'); //Everything is available
    }
    else{
        do{
            c = getchar();
        } while(c!='1' && c!='3' && c!='4' && c!='5'); //Everything except continue
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

void stats(long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost) {
    printf("%s------------------------------------------------\n", PINK);
    printf("|                 Stats Page                   |\n");
    printf("------------------------------------------------\n");
    printf("| Overall games played:  %s%21lld%s |\n", BORE, *overallplayed, PINK);
    printf("| Total wins:            %s%21lld%s |\n", GREEN, *totalwins, PINK);
    printf("| Total losses:          %s%21lld%s |\n", RED, *totallost, PINK);
    printf("| Total ties:            %s%21lld%s |\n", BORE, *totalties, PINK);
    printf("| Money gained:          %s%21lld%s |\n", YELLOW, *moneygained, PINK);
    printf("| Money lost:            %s%21lld%s |\n", RED, *moneylost, PINK);
    printf("------------------------------------------------%s\n", RESET);
}

void print_deck(int deck[][14]){
    putchar('\n');

    for(int k = 0; k<4; k++){ //Print every suit
        for(int i = 0; i<14; i++){ //Top part, print every card of the suit, using the correct color
            printf("%s ---  ", colors[k]);
        }
        putchar('\n');
        for(int i = 0; i<3; i++){ //Middle part
            for(int j = 0; j<14; j++){ //The central part of the card
                printf("| ");
                if(i==1){
                    deck[k][j] ? putchar('-') : printf("%c", symbolmatcher(j)); //When the middle is found, print - if already played; else print the number/symbol
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
