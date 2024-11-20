#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GREEN "\x1b[1;32m"
#define RED     "\x1b[1;31m"
#define BBLU "\x1b[1;34m"
#define BMAG "\x1b[1;35m"
#define RESET   "\x1b[0m"

const char *colors[] = {
    GREEN,
    RED,
    BBLU,
    BMAG,
    RESET
};

void first_time_set(){
    FILE *fp;

    fp = fopen("savegame.txt", "r");
    if(fp==NULL){
        fp = fopen("savegame.txt", "w");
        fclose(fp);
    }

    fp = fopen("leaderboard.txt", "r");
    if(fp==NULL){
        fp = fopen("leaderboard.txt", "w");
        for(int i = 0; i<10; i++){
            fprintf(fp, "%d\n", 0);
        }
        fclose(fp);
    }
}

int startupscreen(){
    char c;
    FILE *fp;

    fp = fopen("savegame.txt", "r");
    if(fp==NULL){
        printf("File not found, exiting...\n");
        exit(EXIT_FAILURE);
    }
    int flag = fscanf(fp, "%c", &c);
    fclose(fp);

    printf("\n /$$$$$$$  /$$                     /$$                                     /$$      \n");
    printf("| $$__  $$| $$                    | $$                                    | $$      \n");
    printf("| $$  \\ $$| $$  /$$$$$$   /$$$$$$$| $$   /$$       /$$  /$$$$$$   /$$$$$$$| $$   /$$\n");
    printf("| $$$$$$$ | $$ |____  $$ /$$_____/| $$  /$$/      |__/ |____  $$ /$$_____/| $$  /$$/\n");
    printf("| $$__  $$| $$  /$$$$$$$| $$      | $$$$$$/        /$$  /$$$$$$$| $$      | $$$$$$/ \n");
    printf("| $$  \\ $$| $$ /$$__  $$| $$      | $$_  $$       | $$ /$$__  $$| $$      | $$_  $$ \n");
    printf("| $$$$$$$/| $$|  $$$$$$$|  $$$$$$$| $$ \\  $$      | $$|  $$$$$$$|  $$$$$$$| $$ \\  $$\n");
    printf("|_______/ |__/ \\_______/ \\_______/|__/  \\__/      | $$ \\_______/ \\_______/|__/  \\__/\n");
    printf("                                             /$$  | $$                              \n");
    printf("                                            |  $$$$$$/                              \n");
    printf("                                             \\______/                               \n");

    printf("Choose:\n");
    printf(GREEN "1. New Game\n");
    flag != -1 ? printf("2. Continue\n") : printf(RED "2. Continue\n");
    printf(GREEN "3. Leaderboard\n" RESET);

    if(flag!=-1){
        do{
            c = getchar();
        } while(c<'1' || c>'3');
    }
    else{
        do{
            c = getchar();
        } while(c!='1' && c!='3');
    }

    return(c - '0');
}

void leaderboard(){
    FILE *fp;
    int board[10];

    fp = fopen("leaderboard.txt", "r");
    if(fp==NULL){
        printf("File not found, exiting...\n");
        exit(EXIT_FAILURE);
    }


    printf("------------------------------------\nLEADERBOARD\n");
    for(int i = 0; i<10; i++){
        fscanf(fp, "%d", &board[i]);
        printf("%2d. %d\n", i+1, board[i]);
    }
    printf("------------------------------------\n");
    fclose(fp);
}

void new_game(char name[], int *money, int *seed, int deck[][14]){
    FILE *fp;
    fp = fopen("savegame.txt", "w");

    printf("Write your name: ");
    scanf("%49s", name);
    *money = 1000;
    fprintf(fp, "%s %d ", name, *money);
    
    printf("Do you want to manually set a seed or have it random? Press 1 or 2: ");
    int answer;
    do{
        scanf("%d", &answer);
    } while(answer!=1 && answer!=2);
    
    if(answer==1){
        printf("Write your seed: ");
        scanf("%d", &answer);
        *seed = answer;
        fprintf(fp, "%d ", *seed);
    }
    else{
        *seed = time(NULL);
        fprintf(fp, "%d ", *seed);
    }

    for(int i = 0; i<4; i++){
        for(int j = 0; j<14; j++){
            fprintf(fp, "%d ", 0);
            deck[i][j] = 0;
        }
    }
    fclose(fp);
}

