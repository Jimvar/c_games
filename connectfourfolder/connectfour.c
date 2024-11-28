#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
// C
#define RED     "\x1b[1;31m"
#define CYAN  "\x1b[1;36m"
#define GREEN "\x1b[1;32m"
#define SYSTEM "\x1b[0;38;5;69m"
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


int errorhandle(int input, int availiable[7]){
    if(input<1 || input>7){
        if(input!=12){
            printf("Wrong input!\n");
            return -1;
        }
        else return 1;
    }
    else{
        if(availiable[input - 1] == -1){
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

#ifdef _WIN32
    #define clear_screen() system("cls")
#else
    #include <unistd.h>
    void clear_screen() {
        if (isatty(fileno(stdout))) {
            printf("\033[H\033[J");  // ANSI escape codes
        } else {
            printf("Output is not a terminal. Screen clear skipped.\n");
        }
    }
#endif

int main(){
    char player1[50], player2[50];
    int wins1 = 0, wins2 = 0, turn = 0, won = 0, counter, bigturn = 0, check, pos1, pos2;
    int input;
    int flag = 1;

    printf("\n");
    printf("%s        CCCCCCCCCCCCC                                                                                                      tttt               %sFFFFFFFFFFFFFFFFFFFFFF                                                   \n", RED, CYAN);
    printf("%s     CCC::::::::::::C                                                                                                   ttt:::t               %sF::::::::::::::::::::F                                                   \n", RED, CYAN);
    printf("%s   CC:::::::::::::::C                                                                                                   t:::::t               %sF::::::::::::::::::::F                                                   \n", RED, CYAN);
    printf("%s  C:::::CCCCCCCC::::C                                                                                                   t:::::t               %sFF::::::FFFFFFFFF::::F                                                   \n", RED, CYAN);
    printf("%s C:::::C       CCCCCC   ooooooooooo   nnnn  nnnnnnnn    nnnn  nnnnnnnn        eeeeeeeeeeee        ccccccccccccccccttttttt:::::ttttttt         %s  F:::::F       FFFFFFooooooooooo   uuuuuu    uuuuuu rrrrr   rrrrrrrrr   \n", RED, CYAN);
    printf("%sC:::::C               oo:::::::::::oo n:::nn::::::::nn  n:::nn::::::::nn    ee::::::::::::ee    cc:::::::::::::::ct:::::::::::::::::t         %s  F:::::F           oo:::::::::::oo u::::u    u::::u r::::rrr:::::::::r  \n", RED, CYAN);
    printf("%sC:::::C              o:::::::::::::::on::::::::::::::nn n::::::::::::::nn  e::::::eeeee:::::ee c:::::::::::::::::ct:::::::::::::::::t         %s  F::::::FFFFFFFFFFo:::::::::::::::ou::::u    u::::u r:::::::::::::::::r \n", RED, CYAN);
    printf("%sC:::::C              o:::::ooooo:::::onn:::::::::::::::nnn:::::::::::::::ne::::::e     e:::::ec:::::::cccccc:::::ctttttt:::::::tttttt         %s  F:::::::::::::::Fo:::::ooooo:::::ou::::u    u::::u rr::::::rrrrr::::::r\n", RED, CYAN);
    printf("%sC:::::C              o::::o     o::::o  n:::::nnnn:::::n  n:::::nnnn:::::ne:::::::eeeee::::::ec::::::c     ccccccc      t:::::t               %s  F:::::::::::::::Fo::::o     o::::ou::::u    u::::u  r:::::r     r:::::r\n", RED, CYAN);
    printf("%sC:::::C              o::::o     o::::o  n::::n    n::::n  n::::n    n::::ne:::::::::::::::::e c:::::c                   t:::::t               %s  F::::::FFFFFFFFFFo::::o     o::::ou::::u    u::::u  r:::::r     rrrrrrr\n", RED, CYAN);
    printf("%sC:::::C              o::::o     o::::o  n::::n    n::::n  n::::n    n::::ne::::::eeeeeeeeeee  c:::::c                   t:::::t               %s  F:::::F          o::::o     o::::ou::::u    u::::u  r:::::r            \n", RED, CYAN);
    printf("%s C:::::C       CCCCCCo::::o     o::::o  n::::n    n::::n  n::::n    n::::ne:::::::e           c::::::c     ccccccc      t:::::t    tttttt     %s  F:::::F          o::::o     o::::ou:::::uuuu:::::u  r:::::r            \n", RED, CYAN);
    printf("%s  C:::::CCCCCCCC::::Co:::::ooooo:::::o  n::::n    n::::n  n::::n    n::::ne::::::::e          c:::::::cccccc:::::c      t::::::tttt:::::t     %sFF:::::::FF        o:::::ooooo:::::ou:::::::::::::::uur:::::r            \n", RED, CYAN);
    printf("%s   CC:::::::::::::::Co:::::::::::::::o  n::::n    n::::n  n::::n    n::::n e::::::::eeeeeeee   c:::::::::::::::::c      tt::::::::::::::t     %sF::::::::FF        o:::::::::::::::o u:::::::::::::::ur:::::r            \n", RED, CYAN);
    printf("%s     CCC::::::::::::C oo:::::::::::oo   n::::n    n::::n  n::::n    n::::n  ee:::::::::::::e    cc:::::::::::::::c        tt:::::::::::tt     %sF::::::::FF         oo:::::::::::oo   uu::::::::uu:::ur:::::r            \n", RED, CYAN);
    printf("%s        CCCCCCCCCCCCC   ooooooooooo     nnnnnn    nnnnnn  nnnnnn    nnnnnn    eeeeeeeeeeeeee      cccccccccccccccc          ttttttttttt       %sFFFFFFFFFFF           ooooooooooo       uuuuuuuu  uuuurrrrrrr            \n", RED, CYAN);
    printf("\n");

    printf(SYSTEM "Welcome to Connect Four!\n");

    printf("Input player 1 name: %s", RED);
    scanf("%49s", player1);

    printf(SYSTEM "Input player 2 name: %s", CYAN);
    scanf("%49s", player2);


    char sym1, sym2;
    sym1 = toupper(player1[0]);
    sym2 = charhandle(sym1, player2);

    while(flag==1){
        char board[7][6];
        int columnAvailability[7] = {0};

        won = 0;
        counter = 0;

        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 6; j++){
                board[i][j] = ' ';
            }
        }

        counter = 0;

        if(bigturn%2==0){
            printf("%s%s%s goes first\n", RED, player1, SYSTEM);
            turn = 0;
        }
        else{
            printf("%s%s%s goes first\n", CYAN, player2, SYSTEM);
            turn = 1;
        }


        while(won==0 && counter<42){

            printboard(board, sym1, sym2);
            do{
                printf("%s%s%s, choose an available number between 1-7, or press 12 if you want to forfeit: ", (turn==0) ? RED : CYAN ,(turn==0) ? player1 : player2, SYSTEM);
                scanf(" %d", &input);
                check = errorhandle(input, columnAvailability);
            } while(check==-1);

            if(check==1){
                break;
            }
            else{
                for(int i = 0; i<7; i++){
                    for(int j = 0; j<6; j++){
                        if(board[i][j] == ' ' && input - 1 == i){
                            board[i][j] = (turn==0) ? sym1 : sym2;
                            if(j+1==6){
                                columnAvailability[i] = -1;
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
        printboard(board, sym1, sym2);
        if(check==1){
            if((turn = 1 - turn) == 0){
                printf(SYSTEM "Congrats to %s%s%s for winning! They have a total of %d wins!\n", RED, player1, SYSTEM, ++wins1);
            }
            else{
                printf(SYSTEM"Congrats to %s%s%s for winning! They have a total of %d wins!\n", CYAN, player2, SYSTEM, ++wins2);
            }
        }
        else if(won==1){
            turn = 1 - turn;
            printf(SYSTEM "Congrats to %s%s%s for winnning! They have a total of %d wins!\n", (turn==0) ? RED : CYAN, (turn==0) ? player1 : player2, SYSTEM, (turn==0) ? ++wins1 : ++wins2);
        }
        else{
            printf(SYSTEM "It's a draw!\n");
        }

        printf("The current score is %s%s:%d%s - %s%d:%s%s\n", RED, player1, wins1, SYSTEM, CYAN, wins2, player2, SYSTEM);

        bigturn++;
        flag = 0;

        printf("If you want to play again, enter 1: ");
        scanf("%d", &flag);
        clear_screen();
    }



}