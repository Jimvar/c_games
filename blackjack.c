#include <stdio.h>
#include <stdlib.h>

#define GREEN "\x1b[1;32m"
#define RED     "\x1b[1;31m"
#define RESET   "\x1b[0m"

int first_time_set(){
    FILE *fp;

    fp = fopen("savegame.txt", "r");
    if(fp==NULL){
        fp = fopen("savegame.txt", "w");
        fclose(fp);
    }

    fp = fopen("leaderboard.txt", "r");
    if(fp==NULL){
        fp = fopen('leaderboard.txt', "w");
        fprintf(fp, "LEADERBOARD\n");
        for(int i = 0; i<10; i++){
            fprintf(fp, "%d. %d\n", i+1, 0);
        }
        fclose(fp);
    }
}

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

    printf("Blackjack\nChoose:\n");
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
        printf("%d. %d\n", i+1, board[i]);
    }
    printf("------------------------------------\n");
    fclose(fp);
}

int main(){
    first_time_set();

    int choice = startupscreen();

    while(1){
        if(choice==3){
            leaderboard();
            choice = startupscreen();
            continue;
        }
        else if(choice==2){

        }
        else{

        }
    }


    
}