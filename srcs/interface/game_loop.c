/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:06:28 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/08 18:42:28 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/interface.h"

void	drawtext(t_interface *interface)
{
	mlx_string_put(interface->mlx_ptr, interface->win_ptr, 512 + 64, 10, 0xFFFFFF, "Turn: ");
	if (interface->board->turn == WHITE)
		mlx_string_put(interface->mlx_ptr, interface->win_ptr, 512 + 64, 30, 0xFFFFFF, "White");
	else
		mlx_string_put(interface->mlx_ptr, interface->win_ptr, 512 + 64, 30, 0xFFFFFF, "Black");

	if (interface->selected_piece[0] != -1)
	{
		char text[50];
		sprintf(text, "Selected Piece: %c, %d", interface->selected_piece[0] + 'a', 8 - interface->selected_piece[1]);
		mlx_string_put(interface->mlx_ptr, interface->win_ptr, 512 + 64, 50, 0xFFFFFF, text);
	}
	else
	{
		mlx_string_put(interface->mlx_ptr, interface->win_ptr, 512 + 64, 50, 0xFFFFFF, "No Piece Selected");
	}
}

int	update(t_interface *interface)
{
	calculate_Delta(interface);
	mlx_mouse_get_pos(interface->mlx_ptr, interface->win_ptr, &interface->mouse_x, &interface->mouse_y);




	return (1);
}

int	renderer(t_interface *interface)
{
	memset(interface->image.addr, 0, SCREEN_SIZE_X * SCREEN_SIZE_Y * (interface->image.bits_per_pixel / 8));
	drawtext(interface);
	drawboard(interface, interface->board);


	mlx_put_image_to_window(interface->mlx_ptr, interface->win_ptr, interface->image.img, 0, 0);
	drawtext(interface);
	return (1);
}

int interface_loop(t_interface *interface)
{
	update(interface);
	// Automate both sides using Stockfish
	if (interface->board->turn == WHITE || interface->board->turn == BLACK) {
		char *stockmove = communicate_with_stockfish(interface->moves);
		if (stockmove && strlen(stockmove) == 4) {
			int from_col = stockmove[0] - 'a';
			int from_row = 8 - (stockmove[1] - '0');
			int to_col = stockmove[2] - 'a';
			int to_row = 8 - (stockmove[3] - '0');
			unsigned char from_piece = get_piece(interface->board, from_col, from_row);
			
			if (from_piece == (KING | WHITE) || from_piece == (KING | BLACK))
			{
				if (interface->board->turn == WHITE)
				{
					if (to_row == 7 && to_col == 6)
					{
						interface->board->board[to_row][to_col + 1] = EMPTY;
						interface->board->board[from_row][from_col + 1] = (ROOK | WHITE);
					}
					if (to_row == 7 && to_col == 2)
					{
						interface->board->board[to_row][to_col - 2] = EMPTY;
						interface->board->board[from_row][from_col - 1] = (ROOK | WHITE);
					}
				}
				if (interface->board->turn == BLACK)
				{
					if (to_row == 0 && to_col == 6)
					{
						interface->board->board[to_row][to_col + 1] = EMPTY;
						interface->board->board[from_row][from_col + 1] = (ROOK | BLACK);
					}
					if (to_row == 0 && to_col == 2)
					{
						interface->board->board[to_row][to_col - 2] = EMPTY;
						interface->board->board[from_row][from_col - 1] = (ROOK | BLACK);
					}
				}
			}
			interface->board->board[to_row][to_col] = from_piece;
			interface->board->board[from_row][from_col] = EMPTY;
			interface->board->turn = (interface->board->turn == WHITE) ? BLACK : WHITE;
			if (interface->moves == NULL || interface->moves[0] == '\0')
				interface->moves = strdup(stockmove);
			else {
				char *tmp = stringjoin(interface->moves, " ");
				free(interface->moves);
				interface->moves = stringjoin(tmp, stockmove);
				free(tmp);
			}
			free(stockmove);
			usleep(700000); // Slow down moves
		}
	}
	renderer(interface);
	return (1);
}
