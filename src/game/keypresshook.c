/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypresshook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:12:35 by bgales            #+#    #+#             */
/*   Updated: 2023/06/12 20:48:56 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	up_down(int keycode, t_game *game)
{
	char	**map_ig;

	map_ig = game->map_ig;
	if (keycode == 13 || keycode == 126)
	{
		if (map_ig[(int)(game->numig.pos_y + game->numig.dir_y
				* game->numig.move_speed)][(int)game->numig.pos_x] == '0')
			game->numig.pos_y += game->numig.dir_y * game->numig.move_speed;
		if (map_ig[(int)game->numig.pos_y][(int)(game->numig.pos_x
			+ game->numig.dir_x * game->numig.move_speed)] == '0')
			game->numig.pos_x += game->numig.dir_x * game->numig.move_speed;
	}
	else if (keycode == 1 || keycode == 125)
	{
		if (map_ig[(int)(game->numig.pos_y - game->numig.dir_y
				* game->numig.move_speed)][(int)game->numig.pos_x] == '0')
			game->numig.pos_y -= game->numig.dir_y * game->numig.move_speed;
		if (map_ig[(int)game->numig.pos_y][(int)(game->numig.pos_x
			- game->numig.dir_x * game->numig.move_speed)] == '0')
			game->numig.pos_x -= game->numig.dir_x * game->numig.move_speed;
	}
}

void	right_left(int keycode, t_game *game)
{
	char	**map_ig;

	map_ig = game->map_ig;
	if (keycode == 0)
	{
		if (map_ig[(int)(game->numig.pos_y + game->numig.plane_y
				* game->numig.move_speed)][(int)game->numig.pos_x] == '0')
			game->numig.pos_x += game->numig.plane_x * game->numig.move_speed;
		if (map_ig[(int)game->numig.pos_y][(int)(game->numig.pos_x
			+ game->numig.plane_x * game->numig.move_speed)] == '0')
			game->numig.pos_y += game->numig.plane_y * game->numig.move_speed;
	}
	if (keycode == 2)
	{
		if (map_ig[(int)(game->numig.pos_y + game->numig.plane_y
				* game->numig.move_speed)][(int)game->numig.pos_x] == '0')
			game->numig.pos_x -= game->numig.plane_x * game->numig.move_speed;
		if (map_ig[(int)game->numig.pos_y][(int)(game->numig.pos_x
			+ game->numig.plane_x * game->numig.move_speed)] == '0')
			game->numig.pos_y -= game->numig.plane_y * game->numig.move_speed;
	}
}

void	rotate_left(int keycode, t_game *game)
{
	double	olddir_x;
	double	oldplane_x;

	if (keycode == 123)
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

void	rotate_right(int keycode, t_game *game)
{
	double	olddir_x;
	double	oldplane_x;

	if (keycode == 124)
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

int	key_press_hook(int keycode, void *params)
{
	t_game	*game;

	game = (t_game *)params;
	game->numig.old_time = game->numig.time;
	game->numig.time = time_calculator() - game->numig.start;
	game->numig.frame_time = (game->numig.time - game->numig.old_time) / 1000.0;
	game->numig.move_speed = 0.17;
	game->numig.rot_speed = 0.10;
	if (keycode == 53)
		exit_game();
	up_down(keycode, game);
	right_left(keycode, game);
	rotate_left(keycode, game);
	rotate_right(keycode, game);
	mlx_clear_window(game->mlx, game->window);
	game->imgig.img = mlx_new_image(game->mlx, 1024, 720);
	game->imgig.addr = mlx_get_data_addr(game->imgig.img, &game->imgig
			.bits_per_pixel, &game->imgig.line_length, &game->imgig.endian);
	game_loop(*game, game->imgig);
	mlx_put_image_to_window(game->mlx, game->window, game->imgig.img, 0, 0);
	return (0);
}
