#include <stdio.h>
#include <time.h>
#include "savingsystem.h"
#include "printingsystem.h"
#include "cardsystem.h"

void first_time_set(){ //Sets up all the files if the game is for the first time opened
    FILE *fp;

    fp = fopen("savegame.txt", "r");
    if(fp==NULL){
        fp = fopen("savegame.txt", "w");
    }
    fclose(fp);

    fp = fopen("leaderboard.txt", "r");
    if(fp==NULL){
        fp = fopen("leaderboard.txt", "w");
        for(int i = 0; i<10; i++){
            fprintf(fp, "%s %d\n", "DEV", 0);
        }
    }
    fclose(fp);

    fp = fopen("stats.txt", "r");
    if(fp==NULL){
        fp = fopen("stats.txt", "w");
        fprintf(fp, "%d %d %d %d %d %d %f", 0, 0, 0, 0, 0, 0, 1.0);
    }
    fclose(fp);

    fp = fopen("achievements.txt", "r");
    if(fp==NULL){
        fp = fopen("achievements.txt", "w");
        fprintf(fp, "%d %d %d %d %d %d", 0, 0, 0, 0, 0, 0);
    }
    fclose(fp);
}

void new_game(char name[], long long *money, long long *seed, float *multiplier, int *buffed_mult, int deck[][4][14], int *packs, int *limitcards, int *played_cards, int achievements_track[]){
    FILE *fp;
    fp = fopen("savegame.txt", "w"); //Open or overwrite all the data inside

    int flag = 0;
    for(int i = 0; i<6; i++){
        if(achievements_track[i]==1){
            flag = 1;
            break;
        }
    }

    printf("Write your name: ");
    scanf("%49s", name);
    *money = 1000;
    *seed = time(NULL); //Generate random seed
    *multiplier = 1.0;
    *buffed_mult = 1; //Give standard multiplier
    *packs = 1;
    *limitcards = 56;
    *played_cards = 0;

    int choice;
    do{
        printf("Choose gamemode:\n%s1. Classic Game\n%s2. Custom Game%s\n", GREEN, flag ? GREEN : RED, PLAYER);
        scanf("%d", &choice);
    } while(choice != 1 && (choice != 2 || flag == 0));

    
    if(choice == 2){
        while(choice!=5){
            printf("Choices:\n%s1. Starting money\n%s2. Starting seed\n", (achievements_track[0] || achievements_track[1]) ? GREEN : RED, achievements_track[3] ? GREEN : RED);
            printf("%s3. Starting multiplier\n%s4. Number of decks\n%s5. Start Game%s\n", achievements_track[2] ? GREEN : RED, achievements_track[4] ? GREEN : RED, GREEN, PLAYER);

            scanf("%d", &choice);
            if(choice==1 && (achievements_track[0] || achievements_track[1])){
                if(achievements_track[1]){
                    printf("Choose your starting money (up to 1m):%s ", YELLOW);
                    *money = read_number();
                    while(*money>1000000 || *money<0){
                        printf("%sWrong input, try again:%s ", RED, YELLOW);
                        *money = read_number();
                    }
                    printf(PLAYER "Registered!\n");
                }
                else{
                    printf("Choose your starting money (up to 10k):%s ", YELLOW);
                    *money = read_number();
                    while(*money>10000 || *money<0){
                        printf("%sWrong input, try again:%s ", RED, YELLOW);
                        *money = read_number();
                    }
                    printf(PLAYER "Registered!\n");
                }
            }
            else if(choice==1) printf("This choice isn't yet available!\n");

            if(choice == 2 && achievements_track[3]){
                printf(PLAYER "Write your seed (numbers only): ");
                scanf("%lld", seed);
                printf(PLAYER "Registered!\n");
            }
            else if(choice==2) printf("This choice isn't yet available!\n");

            if(choice == 3 && achievements_track[2]){
                printf("Do you want:\n1. Normal Multiplier\n2. Buffed Multiplier\n");
                scanf("%d", buffed_mult);
                while(*buffed_mult>2 || *buffed_mult<1){
                    printf("%sWrong input, try again:%s ", RED, PLAYER);
                    scanf("%d", buffed_mult);
                }
                printf(PLAYER "Registered!\n");
            }
            else if(choice==3) printf("This choice isn't yet available!\n");
            
            if(choice == 4 && achievements_track[4]){
                printf("Choose how many decks you want there to be(up to 5): ");
                scanf("%d", packs);
                while(*packs>5 || *packs<1){
                    printf("%sWrong input, try again:%s ", RED, PLAYER);
                    scanf("%d", packs);
                }
                if(*packs==1) *limitcards = 56;
                else if(*packs==2) *limitcards = 112;
                else if(*packs==3) *limitcards = 168;
                else if(*packs==4) *limitcards = 224;
                else if(*packs==5) *limitcards = 280;
                printf(PLAYER "Registered!\n");
            }
            else if(choice==4) printf("This choice isn't yet available!\n");

        }
    }

    fprintf(fp, "%s %lld %lld %f %d %d %d %d ", name, *money, *seed, *multiplier, *buffed_mult, *packs, *limitcards, *played_cards);
    for(int k = 0; k < *packs; k++){
        for(int i = 0; i<4; i++){
            for(int j = 0; j<14; j++){
                fprintf(fp, "%d ", 0); //Save the full deck
                deck[k][i][j] = 0;
            }
        }
    }
    fclose(fp);

}

