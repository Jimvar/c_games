#include <stdio.h>
#include <string.h>

void printboard(char game[3][3]){
    int x = 0, y = 3;
    for(int i = 0; i<7; i++){
        if(i%2==0){
            printf("-------\n");
            y--;
        }
        else{
            printf("|%c|%c|%c|\n", game[x][y], game[x+1][y], game[x+2][y]);
        }
    }
    putchar('\n');
}

int checkwin(char game[3][3]){
    int flag = 0, counter = 0;
    char c;
    for(int i = 0; i<3; i++){ // Koitaei pano
        c = game[i][0];
        if(c == game[i][1] && c == game[i][2] && c!=' '){
            if(c=='X'){
                return 1;
            }
            else{
                return 2;
            }
        }
    }
    for(int j = 0; j<3; j++){ // Koitaei deksia
        c = game[0][j];
        if(c == game[1][j] && c == game[2][j] && c!=' '){
            if(c=='X'){
                return 1;
            }
            else{
                return 2;
            }
        }
    }
    if(game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[0][0]!=' '){
        if(game[0][0]== 'X'){
            return 1;
        }
        else{
            return 2;
        }
    }
    if(game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[0][2]!=' '){
        if(game[0][2]== 'X'){
            return 1;
        }
        else{
            return 2;
        }
    }

    return 0;
}

int errorhandle(int x, int y, char game[3][3]){
    if(x>=3 || y>=3 || x<0 || y<0){
        printf("Wrong Coordinates\n");
        return 1;
    }
    if(game[x][y] == 'X' || game[x][y] == 'O'){
        printf("It has already been played there\n");
        return 1;
    }

    return 0;
}

int main(){
    char player1[50], player2[50];
    int wins1 = 0, wins2 = 0, turn = 0, x, y, won = 0, counter, bigturn = 0;
    int flag = 1;

    printf("Input player 1 name: ");
    scanf("%49s", player1);

    printf("Input player 2 name: ");
    scanf("%49s", player2);

    while(flag == 1){
        char game[3][3] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
        counter = 0;
        won = 0;

        if(bigturn % 2 == 0){
            printf("%s goes first\n", player1);
            turn = 0;
        } else {
            printf("%s goes first\n", player2);
            turn = 1;
        }

        while(won == 0 && counter < 9){
            do {
                printf("%s, choose coordinates of play: ", (turn == 0) ? player1 : player2);
                scanf("%d%d", &x, &y);
            } while(errorhandle(x, y, game));

            game[x][y] = (turn == 0) ? 'X' : 'O';
            printboard(game);
            won = checkwin(game);
            turn = 1 - turn;
            counter++;
        }

        if(won == 1){
            printf("%s wins!\n", player1);
            wins1++;
        } 
        else if(won == 2){
            printf("%s wins!\n", player2);
            wins2++;
        } 
        else{
            printf("It's a draw!\n");
        }

        printf("Score: %s %d - %d %s\n", player1, wins1, wins2, player2);
        bigturn++;

        printf("Do you want to play again? (1 for yes, 0 for no): ");
        scanf("%d", &flag);
    }

    return 0;
}