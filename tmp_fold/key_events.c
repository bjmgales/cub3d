/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:15:37 by bgales            #+#    #+#             */
/*   Updated: 2023/04/26 15:15:32 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	endgame(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	print_free_exit("Thanks for playing !\n", &game);
}

int	key_events(int keycode, t_game *game)
{
	if (keycode == ECHAP)
		endgame(game);
	if (keycode == W_KEY || keycode == ARROW_UP)
		move_up(game);
	if (keycode == S_KEY || keycode == ARROW_DOWN)
		move_down(game);
	if (keycode == A_KEY || keycode == ARROW_LEFT
		|| keycode == D_KEY || keycode == ARROW_RIGHT)
		rotate(game, keycode);
	return (0);
}
