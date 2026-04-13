/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 07:59:16 by andriamr          #+#    #+#             */
/*   Updated: 2026/04/13 16:52:40 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check_name(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 5)
		return (1);
	if (ft_strncmp(file + len - 4, ".cube", 4) != 0)
		return (1);
	return (0);
}

int	parse_file(char *str, t_game *game)
{
	int	fd;

	if (ft_check_name(str) != 0)
		return (print_error("Invalid file extension"), 1);
	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (print_error("Cannot open file"), 1);
	if (parse_config(fd, game) != 0)
		return (close (fd), 1);
	if (parse_map(fd, game) != 0)
		return (close (fd), 1);
	close (fd);
	if (validate_map(game) != 0)
		return (1);
	return (0);
}
