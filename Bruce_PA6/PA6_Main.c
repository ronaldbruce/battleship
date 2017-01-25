#include "PA6_Header.h"

int main()
{
	srand((unsigned int)time(NULL));
	char board1[10][10];
	char board2[10][10];
	//both boards are created
	FILE * outfile = open_output_file();
	int set_ships;
	int target_row;
	int target_col;
	int starter;
	bool hit;
	bool sunk;
	// initialize struct variables
	Player_stats p1;
	Player_stats p2;
	p1.hits = 0;
	p1.hit_miss_ratio = 0.0;
	p1.misses = 0;
	p1.shots_taken = 0;
	p1.winner = false;
	p2.hits = 0;
	p2.hit_miss_ratio = 0.0;
	p2.misses = 0;
	p2.shots_taken = 0;
	p2.winner = false;
	//fill game boards
	initialize_game_board(board1);
	initialize_game_board(board2);
	//print rules
	welcome_screen();
	printf("hit enter to continue \n");
	getch();
	system("cls");
	// print strting menu
	printf("Please select from the following menu:\n");
	printf("1. Enter positions of ships manually.\n");
	printf("2. Allow the program to randomly select positions of ships.\n");
	printf("enter 1 or 2: ");
	scanf("%d", &set_ships);
	// beat dat ass up 
	if (set_ships == 1)
	{
		manually_place_ships_on_board(board1);
	}
	else
	{
		randomly_place_ships_on_board(board1);
	}
	// i got broads in atlanta
	randomly_place_ships_on_board(board2);
	printf("\nplayer2's board has been generated. \n");
	starter = select_who_starts_first();
	// randomly selects who goes first
	printf("player%d will go first\n", starter);

	if (starter == 1) // player 1 starting
	{
		while (is_winner(board1, board2) == 0) // while there is not a winner
		{
			
			display_board(board1, 1);
			display_board(board2, 2);
			printf("enter a target: ");
			scanf("%d%d", &target_row, &target_col);
			system("cls");
			sunk = check_if_sunk_ship(board2, target_row, target_col, 1);// returns boolean
			hit = take_shot(board2, target_row, target_col);// returns boolean
			if (hit == true)
			{
				p1.hits++;
			}
			else {
				p1.misses++;
			}

			output_current_move(outfile, 1, target_row, target_col, hit, sunk);// to file
			display_board(board1, 1);
			display_board(board2, 2);

			target_row = rand() % 10;
			target_col = rand() % 10;
			printf("\nplayer2 selected %d %d\n", target_row, target_col);
			sunk = check_if_sunk_ship(board1, target_row, target_col, 1);// returns boolean
			hit = take_shot(board1, target_row, target_col);// returns boolean
			if (hit == true)
			{
				p2.hits++;
			}
			else {
				p2.misses++;
			}
			output_current_move(outfile, 2, target_row, target_col, hit, sunk);
			printf("hit enter to continue \n");
			getch();
			system("cls");
			p1.shots_taken++;
			p2.shots_taken++;
		}
	}
	else // player 2 is selected to go first
	{
		while (is_winner(board1, board2) == 0)// same while condition
		{
			display_board(board1, 1);
			display_board(board2, 2);

			target_row = rand() % 10; 
			target_col = rand() % 10;
			printf("\nplayer2 selected %d %d\n", target_row, target_col);
			sunk = check_if_sunk_ship(board1, target_row, target_col, 1);
			hit = take_shot(board1, target_row, target_col);
			if (hit == true) // tracking hits
			{
				p2.hits++;
			}
			else {
				p2.misses++;
			}
			output_current_move(outfile, 2, target_row, target_col, hit, sunk);
			printf("hit enter to continue \n");
			getch();
			system("cls");
			display_board(board1, 1);
			display_board(board2, 2);
			printf("enter a target: ");
			scanf("%d%d", &target_row, &target_col);
			sunk = check_if_sunk_ship(board2, target_row, target_col, 1);// returns boolean
			hit = take_shot(board2, target_row, target_col);// returns boolean
			system("cls");
			if (hit == true)
			{
				p1.hits++;
			}
			else {
				p1.misses++;
			}
			output_current_move(outfile, 1, target_row, target_col, hit, sunk);// goes to file
			p1.shots_taken++;
			p2.shots_taken++;
		}
	}
	if (is_winner(board1, board2) == 1) // for stats
	{
		p1.winner = true;
	}
	else if (is_winner(board1, board2) == 2)
	{
		p2.winner = true;
	}
	output_stats(outfile,p1,1); // output stats to file
	output_stats(outfile,p2,2);

	return 0;
}
