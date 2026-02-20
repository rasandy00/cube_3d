/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:43:40 by codespace         #+#    #+#             */
/*   Updated: 2026/02/20 08:51:07 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

t_list    *ft_lstnew(char *line)
{
    t_list  *new;

    new = (t_list *)malloc(sizeof(t_list));
    if (!new)
        return (NULL);
    new->line = line;
    new->next = NULL;
    return (new);
}

t_list  *ft_add_back(t_list *lst, char *line)
{
    t_list  *new;
    t_list  *temp;

    new = ft_lstnew(line);
    if (!new)
        return (NULL);
    if (!lst)
        return (new);
    temp = lst;
    while (temp->next)
        temp = temp->next;
    temp->next = new;
    return (lst);
}

void    ft_lstclear(t_list **lst)
{
    t_list  *temp;
    t_list  *next;

    temp = *lst;
    while (temp)
    {
        next = temp->next;
        free(temp->line);
        free(temp);
        temp = next;
    }
    *lst = NULL;
}

t_list  *ft_all_file(char *path)
{
    t_list  *lst;
    char    *line;
    int     fd;

    lst = NULL;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    line = get_next_line(fd);
    while (line)
    {
        lst = ft_add_back(lst, line);
        line = get_next_line(fd);
    }
    close(fd);
    return (lst);
}

int *ft_take_color(char *str)
{
    int *color;
    char **rgb;
    int i;

    color = (int *)malloc(sizeof(int) * 3);
    if (!color)
        return (NULL);
    rgb = ft_split(str, ',');
    if (!rgb)
    {
        free(color);
        return (NULL);
    }
    i = 0;
    while (rgb[i] && i < 3)
    {
        color[i] = ft_atoi(rgb[i]);
        free(rgb[i]);
        i++;
    }
    free(rgb);
    return (color);
}

int ft_is_space(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return (1);
    return (0);
}

int ft_skip_space(char *str)
{
    int i;

    i = 0;
    while (ft_is_space(str[i]))
        i++;
    return (i);
}
    
char    **ft_take_grid(t_list *lst)
{
    char    **grid;
    int     i;
    int     count;

    count = 0;
    while (lst)
    {
        if (ft_strchr(lst->line, '1'))
            count++;
        lst = lst->next;
    }
    grid = (char **)malloc(sizeof(char *) * (count + 1));
    if (!grid)
        return (NULL);
    i = 0;
    while (lst)
    {
        if (ft_strchr(lst->line, '1'))
        {
            grid[i] = ft_strdup(lst->line);
            i++;
        }
        lst = lst->next;
    }
    grid[i] = NULL;
    return (grid);
}

int ft_take_len_grid(char **grid)
{
    int i;

    i = 0;
    while (grid[i])
        i++;
    return (i);
}

int ft_take_larg_grid(char **grid)
{
    int i;
    int max;

    i = 0;
    max = 0;
    while (grid[i])
    {
        if ((int)ft_strlen(grid[i]) > max)
            max = ft_strlen(grid[i]);
        i++;
    }
    return (max);
}

t_map   *ft_init_map(t_list *lst)
{
    t_map   *map;
    t_list  *tmp;

    tmp = lst;
    map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    while (tmp != NULL)
    {
        if (ft_strncmp(tmp->line, "NO ", 3) == 0)
            map->path_n = ft_strdup(tmp->line + 3);
        else if (ft_strncmp(tmp->line, "SO ", 3) == 0)
            map->path_s = ft_strdup(tmp->line + 3);
        else if (ft_strncmp(tmp->line, "WE ", 3) == 0)
            map->path_w = ft_strdup(tmp->line + 3);
        else if (ft_strncmp(tmp->line, "EA ", 3) == 0)
            map->path_e = ft_strdup(tmp->line + 3);
        else if (ft_strncmp(tmp->line, "F ", 2) == 0)
            map->floor_color = ft_take_color(tmp->line + 2);
        else if (ft_strncmp(tmp->line, "C ", 2) == 0)
            map->ceillign_color = ft_take_color(tmp->line + 2);
        tmp = tmp->next;
    }
    tmp = lst;
    map->grid = ft_take_grid(tmp);
    if (!map->grid)
    {
        free(map);
        return (NULL);
    }
    map->len = ft_take_len_grid(map->grid);
    map->larg = ft_take_larg_grid(map->grid);
    return (map);
}   

t_map    *ft_parsing(char *path)
{
    t_map   *map;
    t_list  *lst;
    
    lst = ft_all_file(path);
    if (!lst)
        return (NULL);
    map = ft_init_map(lst);
    ft_lstclear(&lst);
    return (map);
}
