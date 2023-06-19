/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 15:54:06 by bgales            #+#    #+#             */
/*   Updated: 2023/06/19 20:42:21 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_border(t_data img)
{
	int	x;

	x = -1;
	while (++x < 200)
	{
		if (x < 192)
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

void	draw_walls(t_data img, int x, int y)
{
	int	draw_x;
	int	draw_y;
	int	i;
	int cubesize = 10;

	draw_x = (x * 190) / 20;
	draw_y = (y * 190) / 10;
	i = draw_x;
		while (i++ < draw_x + cubesize && draw_x + cubesize < 200  && draw_y + cubesize < 200)
			draw(img, i, (int [2]){draw_y + 2, draw_y + 22}, 16711680);
}

void draw_player(t_game *game, t_data img)
{
	int draw_x;
	int draw_y;
	int i;
	draw_x = (game->minimap.player_x - 1) * 10;
	draw_y = (game->minimap.player_y * 10) + 50;
	i = draw_x;
	while(i++ < draw_x + 5)
	{
		draw(img, i, (int[2]){draw_y - 2, draw_y + 5}, 0);
	}
	// draw(img, draw_x - 2, (int[2]){draw_y, draw_y + 1}, 0);
	// draw(img, draw_x, (int[2]){draw_y, draw_y + 1}, 0);
	// draw(img, draw_x + 1, (int[2]){draw_y, draw_y + 1}, 0);
	// draw(img, draw_x + 2, (int[2]){draw_y, draw_y + 1}, 0);
}


void	draw_minimap(t_game *game, t_data img)
{
	int	y;
	int	x;

	x = -1;
	y = -1;
	draw_border(img);
	while (game->minimap.minimap[++y])
	{
		while (game->minimap.minimap[y][++x])
			if (game->minimap.minimap[y][x] == '1')
				draw_walls(img, x, y);
		x = -1;
	}
	free_char_array(game->minimap.minimap);
	draw_player(game, img);
}

void	minimap_posxy(t_game *game, int y, int x)
{
	if (x >= 0)
		game->minimap.player_x = 10;
	if (y >= 0)
		game->minimap.player_y = 5;
	if (x < 0)
		game->minimap.player_x = x + 10;
	if (y < 0)
		game->minimap.player_y = y + 2;

}

void	minimap(t_game *game, t_data img)
{
	int	y;
	int	x;
	int i;
	(void)(img);

	y = game->numig.pos_y - 5;
	x = game->numig.pos_x - 10;
	minimap_posxy(game, y, x);
	i = 0;
	if (game->minimap.minimap_h  > game->parse->map_height)
		game->minimap.minimap_h  = game->parse->map_height;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	game->minimap.minimap_h  = y + 13;
	game->minimap.minimap = malloc(sizeof(char *) * (game->minimap.minimap_h  + 1));
	printf("map_h  + 1 = %d\n", game->minimap.minimap_h + 1);
	while (y < game->minimap.minimap_h && game->map_ig[y])
	 	game->minimap.minimap[i++] = ft_substr(game->map_ig[y++], x, game->numig.pos_x + 20);
	printf("i = %d\n", i);
	game->minimap.minimap[i] = NULL;
	draw_minimap(game, img);
}
