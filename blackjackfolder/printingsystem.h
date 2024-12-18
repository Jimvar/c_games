#ifndef PRINTINGSYSTEM_H
#define PRINTINGSYSTEM_H

#define GREEN "\x1b[1;32m"
#define RED   "\x1b[1;31m"
#define CARDRED "\x1b[1;38;5;197m"
#define CARDGREEN "\x1b[1;38;5;28m"
#define CARDYELLOW  "\x1b[1;38;5;172m"
#define CARDGRAY "\x1b[1;38;5;26m"
#define BBLU  "\x1b[1;38;5;19m"
#define BLACK "\x1b[1;90m"
#define RESET "\x1b[0m"
#define YELLOW "\x1b[1;93m"
#define CYAN "\x1b[1;38;5;123m"
#define BLUEISH "\x1b[1;38;5;37m"
#define PINK "\x1b[1;38;5;210m"
#define BORE "\x1b[1;38;5;94m"
#define DEALER "\x1b[1;38;5;88m"
#define PLAYER "\x1b[0;38;5;69m"

extern const char *colors[];

int startupscreen();
void leaderboard();
void stats(long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost, float *biggestmult);
void achievements(int achievements_track[], long long *overallplayed, long long *totalwins);
void achieve_check(int achievements_track[], long long *money, float *multiplier, long long *overallplayed, long long *totalwins);
void reset_prompt();
void print_deck(int deck[][4][14], int packs);
void draw_cards(int how_many, int hand[][20]);

#endif 