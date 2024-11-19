#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GREEN "\x1b[1;32m"
#define RED     "\x1b[1;31m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
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

    printf("Blackjack\nChoose:\n");
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

void new_game(char name[], int *money, int *seed, int *seedflag, int *timer){
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
        *seedflag = 1;
        fprintf(fp, "%d %d ", *seed, *seedflag);
    }
    else{
        *seed = time(NULL);
        *seedflag = 0;
        fprintf(fp, "%d %d ", *seed, *seedflag);
    }
    
    *timer = 0;
    fprintf(fp, "%d", *timer);

    fclose(fp);
}

void card_check(int played_cards, int deck[][14]){
    if(played_cards==56){
        for(int i = 0 ; i<4; i++){
            for(int j = 0; j<14; j++){
                deck[i][j] = 0;
            }
        }
    }
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
                    deck[k][j] ?  putchar('-')  : printf("%c", deck[k][j] + '0' + j);
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

void draw_cards(int questionflag, int how_many, int current_play[2][30], int k, int *start){
    int color;
    
    if(questionflag==1){
        for(int i = 0; i<how_many; i++){
            //color = choose_color();
            printf(" ---  ");
        }
        putchar('\n');
        for(int i = 0; i<3; i++){
            for(int j = 0; j<how_many; j++){
                printf("| ");
                if(i==1){
                    j==1 ? putchar('?') : printf("%c", current_play[1][*start] + '0');
                    (*start)++;
                }
                else{
                    putchar(' ');
                }
                printf(" | ");
            }
            putchar('\n');
        }
        for(int i = 0; i<how_many; i++){
            printf(" ---  ");
        }
    }
    else{
        for(int i = 0; i<how_many; i++){
            printf(" ---  ");
        }
        putchar('\n');
        for(int i = 0; i<3; i++){
            for(int j = 0; j<how_many; j++){
                printf("| ");
                if(i==1){
                    printf("%c", current_play[1][*start] + '0');
                    (*start)++;
                }
                else{
                    putchar(' ');
                }
                printf(" | ");
            }
            putchar('\n');
        }
        for(int i = 0; i<how_many; i++){
            printf(" ---  ");
        }
    }
    putchar('\n');
}

int game(int deck[][14], int *played_cards){
    int setup = 0;
    int current_play[2][30] = {0};
    int k = 0;
    int suit, rank, dealersum = 0, playersum = 0;
    
    do{ //Dealer
        suit = rand()%4;
        rank = rand()%14;
        if(deck[suit][rank]==0){
            deck[suit][rank]++;
            current_play[0][k] = suit;
            current_play[1][k] = rank;
            k++;
            dealersum += rank;
            (*played_cards)++;
            setup++;
            card_check(*played_cards, deck);
        }
    } while(setup<=1);
    
    setup = 0;
    
    do{ //Player
        suit = rand()%4;
        rank = rand()%14;
        if(deck[suit][rank]==0){
            deck[suit][rank]++;
            current_play[0][k] = suit;
            current_play[1][k] = rank;
            k++;
            playersum += rank;
            (*played_cards)++;
            setup++;
            card_check(*played_cards, deck);
        }
    } while(setup<=1);
    
    int start = 0;
    int player_turn = 0;
    int choice;
    while(player_turn==0){
        printf("Dealer\n"); //1 for question, 0 for normal
        draw_cards(1, 2, current_play, k, &start);
        printf("Player\n");
        draw_cards(0, 2, current_play, k, &start);
        start = 0;
        if(playersum>21){
            break;
        }
        
        do{
            printf("Choose action: 1. Draw 2. Stand 3. View Deck: ");
            scanf("%d", &choice);
        } while(choice<=0 || choice>=4);
        
        if(choice==1){
            
        }
        else if(choice==2){
            player_turn++;
        }
        else{
            print_deck(deck);
        }
    }
    
}

int main(){
    first_time_set();
    char name[50];
    int money;
    int seed, seedflag;
    int timer;
    FILE *fp;
    int choice;

    while(1){
        choice = startupscreen();
        if(choice==3){
            leaderboard();
            continue;
        }
        else if(choice==1){
            new_game(name, &money, &seed, &seedflag, &timer);
        }
        else if(choice==2){
            fp = fopen("savegame.txt", "r");
            fscanf(fp, "%s %d %d %d %d", name, &money, &seed, &seedflag, &timer);
            fclose(fp);
        }
        srand(seed);
        int deck[4][14] = {0};
        int played_cards = 0;
        int bet, won;
        
        int again = 1;
        while(again==1){
            
            do{
                printf("Choose bet(You have %d money): ", money);
                scanf("%d", &bet);
            } while(bet>money);
            money -=bet;
            
            won = game(deck, &played_cards);
            
            if(won==0){
                printf("You lost %d money!\n", bet);
            }
            else if(won==1){
                printf("You won %d money!\n", bet);
                money += 2*bet;
            }
            else if(won==2){
                printf("You tied!\n");
                money += bet;
            }
            again = 0;
            printf("Again?(Write 1): ");
            scanf("%d", &again);
            
        }
    }
}
