#include "cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
		if (game->tex_paths[i])
			free(game->tex_paths[i]);
		i++;
	}
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	free_map(&game->map);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}