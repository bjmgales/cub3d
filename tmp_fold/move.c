/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:26:23 by bgales            #+#    #+#             */
/*   Updated: 2023/04/26 15:18:15 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_game *game, double y, double x)
{
	if (game->map[(int)round(y - 0.1)][(int)round(x + 0.1)] != '1'
		&& game->map[(int)round(y - 0.1)][(int)round(x - 0.1)] != '1'
		&& game->map[(int)round(y + 0.1)][(int)round(x + 0.1)] != '1'
		&& game->map[(int)round(y + 0.1)][(int)round(x - 0.1)] != '1')
		return (0);
	return (1);
}

void	clear_position(t_game *game, double i, double j)
{
	double	x;
	double	y;

	x = j - 0.1;
	y = i - 0.1;
	while (x < j)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			(x + 0.5) * 32, (i + 0.5) * 32, 000000);
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			(x + 0.5) * 32, (y + 0.5) * 32, 000000);
		x += 0.01;
	}
	x = j - 0.1;
	y = i - 0.1;
	while (y < i)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			(j + 0.5) * 32, (y + 0.5) * 32, 000000);
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			(x + 0.5) * 32, (y + 0.5) * 32, 000000);
		y += 0.01;
	}
}

void	move_up(t_game *game)
{
	float	x;
	float	y;

	x = game->player->x - game->player->pdx;
	y = game->player->y - game->player->pdy;
	if (!is_wall(game, y, x))
	{
		clear_position(game, game->player->y, game->player->x);
		draw_player(game, game->player->y -= game->player->pdy,
			game->player->x -= game->player->pdx);
	}
}

void	move_down(t_game *game)
{
	float	x;
	float	y;

	x = game->player->x + game->player->pdx;
	y = game->player->y + game->player->pdy;
	if (!is_wall(game, y, x))
	{
		clear_position(game, game->player->y, game->player->x);
		draw_player(game, game->player->y += game->player->pdy,
			game->player->x += game->player->pdx);
	}
}

void	rotate(t_game *game, int keycode)
{
	if (keycode == A_KEY || keycode == ARROW_LEFT)
	{
		game->player->pa -= 0.1;
		if (game->player->pa < 0)
			game->player->pa += 2 * PI;
		game->player->pdx = cos(game->player->pa) * 0.1;
		game->player->pdy = sin(game->player->pa) * 0.1;
	}
	else
	{
		game->player->pa += 0.1;
		if (game->player->pa > 2 * PI)
			game->player->pa -= 2 * PI;
		game->player->pdx = cos(game->player->pa) * 0.1;
		game->player->pdy = sin(game->player->pa) * 0.1;
	}
}
