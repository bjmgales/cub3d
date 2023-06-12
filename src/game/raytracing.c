 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:16:58 by ctardy            #+#    #+#             */
/*   Updated: 2023/06/12 11:38:17 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h>
#include <sys/time.h>

// char *game.map_ig[] =
// {
//   "111111111111111111111111",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000222220000303030001",
//   "100000200020000000000001",
//   "100000200020000300030001",
//   "100000200020000000000001",
//   "100000220220000303030001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001111111111111111111111111",
//   "100000000000000000000000000000000000000000000001",
//   "100000000000000000000001111111111111111111111111",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "100000000000000000000001",
//   "144444444000000000000001",
//   "140400004000000000000001",
//   "140000504000000000000001",
//   "140400004000000000000001",
//   "140444444000000000000001",
//   "140000000000000000000001",
//   "144444444000000000000001",
//   "111111111111111111111111",
// };


double v_abs(double value)
{
	if (value >= 0)
		return (value);
	else
		return (value *= -1);
}

double delta_dist_init(double d, double r)
{
	if (!r)
		d = INFINITY;
	else if (r)
		d = v_abs(1 / r);
	return (d);
}

int	color_select(int tale)
{
	int new_color;
	if (tale == 1)
		return new_color = create_trgb(0, 255, 0, 0); //red
	if (tale == 2)
		return new_color = create_trgb(0, 0, 255, 0); //green
	if (tale == 3)
		return new_color = create_trgb(0, 0, 0, 255); //blue
	if (tale == 4)
		return new_color = create_trgb(0, 0, 0, 255); //white
    return new_color = create_trgb(0, 255, 255, 0); //yellow
}

 double    time_calculator(void)
 {
	struct timeval  start;
	gettimeofday(&start, NULL);
	return ((start.tv_sec * 1000) + (start.tv_usec / 1000));
}

void game_loop(t_game game, t_data img)
{
	printf("LA BOUCLE \n");
	int w = 1024;
	int h = 720;

	// while (1)
	// {
   		for(int x = 0; x < w; x++)
    	{
			//calculate ray position and direction
			double camera_x = 2 * x / (double)w - 1; //x-coordinate in camera space
			double ray_dir_x = game.numig.dir_x - game.numig.plane_x * camera_x;
			double ray_dir_y = game.numig.dir_y - game.numig.plane_y * camera_x;
      //which box of the map we're in
   			int map_x = (int)game.numig.pos_x;
    		int map_y = (int)game.numig.pos_y;

      //length of ray from current position to next x or y-side
    		double side_dist_x=0.0;
    		double side_dist_y = 0.0;

       //length of ray from one x or y-side to next x or y-side
		// TRY LATER WITH MATH.H INFINITY
			double delta_dist_x = delta_dist_init(0, ray_dir_x);
			double delta_dist_y = delta_dist_init(0, ray_dir_y);
			double perp_wall_dist;

      //what direction to step in x or y-direction (either +1 or -1)
		    int step_x = 0.0;
    		int step_y=0.0;

		    int hit = 0; //was there a wall hit?
    		int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
			if (ray_dir_x < 0)
			{
				step_x = -1;
				side_dist_x = (game.numig.pos_x - map_x) * delta_dist_x;
      		}
			else
			{
				step_x = 1;
				side_dist_x = (map_x + 1.0 - game.numig.pos_x) * delta_dist_x;
			}
		    if (ray_dir_y < 0)
			{
				step_y = -1;
				side_dist_y = (game.numig.pos_y - map_y) * delta_dist_y;
			}
			else
			{
				step_y = 1;
				side_dist_y = (map_y + 1.0 - game.numig.pos_y) * delta_dist_y;
			}

			//perform DDA
			while (hit == 0)
      		{
        	//jump to next map square, either in x-direction, or in y-direction
        		if (side_dist_y < side_dist_x)
        		{
          			side_dist_y += delta_dist_y;
          			map_y += step_y;
          			side = 0;
       			}
        		else
        		{
          			side_dist_x += delta_dist_x;
          			map_x += step_x;
          			side = 1;
        		}
        //Check if ray has hit a wall
        		if (game.map_ig[map_y][map_x] > '0')
					hit = 1;

      		}

      //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
      		if (side == 0)
				perp_wall_dist = (side_dist_y - delta_dist_y);
      		else
				perp_wall_dist = (side_dist_x - delta_dist_x);

      //Calculate height of line to draw on screen
    		int line_height = (int)(h / perp_wall_dist);

      //calculate lowest and highest pixel to fill in current stripe
    		int *se_draw = malloc(sizeof(int) * 2);
			se_draw[0] = -line_height / 2 + h / 2;
    		if (se_draw[0] < 0)
				se_draw[0] = 0;
      		se_draw[1] = line_height / 2 + h / 2;
    		if (se_draw[1] >= h)
				se_draw[1] = h - 1;

     	 //choose wall color
			int color;
			color = color_select(game.map_ig[map_y][map_x]);

      //give x and y sides different brightness
		    if (side == 1)
				color = color / 2;

    		 //draw the pixels of the stripe as a vertical line
	  		draw(img, x, se_draw, color);
			printf("lol\n");
			free(se_draw);
	  		//verLine(x, draw_start, draw_end, color);
    	 }

}

int exit_game(void)
{
	exit(0);
}



