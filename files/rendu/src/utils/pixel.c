#include "cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->img_addr + (y * game->img_line_len + x * (game->img_bpp / 8));
	*(unsigned int *)dst = color;
}
