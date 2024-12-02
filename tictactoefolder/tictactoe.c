#include <stdio.h>
#include <string.h>

#define CLEARSCREEN "\033[H\033[J"
#define DARKBLUE "\033[1;34m"
#define LIGHTBLUE "\033[1;36m"
#define OCEANBLUE "\033[38;5;33m"
#define WHITE "\033[97m"
#define LIGHTCYAN "\033[38;5;51m"
#define BRIGHTBLUE "\033[38;5;45m"
#define RESET "\x1b[0m"
#define SYSTEM "\x1b[0;38;5;69m"
#define PLAYERS "\033[1;34m"
#define RED   "\x1b[1;31m"
#define GREEN "\x1b[1;32m"
#define BOARD "\033[38;5;102m"

void displayBanner(){
    printf(RED" .----------------.  .----------------.  .----------------. \n");
    printf("| .--------------. || .--------------. || .--------------. |\n");
    printf("| |  _________   | || |     _____    | || |     ______   | |\n");
    printf("| | |  _   _  |  | || |    |_   _|   | || |   .' ___  |  | |\n");
    printf("| | |_/ | | \\_|  | || |      | |     | || |  / .'   \\_|  | |\n");
    printf("| |     | |      | || |      | |     | || |  | |         | |\n");
    printf("| |    _| |_     | || |     _| |_    | || |  \\ `.___.'\\  | |\n");
    printf("| |   |_____|    | || |    |_____|   | || |   `._____.'  | |\n");
    printf("| |              | || |              | || |              | |\n");
    printf("| '--------------' || '--------------' || '--------------' |\n");
    printf(" '----------------'  '----------------'  '----------------' \n");
    printf(GREEN" .----------------.  .----------------.  .----------------. \n");
    printf("| .--------------. || .--------------. || .--------------. |\n");
    printf("| |  _________   | || |      __      | || |     ______   | |\n");
    printf("| | |  _   _  |  | || |     /  \\     | || |   .' ___  |  | |\n");
    printf("| | |_/ | | \\_|  | || |    / /\\ \\    | || |  / .'   \\_|  | |\n");
    printf("| |     | |      | || |   / ____ \\   | || |  | |         | |\n");
    printf("| |    _| |_     | || | _/ /    \\ \\_ | || |  \\ `.___.'\\  | |\n");
    printf("| |   |_____|    | || ||____|  |____|| || |   `._____.'  | |\n");
    printf("| |              | || |              | || |              | |\n");
    printf("| '--------------' || '--------------' || '--------------' |\n");
    printf(" '----------------'  '----------------'  '----------------' \n");
    printf(OCEANBLUE" .----------------.  .----------------.  .----------------. \n");
    printf("| .--------------. || .--------------. || .--------------. |\n");
    printf("| |  _________   | || |     ____     | || |  _________   | |\n");
    printf("| | |  _   _  |  | || |   .'    `.   | || | |_   ___  |  | |\n");
    printf("| | |_/ | | \\_|  | || |  /  .--.  \\  | || |   | |_  \\_|  | |\n");
    printf("| |     | |      | || |  | |    | |  | || |   |  _|  _   | |\n");
    printf("| |    _| |_     | || |  \\  `--'  /  | || |  _| |___/ |  | |\n");
    printf("| |   |_____|    | || |   `.____.'   | || | |_________|  | |\n");
    printf("| |              | || |              | || |              | |\n");
    printf("| '--------------' || '--------------' || '--------------' |\n");
    printf(" '----------------'  '----------------'  '----------------' \n\n\n");
}

void printboard(char game[3][3]){
    int x = 0, y = 3;
    putchar('\n');
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
    for(int i = 0; i<3; i++){ // Looks up
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
    for(int j = 0; j<3; j++){ // Looks down
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
    if(game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[0][0]!=' '){ // Looks main diagonal
        if(game[0][0]== 'X'){
            return 1;
        }
        else{
            return 2;
        }
    }
    if(game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[0][2]!=' '){ // Looks secondary diagonal
        if(game[0][2]== 'X'){
            return 1;
        }
        else{
            return 2;
        }
    }

    return 0;
}

int errorhandle(int num, char game[3][3], int pos[][2]){
    if(num<=0 || num>=10){
        printf(RED"Wrong Number.\n" SYSTEM);
        return 1;
    }
    if(game[pos[num-1][0]][pos[num-1][1]] == 'X' || game[pos[num-1][0]][pos[num-1][1]] == 'O'){
        printf(RED"It has already been played there.\n" SYSTEM);
        return 1;
    }

    return 0;
}

void getname(char player[], int which, int size){
    printf(SYSTEM "Input player %d name: %s", which, PLAYERS);
    fgets(player, size, stdin);
    // Remove the newline character if present
    size_t len = strlen(player);
    if (len > 0 && player[len - 1] == '\n') {
        player[len - 1] = '\0';
    }
}

int main(){
    char player1[50], player2[50];
    int wins1 = 0, wins2 = 0, turn = 0, won = 0, counter, bigturn = 0, num = 0;
    int pos[9][2] = {{0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}, {0, 2}, {1, 2}, {2, 2}};
    int flag = 1;

    displayBanner();

    getname(player1, 1, sizeof(player1));
    getname(player2, 2, sizeof(player2));

    while(flag == 1){
        char game[3][3] = {'1','4','7','2','5','8','3','6','9'};
        counter = 0;
        won = 0;

        if(bigturn % 2 == 0){
            printf(SYSTEM"%s goes first\n", player1);
            turn = 0;
        } else {
            printf(SYSTEM"%s goes first\n", player2);
            turn = 1;
        }

        while(won == 0 && counter < 9){
            if(counter==0) printboard(game);
            do {
                printf("%s, choose number to play on: ", (turn == 0) ? player1 : player2);
                scanf("%d", &num);
            } while(errorhandle(num, game, pos));

            game[pos[num-1][0]][pos[num-1][1]] = (turn == 0) ? 'X' : 'O';
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