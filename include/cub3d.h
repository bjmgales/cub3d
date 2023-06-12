/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:19:22 by bgales            #+#    #+#             */
/*   Updated: 2023/06/12 15:38:00 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# define PI 3.1415926535

// *****************************************************************************
// Personal library

# include "libft.h"
# include "structures.h"
# include "parse.h"
# include "utils.h"
# include "game.h"

char	*get_next_line(int fd);
int		create_trgb(int t, int r, int g, int b);
void	draw(t_data img, int x, int draw_start, int draw_end, int color);
int		key_press_hook(int keycode, void *params);
double	time_calculator(void);
void	game_loop(t_game game, t_data img, double pos_x, double pos_y, double dir_x, double dir_y, double plane_x, double plane_y, char **map_ig);
int		exit_game(void);

#endif
