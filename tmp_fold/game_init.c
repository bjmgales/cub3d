/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:10:15 by bgales            #+#    #+#             */
/*   Updated: 2023/04/26 16:18:04 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_angles(t_game *game)
{
	game->player->pa = 2;
	game->player->pdx = cos(game->player->pa) * 0.1;
	game->player->pdy = sin(game->player->pa) * 0.1;
}

void	game_init(t_game **game)
{
	(*game)->mlx_ptr = mlx_init();
	(*game)->win_ptr = mlx_new_window((*game)->mlx_ptr,
			(((*game)->width - 1)) * 32, (((*game)->height) * 32), "cub3D");
	(*game)->player = malloc(sizeof(t_player));
	init_angles(*game);
	display(*game);
	mlx_hook((*game)->win_ptr, 02, 0L, key_events, *game);
	mlx_loop((*game)->mlx_ptr);
}
