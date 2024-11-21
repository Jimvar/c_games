#include <stdio.h>
#include <stdlib.h>
#include "printingsystem.h"
#include "cardsystem.h"

const char *colors[] = {
    GREEN,
    RED,
    BBLU,
    BMAG,
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
        printf("File not found, exiting...\n");
        exit(EXIT_FAILURE);
    }
    int flag = fscanf(fp, "%c", &c);
    fclose(fp);

    printf(BORE "Choose:\n");
    printf(GREEN "1. New Game\n");
    flag != -1 ? printf("2. Continue\n") : printf(RED "2. Continue\n");
    printf(GREEN "3. Leaderboard\n4. Stats\n5. Quit\n" PLAYER);

    if(flag!=-1){
        do{
            c = getchar();
        } while(c<'1' || c>'5');
    }
    else{
        do{
            c = getchar();
        } while(c!='1' && c!='3' && c!='4' && c!='5');
    }

    return(c - '0');
}

void leaderboard(){
    FILE *fp;
    long long board[10];

    fp = fopen("leaderboard.txt", "r");
    if(fp==NULL){
        printf("File not found, exiting...\n");
        exit(EXIT_FAILURE);
    }


    printf(BLUEISH "------------------------------------\nLEADERBOARD\n" RESET);
    for(int i = 0; i<10; i++){
        fscanf(fp, "%lld", &board[i]);
        printf("%s%2d. %s%lld\n", BLUEISH, i+1, YELLOW, board[i]);
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

    for(int k = 0; k<4; k++){
        for(int i = 0; i<14; i++){
            printf("%s ---  ", colors[k]);
        }
        putchar('\n');
        for(int i = 0; i<3; i++){
            for(int j = 0; j<14; j++){
                printf("| ");
                if(i==1){
                    deck[k][j] ?  putchar('-')  : printf("%c", symbolmatcher(j));
                }
                else{
                    putchar(' ');
                }
                printf(" | ");
            }
            putchar('\n');
        }
        for(int i = 0; i<14; i++){
            printf(" ---  ");
        }
        putchar('\n');
    }
    putchar('\n');
    printf(RESET);
}

void draw_cards(int how_many, int hand[][20]){
    int start = 0;
    int temp = start;

    for(int i = 0; i<how_many; i++){
        printf("%s ---  ", colors[hand[0][temp]]);
        temp++;
    }
    putchar('\n');
    for(int i = 0; i<3; i++){
        temp = start;
        for(int j = 0; j<how_many; j++){
            printf("%s| ", colors[hand[0][temp]]);
            if(i==1){
                printf("%c", symbolmatcher(hand[1][temp]));
            }
            else{
                putchar(' ');
            }
            printf(" | ");
            temp++;
        }
        putchar('\n');
    }
    temp = start;
    for(int i = 0; i<how_many; i++){
        printf("%s ---  ", colors[hand[0][temp]]);
        temp++;
    }
    printf(RESET "\n");
}