void leaderboard_save_delete(int money){
    FILE *fp;
    int board[11];

    fp = fopen("leaderboard.txt", "r");
    for(int i = 0; i<10; i++){
        fscanf(fp, "%d", &board[i]);
    }
    fclose(fp);
    board[10] = money;

    for (int i = 0; i < 11 - 1; i++) {
        for (int j = 0; j < 11 - i - 1; j++) {
            if (board[j] < board[j + 1]) {
                int temp = board[j];
                board[j] = board[j + 1];
                board[j + 1] = temp;
            }
        }
    }

    fp = fopen("leaderboard.txt", "w");
    for(int i = 0; i<10; i++){
        fprintf(fp, "%d\n", board[i]);
    }
    fclose(fp);

    fp = fopen("savegame.txt", "w");
    fclose(fp);
}

void savegame(char name[], int *money, int *seed, int deck[][14]){
    FILE *fp;
    fp = fopen("savegame.txt", "w");

    fprintf(fp, "%s %d ", name, *money);
    fprintf(fp, "%d ", *seed);
    for(int i = 0; i<4; i++){
        for(int j = 0; j<14; j++){
            fprintf(fp, "%d ", deck[i][j]);
        }
    }

    fclose(fp);

}

int card_check(int played_cards, int deck[][14]){
    if(played_cards==56){
        for(int i = 0 ; i<4; i++){
            for(int j = 0; j<14; j++){
                deck[i][j] = 0;
            }
        }
        printf("Resuffled cards!\n\n");
        return 0;
    }
    return played_cards;
}

char symbolmatcher(int symbol){
    if(symbol == 0) return '1';
    else if(symbol == 1) return '2';
    else if(symbol == 2) return '3';
    else if(symbol == 3) return '4';
    else if(symbol == 4) return '5';
    else if(symbol == 5) return '6';
    else if(symbol == 6) return '7';
    else if(symbol == 7) return '8';
    else if(symbol == 8) return '9';
    else if(symbol == 9) return 'T';
    else if(symbol == 10) return 'J';
    else if(symbol == 11) return 'Q';
    else if(symbol == 12) return 'K';
    else if(symbol == 13) return 'A';
}

void print_deck(int deck[][14]){
    putchar('\n');

    for(int k = 0; k<4; k++){
        for(int i = 0; i<14; i++){
            printf("%s ---  ", colors[k]);
        }
        putchar('\n');
        for(int i = 0; i<3; i++){
            for(int j = 0; j<14; j++){
                printf("| ");
                if(i==1){
                    deck[k][j] ?  putchar('-')  : printf("%c", symbolmatcher(j));
                }
                else{
                    putchar(' ');
                }
                printf(" | ");
            }
            putchar('\n');
        }
        for(int i = 0; i<14; i++){
            printf(" ---  ");
        }
        putchar('\n');
    }
    putchar('\n');
    printf(RESET);
}

void draw_cards(int how_many, int hand[][20]){
    int start = 0;
    int temp = start;

    for(int i = 0; i<how_many; i++){
        printf("%s ---  ", colors[hand[0][temp]]);
        temp++;
    }
    putchar('\n');
    for(int i = 0; i<3; i++){
        temp = start;
        for(int j = 0; j<how_many; j++){
            printf("%s| ", colors[hand[0][temp]]);
            if(i==1){
                printf("%c", symbolmatcher(hand[1][temp]));
            }
            else{
                putchar(' ');
            }
            printf(" | ");
            temp++;
        }
        putchar('\n');
    }
    temp = start;
    for(int i = 0; i<how_many; i++){
        printf("%s ---  ", colors[hand[0][temp]]);
        temp++;
    }
    printf(RESET "\n");
}

int sumcheck(int symbol, int sum, int *flag){
    int now = 0;
    if(symbol==13 && *flag==1){
        return sum + 1;
    }
    else if(symbol==13){
        *flag = 1;
        now = 1;
    }

    if(symbol == 0) symbol = 1;
    else if(symbol == 1) symbol = 2;
    else if(symbol == 2) symbol = 3;
    else if(symbol == 3) symbol = 4;
    else if(symbol == 4) symbol = 5;
    else if(symbol == 5) symbol = 6;
    else if(symbol == 6) symbol = 7;
    else if(symbol == 7) symbol = 8;
    else if(symbol == 8) symbol = 9;
    else if(symbol == 9) symbol = 10;
    else if(symbol == 10) symbol = 10;
    else if(symbol == 11) symbol = 10;
    else if(symbol == 12) symbol = 10;;

    if(*flag==1){
        if(now==1){
            if(sum + 11 > 21){
                *flag = 0;
                return sum + 1;
            }
            else{
                return sum + 11;
            }
        }
        else{
            if(sum + symbol > 21){
                *flag = 0;
                return sum - 10 + symbol;
            }
        }
    }
    else{
        return sum + symbol;
    }
}

