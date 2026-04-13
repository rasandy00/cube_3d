/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 07:59:39 by andriamr          #+#    #+#             */
/*   Updated: 2026/04/13 18:21:17 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	utils_trim_line(t_map *map, char *line, int i)
{
	map->grid[i] = ft_strtrim(line, "\n");
	if (!map->grid[i])
		return (1);
	return (0);
}

static int	count_player(t_map *map)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (ft_strchr("NEWS", map->grid[i][j]))
			{
				map->player_x = j;
				map->player_y = i;
				map->player_dir = map->grid[i][j];
				player++;
			}
			j++;
		}
		i++;
	}
	return (player);
}

// int	parse_map(int fd, t_game *game)
// {
// 	char	*line;
// 	int		i;
// 	int		player_count;

// 	game->map.grid = ft_calloc(10000, sizeof(char *));
// 	if (!game->map.grid)
// 		return (print_error("Memory error"), 1);
// 	i = 0;
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		if (line[0] == '\n')
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		if (utils_trim_line(&game->map, line, i) != 0)
// 			return (free(line), print_error("Memory error"), 1);
// 		free(line);
// 		i++;
// 	}
// 	game->map.grid[i] = NULL;
// 	game->map.height = i;
// 	if (i == 0)
// 		return (print_error("Empty map"), 1);
// 	player_count = count_player(&game->map);
// 	if (player_count == 0)
// 		return (print_error("No player"), 1);
// 	if (player_count > 1)
// 		return (print_error("Multiple players"), 1);
// 	return (0);
// }


static int	validate_map_state(t_map *map)
{
	int	p_count;

	if (map->height == 0)
	{
		print_error("Empty map");
		return (1);
	}
	p_count = count_player(map);
	if (p_count == 0)
	{
		print_error("No player");
		return (1);
	}
	if (p_count > 1)
	{
		print_error("Multiple players");
		return (1);
	}
	return (0);
}

static int	read_map_lines(int fd, t_map *map)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
		{
			if (utils_trim_line(map, line, i) != 0)
			{
				free(line);
				return (-1);
			}
			i++;
		}
		free(line);
	}
	return (i);
}

int	parse_map(int fd, t_game *game)
{
	int	i;

	game->map.grid = ft_calloc(10000, sizeof(char *));
	if (!game->map.grid)
	{
		print_error("Memory error");
		return (1);
	}
	i = read_map_lines(fd, &game->map);
	if (i == -1)
	{
		print_error("Memory error");
		return (1);
	}
	game->map.grid[i] = NULL;
	game->map.height = i;
	return (validate_map_state(&game->map));
}
