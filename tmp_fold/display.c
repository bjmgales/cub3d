/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:17:24 by bgales            #+#    #+#             */
/*   Updated: 2023/04/27 12:19:04 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(t_game *game, double y, double x)
{
	double	x_draw;
	double	y_draw;

	x_draw = x;
	y_draw = y;
	while (y_draw < y + 0.9)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			x * 32, y_draw * 32, 16711680);
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			(x + 0.9) * 32, y_draw * 32, 16711680);
		y_draw += 0.01;
	}
	while (x_draw < x + 0.9)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			x_draw * 32, y * 32, 16711680);
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			x_draw * 32, (y + 0.9) * 32, 16711680);
		x_draw += 0.01;
	}
}

void	draw_player(t_game *game, double i, double j)
{
	double	x;
	double	y;

	x = j - 0.1;
	y = i - 0.1;
	while (x < j)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			(x + 0.5) * 32, (i + 0.5) * 32, 16777011);
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			(x + 0.5) * 32, (y + 0.5) * 32, 16777011);
		x += 0.01;
	}
	x = j - 0.1;
	y = i - 0.1;
	while (y < i)
	{
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			(j + 0.5) * 32, (y + 0.5) * 32, 16777011);
		mlx_pixel_put(game->mlx_ptr, game->win_ptr,
			(x + 0.5) * 32, (y + 0.5) * 32, 16777011);
		y += 0.01;
	}
}

void	display(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (game->map[++i])
	{
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '1')
				draw_map(game, i, j);
			if (in_set("NEWS", game->map[i][j]))
			{
				game->player->orientation = game->map[i][j];
				game->player->x = j;
				game->player->y = i;
				draw_player(game, i, j);
			}
		}
		j = -1;
	}
}
