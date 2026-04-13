/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 08:01:53 by andriamr          #+#    #+#             */
/*   Updated: 2026/04/13 17:58:10 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_tex_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (TEX_EAST);
		return (TEX_WEST);
	}
	if (ray->step_y > 0)
		return (TEX_SOUTH);
	return (TEX_NORTH);
}

static double	get_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = game->player.x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
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

int	calc_tex_x(t_game *game, t_ray *ray, int t_idx)
{
	int		t_x;
	double	wall_x;

	wall_x = get_wall_x(game, ray);
	t_x = (int)(wall_x * (double)game->tex[t_idx].width);
	if (ray->side == 0 && ray->dir_x > 0)
		return (game->tex[t_idx].width - t_x - 1);
	if (ray->side == 1 && ray->dir_y < 0)
		return (game->tex[t_idx].width - t_x - 1);
	return (t_x);
}

void	init_draw(t_game *game, t_ray *ray, t_draw *d)
{
	d->line_h = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	d->start = -d->line_h / 2 + SCREEN_HEIGHT / 2;
	if (d->start < 0)
		d->start = 0;
	d->end = d->line_h / 2 + SCREEN_HEIGHT / 2;
	if (d->end >= SCREEN_HEIGHT)
		d->end = SCREEN_HEIGHT - 1;
	d->t_idx = get_tex_index(ray);
	d->t_x = calc_tex_x(game, ray, d->t_idx);
	d->step = (double)game->tex[d->t_idx].height / d->line_h;
	d->t_pos = (d->start - SCREEN_HEIGHT / 2 + d->line_h / 2) * d->step;
}

void	draw_texture_line(t_game *game, t_ray *ray, int x)
{
	t_draw	d;
	int		y;

	init_draw(game, ray, &d);
	y = 0;
	while (y < d.start)
		my_mlx_pixel_put(game, x, y++, game->ceiling_color);
	while (y < d.end)
	{
		my_mlx_pixel_put(game, x, y++, get_tex_color(game, &d));
		d.t_pos += d.step;
	}
	while (y < SCREEN_HEIGHT)
		my_mlx_pixel_put(game, x, y++, game->floor_color);
}
