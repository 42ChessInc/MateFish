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

int	update(t_interface *interface)
{
	calculate_Delta(interface);

	return (1);
}

int	renderer(t_interface *interface)
{
	memset(interface->image.addr, 0, SCREEN_SIZE_X * SCREEN_SIZE_Y * (interface->image.bits_per_pixel / 8));
	drawtexture(interface, (t_point){0, 0}, &interface->background, 1.0f);
	drawtexture(interface, (t_point){0, 0}, &interface->white_pieces[interface->index_lookup[PAWN]], 1.0f);
	mlx_put_image_to_window(interface->mlx_ptr, interface->win_ptr, interface->image.img, 0, 0);
	return (1);
}

int	interface_loop(t_interface *interface)
{
	update(interface);
	renderer(interface);
	return (1);
}
