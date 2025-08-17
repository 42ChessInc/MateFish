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


void run_chess(void)
{
	t_interface interface;

	interface.index_lookup = malloc(64 * sizeof(unsigned char));
	if (!interface.index_lookup)
	{
		fprintf(stderr, "Error allocating memory for index lookup.\n");
		exit(EXIT_FAILURE);
	}

	interface.index_lookup[PAWN] = 0;
	interface.index_lookup[ROOK] = 1;
	interface.index_lookup[KNIGHT] = 2;
	interface.index_lookup[BISHOP] = 3;
	interface.index_lookup[QUEEN] = 4;
	interface.index_lookup[KING] = 5;

	init_window(&interface);
	get_textures(&interface);
	mlx_hook(interface.win_ptr, DestroyNotify, (1L<<17), free_displays, &interface);
	mlx_loop_hook(interface.mlx_ptr, interface_loop, &interface);
	mlx_loop(interface.mlx_ptr);
}



