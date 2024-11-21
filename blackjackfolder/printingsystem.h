#ifndef PRINTINGSYSTEM_H
#define PRINTINGSYSTEM_H

#define GREEN "\x1b[1;32m"
#define RED   "\x1b[1;31m"
#define BBLU  "\x1b[1;34m"
#define BMAG  "\x1b[1;35m"
#define RESET "\x1b[0m"

extern const char *colors[];

int startupscreen();
void leaderboard();
void stats(long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost);
void print_deck(int deck[][14]);
void draw_cards(int how_many, int hand[][20]);
void carddraw(int deck[][14], int hand[][20], int *limit, int *sum, int *played_cards, int *softflag);


#endif 