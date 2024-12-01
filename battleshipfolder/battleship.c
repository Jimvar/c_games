#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "printingsystem.h"
#include "soundsystem.h"

int main() {
    init_audio();

    int choice;
    choice = startupscreen();

    if(choice==1){
        char player1[50], player2[50];
        int ship_placement[2][10][10] = {0};
        int bigturn = 0;
        int win, wins1 = 0, wins2 = 0;

        while(getchar()!='\n');
        getname(player1, 1, sizeof(player1));
        getname(player2, 2, sizeof(player2));

        while(choice==1){
            ship_setup(player1, player2, bigturn, ship_placement);

            win = gameplay(player1, player2, bigturn, ship_placement);

            if(win==1){
                printf(SYSTEM "Congrats to %s%s%s for winning!\n", PLAYERS, player1, SYSTEM);
                wins1++;
            }
            else{
                printf(SYSTEM "Congrats to %s%s%s for winning!\n", PLAYERS, player2, SYSTEM);
                wins2++;
            }

            printf("The current score is %s%s:%d%s - %s%d:%s%s\n", PLAYERS, player1, wins1, SYSTEM, PLAYERS, wins2, player2, SYSTEM);
            bigturn = 1 - bigturn;
            printf("If you want to play again, enter 1: ");
            scanf("%d", &choice);
        }
    }

    atexit(cleanup_audio);
    return 0;
}
