/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 06:35:58 by andriamr          #+#    #+#             */
/*   Updated: 2026/04/13 15:35:41 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <libft.h>
# include <mlx.h>

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST 2
# define TEX_EAST 3

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
}	t_ray;

typedef struct t_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_addr;
	int			img_bpp;
	int			img_line_len;
	int			img_endian;
	t_texture	tex[4];
	char		*tex_paths[4];
	int			floor_color;
	int			ceiling_color;
	t_player	player;
	t_map		map;
	int			keys[65536];
}	t_game;

// parsing
void	free_map(t_map *map);
void	print_error(char *msg);
int		load_textures(t_game *game);
int		parse_file(char *str, t_game *game);
int		parse_map(int fd, t_game *game);
int		parse_config(int fd, t_game *game);
int		parse_texture_path(char *line, t_game *game);
int		parse_color_value(char *line, t_game *game);
int		validate_map(t_game *game);

// player
int		check_collision(t_game *game, double x, double y);
void	move_player(t_game *game);
void	rotate_player(t_game *game, double rot_speed);
//  render
void	init_player_dir(t_game *game);
void	render_frame(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
int		close_window(t_game *game);
int		game_loop(t_game *game);
void	init_game(t_game *game);
// raycasting
void	perform_dda(t_game *game, t_ray *ray);
int		raycast(t_game *game);
void	draw_texture_line(t_game *game, t_ray *ray, int x);



// utils
int		create_trgb(int t, int r, int g, int b);
void	free_game(t_game *game);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);
void	ft_free_split(char **split);

#endif