/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:46:25 by andriamr          #+#    #+#             */
/*   Updated: 2026/02/23 08:55:10 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void    printf_map(t_map *map)
{
    int i;

    i = 0;
    printf("path_n = %s", map->path_n);
    printf("path_s = %s", map->path_s);
    printf("path_e = %s", map->path_e);
    printf("path_w = %s", map->path_w);
    printf("floor_color = %d, %d, %d\n", map->floor_color[0], map->floor_color[1], map->floor_color[2]);
    printf("ceiling_color = %d, %d, %d\n", map->ceillign_color[0], map->ceillign_color[1], map->ceillign_color[2]);

    printf("len = %d\n", map->len);
    printf("larg = %d\n", map->larg);
    while (map->grid[i])
    {
        printf("%s\n", map->grid[i]);
        i++;
    }
    printf("\n");
}   

int  main(int ac, char **av)
{
    t_map *map;

    if (ac != 2)
    {
        printf("Error\n");
        return (1);
    }
    map = ft_parsing(av[1]);
    if (!map)
    {
        printf("Error map\n");
        return (1);
    }
    printf_map(map);
    return (0);
}