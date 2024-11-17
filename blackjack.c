#include <stdio.h>
#include <stdlib.h>

#define GREEN "\x1b[1;32m"
#define RED     "\x1b[1;31m"
#define RESET   "\x1b[0m"


int startupscreen(){
    FILE *fp;
    fp = fopen("savegame.txt", "r");
    if(fp==NULL){
        printf("File not found, exiting...\n");
        exit(EXIT_FAILURE);
    }
    printf("Blackjack\n");
    char c;
    printf("Choose:\n");
    printf(GREEN "1. New Game\n");
    (fscanf(fp, "%c", &c) != EOF) ? printf("2. Continue\n") : printf(RED "2. Continue\n");
    printf(GREEN "3. Leaderboard\n" RESET);
    fclose(fp);
}

int main(){
    int choice = startupscreen();



    
}