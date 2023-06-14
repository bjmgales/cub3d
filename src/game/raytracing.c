/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:04:25 by bgales            #+#    #+#             */
/*   Updated: 2023/06/14 19:44:50 by bgales           ###   ########.fr       */
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

	printf("LA BOUCLE \n");
	n.x = -1;
	n.w = 1024;
	n.h = 720;
	while (++n.x < n.w)
	{
		game_loop_init(game, &n);
		ray_dir_calc(game, &n);
		hit_wall(game, &n);
		last_calcul(game, &n);
		draw(img, n.x, n.se_draw, n.color);
	}
}

int	exit_game(void)
{
	exit(0);
}
