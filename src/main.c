/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:46:25 by andriamr          #+#    #+#             */
/*   Updated: 2026/02/20 07:56:19 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int  main(int ac, char **av)
{
    int fd;
    int i;
    char *line;
    
    i = 0;
    if (ac != 2)
    {
        printf("Error\n");
        return (1);
    }
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error open\n");
        return (1);
    }
    line = get_next_line(fd);
    while (line != NULL)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    return (0);
}