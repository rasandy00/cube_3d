#include "cub3d.h"

static int	store_map_line(t_map *map, char *line, int i)
{
	map->grid[i] = ft_strtrim(line, "\n");
	if (!map->grid[i])
		return (1);
	return (0);
}

static int	find_player(t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (ft_strchr("NSEW", map->grid[i][j]))
			{
				map->player_x = j;
				map->player_y = i;
				map->player_dir = map->grid[i][j];
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

int	parse_map(int fd, t_game *game)
{
	char	*line;
	int		i;
	int		player_count;

	game->map.grid = ft_calloc(10000, sizeof(char *));
	if (!game->map.grid)
		return (print_error("Memory error"), 1);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		if (store_map_line(&game->map, line, i) != 0)
			return (free(line), print_error("Memory error"), 1);
		free(line);
		i++;
	}
	game->map.grid[i] = NULL;
	game->map.height = i;
	if (i == 0)
		return (print_error("Empty map"), 1);
	player_count = find_player(&game->map);
	if (player_count == 0)
		return (print_error("No player"), 1);
	if (player_count > 1)
		return (print_error("Multiple players"), 1);
	return (0);
}