/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 07:58:43 by andriamr          #+#    #+#             */
/*   Updated: 2026/04/13 15:54:46 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures(t_game *game)
{
	int	i;
	int	w;
	int	h;

	i = 0;
	while (i < 4)
	{
		if (!game->tex_paths[i])
			return (print_error("Missing texture path"), 1);
		game->tex[i].img = mlx_xpm_file_to_image(game->mlx,
				game->tex_paths[i], &w, &h);
		if (!game->tex[i].img)
			return (print_error("Failed to load texture"), 1);
		game->tex[i].addr = mlx_get_data_addr(game->tex[i].img,
				&game->tex[i].bpp, &game->tex[i].line_len,
				&game->tex[i].endian);
		game->tex[i].width = w;
		game->tex[i].height = h;
		free (game->tex_paths[i]);
		game->tex_paths[i] = NULL;
		i++;
	}
	return (0);
}
