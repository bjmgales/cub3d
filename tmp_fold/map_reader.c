/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:49:49 by ctardy            #+#    #+#             */
/*   Updated: 2023/06/08 15:48:41 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_reader(t_game *game, char **argv, int flag)
{
	// int		fd;
	// char	*inter;
	// int		count;

	// count = 0;
	// fd = open(argv[1], O_RDONLY);
	// if (flag)
	// 	game->mapstr.map = (char **)malloc(sizeof(char *) * flag);
	// while("oh yeah")
	// {
	// 	inter = get_next_line(fd);
	// 	if (flag)
	// 		game->mapstr.map[count] = inter;
	// 	count++;
	// 	if (!inter)
	// 		break ;
	// 	free(inter);
	// }
	// close (fd);
	// if (!flag)
	// 	return (count);
	// return (0);
	(void)game;
	(void)argv;
	(void)flag;
	return 24;
}