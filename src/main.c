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

// int	minimap_test(t_game *game)
// {
// 	return (0);
// }

void print_map(t_game *game, t_data img)
{
	int y = -1;
	int x = -1;
	int map_width = game->parse->map_width;
	int map_height = game->parse->map_height;
	int minimap_width = 200;
	int minimap_height = 200;
	int draw_x;
	int draw_y;
	int cubesize = 5;


	while (++y < map_height)
	{
		while (game->map_ig[y][++x])
		{
			if (game->map_ig[y][x] == '1')
			{
				draw_x = (x * minimap_width) / map_width;
				draw_y = (y * minimap_height) / map_height;

				draw(img, draw_x, (int[2]){draw_y, draw_y + cubesize}, 16711680);
				draw(img, draw_x, (int[2]){draw_y, draw_y + cubesize}, 16711680);
				for (int i = draw_x; i < draw_x + 5; i++)
					draw(img, i, (int[2]){draw_y, draw_y + cubesize}, 16711680);

			}
		}
		x = -1;
	}

	int player_x = (game->numig.pos_x * minimap_width) / map_width - (5 / 2);
	int player_y = (game->numig.pos_y * minimap_height) / map_height - (5 / 2);

	draw(img, player_x, (int[2]){player_y, player_y + 1}, 711680);

}

void	set_image(t_game *game, t_data *img, char *path);

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
	game.window = mlx_new_window(game.mlx, game.window_width, game.window_height, "cub5D");
	game.imgig.img = mlx_new_image(game.mlx,  game.window_width, game.window_height);
	game.imgig.addr = mlx_get_data_addr(game.imgig.img,
			&game.imgig.bits_per_pixel, &game.imgig.line_length,
			&game.imgig.endian);
	game.minimap.img = mlx_new_image(game.mlx,  200, 200);
	game.minimap.addr = mlx_get_data_addr(game.minimap.img,
			&game.minimap.bits_per_pixel, &game.minimap.line_length,
			&game.minimap.endian);

	// j'minstall tsé ---------------

	set_image(&game, &game.texig.no, "./ressources/textures/NO.xpm");
	set_image(&game, &game.texig.so, "./ressources/textures/SO.xpm");
	set_image(&game, &game.texig.ea, "./ressources/textures/EA.xpm");
	set_image(&game, &game.texig.we, "./ressources/textures/WE.xpm");

	game_loop(game, game.imgig);
	print_map(&game, game.minimap);
	mlx_put_image_to_window(game.mlx, game.window, game.imgig.img, 0, 0);
	mlx_put_image_to_window(game.mlx, game.window, game.minimap.img, 0, 0);
	// mlx_hook(game.window, 17, (1L << 17), exit_game, &game);
	// mlx_hook(game.window, 2, (1L << 0), key_press_hook, &game);
	mlx_hook(game.window, 2, 0, lock_key, &game);
	mlx_hook(game.window, 3, 0, unlock_key, &game);
	// mlx_hook(game.window, 2, (1L << 0), minimap_test, &game);
	mlx_loop_hook(game.mlx, key_events, &game);
	mlx_loop(game.mlx);
}
