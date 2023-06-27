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
	game->imgig.img = mlx_new_image(game->mlx,
			game->window_width, game->window_height);
	game->imgig.addr = mlx_get_data_addr(game->imgig.img,
			&game->imgig.bits_per_pixel, &game->imgig.line_length,
			&game->imgig.endian);
}

void	init_game(t_game *game)
{
	game->parse->map[game->parse->player_y][game->parse->player_x] = '0';
	game->map_ig = game->parse->map;
	game->mlx = mlx_init();
	game->window_height = GAME_HEIGHT - 100;
	game->window_width = GAME_WIDTH;
	game->window = mlx_new_window(game->mlx, game->window_width,
			game->window_height, "cub3D");
}

void	init_all(t_game *game, int argc, char **argv)
{
	ft_memset(game, 0, sizeof(t_game));
	game->parse = parse(argv[1], argc);
	init_camera_dir(game);
	init_numig(game);
	init_game(game);
	init_img(game);
	texture_init(game);
}

#define MAX_LINES 10000
#define PIXEL_START "/* pixels */"

// Function to reverse a string
void str_reverse(char *str) {
    int start = 0;
    int end = strlen(str) - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void reverse_xpm_file(char *input_file, char *output_file) {
    int fd = open(input_file, O_RDONLY);
    if (fd == -1) {
        printf("Failed to open input file\n");
        return;
    }
    
    // Allocate the char* array
    char **arr = malloc(sizeof(char*) * 10000); // Replace 10000 by an appropriate size
    if (!arr) {
        printf("Failed to allocate memory\n");
        return;
    }
    
    char *line;
    int i = 0;
    int is_pixels_started = 0;
    int is_blank_skipped = 0;
    while ((line = get_next_line(fd)) != NULL) {
        // Remove trailing newline character
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        if (is_pixels_started && strcmp(line, "};") != 0) {
            // Skip the first blank line
            if (!is_blank_skipped && strcmp(line, "") == 0) {
                is_blank_skipped = 1;
                continue;
            }
            // Reverse each line pixel by pixel, except the last one
            str_reverse(line);
        }
        if (strcmp(line, "/* pixels */") == 0) {
            is_pixels_started = 1;
        }
        arr[i] = line;
        i++;
    }
    close(fd);
    
    // Write to the output file
    FILE *f = fopen(output_file, "w");
    if (!f) {
        printf("Failed to open output file for writing\n");
        return;
    }
    for (int j = 0; j < i; j++) {
        fputs(arr[j], f);
        // Add a new line character only if the line is not empty
        if (j < i - 1) {
            fputs("\n", f);
        }
    }
    fclose(f);
    
    // Free the memory
    for (int j = 0; j < i; j++) {
        free(arr[j]);
    }
    free(arr);
}

int	main(int argc, char **argv)
{
	t_game	game;

	reverse_xpm_file("./ressources/textures/NO.xpm", "./ressources/textures/test.xpm");
	init_all (&game, argc, argv);
	game_loop(game, game.imgig);
	mlx_put_image_to_window(game.mlx, game.window, game.imgig.img, 0, 0);
	mlx_hook(game.window, 2, 0, lock_key, &game);
	mlx_hook(game.window, 3, 0, unlock_key, &game);
	mlx_hook(game.window, 17, (1L << 17), exit_game, &game);
	mlx_loop_hook(game.mlx, key_events, &game);
	mlx_loop(game.mlx);
}
