#include "cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	game->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	game->keys[keycode] = 0;
	return (0);
}

int	close_window(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}
