/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:15:15 by bgales            #+#    #+#             */
/*   Updated: 2023/06/14 23:46:25 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	set_image(t_game *game, t_data *img, char *path);

void	initial_camera_dir(double *dir_x, double *dir_y, double *plane_x, double *plane_y, char orientation)
{
	printf("%c\n", orientation);
	if (orientation == 'W')
	{
		*dir_x = -1, *dir_y = 0; //initial direction vector
		*plane_x = 0, *plane_y = 0.66;
	}
	if (orientation == 'N')
	{
		*dir_x = 0, *dir_y = -1; // Initial direction vector
		*plane_x = -0.66, *plane_y = 0; // Camera plane

	}
	if (orientation == 'E')
	{
		*dir_x = 1, *dir_y = 0; // Initial direction vector
		*plane_x = 0, *plane_y = -0.66; // Camera plane
	}
	if (orientation == 'S')
	{
		*dir_x = 0, *dir_y = 1; // Initial direction vector
		*plane_x = 0.66, *plane_y = 0; // Camera plane

	}
}
int main (int argc, char **argv)
{

	/***********************************BEN PART*************************************************/

	t_parse	*parse;
	char	**cub_file;

	cub_file = NULL;
	parse = malloc(sizeof(t_parse));
	if (argc != 2)
	{
		printf("Wrong argument format");
		exit (0);
	}
	parser(&parse, cub_file, argv[1]);





	/***********************************CHARLY PART*************************************************/


	(void)argc;
	(void)argv;
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	// game.map_ig = parse->map;

	game.numig.pos_x = parse->player_x + 0.5; // +0.5 pour qu'il soit bien aligné avec le centre des murs
	game.numig.pos_y = parse->player_y + 0.5;//x and y start position
	game.map_ig = parse->map;
	initial_camera_dir(&game.numig.dir_x, &game.numig.dir_y, &game.numig.plane_x, &game.numig.plane_y, game.map_ig[parse->player_y][parse->player_x]);
	game.map_ig[parse->player_y][parse->player_x] = '0';
	game.numig.time = 0; //time of current frame
	game.numig.start = time_calculator(); //time of current frame
	game.numig.old_time = 0; //time of previous frame
	game.numig.old_time = game.numig.time;
    game.numig.time = time_calculator() - game.numig.start;

	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, 1024, 720, "cub3D");
	game.imgig.img = mlx_new_image(game.mlx, 1024, 720);
	game.imgig.addr = mlx_get_data_addr(game.imgig.img, &game.imgig.bits_per_pixel, &game.imgig.line_length, &game.imgig.endian);

	game.parseig = *parse;
	set_image(&game, &game.texig.no, "./ressources/textures/NO.xpm");
	set_image(&game, &game.texig.so, "./ressources/textures/SO.xpm");
	set_image(&game, &game.texig.ea, "./ressources/textures/EA.xpm");
	set_image(&game, &game.texig.we, "./ressources/textures/WE.xpm");

	game_loop(game, game.imgig, game.numig.pos_x, game.numig.pos_y, game.numig.dir_x, game.numig.dir_y, game.numig.plane_x, game.numig.plane_y, game.map_ig, parse);

	mlx_put_image_to_window(game.mlx, game.window, game.imgig.img, 0, 0); // redraw();
	mlx_hook(game.window, 17, (1L << 17), exit_game, &game);
 	mlx_hook(game.window, 2, (1L << 0), key_press_hook, &game); //readKeys();
	mlx_loop(game.mlx);
}
