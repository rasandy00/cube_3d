/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 07:59:59 by andriamr          #+#    #+#             */
/*   Updated: 2026/04/13 18:17:31 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_config(int fd, t_game *game)
{
	char	*line;
	int		count;

	count = 0;
	while (count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			return (print_error("Missing configuration"), 1);
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		if (parse_texture_path(line, game) == 0)
			count++;
		else if (parse_color_value(line, game) == 0)
			count++;
		else
			return (free(line), print_error("Invalid configuration"), 1);
		free(line);
	}
	return (0);
}

int	parse_texture_path(char *line, t_game *game)
{
	char	**split;
	int		index;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (ft_free_split(split), 1);
	if (ft_strncmp(split[0], "NO", 2) == 0)
		index = TEX_NORTH;
	else if (ft_strncmp(split[0], "SO", 2) == 0)
		index = TEX_SOUTH;
	else if (ft_strncmp(split[0], "WE", 2) == 0)
		index = TEX_WEST;
	else if (ft_strncmp(split[0], "EA", 2) == 0)
		index = TEX_EAST;
	else
		return (ft_free_split(split), 1);
	if (game->tex_paths[index] != NULL)
		return (ft_free_split(split), print_error("Duplicate texture"), 1);
	game->tex_paths[index] = ft_strtrim(split[1], "\n");
	ft_free_split(split);
	return (0);
}

// int	parse_color_value(char *line, t_game *game)
// {
// 	char	**split;
// 	char	**rgb;
// 	int		r;
// 	int		g;
// 	int		b;
// 	int		is_floor;

// 	split = ft_split(line, ' ');
// 	if (!split || !split[0] || !split[1])
// 		return (ft_free_split(split), 1);
// 	if (ft_strncmp(split[0], "F", 1) == 0)
// 		is_floor = 1;
// 	else if (ft_strncmp(split[0], "C", 1) == 0)
// 		is_floor = 0;
// 	else
// 		return (ft_free_split(split), 1);
// 	rgb = ft_split(split[1], ',');
// 	ft_free_split(split);
// 	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
// 		return (ft_free_split(rgb), print_error("Invalid color format"), 1);
// 	r = ft_atoi(rgb[0]);
// 	g = ft_atoi(rgb[1]);
// 	b = ft_atoi(rgb[2]);
// 	ft_free_split(rgb);
// 	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
// 		return (print_error("Color out of range"), 1);
// 	if (is_floor)
// 	{
// 		if (game->floor_color != -1)
// 			return (print_error("Duplicate floor color"), 1);
// 		game->floor_color = create_trgb(0, r, g, b);
// 	}
// 	else
// 	{
// 		if (game->ceiling_color != -1)
// 			return (print_error("Duplicate ceiling color"), 1);
// 		game->ceiling_color = create_trgb(0, r, g, b);
// 	}
// 	return (0);
// }


static int	assign_game_color(t_game *game, int is_floor, int color)
{
	if (is_floor)
	{
		if (game->floor_color != -1)
		{
			print_error("Duplicate floor color");
			return (1);
		}
		game->floor_color = color;
	}
	else
	{
		if (game->ceiling_color != -1)
		{
			print_error("Duplicate ceiling color");
			return (1);
		}
		game->ceiling_color = color;
	}
	return (0);
}

static int	parse_rgb(char *rgb_str, int *color)
{
	char	**rgb;
	int		c[3];

	rgb = ft_split(rgb_str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		print_error("Invalid color format");
		return (ft_free_split(rgb), 1);
	}
	c[0] = ft_atoi(rgb[0]);
	c[1] = ft_atoi(rgb[1]);
	c[2] = ft_atoi(rgb[2]);
	ft_free_split(rgb);
	if (c[0] < 0 || c[0] > 255 || c[1] < 0 || c[1] > 255
		|| c[2] < 0 || c[2] > 255)
	{
		print_error("Color out of range");
		return (1);
	}
	*color = create_trgb(0, c[0], c[1], c[2]);
	return (0);
}

int	parse_color_value(char *line, t_game *game)
{
	char	**split;
	int		is_floor;
	int		color;
	int		ret;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (ft_free_split(split), 1);
	if (ft_strncmp(split[0], "F", 2) == 0)
		is_floor = 1;
	else if (ft_strncmp(split[0], "C", 2) == 0)
		is_floor = 0;
	else
		return (ft_free_split(split), 1);
	ret = parse_rgb(split[1], &color);
	ft_free_split(split);
	if (ret)
		return (1);
	return (assign_game_color(game, is_floor, color));
}
