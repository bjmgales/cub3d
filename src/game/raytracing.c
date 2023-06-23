/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:04:25 by bgales            #+#    #+#             */
/*   Updated: 2023/06/23 15:31:18 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <sys/time.h>

int	color_select(int tale)
{
	int	color;

	(void)tale;
	color = create_trgb(0, 0, 0, 255);
	return (color);
}

double	time_calculator(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

void	game_loop(t_game game, t_data img)
{
	t_calc	n;

	n.x = -1;
	n.w = game.window_width;
	n.h = game.window_height;
	n.se_draw = malloc(sizeof(int) * 2);
	n.se_draw[0] = 0;
	n.se_draw[1] = 1;
	
	while (++n.x < n.w)
	{
		game_loop_init(game, &n);
		ray_dir_calc(game, &n);
		hit_wall(game, &n);
		last_calcul(&game, &n, img);
		
					// printf("valeur largeur %d\n", game.texig.texture_width);
					// printf("tex_x a la sortie %d\n", game.texig.tex_x);
					// printf("tex_y a la sortie %d\n", game.texig.tex_y);
					// printf("x a la sortie %d\n", n.x);
					// printf("---------------------------------------\n");
						// exit(0);
		// draw(img, n.x, n.se_draw, n.color);
	}
	// printf("********************************************************************\n");
	free(n.se_draw);
}

int	exit_game(void)
{
	exit(0);
}
