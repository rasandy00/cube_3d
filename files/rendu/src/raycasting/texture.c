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

void	draw_texture_line(t_game *game, t_ray *ray, int x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	int		tex_y;
	int		tex_index;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
	if (draw_end >= SCREEN_HEIGHT)
		draw_end = SCREEN_HEIGHT - 1;
	tex_index = get_tex_index(ray);
	wall_x = get_wall_x(game, ray);
	tex_x = (int)(wall_x * (double)game->tex[tex_index].width);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = game->tex[tex_index].width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = game->tex[tex_index].width - tex_x - 1;
	step = (double)game->tex[tex_index].height / line_height;
	tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
	y = 0;
	while (y < draw_start)
		my_mlx_pixel_put(game, x, y++, game->ceiling_color);
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (game->tex[tex_index].height - 1);
		tex_pos += step;
		color = *(int *)(game->tex[tex_index].addr + tex_y
				* game->tex[tex_index].line_len + tex_x
				* (game->tex[tex_index].bpp / 8));
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
	while (y < SCREEN_HEIGHT)
		my_mlx_pixel_put(game, x, y++, game->floor_color);
}
