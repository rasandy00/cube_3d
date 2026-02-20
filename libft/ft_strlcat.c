/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andriamr <andriamr@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:13:33 by andriamr          #+#    #+#             */
/*   Updated: 2025/03/19 09:05:52 by andriamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;
	size_t	j;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (len_src);
	if (len_dst >= size)
		return (len_src + size);
	j = len_dst;
	while (j < size - 1 && src[i])
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (len_src + len_dst);
}
/*
int main ()
{
	char *src;
	char *dest;
	src = "12fff44";
	dest = "12fgfdfdsfdgarfdfd344";
	printf ("len of src = %d\n",ft_strlen(src));
	printf ("len of dest = %d\n",ft_strlen(dest));
	printf ("len of cast = %d\n",ft_strlcat(src, dest, 4));
	printf ("len of cast original = %d\n",strlcat(src, dest, 4));
	return (0);
}*/
