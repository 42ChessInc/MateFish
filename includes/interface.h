#ifndef INTERFACE_H
#define INTERFACE_H

#include "board.h"
#include "../libs/mlx/mlx.h"
#include "../libs/mlx/mlx_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

//get all prototypes from interface folder

#define SCREEN_SIZE_X 336
#define SCREEN_SIZE_Y 336

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}	t_image;

typedef struct s_interface
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	image;
	t_image	background;
	float	delta;
	long	last_frame_time;
	int		started;
	t_image white_pieces[6];
	t_image black_pieces[6];

	unsigned char	*index_lookup;;

}	t_interface;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;



void	init_window(t_interface *interface);
void	get_textures(t_interface *interface);
int		free_displays(t_interface *interface);

int	interface_loop(t_interface *interface);
void	calculate_Delta(t_interface *interface);
void	ft_pixelput(t_image *data, int x, int y, int color);
long long	get_time(void);
void	drawtexture(t_interface *interface, t_point pos, t_image *text, float scale);






#endif
