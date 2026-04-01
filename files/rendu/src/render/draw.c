#include "cub3d.h"

void	render_frame(t_game *game)
{
	raycast(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