void carddraw(int deck[][14], int hand[][20], int *limit, int *sum, int *played_cards, int *softflag){
    int suit, rank;
    suit = rand()%4;
    rank = rand()%14;
    if(deck[suit][rank]==0){
        deck[suit][rank]++;
        hand[0][*limit] = suit;
        hand[1][*limit] = rank;
        (*limit)++;
        //printf("%d\n", *limit);
        (*sum) = sumcheck(rank, *sum, softflag);
        (*played_cards)++;
        (*played_cards) = card_check(*played_cards, deck);
    }
}

int game(int deck[][14], int *played_cards){
    int setup = 0;
    int dealerhand[2][20] = {0};
    int playerhand[2][20] = {0};
    int dealerlimit = 0, playerlimit = 0; 
    int dealersum = 0, playersum = 0, softflagdealer = 0, softflagplayer = 0;
    
    
    do{ //Dealer
        carddraw(deck, dealerhand, &dealerlimit, &dealersum, played_cards, &softflagdealer);
    } while(dealerlimit<=1);
    
    do{ //Player
        carddraw(deck, playerhand, &playerlimit, &playersum, played_cards, &softflagplayer);
    } while(playerlimit<=1);
    
    int start = playersum;
    int player_turn = 0;
    int choice;
    while(player_turn==0){
        printf("Dealer\n"); 
        draw_cards(dealerlimit, dealerhand);
        printf("Sum: %d\n", dealersum);
        printf("Player\n");
        draw_cards(playerlimit, playerhand);
        printf("Sum: %d\n", playersum);
        if(playersum>=21 || dealersum>=21){
            break;
        }
        
        do{
            printf("Choose action: 1. Draw 2. Stand 3. View Deck: ");
            scanf("%d", &choice);
        } while(choice<=0 || choice>=4);
        
        if(choice==1){
            do{ //Player
                carddraw(deck, playerhand, &playerlimit, &playersum, played_cards, &softflagplayer);
            } while(start==playersum);
            start = playersum;
        }
        else if(choice==2){
            player_turn++;
        }
        else{
            print_deck(deck);
        }
    }

    if(playersum>21){
        return 0;
    }
    else{
        if(dealersum>=17){
            if(playersum>dealersum){
                return 1;
            }
            else if(playersum==dealersum){
                return 2;
            }
            else{
                return 0;
            }
        }
        else{
            do{ //Dealer
                carddraw(deck, dealerhand, &dealerlimit, &dealersum, played_cards, &softflagdealer);
            } while(dealersum<17);

            printf("Dealer\n"); 
            draw_cards(dealerlimit, dealerhand);
            printf("Sum: %d\n", dealersum);
            printf("Player\n");
            draw_cards(playerlimit, playerhand);
            printf("Sum: %d\n", playersum);

            if(dealersum>21){
                return 1;
            }
            else if(playersum>dealersum){
                return 1;
            }
            else if(playersum==dealersum){
                return 2;
            }
            else{
                return 0;
            }

        }
    }
    
}

int main(){
    first_time_set();
    char name[50];
    int money;
    int seed;
    FILE *fp;
    int choice;
    int deck[4][14];

    while(1){
        choice = startupscreen();
        if(choice==3){
            leaderboard();
            continue;
        }
        else if(choice==1){
            new_game(name, &money, &seed, deck);
        }
        else if(choice==2){
            fp = fopen("savegame.txt", "r");
            fscanf(fp, "%s %d %d", name, &money, &seed);
            for(int i = 0; i<4; i++){
                for(int j = 0; j<14; j++){
                    fscanf(fp, "%d", &deck[i][j]);
                }
            }
            fclose(fp);
        }
        srand(seed);
        int played_cards = 0;
        int bet, won;
        
        int again = 1;
        while(again==1){
            
            do{
                printf("Choose bet(You have %d money): ", money);
                scanf("%d", &bet);
            } while(bet>money || bet<=0);
            money -=bet;
            
            won = game(deck, &played_cards);
            
            if(won==0){
                printf( RED "You lost %d money!\n" RESET, bet);
            }
            else if(won==1){
                printf(GREEN "You won %d money!\n" RESET, bet);
                money += 2*bet;
            }
            else if(won==2){
                printf("You tied!\n");
                money += bet;
            }
            savegame(name, &money, &seed, deck);

            if(money==0){
                printf(RED "You lost completely!\n" RESET);
                leaderboard_save_delete(money);
                break;
            }

            do{
                printf(GREEN "Choose what to do next:\n1. Play again?\n2.Quit\n3.End game and put your money in the leaderboard\n" RESET);
                scanf("%d", &again);
            } while(again<1 || again>3);

            if(again==2){
                return 0;
            }
            else if(again == 3){
                leaderboard_save_delete(money);
            }
        }
    }
}
