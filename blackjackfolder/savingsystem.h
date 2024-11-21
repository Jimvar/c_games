#ifndef SAVINGSYSTEM_H
#define SAVINGSYSTEM_H

void first_time_set();
void new_game(char name[], int *money, int *seed, int deck[][14]);
void load_game(char name[], int *money, int *seed, int deck[][14]);
void load_stats(int *overallplayed, int *totalwins, int *totallost, int *totalties, int *moneygained, int *moneylost);
void leaderboard_save_delete(int money);
void savegame(char name[], int *money, int *seed, int deck[][14]);
void savestats(int *overallplayed, int *totalwins, int *totallost, int *totalties, int *moneygained, int *moneylost);

#endif 