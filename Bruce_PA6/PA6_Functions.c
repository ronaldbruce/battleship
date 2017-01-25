#include "PA6_Header.h"

/*******************************************
purpose: to print the rules
return type: void
paramater types: void
*******************************************/
void welcome_screen()
{
	printf("***** Welcome to Battleship! ***** \n");
	printf("Rules of the Game: \n");
	printf("1. This is a two player game. \n");
	printf("2. Player1 is you and Player2 is the computer. \n");
	printf("3. you win by sinking all 5 of the opponents board \n");
	printf("4. you will take turns guessing coordinates \n");
	printf("5. the computer will tell you if it is a hit or miss \n");
	printf("\n");
}
/*******************************************
purpose: to initialize the game board
return type: void
paramater types: void
*******************************************/
void initialize_game_board(char board[10][10])
{
	int i;
	int j;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			board[i][j] = '_';
		}
	}
}
/*******************************************
purpose: selects who starts first
return type: int
paramater types: void
*******************************************/
int select_who_starts_first()
{
	int player;
	player = (rand() % 2) + 1;
	return player;
}
/*******************************************
purpose: to place ships on board
return type: void
paramater types: char 2d array
*******************************************/
void manually_place_ships_on_board(char board1[10][10])
{
	int i;
	int row;
	int col;
	int coordinates[100] = { 0 };
	
	printf("enter the coordinates for the carrier (5 coordinates with the form: row# col# row# col# etc.) : ");
	scanf("%d%d %d%d %d%d %d%d %d%d", &coordinates[1], &coordinates[2], &coordinates[3], &coordinates[4], &coordinates[5], &coordinates[6], &coordinates[7], &coordinates[8], &coordinates[9], &coordinates[10]);
	
	printf("\n enter the coordinates for the battleship (4 coordinates with the form row# col# row# col# etc.) : ");
	scanf("%d%d %d%d %d%d %d%d", &coordinates[11], &coordinates[12], &coordinates[13], &coordinates[14], &coordinates[15], &coordinates[16], &coordinates[17], &coordinates[18]);

	printf("\n enter the coordinates for the cruiser (3 coordinates with the form row# col# row# col# etc.) :");
	scanf("%d%d %d%d %d%d", &coordinates[19], &coordinates[20], &coordinates[21], &coordinates[22], &coordinates[23], &coordinates[24]);

	printf("\n enter the coordinates for the submarine (3 coordinates with the form row# col# row# col# etc.) :");
	scanf("%d%d %d%d %d%d", &coordinates[25], &coordinates[26], &coordinates[27], &coordinates[28], &coordinates[29], &coordinates[30]);

	printf("\n enter the coordinates for the destroyer (2 coordinates with the form row# col# row# col#) :");
	scanf("%d%d %d%d", &coordinates[31], &coordinates[32], &coordinates[33], &coordinates[34]);

	for (i = 1; i < 35; i += 2)
	{
		row = coordinates[i];
		col = coordinates[i + 1];

		if (i <= 10)
		{
			board1[row][col] = 'C';
		}
		else if (i > 10 && i <= 18)
		{
			board1[row][col] = 'B';
		}
		else if (i > 18 && i <= 24)
		{
			board1[row][col] = 'R';
		}
		else if (i > 24 && i <= 30)
		{
			board1[row][col] = 'S';
		}
		else if (i > 30 && i <= 34)
		{
			board1[row][col] = 'D';
		}
	}
	printf("player 1's board has been set \n");
}
/*******************************************
purpose: to place ships on board
return type: void
paramater types: char 2d array
*******************************************/
void randomly_place_ships_on_board(char board2[10][10])
{
	int dir;
	dir = (rand() % 2) + 1;
	set_ship(board2, 5, dir, 'C');
	dir = (rand() % 2) + 1;
	set_ship(board2, 4, dir, 'B');
	dir = (rand() % 2) + 1;
	set_ship(board2, 3, dir, 'S');
	dir = (rand() % 2) + 1;
	set_ship(board2, 3, dir, 'R');
	dir = (rand() % 2) + 1;
	set_ship(board2, 2, dir, 'D');
	
}
/*******************************************
purpose: to place ships on board
return type: void
paramater types: char 2d array, int, int, char
*******************************************/
void set_ship(char board[10][10], int ship_length, int direction,char ship_symbol)
{
	int index = 0;
	int row_start;
	int col_start;
	bool can_set = false;

	while (can_set == false) {
		can_set = true;
		if (direction == 1)
		{
			row_start = rand() % 10; // 0 - 9
			col_start = rand() % (10 - (ship_length - 1));
		}
		else
		{
			row_start = rand() % (10 - (ship_length - 1));
			col_start = rand() % 10; // 0 - 9
		}
		for (index = 0; index < ship_length; index++)
		{
			if (direction == 1)
			{
				if (board[row_start][col_start + index] != '_')
				{
					can_set = false;
				}
			}
			else
			{
				if (board[row_start + index][col_start] != '_')
				{
					can_set = false;
				}
			}
		}
		if (can_set == true) {

			for (index = 0; index < ship_length; index++)
			{
				if (direction == 1)
				{
					board[row_start][col_start + index] = ship_symbol;
				}
				else
				{
					board[row_start + index][col_start] = ship_symbol;
				}
			}
		}
	}
}
/*******************************************
purpose: to determine if shot is hit or miss
return type: boolean
paramater types: char 2d array, int , int
*******************************************/
bool take_shot(char board[10][10], int row, int col)
{
	if (board[row][col] != '_' && board[row][col] != 'M' && board[row][col] != '*')
	{
		board[row][col] = '*';
		printf("%d,%d is a hit!\n", row, col);
		return true;
	}
	else
	{
		board[row][col] = 'M';
		printf("%d,%d is a miss.\n", row, col);
		return false;
	}
}
/*******************************************
purpose: to determine if there is a winner
return type: bool
paramater types: char 2d array times two 
*******************************************/
int is_winner(char board1[10][10], char board2[10][10])
{
	int winner = 0;
	bool player1 = true;
	bool player2 = true;
	int i;
	int j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (board1[i][j] == 'C' || board1[i][j] == 'D' || board1[i][j] == 'B' || board1[i][j] == 'R' || board1[i][j] == 'S')
			{
				player1 = false;
			}
			else if(board2[i][j] == 'C' || board2[i][j] == 'D' || board2[i][j] == 'B' || board2[i][j] == 'R' || board2[i][j] == 'S')
			{
				player2 = false;
			}
		}
	}
	if (player1 == true && player2 == false)
	{
		return 1;
	}
	else if (player2 == true && player1 == false)
	{
		return 2;
	}
	else
	{
		return false;
	}
}
/*******************************************
purpose: to print the board to the console
return type: void
paramater types: char 2d array, int
*******************************************/
void display_board(char board[10][10], int player)
{
	int i;
	int j;

	printf("   0  1  2  3  4  5  6  7  8  9 \n");

	for (i = 0; i < 10; i++)
	{
		printf("%d ", i);
		for (j = 0; j < 10; j++)
		{
			if (player == 1)
			{
				printf(" %c ", board[i][j]);
			}
			else 
			{
				if (board[i][j] != '*' && board[i][j] != 'M')
				{
					printf(" %c ", '_');
				}
				else
				{
					printf(" %c ", board[i][j]);
				}
			}
		}
		printf("\n");
	}
	printf("\n");
}
/*******************************************
purpose: to check if there is a sunk ship
return type: bool
paramater types: char 2d array, int, int, int
*******************************************/
bool check_if_sunk_ship(char board[10][10], int row, int col, int player)
{
	char ship = board[row][col];
	int i;
	int j;
	int count = 0;

	if (ship != '_' && ship != 'M' && ship != '*')
	{
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (board[i][j] == ship)
				{
					count++;
				}

			}
		}
		if (count == 1 && ship == 'C')
		{
			printf("player%d's Carrier has been sunk. \n",player);
			return true;
		}
		else if (count == 1 && ship == 'D')
		{
			printf("player%d's Destroyer has been sunk. \n", player);
			return true;
		}
		else if (count == 1 && ship == 'B')
		{
			printf("player%d's Battleship has been sunk. \n", player);
			return true;
		}
		else if (count == 1 && ship == 'R')
		{
			printf("player%d's Cruiser has been sunk. \n", player);
			return true;
		}
		else if (count == 1 && ship == 'S')
		{
			printf("player%d's Submarine has been sunk. \n", player);
			return true;
		}
	}
	return false;
}
/*******************************************
purpose: to open an output file
return type: file pointer
paramater types: void
*******************************************/
FILE * open_output_file()
{
	FILE * outfile = NULL;
	outfile = fopen("battleship.log", "w");
	return outfile;
}
/*******************************************
purpose: to print the current players move to the stats file
return type: void
paramater types: whole bunch of shit
*******************************************/
void output_current_move(FILE *outfile, int player, int row,int col, bool hit, bool sunk)
{
	fprintf(outfile, "player%d targeted %d%d \n", player, row, col);

	if (hit == true)
	{
		fprintf(outfile, "player%d hit a ship \n", player);
	}
	if (sunk == true)
	{
		fprintf(outfile, "player%d sunk a ship \n", player);
	}
	fprintf(outfile, "+--------------------------------------+\n");

}
/*******************************************
purpose: to output the final stats
return type: void
paramater types: file pointer, player_stats struct, int
*******************************************/
void output_stats(FILE *outfile,Player_stats player, int playa)
{
	fprintf(outfile, "player%d had %d total hits, %d total misses, and %d total shots \n", playa,player.hits,player.misses,player.shots_taken);
	player.hit_miss_ratio = ((double)player.hits / player.misses);
	fprintf(outfile, "player%d had a %f hit:miss ratio \n", playa,player.hit_miss_ratio);

	if (player.winner == true)
	{
		fprintf(outfile,"player%d is the winner \n", playa);
	}
}