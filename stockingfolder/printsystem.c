#include <stdio.h>
#include <stdlib.h>
#include "printsystem.h"

int startupscreen(){
    char c;
    FILE *fp;

    fp = fopen("savegame.txt", "r");
    if(fp==NULL){
        printf("File not found, exiting...\n"); //Checks if file is deleted
        exit(EXIT_FAILURE);
    }
    int flag = fscanf(fp, "%c", &c); //Checks if the file is empty; if empty it will print continue as red
    fclose(fp);

    printf(SYSTEM "Choose:\n");
    printf("%s1. New Game\n%s2. Continue\n%s3. Exit\n%s", GREEN, (flag==-1) ? RED : GREEN, GREEN, PLAYER);

    c = getchar();
    while(c!='1' && (c!='2' || flag== -1) && c!='3'){
        while(getchar()!='\n');
        printf(RED "Wrong input, choose again: " PLAYER);
        c = getchar();
    }
    while(getchar()!='\n');

    return(c - '0');
}