#ifndef CARDSYSTEM_H
#define CARDSYSTEM_H

int card_check(int played_cards, int deck[][14]);
char symbolmatcher(int symbol);
int sumcheck(int symbol, int sum, int *flag);
int game(int deck[][14], int *played_cards);

#endif