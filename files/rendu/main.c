#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (print_error("Usage: ./cub3D <map.cub>"), 1);
	ft_memset(&game, 0, sizeof(t_game));
	game.floor_color = -1;
	game.ceiling_color = -1;
	if (parse_file(argv[1], &game) != 0)
		return (free_game(&game), 1);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (print_error("MLX initialization failed"), free_game(&game), 1);
	if (load_textures(&game) != 0)
		return (free_game(&game), 1);
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!game.win)
		return (print_error("Window creation failed"), free_game(&game), 1);
	game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.img_addr = mlx_get_data_addr(game.img, &game.img_bpp,
			&game.img_line_len, &game.img_endian);
	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
