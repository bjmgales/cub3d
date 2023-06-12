/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:19:22 by bgales            #+#    #+#             */
/*   Updated: 2023/06/12 18:58:52 by bgales           ###   ########.fr       */
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
void	draw(t_data img, int x, int *se_draw, int color);
int		key_press_hook(int keycode, void *params);
double	time_calculator(void);
void	game_loop(t_game game, t_data img);
void	game_loop_init(t_game game, t_calc *n);
void	ray_dir_calc(t_game game, t_calc *n);
int		exit_game(void);
void	hit_wall(t_game game, t_calc *n);
void	last_calcul(t_game game, t_calc *n);
int		color_select(int tale);
double	delta_dist_init(double d, double r);
double	v_abs(double value);
#endif
