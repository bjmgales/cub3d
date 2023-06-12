/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 14:31:43 by bgales            #+#    #+#             */
/*   Updated: 2023/06/12 16:07:52 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cam_eastwest(t_game *game)
{
	if ((*game).parse->map[(*game).parse->player_y]
		[(*game).parse->player_x] == 'W')
	{
		(*game).numig.dir_x = -1;
		(*game).numig.dir_y = 0;
		(*game).numig.plane_x = 0;
		(*game).numig.plane_y = 0.66;
	}
	else if ((*game).parse->map[(*game).parse->player_y]
		[(*game).parse->player_x] == 'E')
	{
		(*game).numig.dir_x = 1;
		(*game).numig.dir_y = 0;
		(*game).numig.plane_x = 0;
		(*game).numig.plane_y = -0.66;
	}
}

void	init_camera_dir(t_game *game)
{
	if ((*game).parse->map[(*game).parse->player_y]
		[(*game).parse->player_x] == 'N')
	{
		(*game).numig.dir_x = 0;
		(*game).numig.dir_y = -1;
		(*game).numig.plane_x = -0.66;
		(*game).numig.plane_y = 0;
	}
	else if ((*game).parse->map[(*game).parse->player_y]
		[(*game).parse->player_x] == 'S')
	{
		(*game).numig.dir_x = 0;
		(*game).numig.dir_y = 1;
		(*game).numig.plane_x = 0.66;
		(*game).numig.plane_y = 0;
	}
	else
		init_cam_eastwest(game);
}

void	init_numig(t_game *game)
{
	(*game).numig.time = 0;
	(*game).numig.start = time_calculator();
	(*game).numig.old_time = 0;
	(*game).numig.old_time = (*game).numig.time;
	(*game).numig.time = time_calculator() - (*game).numig.start;
	(*game).numig.pos_x = (*game).parse->player_x + 0.5;
	(*game).numig.pos_y = (*game).parse->player_y + 0.5;
}
