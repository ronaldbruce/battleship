#include <stdio.h>
#include <stdbool.h>
#ifndef STRUCTURES_H
#define STRUCTURES_H

int select_who_starts_first();
int is_winner(char board1[10][10], char board2[10][10]);

bool take_shot(char board[10][10],int row, int col);
bool check_if_sunk_ship(char board[10][10],int row, int col,int player);

void welcome_screen();
void initialize_game_board(char board[10][10]);
void manually_place_ships_on_board(char board1[10][10]);
void randomly_place_ships_on_board(char board2[10][10]);

FILE * open_output_file();
void display_board(char board[10][10], int player);

void set_ship(char board[10][10], int ship_length, int direction, char ship_symbol);
void output_current_move(FILE *outfile, int player, int row, int col, bool hit, bool sunk);
struct player_stats {

	int hits;
	int misses;
	int shots_taken;
	double hit_miss_ratio;
	bool winner;

};
typedef struct player_stats Player_stats;
void output_stats(FILE *outfile, Player_stats player, int playa);


#endif