/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypresshook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:12:35 by bgales            #+#    #+#             */
/*   Updated: 2023/06/23 15:24:06 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



void	up_down(t_game *game, int type)
{

	char	**map_ig;

	map_ig = game->map_ig;
	if (type == 'U')
	{
		if (map_ig[(int)(game->numig.pos_y + game->numig.dir_y
				* game->numig.move_speed)][(int)game->numig.pos_x] == '0')
			game->numig.pos_y += game->numig.dir_y * game->numig.move_speed;
		if (map_ig[(int)game->numig.pos_y][(int)(game->numig.pos_x
			+ game->numig.dir_x * game->numig.move_speed)] == '0')
			game->numig.pos_x += game->numig.dir_x * game->numig.move_speed;
	}
	else if (type == 'D')
	{
		if (map_ig[(int)(game->numig.pos_y - game->numig.dir_y
				* game->numig.move_speed)][(int)game->numig.pos_x] == '0')
			game->numig.pos_y -= game->numig.dir_y * game->numig.move_speed;
		if (map_ig[(int)game->numig.pos_y][(int)(game->numig.pos_x
			- game->numig.dir_x * game->numig.move_speed)] == '0')
			game->numig.pos_x -= game->numig.dir_x * game->numig.move_speed;
	}
}

///////////////////////////

void	right_left(t_game *game, int type)
{
	char	**map_ig;

	map_ig = game->map_ig;
	if (type == 'R')
	{
		if (map_ig[(int)(game->numig.pos_y + game->numig.dir_x
				* game->numig.move_speed)][(int)game->numig.pos_x] == '0')
			game->numig.pos_y += game->numig.dir_x * game->numig.move_speed;
		if (map_ig[(int)game->numig.pos_y][(int)(game->numig.pos_x
			- game->numig.dir_y * game->numig.move_speed)] == '0')
			game->numig.pos_x -= game->numig.dir_y * game->numig.move_speed;
	}
	else if (type == 'L')
	{
		if (map_ig[(int)(game->numig.pos_y - game->numig.dir_x
				* game->numig.move_speed)][(int)game->numig.pos_x] == '0')
			game->numig.pos_y -= game->numig.dir_x * game->numig.move_speed;
		if (map_ig[(int)game->numig.pos_y][(int)(game->numig.pos_x
			+ game->numig.dir_y * game->numig.move_speed)] == '0')
			game->numig.pos_x += game->numig.dir_y * game->numig.move_speed;
	}
}

void	rotate_right(t_game *game)
{
	double	olddir_x;
	double	oldplane_x;

	if ((*game).keys.right)
	{
		olddir_x = game->numig.dir_x;
		game->numig.dir_x = game->numig.dir_x * cos(-game->numig.rot_speed)
			- game->numig.dir_y * sin(-game->numig.rot_speed);
		game->numig.dir_y = olddir_x * sin(-game->numig.rot_speed)
			+ game->numig.dir_y * cos(-game->numig.rot_speed);
		oldplane_x = game->numig.plane_x;
		game->numig.plane_x = game->numig.plane_x * cos(-game->numig.rot_speed)
			- game->numig.plane_y * sin(-game->numig.rot_speed);
		game->numig.plane_y = oldplane_x * sin(-game->numig.rot_speed)
			+ game->numig.plane_y * cos(-game->numig.rot_speed);
	}
}

void	rotate_left(t_game *game)
{
	double	olddir_x;
	double	oldplane_x;

	if ((*game).keys.left)
	{
		olddir_x = game->numig.dir_x;
		game->numig.dir_x = game->numig.dir_x * cos(game->numig.rot_speed)
			- game->numig.dir_y * sin(game->numig.rot_speed);
		game->numig.dir_y = olddir_x * sin(game->numig.rot_speed)
			+ game->numig.dir_y * cos(game->numig.rot_speed);
		oldplane_x = game->numig.plane_x;
		game->numig.plane_x = game->numig.plane_x * cos(game->numig.rot_speed)
			- game->numig.plane_y * sin(game->numig.rot_speed);
		game->numig.plane_y = oldplane_x * sin(game->numig.rot_speed)
			+ game->numig.plane_y * cos(game->numig.rot_speed);
	}
}

int	key_press_hook(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	game->numig.old_time = game->numig.time;
	game->numig.time = time_calculator() - game->numig.start;
	game->numig.frame_time = (game->numig.time - game->numig.old_time) / 1000.0;
	game->numig.move_speed = 0.07;
	game->numig.rot_speed = 0.05;
	mlx_clear_window(game->mlx, game->window);
	game->imgig.img = mlx_new_image(game->mlx, 1024, 720);
	game->imgig.addr = mlx_get_data_addr(game->imgig.img, &game->imgig
			.bits_per_pixel, &game->imgig.line_length, &game->imgig.endian);
	game->minimap.img = mlx_new_image(game->mlx,  200, 200);
	game->minimap.addr = mlx_get_data_addr(game->minimap.img,
			&game->minimap.bits_per_pixel, &game->minimap.line_length,
			&game->minimap.endian);
	game_loop(*game, game->imgig);
	print_map(game, game->minimap);
	mlx_put_image_to_window(game->mlx, game->window, game->imgig.img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window, game->minimap.img, 0, 0);
	return (0);
}
