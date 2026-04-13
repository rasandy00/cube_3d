/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 08:00:17 by andriamr          #+#    #+#             */
/*   Updated: 2026/04/13 15:37:50 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_map_char(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (!ft_strchr("01 NEWS", map->grid[i][j]))
				return (print_error("Invalid character") , 1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	flood_fill(t_map *map, char **visited, int i, int j)
{
	if (i < 0 || j < 0 || i >= map->height || j >= (int)ft_strlen(map->grid[i]))
		return (1);
	if (visited[i][j] == '1' || map->grid[i][j] == '1')
		return (0);
	// if (map->grid[i][j] == ' ')
	// 	return (1);
	visited[i][j] = '1';
	if (flood_fill(map, visited, i + 1, j) != 0)
		return (1);
	if (flood_fill(map, visited, i - 1, j) != 0)
		return (1);
	if (flood_fill(map, visited, i, j + 1) != 0)
		return (1);
	if (flood_fill(map, visited, i, j - 1) != 0)
		return (1);
	return (0);
}

int	validate_map(t_game *game)
{
	char	**visited;
	int		i;

	if (check_map_char(&game->map) != 0)
		return (1);
	visited = ft_calloc(game->map.height + 1, sizeof(char *));
	if (!visited)
		return (1);
	i = 0;
	while (i < game->map.height)
	{
		visited[i] = ft_strdup(game->map.grid[i]);
		i++;
	}
	if (flood_fill(&game->map, visited, game->map.player_y,
			game->map.player_x) != 0)
	{
		ft_free_split(visited);
		return (print_error("Map not closed"), 1);
	}
	ft_free_split(visited);
	return (0);
}
