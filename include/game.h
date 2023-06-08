/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgales <bgales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 12:39:01 by bgales            #+#    #+#             */
/*   Updated: 2023/04/26 16:19:14 by bgales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

// *****************************************************************************
// Functions - game_init.c

/*
@brief Initialize the angles for the player.

@param game   Pointer to the game structure.
*/
void			init_angles(t_game *game);

/*
@brief Initialize the game, set up the window, and start the game loop.

@param game   Pointer to the game structure.
*/
void			game_init(t_game **game);

// *****************************************************************************
// Functions - display.c

/*
@brief Draw the map walls on the screen.

@param game   Pointer to the game structure.
@param y      The y-coordinate of the map cell.
@param x      The x-coordinate of the map cell.
*/
void			draw_map(t_game *game, double y, double x);

/*
@brief Draw the player on the screen.

@param game   Pointer to the game structure.
@param i      The y-coordinate of the player.
@param j      The x-coordinate of the player.
*/
void			draw_player(t_game *game, double i, double j);

/*
@brief Display the game map and the player on the screen.

@param game   Pointer to the game structure.
*/
void			display(t_game *game);

// *****************************************************************************
// Functions - key_events.c

/*
@brief Close the game window and print a message.

@param game   Pointer to the game structure.
*/
void			endgame(t_game *game);

/*
@brief Process key events in the game.

@param keycode The code of the key that was pressed.
@param game    Pointer to the game structure.
@return        Returns 0.
*/
int				key_events(int keycode, t_game *game);

// *****************************************************************************
// Functions - move.c

/*
@brief Check if there's a wall at the given position.

@param game   Pointer to the game structure.
@param y      The Y position to check.
@param x      The X position to check.
@return       Returns 1 if there's a wall, 0 otherwise.
*/
int				is_wall(t_game *game, double y, double x);

/*
@brief Clear the previous position of the player on the map.

@param game   Pointer to the game structure.
@param i      The Y position of the player.
@param j      The X position of the player.
*/
void			clear_position(t_game *game, double i, double j);

/*
@brief Move the player up (forward) in the game.

@param game   Pointer to the game structure.
*/
void			move_up(t_game *game);

/*
@brief Move the player down (backward) in the game.

@param game   Pointer to the game structure.
*/
void			move_down(t_game *game);

/*
@brief Rotate the player in the game.

@param game    Pointer to the game structure.
@param keycode The code of the key that was pressed.
*/
void			rotate(t_game *game, int keycode);

#endif