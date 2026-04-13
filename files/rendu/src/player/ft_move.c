/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 08:00:48 by andriamr          #+#    #+#             */
/*   Updated: 2026/04/13 14:43:37 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED;
	if (check_collision(game, new_x, game->player.y) == 0)
		game->player.x = new_x;
	if (check_collision(game, game->player.x, new_y) == 0)
		game->player.y = new_y;
}

static void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.dir_x * MOVE_SPEED;
	new_y = game->player.y - game->player.dir_y * MOVE_SPEED;
	if (check_collision(game, new_x, game->player.y) == 0)
		game->player.x = new_x;
	if (check_collision(game, game->player.x, new_y) == 0)
		game->player.y = new_y;
}

static void	strafe_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x - game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y - game->player.plane_y * MOVE_SPEED;
	if (check_collision(game, new_x, game->player.y) == 0)
		game->player.x = new_x;
	if (check_collision(game, game->player.x, new_y) == 0)
		game->player.y = new_y;
}

static void	strafe_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.plane_x * MOVE_SPEED;
	new_y = game->player.y + game->player.plane_y * MOVE_SPEED;
	if (check_collision(game, new_x, game->player.y) == 0)
		game->player.x = new_x;
	if (check_collision(game, game->player.x, new_y) == 0)
		game->player.y = new_y;
}

void	move_player(t_game *game)
{
	if (game->keys[KEY_W])
		move_forward(game);
	if (game->keys[KEY_S])
		move_backward(game);
	if (game->keys[KEY_A])
		strafe_left(game);
	if (game->keys[KEY_D])
		strafe_right(game);
}
