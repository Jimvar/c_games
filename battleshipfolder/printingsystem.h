#ifndef PRINTINGSYSTEM_H
#define PRINTINGSYSTEM_H

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

int startupscreen();
void getname(char player[], int which, int size);
void ship_setup(char player1[], char player2[], int bigturn, int ship_placement[][10][10]);

#endif 