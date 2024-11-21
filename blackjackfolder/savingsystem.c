#include <stdio.h>
#include <time.h>
#include "savingsystem.h"

void first_time_set(){
    FILE *fp;

    fp = fopen("savegame.txt", "r");
    if(fp==NULL){
        fp = fopen("savegame.txt", "w");
        fclose(fp);
    }

    fp = fopen("leaderboard.txt", "r");
    if(fp==NULL){
        fp = fopen("leaderboard.txt", "w");
        for(int i = 0; i<10; i++){
            fprintf(fp, "%d\n", 0);
        }
        fclose(fp);
    }

    fp = fopen("stats.txt", "r");
    if(fp==NULL){
        fp = fopen("stats.txt", "w");
        fprintf(fp, "%d %d %d %d %d %d", 0, 0, 0, 0, 0, 0);
        fclose(fp);
    }
}

void new_game(char name[], int *money, int *seed, int deck[][14]){
    FILE *fp;
    fp = fopen("savegame.txt", "w");

    printf("Write your name: ");
    scanf("%49s", name);
    *money = 1000;
    fprintf(fp, "%s %d ", name, *money);
    
    printf("Do you want to manually set a seed or have it random? Press 1 or 2: ");
    int answer;
    do{
        scanf("%d", &answer);
    } while(answer!=1 && answer!=2);
    
    if(answer==1){
        printf("Write your seed: ");
        scanf("%d", &answer);
        *seed = answer;
        fprintf(fp, "%d ", *seed);
    }
    else{
        *seed = time(NULL);
        fprintf(fp, "%d ", *seed);
    }

    for(int i = 0; i<4; i++){
        for(int j = 0; j<14; j++){
            fprintf(fp, "%d ", 0);
            deck[i][j] = 0;
        }
    }
    fclose(fp);
}

void load_game(char name[], int *money, int *seed, int deck[][14]){
    FILE *fp;
    fp = fopen("savegame.txt", "r");
    fscanf(fp, "%s %d %d", name, money, seed);
    for(int i = 0; i<4; i++){
        for(int j = 0; j<14; j++){
            fscanf(fp, "%d", &deck[i][j]);
        }
    }
    fclose(fp);
}

void load_stats(int *overallplayed, int *totalwins, int *totallost, int *totalties, int *moneygained, int *moneylost){
    FILE *fp;
    fp = fopen("stats.txt", "r");
    fscanf(fp, "%d %d %d %d %d %d", overallplayed, totalwins, totallost, totalties, moneygained, moneylost);
    fclose(fp);
}

void leaderboard_save_delete(int money){
    FILE *fp;
    int board[11];

    fp = fopen("leaderboard.txt", "r");
    for(int i = 0; i<10; i++){
        fscanf(fp, "%d", &board[i]);
    }
    fclose(fp);
    board[10] = money;

    for (int i = 0; i < 11 - 1; i++) {
        for (int j = 0; j < 11 - i - 1; j++) {
            if (board[j] < board[j + 1]) {
                int temp = board[j];
                board[j] = board[j + 1];
                board[j + 1] = temp;
            }
        }
    }

    fp = fopen("leaderboard.txt", "w");
    for(int i = 0; i<10; i++){
        fprintf(fp, "%d\n", board[i]);
    }
    fclose(fp);

    fp = fopen("savegame.txt", "w");
    fclose(fp);
}

void savegame(char name[], int *money, int *seed, int deck[][14]){
    FILE *fp;
    fp = fopen("savegame.txt", "w");

    fprintf(fp, "%s %d ", name, *money);
    fprintf(fp, "%d ", *seed);
    for(int i = 0; i<4; i++){
        for(int j = 0; j<14; j++){
            fprintf(fp, "%d ", deck[i][j]);
        }
    }
    fclose(fp);
}

void savestats(int *overallplayed, int *totalwins, int *totallost, int *totalties, int *moneygained, int *moneylost){
    FILE *fp;
    fp = fopen("stats.txt", "w");

    fprintf(fp, "%d %d %d %d %d %d", *overallplayed, *totalwins, *totallost, *totalties, *moneygained, *moneylost);
    fclose(fp);
}
