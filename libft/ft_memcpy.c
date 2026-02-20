/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:00:33 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/13 18:16:52 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s, const void *src, size_t n)
{
	size_t	i;
	char	*s1;
	char	*s2;

	i = 0;
	s1 = (char *)s;
	s2 = (char *)src;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (s);
}
/*
int main()
{
	int size = 30;
	char dest[size];
	char *src;

	src = "sandy kely mlay be!";
	write(1, src, 20);
	write(1, "\n", 1);
	ft_memcpy(dest, src, 10);

	write(1, dest, 10);
	return (0);
}*/
