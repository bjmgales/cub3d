/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 20:00:57 by bgales            #+#    #+#             */
/*   Updated: 2023/06/25 11:31:44 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_data_color(t_data *data, int x, int y, void *addr)
{
	char	*dst;

	dst = addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	set_image(t_game *game, t_data *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path,
			&img->width, &img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

unsigned int	test_texture(t_game *game, t_calc *n)
{
	unsigned int	pixel;

	pixel = 0;
	if ((*n).side == 0)
	{
		if ((*n).step_x <= 0)
			pixel = get_data_color(&game->texig.no, game->texig.tex_x,
					game->texig.tex_y, game->texig.no.addr);
		if ((*n).step_x > 0)
			pixel = get_data_color(&game->texig.so, game->texig.tex_x,
					game->texig.tex_y, game->texig.so.addr);
	}
	if ((*n).side == 1)
	{
		if ((*n).step_y <= 0)
			pixel = get_data_color(&game->texig.we, game->texig.tex_x,
					game->texig.tex_y, game->texig.we.addr);
		if ((*n).step_y > 0)
			pixel = get_data_color(&game->texig.ea, game->texig.tex_x,
					game->texig.tex_y, game->texig.ea.addr);
	}
	return (pixel);
}

char	*get_path(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '.')
		;
	return (ft_strtrim(&str[i], " 	\n"));
}

void	texture_init(t_game *game)
{
	game->texig.texture_width = 64;
	game->texig.texture_height = 64;
	set_image(game, &game->texig.no, get_path(game->parse->north));
	set_image(game, &game->texig.so, get_path(game->parse->south));
	set_image(game, &game->texig.ea, get_path(game->parse->east));
	set_image(game, &game->texig.we, get_path(game->parse->west));
}