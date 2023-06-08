/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:46:22 by bgales            #+#    #+#             */
/*   Updated: 2023/06/08 15:56:37 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

enum e_keycode
{
	A_KEY,
	S_KEY,
	D_KEY,
	W_KEY = 13,
	SPACE = 49,
	ECHAP = 53,
	ARROW_LEFT = 123,
	ARROW_RIGHT,
	ARROW_DOWN,
	ARROW_UP
};

typedef struct s_player{
	float	x;
	float	y;
	float	pdx;
	float	pdy;
	float	pa;
	char	orientation;
}	t_player;


typedef struct s_map
{
	char **map;
} 	t_mapstr;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct t_num
{
	double time;
	double old_time;
	double frame_time;
	double plane_x;
	double plane_y;
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double move_speed;
	double rot_speed;
	double start;
}	t_num;

typedef struct s_tex
{
	int	tex_x;
	int	tex_y;
	int **buffer;
	int *texture[8];
	int	texture_width;
	int	texture_height;
}	t_tex;

typedef struct s_parse
{
	char 		**map;
	char		**ressources;
	int			map_width;
	int			map_height;
	int			c_rgb[3];
	int			f_rgb[3];
	char		*ceiling;
	char		*floor;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}	t_parse;

typedef struct s_game
{
	void		*mlx;
	void		*window;

	int			**map_ig;
	t_num		numig;
	t_data		imgig;
	t_tex		texig;
	int			window_height;
	int			window_width;
}	t_game ;

#endif