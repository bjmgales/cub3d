/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_calc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:45:51 by bgales            #+#    #+#             */
/*   Updated: 2023/06/12 18:58:03 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

double v_abs(double value)
{
	if (value >= 0)
		return (value);
	else
		return (value *= -1);
}

void	ray_dir_calc(t_game game, t_calc *n)
{
	if ((*n).ray_dir_x < 0)
	{
				(*n).step_x = -1;
				(*n).side_dist_x = (game.numig.pos_x - (*n).map_x) * (*n).delta_dist_x;
	}
	else
	{
		(*n).step_x = 1;
		(*n).side_dist_x = ((*n).map_x + 1.0 - game.numig.pos_x) * (*n).delta_dist_x;
	}
	if ((*n).ray_dir_y < 0)
	{
		(*n).step_y = -1;
		(*n).side_dist_y = (game.numig.pos_y - (*n).map_y) * (*n).delta_dist_y;
	}
	else
	{
		(*n).step_y = 1;
		(*n).side_dist_y = ((*n).map_y + 1.0 - game.numig.pos_y) * (*n).delta_dist_y;
	}
}

void	hit_wall(t_game game, t_calc *n)
{
	while ((*n).hit == 0)
	{
		if ((*n).side_dist_y < (*n).side_dist_x)
		{
			(*n).side_dist_y += (*n).delta_dist_y;
			(*n).map_y += (*n).step_y;
			(*n).side = 0;
		}
		else
		{
			(*n).side_dist_x += (*n).delta_dist_x;
			(*n).map_x += (*n).step_x;
			(*n).side = 1;
		}
		if (game.map_ig[(*n).map_y][(*n).map_x] > '0')
			(*n).hit = 1;
	}
}

void	last_calcul(t_game game, t_calc *n)
{
	if ((*n).side == 0)
		(*n).perp_wall_dist = ((*n).side_dist_y - ((*n).delta_dist_y));
	else
		(*n).perp_wall_dist = ((*n).side_dist_x - (*n).delta_dist_x);
	(*n).line_height = (int)((*n).h / (*n).perp_wall_dist);
	(*n).se_draw = malloc(sizeof(int) * 2);
	(*n).se_draw[0] = -(*n).line_height / 2 + (*n).h / 2;
	if ((*n).se_draw[0] < 0)
		(*n).se_draw[0] = 0;
	(*n).se_draw[1] = (*n).line_height / 2 + (*n).h / 2;
	if ((*n).se_draw[1] >= (*n).h)
		(*n).se_draw[1] = (*n).h - 1;
	(*n).color = color_select(game.map_ig[(*n).map_y][(*n).map_x]);
	if ((*n).side == 1)
		(*n).color = ((*n).color / 2);
}