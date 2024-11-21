#ifndef SAVINGSYSTEM_H
#define SAVINGSYSTEM_H

void first_time_set();
void new_game(char name[], int *money, int *seed, int deck[][14]);
void load_game(char name[], int *money, int *seed, int deck[][14]);
void leaderboard_save_delete(int money);
void savegame(char name[], int *money, int *seed, int deck[][14]);

#endif 