/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctardy <ctardy@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:15:15 by bgales            #+#    #+#             */
/*   Updated: 2023/06/12 16:23:08 by ctardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

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

int malloc_texture(t_game *game)
{
    int i = 0;
    game->texig.buffer = malloc(sizeof(int *) * game->window_height);
    if (game->texig.buffer == NULL) {
        // Handle allocation failure
        return -1;
    }

    while (i < game->window_height)
    {
        game->texig.buffer[i] = malloc(sizeof(int) * game->window_width);
        if (game->texig.buffer[i] == NULL) {
            // Handle allocation failure
            return -1;
        }
        i++;
    }

    game->texig.texture = malloc(sizeof(int *) * 8);
    if (game->texig.texture == NULL) {
        // Handle allocation failure
        return -1;
    }

    for (int i = 0; i < 8; i++) {
        game->texig.texture[i] = malloc(sizeof(int) * (64 * 64));
        if (game->texig.texture[i] == NULL) {
            // Handle allocation failure
            return -1;
        }
    }
    
    return 0;
}

void free_texture(t_game *game)
{
    // Free game->texig.buffer
    for (int i = 0; i < game->window_height; i++) {
        free(game->texig.buffer[i]);
    }
    free(game->texig.buffer);

    // Free game->texig.texture
    for (int i = 0; i < 8; i++) {
        free(game->texig.texture[i]);
    }
    free(game->texig.texture);
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
	
	
	game.texig.texture_width = 64;
	game.texig.texture_height = 64;

	game.window_height = 720;
	game.window_width = 1024;
	malloc_texture(&game);
	//exit(0);
	//game.texig.buffer[0][2] = 21;
	for(int x = 0; x < game.texig.texture_width; x++) {
		for(int y = 0; y < game.texig.texture_height; y++)
		{
			//printf("game.texig.texture_width : %d\n", game.texig.texture_width);
			int xorcolor = (x * 256 / game.texig.texture_width) ^ (y * 256 / game.texig.texture_height);
			//int xcolor = x * 256 / game.texig.texture_width;
			int ycolor = y * 256 / game.texig.texture_height;
			int xycolor = y * 128 / game.texig.texture_height + x * 128 / game.texig.texture_width;
			game.texig.texture[0][game.texig.texture_width * y + x] = 65536 * 254 * (x != y && x != game.texig.texture_width - y); //flat red texture with black cross
			game.texig.texture[1][game.texig.texture_width * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			game.texig.texture[2][game.texig.texture_width * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			game.texig.texture[3][game.texig.texture_width * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			game.texig.texture[4][game.texig.texture_width * y + x] = 256 * xorcolor; //xor green
			game.texig.texture[5][game.texig.texture_width * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			game.texig.texture[6][game.texig.texture_width * y + x] = 65536 * ycolor; //red gradient
			game.texig.texture[7][game.texig.texture_width * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}

	game_loop(game, game.imgig, game.numig.pos_x, game.numig.pos_y, game.numig.dir_x, game.numig.dir_y, game.numig.plane_x, game.numig.plane_y, game.map_ig);

	mlx_put_image_to_window(game.mlx, game.window, game.imgig.img, 0, 0); // redraw();
	mlx_hook(game.window, 17, (1L << 17), exit_game, &game);
 	mlx_hook(game.window, 2, (1L << 0), key_press_hook, &game); //readKeys();
	// free_texture(&game);
	mlx_loop(game.mlx);
}
