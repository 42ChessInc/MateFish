/* ************************************************************************** */
/*    */
/*  :::::::::::   */
/*   main.c   :+::+:    :+:   */
/*    +:+ +:+   +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+ +#+  */
/*+#+#+#+#+#+   +#+     */
/*   Created: 2025/01/25 17:42:20 by rafaelfe    #+#    #+# */
/*   Updated: 2025/05/15 16:45:52 by rafaelfe   ###   ########.fr */
/*    */
/* ************************************************************************** */

#include "../../includes/interface.h"

int mouse_hook(int button, int x, int y, t_interface *interface)
{
	char piece;
	piece = get_piece(interface->board, x / 64, y / 64);
	int mouse_x = x / 64;
	int mouse_y = y / 64;

	if (mouse_x < 0 || mouse_x >= 8 || mouse_y < 0 || mouse_y >= 8)
		return (0);
	if (button == 1) // Left mouse button
	{
		if (interface->board->turn == WHITE)
		{
			if (IS_WHITE(piece))
			{
				interface->selected_piece[0] = mouse_x;
				interface->selected_piece[1] = mouse_y;
				interface->mouse_pressed = 1;
			}
			else if (interface->selected_piece[0] != -1 && is_valid_move(interface->board, interface->selected_piece[1], interface->selected_piece[0], mouse_y, mouse_x))
			{
				char from_piece = get_piece(interface->board, interface->selected_piece[0], interface->selected_piece[1]);
				char to_piece = get_piece(interface->board, mouse_x, mouse_y);
				interface->mouse_pressed = 0;
				interface->board->board[mouse_y][mouse_x] = from_piece;
				interface->board->board[interface->selected_piece[1]][interface->selected_piece[0]] = EMPTY;

				if ((from_piece & KING) == KING)
				{
					interface->board->white_king_pos[0] = mouse_x;
					interface->board->white_king_pos[1] = mouse_y;
				}
				interface->board->turn = (interface->board->turn == WHITE) ? BLACK : WHITE;
				if (is_in_check(interface->board))
				{
					interface->board->board[interface->selected_piece[1]][interface->selected_piece[0]] = from_piece;
					interface->board->board[mouse_y][mouse_x] = to_piece;
					interface->selected_piece[0] = -1;
					interface->selected_piece[1] = -1;
					interface->board->turn = (interface->board->turn == WHITE) ? BLACK : WHITE;
					fprintf(stderr, "Invalid move: King is in check.\n");
					return (0);
				}

				interface->selected_piece[0] = -1;
				interface->selected_piece[1] = -1;
			}
		}
		else
		{
			if (IS_BLACK(piece))
			{
				interface->selected_piece[0] = mouse_x;
				interface->selected_piece[1] = mouse_y;
				interface->mouse_pressed = 1;
			}
			else if (interface->selected_piece[0] != -1 && is_valid_move(interface->board, interface->selected_piece[1], interface->selected_piece[0], mouse_y, mouse_x))
			{
				char from_piece = get_piece(interface->board, interface->selected_piece[0], interface->selected_piece[1]);
				char to_piece = get_piece(interface->board, mouse_x, mouse_y);
				interface->mouse_pressed = 0;
				interface->board->board[mouse_y][mouse_x] = from_piece;
				interface->board->board[interface->selected_piece[1]][interface->selected_piece[0]] = EMPTY;

				if ((from_piece & KING) == KING)
				{
					interface->board->black_king_pos[0] = mouse_x;
					interface->board->black_king_pos[1] = mouse_y;
				}
				if (is_in_check(interface->board))
				{
					interface->board->board[interface->selected_piece[1]][interface->selected_piece[0]] = from_piece;
					interface->board->board[mouse_y][mouse_x] = to_piece;
					fprintf(stderr, "Invalid move: King is in check.\n");
					return (0);
				}
				interface->board->turn = (interface->board->turn == WHITE) ? BLACK : WHITE;
				interface->selected_piece[0] = -1;
				interface->selected_piece[1] = -1;
			}
		}

	}

	return (0);
}


void run_chess(t_board *board)
{
	t_interface interface;

	interface.board = board;
	interface.index_lookup = malloc(64 * sizeof(unsigned char));
	if (!interface.index_lookup)
	{
		fprintf(stderr, "Error allocating memory for index lookup.\n");
		exit(EXIT_FAILURE);
	}
	interface.mouse_pressed = 0;
	interface.index_lookup[PAWN] = 0;
	interface.index_lookup[ROOK] = 1;
	interface.index_lookup[KNIGHT] = 2;
	interface.index_lookup[BISHOP] = 3;
	interface.index_lookup[QUEEN] = 4;
	interface.index_lookup[KING] = 5;

	interface.selected_piece[0] = -1;
	interface.selected_piece[1] = -1;

	init_window(&interface);
	get_textures(&interface);
	mlx_hook(interface.win_ptr, DestroyNotify, (1L<<17), free_displays, &interface);
	mlx_mouse_hook(interface.win_ptr, mouse_hook, &interface);
	mlx_loop_hook(interface.mlx_ptr, interface_loop, &interface);
	mlx_loop(interface.mlx_ptr);
}




