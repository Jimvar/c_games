#include <stdio.h>
#include <time.h>
#include "savingsystem.h"

void first_time_set(){ //Sets up all the files if the game is for the first time opened
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

void new_game(char name[], long long *money, long long *seed, float *multiplier, int deck[][14]){
    FILE *fp;
    fp = fopen("savegame.txt", "w"); //Open or overwrite all the data inside

    printf("Write your name: ");
    scanf("%49s", name); 
    *money = 1000;
    fprintf(fp, "%s %lld ", name, *money); //Save player name, and give them a standard amount of money
    
    printf("Do you want to manually set a seed or have it random? Press 1 or 2: ");
    long long answer;
    do{
        scanf("%lld", &answer);
    } while(answer!=1 && answer!=2); //Let them choose if the want a specific seed or "random"
    
    if(answer==1){
        printf("Write your seed: ");
        scanf("%lld", &answer);
        *seed = answer;
        fprintf(fp, "%lld ", *seed); //Save their specific seed
    }
    else{
        *seed = time(NULL); //Generate random seed
        fprintf(fp, "%lld ", *seed); //Save random seed
    }

    *multiplier = 1.0; //Give standard multiplier
    fprintf(fp, "%f ", *multiplier); //Save it

    for(int i = 0; i<4; i++){
        for(int j = 0; j<14; j++){
            fprintf(fp, "%d ", 0); //Save the full deck
            deck[i][j] = 0;
        }
    }
    fclose(fp);
}

void load_game(char name[], long long *money, long long *seed, float *multiplier, int deck[][14]){
    FILE *fp;
    fp = fopen("savegame.txt", "r");
    fscanf(fp, "%s %lld %lld %f", name, money, seed, multiplier); 
    for(int i = 0; i<4; i++){
        for(int j = 0; j<14; j++){
            fscanf(fp, "%d", &deck[i][j]); //Load everything
        }
    }
    fclose(fp);
}

void load_stats(long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost){
    FILE *fp;
    fp = fopen("stats.txt", "r");
    fscanf(fp, "%lld %lld %lld %lld %lld %lld", overallplayed, totalwins, totallost, totalties, moneygained, moneylost); //Load everything
    fclose(fp);
}

void leaderboard_save_delete(long long money){
    FILE *fp;
    long long board[11]; //Get leaderboard, with an extra row

    fp = fopen("leaderboard.txt", "r");
    for(int i = 0; i<10; i++){
        fscanf(fp, "%lld", &board[i]); //Read the existing data
    }
    fclose(fp);
    board[10] = money; //Store in the extra row the current run money

    for (int i = 0; i < 11 - 1; i++) {
        for (int j = 0; j < 11 - i - 1; j++) {
            if (board[j] < board[j + 1]) {
                int temp = board[j];
                board[j] = board[j + 1]; //Bubblesort it and kick the lowest in the last place
                board[j + 1] = temp;
            }
        }
    }

    fp = fopen("leaderboard.txt", "w");
    for(int i = 0; i<10; i++){
        fprintf(fp, "%lld\n", board[i]); //Save only the top 10
    }
    fclose(fp);

    fp = fopen("savegame.txt", "w"); //Delete savefile
    fclose(fp);
}

void savegame(char name[], long long *money, long long *seed, float *multiplier, int deck[][14]){
    FILE *fp;
    fp = fopen("savegame.txt", "w");

    fprintf(fp, "%s %lld ", name, *money);
    fprintf(fp, "%lld %f ", *seed, *multiplier);
    for(int i = 0; i<4; i++){
        for(int j = 0; j<14; j++){
            fprintf(fp, "%d ", deck[i][j]); //Save the data
        }
    }
    fclose(fp);
}

void save_stats(long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost){
    FILE *fp;
    fp = fopen("stats.txt", "w");

    fprintf(fp, "%lld %lld %lld %lld %lld %lld", *overallplayed, *totalwins, *totallost, *totalties, *moneygained, *moneylost); //Save the stats
    fclose(fp);
}
