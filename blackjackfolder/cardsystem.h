#ifndef CARDSYSTEM_H
#define CARDSYSTEM_H

int card_check(int played_cards, int deck[][14]);
char symbolmatcher(int symbol);
int sumcheck(int symbol, int sum, int *flag);
void carddraw(int deck[][14], int hand[][20], int *limit, int *sum, int *played_cards, int *softflag);
int game(char name[], int deck[][14], int *played_cards);

#endif