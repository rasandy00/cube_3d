#include "cub3d.h"

static int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (1);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (1);
	return (0);
}

int	parse_file(char *filename, t_game *game)
{
	int	fd;

	if (check_extension(filename) != 0)
		return (print_error("Invalid file extension"), 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_error("Cannot open file"), 1);
	if (parse_config(fd, game) != 0)
		return (close(fd), 1);
	if (parse_map(fd, game) != 0)
		return (close(fd), 1);
	close(fd);
	if (validate_map(game) != 0)
		return (1);
	return (0);
}
