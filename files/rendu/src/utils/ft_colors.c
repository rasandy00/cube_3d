/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 08:03:21 by andriamr          #+#    #+#             */
/*   Updated: 2026/04/13 18:35:44 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_tex_color(t_game *game, t_draw *d)
{
	char	*addr;
	int		t_y;

	t_y = (int)d->t_pos & (game->tex[d->t_idx].height - 1);
	addr = game->tex[d->t_idx].addr;
	addr += t_y * game->tex[d->t_idx].line_len;
	addr += d->t_x * (game->tex[d->t_idx].bpp / 8);
	return (*(int *)addr);
}
