/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:39:33 by bgales            #+#    #+#             */
/*   Updated: 2023/04/26 15:11:54 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;
	char	**cub_file;

	game = malloc(sizeof(t_game));
	if (argc != 2)
	{
		printf("Wrong argument format");
		exit (0);
	}
	parser(&game, cub_file, argv[1]);
	game_init(&game);
}
