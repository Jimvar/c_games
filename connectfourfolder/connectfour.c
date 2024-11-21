#include <stdio.h>
#include <ctype.h>
// C
#define RED     "\x1b[1;31m"
#define CYAN  "\x1b[1;36m"
#define GREEN "\x1b[1;32m"
#define RESET   "\x1b[0m"

void printboard(char board[7][6], char sym1, char sym2){

    printf(GREEN " ---------------\n" RESET);
    for(int j = 5; j >= 0; j--){
        printf(GREEN "|" RESET);
        for(int i = 0; i < 7; i++){
            if (board[i][j] == sym1) {
                printf(RED " %c" RESET, sym1);
            } else if (board[i][j] == sym2) {
                printf(CYAN " %c" RESET, sym2);
            } else {
                printf(" %c", board[i][j]);
            }
        }
        printf(GREEN" |\n" RESET);
    }
    printf(GREEN " ---------------\n" RESET);
    printf(GREEN "  1 2 3 4 5 6 7\n" RESET);

}


int errorhandle(char input, int availiable[7]){



    if(input<'1' || input>'7'){
        if(input!='f'){
            printf("Wrong input!\n");
            return -1;
        }
        else return 1;
    }
    else{
        if(availiable[input - '0' - 1] == -1){
            printf("You can't place there, collumn is full!\n");
            return -1;
        }
        return 0;
    }
}

char charhandle(char sim1, char player2[50]){
    for(int i = 0; i<50; i++){
        if(player2[i]=='\0'){
            break;
        }
        if(sim1!=toupper(player2[i])){
            return toupper(player2[i]);
        }
    }

    return (sim1!='X') ? 'X' : 'O';

}

int wincheck(char board[7][6], int pos1, int pos2){
    int i,j, consecutive = 1;

    char c = board[0][pos2];
    for(i = 1; i<7; i++){
        if(board[i][pos2]==c && c!=' '){
            consecutive++;
            if(consecutive==4){
                return 1;
            }
        }
        else{
            c = board[i][pos2];
            consecutive = 1;
        }
    }

    c = board[pos1][0];
    for(j = 1; j<6; j++){
        if(board[pos1][j]==c && c!=' '){
            consecutive++;
            if(consecutive==4){
                return 1;
            }
        }
        else{
            c = board[pos1][j];
            consecutive = 1;
        }
    }

    consecutive = 1;
    i = pos1;
    j = pos2;
    while(i > 0 && j > 0){
        i--;
        j--;
    }
    while(i < 6 && j < 5){
        if(board[i][j] == board[i+1][j+1] && board[i][j] != ' '){
            consecutive++;
            if(consecutive == 4){
                return 1;
            }
        } 
        else{
            consecutive = 1;
        }
        i++;
        j++;
    }

    consecutive = 1;
    i = pos1;
    j = pos2;
    while(i > 0 && j < 5){
        i--;
        j++;
    }
    while(i < 6 && j > 0){
        if(board[i][j] == board[i+1][j-1] && board[i][j] != ' '){
            consecutive++;
            if(consecutive == 4){
                return 1;
            }
        } 
        else{
            consecutive = 1;
        }
        i++;
        j--;
    }

    return 0;

}


int main(){
    char player1[50], player2[50];
    int wins1 = 0, wins2 = 0, turn = 0, won = 0, counter, bigturn = 0, check, pos1, pos2;
    char input;
    int flag = 1;

    printf("Welcome to Connect Four!\n");

    printf("Input player 1 name: ");
    scanf("%49s", player1);

    printf("Input player 2 name: ");
    scanf("%49s", player2);


    char sym1, sym2;
    sym1 = toupper(player1[0]);
    sym2 = charhandle(sym1, player2);

    while(flag==1){
        char board[7][6];
        int availiable[7] = {0};

        won = 0;
        counter = 0;

        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 6; j++){
                board[i][j] = ' ';
            }
        }

        counter = 0;

        if(bigturn%2==0){
            printf("%s goes first\n", player1);
            turn = 0;
        }
        else{
            printf("%s goes first\n", player2);
            turn = 1;
        }


        while(won==0 && counter<42){

            printboard(board, sym1, sym2);
            do{
                printf("%s, choose an availiable number between 1-7, or press f if you want to forfeit): ", (turn==0) ? player1 : player2);
                scanf(" %c", &input);
                check = errorhandle(input, availiable);
            } while(check==-1);

            if(check==1){
                break;
            }
            else{
                for(int i = 0; i<7; i++){
                    for(int j = 0; j<6; j++){
                        if(board[i][j] == ' ' && input - '0' - 1 == i){
                            board[i][j] = (turn==0) ? sym1 : sym2;
                            if(j+1==6){
                                availiable[i] = -1;
                            }
                            pos1 = i;
                            pos2 = j;
                            i = 7;
                            break;
                        }
                    }
                }
                won = wincheck(board, pos1, pos2);
            }

            turn = 1 - turn;
            counter++;
        }


        if(check==1){
            if((turn = 1 - turn) == 0){
                printf("Congrats to %s for winning! They have a total of %d wins!\n", player1, ++wins1);
            }
            else{
                printf("Congrats to %s for winning! They have a total of %d wins!\n", player2, ++wins2);
            }
        }
        else if(won==1){
            turn = 1 - turn;
            printf("Congrats to %s for winnning! They have a total of %d wins!\n", (turn==0) ? player1 : player2, (turn==0) ? ++wins1 : ++wins2);
        }
        else{
            printf("It's a draw!\n");
        }

        bigturn++;
        flag = 0;

        printf("If you want to play again, enter 1: ");
        scanf("%d", &flag);
    }



}