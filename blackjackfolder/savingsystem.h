#ifndef SAVINGSYSTEM_H
#define SAVINGSYSTEM_H

void first_time_set();
void new_game(char name[], long long *money, long long *seed, float *multiplier, int *buffed_mult, int deck[][4][14], int *packs, int *limitcards, int *played_cards, int achievements_track[]);
void load_game(char name[], long long *money, long long *seed, float *multiplier, int *buffed_mult, int deck[][4][14], int *packs, int *limitcards, int *played_cards);
void load_stats(long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost);
void load_achievements(int achievements_track[]);
void leaderboard_save_delete(long long money);
void savegame(char name[], long long *money, long long *seed, float *multiplier, int *buffed_mult, int deck[][4][14], int *packs, int *limitcards, int *played_cards);
void save_stats(long long *overallplayed, long long *totalwins, long long *totallost, long long *totalties, long long *moneygained, long long *moneylost);
void save_achievements(int achievements_track[]);
void resetchoice(int choice);

#endif 