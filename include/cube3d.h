/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:43:48 by codespace         #+#    #+#             */
/*   Updated: 2026/02/20 08:21:23 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUBE3D_H
#define CUBE3D_H

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <math.h>

typedef struct  s_list
{
    char    *line;
    struct  s_list  *next;
}   t_list;

typedef struct s_img
{
    void    *img_ptr;
    char    *adres;
    int     bit_per_pix;
    int     line_len;
    int     edian;
    int     len;
    int     larg;
}   t_img;

typedef struct  s_map
{
    char    **grid;
    int     len;
    int     larg;
    char    *path_n;
    char    *path_s;
    char    *path_e;
    char    *path_w;
    int     *floor_color;
    int     *ceillign_color;
}   t_map;

typedef struct  s_ray
{
    double  posi_x;
    double  posi_y;
    double  dir_x;
    double  dri_y;
    double  plan_cam_x;
    double  plan_cam_y;
    double  cam_x;
    double  cam_y;
    double  ray_x;
    double  ray_y;
    int     map_x;
    int     map_y;
    double  side_dest_x;
    double  side_dest_y;
    double  delta_dest_x;
    double  delta_dest_y;
    int     step_x;
    int     step_y;
    int     side;
}   t_ray;

typedef struct  s_game
{
    void    *mlx_prt;
    void    *mlx_win;
    t_img   *img;
    t_map   *map;
    t_ray   *ray;
    t_img   tex[4];
}   t_game;

char	*get_next_line(int fd);


#endif