/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 08:02:36 by andriamr          #+#    #+#             */
/*   Updated: 2026/04/13 16:52:08 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	utils_init_player(t_game *game)
{
	game->player.x = game->map.player_x + 0.5;
	game->player.y = game->map.player_y + 0.5;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0;
}

void	init_player_dir(t_game *game)
{
	utils_init_player(game);
	if (game->map.player_dir == 'N')
	{
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
	}
	else if (game->map.player_dir == 'S')
	{
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
	}
	else if (game->map.player_dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_y = 0.66;
	}
	else if (game->map.player_dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.plane_y = -0.66;
	}
}

int	game_loop(t_game *game)
{
	if (game->keys[KEY_LEFT])
		rotate_player(game, -ROT_SPEED);
	if (game->keys[KEY_RIGHT])
		rotate_player(game, ROT_SPEED);
	move_player(game);
	render_frame(game);
	return (0);
}

void	init_game(t_game *game)
{
	init_player_dir(game);
	ft_memset(game->keys, 0, sizeof(game->keys));
}
