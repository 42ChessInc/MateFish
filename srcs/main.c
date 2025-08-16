#include "board.h"
#include <stdio.h>

void initialize_board(t_board *board)
{
	board->turn = 0; // 0 for player 1, 1 for player 2
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board->board[i][j] = 0; // Initialize all squares to empty
		}
	}

	board->turn = WHITE;
		// Place black pieces
	board->board[0][0] = ROOK | BLACK;
	board->board[0][1] = KNIGHT | BLACK;
	board->board[0][2] = BISHOP | BLACK;
	board->board[0][3] = QUEEN | BLACK;
	board->board[0][4] = KING | BLACK;
	board->board[0][5] = BISHOP | BLACK;
	board->board[0][6] = KNIGHT | BLACK;
	board->board[0][7] = ROOK | BLACK;
	for (int i = 0; i < 8; i++)
		board->board[1][i] = PAWN | BLACK;

	// Place white pieces
	board->board[7][0] = ROOK | WHITE;
	board->board[7][1] = KNIGHT | WHITE;
	board->board[7][2] = BISHOP | WHITE;
	board->board[7][3] = QUEEN | WHITE;
	board->board[7][4] = KING | WHITE;
	board->board[7][5] = BISHOP | WHITE;
	board->board[7][6] = KNIGHT | WHITE;
	board->board[7][7] = ROOK | WHITE;
	for (int i = 0; i < 8; i++)
		board->board[6][i] = PAWN | WHITE;
}


void print_board(const t_board *board)
{
	int column = 0;
	while (column < 8)
	{
		int row_pos = 0;
		printf("%d ", 8 - column);


		while (row_pos < 8)
		{	//change write to printf(%s, char)
			 if (board->board[column][row_pos] != EMPTY)
			 {
			 	if (board->board[column][row_pos] == (PAWN | BLACK))
				{
					printf("%s", BLACK_PAWN_CHAR);
				}
				else if (board->board[column][row_pos] == (ROOK | BLACK))
				{
					printf("%s", BLACK_ROOK_CHAR);
				}
				else if (board->board[column][row_pos] == (KNIGHT | BLACK))
				{
					printf("%s", BLACK_KNIGHT_CHAR);
				}
				else if (board->board[column][row_pos] == (BISHOP | BLACK))
				{
					printf("%s", BLACK_BISHOP_CHAR);
				}
				else if (board->board[column][row_pos] == (QUEEN | BLACK))
				{
					printf("%s", BLACK_QUEEN_CHAR);
				}
				else if (board->board[column][row_pos] == (KING | BLACK))
				{
					printf("%s", BLACK_KING_CHAR);
				}
				else if (board->board[column][row_pos] == (PAWN | WHITE))
				{
					printf("%s", WHITE_PAWN_CHAR);
				}
				else if (board->board[column][row_pos] == (ROOK | WHITE))
				{
					printf("%s", WHITE_ROOK_CHAR);
				}
				else if (board->board[column][row_pos] == (KNIGHT | WHITE))
				{
					printf("%s", WHITE_KNIGHT_CHAR);
				}
				else if (board->board[column][row_pos] == (BISHOP | WHITE))
				{
					printf("%s", WHITE_BISHOP_CHAR);
				}
				else if (board->board[column][row_pos] == (QUEEN | WHITE))
				{
					printf("%s", WHITE_QUEEN_CHAR);
				}
				else if (board->board[column][row_pos] == (KING | WHITE))
				{
					printf("%s", WHITE_KING_CHAR);
				}
			 }
			else  if ((column + row_pos) % 2 == 0)
			{
				printf("%s", "#");
			}
			else
			{
				printf("%s", "*");
			}
			if (row_pos < 7)
				printf("%s", " " );
			row_pos++;
		}
		printf("\n");
		if (column == 7)
			printf("  A B C D E F G H\n");
		column++;
	}
}
int	main(void)
{
	t_board board;
	initialize_board(&board);
	print_board(&board);

	return (0);
}
