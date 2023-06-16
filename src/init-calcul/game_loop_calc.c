/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_calc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:45:51 by bgales            #+#    #+#             */
/*   Updated: 2023/06/16 08:25:23 by ctardy           ###   ########.fr       */
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


// je casse tout oééééééé --------------------------

unsigned int	get_data_color(t_data *data, int x, int y, void *addr)
{
	char	*dst;
	// printf("VALEUR DE X %d\n", x);
	// printf("VALEUR DE Y %d\n", y);
	dst = addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	set_image(t_game *game, t_data *img, char *path)
{
	int i = 0;
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width, &img->height);
	// if (!img->img)
	// 	exit(0);
	img->addr = mlx_get_data_addr(img->img, &i, &i, &i);
	// if (!img->addr)
	// 	exit(0);
}

unsigned int test_texture(t_game *game, t_calc *n)
{
	// welcome to rainbow road
	
	unsigned int pixel;
	pixel = 0;
	// (void)(game);
	// printf("salut salut map x %d\n", (*n).map_x);
	// printf("salut salut map y %d\n", (*n).map_y);

	// printf("salut salut map x %d\n", (*n).side);
	if ((*n).side == 0)
	{
		if ((*n).step_y <= 0)
			// pixel = create_trgb(0, 255, 0, 0);
			pixel = get_data_color(&game->texig.no, game->texig.tex_x, game->texig.tex_y,
					game->texig.no.addr);
		if ((*n).step_y > 0)
			// pixel = create_trgb(255, 0, 0, 0);
			pixel = get_data_color(&game->texig.so, game->texig.tex_x, game->texig.tex_y,
					game->texig.so.addr);
	}
	if ((*n).side == 1)
	{
		if ((*n).step_x <= 0)
			// pixel = create_trgb(0, 0, 255, 0);
			pixel = get_data_color(&game->texig.we, game->texig.tex_x, game->texig.tex_y,
					game->texig.we.addr);
		if ((*n).step_x > 0)
			// pixel = create_trgb(0, 0, 0, 255);
			pixel = get_data_color(&game->texig.ea, game->texig.tex_x, game->texig.tex_y,
					game->texig.ea.addr);
	}	
	return pixel;
}


void	last_calcul(t_game *game, t_calc *n, t_data img)
{
	(void)img;
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


	// textures calcul implementation --------------------------

	    //calculate value of wall_x

		// inversion of x / y fixed wall_x and so tex_x
    	if ((*n).side == 0)
			(*n).wall_x = game->numig.pos_x + (*n).perp_wall_dist * (*n).ray_dir_x;
    	else
			(*n).wall_x = game->numig.pos_y + (*n).perp_wall_dist * (*n).ray_dir_y;
    	(*n).wall_x -= floor(((*n).wall_x));

      //x coordinate on the texture
	//   printf(" HELLOOOOO %d\n", line_height);
	//   exit(0);
	  
    	game->texig.tex_x = (int)((*n).wall_x * (double)(game->texig.texture_width));
    	if(((*n).side == 0 && (*n).ray_dir_x > 0) || ((*n).side == 1 && (*n).ray_dir_y < 0))
			game->texig.tex_x = game->texig.texture_width - game->texig.tex_x - 1;
    	// game->texig.tex_x = game->texig.texture_width - game->texig.tex_x - 1;
    // How much to increase the texture coordinate per screen pixel
    	(*n).step = 1.0 * game->texig.texture_height / (*n).line_height;
    // Starting texture coordinate
		(*n).tex_pos = ((*n).se_draw[0] - (*n).h / 2 + (*n).line_height / 2) * (*n).step;
		

		// tex_x_y irrelevant ? why ?
		// tex_x not the same anymore at the end of the function ??????????? <- fixed
		
		// while ((*n).se_draw[0] < (*n).se_draw[1])
		// {
			// printf("VALEUR DE 0 %d\n", (*n).se_draw[0]);
			// printf("VALEUR DE 1 %d\n", (*n).se_draw[1]);
			game->texig.tex_y = (int)(*n).tex_pos & (game->texig.texture_height - 1);
			(*n).tex_pos += (*n).step;
			(*n).color = test_texture(game, n);
			
			
			
			
			
			// printf("pos_y dans last calcul %f\n", game->numig.pos_y);
			// printf("pos_x dans last calcul %f\n", game->numig.pos_x);
			printf("wall_x dans last calcul %f\n", (*n).wall_x);
			printf("tex_x dans last calcul %d\n", game->texig.tex_x);
			// printf("tex_y dans last calcul %d\n", game->texig.tex_y);
			// printf("color dans last calcul %d\n", (*n).color);
			printf("---------------------------------------\n");

			
			
			
			
			// (*n).se_draw[0]++;
			// my_mlx_pixel_put(&img, (*n).x, (*n).se_draw[0], (*n).color);
		// }
	}
	// (*n).(*n).color = (*n).color_select(game->map_ig[(*n).map_y][(*n).map_x]);
	// if ((*n).side == 1)
	// 	(*n).(*n).color = ((*n).(*n).color / 2);

