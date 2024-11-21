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

    fp = fopen("savegame.txt", "r");
    if(fp==NULL){
        printf("File not found, exiting...\n");
        exit(EXIT_FAILURE);
    }
    int flag = fscanf(fp, "%c", &c);
    fclose(fp);

    printf("\n /$$$$$$$  /$$                     /$$                                     /$$      \n");
    printf("| $$__  $$| $$                    | $$                                    | $$      \n");
    printf("| $$  \\ $$| $$  /$$$$$$   /$$$$$$$| $$   /$$       /$$  /$$$$$$   /$$$$$$$| $$   /$$\n");
    printf("| $$$$$$$ | $$ |____  $$ /$$_____/| $$  /$$/      |__/ |____  $$ /$$_____/| $$  /$$/\n");
    printf("| $$__  $$| $$  /$$$$$$$| $$      | $$$$$$/        /$$  /$$$$$$$| $$      | $$$$$$/ \n");
    printf("| $$  \\ $$| $$ /$$__  $$| $$      | $$_  $$       | $$ /$$__  $$| $$      | $$_  $$ \n");
    printf("| $$$$$$$/| $$|  $$$$$$$|  $$$$$$$| $$ \\  $$      | $$|  $$$$$$$|  $$$$$$$| $$ \\  $$\n");
    printf("|_______/ |__/ \\_______/ \\_______/|__/  \\__/      | $$ \\_______/ \\_______/|__/  \\__/\n");
    printf("                                             /$$  | $$                              \n");
    printf("                                            |  $$$$$$/                              \n");
    printf("                                             \\______/                               \n");

    printf("Choose:\n");
    printf(GREEN "1. New Game\n");
    flag != -1 ? printf("2. Continue\n") : printf(RED "2. Continue\n");
    printf(GREEN "3. Leaderboard\n" RESET);

    if(flag!=-1){
        do{
            c = getchar();
        } while(c<'1' || c>'3');
    }
    else{
        do{
            c = getchar();
        } while(c!='1' && c!='3');
    }

    return(c - '0');
}

void leaderboard(){
    FILE *fp;
    int board[10];

    fp = fopen("leaderboard.txt", "r");
    if(fp==NULL){
        printf("File not found, exiting...\n");
        exit(EXIT_FAILURE);
    }


    printf("------------------------------------\nLEADERBOARD\n");
    for(int i = 0; i<10; i++){
        fscanf(fp, "%d", &board[i]);
        printf("%2d. %d\n", i+1, board[i]);
    }
    printf("------------------------------------\n");
    fclose(fp);
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

void carddraw(int deck[][14], int hand[][20], int *limit, int *sum, int *played_cards, int *softflag){
    int suit, rank;
    suit = rand()%4;
    rank = rand()%14;
    if(deck[suit][rank]==0){
        deck[suit][rank]++;
        hand[0][*limit] = suit;
        hand[1][*limit] = rank;
        (*limit)++;
        //printf("%d\n", *limit);
        (*sum) = sumcheck(rank, *sum, softflag);
        (*played_cards)++;
        (*played_cards) = card_check(*played_cards, deck);
    }
}
