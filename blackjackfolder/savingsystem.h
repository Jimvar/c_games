#ifndef SAVINGSYSTEM_H
#define SAVINGSYSTEM_H

void first_time_set();
void new_game(char name[], long long *money, long long *seed, float *multiplier, int deck[][14]);
void load_game(char name[], long long *money, long long *seed, float *multiplier, int deck[][14]);
void load_stats(long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost);
void leaderboard_save_delete(long long money);
void savegame(char name[], long long *money, long long *seed, float *multiplier, int deck[][14]);
void save_stats(long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost);
void resetchoice(int choice);

#endif 