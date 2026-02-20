/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:09:58 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/19 15:21:26 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	s1 = (unsigned char *)dest;
	s2 = (unsigned char *)src;
	i = 0;
	if (!dest || !src)
		return (NULL);
	if (dest <= src)
	{
		ft_memcpy(s1, s2, n);
		return (dest);
	}
	else
	{
		while (i < n)
		{
			s1[n - 1] = s2[n - 1];
			n--;
		}
	}
	return (dest);
}
/*
int main()
{
	char src[] = "sandy kely mlay be!";
	write(1, src, 20);
	write(1, "\n", 1);
	ft_memmove(src+5, src, 5);
	write (1, src, 20);
	return (0);
}*/
