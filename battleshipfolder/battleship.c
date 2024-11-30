#include <stdio.h>
#include "printingsystem.h"

int main() {
    int choice;
    choice = startupscreen();

    if(choice==1){
        char player1[50], player2[50];
        int ship_placement[2][10][10] = {0};
        int bigturn = 0;
        int win;

        while(getchar()!='\n');
        getname(player1, 1, sizeof(player1));
        getname(player2, 2, sizeof(player2));

        ship_setup(player1, player2, bigturn, ship_placement);

        win = gameplay(player1, player2, bigturn, ship_placement);
    }

    return 0;
}
