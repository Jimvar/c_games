#include <stdio.h>
#include <stdlib.h>
#include "savesystem.h"

void first_time_set(){ //Sets up all the files if the game is for the first time opened
    FILE *fp;

    fp = fopen("savegame.txt", "r");
    if(fp==NULL){
        fp = fopen("savegame.txt", "w");
    }
    fclose(fp);

    fp = fopen("stats.txt", "r");
    if(fp==NULL){
        fp = fopen("stats.txt", "w");
        fprintf(fp, "%d %d %d %d %d %d %f", 0, 0, 0, 0, 0, 0, 1.0);
    }
    fclose(fp);
}