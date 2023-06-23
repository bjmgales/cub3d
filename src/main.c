/* ************************************************************************** */
/*				            */
/*				        :::      ::::::::   */
/*   main.c				             :+:      :+:    :+:   */
/*				    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*				+#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:22:05 by bgales            #+#    #+#             */
/*   Updated: 2025/06/15 15:55:08 by bgales           ###   ########.fr       */
/*				            */
/* ************************************************************************** */

#include "cub3d.h"

t_parse	*parse(char *map_path, int argc)
{
	t_parse	*parse;
	char	**cub_file;

	cub_file = NULL;
	parse = malloc(sizeof(t_parse));
	if (argc != 2)
	{
		printf("Wrong argument format");
		exit (0);
	}
	parser(&parse, cub_file, map_path);
	return (parse);
}

void	init_img(t_game *game)
{
	(*game).imgig.img = mlx_new_image((*game).mlx,
			(*game).window_width, (*game).window_height);
	(*game).imgig.addr = mlx_get_data_addr((*game).imgig.img,
			&(*game).imgig.bits_per_pixel, &(*game).imgig.line_length,
			&(*game).imgig.endian);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	game.parse = parse(argv[1], argc);
	init_camera_dir(&game);
	game.parse->map[game.parse->player_y][game.parse->player_x] = '0';
	init_numig(&game);
	game.map_ig = game.parse->map;
	game.mlx = mlx_init();
	game.window_height = 720;
	game.window_width = 1024;
	game.window = mlx_new_window(game.mlx, game.window_width,
			game.window_height, "cub3D");
	init_img(&game);

	game.texig.texture_width = 64;
	game.texig.texture_height = 64;
	set_image(&game, &game.texig.no, "./ressources/textures/NO.xpm");
	set_image(&game, &game.texig.so, "./ressources/textures/SO.xpm");
	set_image(&game, &game.texig.ea, "./ressources/textures/EA.xpm");
	set_image(&game, &game.texig.we, "./ressources/textures/WE.xpm");

	game_loop(game, game.imgig);
	mlx_put_image_to_window(game.mlx, game.window, game.imgig.img, 0, 0);
	mlx_hook(game.window, 2, 0, lock_key, &game);
	mlx_hook(game.window, 3, 0, unlock_key, &game);
	mlx_loop_hook(game.mlx, key_events, &game);
	mlx_loop(game.mlx);
}
