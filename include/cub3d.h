/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:19:22 by bgales            #+#    #+#             */
/*   Updated: 2023/04/26 15:40:52 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# define PI 3.1415926535

// *****************************************************************************
// Personal library

# include "libft.h"
# include "structures.h"
# include "parse.h"
# include "utils.h"
# include "game.h"

char	*get_next_line(int fd);
#endif