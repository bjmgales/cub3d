/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_calc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:45:51 by bgales            #+#    #+#             */
/*   Updated: 2023/06/23 16:23:24 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	v_abs(double value)
{
	if (value >= 0)
		return (value);
	else
		return (value *= -1);
}

double	delta_dist_init(double d, double r)
{
	if (!r)
		d = INFINITY;
	else if (r)
		d = v_abs(1 / r);
	return (d);
}

void	ray_dir_calc(t_game game, t_calc *n)
{
	if ((*n).ray_dir_x < 0)
	{
		(*n).step_x = -1;
		(*n).side_dist_x = (game.numig.pos_x - (*n).map_x)
			* (*n).delta_dist_x;
	}
	else
	{
		(*n).step_x = 1;
		(*n).side_dist_x = ((*n).map_x + 1.0
				- game.numig.pos_x) * (*n).delta_dist_x;
	}
	if ((*n).ray_dir_y < 0)
	{
		(*n).step_y = -1;
		(*n).side_dist_y = (game.numig.pos_y - (*n).map_y) * (*n).delta_dist_y;
	}
	else
	{
		(*n).step_y = 1;
		(*n).side_dist_y = ((*n).map_y + 1.0
				- game.numig.pos_y) * (*n).delta_dist_y;
	}
}

void	hit_wall(t_game game, t_calc *n)
{
	while ((*n).hit == 0)
	{
		if ((*n).side_dist_x < (*n).side_dist_y)
		{
			(*n).side_dist_x += (*n).delta_dist_x;
			(*n).map_x += (*n).step_x;
			(*n).side = 0;
		}
		else
		{
			(*n).side_dist_y += (*n).delta_dist_y;
			(*n).map_y += (*n).step_y;
			(*n).side = 1;
		}
		if (game.map_ig[(*n).map_y][(*n).map_x] > '0')
			(*n).hit = 1;
	}
}

unsigned int	get_data_color(t_data *data, int x, int y, void *addr)
{
	char	*dst;

	dst = addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	set_image(t_game *game, t_data *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width, &img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
}

unsigned int test_texture(t_game *game, t_calc *n)
{
	unsigned int pixel;
	pixel = 0;

	if ((*n).side == 0)
	{
		if ((*n).step_x <= 0)
			pixel = get_data_color(&game->texig.no, game->texig.tex_x, game->texig.tex_y,
					game->texig.no.addr);
		if ((*n).step_x > 0)
			pixel = get_data_color(&game->texig.so, game->texig.tex_x, game->texig.tex_y,
					game->texig.so.addr);
	}
	if ((*n).side == 1)
	{
		if ((*n).step_y <= 0)
			pixel = get_data_color(&game->texig.we, game->texig.tex_x, game->texig.tex_y,
					game->texig.we.addr);
		if ((*n).step_y > 0)
			pixel = get_data_color(&game->texig.ea, game->texig.tex_x, game->texig.tex_y,
					game->texig.ea.addr);
	}	
	return pixel;
}


void	last_calcul(t_game *game, t_calc *n, t_data img)
{
	(void)img;
	double tex_pos=0;
	double step;
	if ((*n).side == 0)
		(*n).perp_wall_dist = ((*n).side_dist_x - (*n).delta_dist_x);
	else
		(*n).perp_wall_dist = ((*n).side_dist_y - ((*n).delta_dist_y));
	(*n).line_height = (int)((*n).h / (*n).perp_wall_dist);
	(*n).se_draw[0] = -(*n).line_height / 2 + (*n).h / 2;
	(*n).se_draw[1] = (*n).line_height / 2 + (*n).h / 2;
		
	step = (double)(1.0 * (double)game->texig.texture_height / (double)(*n).line_height);
	(*n).wall_x = game->numig.pos_x + ((*n).perp_wall_dist * (*n).ray_dir_x);
	if ((*n).side == 0)
		(*n).wall_x = game->numig.pos_y + ((*n).perp_wall_dist * (*n).ray_dir_y);
	(*n).wall_x -= floor(((*n).wall_x));
	game->texig.tex_x = (int)((*n).wall_x * (game->texig.texture_width) - 1);

	
	if(((*n).side == 0 && (*n).ray_dir_x > 0) || ((*n).side == 1 && (*n).ray_dir_y < 0))
		game->texig.tex_x = game->texig.texture_height - game->texig.tex_x - 1;

	if ((*n).se_draw[0] < 0) {
		tex_pos += step * -(*n).se_draw[0];
		(*n).se_draw[0] = 0;
	}
	if ((*n).se_draw[1] >= game->window_height)
		(*n).se_draw[1] = game->window_height - 1;

	while ((*n).se_draw[0] < (*n).se_draw[1])
	{
		game->texig.tex_y = (int)tex_pos & (game->texig.texture_height - 1);

		tex_pos += step;
		(*n).color = test_texture(game, n);
		my_mlx_pixel_put(&img, (*n).x, (*n).se_draw[0], (*n).color);
		(*n).se_draw[0]++;
	}
}

