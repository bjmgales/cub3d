/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:54:06 by bgales            #+#    #+#             */
/*   Updated: 2023/06/16 17:28:37 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_border(t_data img)
{
	int	y;
	int	x;

	y = -1;
	x = -1;
	while (++x < 200)
	{
		if (x < 195)
			draw(img, x, (int [2]){0,
				195}, 16777215);
		else
			draw(img, x, (int [2]){0,
				195}, 0);
	}
	x = -1;
	while (++x < 200)
		draw(img, x, (int [2]){195, 200}, 0);
}

void	draw_map(t_game *game, t_data img, int x, int y)
{
	int	draw_x;
	int	draw_y;
	int	i;

	draw_x = (x * 190) / game->parse->map_width;
	draw_y = (y * 190) / game->parse->map_height;
	i = draw_x;
	if (y == game->parse->map_height - 1 || y == 0)
		while (i++ < draw_x + 10)
			draw(img, i - 1, (int [2]){draw_y, draw_y + 10}, 16711680);
	while (i++ < draw_x + 5)
		draw(img, i - 1, (int [2]){draw_y, draw_y + 10}, 16711680);
}

void	draw_player(t_game *game, t_data img)
{
	int	draw_x;
	int	draw_y;

	draw_x = (game->numig.pos_x * 190) / game->parse->map_width - (5 / 2);
	draw_y = (game->numig.pos_y * 190) / game->parse->map_height - (5 / 2);
	draw(img, draw_x, (int [2]){draw_y, draw_y + 1}, 1);
}

void	minimap(t_game *game, t_data img)
{
	int	y;
	int	x;

	x = -1;
	y = -1;
	draw_border(img);
	while (++y < game->parse->map_height)
	{
		while (game->map_ig[y][++x])
			if (game->map_ig[y][x] == '1')
				draw_map(game, img, x, y);
		x = -1;
	}
	draw_player(game, img);
}