void load_game(char name[], long long *money, long long *seed, float *multiplier, int *buffed_mult,int deck[][4][14], int *packs, int *limitcards, int *played_cards){
    FILE *fp;
    fp = fopen("savegame.txt", "r");
    fscanf(fp, "%s %lld %lld %f %d %d %d %d ", name, money, seed, multiplier, buffed_mult, packs, limitcards, played_cards); 
    for(int k = 0; k < *packs; k++){
        for(int i = 0; i<4; i++){
            for(int j = 0; j<14; j++){
                fscanf(fp, "%d", &deck[k][i][j]);
            }
        }
    }
    fclose(fp);
}

void load_stats(long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost, float *biggestmult){
    FILE *fp;
    fp = fopen("stats.txt", "r");
    fscanf(fp, "%lld %lld %lld %lld %lld %lld %f", overallplayed, totalwins, totallost, totalties, moneygained, moneylost, biggestmult); //Load everything
    fclose(fp);
}

void load_achievements(int achievements_track[]){
    FILE *fp;
    fp = fopen("achievements.txt", "r");
    for(int i = 0; i<6; i++){
        fscanf(fp, "%d", &achievements_track[i]);
    }
    fclose(fp);
}

void leaderboard_save_delete(long long money){
    FILE *fp;
    char users[11][50]; //To track old names, with an extra row
    long long board[11]; //Get leaderboard, with an extra row

    fp = fopen("leaderboard.txt", "r");
    for(int i = 0; i<10; i++){
        fscanf(fp, "%s %lld", users[i], &board[i]); //Read the existing data
    }
    fclose(fp);

    fp = fopen("savegame.txt", "r");
    fscanf(fp, "%s", users[10]); //Store current playthrough name
    fclose(fp);
    board[10] = money; //Store in the extra row the current run money

    int temp; //Transports numbers
    char temp2[50]; //Transports names
    int k; //Helps keep track of the transporting

    for (int i = 0; i < 11 - 1; i++) {
        for (int j = 0; j < 11 - i - 1; j++) {
            if (board[j] < board[j + 1]) {
                temp = board[j];
                board[j] = board[j + 1]; //Bubblesort it and kick the lowest in the last place
                board[j + 1] = temp;
                k = 0;
                while(users[j][k]!='\0'){
                    temp2[k] = users[j][k];
                    k++;
                }
                temp2[k] = '\0'; //Ensures the string ends properly, this is important since it gets cut of by the while()

                k = 0;
                while(users[j + 1][k]!='\0'){
                    users[j][k] = users[j+1][k]; //Follows the numbers
                    k++;
                }
                users[j][k] = '\0';

                k = 0;
                while(temp2[k]!='\0'){
                    users[j+1][k] = temp2[k];
                    k++;
                }
                users[j+1][k] = '\0';
            }
        }
    }

    fp = fopen("leaderboard.txt", "w"); //Clear file
    for(int i = 0; i<10; i++){
        fprintf(fp, "%s %lld\n", users[i], board[i]); //Save only the top 10
    }
    fclose(fp);

    fp = fopen("savegame.txt", "w"); //Clear file
    fclose(fp);
}

void savegame(char name[], long long *money, long long *seed, float *multiplier, int *buffed_mult,int deck[][4][14], int *packs, int *limitcards, int *played_cards){
    FILE *fp;
    fp = fopen("savegame.txt", "w");

    fprintf(fp, "%s %lld %lld %f %d %d %d %d ", name, *money, *seed, *multiplier, *buffed_mult, *packs, *limitcards, *played_cards);
    for(int k = 0; k < *packs; k++){
        for(int i = 0; i<4; i++){
            for(int j = 0; j<14; j++){
                fprintf(fp, "%d ", deck[k][i][j]); //Save the full deck
            }
        }
    }
    fclose(fp);
}

void save_stats(long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost, float *biggestmult){
    FILE *fp;
    fp = fopen("stats.txt", "w");

    fprintf(fp, "%lld %lld %lld %lld %lld %lld %f", *overallplayed, *totalwins, *totallost, *totalties, *moneygained, *moneylost, *biggestmult); //Save the stats
    fclose(fp);
}

void save_achievements(int achievements_track[]){
    FILE *fp;
    fp = fopen("achievements.txt", "w");

    for(int i = 0; i<6; i++){
        fprintf(fp, "%d ", achievements_track[i]);
    }
    fclose(fp);
}

void resetchoice(int choice){
    FILE *fp;

    if(choice == 1){
        fp = fopen("leaderboard.txt", "w");
        for(int i = 0; i<10; i++){
            fprintf(fp, "%s %d\n", "DEV", 0);
        }
        fclose(fp);
    }
    else if(choice == 2){
        fp = fopen("stats.txt", "w");
        fprintf(fp, "%d %d %d %d %d %d", 0, 0, 0, 0, 0, 0);
        fclose(fp);
    }
    else if(choice == 3){
        fp = fopen("achievements.txt", "w");
        fprintf(fp, "%d %d %d %d %d %d", 0, 0, 0, 0, 0, 0);
        fclose(fp);
    }
    else{
        fp = fopen("leaderboard.txt", "w");
        for(int i = 0; i<10; i++){
            fprintf(fp, "%s %d\n", "DEV", 0);
        }
        fclose(fp);

        fp = fopen("stats.txt", "w");
        fprintf(fp, "%d %d %d %d %d %d", 0, 0, 0, 0, 0, 0);
        fclose(fp);

        fp = fopen("achievements.txt", "w");
        fprintf(fp, "%d %d %d %d %d %d", 0, 0, 0, 0, 0, 0);
        fclose(fp);
    }

}
