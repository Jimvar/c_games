#ifndef CARDSYSTEM_H
#define CARDSYSTEM_H

int card_check(int played_cards, int deck[][4][14], int limitcards);
char symbolmatcher(int symbol);
int sumcheck(int symbol, int sum, int *flag);
void carddraw(int deck[][4][14], int hand[][20], int *limit, int *sum, int *played_cards, int *softflag, int limitcards, int packs);
int game(char name[], int deck[][4][14], int *played_cards, int double_down, int *flagdoubling, int packs, int limitcards);

#endif