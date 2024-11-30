#include <stdio.h>
#include <unistd.h> // For usleep()
#include "printingsystem.h"

int main() {
    int choice;
    choice = startupscreen();

    if(choice==1){
        char player1[50], player2[50];

        while(getchar()!='\n');
        getname(player1, 1, sizeof(player1));
        getname(player2, 2, sizeof(player2));
    }

    return 0;
}
