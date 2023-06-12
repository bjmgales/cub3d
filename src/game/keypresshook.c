/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypresshook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:04:58 by bgales            #+#    #+#             */
/*   Updated: 2023/06/12 17:05:23 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int key_press_hook(int keycode, void *params)
{
	t_game *game = (t_game *)params;
	char **map_ig = game->map_ig;
	// game->nmig.start = time_calculator();

	game->numig.old_time = game->numig.time;
	game->numig.time = time_calculator() - game->numig.start;
	//printf("VALEUR DE START %f\n", game->numig.start);
    game->numig.frame_time = (game->numig.time - game->numig.old_time) / 1000.0; //frame_time is the time this frame has taken, in seconds

	printf("FPS %f\n", game->numig.frame_time);
	printf("---- time %f\n", game->numig.time);
	printf("old_time %f\n", game->numig.old_time);

    //speed modifiers
    // game->numig.move_speed = game->numig.frame_time * 5.0; //the constant value is in squares/second
	// printf("---- game->numig.move_speed : %f\n",game->numig.move_speed);
    // game->numig.rot_speed = game->numig.frame_time * 3.0; //the constant value is in radians/second

	game->numig.move_speed = 0.17;
	game->numig.rot_speed = 0.10;


	// printf("vec %f %f\n", game->numig.plane_x, game->numig.plane_y);
	// printf("pos play %f %f\n", game->numig.pos_x, game->numig.pos_y);
	// printf ("pos_x %f\n", game->numig.pos_x);
	// printf ("dir_x %f\n", game->numig.dir_x);
	// printf ("MS %f\n", game->numig.move_speed);
	// printf ("pos_y %f\n", game->numig.pos_y);
	if (keycode == 53)
		exit_game();

//move up
if (keycode == 13 || keycode == 126)
{
    if (map_ig[(int)(game->numig.pos_y + game->numig.dir_y * game->numig.move_speed)][(int)game->numig.pos_x] == '0')
        game->numig.pos_y += game->numig.dir_y * game->numig.move_speed;
    if (map_ig[(int)game->numig.pos_y][(int)(game->numig.pos_x + game->numig.dir_x * game->numig.move_speed)] == '0')
        game->numig.pos_x += game->numig.dir_x * game->numig.move_speed;
}

//move down
if (keycode == 1 || keycode == 125)
{
    if (map_ig[(int)(game->numig.pos_y - game->numig.dir_y * game->numig.move_speed)][(int)game->numig.pos_x] == '0')
        game->numig.pos_y -= game->numig.dir_y * game->numig.move_speed;
    if (map_ig[(int)game->numig.pos_y][(int)(game->numig.pos_x - game->numig.dir_x * game->numig.move_speed)] == '0')
        game->numig.pos_x -= game->numig.dir_x * game->numig.move_speed;
}
	//move left
	if (keycode == 0)
    {
		//exit(0);
     	if(map_ig[(int)(game->numig.pos_y + game->numig.plane_y * game->numig.move_speed)][(int)game->numig.pos_x] == '0')
			game->numig.pos_x += game->numig.plane_x * game->numig.move_speed;
      	if(map_ig[(int)game->numig.pos_y][(int)(game->numig.pos_x + game->numig.plane_x * game->numig.move_speed)] == '0')
			game->numig.pos_y += game->numig.plane_y * game->numig.move_speed;
   	}
	//move right
	if (keycode == 2)
    {
		//exit(0);
     	if(map_ig[(int)(game->numig.pos_y + game->numig.plane_y * game->numig.move_speed)][(int)game->numig.pos_x] == '0')
			game->numig.pos_x -= game->numig.plane_x * game->numig.move_speed;
      	if(map_ig[(int)game->numig.pos_y][(int)(game->numig.pos_x + game->numig.plane_x * game->numig.move_speed)] == '0')
			game->numig.pos_y -= game->numig.plane_y * game->numig.move_speed;
   	}

	//rotate left
   if (keycode == 123)
    {
		printf("Pressed A\n");
      //both camera direction and camera plane must be rotated
      	double oldDir_x = game->numig.dir_x;
      	game->numig.dir_x = game->numig.dir_x * cos(-game->numig.rot_speed) - game->numig.dir_y * sin(-game->numig.rot_speed);
      	game->numig.dir_y = oldDir_x * sin(-game->numig.rot_speed) + game->numig.dir_y * cos(-game->numig.rot_speed);
      	double oldPlane_x = game->numig.plane_x;
      	game->numig.plane_x = game->numig.plane_x * cos(-game->numig.rot_speed) - game->numig.plane_y * sin(-game->numig.rot_speed);
      	game->numig.plane_y = oldPlane_x * sin(-game->numig.rot_speed) + game->numig.plane_y * cos(-game->numig.rot_speed);

   	}
    //rotate to the right
    if (keycode == 124)
    {
		printf("Pressed D\n");
      //both camera direction and camera plane must be rotated
      	double oldDir_x = game->numig.dir_x;
      	game->numig.dir_x = game->numig.dir_x * cos(game->numig.rot_speed) - game->numig.dir_y * sin(game->numig.rot_speed);
      	game->numig.dir_y = oldDir_x * sin(game->numig.rot_speed) + game->numig.dir_y * cos(game->numig.rot_speed);
      	double oldPlane_x = game->numig.plane_x;
      	game->numig.plane_x = game->numig.plane_x * cos(game->numig.rot_speed) - game->numig.plane_y * sin(game->numig.rot_speed);
      	game->numig.plane_y = oldPlane_x * sin(game->numig.rot_speed) + game->numig.plane_y * cos(game->numig.rot_speed);
   	}
  	mlx_clear_window(game->mlx, game->window); // cls();
	game->imgig.img = mlx_new_image(game->mlx, 1024, 720);
	game->imgig.addr = mlx_get_data_addr(game->imgig.img, &game->imgig.bits_per_pixel, &game->imgig.line_length, &game->imgig.endian);
	game_loop(*game, game->imgig, game->numig.pos_x, game->numig.pos_y, game->numig.dir_x, game->numig.dir_y, game->numig.plane_x, game->numig.plane_y, game->map_ig);
	mlx_put_image_to_window(game->mlx, game->window, game->imgig.img, 0, 0); // redraw();
	return 0;
}
