#ifndef CARDSYSTEM_H
#define CARDSYSTEM_H

long long read_number();
int card_check(int played_cards, int deck[][4][14], int limitcards);
char symbolmatcher(int symbol);
int sumcheck(int symbol, int sum, int *flag);
void carddraw(int deck[][4][14], int hand[][20], int *limit, int *sum, int *played_cards, int *softflag, int limitcards, int packs);
int game(char name[], int deck[][4][14], int *played_cards, int packs, int limitcards, int *win, int *loss, int *tie, long long *money, float *multiplier, long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost, float *biggestmult, float *mult_increase, float *mult_double, float *all_in_mult);

#endif