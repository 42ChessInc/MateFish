#include "board.h"
#include <stdio.h>

void initialize_board(t_board *board)
{
	board->turn = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board->board[i][j] = 0;
		}
	}

	board->turn = WHITE;

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
		{
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
			else if ((column + row_pos) % 2 == 0)
			{
				printf("%s", "#");
			}
			else
			{
				printf("%s", "*");
			}
			if (row_pos < 7)
				printf(" ");

			row_pos++;
		}
		printf("\n");
		if (column == 7)
			printf("  a b c d e f g h\n");
		column++;
	}
}

int move_piece(t_board *board, char *move)
{
	if (strlen(move) != 5)
	{
		fprintf(stderr, "Invalid move format. Use 'e2e4' format.\n");
		return -1;
	}

	int start_row = move[0] - 'a';
	int start_col = 8 - (move[1] - '0');
	int end_row = move[2] - 'a';
	int end_col = 8 - (move[3] - '0');
	if (start_col < 0 || start_col > 7 || start_row < 0 || start_row > 7 ||
		end_col < 0 || end_col > 7 || end_row < 0 || end_row > 7)
	{		fprintf(stderr, "Move out of bounds.\n");
		return -1;
	}
	int piece = board->board[start_col][start_row];
	if (piece == EMPTY)
	{
		fprintf(stderr, "No piece at starting position.\n");
		return -1;
	}
	if ((piece & WHITE) && board->turn == BLACK)
	{
		fprintf(stderr, "It's not your turn.\n");
		return -1;
	}
	if ((piece & BLACK) && board->turn == WHITE)
	{
		fprintf(stderr, "It's not your turn.\n");
		return -1;
	}
	if (!is_valid_move(board, start_col, start_row, end_col, end_row))
	{
		fprintf(stderr, "Invalid move for the piece.\n");
		return -1;
	}
	board->board[end_col][end_row] = piece;
	board->board[start_col][start_row] = EMPTY;
	board->turn = (board->turn == WHITE) ? BLACK : WHITE;

	return 0;
}
int	main(void)
{
	t_board board;
	initialize_board(&board);
	print_board(&board);
	char move[6];
	int bytesread = 0;
	while (1)
	{
		if (board.turn == WHITE)
			printf("White's turn.\n");
		else
			printf("Black's turn.\n");
		printf("Enter your move: \n");
		bytesread = read(0, move, 5);
		if (bytesread == -1)
		{
			perror("getline");
			return (1);
		}
		move[bytesread ] = '\0';
		printf("You entered: %s\n\n", move);
		move_piece(&board, move);
		print_board(&board);
	}

	return (0);
}
