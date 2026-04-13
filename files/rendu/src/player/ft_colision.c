/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colision.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 08:01:17 by andriamr          #+#    #+#             */
/*   Updated: 2026/04/13 16:51:52 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_collision(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x + 0.1);
	map_y = (int)(y + 0.1);
	if (game->map.grid[map_y][map_x] == '1')
		return (1);
	map_x = (int)(x - 0.1);
	map_y = (int)(y - 0.1);
	if (game->map.grid[map_y][map_x] == '1')
		return (1);
	map_x = (int)(x - 0.1);
	map_y = (int)(y + 0.1);
	if (game->map.grid[map_y][map_x] == '1')
		return (1);
	map_x = (int)(x + 0.1);
	map_y = (int)(y - 0.1);
	if (game->map.grid[map_y][map_x] == '1')
		return (1);
	return (0);
}
