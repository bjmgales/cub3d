/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:15:15 by bgales            #+#    #+#             */
/*   Updated: 2023/06/12 16:06:02 by bgales           ###   ########.fr       */
/*                                                                            */
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
	game.window = mlx_new_window(game.mlx, 1024, 720, "cub3D");
	game.imgig.img = mlx_new_image(game.mlx, 1024, 720);
	game.imgig.addr = mlx_get_data_addr(game.imgig.img,
			&game.imgig.bits_per_pixel, &game.imgig.line_length,
			&game.imgig.endian);
	game_loop(game, game.imgig, game.numig.pos_x, game.numig.pos_y,
		game.numig.dir_x, game.numig.dir_y, game.numig.plane_x,
		game.numig.plane_y, game.parse->map);
	mlx_put_image_to_window(game.mlx, game.window, game.imgig.img, 0, 0);
	mlx_hook(game.window, 17, (1L << 17), exit_game, &game);
	mlx_hook(game.window, 2, (1L << 0), key_press_hook, &game);
	mlx_loop(game.mlx);
}
