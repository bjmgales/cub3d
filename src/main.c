/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:15:15 by bgales            #+#    #+#             */
/*   Updated: 2023/06/09 09:54:10 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

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

	game.numig.pos_x = parse->player_x, game.numig.pos_y = parse->player_y;//x and y start position
	game.numig.dir_x = -1, game.numig.dir_y = 0; //initial direction vector
	game.numig.plane_x = 0, game.numig.plane_y = 0.66; //the 2d raycaster version of camera plane
	game.numig.time = 0; //time of current frame
	game.numig.start = time_calculator(); //time of current frame
	game.numig.old_time = 0; //time of previous frame
	game.numig.old_time = game.numig.time;
    game.numig.time = time_calculator() - game.numig.start;

	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, 1024, 720, "cub3D");
	game.imgig.img = mlx_new_image(game.mlx, 1024, 720);
	game.imgig.addr = mlx_get_data_addr(game.imgig.img, &game.imgig.bits_per_pixel, &game.imgig.line_length, &game.imgig.endian);
		// char **map = parse->map;
	game.map_ig = malloc(sizeof(char *) * parse->map_height + 1);
	for (int i = 0; parse->map[i]; i++)
		game.map_ig[i] = ft_strdup(parse->map[i]);

	game_loop(game, game.imgig, game.numig.pos_x, game.numig.pos_y, game.numig.dir_x, game.numig.dir_y, game.numig.plane_x, game.numig.plane_y, game.map_ig);

	mlx_put_image_to_window(game.mlx, game.window, game.imgig.img, 0, 0); // redraw();
	mlx_hook(game.window, 17, (1L << 17), exit_game, &game);
 	mlx_hook(game.window, 2, (1L << 0), key_press_hook, &game); //readKeys();
	mlx_loop(game.mlx);
}
